/*
**	Filename : Write.h
**	2022-09-27
**	username : rsehgal
*/
#ifndef Write_h
#define Write_h

#include <string>

class TTree;
class TFile;
class TH1F;

class Tree {
public:
  Tree();
  Tree(std::string filename);
  void Fill(unsigned int phot_0, unsigned int phot_1, unsigned int phot_2, unsigned int phot_3);
  void Write();

private:
  std::string fFileName;
  TFile *fp; 
  TTree *ftree; 
  TH1F *fHistPhotonCount_0;
  TH1F *fHistPhotonCount_1;
  TH1F *fHistPhotonCount_2;
  TH1F *fHistPhotonCount_3;
  unsigned int fPhotonCount_0;
  unsigned int fPhotonCount_1;
  unsigned int fPhotonCount_2;
  unsigned int fPhotonCount_3;
};

#endif
