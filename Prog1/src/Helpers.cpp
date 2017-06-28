/*
 * Helpers.h
 *
 *  Created on: Jun 28, 2017
 *      Author: rsehgal
 */

#include <random>
#include "Helpers.h"
#include <iomanip>
#include <G4ThreeVector.hh>
#include <TVector3.h>

double Helpers::unifRand()
{
    return rand() / double(RAND_MAX);
}
//
// Generate a random number in a real interval.
// param a one end point of the interval
// param b the other end of the interval
// return a inform rand numberin [a,b].
double Helpers::unifRand(double a, double b)
{
    return (b-a)*unifRand() + a;
}

G4ThreeVector Helpers::GenRandomPoint(){

	//G4double theta = G4UniformRand(0,2*M_PI);
  double theta = unifRand(0,2*M_PI);
  G4double x = 0.005*std::cos(theta);
  G4double y = 0.005*std::sin(theta);
  G4double z = 0.;//G4UniformRand();

  //std::cout<< std::setprecision(20) << "Random point on Disc : "<< G4ThreeVector(x,y,z) << std::endl;
  return G4ThreeVector(x,y,z);

}

// Reset the random number generator with the system clock.
void Helpers::seed()
{
    srand(time(0));
}

TVector3 Helpers::GetOtherVector(TVector3 R1){

	double foldang=175;
	double th = 0.;//-180.;
	double phi = 0.;//-180.;
	double RelAng=0., RelAng2=0.;
	int nbin_Theta=0,nbin_Phi=0;
	double delTheta=0.05;
	double delPhi=0.05;
	nbin_Theta=361/delTheta;
	nbin_Phi=361/delPhi;
	TVector3 R2(0.000000001,0.0000000001,0.00000000001);
	for (int i=0; i<nbin_Theta;++i)
	{

		R2.SetMag(R1.Mag());
		R2.SetTheta(th*dtr);
	    th=th+delTheta;
		phi=0.0;
		for (int j=0; j<nbin_Phi;++j)
		{
		R2.SetPhi(phi*dtr);
	    RelAng=R1.Angle(R2)*rtd;
		phi=phi+delPhi;
		if((RelAng > 174.9999) && (RelAng < 175.0001)){
		//	std::cout <<" Raman :  "<<RelAng<<"    "<< R1.Mag() <<" " << R2.Mag() <<" "<< R2.Theta()*rtd<<"  "<< R2.Phi()*rtd << std::endl;
			break;
			}
		}

		if((RelAng > 174.9999) && (RelAng < 175.0001))
			break;

	}

	return R2;
}

TVector3 Helpers::GetOtherVector(G4ThreeVector R1,bool g4){ //Using ROOT
	return GetOtherVector(ConvertToROOT(R1));
}

TVector3 Helpers::ConvertToROOT(G4ThreeVector vec){
	return TVector3(vec.x(),vec.y(),vec.z());
}

G4ThreeVector Helpers::ConvertToG4(TVector3 vec){
	return G4ThreeVector(vec.x(),vec.y(),vec.z());
}

G4ThreeVector Helpers::GetOtherVector(G4ThreeVector R1){ //,double th, double phi){
std::cout<<"----- Here 3 ----------" << std::endl;
double foldang=175;
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

