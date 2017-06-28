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
//double rtd=180/3.14159;
//double dtr=3.14159/180;
Helpers h;

   //fParticleGun->SetParticlePosition(G4ThreeVector(-50 * cm, 0., -120 * cm));
   //fParticleGun->GeneratePrimaryVertex(event);
  G4ThreeVector rand = h.GenRandomPoint();
  G4ThreeVector fix(3.8051e-06*mm,2.86789*mm,-4.09575*mm); 
  G4ThreeVector initial = (fix-rand);
 // std::cout<<"Rand Theta : "<< rand.theta() <<" : Rand PHI : "<< rand.phi() << std::endl;
//  std::cout<<"Initail Theta : "<< initial.theta() <<" : PHI : "<< initial.phi() << std::endl;
G4ThreeVector newVec(0.00000000001,0.00000000001,0.00000000001); 
G4ThreeVector backup(0.00000000001,0.00000000001,0.00000000001); 

#if(1)
//std::cout<<"----- Here ----------" << std::endl;

//if(c==0)
if(1)
{
//std::cout<<"----- Here 2 ----------" << std::endl;
  newVec = h.ConvertToG4(h.GetOtherVector(initial,true));//,initial.theta(),initial.phi());
//std::cout<< "First Theta : "<< newVec.theta()*rtd <<" :: PHI : "<< newVec.phi()*rtd << std::endl;
  backup = newVec;
  c++;
}else{
  newVec.setZ(backup.z());
  double r = newVec.perp();
  double phii = h.unifRand(0,2*M_PI);
  G4double x = r*std::cos(phii);
  G4double y = r*std::sin(phii);
  newVec.setX(x);
  newVec.setY(y);
  //std::cout<< "Other Theta : "<< newVec.theta()*rtd <<" :: PHI : "<< newVec.phi()*rtd << std::endl;
}

#endif
   if(1){
   std::cout << std::setprecision(15);
   std::cout<<"===========================================================" << std::endl;
   std::cout<<"Initial : " << initial <<" :: NewVec : " << newVec << " : Th : "<< newVec.theta() <<" : PHI : "<< newVec.phi() << std::endl;
   std::cout<<"Angle between intial and new : " << h.ConvertToROOT(initial).Angle(h.ConvertToROOT(newVec))*rtd << std::endl;
   std::cout<<"===========================================================" << std::endl;
   }
 // G4ThreeVector  newVec = GetOtherVector(initial);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0 ));
  fParticleGun->SetParticleMomentumDirection(initial);

  fParticleGun->GeneratePrimaryVertex(event);

fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0 ));
  fParticleGun->SetParticleMomentumDirection(newVec);
fParticleGun->GeneratePrimaryVertex(event);
   //fParticleGun->SetParticlePosition(G4ThreeVector(50 * cm, 0., -120 * cm));
   //fParticleGun->GeneratePrimaryVertex(event);
}


