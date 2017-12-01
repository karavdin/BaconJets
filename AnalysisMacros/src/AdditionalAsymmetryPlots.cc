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
#include <TH2D.h>

using namespace std;

void CorrectionObject::AdditionalAsymmetryPlots(bool eta_abs){
  cout << "--------------- StartingAdditionalAsymmetryPlots() ---------------" << endl << endl;
  gStyle->SetOptStat(0);

  CorrectionObject::make_path(CorrectionObject::_outpath+"plots/control/fullAsym/");

  //Table with number of events in each pT- and eta-bin

  TH1D *hdata_asymmetry[n_pt-1][(eta_abs ? n_eta : n_eta_full)  -1]; // A for data
  TH2D *hdata_asymmetry_nvert[n_pt-1][(eta_abs ? n_eta : n_eta_full)-1]; // A for data
  TH2D *hdata_asymmetry_rho[n_pt-1][(eta_abs ? n_eta : n_eta_full)-1]; // A for data

  TH1D *hdata_jet1_pt[(eta_abs ? n_eta : n_eta_full)-1];
  TH1D *hdata_jet2_pt[(eta_abs ? n_eta : n_eta_full)-1];  
  TH1D *hdata_jet3_pt[(eta_abs ? n_eta : n_eta_full)-1];
  
  int count = 0;
  TString name1 = "hist_data_A_";
  TString name2 = "hist_data_";
 
  for(int j=0; j<(eta_abs ? n_eta : n_eta_full)-1; j++){
      TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[j]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[j+1];

      hdata_jet1_pt[j] = new TH1D(name2+"jet1_pt_"+eta_name,"",nResponseBins,0,600);
      hdata_jet2_pt[j] = new TH1D(name2+"jet2_pt_"+eta_name,"",nResponseBins,0,600);    
      hdata_jet3_pt[j] = new TH1D(name2+"jet3_pt_"+eta_name,"",nResponseBins,0,600);
      
    for(int k=0; k<n_pt-1; k++){
      TString pt_name = "pt_"+pt_range[k]+"_"+pt_range[k+1];

      TString name = name1 + eta_name + "_" + pt_name; 
      hdata_asymmetry[k][j] = new TH1D(name,"",3*nResponseBins, -1.2, 1.2);
      name = name1+"nvert_" + eta_name + "_" + pt_name;      
      hdata_asymmetry_nvert[k][j] = new TH2D(name,"",nResponseBins/2, -1.2, 1.2,nResponseBins/10 ,0,60);
      name = name1+"rho_" + eta_name + "_" + pt_name;    
      hdata_asymmetry_rho[k][j] = new TH2D(name,"",nResponseBins/2, -1.2, 1.2,nResponseBins/10 ,0,60);
    
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
  
  TTreeReaderValue<int> nvertices_data(myReader_DATA, "nvertices");
  TTreeReaderValue<Float_t> rho_data(myReader_DATA, "rho");
  
  TTreeReaderValue<Float_t> jet1_pt_data(myReader_DATA, "jet1_pt");
  TTreeReaderValue<Float_t> jet2_pt_data(myReader_DATA, "jet2_pt");
  TTreeReaderValue<Float_t> jet3_pt_data(myReader_DATA, "jet3_pt");
    
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
      for(int j=0; j<(eta_abs ? n_eta : n_eta_full)-1; j++){
	if( (eta_abs ? fabs(*probejet_eta_data) : *probejet_eta_data) > (eta_abs ? eta_bins : eta_bins_full)[j+1] || (eta_abs ? fabs(*probejet_eta_data) : *probejet_eta_data)  < (eta_abs ? eta_bins : eta_bins_full)[j]) continue;
	else{
	  hdata_jet1_pt[j]->Fill(fabs(*jet1_pt_data),*weight_data);
	  hdata_jet2_pt[j]->Fill(fabs(*jet2_pt_data),*weight_data);
	  hdata_jet3_pt[j]->Fill(fabs(*jet3_pt_data),*weight_data);	  
	  hdata_asymmetry[k][j]->Fill(*asymmetry_data,*weight_data);
	  hdata_asymmetry_rho[k][j]->Fill(*asymmetry_data,*rho_data,*weight_data);
	  hdata_asymmetry_nvert[k][j]->Fill(*asymmetry_data,*nvertices_data,*weight_data);
	  myCount++;
	}
      }
    }
  }

  //DEBUG
  std::cout<<"\ncount data "<<myCount<<"  count cut data "<<myCount_cut<<std::endl<<std::endl;

  TFile* test_out_data_A = new TFile(CorrectionObject::_outpath+"plots/control/A_1d_data_smaller_split.root","RECREATE");
  for(int j=0; j<(eta_abs ? n_eta : n_eta_full)-1; j++){
    for(int k=0; k<n_pt-1; k++){
      hdata_asymmetry[k][j]->Write();
    }
  }
  test_out_data_A->Close();
  delete test_out_data_A;

  TFile* test_out_data_A_rho = new TFile(CorrectionObject::_outpath+"plots/control/A_rho_2d_data.root","RECREATE");
  for(int j=0; j<(eta_abs ? n_eta : n_eta_full)-1; j++){
    for(int k=0; k<n_pt-1; k++){
      hdata_asymmetry_rho[k][j]->Write();
    }
  }
  test_out_data_A_rho->Close();
  delete test_out_data_A_rho;
  

  TFile* test_out_data_A_nvert = new TFile(CorrectionObject::_outpath+"plots/control/A_nvert_2d_data.root","RECREATE");
  for(int j=0; j<(eta_abs ? n_eta : n_eta_full)-1; j++){
    for(int k=0; k<n_pt-1; k++){
      hdata_asymmetry_nvert[k][j]->Write();
    }
  }
  test_out_data_A_nvert->Close();
  delete test_out_data_A_nvert;

    TFile* test_out_data_jet_pt = new TFile(CorrectionObject::_outpath+"plots/control/jet_pt_data.root","RECREATE");
  for(int j=0; j<(eta_abs ? n_eta : n_eta_full)-1; j++){
      hdata_jet1_pt[j]->Write();
      hdata_jet2_pt[j]->Write();
      hdata_jet3_pt[j]->Write();     
  }
  test_out_data_jet_pt->Close();
  delete test_out_data_jet_pt;
  


  //R_MC and R_DATA overlaid in the same plot as a function of pT, in bins of |eta|
  double val_rel_mc[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //value at pt,eta
  double err_rel_mc[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //error of ratio at pt,eta
  double val_mpf_mc[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //ratio at pt,eta
  double err_mpf_mc[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //error of ratio at pt,eta
  double val_rel_data[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //value at pt,eta
  double err_rel_data[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //error of ratio at pt,eta
  double val_mpf_data[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //ratio at pt,eta
  double err_mpf_data[(eta_abs ? n_eta : n_eta_full)-1][n_pt-1]; //error of ratio at pt,eta

  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
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

  
  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
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

  //Get histo files
 

  TFile* f_jet_pt = new TFile(CorrectionObject::_outpath+"plots/control/jet_pt_data.root","READ");
  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
    TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[i]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[i+1];
    
    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 
    TString text = eta_range[i] + " < |#eta| < " + eta_range[i+1];

    TLatex *tex_lumi = new TLatex();
    tex_lumi->SetNDC();
    tex_lumi->SetTextSize(0.045); 
    
      TCanvas* cFull_pt1 = new TCanvas();
      tdrCanvas(cFull_pt1,"cFull_pt1",h,4,10,kSquare,CorrectionObject::_lumitag);
      TH1D* htemp_rel_data;
      TString name_rel_data = "hist_data_jet1_pt_"+eta_name;
      htemp_rel_data = (TH1D*)f_jet_pt->Get(name_rel_data);
      htemp_rel_data->Draw();
      htemp_rel_data->GetXaxis()->SetTitle("pt jet1");
      htemp_rel_data->GetYaxis()->SetTitle("Entries per Bin");      
      // htemp_rel_data->GetXaxis()->SetLimits(-1.2,1.2);
      htemp_rel_data->Draw("EP");		
      tex->DrawLatex(0.47,0.85,"Data, " + text);
      cFull_pt1->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/jet1_pt_DATA_" + CorrectionObject::_generator_tag + "_eta_" + (eta_abs ? eta_range2 : eta_range2_full)[i] + "_" + (eta_abs ? eta_range2 : eta_range2_full)[i+1]+ ".pdf");
      delete cFull_pt1;
      delete htemp_rel_data;
    
  }

  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
    TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[i]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[i+1];
    
    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 
    TString text = eta_range[i] + " < |#eta| < " + eta_range[i+1];

    TLatex *tex_lumi = new TLatex();
    tex_lumi->SetNDC();
    tex_lumi->SetTextSize(0.045); 
    
      TCanvas* cFull_pt2 = new TCanvas();
      tdrCanvas(cFull_pt2,"cFull_pt2",h,4,10,kSquare,CorrectionObject::_lumitag);
      TH1D* htemp_rel_data;
      TString name_rel_data = "hist_data_jet2_pt_"+eta_name;
      htemp_rel_data = (TH1D*)f_jet_pt->Get(name_rel_data);
      htemp_rel_data->Draw();
      htemp_rel_data->GetXaxis()->SetTitle("pt jet2");
      htemp_rel_data->GetYaxis()->SetTitle("Entries per Bin");      
      // htemp_rel_data->GetXaxis()->SetLimits(-1.2,1.2);
      htemp_rel_data->Draw("EP");		
      tex->DrawLatex(0.47,0.85,"Data, " + text);
      cFull_pt2->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/jet2_pt_DATA_" + CorrectionObject::_generator_tag + "_eta_" + (eta_abs ? eta_range2 : eta_range2_full)[i] + "_" + (eta_abs ? eta_range2 : eta_range2_full)[i+1]+ ".pdf");
      delete cFull_pt2;
      delete htemp_rel_data;
    
  }

  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
    TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[i]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[i+1];
    
    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 
    TString text = eta_range[i] + " < |#eta| < " + eta_range[i+1];

    TLatex *tex_lumi = new TLatex();
    tex_lumi->SetNDC();
    tex_lumi->SetTextSize(0.045); 
    
      TCanvas* cFull_pt3 = new TCanvas();
      tdrCanvas(cFull_pt3,"cFull_pt3",h,4,10,kSquare,CorrectionObject::_lumitag);
      TH1D* htemp_rel_data;
      TString name_rel_data = "hist_data_jet3_pt_"+eta_name;
      htemp_rel_data = (TH1D*)f_jet_pt->Get(name_rel_data);
      htemp_rel_data->Draw();
      htemp_rel_data->GetXaxis()->SetTitle("pt jet3");
      htemp_rel_data->GetYaxis()->SetTitle("Entries per Bin");      
      // htemp_rel_data->GetXaxis()->SetLimits(-1.2,1.2);
      htemp_rel_data->Draw("EP");		
      tex->DrawLatex(0.47,0.85,"Data, " + text);
      cFull_pt3->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/jet3_pt_DATA_" + CorrectionObject::_generator_tag + "_eta_" + (eta_abs ? eta_range2 : eta_range2_full)[i] + "_" + (eta_abs ? eta_range2 : eta_range2_full)[i+1]+ ".pdf");
      delete cFull_pt3;
      delete htemp_rel_data;
    
  }  
  

   TFile* f_rel_data_nvert = new TFile(CorrectionObject::_outpath+"plots/control/A_nvert_2d_data.root","READ");
  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
    TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[i]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[i+1];
    
    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 
    TString text = eta_range[i] + " < |#eta| < " + eta_range[i+1];

    TLatex *tex_lumi = new TLatex();
    tex_lumi->SetNDC();
    tex_lumi->SetTextSize(0.045); 
    
    for(int j=0; j<n_pt-1; j++){
      TCanvas* cFullA_nvert = new TCanvas();
      // tdrCanvas(cFullA_nvert,"cFullA_nvert",h,4,10,kSquare,CorrectionObject::_lumitag);
      TH2D* htemp_rel_data_nvert;
      TString pt_name = "pt_"+pt_range[j]+"_"+pt_range[j+1];
      TString legname = "p_{T} #in [" + pt_range[j] + "," + pt_range[j+1] + "]";
      TString name_rel_data = "hist_data_A_nvert_"+eta_name+"_"+pt_name;
      htemp_rel_data_nvert = (TH2D*)f_rel_data_nvert->Get(name_rel_data);
      htemp_rel_data_nvert->Draw("E");
      htemp_rel_data_nvert->GetXaxis()->SetTitle("A");
      htemp_rel_data_nvert->GetYaxis()->SetTitle("n vertices");
      htemp_rel_data_nvert->GetZaxis()->SetTitle("Entries per Bin");      
      htemp_rel_data_nvert->GetXaxis()->SetLimits(-1.2,1.2);
      htemp_rel_data_nvert->Draw("COLZ");		
      tex->DrawLatex(0.47,0.85,"Data, " + text);
      tex->DrawLatex(0.54,0.8,legname);		
      cFullA_nvert->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/A_nvert_DATA_" + CorrectionObject::_generator_tag + "_eta_" + (eta_abs ? eta_range2 : eta_range2_full)[i] + "_" + (eta_abs ? eta_range2 : eta_range2_full)[i+1]+"_pt_"+ pt_range[j] + "_" + pt_range[j+1] + ".pdf");
      delete cFullA_nvert;
      delete htemp_rel_data_nvert;
    }
  }
 
  TFile* f_rel_data = new TFile(CorrectionObject::_outpath+"plots/control/A_1d_data_smaller_split"+".root","READ");
  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
    TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[i]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[i+1];
    
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
      cFullA->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/A_DATA_" + CorrectionObject::_generator_tag + "_eta_" + (eta_abs ? eta_range2 : eta_range2_full)[i] + "_" + (eta_abs ? eta_range2 : eta_range2_full)[i+1]+"_pt_"+ pt_range[j] + "_" + pt_range[j+1] + ".pdf");
      delete cFullA;
      delete htemp_rel_data;
    }
  }

  TFile* f_rel_data_rho = new TFile(CorrectionObject::_outpath+"plots/control/A_rho_2d_data.root","READ");
  cout<<"Read rho root file"<<endl;
  for(int i=0; i<(eta_abs ? n_eta : n_eta_full)-1; i++){
    TString eta_name = "eta_"+(eta_abs ? eta_range2 : eta_range2_full)[i]+"_"+(eta_abs ? eta_range2 : eta_range2_full)[i+1];
    
    TLatex *tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSize(0.045); 
    TString text = eta_range[i] + " < |#eta| < " + eta_range[i+1];

    TLatex *tex_lumi = new TLatex();
    tex_lumi->SetNDC();
    tex_lumi->SetTextSize(0.045); 
    
    for(int j=0; j<n_pt-1; j++){
      TCanvas* cFullA_rho = new TCanvas();
      // tdrCanvas(cFullA_rho,"cFullA_rho",h,4,10,kSquare,CorrectionObject::_lumitag);
      TH2D* htemp_rel_data_rho;
      TString pt_name = "pt_"+pt_range[j]+"_"+pt_range[j+1];
      TString legname = "p_{T} #in [" + pt_range[j] + "," + pt_range[j+1] + "]";
      TString name_rel_data = "hist_data_A_rho_"+eta_name+"_"+pt_name;
      htemp_rel_data_rho = (TH2D*)f_rel_data_rho->Get(name_rel_data);
      htemp_rel_data_rho->Draw("E");
      htemp_rel_data_rho->GetXaxis()->SetTitle("A");
      htemp_rel_data_rho->GetYaxis()->SetTitle("rho");
      htemp_rel_data_rho->GetZaxis()->SetTitle("Entries per Bin");      
      htemp_rel_data_rho->GetXaxis()->SetLimits(-1.2,1.2);
      htemp_rel_data_rho->Draw("COLZ");		
      tex->DrawLatex(0.47,0.85,"Data, " + text);
      tex->DrawLatex(0.54,0.8,legname);		
      cFullA_rho->SaveAs(CorrectionObject::_outpath+"plots/control/fullAsym/A_rho_DATA_" + CorrectionObject::_generator_tag + "_eta_" + (eta_abs ? eta_range2 : eta_range2_full)[i] + "_" + (eta_abs ? eta_range2 : eta_range2_full)[i+1]+"_pt_"+ pt_range[j] + "_" + pt_range[j+1] + ".pdf");
      delete cFullA_rho;
      delete htemp_rel_data_rho;
    }
  }
  

}
    
    


