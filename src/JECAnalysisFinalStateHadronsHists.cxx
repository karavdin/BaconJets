#include "UHH2/BaconJets/include/JECAnalysisFinalStateHadronsHists.h"
#include "UHH2/BaconJets/include/constants.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Jet.h"

// #include "UHH2/BaconTrans/baconheaders/TJet.hh"
// #include "UHH2/BaconTrans/baconheaders/TEventInfo.hh"
// #include "UHH2/BaconTrans/baconheaders/BaconAnaDefs.hh"
// #include "UHH2/BaconTrans/baconheaders/TVertex.hh"

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
//    uhh2::Event::Handle<TClonesArray> h_pv;
JECAnalysisFinalStateHadronsHists::JECAnalysisFinalStateHadronsHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
    // book all histograms here
    // jets
    TH1::SetDefaultSumw2();

    book<TH1F>("Hadrons", "Hadrons", 7000, -3500, 3500);
    book<TH2F>("Hadrons_pt", "Hadrons_pt;;hadron pt", 8, 0, 8,200,0.001,100);
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(1,"#gamma");
    //    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(2,"#pi^{0}");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(2,"#pi^{#pm}");
    //    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(4,"K^{0}");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(3,"K^{0}_{L}");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(4,"K^{0}_{S}");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(5,"K^{#pm}");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(6,"p");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(7,"n");
    ((TH2D*)hist("Hadrons_pt"))->GetXaxis()->SetBinLabel(8,"other");

    double eta_bins[n_eta];                                                                                                                                           
    for(int i=0; i<n_eta; i++) eta_bins[i] = eta_range[i];  
    book<TH2F>("Hadrons_genjeteta", "Hadrons_genjeteta;;GEN jet #eta (matched to probe RECO jet)", 8,0,8,n_eta-1, eta_bins);
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(1,"#gamma");
    //    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(2,"#pi^{0}");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(2,"#pi^{#pm}");
    //    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(4,"K^{0}");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(3,"K^{0}_{L}");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(4,"K^{0}_{S}");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(5,"K^{#pm}");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(6,"p");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(7,"n");
    ((TH2D*)hist("Hadrons_genjeteta"))->GetXaxis()->SetBinLabel(8,"other");
}

void JECAnalysisFinalStateHadronsHists::fill(const uhh2::Event & ev){
  fill(ev, 0);
}
void JECAnalysisFinalStateHadronsHists::fill(const uhh2::Event & ev, const int gen_jet_id){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  // Don't forget to always use the weight when filling.

  if(ev.isRealData) return;//fill only for MC
  double dr_max=0.2;
  double weight = ev.weight;
  Particle & genj = ev.genjets->at(gen_jet_id);
  double genjet_eta=genj.eta();
  for(GenParticle & genp: *ev.genparticles){
    if(genp.status()!=1) continue;//looking only at final state partons
    double dr = deltaR(genj,genp); 
    if(dr<dr_max){
      int ptcl_id = genp.flavor();
      int ptcl_pt = genp.pt();
      hist("Hadrons")->Fill(ptcl_id,weight);
      if(fabs(ptcl_id)==22){
	((TH2D*)hist("Hadrons_pt"))->Fill("#gamma",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("#gamma",genjet_eta,weight);
      }
      // if(fabs(ptcl_id)==111){
      // 	((TH2D*)hist("Hadrons_pt"))->Fill(1,ptcl_pt,weight);
      // 	((TH2D*)hist("Hadrons_genjeteta"))->Fill(1,genjet_eta,weight);
      // }
      if(fabs(ptcl_id)==211){
	((TH2D*)hist("Hadrons_pt"))->Fill("#pi^{#pm}",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("#pi^{#pm}",genjet_eta,weight);
      }
      // if(fabs(ptcl_id)==311){
      // 	((TH2D*)hist("Hadrons_pt"))->Fill(3,ptcl_pt,weight);
      // 	((TH2D*)hist("Hadrons_genjeteta"))->Fill(3,genjet_eta,weight);
      // }
      if(fabs(ptcl_id)==130){
	((TH2D*)hist("Hadrons_pt"))->Fill("K^{0}_{L}",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("K^{0}_{L}",genjet_eta,weight);
      }
      if(fabs(ptcl_id)==310){
	((TH2D*)hist("Hadrons_pt"))->Fill("K^{0}_{S}",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("K^{0}_{S}",genjet_eta,weight);
      }
      if(fabs(ptcl_id)==321){
	((TH2D*)hist("Hadrons_pt"))->Fill("K^{#pm}",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("K^{#pm}",genjet_eta,weight);
      }
      if(fabs(ptcl_id)==2212){
	((TH2D*)hist("Hadrons_pt"))->Fill("p",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("p",genjet_eta,weight);
      }
      if(fabs(ptcl_id)==2112){
	((TH2D*)hist("Hadrons_pt"))->Fill("n",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("n",genjet_eta,weight);
      }
      if(fabs(ptcl_id)!=2112 && fabs(ptcl_id)!=2212 && fabs(ptcl_id)!=321 && fabs(ptcl_id)!=310 && fabs(ptcl_id)!=130 && fabs(ptcl_id)!=311 && fabs(ptcl_id)!=211 && fabs(ptcl_id)!=111 && fabs(ptcl_id)!=22){
	//	cout<<"fabs(ptcl_id)="<<fabs(ptcl_id)<<endl;
	((TH2D*)hist("Hadrons_pt"))->Fill("other",ptcl_pt,weight);
	((TH2D*)hist("Hadrons_genjeteta"))->Fill("other",genjet_eta,weight);
      }

      // ((TH2D*)hist("Hadrons_pt"))->Fill(fabs(ptcl_id),ptcl_pt,weight);
      // ((TH2D*)hist("Hadrons_genjeteta"))->Fill(fabs(ptcl_id),genj.eta(),weight);

    }
  }
}

JECAnalysisFinalStateHadronsHists::~JECAnalysisFinalStateHadronsHists(){}
