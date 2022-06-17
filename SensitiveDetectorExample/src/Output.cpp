/*
**	Filename : Output.cpp
**	2022-03-17
**	username : rsehgal
*/

#include "Output.h"
#include <TFile.h>
#include <iostream>
#include <string>
#include "colors.h"
Output *Output::s_instance = 0;

Output::Output() {}

Output::~Output() {}

Output::Output(std::string fileName) : fFileName(fileName) {
  fp = new TFile(fFileName.c_str(), "RECREATE");
  fCryHist = new TH1F("HistCry", "HistCry", 100, 0., M_PI / 2.);
  fDetHist = new TH1F("DetCry", "DetCry", 100, 0., M_PI / 2.);
  fEnergyHist = new TH1F("EnergyHist", "Energy", 100, 0., 10000.);
  fPhiHist = new TH1F("PhiHist", "PhiHist", 200, 0., 2*M_PI);
  fDiffHist = new TH1F("DiffHist","DiffHist",200,-100,100);
}

Output *Output::instance() {
  if (!s_instance) {
    std::cout << RED << "Instance of Output class doesn't exist in memory, Please create it first" << RESET
              << std::endl;
  }
}

Output *Output::instance(std::string fileName) {
  if (!s_instance) {
    s_instance = new Output(fileName);
  }
  return s_instance;
}

TH1F *Output::GetCryHist() const { return fCryHist; }

TH1F *Output::GetDetHist() const { return fDetHist; }

TH1F *Output::GetDiffHist() const { return fDiffHist; }

void Output::FillCryHist(double val) {fCryHist->Fill(val);}
void Output::FillDetHist(double val) {fDetHist->Fill(val);}
void Output::FillEnergyHist(double val) {fEnergyHist->Fill(val);}
void Output::FillPhiHist(double val) {fPhiHist->Fill(val);}
void Output::FillDiffHist(double val) {fDiffHist->Fill(val);}

void Output::Close(){
fp->cd();
fCryHist->Write();
fDetHist->Write();
fEnergyHist->Write();
fPhiHist->Write();
fDiffHist->Write();
fp->Close();
}
