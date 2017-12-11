/*
 * MySD.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#include "MySD.h"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

/*MySD::MySD() {
	// TODO Auto-generated constructor stub

}*/

MySD::~MySD() {
	// TODO Auto-generated destructor stub
}

MySD::MySD(const G4String& name, const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

void MySD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
	std::cout<<"RAMAN Entered Initialize Of SD" << std::endl;

  fHitsCollection
    = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce

  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool MySD::ProcessHits(G4Step* aStep,
                                     G4TouchableHistory*)
{
	std::cout<<"SEHGAL Entered ProcessHits Of SD" << std::endl;
  // energy deposit


  //if (edep==0.) return false;

  MyHit* newHit = new MyHit();

/*
  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()
                                               ->GetCopyNumber());
  newHit->SetEdep(edep);
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
*/
  newHit->SetPosition(aStep->GetPostStepPoint()->GetPosition());
  G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
  newHit->SetName(touchable->GetVolume(0)->GetName());

  G4double edep = aStep->GetTotalEnergyDeposit();

  std::cout<<"Volume Name : " << newHit->GetName() << std::endl;
  std::cout<<"Energy Deposited in the Step : " << edep << std::endl;
  std::cout<<"Position : " << newHit->GetPosition() << std::endl;
  std::cout<<"Paticle Name : "<< (aStep->GetTrack()->GetDefinition()->GetParticleName()) << std::endl;

  std::cout<<" ================ Trying to fetch secondaries produced in the current step ==================" << std::endl;
  const std::vector<const G4Track*>* secondaries = aStep->GetSecondaryInCurrentStep();
  for(int i = 0 ; i < secondaries->size() ; i++){
	  std::cout << "SecondaryName : " << (secondaries->at(i))->GetDefinition()->GetParticleName() << std::endl;
  }
  std::cout<<"=============================================================================================" << std::endl;


  fHitsCollection->insert( newHit );

  //newHit->Print();

  return true;
}

void MySD::EndOfEvent(G4HCofThisEvent*)
{
  std::cout<<"RAMAN Entered EndOfEvent Of SD" << std::endl;
  //if ( verboseLevel>1 ) {
  if(1){
     G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits
            << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

