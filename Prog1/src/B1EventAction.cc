#include "B1EventAction.hh"
#include "B1Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "B1SteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int B1EventAction::evNo = 0;

B1EventAction::B1EventAction()
: G4UserEventAction(),
  fEdep(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{ 
B1SteppingAction::countSteps=0;
evNo++;
  //std::cout << "======== Event no : "<< evNo << "  started =======" << std::endl;
  fEdep = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{  

  
  B1Run* run 
    = static_cast<B1Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);
  std::cout << "\n========Energy deposited in  Event no : "<< evNo << "  :  "<< fEdep <<  " : No of Steps : " << B1SteppingAction::countSteps << " =======" << std::endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

