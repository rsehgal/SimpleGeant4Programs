
#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>
#include <G4String.hh>
#include <G4ThreeVector.hh>
/// Event action class
///

class B1EventAction : public G4UserEventAction
{
static int evNo;
public:


  public:
	static int GetEventNum(){return evNo;}
    B1EventAction();
    virtual ~B1EventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

    double GetInitialDivergence(){return  fInitialDivergence;}
    double GetExitDivergence() {return fExitDivergence;}



  private:
    G4double  fEdep;
    double fInitialDivergence;
    double fExitDivergence;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

