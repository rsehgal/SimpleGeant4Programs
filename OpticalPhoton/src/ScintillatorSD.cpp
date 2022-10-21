/*
**	Filename : ScintillatorSD.cpp
**	2022-09-29
**	username : rsehgal
*/
#include "G4HCofThisEvent.hh"
#include "ScintillatorSD.h"
#include "colors.h"
#include <iostream>
#include <G4Track.hh>

#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"

void ScintillatorSD::Initialize(G4HCofThisEvent *hce) {
  //  std::cout << "Inside Initialize of ScintillatorSD.........." << std::endl;
  fEnergyDepInAEvent = 0;
  //std::cout << BLUE << "================= EVENT BEGIN  ==============" << RESET << std::endl;
}

G4bool ScintillatorSD::ProcessHits(G4Step *aStep, G4TouchableHistory *history) {
  fEnergyDepInAEvent += aStep->GetTotalEnergyDeposit();

  G4Track *track = aStep->GetTrack();
  //std::cout << "Vertex Energy : " << track->GetVertexKineticEnergy() << std::endl;
  G4String particleName = track->GetDefinition()->GetParticleName();
  const G4VProcess *creatorProcess = aStep->GetPostStepPoint()->GetProcessDefinedStep();
  if (creatorProcess && 0)
    std::cout << "*********** " << particleName << " : " << creatorProcess->GetProcessName() << std::endl
              << " : GetTotalEnergyDeposit (Step) : " << aStep->GetTotalEnergyDeposit() << std::endl
              << RED << " : GetDeltaEnergy (Step) : " << aStep->GetDeltaEnergy() << std::endl
              << RESET << " : GetTotalEnergy (Track) : " << track->GetTotalEnergy() << std::endl
              << " : GetKineticEnergy (Track) : " << track->GetKineticEnergy() << std::endl
              << " : GetVertexKineticEnergy (Track) : " << track->GetVertexKineticEnergy() << std::endl;
}

void ScintillatorSD::EndOfEvent(G4HCofThisEvent *) {
  //  std::cout << RED << "Energy Deposited : " << fEnergyDepInAEvent << RESET <<  std::endl;
  fHistEDep->Fill(fEnergyDepInAEvent * 1000.);
  //std::cout << BLUE << "================= EVENT END ==============" << RESET << std::endl;
}
