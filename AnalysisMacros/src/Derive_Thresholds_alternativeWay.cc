#include "../include/parameters.h"
#include "../include/useful_functions.h"
#include "../include/CorrectionObject.h"
#include "../include/tdrstyle_mod15.h"

#include <TStyle.h>
#include <TF1.h>
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

void CorrectionObject::Derive_Thresholds_alternativeWay(){
  cout << "--------------- Starting Derive_Thresholds_alternativeWay() ---------------" << endl << endl;
  gStyle->SetOptStat(0);

  bool pt1_check = false;
  
  CorrectionObject::make_path(CorrectionObject::_outpath+"plots/thresholds/");

  int trg_nr=n_trigger;
  
  TH1D *hdata_pt_ave[trg_nr-1];
  TH1D *hdata_pt_ave_wNext[trg_nr-1];

  for(int j=0; j<trg_nr-1; j++){
    TString name = "pt_ave_trg"+to_string(triggerVal[j]);
    TString name2 = "pt_ave_wNext_trg"+to_string(triggerVal[j]);

    hdata_pt_ave[j]= new TH1D(name,"",nResponseBins*6,0,j<7?600:1200);
    hdata_pt_ave_wNext[j]= new TH1D(name2,"",nResponseBins*6,0,j<7?600:1200);
  }
  

  //Get relevant information from DATA, loop over DATA events
  TTreeReader myReader_DATA("AnalysisTree", CorrectionObject::_DATAFile);
  TTreeReaderValue<int> trg40(myReader_DATA, "trigger40");
  TTreeReaderValue<int> trg60(myReader_DATA, "trigger60");
  TTreeReaderValue<int> trg80(myReader_DATA, "trigger80");
  TTreeReaderValue<int> trg140(myReader_DATA, "trigger140");
  TTreeReaderValue<int> trg200(myReader_DATA, "trigger200");
  TTreeReaderValue<int> trg260(myReader_DATA, "trigger260");
  TTreeReaderValue<int> trg320(myReader_DATA, "trigger320");
  TTreeReaderValue<int> trg400(myReader_DATA, "trigger400");
  TTreeReaderValue<int> trg450(myReader_DATA, "trigger450");
  TTreeReaderValue<int> trg500(myReader_DATA, "trigger500");
  TTreeReaderValue<Float_t> pt_ave_data(myReader_DATA, "pt_ave");
  TTreeReaderValue<Float_t> weight_data(myReader_DATA, "weight");

  TTreeReaderValue<int> trg_arr[trg_nr] = {trg40,trg60,trg80,trg140,trg200,trg260,trg320,trg400,trg450,trg500};
  
  int myCount = 0;
  int myCount_notX = 0;
  bool allExclusive = true;
  while (myReader_DATA.Next()) {
    bool exclusive = true;
    exclusive = (*trg40)^(*trg60)^(*trg80)^(*trg140)^(*trg200)^(*trg260)^(*trg320)^(*trg400)^(*trg450)^(*trg500);
    for(int j=0; j<trg_nr-1; j++){
       if(*(trg_arr[j])) hdata_pt_ave[j]->Fill(*pt_ave_data);
       if((*(trg_arr[j]))&&(*(trg_arr[j+1]))) hdata_pt_ave_wNext[j]->Fill(*pt_ave_data);
    }
    myCount++;
    if(!exclusive){
      myCount_notX++;
    }
  }

  std::cout<<"\ncount data "<<myCount<<"  count data trg not exclusive "<<myCount_notX<<std::endl;
  
  TH1D* ptave_data_eff[n_trigger-1];
  for(int j=0; j<trg_nr-1; j++){
    hdata_pt_ave_wNext[j]->SaveAs(CorrectionObject::_outpath+"plots/thresholds/"+"HLT_PFJet"+to_string(triggerVal[j])+"_pt_ave_wNext"+".root");
    hdata_pt_ave[j]->SaveAs(CorrectionObject::_outpath+"plots/thresholds/"+"HLT_PFJet"+to_string(triggerVal[j])+"_pt_ave"+".root");
    
    ptave_data_eff[j]= (TH1D*) hdata_pt_ave_wNext[j]->Clone();
    ptave_data_eff[j]->Divide((TH1D*) hdata_pt_ave[j]->Clone());
    ptave_data_eff[j]->Rebin(6);
    ptave_data_eff[j]->SaveAs(CorrectionObject::_outpath+"plots/thresholds/"+"HLT_PFJet"+to_string(triggerVal[j+1])+".root");
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
  // double fitrange_up[n_trigger-1] = {50, 50, 50, 60, 60, 70 , 90, 60, 80};
  // double fitrange_down[n_trigger-1] = {-10, -10, -30, -30, -30, -30 , -30, -10, 0}; 
  for(int i=0; i<n_trigger-1; i++){
    TString fitname = "fit";
    fitname +=  to_string(triggerVal[i+1]); 
    func[i] = new TF1(fitname,SmoothFit,triggerVal[i]-20,
		      triggerVal[i+1]+200,3);
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
  // TFitResultPtr r = gr095->Fit(func095);
  double thr40 = gr095->Eval(40);
  // double x[1] = { thr40 };
  // double err[1];
  // r->GetConfidenceIntervals(1, 1, 1, x, err, 0.683, false);
  // double thr40_err = err[0];
  
  TGraphErrors* gr09 = new TGraphErrors(n_trigger-1, triggerVal_noLow ,thresholds09);
  TF1* func09 = new TF1("func09", "pol1" , 0, 501);
  // r = gr09->Fit(func09);  
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
  c->Print(CorrectionObject::_outpath+"plots/thresholds/"+"extrapolateLowestTrigger09"+(pt1_check ? "pt1":"")+".pdf","pdf");    
   TCanvas* c2 = new TCanvas("c2");
   gr09->SetMarkerStyle(3);
   gr095->SetMarkerStyle(5);
  TMultiGraph* mg = new TMultiGraph();
  mg->Add(gr09);
  mg->Add(gr095);
  mg->Draw("ap");
  // mg->GetHistogram()->GetXaxis()->SetRangeUser(0.,600.);
  mg->Draw("ap");  
  // gr095->Draw("ap");
  c2->Print(CorrectionObject::_outpath+"plots/thresholds/"+"extrapolateLowestTrigger"+(pt1_check ? "pt1":"")+".pdf","pdf");



  
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
      c1->Print(CorrectionObject::_outpath+"plots/thresholds/"+"HLT_PFJet"+to_string(triggerVal[i+1])+(pt1_check ? "pt1":"")+".pdf","pdf");

  }
    

}
    
    


