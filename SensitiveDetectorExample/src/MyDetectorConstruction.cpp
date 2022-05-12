#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicalVolume.hh"
#include "MyDetectorConstruction.h"
#include "MySD.h"
#include "G4Tubs.hh"
MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {

  G4NistManager *nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  // Envelope params
  //
  G4double env_sizeXY = 20 * m, env_sizeZ = 30 * m;
  // G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

  //
  // World
  //
  G4double world_sizeXYZ = 200 * cm;
  G4double world_sizeXY = 1.2 * env_sizeXY;
  G4double world_sizeZ = 1.2 * env_sizeZ;
  G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld = new G4Box("World",                                                        // its name
                                0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ); // its size

  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, // its solid
                                                    world_mat,  // its material
                                                    "World");   // its name

  G4VPhysicalVolume *physWorld = new G4PVPlacement(0,               // no rotation
                                                   G4ThreeVector(), // at (0,0,0)
                                                   logicWorld,      // its logical volume
                                                   "World",         // its name
                                                   0,               // its mother  volume
                                                   false,           // no boolean operation
                                                   0,               // copy number
                                                   checkOverlaps);  // overlaps checking
  MySD *mySD = new MySD("MySensitiveDetector", "MyBlockHitsCollection");
  G4SDManager *sdman = G4SDManager::GetSDMpointer();
  sdman->AddNewDetector(mySD);

  // Lets try to build material from NIST database
  G4Box *leadBlock = new G4Box("LeadBlock", 5. * cm, 10. * cm, 5. * cm);
  G4Material *Pb = nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume *logicalLeadBlock = new G4LogicalVolume(leadBlock, Pb, "LogicalLeadBlock");
  //logicalLeadBlock->SetSensitiveDetector(mySD);
  G4VPhysicalVolume *phyLeadBlock1 = new G4PVPlacement(0,
                                                       // G4ThreeVector(),
                                                       G4ThreeVector(0., 0., -10. * cm), logicalLeadBlock,
                                                       "Physical_LEAD_BLOCK_1", logicWorld, false, 0, checkOverlaps);
  G4VPhysicalVolume *phyLeadBlock2 = new G4PVPlacement(0,
                                                       // G4ThreeVector(),
                                                       G4ThreeVector(0., 0., 10. * cm), logicalLeadBlock,
                                                       "Physical_LEAD_BLOCK_2", logicWorld, false, 1, checkOverlaps);

  G4Box *bp = new G4Box("BP", 5. * cm, 10. * cm, 5. * cm);
  G4Material *mat_bp = nist->FindOrBuildMaterial("G4_Galactic");
  G4LogicalVolume *logicalBP = new G4LogicalVolume(bp, mat_bp, "Logical_BP");

  G4VPhysicalVolume *phy_BP =
      new G4PVPlacement(0,
                        // G4ThreeVector(),
                        G4ThreeVector(0., 0., 0.), logicalBP, "Physical_BP", logicWorld, false, 0, checkOverlaps);

  G4Tubs *bgo = new G4Tubs("BGO", 0., 2.54 * cm, 2.54 * cm, 0., 2 * M_PI);
  G4Material *mat_bgo = nist->FindOrBuildMaterial("G4_BGO");
  G4LogicalVolume *logicalBGO = new G4LogicalVolume(bgo, mat_bgo, "Logical_BGO");
  G4VPhysicalVolume *phy_BGO = new G4PVPlacement(0,
                                                 // G4ThreeVector(),
                                                 G4ThreeVector(0., 0., 20.54 * cm), logicalBGO, "Physical_BGO",
                                                 logicWorld, false, 0, checkOverlaps);

  logicalBGO->SetSensitiveDetector(mySD);

  G4Box *sample = new G4Box("Sample", 5. * cm, 5. * cm, 5. * cm);
  G4Material *mat_sample = nist->FindOrBuildMaterial("G4_C");
  G4LogicalVolume *logicalSAMPLE = new G4LogicalVolume(sample, mat_sample, "Logical_SAMPLE");

  G4VPhysicalVolume *phy_SAMPLE =
      new G4PVPlacement(0,
                        // G4ThreeVector(),
                        G4ThreeVector(0., -18*cm, 0.), logicalSAMPLE, "Physical_SAMPLE", logicWorld, false, 0, checkOverlaps);

  return physWorld;
}
