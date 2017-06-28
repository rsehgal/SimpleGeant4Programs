/*
#ifndef MyPrimaryGeneratorAction
#define MyPrimaryGeneratorAction

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"


class G4VUserPrimaryGeneratorAction;
class G4Event;
class G4ParticleGun;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	MyPrimaryGeneratorAction();
	~MyPrimaryGeneratorAction();
	void GeneratePrimaries(G4Event* event);
	G4ParticleGun* GetParticleGun(){return fParticleGun;}

private:
	G4ParticleGun *fParticleGun;

	
};
#endif
*/

#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
//#include "MyRandom.h"
#include <iostream>
#include <G4ThreeVector.hh>
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <random>
#include <iostream>
#include <iomanip>
#include "Helpers.h"
/*
double foldang=175;
double rtd=180/3.14159;
double dtr=3.14159/180;
*/

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
static int c;
  public:
    MyPrimaryGeneratorAction();    
     ~MyPrimaryGeneratorAction();

    // method from the base class
    void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }




//
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    //G4Box* fEnvelopeBox;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
