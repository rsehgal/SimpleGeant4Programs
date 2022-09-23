/*
**	Filename : MyDetectorMessenger.h
**	2022-09-19
**	username : rsehgal
*/
#ifndef MyDetectorMessenger_h
#define MyDetectorMessenger_h

class MyDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

#include "G4UImessenger.hh"
#include "globals.hh"

class MyDetectorMessenger:public G4UImessenger {
public:
  MyDetectorMessenger(MyDetectorConstruction *det);
  virtual ~MyDetectorMessenger();
  virtual void SetNewValue(G4UIcommand *cmd, G4String command);

private:
  MyDetectorConstruction *fDetectorConstruction;
  G4UIdirectory *fB2Directory;
  G4UIdirectory *fDetDirectory;
  G4UIcmdWithAString *fTargMatCmd;
};

#endif
