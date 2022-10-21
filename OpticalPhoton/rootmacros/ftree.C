void run(Long64_t entryNum){
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated
  //     (Tue Oct  4 13:31:57 2022 by ROOT version6.22/08)
  //   from TTree ftree/A tree to hold photon count of 4 scintillators
  //   found on file: ScintillatorData.root
  //////////////////////////////////////////////////////////

  // Reset ROOT and connect tree file
  gROOT->Reset();
  TFile *f = (TFile *)gROOT->GetListOfFiles()->FindObject("ScintillatorData.root");
  if (!f) {
    //TFile *
    f = new TFile("ScintillatorData.root");
  }
  TTree *ftree = new TTree;
  f->GetObject("ftree", ftree);

  TH1F *histPhotonTime_0 = new TH1F("histPhotonTime_0", "histPhotonTime_0", 200, 0, 10000.);
  TH1F *histPhotonTime_0_Inv = new TH1F("histPhotonTime_0_Inv", "histPhotonTime_0_Inv", 200, 0, 10000.);
  // Declaration of leaves types
  UInt_t fPhotonCount_0=0;
  UInt_t fPhotonCount_1=0;
  UInt_t fPhotonCount_2=0;
  UInt_t fPhotonCount_3=0;
  vector<unsigned int> *photonTime_0=0;
  vector<unsigned int> *photonTime_1=0;
  vector<unsigned int> *photonTime_2=0;
  vector<unsigned int> *photonTime_3=0;

  // Set branch addresses.
  ftree->SetBranchAddress("photonCount_0", &fPhotonCount_0);
  ftree->SetBranchAddress("photonCount_1", &fPhotonCount_1);
  ftree->SetBranchAddress("photonCount_2", &fPhotonCount_2);
  ftree->SetBranchAddress("photonCount_3", &fPhotonCount_3);
  ftree->SetBranchAddress("photonTime_0", &photonTime_0);
  ftree->SetBranchAddress("photonTime_1", &photonTime_1);
  ftree->SetBranchAddress("photonTime_2", &photonTime_2);
  ftree->SetBranchAddress("photonTime_3", &photonTime_3);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // ftree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = entryNum;//ftree->GetEntries();

  Long64_t nbytes = 0;
  //for (Long64_t i = 0; i < nentries; i++) {
  for (Long64_t i = nentries-1; i < nentries; i++) {
    nbytes += ftree->GetEntry(i);

    for (unsigned int j = 0; j < (*photonTime_0).size(); j++) {
      histPhotonTime_0->Fill((*photonTime_0)[j]);
    }
  }

  
  for(unsigned int i = 0 ; i < histPhotonTime_0->GetNbinsX() ; i++){
	histPhotonTime_0_Inv->SetBinContent(i,-1.*histPhotonTime_0->GetBinContent(i));
  } 
  histPhotonTime_0->Draw();
  std::cout << "Integral 1 : " << histPhotonTime_0->Integral() << std::endl;
  new TCanvas();
  std::cout << "Integral 2 : " << histPhotonTime_0_Inv->Integral() << std::endl;
  histPhotonTime_0_Inv->Draw();
}
void ftree(Long64_t entryNum)
{
run(entryNum);
}
