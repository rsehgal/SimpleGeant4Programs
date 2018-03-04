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
#include "G4GDMLParser.hh"

G4NistManager* nist = G4NistManager::Instance();
G4Material* mat = nist->FindOrBuildMaterial("G4_Galactic");
double sphi = 0.;
double dphi = 360.*deg;

MyDetectorConstruction::MyDetectorConstruction(){

}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct(){
  
  // G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  
  // Envelope params
  //
  G4double env_sizeXY = 20*m, env_sizeZ = 30*m;
  // G4Material* mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  //     
  // World
  //
  G4double world_sizeXYZ = 200*cm;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4double fExpHall_x = 600.*cm;
  G4double fExpHall_y = 600.*cm;
  G4double fExpHall_z = 600.*cm;


  G4Box * experimentalHall_box
    = new G4Box("expHall_b",fExpHall_x,fExpHall_y,fExpHall_z);
  G4LogicalVolume * experimentalHall_log
    = new G4LogicalVolume(experimentalHall_box,mat,"expHall_Logical");
  G4VPhysicalVolume * experimentalHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),experimentalHall_log,"expHall_Physical",
                        0,false,0);

 

  //Lets try to build material from NIST database
  // G4Box *leadBlock = new G4Box("LeadBlock",5.*cm,5.*cm,15.*cm);
  double rmin[]={250.,300.,350.,400.,450.};
  double rmax[]={255.,305.,355.,405.,455.};
  double dz[]={500.,600.,700.,800.,900.};

  for(int i = 0 ; i < 5 ; i++){
    new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            GetTube("tracker_tube_"+std::to_string(i),rmin[i],rmax[i],dz[i]),
                            ("tracker_tube_"+std::to_string(i)+"_Physical").c_str(),
                            experimentalHall_log,
                            false,
                            0,
                            checkOverlaps);
  }

  //Now building calorimeter geometries
  int startInnerRad = 500;
  for(int i = 0 ; i < 50 ; i++){
    //int startInnerRad = 500;
    new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            GetTube("calo_tube_"+std::to_string(i),startInnerRad,startInnerRad+30,4000),
                            ("calo_tube_"+std::to_string(i)+"_Physical").c_str(),
                            experimentalHall_log,
                            false,
                            0,
                            checkOverlaps);
    startInnerRad += 50;
    
  }


/*  G4Material *Pb=nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume *logicalLeadBlock = new G4LogicalVolume(leadBlock,Pb,"LogicalLeadBlock");
  G4VPhysicalVolume *phyLeadBlock = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            logicalLeadBlock,
                            "PhysicalWorld",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);

*/
  G4GDMLParser parser;
  //#define USE_CONS
  #ifdef USE_CONS
    parser.Write("debugRE01Cons.gdml", experimentalHall_phys);
  #else
    parser.Write("debugRE01Tube.gdml", experimentalHall_phys);
  #endif
  return experimentalHall_phys;

}

G4LogicalVolume* MyDetectorConstruction::GetTube(std::string name,double rmin,double rmax,double dz){//, double sphi, double dphi){

  G4VSolid *tube
  //#define USE_CONS
  #ifdef USE_CONS
    = new G4Cons(name.c_str(),rmin, rmax,rmin, rmax,dz, sphi, dphi);
  #else  
    = new G4Tubs(name.c_str(),rmin, rmax,dz, sphi, dphi);
  #endif
  G4LogicalVolume * tube_log
    = new G4LogicalVolume(tube,mat,(name+"_Logical").c_str());

  return tube_log;  
}


/*G4VPhysicalVolume* MyDetectorConstruction::Construct(){
  
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

 

  //Lets try to build material from NIST database
  G4Box *leadBlock = new G4Box("LeadBlock",5.*cm,5.*cm,15.*cm);
  G4Material *Pb=nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume *logicalLeadBlock = new G4LogicalVolume(leadBlock,Pb,"LogicalLeadBlock");
  G4VPhysicalVolume *phyLeadBlock = new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            logicalLeadBlock,
                            "PhysicalWorld",
                            logicWorld,
                            false,
                            0,
                            checkOverlaps);



	return physWorld;

}*/
