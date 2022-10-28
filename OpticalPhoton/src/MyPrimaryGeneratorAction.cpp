#include "MyPrimaryGeneratorAction.h"

#include "G4Box.hh"
#include "G4Electron.hh"
#include "G4IonTable.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
  G4int n_particle = 1;
  //fParticleGun = new G4ParticleGun(n_particle);
  //fParticleGun = new G4GeneralParticleSource();//new G4ParticleGun(n_particle);
  fParticleGun = new G4ParticleGun(n_particle);

  // fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

  // Set the kinetic energy of the protons to 50 keV
  // and tell the gun to emit them along the x-axis
  // fParticleGun->SetParticleEnergy(50. * keV);
  // fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -120 * cm ));
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}
MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete fParticleGun; }

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
  // fParticleGun->SetParticlePosition(G4ThreeVector(-50 * cm, 0., -120 * cm));
  // fParticleGun->GeneratePrimaryVertex(event);
  // fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -120 * cm));
  // std::cout << fParticleGun->GetParticleEnergy() << std::endl;

  //------- Trying to use Cs137 source -----------
  /*G4int Z = 55, A = 137;
  G4double ionCharge = 0.*eplus;
  G4double excitEnergy = 0.*keV;
  G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
  fParticleGun->SetParticleDefinition(ion);
  fParticleGun->SetParticleCharge(ionCharge);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,5.1*cm,0.));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));*/

  //std::cout << "--------------------------------------" << std::endl;
  //std::cout << "Energy : " << fParticleGun->GetParticleEnergy() << std::endl;
  fParticleGun->GeneratePrimaryVertex(event);
  // fParticleGun->SetParticlePosition(G4ThreeVector(50 * cm, 0., -120 * cm));
  // fParticleGun->GeneratePrimaryVertex(event);
}
