
#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "MyDetectorConstruction.h"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include <fstream>
#include "G4SystemOfUnits.hh"


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

  

  
  if(touch1->GetVolume()->GetName()== "PhysicalAlSheet"

                          && point1->GetStepStatus()==fGeomBoundary){
        std::ofstream outfile("exitPoints.txt",std::ios::app);
//	std::cout << "\nHit Location : " << point2->GetPosition() << std::endl;
        
	//std::cout << "\nHit Location : " << point1->GetPosition() << std::endl;
         G4ThreeVector gunpos(0.,0.,-75*cm);
         G4ThreeVector exitPoint = point1->GetPosition();
         
         G4ThreeVector fdir = exitPoint - gunpos;
         fdir = fdir.unit();
          double diversionAngle = fdir.angle(G4ThreeVector(0.,0.,1.));
          outfile << exitPoint.x() << " " << exitPoint.y() <<" " <<exitPoint.z()<< " "<< diversionAngle << std::endl;
         outfile.close();
        
	//std::cout << " @@ KE : "<< track->GetKineticEnergy() <<" @@ " ;
  }
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

