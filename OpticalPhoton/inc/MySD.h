/*
**	Filename : MySD.h
**	2022-09-27
**	username : rsehgal
*/
#ifndef INC_MYSD_H_
#define INC_MYSD_H_

#include "G4VSensitiveDetector.hh"
#include "MyHit.h"
#include "vector"
#include "Write.h"
class G4Step;
class G4HCofThisEvent;

class MySD : public G4VSensitiveDetector {

public:
  //	MySD();
  MySD(const G4String &name, const G4String &hitsCollectionName);
  virtual ~MySD();

  // methods from base class
  virtual void Initialize(G4HCofThisEvent *hitCollection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hitCollection);
  static int numOfParticlesReached;

private:
  MyHitsCollection *fHitsCollection;
  static int stepNum;
  unsigned int photonCounter[4];
  Tree *fWrite;
  static unsigned int fEventCounter;
};

#endif /* INC_MYSD_H_ */
