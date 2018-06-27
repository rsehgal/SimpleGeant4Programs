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
  G4double world_sizeXYZ = 300*cm;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
 
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
  G4Box *RPCBlock = new G4Box("RPC",50.*cm,50.*cm,1.*cm);
  G4Material *AIR=nist->FindOrBuildMaterial("G4_AIR");
  G4LogicalVolume *logicalRPCBlock = new G4LogicalVolume(RPCBlock,AIR,"LogicalRPCBlock");
  //G4ThreeVector pos(0.,0.,0.);
 G4Box *PbBlock = new G4Box("Pb",15.*cm,15.*cm,15.*cm);
  G4Material *Pb=nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume *logicalPbBlock = new G4LogicalVolume(PbBlock,Pb,"LogicalPbBlock");
  //G4ThreeVector pos(0.,0.,0.);

  G4VPhysicalVolume *phyRPCBlock = new G4PVPlacement(0,
                            G4ThreeVector(0.*cm,0.*cm,-105.*cm),
                            //pos,
                            logicalRPCBlock,
                            "PhysicalRPCBlock",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

  G4VPhysicalVolume *phyRPCBlock1 = new G4PVPlacement(0,
                            G4ThreeVector(0.*cm,0.*cm,-75.*cm),
                            //pos,
                            logicalRPCBlock,
                            "PhysicalRPCBlock1",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);
  G4VPhysicalVolume *phyRPCBlock2 = new G4PVPlacement(0,
                            G4ThreeVector(0.*cm,0.*cm,75.*cm),
                            //pos,
                            logicalRPCBlock,
                            "PhysicalRPCBlock2",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

  G4VPhysicalVolume *phyRPCBlock3 = new G4PVPlacement(0,
                            G4ThreeVector(0.*cm,0.*cm,105.*cm),
                            //pos,
                            logicalRPCBlock,
                            "PhysicalRPCBlock3",
                            logicWorld,
                            false,
                            0,
   
                            checkOverlaps);
 G4VPhysicalVolume *phyPbBlock = new G4PVPlacement(0,
                            G4ThreeVector(0.*cm,0.*cm,0.*cm),
                            //pos,
                            logicalPbBlock,
                            "PhysicalPbBlock",
                            logicWorld,
                            false,
                            0,
   
                            checkOverlaps);

	return physWorld;

}
