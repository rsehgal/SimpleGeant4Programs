#include "MyDetectorConstruction.h"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include <G4Tubs.hh>
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
#include <cmath>
#include <iostream>

int MyDetectorConstruction::stripNum = 0;
int MyDetectorConstruction::blockNum=-1;
int MyDetectorConstruction::eBlockNum=-1;


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
  
  G4double innerRadiusOfTheTube = 0.*cm;
  G4double outerRadiusOfTheTube = 60.*cm;
  G4double hightOfTheTube = 10. *cm;
  G4double startAngleOfTheTube = 0.*deg;
  G4double spanningAngleOfTheTube = 360.*deg;



  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.25*world_sizeXYZ, 0.25*world_sizeXYZ, 0.25*world_sizeXYZ);     //its size

   G4Tubs* tracker_tube= 
     new G4Tubs("World",
                 innerRadiusOfTheTube, 
                 outerRadiusOfTheTube,
                 hightOfTheTube,
                 startAngleOfTheTube, 
                 spanningAngleOfTheTube);


     
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


  G4double trackerPos_x =  0.0*meter;
  G4double trackerPos_y =  0.0*meter;
  G4double trackerPos_z =  0.0*meter;

  G4VPhysicalVolume* tracker_phys
    = new G4PVPlacement(0,                       // no rotation
                        G4ThreeVector(trackerPos_x,trackerPos_y,trackerPos_z), // translation position
                        logicWorld,             // its logical volume
                        "World",               // its name
                        0,    // its mother (logical) volume
                        false,                   // no boolean operations
                        0);                      // its copy number



  //Lets try to build target material from NIST database


//Lets try to build material from NIST database
/*
   double stripLen = 5.*cm/16.;
   double stripHalfLen = 0.5*stripLen;
  G4Box *deltaE = new G4Box("DeltaE",stripHalfLen,2.5*cm,0.0025*cm);

  std::cout<<"Strip length : "<< deltaE->GetXHalfLength(); 
  G4Material *Si=nist->FindOrBuildMaterial("G4_Si");
  G4LogicalVolume *deltaELogical = new G4LogicalVolume(deltaE,Si,"DeltaE");
  
*/
  G4Material *Si=nist->FindOrBuildMaterial("G4_Si");
  G4LogicalVolume *planeLogical = GetBlock("planeDeltaE",2.5*cm,2.5*cm,0.0025*cm,Si,16,0.0025*cm,1);

  G4LogicalVolume *planeE1Logical = GetBlock("planeE1",2.5*cm,2.5*cm,0.0025*cm,Si,16,0.0750*cm,1);
  G4LogicalVolume *planeE2Logical = GetBlock("planeE2",2.5*cm,2.5*cm,0.0025*cm,Si,16,0.0750*cm,2);
  G4LogicalVolume *planeE = CreateEBlock(planeE1Logical, planeE2Logical, 0.1500*cm, Si);

   G4Tubs *target = new G4Tubs("Target",0.*cm,0.5*cm,0.007*cm,0.*deg,360.*deg);
   G4Material *Sn=nist->FindOrBuildMaterial("G4_Sn");
   G4LogicalVolume *logicalTarget = new G4LogicalVolume(target,Sn,"Target");
   G4VPhysicalVolume *phyTarget = new G4PVPlacement(0,
                            G4ThreeVector (0.*cm,2.3*cm,0*cm),
                            logicalTarget,
                            "PhysicalWorld",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

for(int k=0; k < 5 ; k++){

  G4RotationMatrix *yRot=new G4RotationMatrix;
  yRot->rotateY((50+(20*k))*3.14/180);

  blockNum++;
G4VPhysicalVolume *planePhy = new G4PVPlacement(yRot,
                            G4ThreeVector(0.-std::cos((90-(55+(20*k)))*3.14/180)*17.5*cm,0.,0.+std::cos((55+(20*k))*3.14/180)*17.5*cm),
                            planeLogical,
                            "DeltaE"+std::to_string(k),
                            logicWorld,
                            false,
                            blockNum,
                           checkOverlaps);

 eBlockNum++;
 G4VPhysicalVolume *planeEPhy = new G4PVPlacement(yRot,
                            G4ThreeVector(0.-std::cos((90-(55+(20*k)))*3.14/180)*18.65*cm,0.,(1.15*cm-0.075*cm)+std::cos((55+(20*k))*3.14/180)*18.65*cm),
                            planeE,
                            "E"+std::to_string(k),
                            logicWorld,
                            false,
							eBlockNum,
                           checkOverlaps);
}


	return physWorld;
}

G4LogicalVolume* MyDetectorConstruction::GetBlock(std::string name,double halfX,double halfY, double halfZ, G4Material *mat,int numOfStrips, double stripHalfZ,int dir){
  G4bool checkOverlaps = true;
  double stripLen = 5.*cm/16.;
  double stripHalfLen = 0.5*stripLen;
  G4LogicalVolume *tempLogical =  new G4LogicalVolume( (new G4Box(name,halfX,halfY,halfZ)),mat, name+"Logical" );
  for(int i = 0 ; i < numOfStrips ; i++){
        G4ThreeVector temp(0.,0.,0.);
        
        if(dir==1){
	temp.setX(-halfX + stripHalfLen + i*stripLen);
	G4VPhysicalVolume *blockPhy = new G4PVPlacement(0,//yRot,
		            temp,		   
                            GetStrip("strip",stripHalfLen,2.5*cm,stripHalfZ,mat),
                            tempLogical->GetName()+"Strip"+std::to_string(i),
                            tempLogical,
                            false,
                            i,
                           checkOverlaps);
	}
	else{
	temp.setY(-halfY + stripHalfLen + i*stripLen);
	G4VPhysicalVolume *blockPhy = new G4PVPlacement(0,//yRot,
		            temp,		   
                            GetStrip("strip",2.5*cm,stripHalfLen,stripHalfZ,mat),
                            tempLogical->GetName()+"Strip"+std::to_string(i),
                            tempLogical,
                            false,
                            i,
                           checkOverlaps);
	
	}	
  }

  return tempLogical;
}

G4LogicalVolume* MyDetectorConstruction::GetStrip(std::string name,double halfX,double halfY, double halfZ, G4Material *mat){

return (new G4LogicalVolume( (new G4Box(name+std::to_string(stripNum),halfX,halfY,halfZ)),mat, name+std::to_string(stripNum)+"Logical" ));

}

G4LogicalVolume* MyDetectorConstruction::CreateEBlock(G4LogicalVolume* E1, G4LogicalVolume* E2, double halfZ, G4Material *mat){
  G4bool checkOverlaps = true;
G4LogicalVolume* EBlockLogical = GetStrip("XYBlock",2.5*cm,2.5*cm,halfZ,mat);
G4ThreeVector temp1(0.,0.,-halfZ);

G4VPhysicalVolume *blockEPhy1 = new G4PVPlacement(0,//yRot,
		            temp1,		   
                            E1,
                            "PlaneX",
                            EBlockLogical,
                            false,
                            0,
                           checkOverlaps);


G4ThreeVector temp2(0.,0.,halfZ);
G4VPhysicalVolume *blockEPhy2 = new G4PVPlacement(0,//yRot,
		            temp2,		   
                            E2,
                            "PlaneY",
                            EBlockLogical,
                            false,
                            0,
                           checkOverlaps);

return EBlockLogical;

}
