
#include "B1RunAction.hh"
#include "MyPrimaryGeneratorAction.h"
#include "MyDetectorConstruction.h"
#include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <G4FastStep.hh>
#include <string.h>
#include "B1EventAction.hh"
#include <vector>

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ofstream* B1RunAction::myfile=NULL;

double B1RunAction::fScatteringAngle = 0;

#ifdef STORE
//TTree* B1RunAction::fTree=NULL;
#endif

B1RunAction::B1RunAction()
: G4UserRunAction()
{ 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* B1RunAction::GenerateRun()
{
  return new B1Run; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{
  myfile = new ofstream(); 
  myfile->open("energy.txt");
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

#ifdef STORE
  //fRootFile = new TFile ("1234.root","RECREATE","My GEANT4 simulation") ;
  //fTree = new TTree ("BSC_DATA_TREE","My GEANT4 simulation") ;
#endif

 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{

  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  const B1Run* b1Run = static_cast<const B1Run*>(run);


  const MyDetectorConstruction* detectorConstruction
   = static_cast<const MyDetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const MyPrimaryGeneratorAction* generatorAction
   = static_cast<const MyPrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
          
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }

  //Writing run.txt file
  ofstream fs("run.txt");
  for(int i = 0 ; i < b1Run->GetScatteringAngleVector().size() ; i++){
	  fs << b1Run->GetScatteringAngleVector()[i] << std::endl;
  }
  fs.close();


#ifdef STORE
//  fTree->Write();
//  fRootFile->Close();
#endif

  myfile->close();

    delete myfile;

  std::cout <<"=========================================" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
