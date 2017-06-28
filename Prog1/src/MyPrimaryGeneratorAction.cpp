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
#include "Helpers.h"
int MyPrimaryGeneratorAction::c = 0;

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

  // Set the kinetic energy of the protons to 50 keV
  // and tell the gun to emit them along the x-axis
  fParticleGun->SetParticleEnergy(50. * keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -120 * cm ));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}
MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete fParticleGun; }

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {

 Helpers h;
 G4ThreeVector rand = h.GenRandomPoint();
  G4ThreeVector fix(3.8051e-06*mm,2.86789*mm,-4.09575*mm); 
  G4ThreeVector initial = (fix-rand);
  G4ThreeVector newVec(0.00000000001,0.00000000001,0.00000000001); 

  newVec = h.ConvertToG4(h.GetOtherVector(initial,true));

   if(1){
   std::cout << std::setprecision(15);
   std::cout<<"===========================================================" << std::endl;
   std::cout<<"Initial : " << initial <<" :: NewVec : " << newVec << " : Th : "<< newVec.theta() <<" : PHI : "<< newVec.phi() << std::endl;
   std::cout<<"Angle between intial and new : " << h.ConvertToROOT(initial).Angle(h.ConvertToROOT(newVec))*rtd << std::endl;
   std::cout<<"===========================================================" << std::endl;
   }
  fParticleGun->SetParticlePosition(rand);
  fParticleGun->SetParticleMomentumDirection(initial);
  fParticleGun->GeneratePrimaryVertex(event);

  fParticleGun->SetParticlePosition(rand);
  fParticleGun->SetParticleMomentumDirection(newVec);
  fParticleGun->GeneratePrimaryVertex(event);
}


