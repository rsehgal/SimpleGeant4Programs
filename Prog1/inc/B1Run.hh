
#ifndef B1Run_h
#define B1Run_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class B1Run : public G4Run
{
	std::vector<double> fScatteringAngleVect;

  public:
    B1Run();
    virtual ~B1Run();

    // method from the base class
    virtual void Merge(const G4Run*);
    
    // get methods
    std::vector<double> GetScatteringAngleVector() const{
    //std::cout << "GetScatteringAngleVector Called ........" << std::endl;
    	return fScatteringAngleVect;

    }
    void FillScatteringAngleVector(double scatteringAngle){fScatteringAngleVect.push_back(scatteringAngle);}


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

