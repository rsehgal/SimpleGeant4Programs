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

MyDetectorConstruction::MyDetectorConstruction(){

}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct(){
  
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  
  // Envelope params
  //
  G4double env_sizeXY = 20*m, env_sizeZ = 30*m;
  //G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  
  //     
  // World
  //
  G4double world_sizeXYZ = 200*cm;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

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

 

  //Scan Horn
  G4Box *scanHorn = new G4Box("ScanHorn",50.*cm,10.*cm,50.*cm);
  G4Material *scanHornMat = nist->FindOrBuildMaterial("G4_Galactic");
  G4LogicalVolume *logicalScanHorn = new G4LogicalVolume(scanHorn,scanHornMat,"ScanHorn-Logical");
  G4VPhysicalVolume *phyScanHorn = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,20.*cm),
                            logicalScanHorn,
                            "PhysicalScanHorn",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

  //Titanium Foil
  G4Box *tiFoil = new G4Box("TiFoil",50.*cm,10.*cm,.025*mm);
  G4Material *foilMat = nist->FindOrBuildMaterial("G4_Ti");
  G4LogicalVolume *logicalTiFoil = new G4LogicalVolume(tiFoil,foilMat,"'TiFoil-Logical");
  G4VPhysicalVolume *phyTiFoil = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,-30.0025*cm),
                            logicalTiFoil,
                            "PhysicalTiFoil",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);



  //Lets try to build material from NIST database
  G4Box *taTarget = new G4Box("TantalumTarget",50.*cm,10.*cm,1.5*cm);
  G4Material *ta = nist->FindOrBuildMaterial("G4_Ta");
  G4LogicalVolume *logicalTaTarget = new G4LogicalVolume(taTarget,ta,"TaTarget-Logical");
  G4VPhysicalVolume *phyTaTarget = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(0.,0.,-50.*cm),
                            logicalTaTarget,
                            "PhysicalTaTarget",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);



	return physWorld;

}
