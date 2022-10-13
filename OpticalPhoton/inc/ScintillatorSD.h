/*
 *	Filename : ScintillatorSD.h
 **	2022-09-29
 **	username : rsehgal
 */
#ifndef ScintillatorSD_h
#define ScintillatorSD_h

#include "G4VSensitiveDetector.hh"
class G4HCofThisEvent;
class ScintillatorSD : public G4VSensitiveDetector {
public:
double fEnergyDepInAEvent;
public:
  ScintillatorSD(const G4String name, const G4String hitsCollectionName) : G4VSensitiveDetector(name) {}
  ScintillatorSD(const G4String name) : G4VSensitiveDetector(name) {}
  ScintillatorSD() : G4VSensitiveDetector("Hello") {}
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  void 	Initialize (G4HCofThisEvent *);
};

#endif
