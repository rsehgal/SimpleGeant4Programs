/*
**	Filename : MySD.cpp
**	2022-09-27
**	username : rsehgal
*/
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "MySD.h"
#include "Write.h"
#include "TH1F.h"
int MySD::stepNum = 0;
int MySD::numOfParticlesReached = 0;
unsigned int MySD::fEventCounter = 0;

/*MySD::MySD() {
        // TODO Auto-generated constructor stub

}*/

MySD::~MySD() {
  // TODO Auto-generated destructor stub
  fWrite->Write();
}

MySD::MySD(const G4String &name, const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name), fHitsCollection(NULL) {
  collectionName.insert(hitsCollectionName);
  fWrite = new Tree("ScintillatorData.root");
}

void MySD::Initialize(G4HCofThisEvent *hce) {
  fHitsCollection = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
  photonCounter[0] = 0;
  photonCounter[1] = 0;
  photonCounter[2] = 0;
  photonCounter[3] = 0;
  fEventCounter++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool MySD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
  MyHit *newHit = new MyHit();
  G4Track *track = aStep->GetTrack();
  bool isPrimary = (track->GetParentID() == 0);
  G4StepPoint *startPoint = aStep->GetPreStepPoint();
  G4TouchableHandle touch1 = startPoint->GetTouchableHandle();
  G4String particleName = track->GetDefinition()->GetParticleName();
  if (particleName == "opticalphoton") {
    track->SetTrackStatus(fStopAndKill);
    if (touch1->GetVolume()->GetName() == "Physical_PMT_0")
      photonCounter[0]++;
    if (touch1->GetVolume()->GetName() == "Physical_PMT_1")
      photonCounter[1]++;
    if (touch1->GetVolume()->GetName() == "Physical_PMT_2")
      photonCounter[2]++;
    if (touch1->GetVolume()->GetName() == "Physical_PMT_3")
      photonCounter[3]++;
  }
  return true;
}
void MySD::EndOfEvent(G4HCofThisEvent *) {
  if (0) {
    G4int nofHits = fHitsCollection->entries();
    G4cout << G4endl << "-------->Hits Collection: in this event there are " << nofHits << " hits  " << G4endl;
    for (G4int i = 0; i < nofHits; i++)
      (*fHitsCollection)[i]->Print();
  }
  if (0) {
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "No Of photons reached PMT_0 : " << photonCounter[0] << std::endl;
    std::cout << "No Of photons reached PMT_1 : " << photonCounter[1] << std::endl;
    std::cout << "No Of photons reached PMT_2 : " << photonCounter[2] << std::endl;
    std::cout << "No Of photons reached PMT_3 : " << photonCounter[3] << std::endl;
    std::cout << "--------------------------------------" << std::endl;
  }

  fWrite->Fill(photonCounter[0], photonCounter[1], photonCounter[2], photonCounter[3]);
  if(!(fEventCounter%10000) && fEventCounter!=0)
	std::cout << "Processed : " << fEventCounter << " Events....." << std::endl;

}
