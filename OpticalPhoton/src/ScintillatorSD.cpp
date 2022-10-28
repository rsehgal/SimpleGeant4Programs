/*
**	Filename : ScintillatorSD.cpp
**	2022-09-29
**	username : rsehgal
*/
#include "G4HCofThisEvent.hh"
#include "ScintillatorSD.h"
#include "colors.h"
#include <G4Track.hh>
#include <iostream>

#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include <TRandom3.h>
void ScintillatorSD::Initialize(G4HCofThisEvent *hce) {
  //  std::cout << "Inside Initialize of ScintillatorSD.........." << std::endl;
  fEnergyDepInAEvent = 0;
  // std::cout << BLUE << "================= EVENT BEGIN  ==============" << RESET << std::endl;
  fPhotonCounter = 0;
  rng = new TRandom3();
}

G4bool ScintillatorSD::ProcessHits(G4Step *aStep, G4TouchableHistory *history) {
  fEnergyDepInAEvent += aStep->GetTotalEnergyDeposit();

  G4Track *track = aStep->GetTrack();
  //std::cout << "RAMAN : material name : "<< track->GetMaterial()->GetName() << std::endl;
  // std::cout << "Vertex Energy : " << t rack->GetVertexKineticEnergy() << std::endl;
  G4String particleName = track->GetDefinition()->GetParticleName();
#define DEBUG
#ifdef DEBUG
  if (particleName == "opticalphoton") {
    //std::cout << "RAMAN" << std::endl;
    track->SetTrackStatus(fStopAndKill);
    fPhotonCounter++;
  }
#endif
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
#ifdef VERBOSE
  std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
  std::cout << "Number of Photons Generated : " << fPhotonCounter << std::endl;
  std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

#endif
  double quantumEff = 0.25;
  double gain=4.5*1e+4;
  double echarge = 1.6*1e-19;
  double chargeSensitivity = 20*1e-15;
  double attenFactor = 1./380.;
  unsigned int nP_Far = fPhotonCounter*exp(-1.*attenFactor*50);//*quantumEff*gain;
  //double factor = quantumEff*gain*echarge/chargeSensitivity;
  double factor = quantumEff*2.5*1.6/20;
  //unsigned int channelNum = nP_Far*echarge/chargeSensitivity;
  //if(channelNum > 0)
  //std::cout << "Final Number of ELECTRONS : " << nP_Far << " : Channel Num : " << channelNum << std::endl;
  if(nP_Far>0)
  fHistADC->Fill(rng->Gaus(nP_Far*factor,67));
  //fHistADC->Fill(channelNum);
// std::cout << BLUE << "================= EVENT END ==============" << RESET << std::endl;
}
