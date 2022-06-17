/*
 * MySD.h
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#ifndef INC_MYSD_H_
#define INC_MYSD_H_

#include "G4VSensitiveDetector.hh"
#include "MyHit.h"
#include "vector"
#include <G4ThreeVector.hh>
class G4Step;
class G4HCofThisEvent;
class TH1F;
class TRandom;
class MySD : public G4VSensitiveDetector {

public:
//	MySD();
	MySD(const G4String& name,
	                const G4String& hitsCollectionName);
	virtual ~MySD();

	// methods from base class
	virtual void   Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
	static int numOfParticlesReached;

        double GetRandom(double val);
private:
	    MyHitsCollection* fHitsCollection;
	    static int stepNum;
	    static unsigned short numOfStrips;
	    static unsigned short stripSize;
 	    std::vector<G4ThreeVector> vecOfHitPts;

  	    TH1F *sampleHist;
	    TRandom *rndm;

};

#endif /* INC_MYSD_H_ */
