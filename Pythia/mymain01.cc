// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"
// ROOT, for histogramming.
#include "TH1.h"
// ROOT, for trees
#include "TTree.h"
#include "TMath.h"

//
#include "Vector.h"
#include "Processing.h"
using namespace Pythia8;

int main(int argc, char* argv[]) {
  // Create the ROOT application environment.
  TApplication theApp("hist", &argc, argv);
  // Generator.
  Pythia pythia;

  // Allow no substructure in e+- beams: normal for corrected LEP data.
  pythia.readString("PDF:lepton = off");
  // Process selection.
  pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
  // Switch off all Z0 decays and then switch back on those to quarks.
  /*pythia.readString("23:onMode = off");
  pythia.readString("23:onIfAny = 1 2 3 4 5");*/

  // LEP1 initialization at Z0 mass.
  pythia.readString("Beams:idA =  11");
  pythia.readString("Beams:idB = -11");
  double mZ = pythia.particleData.m0(23);
  pythia.settings.parm("Beams:eCM", mZ);
  pythia.init();

  // Create file on which histogram(s) can be saved.
  TFile* outFile = new TFile("mymain01.root", "RECREATE");
  /*vector moments;
  vector *event = &moments;
  TTree *T = new TTree("Events","Events Tree");
  TBranch *bLund = T->Branch("Lund",&event);
  TBranch *bJade = T->Branch("Jade",&event);
  TBranch *bDurham = T->Branch("Durham",&event);*/

  // Histograms.
  TH1I *nLund = new TH1I("nLu","Lund jet multiplicity", 10, 0, 10);
  TH1I *nJade = new TH1I("nJA","Jade jet multiplicity", 10, 0, 10);
  TH1I *nDurham = new TH1I("nDu","Durham jet multiplicity", 10, 0, 10);
  TH1F *PlLund = new TH1F("PlLund","Plan Lund ",40,0,1);
  TH1F *PlJade = new TH1F("PlJade","Plan Jade",40,0,1);
  TH1F *PlDurham = new TH1F("PlDurham","Plan Durham",40,0,1);
  TH1F *thLund = new TH1F("thLund","Lund Angle",40,0,1.6);
  TH1F *thJade = new TH1F("thJade","Jade Angle",40,0,1.6);
  TH1F *thDurham = new TH1F("thDurham","Durham Angle",40,0,1.6);
  double lundnorm;
  double jadenorm;
  double durhamnorm;

  // Set up cluster jet analyses.
  ClusterJet lund("Lund");
  ClusterJet jade("Jade");
  ClusterJet durham("Durham");
  Vector P0;
  Vector P1;
  Vector P2;
  Vector n;
  // Begin event loop. Generate event. Skip if error. List first few.
  for (int iEvent = 0; iEvent < 100000; ++iEvent) {
    if (!pythia.next()) continue;

    // Find and histogram cluster jets: Lund, Jade and Durham distance.
    //Lund
    if (lund.analyze( pythia.event, 0.01, 0.)) {
      if (iEvent < 3) lund.list();
      nLund -> Fill( lund.size() );
      if (lund.size() == 3){
          P0.x = lund.p(0).px();
          P0.y = lund.p(0).py();
          P0.z = lund.p(0).pz();
          P1.x = lund.p(1).px();
          P1.y = lund.p(1).py();
          P1.z = lund.p(1).pz();
          P2.x = lund.p(2).px();
          P2.y = lund.p(2).py();
          P2.z = lund.p(2).pz();
          lundnorm = plan(P0,P1,P2);
          PlLund -> Fill(lundnorm);
          thLund -> Fill(TMath::PiOver2()-TMath::ACos(lundnorm));
        }
    }
    //Jade
    if (jade.analyze( pythia.event, 0.01, 0.)) {
      if (iEvent < 3) jade.list();
      nJade -> Fill( jade.size() );
        if (jade.size() == 3){
          P0.x = jade.p(0).px();
          P0.y = jade.p(0).py();
          P0.z = jade.p(0).pz();
          P1.x = jade.p(1).px();
          P1.y = jade.p(1).py();
          P1.z = jade.p(1).pz();
          P2.x = jade.p(2).px();
          P2.y = jade.p(2).py();
          P2.z = jade.p(2).pz();
          jadenorm = plan(P0,P1,P2);
          PlJade -> Fill(jadenorm);
          thJade -> Fill(TMath::PiOver2()-TMath::ACos(jadenorm));
        }
    }
    //Durham
    if (durham.analyze( pythia.event, 0.01, 0.)) {
      if (iEvent < 3) durham.list();
      nDurham -> Fill( durham.size() );
          if (durham.size() == 3){
          P0.x = durham.p(0).px();
          P0.y = durham.p(0).py();
          P0.z = durham.p(0).pz();
          P1.x = durham.p(1).px();
          P1.y = durham.p(1).py();
          P1.z = durham.p(1).pz();
          P2.x = durham.p(2).px();
          P2.y = durham.p(2).py();
          P2.z = durham.p(2).pz();
          durhamnorm = plan(P0,P1,P2);
          PlDurham -> Fill(durhamnorm);
          thDurham -> Fill(TMath::PiOver2()-TMath::ACos(durhamnorm));
        }
    }
  }

  // End of event loop. Statistics. Output histograms.
  pythia.stat();
  nLund -> Write();
  nJade -> Write();
  nDurham -> Write();
  PlLund -> Write();
  PlJade -> Write();
  PlDurham -> Write();
  thLund -> Write();
  thJade -> Write();
  thDurham -> Write();
  delete outFile;
  // Done.
  return 0;
}
