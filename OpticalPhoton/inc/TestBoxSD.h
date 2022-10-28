/*
**	Filename : TestBoxSD.h
**	2022-10-28
**	username : rsehgal
*/
#ifndef TestBoxSD_h
#define TestBoxSD_h

#include "ParentSD.h"

class TestBoxSD : public ParentSD {
public:
unsigned int fPhotonCounter;
public:
  TestBoxSD() : ParentSD() {}
  TestBoxSD(const G4String name) : ParentSD(name) {}
  ~TestBoxSD() {}
  void Initialize(G4HCofThisEvent *hce) {
    fPhotonCounter=0;
    //std::cout << BLUE << "TestBoxSD Initialize called........." << RESET << std::endl;
  }

  G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *history) {
    //std::cout << RED << "TestBoxSD ProcessHits called........." << RESET << std::endl;
    G4Track *track = aStep->GetTrack();
    G4String particleName = track->GetDefinition()->GetParticleName();
    G4String processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    //std::cout << "ParticleName from TestBoxSD ProcessHits : " << particleName << " : ProcessName : " << processName<<std::endl;
    if(particleName=="opticalphoton")
	fPhotonCounter++;
  	//track->SetTrackStatus(fStopAndKill);
  }

  virtual void EndOfEvent(G4HCofThisEvent *hce){
        //std::cout << MAGENTA << "TestBoxSD EndOfEvent called........." << RESET << std::endl;
	std::cout << "Total Number of Photon exiting the Scintilltor : " << fPhotonCounter << std::endl;
  }
};

#endif
