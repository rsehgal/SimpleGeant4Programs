#include "MyDetectorConstruction.h"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4Tubs.hh"
#define PI 3.14159265359
MyDetectorConstruction::MyDetectorConstruction(){

}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct(){
  
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  G4double world_sizeXYZ = 30*cm;
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  //Creating Foil
  G4Tubs *foil = new G4Tubs("Foil",0.*mm,6.*mm,0.075*mm,0.,2*PI);
  G4Material *Be=nist->FindOrBuildMaterial("G4_Be");
  G4LogicalVolume *logicalFoil = new G4LogicalVolume(foil,Be,"LogicalBeFoil");
  G4VPhysicalVolume *phyFoil = new G4PVPlacement(0,
                            G4ThreeVector(),
                            logicalFoil,
                            "PhysicalFoil",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);


  //Now creating Target
  G4Tubs *target = new G4Tubs("Target",0.*mm,7.*mm,7.*mm,0.,2*PI);
  G4Material *W=nist->FindOrBuildMaterial("G4_W");
  G4LogicalVolume *logicalTarget = new G4LogicalVolume(target,W,"LogicalWTarget");
  G4VPhysicalVolume *phyTarget = new G4PVPlacement(0,
                            G4ThreeVector(0.,0.,100*mm),
                            logicalTarget,
                            "PhysicalTarget",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
 



	return physWorld;

}
