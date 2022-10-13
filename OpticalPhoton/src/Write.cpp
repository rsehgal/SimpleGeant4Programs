/*
**	Filename : Write.cpp
**	2022-09-27
**	username : rsehgal
*/
#include "Write.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include <iostream>
#include <vector>
Tree::Tree() {}

Tree::Tree(std::string filename) : fFileName(filename) {
  fp = new TFile(fFileName.c_str(), "RECREATE");
  ftree = new TTree("ftree", "A tree to hold photon count of 4 scintillators");
  ftree->Branch("photonCount_0", &fPhotonCount_0, "fPhotonCount_0/i");
  ftree->Branch("photonCount_1", &fPhotonCount_1, "fPhotonCount_1/i");
  ftree->Branch("photonCount_2", &fPhotonCount_2, "fPhotonCount_2/i");
  ftree->Branch("photonCount_3", &fPhotonCount_3, "fPhotonCount_3/i");
  ftree->Branch("photonTime_0", &fPhotonTime_0);//, "fPhotonTime_0/i");
  ftree->Branch("photonTime_1", &fPhotonTime_1);//, "fPhotonTime_1/i");
  ftree->Branch("photonTime_2", &fPhotonTime_2);//, "fPhotonTime_2/i");
  ftree->Branch("photonTime_3", &fPhotonTime_3);//, "fPhotonTime_3/i");
  ftree->Branch("energyDep", &fEnergyDepositInAnEvent);//, "fPhotonTime_3/i");

  fHistPhotonCount_0 = new TH1F("Hist_PhotonCount_0", "Hist_PhotonCount_0", 10000, 0, 10000);
  fHistPhotonCount_1 = new TH1F("Hist_PhotonCount_1", "Hist_PhotonCount_1", 10000, 0, 10000);
  fHistPhotonCount_2 = new TH1F("Hist_PhotonCount_2", "Hist_PhotonCount_2", 10000, 0, 10000);
  fHistPhotonCount_3 = new TH1F("Hist_PhotonCount_3", "Hist_PhotonCount_3", 10000, 0, 10000);
}

void Tree::Fill(unsigned int phot_0, unsigned int phot_1, unsigned int phot_2, unsigned int phot_3) {
  fPhotonCount_0 = phot_0;
  fPhotonCount_1 = phot_1;
  fPhotonCount_2 = phot_2;
  fPhotonCount_3 = phot_3;
  if (phot_0)
    fHistPhotonCount_0->Fill(phot_0);
  if (phot_1)
    fHistPhotonCount_1->Fill(phot_1);
  if (phot_2)
    fHistPhotonCount_2->Fill(phot_2);
  if (phot_3)
    fHistPhotonCount_3->Fill(phot_3);
}
void Tree::FillTime(std::vector<unsigned int> phot_0, 
                    std::vector<unsigned int> phot_1, 
                    std::vector<unsigned int> phot_2, 
                    std::vector<unsigned int> phot_3) {
  fPhotonTime_0 = phot_0;
  fPhotonTime_1 = phot_1;
  fPhotonTime_2 = phot_2;
  fPhotonTime_3 = phot_3;
}
void Tree::FillEnergy(double energy){
fEnergyDepositInAnEvent = energy;
}
void Tree::FillTree() { ftree->Fill(); }
void Tree::Write() { fp->Write(); }
