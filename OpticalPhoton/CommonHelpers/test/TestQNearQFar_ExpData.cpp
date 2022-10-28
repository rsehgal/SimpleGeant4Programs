/*
**	Filename : TestQNearQFar_ExpData.cpp
**	2022-10-25
**	username : rsehgal
*/
#include "CommonHelpers.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include <TApplication.h>
#include <TCanvas.h>
#include <iostream>
int main(int argc, char *argv[]) {

  TApplication *fApp = new TApplication("TEST", NULL, NULL);
  TFile *fp = new TFile(argv[1], "r");
  TTree *ftree = (TTree *)fp->Get("ftree");

  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  ftree->SetBranchAddress("fBrCh", &fBrCh);
  ftree->SetBranchAddress("fTstamp", &fTstamp);
  ftree->SetBranchAddress("fTime", &fTime);
  ftree->SetBranchAddress("fQlong", &fQlong);
  ftree->SetBranchAddress("fDelt", &fDelt);

  Long64_t nentries = ftree->GetEntries();

  TH1F *qnear = new TH1F("QNear", "QNear", 1000, 0, 1000);
  TH1F *qfar = new TH1F("QFar", "QFar", 1000, 0, 1000);
  TH1F *qmean = new TH1F("QMean", "QMean", 1000, 0, 1000);
  TH1F *numOfElectron = new TH1F("NumOfElectron", "NumOfElectron", 100, 0, 100);
  TH1F *histRatioFarNear = new TH1F("histRatioFarNear", "histRatioFarNear", 100, 0, 100);

  Long64_t nbytes = 0;
  double sum = 0.;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += ftree->GetEntry(i);
    unsigned int qnearVal = GetUnFoldedQNear(fQlong);
    unsigned int qfarVal = GetUnFoldedQFar(fQlong);
    qnear->Fill(qnearVal);
    qfar->Fill(qfarVal);
    qmean->Fill(sqrt(qnearVal * qfarVal));
    if(qnearVal)
    sum += (double)qfarVal / (double)qnearVal;

    // std::cout << "NearCharge : " << qnearVal*20. << std::endl;
    unsigned int numElec = qnearVal * 20. * 1.e+4 / 1.6;
    numElec /= 1.e+6;
    // std::cout << "NumOfElectron : " << numElec << std::endl;
    numOfElectron->Fill(numElec);

    unsigned int numElecFar = qfarVal * 20. * 1.e+4 / 1.6;
    numElecFar /= 1.e+6;

    if (numElec > 0.) {
      double ratioFarNear = qfarVal / qnearVal; // numElecFar / numElec;

      histRatioFarNear->Fill(ratioFarNear);
    }

    // std::cout << "DelT : " << fDelt << std::endl;
  }

  std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout <<"Sum : " << sum <<" : NEntries : " << nentries << std::endl;
  double meanVal = (sum / nentries);
  std::cout << "Mean Value : " << meanVal << std::endl;
  std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
  qnear->SetLineColor(1);
  qfar->SetLineColor(2);
  qnear->Draw();
  qfar->Draw("same");
  qmean->SetLineColor(4);
  qmean->Draw("same");

  new TCanvas("Qmean", "Qmean");
  qmean->Draw();

  new TCanvas;
  numOfElectron->Draw();

  new TCanvas;
  histRatioFarNear->Draw();
  // return
  fApp->Run();
}
