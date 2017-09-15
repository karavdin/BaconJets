#include "../include/parameters.h"
#include "../include/useful_functions.h"
#include "../include/CorrectionObject.h"
#include "../include/tdrstyle_mod15.h"

#include <TStyle.h>
#include <TF1.h>
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


using namespace std;

void CorrectionObject::AdditionalAsymmetryPlots(){
  cout << "--------------- Starting FinalControlPlots_CorrectFormulae() ---------------" << endl << endl;
  gStyle->SetOptStat(0);

  CorrectionObject::make_path(CorrectionObject::_outpath+"plots/control/fullAsym/");

  //Table with number of events in each pT- and eta-bin
  
  //Set up histos for ratios of responses
  TH1D *hdata_asymmetry[n_pt-1][n_eta-1]; // A for data

  int count = 0;
  TString name1 = "hist_data_A_";
 
  for(int j=0; j<n_eta-1; j++){
      TString eta_name = "eta_"+eta_range2[j]+"_"+eta_range2[j+1];
    for(int k=0; k<n_pt-1; k++){
      TString pt_name = "pt_"+pt_range[k]+"_"+pt_range[k+1];

      TString name = name1 + eta_name + "_" + pt_name; 
      hdata_asymmetry[k][j] = new TH1D(name,"",3*nResponseBins, -1.2, 1.2);
    
      count++;
    }
  }


  //Get relevant information from DATA, loop over DATA events
  TTreeReader myReader_DATA("AnalysisTree", CorrectionObject::_DATAFile);
  TTreeReaderValue<Float_t> pt_ave_data(myReader_DATA, "pt_ave");
  TTreeReaderValue<Float_t> alpha_data(myReader_DATA, "alpha");
  TTreeReaderValue<Float_t> asymmetry_data(myReader_DATA, "asymmetry");
  TTreeReaderValue<Float_t> probejet_eta_data(myReader_DATA, "probejet_eta");
  TTreeReaderValue<Float_t> probejet_pt_data(myReader_DATA, "probejet_pt");
  TTreeReaderValue<Float_t> weight_data(myReader_DATA, "weight");
  
  int myCount = 0;
  int myCount_cut = 0;
  while (myReader_DATA.Next()) {
    if(*alpha_data>alpha_cut){
      myCount_cut++;
      continue;
    }
    //fill histos in bins of pt and eta
    for(int k=0; k<n_pt-1; k++){
      if(*pt_ave_data<pt_bins[k] || *pt_ave_data>pt_bins[k+1]) continue;
      for(int j=0; j<n_eta-1; j++){
	if(fabs(*probejet_eta_data)>eta_bins[j+1] || fabs(*probejet_eta_data)<eta_bins[j]) continue;
	else{
	  hdata_asymmetry[k][j]->Fill(*asymmetry_data,*weight_data);
	}
      }
    }
  }

  //DEBUG
  std::cout<<"\ncount data "<<myCount<<"  count cut data "<<myCount_cut<<std::endl<<std::endl;

  TFile* test_out_data_A = new TFile(CorrectionObject::_outpath+"plots/control/A_1d_data_smaller_split"+".root","RECREATE");
  for(int j=0; j<n_eta-1; j++){
    for(int k=0; k<n_pt-1; k++){
      hdata_asymmetry[k][j]->Write();
    }
  }
  test_out_data_A->Close();
  delete test_out_data_A;




  //R_MC and R_DATA overlaid in the same plot as a function of pT, in bins of |eta|
  double val_rel_mc[n_eta-1][n_pt-1]; //value at pt,eta
  double err_rel_mc[n_eta-1][n_pt-1]; //error of ratio at pt,eta
  double val_mpf_mc[n_eta-1][n_pt-1]; //ratio at pt,eta
  double err_mpf_mc[n_eta-1][n_pt-1]; //error of ratio at pt,eta
  double val_rel_data[n_eta-1][n_pt-1]; //value at pt,eta
  double err_rel_data[n_eta-1][n_pt-1]; //error of ratio at pt,eta
  double val_mpf_data[n_eta-1][n_pt-1]; //ratio at pt,eta
  double err_mpf_data[n_eta-1][n_pt-1]; //error of ratio at pt,eta

  for(int i=0; i<n_eta-1; i++){
    for(int j=0; j<n_pt-1; j++){

      //get <A> and error on <A>
      pair <double,double> A_data = GetValueAndError(hdata_asymmetry[j][i]);
      //build MPF and pt_bal and their errors

    }
  }

  //dummy for tdrCanvas
  TH1D *h = new TH1D("h",";dummy;",41,0,5.191);
  h->SetMaximum(1.2);
  h->SetMinimum(0.8);

  TH1D *hEF = new TH1D("hEF",";dummy;",1000,0,5.191);

  TCanvas* c_0 = new TCanvas();
  tdrCanvas(c_0,"c_0",h,4,10,true,CorrectionObject::_lumitag);

  
  for(int i=0; i<n_eta-1; i++){
    //Create and fill TGraphErrors
    double xbin_tgraph[n_pt-1];
    double zero[n_pt-1];
    for(int i=0;i<n_pt-1;i++){
      xbin_tgraph[i]=(pt_bins[i]+pt_bins[i+1])/2;
      zero[i]=(pt_bins[i+1]-pt_bins[i])/2 ;
    }

    TString alVal;
    alVal.Form("%0.2f\n",alpha_cut);
    TString altitle = "{#alpha<"+alVal+"}";
    TString axistitle_mc = "R^{MC}_";
    TString axistitle_data = "R^{DATA}_";
 
     axistitle_data += altitle;

    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 

  }


  //********************************************************************  Plot all Control Hists ********************************************************************************

  //Plot 1d response distributions in a particular eta-bin for different pt-bins onto a single canvas

  //Get histo files
 
  TFile* f_rel_data = new TFile(CorrectionObject::_outpath+"plots/control/A_1d_data_smaller_split"+".root","READ");
  for(int i=0; i<n_eta-1; i++){
    TString eta_name = "eta_"+eta_range2[i]+"_"+eta_range2[i+1];
    
    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 
    TString text = eta_range[i] + " < |#eta| < " + eta_range[i+1];

    TLatex *tex_lumi = new TLatex();
    tex_lumi->SetNDC();
    tex_lumi->SetTextSize(0.045); 
    
    for(int j=0; j<n_pt-1; j++){
      TCanvas* cFullA = new TCanvas();
      tdrCanvas(cFullA,"cFullA",h,4,10,kSquare,CorrectionObject::_lumitag);
      TH1D* htemp_rel_data;
      TString pt_name = "pt_"+pt_range[j]+"_"+pt_range[j+1];
      TString legname = "p_{T} #in [" + pt_range[j] + "," + pt_range[j+1] + "]";
      TString name_rel_data = "hist_data_A_"+eta_name+"_"+pt_name;
      htemp_rel_data = (TH1D*)f_rel_data->Get(name_rel_data);
      htemp_rel_data->Draw("E");
      htemp_rel_data->GetXaxis()->SetTitle("A");
      htemp_rel_data->GetYaxis()->SetTitle("Entries per Bin");
      htemp_rel_data->GetYaxis()->SetTitleOffset(1.5);
      htemp_rel_data->GetXaxis()->SetLimits(-1.2,1.2);
      htemp_rel_data->Draw("E");		
      tex->DrawLatex(0.47,0.85,"Data, " + text);
      tex->DrawLatex(0.54,0.8,legname);		
      cFullA->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/A_DATA_" + CorrectionObject::_generator_tag + "_eta_" + eta_range2[i] + "_" + eta_range2[i+1]+"_pt_"+ pt_range[j] + "_" + pt_range[j+1] + ".pdf");
      delete cFullA;
      delete htemp_rel_data;
    }
  }

}
    
    


