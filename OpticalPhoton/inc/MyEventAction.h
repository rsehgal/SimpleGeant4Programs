
#ifndef MyEventAction_h
#define MyEventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MyEventAction : public G4UserEventAction
{
 public:
  MyEventAction();
  ~MyEventAction();

  void BeginOfEventAction(const G4Event*) override;
  void EndOfEventAction(const G4Event*) override;

/*  void AddRayleigh() { ++fRayleigh; }
  void AddAbsorption() { ++fAbsorption; }
  void AddMie() { ++fMie; }
  void AddBoundary() { ++fBoundary; }*/

/* private:
  G4int fRayleigh;
  G4int fAbsorption;
  G4int fMie;
  G4int fBoundary;*/
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
