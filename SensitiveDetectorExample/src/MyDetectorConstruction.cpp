#include "MyDetectorConstruction.h"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "MySD.h"
//#include "MySD.h"
#include <G4GDMLParser.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::MyDetectorConstruction() : G4VUserDetectorConstruction(), fScoringVolume(0) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::~MyDetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;
  G4double world_sizeXYZ = 1000 * cm;
  G4Material *world_mat = nist->FindOrBuildMaterial("G4_Galactic");

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


  G4Material *bar_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Box *detPlane = new G4Box("DetPlane", 50 * cm, 50 * cm, 0.5 * cm);
  G4LogicalVolume *logicalDetPlane = new G4LogicalVolume(detPlane, bar_mat, "LogicalDetPlane");

  /*--------------------------------------------------------------------------*/
  /* Making the logical volume sensitive
  ** Commenting the below four line, disable the senstivity of the logical volume
  */
  /*--------------------------------------------------------------------------*/
  MySD *mySD = new MySD("SensitiveDetector", "HitColSensitiveDetector");
  G4SDManager *sdman = G4SDManager::GetSDMpointer();
  sdman->AddNewDetector(mySD);
  // Making it Sensitive
  logicalDetPlane->SetSensitiveDetector(mySD);

  double dist=50*cm;
  unsigned short numOfDet = 10; 
  double baseVal = (-1*numOfDet/2)*dist+dist/2;
  for(unsigned int i = 0 ; i < numOfDet ; i++){
  double zval = baseVal+(i*dist);
  new G4PVPlacement(0, G4ThreeVector(0.,0., zval), logicalDetPlane,
                    "PhysicalDetPlane-" + std::to_string(i),
                    logicWorld, false, i, checkOverlaps);


} 


// G4GDMLParser parser;
// parser.Write("geom.gdml", physWorld);
return physWorld;
}

void MyDetectorConstruction::CreateScintMatrix() {

  /*
   * Lets try to build the full matrix of PsBars
   */

  /*int barsInX = 9;
  int barsInY = 10;
  double zval = 0;
  double xstart = -1. * barsInX * halfXOneBar;
  double ystart = -1. * barsInY * halfYOneBar;
  std::cout << "XStart : " << xstart << " : YStart : " << ystart << std::endl;
  int counter = 0;
  G4RotationMatrix *yRot = new G4RotationMatrix; // Rotates X and Z axes only
  // yRot-­>rotateY(M_PI/2.*rad);
  yRot->rotateY(1 * M_PI / 2. * rad);

  for (unsigned int yindex = 0; yindex < barsInY; yindex++) {
    double yval = ystart + (2 * yindex + 1) * halfYOneBar;
    for (unsigned int xindex = 0; xindex < barsInX; xindex++) {
      double xval = xstart + (2 * xindex + 1) * halfXOneBar;
      std::cout << xval << "," << yval << "," << zval << std::endl;

      if (!(yindex % 2)) //&& yindex == 1)
        new G4PVPlacement(0, G4ThreeVector(xval, yval, zval), logicalPsBar,
                          "PhysicalPsBar-" + std::to_string(xindex) + "-" + std::to_string(yindex), logicWorld, false,
                          counter, checkOverlaps);
      else { //  if(yindex == 4)
        new G4PVPlacement(yRot, G4ThreeVector(zval, yval, xval), logicalPsBar,
                          "PhysicalPsBar-" + std::to_string(xindex) + "-" + std::to_string(yindex), logicWorld, false,
                          counter, checkOverlaps);
      }
    }
  }*/
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
