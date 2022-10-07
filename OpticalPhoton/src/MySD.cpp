/*
**	Filename : MySD.cpp
**	2022-09-27
**	username : rsehgal
*/
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "MySD.h"
#include "TH1F.h"
#include "Write.h"
int MySD::stepNum = 0;
int MySD::numOfParticlesReached = 0;
unsigned int MySD::fEventCounter = 0;
unsigned int MySD::quadCoincidenceCounter = 0;
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
  quadCoincidenceCounter = 0;
}

void MySD::Initialize(G4HCofThisEvent *hce) {
  fHitsCollection = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
  photonCounter[0] = 0;
  photonCounter[1] = 0;
  photonCounter[2] = 0;
  photonCounter[3] = 0;
  hitInPMT[0]=false;  //NORTH
  hitInPMT[1]=false;  //SOUTH
  hitInPMT[2]=false;  //EAST
  hitInPMT[3]=false;  //WEST
  photonTime[0].clear();// = 0;
  photonTime[1].clear();// = 0;
  photonTime[2].clear();// = 0;
  photonTime[3].clear();// = 0;
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
    if (touch1->GetVolume()->GetName() == "Physical_PMT_0") {
      photonTime[0].push_back(startPoint->GetGlobalTime() / ps);
      //std::cout << "time : " << (startPoint->GetGlobalTime() / ps) << std::endl;
      //std::cout <<"Energy of photon : " << track->GetVertexKineticEnergy() << std::endl;
      photonCounter[0]++;
      hitInPMT[0]=true;
    }
    if (touch1->GetVolume()->GetName() == "Physical_PMT_1") {
      photonTime[1].push_back(startPoint->GetGlobalTime() / ns);
      photonCounter[1]++;
      hitInPMT[1]=true;
    }
    if (touch1->GetVolume()->GetName() == "Physical_PMT_2") {
      photonTime[2].push_back(startPoint->GetGlobalTime() / ns);
      photonCounter[2]++;
      hitInPMT[2]=true;
    }
    if (touch1->GetVolume()->GetName() == "Physical_PMT_3") {
      photonTime[3].push_back(startPoint->GetGlobalTime() / ns);
      photonCounter[3]++;
      hitInPMT[3]=true;
    }

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
  if (1) {
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "No Of photons reached PMT_0 : " << photonCounter[0] << std::endl;
    std::cout << "No Of photons reached PMT_1 : " << photonCounter[1] << std::endl;
    std::cout << "No Of photons reached PMT_2 : " << photonCounter[2] << std::endl;
    std::cout << "No Of photons reached PMT_3 : " << photonCounter[3] << std::endl;
    std::cout << "--------------------------------------" << std::endl;
  }

  fWrite->Fill(photonCounter[0], photonCounter[1], photonCounter[2], photonCounter[3]);
  fWrite->FillTime(photonTime[0], photonTime[1], photonTime[2], photonTime[3]);
  fWrite->FillTree();

  bool quadCoincidence = hitInPMT[0] && photonCounter[0]>100 && 
                         hitInPMT[1] && photonCounter[1]>100 &&
                         hitInPMT[2] && photonCounter[2]>100 &&
			 hitInPMT[3] && photonCounter[3]>100;
  if(quadCoincidence)
	quadCoincidenceCounter++;
  if (!(fEventCounter % 10000) && fEventCounter != 0)
    std::cout << "Processed : " << fEventCounter << " Events....." << std::endl;
}
