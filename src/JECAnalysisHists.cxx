#include "UHH2/BaconJets/include/JECAnalysisHists.h"
#include "UHH2/BaconJets/include/constants.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Jet.h"

// #include "UHH2/BaconTrans/baconheaders/TJet.hh"
//#include "UHH2/BaconTrans/baconheaders/TEventInfo.hh"
//#include "UHH2/BaconTrans/baconheaders/BaconAnaDefs.hh"
//#include "UHH2/BaconTrans/baconheaders/TVertex.hh"



#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <getopt.h>
using namespace std;
using namespace uhh2;
//using namespace baconhep;
    uhh2::Event::Handle<TClonesArray> h_pv;
JECAnalysisHists::JECAnalysisHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
    // book all histograms here
    // jets
    TH1::SetDefaultSumw2();

    book<TH1F>("N_jets", "N_{jets}", 50, -0.5, 49.5);
    book<TH1F>("pt","p_{T} all jets; p_{T} (GeV)",100,0,1500);
    book<TH1F>("eta","#eta all jets; #eta",100,-5,5);
    double eta_bins[n_eta];
    for(int i=0; i<n_eta; i++) eta_bins[i] = eta_range[i];
    book<TH1F>("eta_binned","|#eta| all jets; |#eta|",n_eta-1, eta_bins);
    book<TH1F>("phi","#phi all jets; #phi",50,-M_PI,M_PI);
    book<TH1F>("MET","MET all jets; MET",400,0,400);

    book<TH1F>("nPu","Number of PU events",60,0,60);
    book<TH1F>("N_PV","Number of PVtx",60,0,60);
    book<TH1F>("weight_histo","weight_histo ",20,0,2);

    book<TH1F>("pt_1","p_{T} jet 1",100,0,600);
    book<TH1F>("eta_1","#eta jet 1",100,-5,5);

    book<TH1F>("pt_2","p_{T} jet 2",100,0,600);
    book<TH1F>("eta_2","#eta jet 2",100,-5,5);

    book<TH1F>("pt_3","p_{T} jet 3",100,0,600);
    book<TH1F>("eta_3","#eta jet 3",100,-5,5);

    book<TH1F>("ptRaw_barrel","p^{Raw}_{T} barrel jet; p_{T}^{Raw,barrel} (GeV)",100,0,600);
    book<TH1F>("ptRaw_probe","p^{Raw}_{T} probe jet; p_{T}^{Raw,probe} (GeV)",100,0,600);
    book<TH1F>("pt_barrel","p_{T} barrel jet; p_{T}^{barrel} (GeV)",100,0,600);
    book<TH1F>("pt_probe","p_{T} probe jet; p_{T}^{probe} (GeV)",100,0,600);
    book<TH1F>("eta_barrel","#eta barrel jet; #eta^{barrel}",100,-5,5);
    book<TH1F>("eta_probe","#eta probe jet; #eta^{probe}",100,-5,5);
    book<TH1F>("eta_probe_pos","#eta probe jet >=0; #eta^{probe}",50,0,5);
    book<TH1F>("eta_probe_neg","#eta probe jet <0; |#eta^{probe}|",50,0,5);
    book<TH1F>("pt_ave","p_{T} ave jet; p_{T}^{ave} (GeV)",600,0,600);
    book<TH1F>("pt_ave_pthat","p_{T} ave jet; p_{T}^{ave} - p_{T}^{hat})/p_{T}^{hat}(GeV)",100,0,600);
    book<TH1F>("pt_ave_rebin","p_{T} ave jet; p_{T}^{ave} (GeV)",300,0,3000);

    book<TH1F>("pt_rel","p_{T}^{jet3} / p_{T}^{ave}; #alpha ", 50, 0, 1);

    book<TH1F>("asym","asymmetrie jet 1 and jet 2; Asymmetry",150,-1.5,1.5);
    book<TH1F>("mpf","MPF response; MPF response",250,0.,2.5);
    book<TH1F>("r_rel","R_{rel}; R_{rel}; Relative response",250,0.,2.5);
 

    // book<TH2D>("mpf_vs_etaProbe","MPF response vs. #eta probe jet; #eta probe; MPF response",100,-5,5,100,0.,2.);
    // book<TH2D>("r_rel_vs_etaProbe","Relative response vs. #eta probe jet; #eta probe; R_{rel}",100,-5,5,100,0.,2.);
    book<TH2D>("mpf_vs_etaProbe","MPF response vs. #eta probe jet; #eta probe; MPF response",20,0,5,100,0.,2.);
    book<TH2D>("r_rel_vs_etaProbe","Relative response vs. #eta probe jet; #eta probe; R_{rel}",20,0,5,100,0.,2.);
    book<TH2D>("N_jets_vs_etaProbe","N_{jets} vs. #eta probe jet; #eta probe; N_{jets}",20,0,5,50, -0.5, 49.5);
    book<TH2D>("N_jets_vs_pt_ave","N_{jets} vs. pT_{ave}; pT_{ave}, GeV; N_{jets}",30,0,1000,50, -0.5, 49.5);
    book<TH2D>("pt_ave_vs_etaProbe","pt ave vs #eta probe jet; #eta probe; pT_{ave}, GeV",100,-5.2,5.2,30,0,1000);
  



    tt_gen_pthat  = ctx.get_handle<float>("gen_pthat");
    tt_gen_weight = ctx.get_handle<float>("gen_weight");
    tt_jet1_pt = ctx.get_handle<float>("jet1_pt");
    tt_jet2_pt = ctx.get_handle<float>("jet2_pt");
    tt_jet3_pt = ctx.get_handle<float>("jet3_pt");
    tt_jet1_ptRaw = ctx.get_handle<float>("jet1_ptRaw");
    tt_jet2_ptRaw = ctx.get_handle<float>("jet2_ptRaw");
    tt_jet3_ptRaw = ctx.get_handle<float>("jet3_ptRaw");
    tt_nvertices = ctx.get_handle<int>("nvertices");
    tt_probejet_eta = ctx.get_handle<float>("probejet_eta");
    tt_probejet_phi = ctx.get_handle<float>("probejet_phi");
    tt_probejet_pt = ctx.get_handle<float>("probejet_pt");
    tt_probejet_ptRaw = ctx.get_handle<float>("probejet_ptRaw");
    tt_barreljet_eta = ctx.get_handle<float>("barreljet_eta");
    tt_barreljet_phi = ctx.get_handle<float>("barreljet_phi");
    tt_barreljet_pt = ctx.get_handle<float>("barreljet_pt");
    tt_barreljet_ptRaw = ctx.get_handle<float>("barreljet_ptRaw");
    tt_pt_ave = ctx.get_handle<float>("pt_ave");
    tt_alpha = ctx.get_handle<float>("alpha");
    tt_alpha_sum = ctx.get_handle<float>("alpha_sum");
    tt_rel_r = ctx.get_handle<float>("rel_r");
    tt_mpf_r = ctx.get_handle<float>("mpf_r");
    tt_asymmetry = ctx.get_handle<float>("asymmetry");
    tt_nPU = ctx.get_handle<int>("nPU");

}

void JECAnalysisHists::fill(const uhh2::Event & ev){
  fill(ev, 0);
}
void JECAnalysisHists::fill(const uhh2::Event & ev, const int rand){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  // Don't forget to always use the weight when filling.


  double weight = ev.weight;
  const int njets = ev.jets->size();
  hist("N_jets")->Fill(njets, weight);
    
  for (int i=0; i<njets; i++){
    Jet* jets = &ev.jets->at(i);
    hist("pt")->Fill(jets->pt(), weight);
    hist("eta")->Fill(jets->eta(), weight);
    hist("eta_binned")->Fill(jets->eta(), weight);
    hist("phi")->Fill(jets->phi(), weight);
       
    hist("MET")->Fill(ev.met->pt(), weight);
    hist("nPu")->Fill(ev.get(tt_nPU), weight);
    hist("weight_histo")->Fill(weight, 1);
  }
  
  hist("N_PV")->Fill(ev.get(tt_nvertices), weight);
    
  

  Jet* jet1 = &ev.jets->at(0);
  hist("pt_1")->Fill(jet1->pt(), weight);
  hist("eta_1")->Fill(jet1->eta(), weight);
  Jet* jet2 = &ev.jets->at(1);
  hist("pt_2")->Fill(jet2->pt(), weight);
  hist("eta_2")->Fill(jet2->eta(), weight);
  float ratio_pt = (ev.get(tt_pt_ave) - ev.get(tt_gen_pthat))/ev.get(tt_gen_pthat);
  hist("pt_ave")          ->Fill(ev.get(tt_pt_ave), weight);
  hist("pt_ave_pthat")   ->Fill(ev.get(tt_pt_ave), weight);
  hist("pt_ave_rebin") ->Fill(ev.get(tt_pt_ave), weight);
  hist("ptRaw_barrel")    ->Fill(ev.get(tt_barreljet_ptRaw), weight);
  hist("ptRaw_probe")     ->Fill(ev.get(tt_probejet_ptRaw) , weight);
  hist("pt_barrel")   ->Fill(ev.get(tt_barreljet_pt), weight);
  hist("pt_probe")    ->Fill(ev.get(tt_probejet_pt) , weight);
  hist("eta_barrel")  ->Fill(ev.get(tt_barreljet_eta), weight);
  hist("eta_probe")   ->Fill(ev.get(tt_probejet_eta) , weight);
  if(ev.get(tt_probejet_eta)>=0) hist("eta_probe_pos")->Fill(ev.get(tt_probejet_eta) , weight);
  else hist("eta_probe_neg")->Fill(fabs(ev.get(tt_probejet_eta)) , weight);
  hist("mpf")         ->Fill(ev.get(tt_mpf_r), weight);
  hist("asym")        ->Fill(ev.get(tt_asymmetry), weight);
  hist("r_rel")       ->Fill(ev.get(tt_rel_r), weight);


  ((TH2D*)hist("mpf_vs_etaProbe"))->Fill(fabs(ev.get(tt_probejet_eta)),ev.get(tt_mpf_r),weight);
  ((TH2D*)hist("r_rel_vs_etaProbe"))->Fill(fabs(ev.get(tt_probejet_eta)),ev.get(tt_rel_r),weight);
  ((TH2D*)hist("N_jets_vs_etaProbe"))->Fill(fabs(ev.get(tt_probejet_eta)),njets,weight);

  float pt_ave = (0.5*(ev.get(tt_jet1_pt) + ev.get(tt_jet2_pt)));
  ((TH2D*)hist("pt_ave_vs_etaProbe"))->Fill(ev.get(tt_probejet_eta),pt_ave,weight);
  ((TH2D*)hist("N_jets_vs_pt_ave"))->Fill(pt_ave,njets,weight);

  if (njets > 2){
    Jet* jet3 = &ev.jets->at(2);
    hist("pt_3")->Fill(ev.get(tt_jet3_pt), weight);
    hist("eta_3")->Fill(jet3->eta(), weight);
    hist("pt_rel")->Fill(ev.get(tt_jet3_pt)/(0.5*(ev.get(tt_barreljet_pt) + ev.get(tt_probejet_pt) )),weight);

  }
}

JECAnalysisHists::~JECAnalysisHists(){}
