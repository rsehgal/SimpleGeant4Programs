/*
 * Helpers.h
 *
 *  Created on: Jun 28, 2017
 *      Author: rsehgal
 */

#ifndef PROG1_INC_HELPERS_H_
#define PROG1_INC_HELPERS_H_

#include <G4ThreeVector.hh>
#include <TVector3.h>

const double rtd = 180./M_PI;
const double dtr = M_PI/180.;

class Helpers{

public:
	Helpers(){}
	~Helpers(){}

	double unifRand();
	double unifRand(double a, double b);
	G4ThreeVector GenRandomPoint();
	void seed();
	G4ThreeVector GetOtherVector(G4ThreeVector R1); // using G4
	TVector3 GetOtherVector(TVector3 R1); //Using ROOT
	G4ThreeVector ConvertToG4(TVector3 vec);
	TVector3 ConvertToROOT(G4ThreeVector vec);
	TVector3 GetOtherVector(G4ThreeVector R1,bool g4);


};

#endif /* PROG1_INC_HELPERS_H_ */
