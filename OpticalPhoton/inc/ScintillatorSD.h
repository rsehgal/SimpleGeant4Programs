/*
 *	Filename : ScintillatorSD.h
 **	2022-09-29
 **	username : rsehgal
 */
#ifndef ScintillatorSD_h
#define ScintillatorSD_h
#include <TFile.h>
#include <TH1F.h>
#include "G4VSensitiveDetector.hh"
class TRandom3;
class G4HCofThisEvent;
//class TFile;
//class TH1F;
class ScintillatorSD : public G4VSensitiveDetector {
public:
  double fEnergyDepInAEvent;
  TFile *fp;
  TH1F *fHistEDep;
  TH1F *fHistADC;
  unsigned int fPhotonCounter;
  TRandom3 *rng;

public:
  ScintillatorSD(const G4String name, const G4String hitsCollectionName) : G4VSensitiveDetector(name) {}
  ScintillatorSD(const G4String name) : G4VSensitiveDetector(name) {}
  ScintillatorSD() : G4VSensitiveDetector("Hello") {
    fp = new TFile("EnergyDep.root", "RECREATE");
    fHistEDep = new TH1F("HistEDep", "HistEDep", 100, 0, 700);
    fHistADC = new TH1F("fHistADC", "fHistADC", 1000, 0, 500);
  }
  ~ScintillatorSD() {
    fp->cd();
    fHistEDep->Write();
    fHistADC->Write();
    fp->Close();
  }
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  void Initialize(G4HCofThisEvent *);
  void EndOfEvent(G4HCofThisEvent *);
};

#endif
