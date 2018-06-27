
#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "MyDetectorConstruction.h"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include <fstream>
#include "G4SystemOfUnits.hh"
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int B1SteppingAction::countSteps = 0;

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  // collect energy deposited in this step

  countSteps++;
G4Track* track = step->GetTrack();
  G4double edepStep = step->GetTotalEnergyDeposit();
//std::cout << edepStep << " : ## KE : " << track->GetKineticEnergy() << "## : ";
  fEventAction->AddEdep(edepStep);  

  G4StepPoint *point1 = step->GetPreStepPoint();
  G4StepPoint *point2 = step->GetPostStepPoint();
  G4TouchableHandle touch1 = point1->GetTouchableHandle();
  G4TouchableHandle touch2 = point2->GetTouchableHandle();

  G4String volName = touch1->GetVolume()->GetName();
if((volName== "PhysicalRPCBlock3"  || volName== "PhysicalRPCBlock2"  
   || volName== "PhysicalRPCBlock1"  || volName== "PhysicalRPCBlock")
                          && point1->GetStepStatus()==fGeomBoundary){

        
	std::ofstream outfile("Hits.txt",std::ios::app);

	G4ThreeVector hitPosition = point1->GetPosition();
	//std::cout<< volName << " : "<< hitPosition << std::endl;

	outfile << hitPosition.x() << " " << hitPosition.y() << " " << hitPosition.z() << std::endl;
        //std::cout << "---------------------------------------------------"<<std::endl;
	outfile.close();
}

/*
if(touch1->GetVolume()->GetName()== "PhysicalRPCBlock3"  
                          && point1->GetStepStatus()==fGeomBoundary){

	G4ThreeVector hitPosition = point1->GetPosition();
	std::cout<<"RPCBlock3 : "<< hitPosition << std::endl;
        std::cout << "---------------------------------------------------"<<std::endl;
}
if(touch1->GetVolume()->GetName()== "PhysicalRPCBlock2"  
                          && point1->GetStepStatus()==fGeomBoundary){

	G4ThreeVector hitPosition = point1->GetPosition();
	std::cout<<"RPCBlock2 : "<< hitPosition << std::endl;
        std::cout << "---------------------------------------------------"<<std::endl;
}
if(touch1->GetVolume()->GetName()== "PhysicalRPCBlock1"  
                          && point1->GetStepStatus()==fGeomBoundary){

	G4ThreeVector hitPosition = point1->GetPosition();
	std::cout<<"RPCBlock1 : "<< hitPosition << std::endl;
        std::cout << "---------------------------------------------------"<<std::endl;
}
if(touch1->GetVolume()->GetName()== "PhysicalRPCBlock"  
                          && point1->GetStepStatus()==fGeomBoundary){

	G4ThreeVector hitPosition = point1->GetPosition();
	std::cout<<"RPCBlock : "<< hitPosition << std::endl;
        std::cout << "---------------------------------------------------"<<std::endl;
}
*/  


//bool isPrimary = (track->GetParentID() == 0 );
  /*
  if(isPrimary && touch1->GetVolume()->GetName()== "PhysicalAlFoil"

                          && point1->GetStepStatus()==fGeomBoundary){
        std::ofstream outfile("exitPoints.txt",std::ios::app);
//	std::cout << "\nHit Location : " << point2->GetPosition() << std::endl;
        
	//std::cout << "\nHit Location : " << point1->GetPosition() << std::endl;
         G4ThreeVector gunpos(0.,0.,-10*cm);
         G4ThreeVector exitPoint = point1->GetPosition();
         
         G4ThreeVector fdir = exitPoint - gunpos;
         fdir = fdir.unit();
          double diversionAnglefinal = fdir.angle(G4ThreeVector(0.,0.,1.));
         outfile << exitPoint.x() << " " << exitPoint.y() <<" " <<exitPoint.z()<< " "<< diversionAnglefinal<< " " << std::sqrt(exitPoint.x()*exitPoint.x()+exitPoint.y()*exitPoint.y())<<std::endl;
outfile.close();
}

  if(isPrimary && touch1->GetVolume()->GetName()== "PhysicalDRZ3"

                          && point1->GetStepStatus()==fGeomBoundary){
        std::ofstream outfile2("finalexitPoints.txt",std::ios::app);
//	std::cout << "\nHit Location : " << point2->GetPosition() << std::endl;
        
	//std::cout << "\nHit Location : " << point1->GetPosition() << std::endl;
         G4ThreeVector finalexitPoint = point1->GetPosition();
          G4ThreeVector gunpos(0.,0.,-10*cm); 
         G4ThreeVector fdir = finalexitPoint - gunpos;
            
         fdir = fdir.unit();
          double diversionAnglefinal = fdir.angle(G4ThreeVector(0.,0.,1.));
          outfile2 << finalexitPoint.x() << " " << finalexitPoint.y() <<" " <<finalexitPoint.z()<< " "<< diversionAnglefinal<< " " << std::sqrt(finalexitPoint.x()*finalexitPoint.x()+finalexitPoint.y()*finalexitPoint.y())<<std::endl;
         outfile2.close();
        
	//std::cout << " @@ KE : "<< track->GetKineticEnergy() <<" @@ " ;
  }
*/
//  G4ThreeVector hitPre = track->GetPosition();
//  G4ThreeVector hitPost = track->GetPosition();
//  G4ThreeVector hitBeginOfPost = track->GetPosition();
//  if(point1->GetPhysicalVolume()->GetName()!="World")
//  if(point2->GetPhysicalVolume()->GetName()!="World")
  {

/*
	  if((touch1->GetVolume(2)->GetName()=="E0" ||
			  touch1->GetVolume(2)->GetName()=="E1" ||
			  touch1->GetVolume(2)->GetName()=="E2" ||
			  touch1->GetVolume(2)->GetName()=="E3" ||
			  touch1->GetVolume(2)->GetName()=="E4" )  && point1->GetStepStatus()==fGeomBoundary)
	  {
		  B1EventAction::energy.push_back(track->GetKineticEnergy());
		  B1EventAction::vertexEnergy.push_back(track->GetVertexKineticEnergy());
		  B1EventAction::position.push_back(point1->GetPosition());
		
	  }
*/ 
  }



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

