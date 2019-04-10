#include "UHH2/BaconJets/include/JECAnalysisPUjetsHists.h"
#include "UHH2/BaconJets/include/constants.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/common/include/Utils.h"

// #include "UHH2/BaconTrans/baconheaders/TJet.hh"
// #include "UHH2/BaconTrans/baconheaders/TEventInfo.hh"
// #include "UHH2/BaconTrans/baconheaders/BaconAnaDefs.hh"
// #include "UHH2/BaconTrans/baconheaders/TVertex.hh"

#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <getopt.h>
using namespace std;
using namespace uhh2;
//using namespace baconhep;
//    uhh2::Event::Handle<TClonesArray> h_pv;
JECAnalysisPUjetsHists::JECAnalysisPUjetsHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
    // book all histograms here
    // jets
    TH1::SetDefaultSumw2();

    double eta_bins[n_eta_RelVals];                                                                                                                                           
    for(int i=0; i<n_eta_RelVals; i++) eta_bins[i] = eta_range_RelVals[i];  
    book<TH2D>("Jet_eta_pt", "Jet_eta_pt;RECO jet #eta; jet pt", n_eta_RelVals-1, eta_bins, 100,0,1000);

    book<TH1F>("nPu","Number of PU events",100,0,100);
    book<TH1F>("N_PV","Number of PVtx",100,0,100);

    tt_nPU = ctx.get_handle<int>("nPU");
    tt_nvertices = ctx.get_handle<int>("nvertices");

    book<TH1F>("PU_id","PU id discrimintant",120,-1.1,1.1);
    book<TH2D>("Jet_eta_PUid", "Jet_eta_PUid;RECO jet #eta; PU id", n_eta_RelVals-1, eta_bins, 120,-1.1,1.1);

    book<TH2D>("Jet_eta_chEM", "Jet_eta_chEM;RECO jet #eta; Ch.EM", n_eta_RelVals-1, eta_bins, 110,0.0,1.1);
    book<TH2D>("Jet_eta_neuEM", "Jet_eta_neuEM;RECO jet #eta; Neut.EM", n_eta_RelVals-1, eta_bins, 110,0.0,1.1);
    book<TH2D>("Jet_eta_chHAD", "Jet_eta_chEM;RECO jet #eta; Ch.HAD", n_eta_RelVals-1, eta_bins, 110,0.0,1.1);
    book<TH2D>("Jet_eta_neuHAD", "Jet_eta_neuEM;RECO jet #eta; Neut.HAD", n_eta_RelVals-1, eta_bins, 110,0.0,1.1);

    //    book<TH2D>("Jet_pt_PUid", "Jet_pt_PUid;RECO jet pt; PU is", 100,0,1000, 120,-1.1,1.1);



}

void JECAnalysisPUjetsHists::fill(const uhh2::Event & ev){
  fill(ev, 0);
}
void JECAnalysisPUjetsHists::fill(const uhh2::Event & ev, const int reco_jet_id){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  // Don't forget to always use the weight when filling.

  if(ev.isRealData) return;//fill only for MC
  Jet & probe_jet = ev.jets->at(reco_jet_id);// probe RECO jet

  double weight = ev.weight;
  ((TH2D*)hist("Jet_eta_pt"))->Fill(fabs(probe_jet.eta()),probe_jet.pt(),weight);
  ((TH2D*)hist("Jet_eta_PUid"))->Fill(fabs(probe_jet.eta()),probe_jet.pileupID(),weight);
  //  ((TH2D*)hist("Jet_pt_PUid"))->Fill(probe_jet.pt(),probe_jet.pileupID(),weight);

  ((TH2D*)hist("Jet_eta_chEM"))->Fill(fabs(probe_jet.eta()),probe_jet.chargedEmEnergyFraction(),weight);
  ((TH2D*)hist("Jet_eta_neuEM"))->Fill(fabs(probe_jet.eta()),probe_jet.neutralEmEnergyFraction(),weight);
  ((TH2D*)hist("Jet_eta_chHAD"))->Fill(fabs(probe_jet.eta()),probe_jet.chargedHadronEnergyFraction(),weight);
  ((TH2D*)hist("Jet_eta_neuHAD"))->Fill(fabs(probe_jet.eta()),probe_jet.neutralHadronEnergyFraction(),weight);

  hist("PU_id")->Fill(probe_jet.pileupID(), weight); 
  hist("nPu")->Fill(ev.get(tt_nPU), weight);
  hist("N_PV")->Fill(ev.get(tt_nvertices), weight);

}

JECAnalysisPUjetsHists::~JECAnalysisPUjetsHists(){}
