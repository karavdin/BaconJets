
// with this script kFSR extrapolations over alpha in bins of eta will be calculated

TString ToString(int num) {
  ostringstream start;
  start<<num;
  TString start1=start.str();
  return start1;
}

void kFSR(){

  gStyle->SetOptFit();

  // input DATA file
  TFile* datafile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/uhh2.AnalysisModuleRunner.DATA.DATA_25ns_DConly_MCcorrected_v2.root","READ"); 
  // input MC file
  TFile* MCfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/uhh2.AnalysisModuleRunner.MC.MC_QCDpt15to7000_13TeV_25ns_MCcorrV2.root","READ");
  
  /*
  // input DATA file
  TFile* datafile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/40pb/uhh2.AnalysisModuleRunner.DATA.DATA_golden_JSON_40pb_morebins.root","READ"); 
  // input MC file
  TFile* MCfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/40pb/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_morebins.root","READ");
  */


  //TFile* datafile = new TFile("/nfs/dust/cms/user/kovalch/sFrame/JEC/uhh2.AnalysisModuleRunner.DATA.data_with_golden_jsondata_13TeV_40pb_all_data_l1.root","READ"); 

  // input DATA file
  //TFile* datafile = new TFile("/nfs/dust/cms/user/kovalch/sFrame/JEC/uhh2.AnalysisModuleRunner.DATA.data_with_golden_jsondata_13TeV_40pb_all_data.root","READ"); 
  // input MC file
  //TFile* MCfile = new TFile("/nfs/dust/cms/user/kovalch/sFrame/JEC/uhh2.AnalysisModuleRunner.MC.JetResolutionSmearerrun2_QCD_JER_smearing.root","READ");

  //no weight
  //TFile* MCfile = new TFile("/nfs/dust/cms/user/kovalch/sFrame/JEC/uhh2.AnalysisModuleRunner.MC.JetResolutionSmearerrun2_QCD_no_weight.root","READ");
  //low pu reweighting
  //TFile* MCfile = new TFile("/nfs/dust/cms/user/kovalch/sFrame/JEC/uhh2.AnalysisModuleRunner.MC.JetResolutionSmearerrun2_QCD_PU_rew.root","READ");


  // choose mpf or dijet balance
  bool mpfMethod(false);


  // define number of bins
  const int n_alpha = 5;
  const int n_eta = 16;

  // define the bin ranges
  TString alpha_range[n_alpha-1] = {"a01", "a02", "a03", "a04"};
  double alpha_bins[n_alpha] = {0.000, 0.100, 0.200, 0.300, 0.400};
  /*
  double eta_bins[n_eta] = {0.000, 0.250, 0.500, 0.750, 1.000, 1.300, 1.600, 1.900, 2.200, 2.500, 2.700, 2.850, 3.000, 3.200, 5.000};
  TString eta_range[n_eta] = {"0.000", "0.250", "0.500", "0.750", "1.000", "1.300", "1.600", "1.900", "2.200", "2.500", "2.700", "2.850", "3.000", "3.200","5.000"};
  TString eta_range2[n_eta] = {"00", "025", "05", "0750", "10", "13", "16", "19", "22", "25", "27", "285", "30", "32", "50"};
  TString eta_range3[n_eta] = {"0.0", "0.25", "0.5", "0.750", "1.0", "1.3", "1.6", "1.9", "2.2", "2.5", "2.7", "2.85", "3.0", "3.2", "5.0"};
  */
  /*
  double eta_bins[n_eta] = {0.000, 0.250, 0.500, 0.750, 1.000, 1.300, 1.600, 1.900, 2.200, 2.500, 2.700, 3.000, 3.200, 5.000};
  TString eta_range[n_eta] = {"0.000", "0.250", "0.500", "0.750", "1.000", "1.300", "1.600", "1.900", "2.200", "2.500", "2.700", "3.000", "3.200","5.000"};
  TString eta_range2[n_eta] = {"00", "025", "05", "0750", "10", "13", "16", "19", "22", "25", "27", "30", "32", "50"};
  TString eta_range3[n_eta] = {"0.0", "0.25", "0.5", "0.750", "1.0", "1.3", "1.6", "1.9", "2.2", "2.5", "2.7", "3.0", "3.2", "5.0"};
  */
  /*
  double eta_bins[n_eta] = {0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.653, 1.93, 2.172, 2.5, 2.853, 2.964, 3.139, 5.191};
  TString eta_range[n_eta] = {"0.000", "0.261", "0.522", "0.783", "1.044", "1.305", "1.653", "1.930", "2.172", "2.500", "2.853", "2.964", "3.139", "5.191"};
  TString eta_range2[n_eta] = {"00", "0261", "0522", "0783", "1044", "1305", "1653", "193", "2172", "25", "2853", "2964", "3139",  "5191"};
  TString eta_range3[n_eta] = {"0.0", "0.261", "0.522", "0.783", "1.044", "1.305", "1.653", "1.93", "2.172", "2.5", "2.853", "2.964", "3.139", "5.191"};
  */
  double eta_bins[n_eta] = {0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 5.191};
  TString eta_range[n_eta] = {"0.000", "0.261", "0.522", "0.783", "1.044", "1.305", "1.653", "1.930", "2.172", "2.322", "2.500", "2.650", "2.853", "2.964", "3.139", "5.191"};
  TString eta_range2[n_eta] = {"00", "0261", "0522", "0783", "1044", "1305", "1653", "193", "2172", "2322", "25", "2650", "2853", "2964", "3139",  "5191"};
  TString eta_range3[n_eta] = {"0.0", "0.261", "0.522", "0.783", "1.044", "1.305", "1.653", "1.93", "2.172", "2.322", "2.5", "2.65", "2.853", "2.964", "3.139", "5.191"};
 


  // get the histos 
  TH1D* data[n_alpha-1][n_eta-1];
  TH1D* mc[n_alpha-1][n_eta-1];

 

  for(int i=0; i<n_alpha-1; i++){
    for(int j=0; j<n_eta-1; j++){
      if(mpfMethod){
	data[i][j] = (TH1D*)datafile->Get(alpha_range[i]+"/eta_"+eta_range[j]+"_"+eta_range[j+1]+"/mpf");
	mc[i][j] = (TH1D*)MCfile->Get(alpha_range[i]+"/eta_"+eta_range[j]+"_"+eta_range[j+1]+"/mpf");
      }
      else{
	data[i][j] = (TH1D*)datafile->Get(alpha_range[i]+"/eta_"+eta_range[j]+"_"+eta_range[j+1]+"/r_rel");
	mc[i][j] = (TH1D*)MCfile->Get(alpha_range[i]+"/eta_"+eta_range[j]+"_"+eta_range[j+1]+"/r_rel");
      }
    }
  }

 


  // create the ratio histograms
  TH1D* ratio[n_eta-1];
  //TF1* fit_func[n_eta-1];
  for (int j=0; j<n_eta-1; j++){
    TString numstr=ToString(j);
    TString histoname="histo"+numstr;
    ratio[j] = new TH1D(histoname,histoname,n_alpha-1,alpha_bins);
  }


  // fill ratio histograms
  for(int j=0; j<n_eta-1; j++){
    for(int i=0; i<n_alpha-1; i++){
      ratio[j]->SetBinContent(i+1, (mc[i][j]->GetMean() / data[i][j]->GetMean()) / (mc[1][j]->GetMean() / data[1][j]->GetMean()) );
      //ratio[j]->SetBinError(i+1, 1/sqrt(data[i][j]->Integral()));
      ratio[j]->SetBinError(i+1, sqrt( pow(data[i][j]->GetRMS(),2)/data[i][j]->Integral()));// + pow(mc[i][j]->GetRMS(),2)/mc[i][j]->Integral() ) );
      //ratio[j]->SetBinError(i+1, sqrt( pow(data[i][j]->GetRMS(),2)/data[i][j]->Integral() + pow(mc[i][j]->GetRMS(),2)/mc[i][j]->Integral() ) );
    }
  }


  // create and fill tgrapherrors
  double xbin_tgraph[n_alpha-1] = {0.1,0.2,0.3,0.4};
  double zero[n_alpha-1] = {0, 0, 0, 0};
  TGraphErrors *graph1[n_eta-1];

  double content[n_alpha-1];
  double error[n_alpha-1];
  double content_dijet[n_alpha-1];
  double error_dijet[n_alpha-1];
  for(int j=0; j<n_eta-1; j++){
    for(int i=0; i<n_alpha-1; i++){
      content[i] = (ratio[j]->GetBinContent(i+1));
      error[i] = (ratio[j]->GetBinError(i+1));
    }
    graph1[j] = new TGraphErrors(n_alpha-1, xbin_tgraph, content , zero, error);
  }



  // create horizontal line for plotting ("ideal value")
  TLine *line = new TLine(0.,1,0.45,1);

 
  // create output .dat file, including the kFSR extrapolation (alpha->0)
  if(mpfMethod){
    FILE *fp = fopen("KFSR_MPF_extrapolation.dat","w");
    TH1D* kFSR_MPF = new TH1D("kfsr_mpf","kfsr_mpf", n_eta-1,eta_bins);
  }
  else{
    FILE *fp = fopen("KFSR_DiJet_extrapolation.dat","w");
    TH1D* kFSR_DiJet = new TH1D("kfsr_dijet","kfsr_dijet", n_eta-1,eta_bins);
  }

  TH1D* plotkfsr = new TH1D("kfsr","kfsr", n_eta-1,eta_bins);


  //create plots
  TCanvas* a[n_eta-1];
  for (int j=0; j<n_eta-1; j++){
    TString numstr=ToString(j);
    TString plotname="eta_"+eta_range[j]+"_"+eta_range[j+1];
    a[j] = new TCanvas(plotname, plotname, 800,600);
    gStyle->SetOptTitle(0);
    graph1[j]->SetMarkerColor(kBlue);
    graph1[j]->SetMarkerStyle(20);
    graph1[j]->SetLineColor(kBlue);
    graph1[j]->Draw("AP");
    graph1[j]->Fit("pol1","R");
    graph1[j]->GetXaxis()->SetTitle("#alpha");
    graph1[j]->GetXaxis()->SetTitleSize(0.05);
    //graph1[j]->GetYaxis()->SetTitle("kFSR");
    graph1[j]->GetXaxis()->SetLimits(0.,0.45);
    graph1[j]->GetYaxis()->SetRangeUser(0.90,1.10);
    line->SetLineStyle(2);
    line->Draw("SAME");
    // fill the output.dat file
    if (fp!=NULL) {
      Float_t value = pol1->GetParameter(0);
      Float_t uncert = pol1->GetParError(0);
      fprintf(fp, "%f %f\n",value,uncert);
    }
    plotkfsr->SetBinContent(j+1,pol1->GetParameter(0));
    plotkfsr->SetBinError(j+1,pol1->GetParError(0));
    if(mpfMethod){
      kFSR_MPF->SetBinContent(j+1,pol1->GetParameter(0));
      kFSR_MPF->SetBinError(j+1,pol1->GetParError(0));
    }
    else{
      kFSR_DiJet->SetBinContent(j+1,pol1->GetParameter(0));
      kFSR_DiJet->SetBinError(j+1,pol1->GetParError(0));
    }
    TLegend *leg1;
    leg1 = new TLegend(0.15,0.65,0.60,0.85,"","brNDC");//x+0.1
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.045);
    leg1->SetFillColor(10);
    leg1->SetLineColor(1);
    leg1->SetTextFont(42);
    if(mpfMethod){
      leg1->SetHeader("MPF, "+eta_range3[j]+"#leq|#eta|<"+eta_range3[j+1]);
    }
    else{
      leg1->SetHeader("dijet balance, "+eta_range3[j]+"#leq|#eta|<"+eta_range3[j+1]);
    }
    leg1->AddEntry(graph1[j], "R(MC)/R(DATA)","P");
    leg1->AddEntry(pol1, "linear fit","L");
    leg1->Draw();
    //save the plots
    if(mpfMethod){
      //a[j]->Print("morebins_kFSR_MPF_eta_"+eta_range2[j]+"_"+eta_range2[j+1]+".pdf");
    }
    else{
      //a[j]->Print("morebins_kFSR_DiJet_eta_"+eta_range2[j]+"_"+eta_range2[j+1]+".pdf");
    }

  }
  fclose(fp);


  // create output file including the kFSR plot
  if(mpfMethod){
    TFile* outputfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_KFSR_MPF_L1.root","RECREATE");
    kFSR_MPF->Write();
    outputfile->Write();
    outputfile->Close();
  }
  else{
    TFile* outputfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_KFSR_DiJet_L1.root","RECREATE");
    kFSR_DiJet->Write();
    outputfile->Write();
    outputfile->Close();
  }


}
