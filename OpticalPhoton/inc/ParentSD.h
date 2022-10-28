/*
**	Filename : ParentSD.h
**	2022-10-28
**	username : rsehgal
*/
#ifndef ParentSD_h
#define ParentSD_h

#include <TFile.h>
#include <TH1F.h>
#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "colors.h"
//class TRandom3;
//class G4HCofThisEvent;

class ParentSD : public G4VSensitiveDetector {

public:
  ParentSD(const G4String name) : G4VSensitiveDetector(name) {}
  ParentSD() : G4VSensitiveDetector("Hello") {
	std::cout << RED << "ParentSD Constructor called........." << RESET << std::endl;
   }
  ~ParentSD() {
	std::cout << BLUE << "ParentSD Destructor called........." << RESET << std::endl;
   }
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history){

	std::cout << YELLOW << "ParentSD ProcessHits called........." << RESET << std::endl;
   }
  
  virtual void Initialize(G4HCofThisEvent *hce){
	std::cout << GREEN << "ParentSD Initialize called........." << RESET << std::endl;

  }
  virtual void EndOfEvent(G4HCofThisEvent *hce){
	std::cout << MAGENTA << "ParentSD EndOfEvent called........." << RESET << std::endl;
  }
};

#endif
