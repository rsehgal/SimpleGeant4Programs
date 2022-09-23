
#include "MySteppingAction.h"

#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MySteppingAction::MySteppingAction(MyEventAction* event)
  : G4UserSteppingAction()
//  , fEventAction(event)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MySteppingAction::~MySteppingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MySteppingAction::UserSteppingAction(const G4Step* step)
{

  //std::cout << "Entereed .. User Stepping Action.........." << std::endl;
  static G4ParticleDefinition* opticalphoton =
    G4OpticalPhoton::OpticalPhotonDefinition();

  const G4ParticleDefinition* particleDef =
    step->GetTrack()->GetDynamicParticle()->GetParticleDefinition();

  //if(particleDef != opticalphoton)
  //if(particleDef->GetParticleName() != "opticalphoton")
  {
    G4StepPoint* endPoint = step->GetPostStepPoint();
    const G4VProcess* pds = endPoint->GetProcessDefinedStep();
    G4String procname     = pds->GetProcessName();
    std::cout << "Particle Def : " << particleDef->GetParticleName() <<"  : ProcessName : " << procname << std::endl;
    /*if(procname.compare("OpRayleigh") == 0)
      fEventAction->AddRayleigh();
    else if(procname.compare("OpAbsorption") == 0)
      fEventAction->AddAbsorption();
    else if(procname.compare("OpMieHG") == 0)
      fEventAction->AddMie();*/

    // for boundary scattering, process name in 'transportation'.
    // Need to check differently:
    /*if(endPoint->GetStepStatus() == fGeomBoundary)
    {
      G4OpBoundaryProcessStatus theStatus = Undefined;
      G4ProcessManager* opManager         = opticalphoton->GetProcessManager();
      G4int n_proc = opManager->GetPostStepProcessVector(typeDoIt)->entries();
      G4ProcessVector* postStepDoItVector =
        opManager->GetPostStepProcessVector(typeDoIt);
      for(G4int i = 0; i < n_proc; ++i)
      {
        G4VProcess* currentProcess = (*postStepDoItVector)[i];

        G4OpBoundaryProcess* opProc =
          dynamic_cast<G4OpBoundaryProcess*>(currentProcess);
        if(opProc)
          theStatus = opProc->GetStatus();
      }
      if(theStatus != Undefined && theStatus != NotAtBoundary &&
         theStatus != StepTooSmall)
      {
        fEventAction->AddBoundary();
      }
    }*/
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
