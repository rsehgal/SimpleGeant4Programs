#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <TCanvas.h>
#include <TApplication.h>
#include <TGraph.h>
#include <vector>

void CreateHistogram(std::string filename){
int nbinsx=100;
double startx = 0.;
double endx = 250.;
TApplication *fApp = new TApplication("Test", NULL, NULL);
TCanvas *c = new TCanvas("TestCanvas", "Energy Histogram", 800, 600);
c->Divide(2,2);
c->cd(1);
TH1F *energyHist = new TH1F("EnergyHistogram","EnergyHistogram",nbinsx,startx,endx);
std::ifstream infile(filename);
std::vector<double> x, y;

//For initial diversion histogram
startx = 0.;
endx = 10.;
nbinsx = 100;
TH1F *diversionHist = new TH1F("Initial Diversino Histogram","Initial Diversino Histogram",nbinsx,startx,endx);

double energy=0., xval=0., yval=0., initialDiversionAngle;
while(!infile.eof()){
   infile >> energy >> xval >> yval >> initialDiversionAngle;
   energyHist->Fill(energy);
   diversionHist->Fill(initialDiversionAngle*1000.);
   x.push_back(xval);
   y.push_back(yval);
}

energyHist->Draw();



//Making graph
c->cd(2);
TGraph *gr = new TGraph(x.size(),&x[0],&y[0]);
gr->SetTitle("Electron Beam Cone Base");
gr->GetXaxis()->SetTitle("X Coordinate");
gr->GetYaxis()->SetTitle("Y Coordinate");
gr->Draw("AP");


//Making histogram for initial diversion
c->cd(3);
diversionHist->Draw();

//Plotting final exit locations
x.clear();y.clear();
std::ifstream exitfile("exitPoints.txt");
double exX(0.),exY(0.);
while(!exitfile.eof()){
  exitfile >> exX >> exY;
  x.push_back(exX);
  y.push_back(exY);
} 

c->cd(4);
TGraph *grExit = new TGraph(x.size(),&x[0],&y[0]);
grExit->SetTitle("Reconstructed two tubes");
grExit->GetXaxis()->SetTitle("X Coordinate");
grExit->GetYaxis()->SetTitle("Y Coordinate");
grExit->Draw("AP");



fApp->Run();

}


