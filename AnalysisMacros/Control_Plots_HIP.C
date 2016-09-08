// plot response to study HIP mitigation effect in MC
// Aug 2016

#include "header.h"


TString ToStringC(int num) {
  ostringstream start;
  start<<num;
  TString start1=start.str();
  return start1;
}

void Control_Plots_HIP(TString path="/nfs/dust/cms/user/karavdia/JEC_80X_standalone/JEC_Aug2016_HIP/", TString GenName="pythia8"){
  
  //MC
  const int num_points = 3;
  TFile *hip[num_points];TFile *hip_mtoff[num_points];
  hip[0] = new TFile(path+"/uhh2.AnalysisModuleRunner.MC.RelValQCD_FlatPt_15_3000_hip0p6_AK4CHS.root","READ");//0.6
  hip[1] = new TFile(path+"/uhh2.AnalysisModuleRunner.MC.RelValQCD_FlatPt_15_3000_hip0p8_AK4CHS.root","READ");//0.8
  hip[2] = new TFile(path+"/uhh2.AnalysisModuleRunner.MC.RelValQCD_FlatPt_15_3000_hip1p2_AK4CHS.root","READ");//1.2
  hip_mtoff[0] = new TFile(path+"/uhh2.AnalysisModuleRunner.MC.RelValQCD_FlatPt_15_3000_hip0p6_mtoff_AK4CHS.root","READ");
  hip_mtoff[1] = new TFile(path+"/uhh2.AnalysisModuleRunner.MC.RelValQCD_FlatPt_15_3000_hip0p8_mtoff_AK4CHS.root","READ");
  hip_mtoff[2] = new TFile(path+"/uhh2.AnalysisModuleRunner.MC.RelValQCD_FlatPt_15_3000_hip1p2_mtoff_AK4CHS.root","READ");
  TString titles_[num_points]={"hip0p6","hip0p8","hip1p2"};
  TString titles_mtoff_[num_points]={"hip0p6 mtoff","hip0p8 mtoff","hip1p2 mtoff"};
  

  // //DATA
  // const int num_points = 1;
  // TFile *hip[num_points];TFile *hip_mtoff[num_points];
  // hip[0] = new TFile(path+"/uhh2.AnalysisModuleRunner.DATA.DATA_RunE_29Jul_AK4CHS.root","READ");//re-reco
  // hip_mtoff[0] = new TFile(path+"/uhh2.AnalysisModuleRunner.DATA.DATA_RunE_AK4CHS.root","READ");
  // TString titles_[num_points]={"RunE_29Jul"};
  // TString titles_mtoff_[num_points]={"RunE"};
 

  TString dirName = "Selection";
  //  TString dirName = "JetMatching";
  //    TString dirName = "diJet";
  //  TString dirName = "noCuts";
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  // Plots

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


  //create plots
  

 TH2F *mpf_vs_etaProbe[num_points];
 TH2F *mpf_vs_etaProbe_mtoff[num_points];
 TH2F *r_rel_vs_etaProbe[num_points];
 TH2F *r_rel_vs_etaProbe_mtoff[num_points];
 TH1F *mpf_vs_etaProbe_Mean[num_points];
 TH1F *mpf_vs_etaProbe_mtoff_Mean[num_points];
 TH1F *mpf_vs_etaProbe_Profile[num_points];
 TH1F *mpf_vs_etaProbe_mtoff_Profile[num_points];
 TH1F *r_rel_vs_etaProbe_Mean[num_points];
 TH1F *r_rel_vs_etaProbe_mtoff_Mean[num_points];
 TH1F *r_rel_vs_etaProbe_Profile[num_points];
 TH1F *r_rel_vs_etaProbe_mtoff_Profile[num_points];
 TH2F *Njets_vs_etaProbe[num_points];
 TH2F *Njets_vs_etaProbe_mtoff[num_points];
 TH1F *Njets_vs_etaProbe_Mean[num_points];
 TH1F *Njets_vs_etaProbe_mtoff_Mean[num_points];
 TH1F *Njets_vs_etaProbe_Profile[num_points];
 TH1F *Njets_vs_etaProbe_mtoff_Profile[num_points];
 TH2F *Njets_vs_pt_ave[num_points];
 TH2F *Njets_vs_pt_ave_mtoff[num_points];
 TH1F *Njets_vs_pt_ave_Mean[num_points];
 TH1F *Njets_vs_pt_ave_mtoff_Mean[num_points];
 TH1F *Njets_vs_pt_ave_Profile[num_points];
 TH1F *Njets_vs_pt_ave_mtoff_Profile[num_points];
 for(int i=0;i<num_points;i++){
   mpf_vs_etaProbe[i] = (TH2F*)hip[i]->Get(dirName+"/mpf_vs_etaProbe")->Clone();
   mpf_vs_etaProbe[i]->FitSlicesY();
   mpf_vs_etaProbe_Mean[i] = (TH1F*)gDirectory->Get("mpf_vs_etaProbe_1")->Clone();
   mpf_vs_etaProbe[i]->ProfileX();
   mpf_vs_etaProbe_Profile[i] = (TH1F*)gDirectory->Get("mpf_vs_etaProbe_pfx")->Clone();

   r_rel_vs_etaProbe[i] = (TH2F*)hip[i]->Get(dirName+"/r_rel_vs_etaProbe")->Clone();
   r_rel_vs_etaProbe[i]->FitSlicesY();
   r_rel_vs_etaProbe_Mean[i] = (TH1F*)gDirectory->Get("r_rel_vs_etaProbe_1")->Clone();
   r_rel_vs_etaProbe[i]->ProfileX();
   r_rel_vs_etaProbe_Profile[i] = (TH1F*)gDirectory->Get("r_rel_vs_etaProbe_pfx")->Clone();

   mpf_vs_etaProbe_mtoff[i] = (TH2F*)hip_mtoff[i]->Get(dirName+"/mpf_vs_etaProbe")->Clone();
   mpf_vs_etaProbe_mtoff[i]->FitSlicesY();
   mpf_vs_etaProbe_mtoff_Mean[i] = (TH1F*)gDirectory->Get("mpf_vs_etaProbe_1")->Clone();
   mpf_vs_etaProbe_mtoff[i]->ProfileX();
   mpf_vs_etaProbe_mtoff_Profile[i] = (TH1F*)gDirectory->Get("mpf_vs_etaProbe_pfx")->Clone();

   r_rel_vs_etaProbe_mtoff[i] = (TH2F*)hip_mtoff[i]->Get(dirName+"/r_rel_vs_etaProbe")->Clone();
   r_rel_vs_etaProbe_mtoff[i]->FitSlicesY();
   r_rel_vs_etaProbe_mtoff_Mean[i] = (TH1F*)gDirectory->Get("r_rel_vs_etaProbe_1")->Clone();
   r_rel_vs_etaProbe_mtoff[i]->ProfileX();
   r_rel_vs_etaProbe_mtoff_Profile[i] = (TH1F*)gDirectory->Get("r_rel_vs_etaProbe_pfx")->Clone();

   mpf_vs_etaProbe_Mean[i]->SetMarkerStyle(20);
   mpf_vs_etaProbe_Mean[i]->SetMarkerColor(i+1);
   mpf_vs_etaProbe_Mean[i]->SetMarkerSize(0.5);
   mpf_vs_etaProbe_mtoff_Mean[i]->SetMarkerStyle(26);
   mpf_vs_etaProbe_mtoff_Mean[i]->SetMarkerColor(i+1);
   mpf_vs_etaProbe_mtoff_Mean[i]->SetMarkerSize(0.5);
   r_rel_vs_etaProbe_Mean[i]->SetMarkerStyle(20);
   r_rel_vs_etaProbe_Mean[i]->SetMarkerColor(i+1);
   r_rel_vs_etaProbe_Mean[i]->SetMarkerSize(0.5);
   r_rel_vs_etaProbe_mtoff_Mean[i]->SetMarkerStyle(26);
   r_rel_vs_etaProbe_mtoff_Mean[i]->SetMarkerColor(i+1);
   r_rel_vs_etaProbe_mtoff_Mean[i]->SetMarkerSize(0.5);

   mpf_vs_etaProbe_Profile[i]->SetMarkerStyle(20);
   mpf_vs_etaProbe_Profile[i]->SetMarkerColor(i+1);
   mpf_vs_etaProbe_Profile[i]->SetMarkerSize(0.5);
   mpf_vs_etaProbe_mtoff_Profile[i]->SetMarkerStyle(26);
   mpf_vs_etaProbe_mtoff_Profile[i]->SetMarkerColor(i+1);
   mpf_vs_etaProbe_mtoff_Profile[i]->SetMarkerSize(0.5);
   r_rel_vs_etaProbe_Profile[i]->SetMarkerStyle(20);
   r_rel_vs_etaProbe_Profile[i]->SetMarkerColor(i+1);
   r_rel_vs_etaProbe_Profile[i]->SetMarkerSize(0.5);
   r_rel_vs_etaProbe_mtoff_Profile[i]->SetMarkerStyle(26);
   r_rel_vs_etaProbe_mtoff_Profile[i]->SetMarkerColor(i+1);
   r_rel_vs_etaProbe_mtoff_Profile[i]->SetMarkerSize(0.5);

   Njets_vs_etaProbe[i] = (TH2F*)hip[i]->Get(dirName+"/N_jets_vs_etaProbe")->Clone();
   Njets_vs_etaProbe[i]->FitSlicesY();
   Njets_vs_etaProbe_Mean[i] = (TH1F*)gDirectory->Get("N_jets_vs_etaProbe_1")->Clone();
   Njets_vs_etaProbe[i]->ProfileX();
   Njets_vs_etaProbe_Profile[i] = (TH1F*)gDirectory->Get("N_jets_vs_etaProbe_pfx")->Clone();

   Njets_vs_etaProbe_mtoff[i] = (TH2F*)hip_mtoff[i]->Get(dirName+"/N_jets_vs_etaProbe")->Clone();
   Njets_vs_etaProbe_mtoff[i]->FitSlicesY();
   Njets_vs_etaProbe_mtoff_Mean[i] = (TH1F*)gDirectory->Get("N_jets_vs_etaProbe_1")->Clone();
   Njets_vs_etaProbe_mtoff[i]->ProfileX();
   Njets_vs_etaProbe_mtoff_Profile[i] = (TH1F*)gDirectory->Get("N_jets_vs_etaProbe_pfx")->Clone();

   Njets_vs_etaProbe_Mean[i]->SetMarkerStyle(20);
   Njets_vs_etaProbe_Mean[i]->SetMarkerColor(i+1);
   Njets_vs_etaProbe_Mean[i]->SetMarkerSize(0.5);
   Njets_vs_etaProbe_mtoff_Mean[i]->SetMarkerStyle(26);
   Njets_vs_etaProbe_mtoff_Mean[i]->SetMarkerColor(i+1);
   Njets_vs_etaProbe_mtoff_Mean[i]->SetMarkerSize(0.5);
   Njets_vs_etaProbe_Profile[i]->SetMarkerStyle(20);
   Njets_vs_etaProbe_Profile[i]->SetMarkerColor(i+1);
   Njets_vs_etaProbe_Profile[i]->SetMarkerSize(0.5);
   Njets_vs_etaProbe_mtoff_Profile[i]->SetMarkerStyle(26);
   Njets_vs_etaProbe_mtoff_Profile[i]->SetMarkerColor(i+1);
   Njets_vs_etaProbe_mtoff_Profile[i]->SetMarkerSize(0.5);

   Njets_vs_pt_ave[i] = (TH2F*)hip[i]->Get(dirName+"/N_jets_vs_pt_ave")->Clone();
   Njets_vs_pt_ave[i]->FitSlicesY();
   Njets_vs_pt_ave_Mean[i] = (TH1F*)gDirectory->Get("N_jets_vs_pt_ave_1")->Clone();
   Njets_vs_pt_ave[i]->ProfileX();
   Njets_vs_pt_ave_Profile[i] = (TH1F*)gDirectory->Get("N_jets_vs_pt_ave_pfx")->Clone();

   Njets_vs_pt_ave_mtoff[i] = (TH2F*)hip_mtoff[i]->Get(dirName+"/N_jets_vs_pt_ave")->Clone();
   Njets_vs_pt_ave_mtoff[i]->FitSlicesY();
   Njets_vs_pt_ave_mtoff_Mean[i] = (TH1F*)gDirectory->Get("N_jets_vs_pt_ave_1")->Clone();
   Njets_vs_pt_ave_mtoff[i]->ProfileX();
   Njets_vs_pt_ave_mtoff_Profile[i] = (TH1F*)gDirectory->Get("N_jets_vs_pt_ave_pfx")->Clone();

   Njets_vs_pt_ave_Mean[i]->SetMarkerStyle(20);
   Njets_vs_pt_ave_Mean[i]->SetMarkerColor(i+1);
   Njets_vs_pt_ave_Mean[i]->SetMarkerSize(0.5);
   Njets_vs_pt_ave_mtoff_Mean[i]->SetMarkerStyle(26);
   Njets_vs_pt_ave_mtoff_Mean[i]->SetMarkerColor(i+1);
   Njets_vs_pt_ave_mtoff_Mean[i]->SetMarkerSize(0.5);

   Njets_vs_pt_ave_Profile[i]->SetMarkerStyle(20);
   Njets_vs_pt_ave_Profile[i]->SetMarkerColor(i+1);
   Njets_vs_pt_ave_Profile[i]->SetMarkerSize(0.5);
   Njets_vs_pt_ave_mtoff_Profile[i]->SetMarkerStyle(26);
   Njets_vs_pt_ave_mtoff_Profile[i]->SetMarkerColor(i+1);
   Njets_vs_pt_ave_mtoff_Profile[i]->SetMarkerSize(0.5);

 }

 TLegend *leg1;
  leg1 = new TLegend(0.13,0.13,0.45,0.4,"","brNDC");//x+0.1
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.045);
  leg1->SetFillColor(10);
  leg1->SetLineColor(1);
  leg1->SetTextFont(42);

  TCanvas* f = new TCanvas(); 
  f->Divide(2,2);
  f->cd(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
  // mpf_vs_etaProbe_Mean[0]->Draw();
  mpf_vs_etaProbe_Mean[0]->SetTitle("MPF");
  mpf_vs_etaProbe_Mean[0]->GetYaxis()->SetRangeUser(0.5,1.25);
  mpf_vs_etaProbe_Mean[0]->GetYaxis()->SetTitle("Response");
  for(int i=0;i<num_points;i++){
    mpf_vs_etaProbe_Mean[i]->Draw("same");
   mpf_vs_etaProbe_mtoff_Mean[i]->Draw("same");//DATA
   leg1->AddEntry(mpf_vs_etaProbe_Mean[i],titles_[i],"lp");
   leg1->AddEntry(mpf_vs_etaProbe_mtoff_Mean[i],titles_mtoff_[i],"lp");
 }
 leg1->Draw();
 f->cd(3);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
 r_rel_vs_etaProbe_Mean[0]->SetTitle("pT-balance");
 r_rel_vs_etaProbe_Mean[0]->GetYaxis()->SetRangeUser(0.5,1.25);
 r_rel_vs_etaProbe_Mean[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   r_rel_vs_etaProbe_Mean[i]->Draw("same");
   r_rel_vs_etaProbe_mtoff_Mean[i]->Draw("same");//DATA
 }

f->cd(2);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
 mpf_vs_etaProbe_mtoff_Mean[0]->SetTitle("MPF");
 mpf_vs_etaProbe_mtoff_Mean[0]->GetYaxis()->SetRangeUser(0.5,1.25);
 mpf_vs_etaProbe_mtoff_Mean[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   mpf_vs_etaProbe_mtoff_Mean[i]->Draw("same");
   //   leg1->AddEntry(mpf_vs_etaProbe_Mean[i],titles_[i],"lp");
   //   leg1->AddEntry(mpf_vs_etaProbe_mtoff_Mean[i],titles_mtoff_[i],"lp");
 }
 // leg1->Draw();
 f->cd(4);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
r_rel_vs_etaProbe_mtoff_Mean[0]->SetTitle("pT-balance");
r_rel_vs_etaProbe_mtoff_Mean[0]->GetYaxis()->SetRangeUser(0.5,1.25);
 r_rel_vs_etaProbe_mtoff_Mean[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   //   r_rel_vs_etaProbe_Mean[i]->Draw("same");
   //   r_rel_vs_etaProbe_mtoff_Mean[i]->Add(r_rel_vs_etaProbe_Mean[i],-1);
   //   r_rel_vs_etaProbe_mtoff_Mean[i]->Divide(r_rel_vs_etaProbe_Mean[i]);
   r_rel_vs_etaProbe_mtoff_Mean[i]->Draw("same");
 }
 f->Print(path+"plots/HIP_test__ResponsesVsEta_"+titles_[0]+".pdf");

 TCanvas* d = new TCanvas();
 d->Divide(2,2);
 d->cd(1);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
 Njets_vs_etaProbe_Mean[0]->SetTitle("");
 Njets_vs_etaProbe_Mean[0]->GetYaxis()->SetTitle("N_{jets}");
 Njets_vs_etaProbe_Mean[0]->GetYaxis()->SetRangeUser(0,20);
 for(int i=0;i<num_points;i++){
   Njets_vs_etaProbe_Mean[i]->Draw("same");
   Njets_vs_etaProbe_mtoff_Mean[i]->Draw("same");//DATA
 }
 leg1->Draw();
 d->cd(2);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
 Njets_vs_etaProbe_mtoff_Mean[0]->SetTitle("");
 Njets_vs_etaProbe_mtoff_Mean[0]->GetYaxis()->SetRangeUser(0,20);
 Njets_vs_etaProbe_mtoff_Mean[0]->GetYaxis()->SetTitle("N_{jets}");
 for(int i=0;i<num_points;i++){
  Njets_vs_etaProbe_mtoff_Mean[i]->Draw("same");
 }
 d->cd(3);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
 Njets_vs_pt_ave_Mean[0]->SetTitle("");
 Njets_vs_pt_ave_Mean[0]->GetYaxis()->SetTitle("N_{jets}");
 Njets_vs_pt_ave_Mean[0]->GetYaxis()->SetRangeUser(0,20);
 for(int i=0;i<num_points;i++){
   Njets_vs_pt_ave_Mean[i]->Draw("same");
   Njets_vs_pt_ave_mtoff_Mean[i]->Draw("same");//DATA
 }
 d->cd(4);
 gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
 Njets_vs_pt_ave_mtoff_Mean[0]->SetTitle("");
 Njets_vs_pt_ave_mtoff_Mean[0]->GetYaxis()->SetRangeUser(0,20);
 Njets_vs_pt_ave_mtoff_Mean[0]->GetYaxis()->SetTitle("N_{jets}");
 for(int i=0;i<num_points;i++){
  Njets_vs_pt_ave_mtoff_Mean[i]->Draw("same");
 }


 d->Print(path+"plots/HIP_test__NjetsVsEta_"+titles_[0]+".pdf");

 //Draw profiles
 TCanvas* fpf = new TCanvas(); 
  fpf->Divide(2,2);
  fpf->cd(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
  mpf_vs_etaProbe_Profile[0]->SetTitle("MPF");
  mpf_vs_etaProbe_Profile[0]->GetYaxis()->SetRangeUser(0.5,1.25);
  mpf_vs_etaProbe_Profile[0]->GetYaxis()->SetTitle("Response");
  for(int i=0;i<num_points;i++){
    mpf_vs_etaProbe_Profile[i]->Draw("same");
    mpf_vs_etaProbe_mtoff_Profile[i]->Draw("same");//DATA
 }
 leg1->Draw();
 fpf->cd(3);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 r_rel_vs_etaProbe_Profile[0]->SetTitle("pT-balance");
 r_rel_vs_etaProbe_Profile[0]->GetYaxis()->SetRangeUser(0.5,1.25);
 r_rel_vs_etaProbe_Profile[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   r_rel_vs_etaProbe_Profile[i]->Draw("same");
   r_rel_vs_etaProbe_mtoff_Profile[i]->Draw("same");//DATA
 }

fpf->cd(2);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 mpf_vs_etaProbe_mtoff_Profile[0]->SetTitle("MPF");
 mpf_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetRangeUser(0.5,1.25);
 mpf_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   mpf_vs_etaProbe_mtoff_Profile[i]->Draw("same");
  }
 fpf->cd(4);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 r_rel_vs_etaProbe_mtoff_Profile[0]->SetTitle("pT-balance");
 r_rel_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetRangeUser(0.5,1.25);
 r_rel_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   r_rel_vs_etaProbe_mtoff_Profile[i]->Draw("same");
 }
 fpf->Print(path+"plots/HIP_test__ResponsesVsEta_Profile_"+titles_[0]+".pdf");

 TCanvas* dpf = new TCanvas();
 dpf->Divide(2,2);
 dpf->cd(1);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 Njets_vs_etaProbe_Profile[0]->SetTitle("");
 Njets_vs_etaProbe_Profile[0]->GetYaxis()->SetTitle("N_{jets}");
 Njets_vs_etaProbe_Profile[0]->GetYaxis()->SetRangeUser(0,20);
 for(int i=0;i<num_points;i++){
   Njets_vs_etaProbe_Profile[i]->Draw("same");
   Njets_vs_etaProbe_mtoff_Profile[i]->Draw("same");//DATA
 }
 leg1->Draw();
 dpf->cd(2);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 Njets_vs_etaProbe_mtoff_Profile[0]->SetTitle("");
 Njets_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetRangeUser(0,20);
 Njets_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetTitle("N_{jets}");
 for(int i=0;i<num_points;i++){
   Njets_vs_etaProbe_mtoff_Profile[i]->Draw("same");
 }
 dpf->cd(3);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 Njets_vs_pt_ave_Profile[0]->SetTitle("");
 Njets_vs_pt_ave_Profile[0]->GetYaxis()->SetTitle("N_{jets}");
 Njets_vs_pt_ave_Profile[0]->GetYaxis()->SetRangeUser(0,20);
 for(int i=0;i<num_points;i++){
   Njets_vs_pt_ave_Profile[i]->Draw("same");
   Njets_vs_pt_ave_mtoff_Profile[i]->Draw("same");//DATA
 }
 dpf->cd(4);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 Njets_vs_pt_ave_mtoff_Profile[0]->SetTitle("");
 Njets_vs_pt_ave_mtoff_Profile[0]->GetYaxis()->SetRangeUser(0,20);
 Njets_vs_pt_ave_mtoff_Profile[0]->GetYaxis()->SetTitle("N_{jets}");
 for(int i=0;i<num_points;i++){
  Njets_vs_pt_ave_mtoff_Profile[i]->Draw("same");
 }


 dpf->Print(path+"plots/HIP_test__NjetsVsEta_Profile_"+titles_[0]+".pdf");


 //In barrel part only
 TCanvas* fpf_br = new TCanvas(); 
  fpf_br->Divide(2,2);
  fpf_br->cd(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
  mpf_vs_etaProbe_Profile[0]->SetTitle("MPF");
  mpf_vs_etaProbe_Profile[0]->GetYaxis()->SetRangeUser(0.95,1.05);
  mpf_vs_etaProbe_Profile[0]->GetYaxis()->SetTitle("Response");
  for(int i=0;i<num_points;i++){
    mpf_vs_etaProbe_Profile[i]->Draw("same");
    mpf_vs_etaProbe_mtoff_Profile[i]->Draw("same");//DATA
 }
 leg1->Draw();
 fpf_br->cd(3);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 r_rel_vs_etaProbe_Profile[0]->SetTitle("pT-balance");
 r_rel_vs_etaProbe_Profile[0]->GetYaxis()->SetRangeUser(0.95,1.05);
 r_rel_vs_etaProbe_Profile[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   r_rel_vs_etaProbe_Profile[i]->Draw("same");
   r_rel_vs_etaProbe_mtoff_Profile[i]->Draw("same");//DATA
 }

fpf_br->cd(2);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 mpf_vs_etaProbe_mtoff_Profile[0]->SetTitle("MPF");
 mpf_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetRangeUser(0.95,1.05);
 mpf_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   mpf_vs_etaProbe_mtoff_Profile[i]->Draw("same");
  }
 fpf_br->cd(4);
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 gPad->Modified();
 r_rel_vs_etaProbe_mtoff_Profile[0]->SetTitle("pT-balance");
 r_rel_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetRangeUser(0.95,1.05);
 r_rel_vs_etaProbe_mtoff_Profile[0]->GetYaxis()->SetTitle("Response");
 for(int i=0;i<num_points;i++){
   r_rel_vs_etaProbe_mtoff_Profile[i]->Draw("same");
 }
 fpf_br->Print(path+"plots/HIP_test__ResponsesVsEta_Profile_zoomin_"+titles_[0]+".pdf");

}
