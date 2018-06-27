#include <fstream>
#include <iostream>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <G4ThreeVector.hh>
#include <vector>
#include <TApplication.h>
using namespace std;

int main()
{

    TApplication *fApp = new TApplication("Test", NULL, NULL);
    TCanvas *c = new TCanvas("TestCanvas", "ScatteringAngleCanvas", 800, 600);
    TH1F  *histogram = new TH1F("SD", "Data", 100, -200,400);

    ifstream infile("Hits.txt");
    double x=0.,y=0.,z=0.;
    int counter=0;
    std::vector<G4ThreeVector> hitVect;
    int evNo=0;
    while(!infile.eof()){

	do{
		infile >> x >> y >> z;		
		hitVect.push_back(G4ThreeVector(x,y,z));
		counter++;
			
	}while(counter%4);
	evNo++;
	G4ThreeVector incoming = hitVect[1]-hitVect[0];
	G4ThreeVector outgoing = hitVect[3]-hitVect[2];
	double scatteringAngle = incoming.angle(outgoing);
	cout<<"Scattering Angle of event :  "<< evNo << " : "<< scatteringAngle << endl;
	

	hitVect.clear();

  	counter = 0;	

//        cout << x <<" " <<y << " " << z << endl;

     histogram->Fill(scatteringAngle*1000.);
    }

    infile.close();
    histogram->Draw();
    fApp->Run();
return 0;
}
