#include "B1EventAction.hh"
#include "B1Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
//#include "Tree.h"
//#include "B1RunAction.hh"
//#include <TVector3.h>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int B1EventAction::evNo = 0;
std::vector<G4ThreeVector> B1EventAction::position({G4ThreeVector(0.,0.,0.)});

B1EventAction::B1EventAction()
: G4UserEventAction(){} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{ evNo++;
  std::cout << "======== Event no : "<< evNo << "  started =======" << std::endl;
  position.clear();
  //B1RunAction::fScatteringAngle = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{  
  B1Run* run 
    = static_cast<B1Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  std::cout << "Printing from EndOfEventAction..........."<<std::endl;

  //std::cout<<"Position Vector Size : "<< position.size() << std::endl;
  G4ThreeVector incoming = position[2]-position[0];
  G4ThreeVector outgoing = position[5]-position[3];
  G4ThreeVector ref(0.,0.,-1.);

  //Filling Tracks
  
  double angleIncoming = incoming.angle(ref);
  double angleOutgoing = outgoing.angle(ref);
  double fScatteringAngle = angleIncoming-angleOutgoing; //outgoing.angle(incoming);
  std::cout<<"Scattering Angle : " << fScatteringAngle << std::endl;
  if(std::abs(fScatteringAngle) > .001)
  run->FillScatteringAngleVector(fScatteringAngle);

}


