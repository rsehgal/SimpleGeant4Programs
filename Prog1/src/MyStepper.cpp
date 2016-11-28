/*
 * MyStepper.cpp
 *
 *  Created on: Nov 28, 2016
 *      Author: rsehgal
 */

#include "MyStepper.h"
#include "G4Step.hh"
#include <iostream>
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4VSolid.hh"
#include "G4VProcess.hh"


MyStepper::MyStepper(){
	std::cout<<"********* Stepper Constructor Called ********" << std::endl;
	// TODO Auto-generated constructor stub

}

MyStepper::~MyStepper() {
	// TODO Auto-generated destructor stub
}

void MyStepper::UserSteppingAction(const G4Step *step){
	G4StepPoint* point1 = step->GetPreStepPoint();
    G4StepPoint* point2 = step->GetPostStepPoint();
    G4ThreeVector pos1 = point1->GetPosition();
    G4ThreeVector pos2 = point2->GetPosition();
    std::cout<<"ProcessName : " << point2->GetProcessDefinedStep()->GetProcessName() ;
    std::cout<<" : ProcessInteractionLength : " << point2->GetProcessDefinedStep()->GetPILfactor();
    std::cout<<" : SafetyToOut : " << point1->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetSolid()->DistanceToOut(pos1);
    std::cout<<" : DistToOut : " << point1->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetSolid()->DistanceToOut(pos1,(pos2-pos1).unit());
    std::cout<<" : Volume Name : " << point1->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName();
    std::cout<<" : Point1 : "<< pos1 << " : Point2 : " << pos2 << std::endl;
	//std::cout<< "StepLength : "<< step->GetStepLength() << std::endl;
}

