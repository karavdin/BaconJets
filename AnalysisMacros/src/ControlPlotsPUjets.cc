// Read histograms filled in JECAnalysisPUjetsHists (by BaconJet/AnalysisModule module) for jets not matched to GEN jets (most probable PU jets)
// created on 10.04.2019 by A. Karavdina

#include "../include/CorrectionObject.h"
#include "../include/parameters.h"
#include <TH1F.h>
#include <TH2D.h>
#include <TH3.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <THStack.h>
#include <TLatex.h>
using namespace std;

void CorrectionObject::ControlPlotsPUjets(bool forEveryPtBin){
  cout << "--------------- Starting ControlPlotsPUjets() ---------------" << endl;
  bool forEveryPtBin_ = forEveryPtBin;
  if(forEveryPtBin_){
    cout<<"ControlPlotsPUjets are gonne be made for each pt bin seperatly"<<endl;
  }
  TString txttag=CorrectionObject::_generator_tag; 
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.05,"x");  
  gStyle->SetTitleSize(0.05,"y");
  gStyle->SetLabelSize(0.05,"x");  
  gStyle->SetLabelSize(0.05,"y");
  gStyle->SetTitleYOffset(0.9);
  gStyle->SetTitleXOffset(0.8);
  gStyle->SetPalette(55);
  gROOT->ForceStyle();



  TString dirNames[30] = {"goodRECO_all", 
			  "goodRECO_10_15","goodRECO_15_20","goodRECO_20_25","goodRECO_25_30","goodRECO_30_40",
			  "goodRECO_40_50","goodRECO_50_70","goodRECO_70_120","goodRECO_120_250",
			  "goodRECO_250_400","goodRECO_400_650","goodRECO_650_1000",
			  "goodRECO_1000_1500","goodRECO_1500_2000",
			  "badRECO_all",
			  "badRECO_10_15","badRECO_15_20","badRECO_20_25","badRECO_25_30","badRECO_30_40",
			  "badRECO_40_50","badRECO_50_70","badRECO_70_120","badRECO_120_250",
			  "badRECO_250_400","badRECO_400_650","badRECO_650_1000",
			  "badRECO_1000_1500","badRECO_1500_2000",
  };

  TString ptbinsLabels[30] = {"10 #leqp^{RECO}_{T}#leq #infty",
			     "10 #leqp^{RECO}_{T}#leq 15",
			     "15 #leqp^{RECO}_{T}#leq 20",
			     "20 #leqp^{RECO}_{T}#leq 25",
			     "25 #leqp^{RECO}_{T}#leq 30",
			     "30 #leqp^{RECO}_{T}#leq 40",
			     "40 #leqp^{RECO}_{T}#leq 50", "50 #leqp^{RECO}_{T}#leq 70", "70 #leqp^{RECO}_{T}#leq 120", 
			     "120 #leqp^{RECO}_{T}#leq 250", "250 #leqp^{RECO}_{T}#leq 400", "400 #leqp^{RECO}_{T}#leq 650",
			     "650 #leqp^{RECO}_{T}#leq 1000", "1000 #leqp^{RECO}_{T}#leq 1500",
			     "1500#leqp^{RECO}_{T}#leq 2000",
			     "10 #leqp^{RECO}_{T}#leq #infty",
			     "10 #leqp^{RECO}_{T}#leq 15",
			     "15 #leqp^{RECO}_{T}#leq 20",
			     "20 #leqp^{RECO}_{T}#leq 25",
			     "25 #leqp^{RECO}_{T}#leq 30",
			     "30 #leqp^{RECO}_{T}#leq 40",
			     "40 #leqp^{RECO}_{T}#leq 50", "50 #leqp^{RECO}_{T}#leq 70", "70 #leqp^{RECO}_{T}#leq 120", 
			     "120 #leqp^{RECO}_{T}#leq 250", "250 #leqp^{RECO}_{T}#leq 400", "400 #leqp^{RECO}_{T}#leq 650",
			     "650 #leqp^{RECO}_{T}#leq 1000", "1000 #leqp^{RECO}_{T}#leq 1500",
			     "1500#leqp^{RECO}_{T}#leq 2000",
};
  int loop_inter = 1;
  if(forEveryPtBin) loop_inter=30;
  
  for(int i = 0; i<loop_inter ; i++){
  
   TString dirName = (TString)dirNames[i];  
   TString ptbinLabel = (TString)ptbinsLabels[i];
   cout<<endl;  
   cout<<dirName<<endl;
      
   TString MCtitle = "MC";
   TString SavePlots = CorrectionObject::_outpath + "plots/control/ControlPlotsPUjets/CP_RecoGenMatched_" + dirName + "_" + CorrectionObject::_generator_tag;
   CorrectionObject::make_path(std::string((_outpath + "plots/").Data()));
   CorrectionObject::make_path(std::string((_outpath + "plots/control/").Data()));
   CorrectionObject::make_path(std::string((_outpath + "plots/control/ControlPlotsPUjets/").Data()));

   cout<<"++++++++++++++++ Collect all histograms ++++++++++++++++\n";
   TH2D* Jet_eta_pt_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_eta_pt");
   TH2D* Jet_eta_PUid_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_eta_PUid");

   TH2D* Jet_eta_chEM_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_eta_chEM");
   TH2D* Jet_eta_neuEM_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_eta_neuEM");
   TH2D* Jet_eta_chHAD_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_eta_chHAD");
   TH2D* Jet_eta_neuHAD_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_eta_neuHAD");


   //   TH2D* Jet_pt_PUid_MC = (TH2D*)CorrectionObject::_MCFile->Get(dirName+"/Jet_pt_PUid");
   
   TH1F* nPu_MC = (TH1F*)CorrectionObject::_MCFile->Get(dirName+"/nPu");
   TH1F* N_PV_MC = (TH1F*)CorrectionObject::_MCFile->Get(dirName+"/N_PV");
   TH1F* PU_id_MC = (TH1F*)CorrectionObject::_MCFile->Get(dirName+"/PU_id");

   Jet_eta_pt_MC->SetName("Jet_eta_pt_MC");
   Jet_eta_PUid_MC->SetName("Jet_eta_PUid_MC");
   //   Jet_pt_PUid_MC->SetName("Jet_pt_PUid_MC");
   nPu_MC->SetName("nPu_MC");
   N_PV_MC->SetName("N_PV_MC");
   PU_id_MC->SetName("PU_id_MC");
   
   TLatex *tex = new TLatex();
   tex->SetNDC();
   tex->SetTextSize(0.045);  

   cout<<"+++++++++++++++++++++ Plot extremely nice histograms ++++++++++++++++++++++++++++\n";
   TCanvas* cJet_eta_pt_MC = new TCanvas();
   //  Jet_eta_pt_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   Jet_eta_pt_MC->GetXaxis()->SetLabelSize(0.045);
   Jet_eta_pt_MC->GetYaxis()->SetLabelSize(0.045);
   Jet_eta_pt_MC->GetYaxis()->SetTitleSize(0.045);
   Jet_eta_pt_MC->SetTitle("");
   Jet_eta_pt_MC->Draw("colz");
   cJet_eta_pt_MC->SetLogy();
   cJet_eta_pt_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cJet_eta_pt_MC->Print(SavePlots + "_Jet_eta_pt.pdf","pdf");

   TCanvas* cJet_eta_PUid_MC = new TCanvas();
   //  Jet_eta_PUid_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   Jet_eta_PUid_MC->GetXaxis()->SetLabelSize(0.045);
   Jet_eta_PUid_MC->GetYaxis()->SetLabelSize(0.045);
   Jet_eta_PUid_MC->GetYaxis()->SetTitleSize(0.045);
   Jet_eta_PUid_MC->SetTitle("");
   Jet_eta_PUid_MC->Draw("colz");
   cJet_eta_PUid_MC->SetLogy();
   cJet_eta_PUid_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cJet_eta_PUid_MC->Print(SavePlots + "_Jet_eta_PUid.pdf","pdf");


   TCanvas* cJet_eta_chEM_MC = new TCanvas();
   //  Jet_eta_chEM_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   Jet_eta_chEM_MC->GetXaxis()->SetLabelSize(0.045);
   Jet_eta_chEM_MC->GetYaxis()->SetLabelSize(0.045);
   Jet_eta_chEM_MC->GetYaxis()->SetTitleSize(0.045);
   Jet_eta_chEM_MC->SetTitle("");
   Jet_eta_chEM_MC->Draw("colz");
   cJet_eta_chEM_MC->SetLogy();
   cJet_eta_chEM_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cJet_eta_chEM_MC->Print(SavePlots + "_Jet_eta_chEM.pdf","pdf");

   TCanvas* cJet_eta_neuEM_MC = new TCanvas();
   //  Jet_eta_neuEM_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   Jet_eta_neuEM_MC->GetXaxis()->SetLabelSize(0.045);
   Jet_eta_neuEM_MC->GetYaxis()->SetLabelSize(0.045);
   Jet_eta_neuEM_MC->GetYaxis()->SetTitleSize(0.045);
   Jet_eta_neuEM_MC->SetTitle("");
   Jet_eta_neuEM_MC->Draw("colz");
   cJet_eta_neuEM_MC->SetLogy();
   cJet_eta_neuEM_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cJet_eta_neuEM_MC->Print(SavePlots + "_Jet_eta_neuEM.pdf","pdf");

   TCanvas* cJet_eta_chHAD_MC = new TCanvas();
   //  Jet_eta_chHAD_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   Jet_eta_chHAD_MC->GetXaxis()->SetLabelSize(0.045);
   Jet_eta_chHAD_MC->GetYaxis()->SetLabelSize(0.045);
   Jet_eta_chHAD_MC->GetYaxis()->SetTitleSize(0.045);
   Jet_eta_chHAD_MC->SetTitle("");
   Jet_eta_chHAD_MC->Draw("colz");
   cJet_eta_chHAD_MC->SetLogy();
   cJet_eta_chHAD_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cJet_eta_chHAD_MC->Print(SavePlots + "_Jet_eta_chHAD.pdf","pdf");

   TCanvas* cJet_eta_neuHAD_MC = new TCanvas();
   //  Jet_eta_neuHAD_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   Jet_eta_neuHAD_MC->GetXaxis()->SetLabelSize(0.045);
   Jet_eta_neuHAD_MC->GetYaxis()->SetLabelSize(0.045);
   Jet_eta_neuHAD_MC->GetYaxis()->SetTitleSize(0.045);
   Jet_eta_neuHAD_MC->SetTitle("");
   Jet_eta_neuHAD_MC->Draw("colz");
   cJet_eta_neuHAD_MC->SetLogy();
   cJet_eta_neuHAD_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cJet_eta_neuHAD_MC->Print(SavePlots + "_Jet_eta_neuHAD.pdf","pdf");


   // TCanvas* cJet_pt_PUid_MC = new TCanvas();
   // //  Jet_pt_PUid_MC->GetYaxis()->SetTitle("p^{RECO}_{T}/p^{GEN}_{T}, GeV");
   // Jet_pt_PUid_MC->GetXaxis()->SetLabelSize(0.045);
   // Jet_pt_PUid_MC->GetYaxis()->SetLabelSize(0.045);
   // Jet_pt_PUid_MC->GetYaxis()->SetTitleSize(0.045);
   // Jet_pt_PUid_MC->SetTitle("");
   // Jet_pt_PUid_MC->Draw("colz");
   // cJet_pt_PUid_MC->SetLogy();
   // cJet_pt_PUid_MC->SetLogz();
   // tex->DrawLatex(0.15,0.95,txttag);
   // tex->DrawLatex(0.68,0.95,ptbinLabel);
   // cJet_pt_PUid_MC->Print(SavePlots + "_Jet_pt_PUid.pdf","pdf");

   TCanvas* cnPu_MC = new TCanvas();
   nPu_MC->GetXaxis()->SetTitle("N_{PU}");
   nPu_MC->GetXaxis()->SetLabelSize(0.045);
   nPu_MC->GetYaxis()->SetLabelSize(0.045);
   nPu_MC->GetYaxis()->SetTitleSize(0.045);
   nPu_MC->SetMarkerColor(kRed);
   nPu_MC->SetMarkerStyle(20);
   nPu_MC->SetTitle("");
   nPu_MC->Draw();
   //   cnPu_MC->SetLogy();
   //   cnPu_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cnPu_MC->Print(SavePlots + "_nPu.pdf","pdf");

   TCanvas* cN_PV_MC = new TCanvas();
   N_PV_MC->GetXaxis()->SetTitle("N_{PV}");
   N_PV_MC->GetXaxis()->SetLabelSize(0.045);
   N_PV_MC->GetYaxis()->SetLabelSize(0.045);
   N_PV_MC->GetYaxis()->SetTitleSize(0.045);
   N_PV_MC->SetMarkerColor(kRed);
   N_PV_MC->SetMarkerStyle(20);
   N_PV_MC->SetTitle("");
   N_PV_MC->Draw();
   //   cN_PV_MC->SetLogy();
   //   cN_PV_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cN_PV_MC->Print(SavePlots + "_N_PV.pdf","pdf");

   TCanvas* cPU_id_MC = new TCanvas();
   PU_id_MC->GetXaxis()->SetTitle("PU ID");
   PU_id_MC->GetXaxis()->SetLabelSize(0.045);
   PU_id_MC->GetYaxis()->SetLabelSize(0.045);
   PU_id_MC->GetYaxis()->SetTitleSize(0.045);
   PU_id_MC->SetMarkerColor(kRed);
   PU_id_MC->SetMarkerStyle(20);
   PU_id_MC->SetTitle("");
   PU_id_MC->Draw();
   //   cPU_id_MC->SetLogy();
   //   cPU_id_MC->SetLogz();
   tex->DrawLatex(0.15,0.95,txttag);
   tex->DrawLatex(0.68,0.95,ptbinLabel);
   cPU_id_MC->Print(SavePlots + "_PU_id.pdf","pdf");



   delete cJet_eta_pt_MC;
   delete cJet_eta_PUid_MC;
   delete cJet_eta_chEM_MC;
   delete cJet_eta_neuEM_MC;
   delete cJet_eta_chHAD_MC;
   delete cJet_eta_neuHAD_MC;
   //   delete cJet_pt_PUid_MC;
   delete cnPu_MC;
   delete cN_PV_MC;
   delete cPU_id_MC;

  };
}
