#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VUserDetectorConstruction;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4LogicalVolume;
class G4Element;
class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
  MyDetectorConstruction();
  ~MyDetectorConstruction();
  G4VPhysicalVolume *Construct();
  void SetBlockMaterial(G4String materalName);

private:
  G4Material *fBlockMaterial;
  G4LogicalVolume *fLogicBlock;

  G4Element *fC;
  G4Element *fH;
  G4Material *fGlass;
  G4Material *fPstyrene;
};
#endif
