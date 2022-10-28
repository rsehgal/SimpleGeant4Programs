#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicalVolume.hh"
#include "MyDetectorConstruction.h"
#include "MyDetectorMessenger.h"
#include "MySD.h"
#include "ScintillatorSD.h"
#include "TestBoxSD.h"
MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  new MyDetectorMessenger(this);
  G4NistManager *nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  // World
  G4double world_sizeXYZ = 130 * cm;
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

  G4double a; // atomic mass
  G4double z; // atomic number

  G4double density;
  fH = new G4Element("H", "H", z = 1., a = 1.01 * g / mole);
  fC = new G4Element("C", "C", z = 6., a = 12.01 * g / mole);
  // Polystyrene
  fPstyrene = new G4Material("Polystyrene", density = 1.03 * g / cm3, 2);
  fPstyrene->AddElement(fC, 8);
  fPstyrene->AddElement(fH, 8);

  // Lets try to build material from NIST database
#ifdef PSBAR_GEOM
  G4Box *leadBlock = new G4Box("ScintillatorBlock", 50. * cm, 5. * cm, 5. * cm);
#else
  G4Box *leadBlock = new G4Box("ScintillatorBlock", 15. * cm, 2. * cm, 15. * cm);
#endif
  // fBlockMaterial = nist->FindOrBuildMaterial("G4_Pb");
  // fBlockMaterial = fPstyrene;
  fBlockMaterial = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  fLogicBlock = new G4LogicalVolume(leadBlock, fBlockMaterial, "LogicalScintillatorBlock");
  // G4VPhysicalVolume *phyLeadBlock =
  new G4PVPlacement(0,
                    // G4ThreeVector(),
                    G4ThreeVector(), fLogicBlock, "PhysicalScintillatorBlock", logicWorld, false, 0, checkOverlaps);
  // PMT
  G4Tubs *pmt = new G4Tubs("PMT", 0., 2. * cm, 1. * cm, 0., 2 * M_PI);
  // G4LogicalVolume *pmt_log = new G4LogicalVolume(pmt, pmt_mat, "Logical_PMT");
  G4LogicalVolume *pmt_log = new G4LogicalVolume(pmt, fBlockMaterial, "Logical_PMT");

  G4SDManager *sdman = G4SDManager::GetSDMpointer();

  MySD *mySD = new MySD("MySensitiveDetector", "MyBlockHitsCollection");
  sdman->AddNewDetector(mySD);
  pmt_log->SetSensitiveDetector(mySD);
  
  ScintillatorSD *myScintSD = new ScintillatorSD;
  sdman->AddNewDetector(myScintSD);
  fLogicBlock->SetSensitiveDetector(myScintSD);

  TestBoxSD *testBoxSD = new TestBoxSD("SensitiveWorld");
  sdman->AddNewDetector(testBoxSD);
  logicWorld->SetSensitiveDetector(testBoxSD);

  // MySD *mySD_Scint = new MySD("MySensitiveDetector_Scint", "MyBlockHitsCollection_Scint");
  // sdman->AddNewDetector(mySD_Scint);
  // fLogicBlock->SetSensitiveDetector(mySD);
    // fLogicBlock->SetSensitiveDetector(mySD_Scint);

  G4RotationMatrix *rm = new G4RotationMatrix;
  rm->rotateY(90 * deg);

#ifdef PSBAR_GEOM
  // G4VPhysicalVolume *phyPMT2 =
  new G4PVPlacement(rm, G4ThreeVector(51. * cm, 0., 0.), pmt_log, "Physical_PMT_2", logicWorld, false, 2,
                    checkOverlaps);
  // G4VPhysicalVolume *phyPMT3 =
  new G4PVPlacement(rm, G4ThreeVector(-51. * cm, 0., 0.), pmt_log, "Physical_PMT_3", logicWorld, false, 3,
                    checkOverlaps);
#else
  // G4VPhysicalVolume *phyPMT0 =
  new G4PVPlacement(0, G4ThreeVector(0., 0., 16. * cm), pmt_log, "Physical_PMT_0", logicWorld, false, 0, checkOverlaps);
  // G4VPhysicalVolume *phyPMT1 =
  new G4PVPlacement(0, G4ThreeVector(0., 0., -16. * cm), pmt_log, "Physical_PMT_1", logicWorld, false, 1,
                    checkOverlaps);

  // G4VPhysicalVolume *phyPMT2 =
  new G4PVPlacement(rm, G4ThreeVector(16. * cm, 0., 0.), pmt_log, "Physical_PMT_2", logicWorld, false, 2,
                    checkOverlaps);
  // G4VPhysicalVolume *phyPMT3 =
  new G4PVPlacement(rm, G4ThreeVector(-16. * cm, 0., 0.), pmt_log, "Physical_PMT_3", logicWorld, false, 3,
                    checkOverlaps);
#endif
  /*  G4VPhysicalVolume *phyPMT4 = new G4PVPlacement(rm, G4ThreeVector(-16.*cm, 0., 5.*cm), pmt_log, "Physical_PMT_4",
                                                   logicWorld, false, 4, checkOverlaps);
  G4RotationMatrix *rm2 = new G4RotationMatrix;
  rm2->rotateY(90*deg);

    G4VPhysicalVolume *phyPMT5 = new G4PVPlacement(rm2, G4ThreeVector(-16.*cm, 0., -5.*cm), pmt_log, "Physical_PMT_5",
                                                   logicWorld, false, 5, checkOverlaps);
  */

  // ------------ Generate & Add Material Properties Table ------------
  //
  std::vector<G4double> reflectivity = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,
                                        1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

  std::vector<G4double> photonEnergy = {
      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
      2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
      2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV};

  // Water
  //
  /*  std::vector<G4double> refractiveIndex1 = {1.3435, 1.344,  1.3445, 1.345,  1.3455, 1.346,  1.3465, 1.347,
                                              1.3475, 1.348,  1.3485, 1.3492, 1.35,   1.3505, 1.351,  1.3518,
                                              1.3522, 1.3530, 1.3535, 1.354,  1.3545, 1.355,  1.3555, 1.356,
                                              1.3568, 1.3572, 1.358,  1.3585, 1.359,  1.3595, 1.36,   1.3608};*/

  std::vector<G4double> refractiveIndex1 = {1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
                                            1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
                                            1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};

  std::vector<G4double> refAir = {1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};
  std::vector<G4double> absorption = {
      3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m,  12.346 * m, 13.889 * m, 15.152 * m, 17.241 * m,
      18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m, 45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m,
      55.556 * m, 52.632 * m, 52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
      30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m, 17.500 * m, 14.500 * m};

  std::vector<G4double> scintilFast = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                                       1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                                       1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};

  /*std::vector<G4double> scintilFast = {0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
                                       7.00, 6.00, 4.00, 3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00, 4.00,
                                       5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 5.00, 4.00};*/
  std::vector<G4double> scintilSlow = {0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
                                       7.00, 6.00, 4.00, 3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00, 4.00,
                                       5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 5.00, 4.00};

  G4MaterialPropertiesTable *myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex1)->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH", photonEnergy, absorption)->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast)->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT", photonEnergy, scintilSlow)->SetSpline(true);
  myMPT1->AddProperty("REFLECTIVITY", photonEnergy, reflectivity);

  myMPT1->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE", 1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 0.9 * ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT", 2.1 * ns);
  myMPT1->AddConstProperty("YIELDRATIO", 0.8);

  fBlockMaterial->SetMaterialPropertiesTable(myMPT1);


  G4MaterialPropertiesTable* Air_MPT = new G4MaterialPropertiesTable();
  Air_MPT->AddProperty("RINDEX", photonEnergy, refAir)->SetSpline(true);
  world_mat->SetMaterialPropertiesTable(Air_MPT);

  /*==== Creating a Test Volume to see the gamma distribution ======*/
  /*G4Material *test_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Box *test_box = new G4Box("TestBox",5 * cm, 0.05 * cm, 5. * cm);
  G4LogicalVolume *logic_test_box = new G4LogicalVolume(test_box, test_mat, "Logical_TestBox");
  new G4PVPlacement(0, G4ThreeVector(0.,6*cm,0.), logic_test_box, "Physical_TestBox", logicWorld, false, 0, checkOverlaps);
  TestBoxSD *testBoxSD = new TestBoxSD;
  sdman->AddNewDetector(testBoxSD);
  logic_test_box->SetSensitiveDetector(testBoxSD);*/
  /*================================================================*/

  return physWorld;
}

void MyDetectorConstruction::SetBlockMaterial(G4String materialName) {
  G4NistManager *nistManager = G4NistManager::Instance();

  G4Material *pttoMaterial = nistManager->FindOrBuildMaterial(materialName);

  if (fBlockMaterial != pttoMaterial) {
    if (pttoMaterial) {
      fBlockMaterial = pttoMaterial;
      if (fLogicBlock)
        fLogicBlock->SetMaterial(fBlockMaterial);
      G4cout << G4endl << "----> The target is made of " << materialName << G4endl;
    } else {
      G4cout << G4endl << "-->  WARNING from SetBlockMaterial : " << materialName << " not found" << G4endl;
    }
  }
}
