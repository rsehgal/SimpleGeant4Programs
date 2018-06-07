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
MyDetectorConstruction::MyDetectorConstruction(){

}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct(){
  
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  
  // Envelope params
  //
 // G4double env_sizeXY = 20*m, env_sizeZ = 30*m;
  //G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  
  //     
  // World
  //
  G4double world_sizeXYZ = 200*cm;
//  G4double world_sizeXY = 1.2*env_sizeXY;
//  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "LogicalWorld");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "PhysicalWorld",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

 

  //Lets try to build material from NIST database
/*  G4Box *leadBlock = new G4Box("LeadBlock",5.*cm,5.*cm,15.*cm);
  G4Material *Pb=nist->FindOrBuildMaterial("G4_Pb");
 G4LogicalVolume *logicalLeadBlock = new G4LogicalVolume(leadBlock,Pb,"LogicalLeadBlock");
    G4VPhysicalVolume *phyLeadBlock = new G4PVPlacement(0,
                            G4ThreeVector(),
                            logicalLeadBlock,
                            "PhysicalLeadBlock",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

 G4VPhysicalVolume *phyLeadBlock2 = new G4PVPlacement(0,
                            G4ThreeVector(25*cm,0.,0.),
                            logicalLeadBlock,
                            "PhysicalLeadBlock2",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

*/

/*
 G4Box *AlSheet = new G4Box("AlBlock",5*cm,5*cm,15*cm);
G4Material *Al=nist->FindOrBuildMaterial("G4_Al");
G4LogicalVolume *logicalAlSheet = new G4LogicalVolume(AlSheet,Al,"LogicalAlSheet");
 G4VPhysicalVolume *phyAlSheet = new G4PVPlacement(0,
                                 G4ThreeVector(0.,0.,10*cm),
                                 logicalAlSheet,
                                "PhysicalAlSheet",
                                 logicWorld,
                                 false,
                                 0,
                                 checkOverlaps);
*/

G4Tubs *AlTube = new G4Tubs("AlTubs",3*cm,5*cm,10*cm,0.,2*M_PI);
G4Material *Al=nist->FindOrBuildMaterial("G4_Al");
G4LogicalVolume *logicalAlTube = new G4LogicalVolume(AlTube,Al,"LogicalAlTube");
G4VPhysicalVolume *phyAlTube = new G4PVPlacement(0,
                                 G4ThreeVector(-10*cm,0.,20*cm),
                                 logicalAlTube,
                                "PhysicalAlTube",
                                 logicWorld,
                                 false,
                                 0,
                                 checkOverlaps);
                                 
G4VPhysicalVolume *phyAlTube2 = new G4PVPlacement(0,
                                 G4ThreeVector(10*cm,0.,20*cm),
                                 logicalAlTube,
                                "PhysicalAlTube",
                                 logicWorld,
                                 false,
                                 0,
                                 checkOverlaps);
                                 
                                 
G4Box *screen = new G4Box("screen",70*cm,70*cm,0.05*mm);
G4Material *Gal=nist->FindOrBuildMaterial("G4_Galactic");
G4LogicalVolume *logicalScreen = new G4LogicalVolume(screen,Gal,"LogicalGalScreen");
 G4VPhysicalVolume *phyScreen = new G4PVPlacement(0,
                                 G4ThreeVector(0.,0.,50*cm),
                                 logicalScreen,
                                "PhysicalScreen",
                                 logicWorld,
                                 false,
                                 0,
                                 checkOverlaps);

	return physWorld;

}
