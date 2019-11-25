
#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
//#include <fstream>
#include <map>
//#include "base/Global.h"


//#include <TTree.h>
//#include <TFile.h>

//#include "Track.h"

using namespace std;
class G4Run;
class G4LogicalVolume;


class B1RunAction : public G4UserRunAction
{
  public:
   static ofstream *myfile;
   static double fScatteringAngle;
   int counter;

#ifdef STORE
   //static TTree *fTree;
   //TFile *fRootFile;
#endif
    //static ofstream GetEnergyFile(){return myfile;}

    B1RunAction();
    virtual ~B1RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

