/*
**	Filename : Output.h
**	2022-03-17
**	username : rsehgal
*/
#ifndef Output_h
#define Output_h

class TFile;

#include <TH1F.h>
#include <iostream>
#include <string>

class Output{

std::string fFileName;
TFile *fp;
TH1F *fCryHist;
TH1F *fDetHist;
TH1F *fEnergyHist;
TH1F *fPhiHist;
TH1F *fDiffHist;
static Output *s_instance;

public:
static Output *instance();
static Output *instance(std::string fileName);
Output();
Output(std::string fileName);
virtual ~Output();

TH1F* GetCryHist() const;
TH1F* GetDetHist() const;
TH1F* GetDiffHist() const;

void FillCryHist(double val);
void FillDetHist(double val);
void FillEnergyHist(double val);
void FillPhiHist(double val);
void FillDiffHist(double val);
void Close();
};

#endif
