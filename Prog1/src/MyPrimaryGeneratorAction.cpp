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
#include <iomanip>
#include <fstream>

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {

#ifdef USE_CRY
  ForCry("test");
#else
  G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

    // Set the kinetic energy of the protons to 50 keV
    // and tell the gun to emit them along the x-axis
    fParticleGun->SetParticleEnergy(50. * keV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -120 * cm ));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

#endif

}

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction(const char *inputfile) {

#ifdef USE_CRY
  ForCry(inputfile);
#endif
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() { delete fParticleGun; }

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {

#ifdef USE_CRY
  GeneratePrimariesForCry(event);
#else
  //fParticleGun->SetParticlePosition(G4ThreeVector(-50 * cm, 0., -120 * cm));
  //fParticleGun->GeneratePrimaryVertex(event);
 fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -120 * cm));
 fParticleGun->GeneratePrimaryVertex(event);
  //fParticleGun->SetParticlePosition(G4ThreeVector(50 * cm, 0., -120 * cm));
  //fParticleGun->GeneratePrimaryVertex(event);
#endif
}

#ifdef USE_CRY
void MyPrimaryGeneratorAction::GeneratePrimariesForCry(G4Event *anEvent){

	  if (InputState != 0) {
	    G4String* str = new G4String("CRY library was not successfully initialized");
	    //G4Exception(*str);
	    G4Exception("PrimaryGeneratorAction", "1",
	                RunMustBeAborted, *str);
	  }
	  G4String particleName;
	  vect->clear();
	  gen->genEvent(vect);

	  //....debug output
	  G4cout << "\nEvent=" << anEvent->GetEventID() << " "
	         << "CRY generated nparticles=" << vect->size()
	         << G4endl;

	  for ( unsigned j=0; j<vect->size(); j++) {
	    particleName=CRYUtils::partName((*vect)[j]->id());

	    //....debug output
	    std::cout << "  "          << particleName << " "
	         << "charge="      << (*vect)[j]->charge() << " "
	         << std::setprecision(4)
	         << "energy (MeV)=" << (*vect)[j]->ke()*MeV << " "
	         << "pos (m)"
	         << G4ThreeVector((*vect)[j]->x(), (*vect)[j]->y(), (*vect)[j]->z())
	         << " " << "direction cosines "
	         << G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w())
	         << " " << std::endl;

	    particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
	    particleGun->SetParticleEnergy((*vect)[j]->ke()*MeV);
	    particleGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->y()*m, (*vect)[j]->z()*m));
	    particleGun->SetParticleMomentumDirection(G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w()));
	    particleGun->SetParticleTime((*vect)[j]->t());
	    particleGun->GeneratePrimaryVertex(anEvent);
	    delete (*vect)[j];
	  }

}

void MyPrimaryGeneratorAction::ForCry(const char *inputfile){
	  // define a particle gun
	  particleGun = new G4ParticleGun();

	  // Read the cry input file
	  std::ifstream inputFile;
	  inputFile.open(inputfile,std::ios::in);
	  char buffer[1000];

	  if (inputFile.fail()) {
	    if( *inputfile !=0)  //....only complain if a filename was given
	      G4cout << "PrimaryGeneratorAction: Failed to open CRY input file= " << inputfile << G4endl;
	    InputState=-1;
	  }else{
	    std::string setupString("");
	    while ( !inputFile.getline(buffer,1000).eof()) {
	      setupString.append(buffer);
	      setupString.append(" ");
	    }

	    CRYSetup *setup=new CRYSetup(setupString,"../data");

	    gen = new CRYGenerator(setup);

	    // set random number generator
	    RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
	    setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
	    InputState=0;
	  }
	  // create a vector to store the CRY particle properties
	  vect=new std::vector<CRYParticle*>;

	  // Create the table containing all particle names
	  particleTable = G4ParticleTable::GetParticleTable();

	  gunMessenger = new PrimaryGeneratorMessenger(this);
}


//----------------------------------------------------------------------------//
void MyPrimaryGeneratorAction::InputCRY()
{
  InputState=1;
}

//----------------------------------------------------------------------------//
void MyPrimaryGeneratorAction::UpdateCRY(std::string* MessInput)
{
  CRYSetup *setup=new CRYSetup(*MessInput,"../data");

  gen = new CRYGenerator(setup);

  // set random number generator
  RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
  setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
  InputState=0;

}

//----------------------------------------------------------------------------//
void MyPrimaryGeneratorAction::CRYFromFile(G4String newValue)
{
  // Read the cry input file
  std::ifstream inputFile;
  inputFile.open(newValue,std::ios::in);
  char buffer[1000];

  if (inputFile.fail()) {
    G4cout << "Failed to open input file " << newValue << G4endl;
    G4cout << "Make sure to define the cry library on the command line" << G4endl;
    InputState=-1;
  }else{
    std::string setupString("");
    while ( !inputFile.getline(buffer,1000).eof()) {
      setupString.append(buffer);
      setupString.append(" ");
    }

    CRYSetup *setup=new CRYSetup(setupString,"../data");

    gen = new CRYGenerator(setup);

  // set random number generator
    RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
    setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
    InputState=0;
  }
}


#endif
