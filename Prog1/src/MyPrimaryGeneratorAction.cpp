#include "MyPrimaryGeneratorAction.h"

#include "G4Box.hh"
#include "G4Electron.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <random>
#include <G4FastStep.hh>
#include <fstream>
#include "B1RunAction.hh"
using namespace std;

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

  G4double cosTheta = 2*G4UniformRand() - 1., phi = 2*(M_PI/rad)*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi);
  G4double uy = sinTheta*std::sin(phi);
  G4double uz = cosTheta;

  // Set the kinetic energy of the protons to 50 keV
  // and tell the gun to emit them along the x-axis
  //std::cout<<"== Called Constructor ==" << std::endl;
  fParticleGun->SetParticleEnergy(50. * keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -120 * cm ));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
//  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1., 0., 0.));
}
MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete fParticleGun; }
    ofstream myfile;
void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
   //fParticleGun->SetParticlePosition(G4ThreeVector(-50 * cm, 0., -120 * cm));
   //fParticleGun->GeneratePrimaryVertex(event);
  //std::cout<<"== Called GeneratePrimaries ==" << std::endl;
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0 * cm));

  //fParticleGun->SetParticleEnergy(35.*G4UniformRand()*MeV);

  G4double x = G4UniformRand();
  G4double y = G4UniformRand();
  G4double z = G4UniformRand();
  G4double energy = G4RandGauss::shoot(17.* MeV,2. * MeV);

  *B1RunAction::myfile << energy << std::endl;
//  fstream fs;
//  fs.open("energy.txt",fstream::app);
//  fs << energy << endl;
//  fs.close();

    

//  G4bool Write();
  fParticleGun->SetParticleEnergy(energy);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-x,-y,-z));
  fParticleGun->GeneratePrimaryVertex(event);
   //fParticleGun->SetParticlePosition(G4ThreeVector(50 * cm, 0., -120 * cm));
   //fParticleGun->GeneratePrimaryVertex(event);
}
