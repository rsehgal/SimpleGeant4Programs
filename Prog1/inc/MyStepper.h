/*
 * MyStepper.h
 *
 *  Created on: Nov 28, 2016
 *      Author: rsehgal
 */

#ifndef INC_MYSTEPPER_H_
#define INC_MYSTEPPER_H_

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"


class MyStepper : public G4UserSteppingAction {
public:
	MyStepper();//MyEventAction *eventAction);
	//virtual
	~MyStepper();

	//Method from base class
	virtual void UserSteppingAction(const G4Step*);

};

#endif /* INC_MYSTEPPER_H_ */
