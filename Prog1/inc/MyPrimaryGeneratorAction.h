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

G4ThreeVector GenRandomPoint(){

  
  
  //G4double theta = G4UniformRand(0,2*M_PI);
  double theta = unifRand(0,2*M_PI);
  G4double x = 0.0000000005*mm*std::cos(theta);
  G4double y = 0.0000000005*mm*std::sin(theta);
  G4double z = 0.;//G4UniformRand();

  std::cout<< std::setprecision(20) << "Random point on Disc : "<< G4ThreeVector(x,y,z) << std::endl;
  return G4ThreeVector(x,y,z);

}

long unifRand(long n)
{
    
    if (n < 0) n = -n;
    if (n==0) return 0;
    /* There is a slight error in that this code can produce a return value of n+1
    **
    **  return long(unifRand()*n) + 1;
    */
    //Fixed code
    long guard = (long) (unifRand() * n) +1;
    return (guard > n)? n : guard;
}

G4ThreeVector GetOtherVector(G4ThreeVector R1){ //,double th, double phi){
std::cout<<"----- Here 3 ----------" << std::endl;
double foldang=175;
double rtd=180/3.14159;
double dtr=3.14159/180;
double th = 0.;// = R1.theta()*rtd;
double phi = 0.; //= R1.phi()*rtd;

std::cout<<"R1 : "<< R1.mag() <<" :: Theta : " << R1.theta() <<" :: PHI : "<< R1.phi() << std::endl;

double RelAng=0., RelAng2=0.;
int nbin_Theta=0,nbin_Phi=0;
double delTheta=0.05;
double delPhi=0.05;
nbin_Theta=181/delTheta;
nbin_Phi=361/delPhi;
G4ThreeVector R2(0.000000001,0.0000000001,0.00000000001);
for (int i=0; i<nbin_Theta;++i)
{
	
	R2.setMag(R1.mag());
	R2.setTheta(th*dtr);
        th=th+delTheta;
	phi=0.0;
	for (int j=0; j<nbin_Phi;++j)
	{
	R2.setPhi(phi*dtr);
        RelAng=R1.angle(R2)*rtd;
	phi=phi+delPhi;
	//std::cout<<"Realatfdsfsd Angle : "<< RelAng << " : " << th <<" : " << phi << std::endl;
	//outFile1<<"   "<<RelAng<<" "<<i<<" "<<j<<endl;
	//if(RelAng==175.0)
//std::cout<<"----- Here 4 ----------" << std::endl;
	if((174.9999<RelAng)&&(RelAng<175.0001))
		{
		std::cout <<" Raman :  "<<RelAng<<"    "<< R1.mag() <<" " << R2.mag() <<" "<< R2.theta()*rtd<<"  "<< R2.phi()*rtd << std::endl;
		break;
		}
	}

if((174.9999<RelAng)&&(RelAng<175.0001))
	break;
 
}

std::cout<< "R2 before return :  Theta : "<< R2.theta()*rtd <<" :: PHI : "<< R2.phi()*rtd << std::endl;
return R2;

}
//
// Reset the random number generator with the system clock.
void seed()
{
    srand(time(0));
}

double unifRand()
{
    return rand() / double(RAND_MAX);
}
//
// Generate a random number in a real interval.
// param a one end point of the interval
// param b the other end of the interval
// return a inform rand numberin [a,b].
double unifRand(double a, double b)
{
    return (b-a)*unifRand() + a;
}
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    //G4Box* fEnvelopeBox;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
