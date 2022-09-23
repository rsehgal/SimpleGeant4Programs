#ifndef MySteppingAction_h
#define MySteppingAction_h 1

#include "MyEventAction.h"

#include "globals.hh"
#include "G4UserSteppingAction.hh"

class MySteppingAction : public G4UserSteppingAction
{
 public:
  MySteppingAction(MyEventAction*);
  ~MySteppingAction();

  void UserSteppingAction(const G4Step*) override;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
