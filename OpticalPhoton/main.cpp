#include "B1ActionInitialization.hh"
#include "MyDetectorConstruction.h"

//#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "Randomize.hh"

#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"
//#include <TFile.h>
//#include "physicslist.hh"
#include "MySD.h"
/*Visualizer related includes*/
//#include "EveVisualizer.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#include "OutputFile.h"
// TFile *fp;

//#include "Output.h"
//#include "MuonReader.h"
//#include "EcoMug.h"
//#include "SingleTon_T.h"

int main(int argc, char **argv) {
  // SingleTon_T<EcoMug> *obj = SingleTon_T<EcoMug>::instance();
  // lite_interface::MuonReader::instance("Muons-50L.root");
  // Output::instance("acceptance.root");

  // Detect interactive mode (if no arguments) and define UI session
  //
  // fp = new TFile("anal.root","RECREATE");
  // fp->cd();
  // lite_interface::OutputFile::instance("anal.root");
  G4UIExecutive *ui = 0;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);

  // Construct the default run manager
  //
  //  auto* runManager =
  G4RunManager *runManager = new G4RunManager;
  // G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new MyDetectorConstruction());

  // Physics list
  // G4VModularPhysicsList* physicsList = new FTFP_BERT;//QBBC;

  G4VModularPhysicsList *physicsList = new FTFP_BERT;
  // physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
#ifdef ENABLE_OPTICAL_PHYSICS
  G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
#endif

  // physicsList->SetVerboseLevel(1);
  // runManager->SetUserInitialization(physicsList);

  // runManager->SetUserInitialization(new MYphysicslist());
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new B1ActionInitialization());

  // Initialize visualization
  //
  G4VisManager *visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  // Output::instance()->Close();

  std::cout << "**************************************" << std::endl;
  std::cout << "Total number of QuadCoincidenct events : " << MySD::quadCoincidenceCounter << std::endl;
  std::cout << "**************************************" << std::endl;
  delete visManager;
  delete runManager;
  // fp->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
