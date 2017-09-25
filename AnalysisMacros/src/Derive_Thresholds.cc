#include "../include/parameters.h"
#include "../include/useful_functions.h"
#include "../include/CorrectionObject.h"

#include <iostream>
#include <fstream>
#include <string> 

#include <TStyle.h>
#include <TF1.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TMatrixDSym.h>
#include <TPaveStats.h>
#include <TFitResult.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TVirtualFitter.h>
#include <TMath.h>
#include <TFile.h>
#include <TProfile.h>


using namespace std;

void CorrectionObject::Derive_Thresholds(bool pt1_check){
  cout << "--------------- Starting Derive_Thresholds() ---------------" << endl << endl;
  cout << "!!! THE WAY THE THRESHOLD WERE ESTIMATED HERE IS WRONG !!!" << endl << endl;
  CorrectionObject::make_path(CorrectionObject::_outpath+"plots/thresholds/");
  TStyle* m_gStyle = new TStyle();
  m_gStyle->SetOptFit(000);

  
  // fill the histos for pt average in bins of eta
  TH1D* ptave_data[n_trigger];
  TH1D* ptave_data_eff[n_trigger-1];  
  int countPt = 0;
  TString namehist = "ptave_";
  
  for(int i=0; i<n_trigger; i++){
    TString dirName = "HLT_PFJet";
    dirName += to_string(triggerVal[i]); 
    TString var1 = "pt_ave";
    if(pt1_check) var1="pt_1";

    TH1D* hist;
    
    cout << "looking for "<<dirName << endl;
    
    ptave_data[i] = (TH1D*) CorrectionObject::_DATAFile->Get(dirName+"/"+var1) ->Clone();
    ptave_data[i]->SetName(dirName);
    ptave_data[i]->Print();
    
    countPt++;

    if(i>0){
      ptave_data_eff[i-1] = (TH1D*) ptave_data[i]->Clone();
      ptave_data_eff[i-1]->Add((TH1D*)ptave_data[i-1]);
      ptave_data_eff[i-1]->Divide(ptave_data[i-1]);
      ptave_data_eff[i-1]->Rebin(6);
      ptave_data_eff[i-1]->SaveAs(CorrectionObject::_outpath+"plots/thresholds/"+"HLT_PFJet"+to_string(triggerVal[i])+".root");
    }

  }

  cout << "fit the thresholds" << endl << endl;

  TF1 *func[n_trigger-1];
  double thresholds[n_trigger-1];
  double thresholds09[n_trigger-1];
  double thresholds_err[n_trigger-1];
  double thresholds09_err[n_trigger-1];
  double thresholds_errUp[n_trigger-1];
  double thresholds09_errUp[n_trigger-1];
  double thresholds_errDown[n_trigger-1];
  double thresholds09_errDown[n_trigger-1];
  double fitrange_up[n_trigger-1] = {50, 50, 50, 60, 60, 70 , 90, 60, 80};
  double fitrange_down[n_trigger-1] = {-10, -10, -30, -30, -30, -30 , -30, -10, 0}; 
  for(int i=0; i<n_trigger-1; i++){
    TString fitname = "fit";
    fitname +=  to_string(triggerVal[i+1]); 
    func[i] = new TF1(fitname,SmoothFit,triggerVal[i]-fitrange_down[i],
		      triggerVal[i+1]+fitrange_up[i],3);
    func[i]->SetParameters(triggerVal[i+1], 40., 1.);
    func[i]->SetParNames("p0", "p1", "N");
    ptave_data_eff[i]->Fit(func[i],"R");

    thresholds[i] = func[i]->GetX(0.95*func[i]->GetParameter(2), triggerVal[i+1]-10, 800);
    thresholds09[i] = func[i]->GetX(0.9*func[i]->GetParameter(2), triggerVal[i+1]-10, 800);
 
    cout<< std::fixed << std::setprecision(2) << "Trigger value: "<< triggerVal[i+1] << "; 0.95 threshold: "<< thresholds[i]  << endl;;
    cout<< std::fixed << std::setprecision(2) << "Trigger value: "<< triggerVal[i+1] << "; 0.90 threshold: "<< thresholds09[i]  << endl;
    cout << "Old Threshold: " << pt_bins[i+1] <<endl <<endl;
  }

  
  const double triggerVal_noLow[n_trigger-1] = {60, 80, 140, 200, 260, 320, 400, 450, 500};
  cout << "extrapolate the threshold of the lowest trigger" << endl << endl;
  
    
  TGraphErrors* gr095 = new TGraphErrors(n_trigger-1, triggerVal_noLow  ,thresholds);
  TF1* func095 = new TF1("func095", "pol1" , 0, 501);
  func095->SetLineColor(kBlue);
  TFitResultPtr r = gr095->Fit(func095);
  double thr40 = gr095->Eval(40);
  // double x[1] = { thr40 };
  // double err[1];
  // r->GetConfidenceIntervals(1, 1, 1, x, err, 0.683, false);
  // double thr40_err = err[0];
  
  TGraphErrors* gr09 = new TGraphErrors(n_trigger-1, triggerVal_noLow ,thresholds09);
  TF1* func09 = new TF1("func09", "pol1" , 0, 501);
  r = gr09->Fit(func09);  
  double thr40_09 = gr09->Eval(40);
  // x[1] = { thr40_09 };
  // r->GetConfidenceIntervals(1, 1, 1, x, err, 0.683, false);
  // double thr40_09_err = err[0];

    cout<< std::fixed << std::setprecision(2) << "Trigger value: "<< triggerVal[0] << "; 0.95 threshold: "<< thr40 << endl;;
    cout<< std::fixed << std::setprecision(2) << "Trigger value: "<< triggerVal[0] << "; 0.90 threshold: "<< thr40_09  << endl;
    cout << "Old Threshold: " << pt_bins[0] <<endl <<endl;
  
    
  cout << "Draw plots to "<<CorrectionObject::_outpath+"plots/thresholds" << endl;

  ofstream myfile;
  myfile.open (CorrectionObject::_outpath+"plots/thresholds/"+"/thresholds.txt",ios::trunc);
  myfile << "trigger  old  \t  0.90 \t  0.95  \n";
  myfile<< std::fixed << std::setprecision(2) << triggerVal[0]<< " \t " << pt_bins[0]<< " \t "<< thr40_09  << " \t "<< thr40   << " \n";
  for(int i=0; i<n_trigger-1; i++){
    myfile<< std::fixed << std::setprecision(2) << triggerVal[i+1]<< " \t " << pt_bins[i+1]<< " \t "<< thresholds09[i]<< " \t "<< thresholds[i] << " \n"; 
  }
  myfile.close();

  TCanvas* c = new TCanvas("c");
  // TMultiGraph* mg = new TMultiGraph();
  // mg->Add(gr09);
  // mg->Add(gr095);
  // mg->Draw();
  gr09->SetMarkerStyle(3);
  gr09->Draw("ap");
  c->Print(CorrectionObject::_outpath+"plots/thresholds/"+"extrapolateLowestTrigger09"+(pt1_check ? "pt1":"")+".eps","eps");    
   TCanvas* c2 = new TCanvas("c2");
   gr09->SetMarkerStyle(3);
   gr095->SetMarkerStyle(5);
  TMultiGraph* mg = new TMultiGraph();
  mg->Add(gr09);
  mg->Add(gr095);
  mg->Draw("ap");
  mg->GetHistogram()->GetXaxis()->SetRangeUser(0.,600.);
  mg->Draw("ap");  
  // gr095->Draw("ap");
  c2->Print(CorrectionObject::_outpath+"plots/thresholds/"+"extrapolateLowestTrigger"+(pt1_check ? "pt1":"")+".eps","eps");



  
  for(int i=0; i<n_trigger-1; i++){
      TCanvas* c1 = new TCanvas("c1");
      ptave_data_eff[i]->Draw();
      TLine *line = new TLine(thresholds[i],0,thresholds[i],
			      1.05*func[i]->GetParameter(2));
      line->SetLineColor(kBlack);
      line->Draw();
       TLine *line09 = new TLine(thresholds09[i],0,thresholds09[i],
				 1.05*func[i]->GetParameter(2));
      line09->SetLineColor(kBlack);
      line09->SetLineStyle(2);
      line09->Draw();     
      c1->Print(CorrectionObject::_outpath+"plots/thresholds/"+"HLT_PFJet"+to_string(triggerVal[i+1])+(pt1_check ? "pt1":"")+".eps","eps");

  }
    
    
  
}
