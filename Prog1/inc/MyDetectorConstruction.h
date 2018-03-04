#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VUserDetectorConstruction;
class G4VPhysicalVolume;
class G4LogicalVolume;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetTube(std::string name,double rmin,double rmax,double dz);//, double sphi, double dphi);
};
#endif