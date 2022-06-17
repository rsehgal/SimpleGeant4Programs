#include "MyPrimaryGeneratorAction.h"

//#include "EcoMug.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "MuonReader.h"
#include "Output.h"
#include "Randomize.hh"
#include "SingleTon_T.h"
#include "base/Vector3D.h"
#include <TRandom.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using Tracking::Vector3D;

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0), fEnvelopeBox(0) {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName = "mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
  // fParticleGun->SetParticleEnergy(6.*MeV);
  fRand = new TRandom;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete fParticleGun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

  double gunZ = 155 * cm;
  Muon *muon = new Muon(*lite_interface::MuonReader::instance()->GetMuon());
  // muon->Print();

  /*EcoMug *gen = SingleTon_T<EcoMug>::instance()->GetTargetObject();
  gen->SetUseSky();                          // plane surface gen->ration
  gen->SetSkySize({{100. * cm, 100. * cm}}); // x and y size of the plane
  // (x,y,z) position of the center of the plane
  gen->SetSkyCenterPosition({{0., 0, 60. * cm}});*/

  G4ThreeVector ref(0., 0., -1.);
  Vector3D<double> pt1(Tracking::Global::GenRandomDet(-50. * cm, 50. * cm),
                       Tracking::Global::GenRandomDet(-50. * cm, 50. * cm), gunZ);
  Vector3D<double> pt2(Tracking::Global::GenRandomDet(-50. * cm, 50. * cm),
                       Tracking::Global::GenRandomDet(-50. * cm, 50. * cm), -1.*gunZ);
 
  fParticleGun->SetParticlePosition(G4ThreeVector(pt1.x(), pt1.y(), pt1.z()));

  Vector3D<double> dirVec=(pt2-pt1).Unit();
  //G4ThreeVector dir(muon->angleX, muon->angleY, muon->angleZ);
  G4ThreeVector dir(dirVec.x(), dirVec.y(), dirVec.z());

  dir = dir.unit();
  //double muon_phi = acos(dir.x() / sin(dir.angle(ref))); 
  //double muon_phi = asin(dir.y() / sin(dir.angle(ref))); 
  double muon_phi = atan2(dir.y() , dir.x()); 
  fParticleGun->SetParticleEnergy(muon->energy * MeV);

  //-------------------------- Ecomug ------------------------
/*  std::array<double, 3> muon_position;
  gen->Generate();
  muon_position = gen->GetGenerationPosition();
  double muon_p = gen->GetGenerationMomentum();
  double muon_theta = gen->GetGenerationTheta();
  double muon_phi = gen->GetGenerationPhi();

  fParticleGun->SetParticlePosition(G4ThreeVector(muon_position[0], muon_position[1], muon_position[2]));
  G4ThreeVector dir(sin(muon_theta) * cos(muon_phi), sin(muon_theta) * sin(muon_phi), cos(muon_theta));
  fParticleGun->SetParticleMomentum(G4ParticleMomentum(muon_p*sin(muon_theta) * cos(muon_phi)*GeV,
							muon_p*sin(muon_theta) * sin(muon_phi)*GeV,
							muon_p*cos(muon_theta) *GeV));
 */ //--------------------------------------------------------------

  double angle = dir.angle(ref);
  // Output::instance()->FillCryHist(M_PI-angle);
  Output::instance()->FillCryHist(angle);
  Output::instance()->FillEnergyHist(fParticleGun->GetParticleEnergy()*MeV);
  Output::instance()->FillPhiHist(muon_phi);

  fParticleGun->SetParticleMomentumDirection(dir);

  // fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,10.));
  // G4ThreeVector startPt = G4ThreeVector(fRand->Uniform(-50*cm,50*cm),fRand->Uniform(-50*cm,50*cm),100*cm);

  // fParticleGun->SetParticlePosition(startPt);
  fParticleGun->GeneratePrimaryVertex(anEvent);
  //std::cout << "End of primary generator........." << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
