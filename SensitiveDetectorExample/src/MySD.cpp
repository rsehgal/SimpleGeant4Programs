/*
 * MySD.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "MySD.h"
#include "Output.h"
#include "colors.h"
#include <TF1.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TRandom.h>
int MySD::stepNum = 0;
int MySD::numOfParticlesReached = 0;
unsigned short MySD::numOfStrips = 0;
unsigned short MySD::stripSize = 0;
/*MySD::MySD() {
        // TODO Auto-generated constructor stub

}*/

MySD::~MySD() {
  // TODO Auto-generated destructor stub
}

MySD::MySD(const G4String &name, const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name), fHitsCollection(NULL) {
  collectionName.insert(hitsCollectionName);
  // unsigned short numOfStrips=10;
  numOfStrips = 100;
  stripSize = 100 * cm / numOfStrips;
  sampleHist = new TH1F("sampleHist", "sampleHist", numOfStrips, -50 * cm, 50 * cm);
  rndm = new TRandom;
}

void MySD::Initialize(G4HCofThisEvent *hce) {
  // Create hits collection
  // std::cout << "RAMAN Entered Initialize Of SD" << std::endl;
  numOfParticlesReached++;
  fHitsCollection = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool MySD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
  //	std::cout<<"SEHGAL Entered ProcessHits Of SD" << std::endl;
  // energy deposit

  // if (edep==0.) return false;

  MyHit *newHit = new MyHit();

  G4Track *track = aStep->GetTrack();
  bool isPrimary = (track->GetParentID() == 0);
  /*
    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
    newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()
                                                 ->GetCopyNumber());
    newHit->SetEdep(edep);
    newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
  */
  //  if(isPrimary)
  {
    G4ThreeVector hitPos = aStep->GetPostStepPoint()->GetPosition();
    newHit->SetPosition(hitPos);

    G4ThreeVector randomPos(GetRandom(hitPos.x()), GetRandom(hitPos.y()), hitPos.z());
    newHit->SetRandomPosition(randomPos);
    newHit->SetProcessName(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
    G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    newHit->SetName(touchable->GetVolume(0)->GetName());
    G4String particleName = track->GetDefinition()->GetParticleName();
    // std::cout << particleName << "  " ;
    fHitsCollection->insert(newHit);
  }
  //  std::cout << "New Hit position : " << newHit->GetPosition() << std::endl;

  return true;
}

double MySD::GetRandom(double val) {
  int binNum = sampleHist->GetXaxis()->FindBin(val);
  // std::cout << BLUE << "Val : " << val << " : BinNum : " << binNum << " :: Start : " << (-50*cm+(binNum-1)*stripSize)
  // << " :: End : " << (-50*cm+(binNum)*stripSize) << RESET << std::endl;
  double startVal = (-50 * cm + (binNum - 1) * stripSize);
  double endVal = (-50 * cm + (binNum)*stripSize);
  //TRandom rndm;
  double rndmVal = rndm->Uniform(startVal, endVal);
  // std::cout << "Act Val : " << val <<" : startVal : " << startVal <<" : endVal : " << endVal << " : Random Val : " <<
  // rndmVal << std::endl;
  return rndmVal;
}
void MySD::EndOfEvent(G4HCofThisEvent *) {
  // std::cout << "++++" << std::endl;
  // std::cout << "No of Hits : " << fHitsCollection->entries() << std::endl;
  // std::cout << "RAMAN Entered EndOfEvent Of SD" << std::endl;
  // if ( verboseLevel>1 ) {
  if (1) {
    G4int nofHits = fHitsCollection->entries();
    //    std::cout << RED << "-------->Hits Collection: in this event there are " << nofHits << " hits  " << RESET <<
    //    std::endl;
    //if (nofHits == 10) {
    if (nofHits == 4) {

      double x[3], y[3], z[3];
      //double x[9], y[9], z[9];
      x[0] = ((*fHitsCollection)[0]->GetRandomPosition()).x();
      y[0] = ((*fHitsCollection)[0]->GetRandomPosition()).y();
      z[0] = ((*fHitsCollection)[0]->GetRandomPosition()).z();

      x[1] = ((*fHitsCollection)[1]->GetRandomPosition()).x();
      y[1] = ((*fHitsCollection)[1]->GetRandomPosition()).y();
      z[1] = ((*fHitsCollection)[1]->GetRandomPosition()).z();

      x[2] = ((*fHitsCollection)[3]->GetRandomPosition()).x();
      y[2] = ((*fHitsCollection)[3]->GetRandomPosition()).y();
      z[2] = ((*fHitsCollection)[3]->GetRandomPosition()).z();
/*
      x[3] = ((*fHitsCollection)[3]->GetRandomPosition()).x();
      y[3] = ((*fHitsCollection)[3]->GetRandomPosition()).y();
      z[3] = ((*fHitsCollection)[3]->GetRandomPosition()).z();

      x[4] = ((*fHitsCollection)[5]->GetRandomPosition()).x();
      y[4] = ((*fHitsCollection)[5]->GetRandomPosition()).y();
      z[4] = ((*fHitsCollection)[5]->GetRandomPosition()).z();

      x[5] = ((*fHitsCollection)[6]->GetRandomPosition()).x();
      y[5] = ((*fHitsCollection)[6]->GetRandomPosition()).y();
      z[5] = ((*fHitsCollection)[6]->GetRandomPosition()).z();

      x[6] = ((*fHitsCollection)[7]->GetRandomPosition()).x();
      y[6] = ((*fHitsCollection)[7]->GetRandomPosition()).y();
      z[6] = ((*fHitsCollection)[7]->GetRandomPosition()).z();

      x[7] = ((*fHitsCollection)[8]->GetRandomPosition()).x();
      y[7] = ((*fHitsCollection)[8]->GetRandomPosition()).y();
      z[7] = ((*fHitsCollection)[8]->GetRandomPosition()).z();

      x[8] = ((*fHitsCollection)[9]->GetRandomPosition()).x();
      y[8] = ((*fHitsCollection)[9]->GetRandomPosition()).y();
      z[8] = ((*fHitsCollection)[9]->GetRandomPosition()).z();
*/
      double actX = ((*fHitsCollection)[2]->GetPosition()).x();
      double actY = ((*fHitsCollection)[2]->GetPosition()).y();
      // int binnum = sampleHist->GetXaxis()->FindBin(actY);
      // actY = sampleHist->GetXaxis()->GetBinCenter(binnum);
      // double actY = ((*fHitsCollection)[1]->GetPosition()).y();
      double actZ = ((*fHitsCollection)[2]->GetPosition()).z();

      double randX = ((*fHitsCollection)[2]->GetRandomPosition()).x();
      double randY = ((*fHitsCollection)[2]->GetRandomPosition()).y();

      TGraph *zx = new TGraph(3, z, x);
      TGraph *zy = new TGraph(3, z, y);

      TF1 *formulaZX = new TF1("linear_ZX", "[0]+[1]*x", -155 * cm, 155 * cm);
      TF1 *formulaZY = new TF1("linear_ZY", "[0]+[1]*x", -155 * cm, 155 * cm);

      zx->Fit(formulaZX, "q");
      zy->Fit(formulaZY, "q");

      double evalX = formulaZX->Eval(actZ);
      double evalY = formulaZY->Eval(actZ);

      //std::cout << MAGENTA << "Actual X : " << actX << " :: Random X : " << randX << " : Evaluated X : " << evalX <<  RESET << std::endl; 
//std::cout << MAGENTA << "Actual Y : " << actY << " :: Random Y : " << randY << " :
      // Evaluated Y : " << evalY << RESET << std::endl;

      // Output::instance()->FillDiffHist(actX-evalX);
      // if(formulaZY->GetChisquare() > 1)
      {
        double diffVal = randY - evalY;
        // std::cout << "Diff : " << diffVal << std::endl;
        Output::instance()->FillDiffHist(diffVal);
      }

      /*for (G4int i = 0; i < nofHits; i++) {
        (*fHitsCollection)[i]->Print();
      }*/
    }
  }
  // delete fHitsCollection;
}
