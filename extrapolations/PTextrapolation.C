
// with this script pT extrapolations in bins of eta will be calculated

TString ToString(int num) {
  ostringstream start;
  start<<num;
  TString start1=start.str();
  return start1;
}

void PTextrapolation(){

  gStyle->SetOptFit();
  gStyle->SetOptFit(0);

  
  // input DATA file
  TFile* datafile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/uhh2.AnalysisModuleRunner.DATA.DATA_25ns_DConly_MCcorrected_v2.root","READ"); 
  // input MC file
  TFile* MCfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/uhh2.AnalysisModuleRunner.MC.MC_QCDpt15to7000_13TeV_25ns_MCcorrV2.root","READ");
  

  // choose mpf or dijet balance
  bool mpfMethod(false);


  // define number of bins
  const int n_eta = 16;
  const int n_pt = 9;
  //const int n_alpha = 5;


  // define the bin ranges
  //TString pt_range[n_pt] = {"43.000", "80.000", "88.000", "135.000", "223.000", "290.000", "365.000", "448.000", "561.000"};
  //double alpha_bins[n_alpha] = {0.000, 0.100, 0.200, 0.300, 0.400};
  //double pt_bins[n_pt] = {43, 80, 88, 135, 223, 290, 365, 448, 561};//{66, 107, 191, 240, 306, 379, 468, 900};
  //TString alpha_range[n_alpha] = {"0.000", "0.100", "0.200", "0.300", "0.400"};
  TString pt_range[n_pt] = {"55.000", "76.000", "93.000", "172.000", "232.000", "300.000", "366.000", "452.000", "558.000"};
  double pt_bins[n_pt] = {55, 76, 93, 172, 232, 300, 366, 452, 558};

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
  TH1D* data[n_eta-1][n_pt-1];
  TH1D* mc[n_eta-1][n_pt-1];
  TH1D* ptave_data[n_eta-1];
  
  for(int i=0; i<n_eta-1; i++){
    ptave_data[i] = (TH1D*)datafile->Get("/a02/eta_"+eta_range[i]+"_"+eta_range[i+1]+"/pt_ave");
    for(int j=0; j<n_pt-1; j++){
      if(mpfMethod){
	data[i][j] = (TH1D*)datafile->Get("/eta_"+eta_range[i]+"_"+eta_range[i+1]+"/pt_"+pt_range[j]+"_"+pt_range[j+1]+"/mpf");
	mc[i][j] = (TH1D*)MCfile->Get("/eta_"+eta_range[i]+"_"+eta_range[i+1]+"/pt_"+pt_range[j]+"_"+pt_range[j+1]+"/mpf");
      }
      else{
	data[i][j] = (TH1D*)datafile->Get("/eta_"+eta_range[i]+"_"+eta_range[i+1]+"/pt_"+pt_range[j]+"_"+pt_range[j+1]+"/r_rel");
	mc[i][j] = (TH1D*)MCfile->Get("/eta_"+eta_range[i]+"_"+eta_range[i+1]+"/pt_"+pt_range[j]+"_"+pt_range[j+1]+"/r_rel");
      }
    }
  }

 
  
  // create the ratio histogram
  TH1D* ratio[n_eta-1];
  //TF1* fit_func[n_eta-1];
  for (int j=0; j<n_eta-1; j++){
    TString numstr=ToString(j);
    TString histoname="histo"+numstr;
    ratio[j] = new TH1D(histoname,histoname,n_pt-1,pt_bins);
    //fit_func[j] = new TF1("lin_fit[j]", "pol1", 0., n_alpha);
  }


  
  // fill ratio histograms
  for(int j=0; j<n_eta-1; j++){
    for(int i=0; i<n_pt-1; i++){
      ratio[j]->SetBinContent(i+1, (mc[j][i]->GetMean() / data[j][i]->GetMean()));
      ratio[j]->SetBinError(i+1, sqrt( pow(data[j][i]->GetRMS(),2)/data[j][i]->Integral())); // + pow(mc[j][i]->GetRMS(),2)/mc[j][i]->Integral() ) );
      //ratio[j]->SetBinError(i+1, sqrt( (mc[j][i]->GetMean()/pow(data[j][i]->GetMean(),2))* pow(data[j][i]->GetRMS(),2)/data[j][i]->Integral() + (1/data[j][i]->GetMean())* pow(mc[j][i]->GetRMS(),2)/mc[j][i]->Integral() ) );
      //ratio[j]->SetBinError(i+1, 1/sqrt(data[j][i]->Integral()));
      //ratio[j]->SetBinError(i+1, 1/data[j][i]->Integral());
    }
  }
 

  // create and fill tgrapherrors
  double xbin_tgraph[n_pt-1];
  double zero[n_pt-1];
  for(int i=0;i<n_pt-1;i++){
    xbin_tgraph[i]=(pt_bins[i]+pt_bins[i+1])/2;
    zero[i]=(pt_bins[i+1]-pt_bins[i])/2 ;
  }
  TGraphErrors *graph1[n_eta-1];
  double content[n_pt-1];
  double error[n_pt-1];
  for(int j=0; j<n_eta-1; j++){
    for(int i=0; i<n_pt-1; i++){
      content[i] = ratio[j]->GetBinContent(i+1);
      error[i] = ratio[j]->GetBinError(i+1);
    }
    graph1[j] = new TGraphErrors(n_pt-1, xbin_tgraph, content , zero, error);
  }

  
  // clean up nonphysical values
  for(int i=0; i<n_eta-1; i++){
    for(int j= graph1[i]->GetN()-1; j != -1; --j) {
      if(graph1[i]->GetY()[j]!=graph1[i]->GetY()[j] || graph1[i]->GetEY()[j]!=graph1[i]->GetEY()[j]) graph1[i]->RemovePoint(j);
    }
  }
  

  // remove all data point with less than 100 entries  
  for(int j=0; j<n_eta-1; j++){
    for(int i=n_pt-2; i!=-1; --i){
      if(data[j][i]->GetEntries()<100){
	graph1[j]->RemovePoint(i);
      }
    }
  }
  // make sure that the cut was working
  for(int i=0; i<n_eta-1; i++){
      cout << graph1[i]->GetN() << endl;
  }
  


  // create horizontal line for plotting ("ideal value")
  TLine *line = new TLine(0.,1,700,1);

  // dummy text for presentations..
  TPaveText * text[n_eta-1];

  // create a function for the loglinear fit
  TF1 * f1[n_eta-1];
  // create a function for the constant fit
  TF1 * f2[n_eta-1];

  // create output .dat file, including the kFSR extrapolation (alpha->0)
  if(mpfMethod){
    FILE *fp = fopen("pT_MPF_extrapolations.dat","w");
    FILE *fp2 = fopen("pT_MPF_constantExtrapolation.dat","w");
    FILE *l2resfile = fopen("L2Res_MPF.dat","w");
  }
  else{
    FILE *fp = fopen("pT_DiJet_extrapolations.dat","w");
    FILE *fp2 = fopen("pT_DiJet_constantExtrapolation.dat","w");
    FILE *l2resfile = fopen("L2Res_DiJet.dat","w");
  }

  // dummy printed values for presentation
  /* //dijet balance
  TString fitval[n_eta-1]={"0.999283","1.0045","1.01964","1.08269","1.27129","1.33222"};
  TString fitvalerr[n_eta-1]={"0.00655323","0.00785023","0.00974514","0.0147418","0.0347744","0.0205742"};
  */
  //mpf
  //TString fitval[n_eta-1]={"1.00008","1.00507","1.02389","1.08707","1.2876","1.30467"};
  //TString fitvalerr[n_eta-1]={"0.00649284","0.00777939","0.0096423","0.0144695","0.0339931","0.0200854"};
  

  TCanvas* a[n_eta-1];
  for (int j=0; j<n_eta-1; j++){
    TString numstr=ToString(j);
    TString plotname="eta_"+eta_range[j]+"_"+eta_range[j+1];
    a[j] = new TCanvas(plotname, plotname, 800,700);
    gStyle->SetOptTitle(0);
    gPad->SetLogx();
    graph1[j]->SetMarkerColor(kBlue);
    graph1[j]->SetMarkerStyle(20);
    graph1[j]->SetLineColor(kBlue);
 
    f1[j] = new TF1(plotname+"f1","[0]+[1]*TMath::Log(x)");
    f2[j] = new TF1(plotname+"f2","pol0");
    f2[j]->SetLineColor(kBlue);
    f2[j]->SetLineStyle(3);

    graph1[j]->Fit(plotname+"f1","W");
    graph1[j]->Fit(plotname+"f2","+ SAME");
    graph1[j]->Draw("AP");
    graph1[j]->GetXaxis()->SetTitle("#bar{p}_{T} [GeV]");
    graph1[j]->GetXaxis()->SetTitleSize(0.05);
    graph1[j]->GetXaxis()->SetTitleOffset(0.80);
    //graph1[j]->GetYaxis()->SetTitle("kFSR");
    graph1[j]->GetXaxis()->SetLimits(30,700);
    graph1[j]->GetYaxis()->SetRangeUser(0.85,1.55);

    // dummy text for presentation
    text[j]=new TPaveText(0.65,0.75,0.95,0.65,"brNDC");
    //text[j]->AddText("const fit p0   "+fitval[j]+" #pm "+fitvalerr[j]);
    //text[j]->Draw("SAME");  


    line->SetLineStyle(2);
    line->Draw("SAME");
    // fill the output.dat file
    /*if (fp!=NULL) {
      // getting the slope parameter from the loglinear fit
      Float_t value = f1[j]->GetParameter(1);
      fprintf(fp, "%f\n",value);
      }*/
    if (fp2!=NULL) {
      // getting the p0 parameter from the constant fit
      Float_t value = f2[j]->GetParameter(0);
      fprintf(fp2, "%f\n",value);
    }
    if (l2resfile!=NULL) {

      fprintf(l2resfile, "%f\n", eta_bins[j]);
    }
    TLegend *leg1;
    leg1 = new TLegend(0.15,0.65,0.60,0.85,"","brNDC");//x+0.1
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.038);
    leg1->SetFillColor(10);
    leg1->SetLineColor(1);
    leg1->SetTextFont(42);
    if(mpfMethod){
      leg1->SetHeader("MPF #bar{p}_{T} extrapolation, "+eta_range3[j]+"#leq|#eta|<"+eta_range3[j+1]);
    }
    else{
      leg1->SetHeader("DiJet balance #bar{p}_{T} extrapolation, "+eta_range3[j]+"#leq|#eta|<"+eta_range3[j+1]);
    }
    leg1->AddEntry(graph1[j], "R(MC)/R(DATA)","P");
    leg1->AddEntry(f1[j], "loglinear fit","L");
    leg1->AddEntry(f2[j], "constant fit","L");
    leg1->Draw();

    //save plots
    if(mpfMethod){
      //a[j]->Print("morebinspTextrapol_MPF_pT_"+eta_range2[j]+"_"+eta_range2[j+1]+".pdf");
    }
    else{
      //a[j]->Print("morebinspTextrapol_DiJet_pT_"+eta_range2[j]+"_"+eta_range2[j+1]+".pdf");
    }
  }
  fclose(fp);
  fclose(fp2);

  /*
  for (int j=0; j<n_eta-1; j++){
   cout << f2[j]->GetParameter(0) << endl;
   cout << f2[j]->GetParError(0) << endl;
  }
  */


  for(int i=0; i<n_eta-1; i++){
    cout << "mean value, eta " << eta_range[i] << " to " << eta_range[i+1] << ": " << ptave_data[i]->GetMean() << endl;
    //cout << "max value, eta " << eta_range[i] << " to " << eta_range[i+1] << ": " << ptave_data[i]->FindLastBinAbove() << endl;
  }
  for(int i=0; i<n_eta-1; i++){
    cout << "loglin fit value " << eta_range[i] << " to " << eta_range[i+1] << ": " << f1[i]->GetParameter(1) << endl;
  }

  const int n_etabarr=5;

  // get the kFSR plots and calculate residuals
  if(mpfMethod){
    TFile* kfsr_mpf = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_KFSR_MPF_L1.root","READ");
    TH1D* hist_kfsr_mpf = kfsr_mpf->Get("kfsr_mpf");
    double flat[n_eta-1];
    double loglin[n_eta-1];
    for (int j=0; j<n_eta-1; j++){
      flat[j] = hist_kfsr_mpf->GetBinContent(j+1)*f2[j]->GetParameter(0);
      loglin[j] = hist_kfsr_mpf->GetBinContent(j+1)*(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()) );
    }
    double flat_norm, loglin_norm;
    for (int j=0; j<n_etabarr; j++){
      flat_norm += flat[j];
      loglin_norm += loglin[j];
    }
    flat_norm = flat_norm/n_etabarr;
    loglin_norm = loglin_norm/n_etabarr;
    for (int j=0; j<n_eta-1; j++){
      flat[j] = flat[j]/flat_norm;
      loglin[j] = loglin[j]/loglin_norm;
      //cout << flat[j] << endl;
    }

    TH1D* Residual_logpt_MPF = new TH1D("res_logpt_mpf","res_logpt_mpf", n_eta-1,eta_bins);
    TH1D* Residual_const_MPF = new TH1D("res_const_mpf","res_const_mpf", n_eta-1,eta_bins);
    TH1D* ptave_const_MPF = new TH1D("ptave_const_mpf","ptave_const_mpf", n_eta-1,eta_bins);
    ofstream output, output_loglin;
    output.open("Summer15_25ns_MPF_FLAT_L2Residual_v1UHH1_AK4PFchs.txt");
    output_loglin.open("Summer15_25ns_MPF_LOGLIN_L2Residual_v1UHH1_AK4PFchs.txt");
    output  << "JetEta (abs)      " << "p[0]" << "       " <<  "kFSR * p[0] " << "  statistical unc" << endl;
    output_loglin  << "JetEta (abs)      "  << "p[0]        "  << "p[1]"  << "       " <<  "kFSR*[p[0]+p[1]*Log(max(ptmin,min(ptmax, x)) )] " << "  statistical unc" << endl;
    for (int j=0; j<n_eta-1; j++){
      output << std::setprecision(5)  << eta_range[j]<< "    " << eta_range[j+1] << "    " <<  f2[j]->GetParameter(0)  << "     " << flat[j] << "        " << sqrt( pow(f2[j]->GetParameter(0)*hist_kfsr_mpf->GetBinError(j+1),2)+pow( hist_kfsr_mpf->GetBinContent(j+1)*f2[j]->GetParError(0),2)  ) / flat_norm  << endl;
      output_loglin << std::setprecision(5)  << eta_range[j]<< "    " << eta_range[j+1] << "    " <<  f1[j]->GetParameter(0)  << "     " << f1[j]->GetParameter(1) << "            " << loglin[j] << "        " << sqrt(  pow(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()),2)*pow(hist_kfsr_mpf->GetBinError(j+1),2)   + pow(hist_kfsr_mpf->GetBinContent(j+1),2)*(pow(f2[j]->GetParError(0),2)+pow(f1[j]->GetParError(1),2)) ) / loglin_norm  << endl;

      Residual_logpt_MPF->SetBinContent(j+1,hist_kfsr_mpf->GetBinContent(j+1)*(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()) ) );
      Residual_logpt_MPF->SetBinError(j+1, sqrt(  pow(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()),2)*pow(hist_kfsr_mpf->GetBinError(j+1),2)   + pow(hist_kfsr_mpf->GetBinContent(j+1),2)*(pow(f2[j]->GetParError(0),2)+pow(f1[j]->GetParError(1),2)) )  );
      Residual_const_MPF->SetBinContent(j+1,hist_kfsr_mpf->GetBinContent(j+1)*f2[j]->GetParameter(0));
      Residual_const_MPF->SetBinError(j+1, sqrt( pow(f2[j]->GetParameter(0)*hist_kfsr_mpf->GetBinError(j+1),2)+pow( hist_kfsr_mpf->GetBinContent(j+1)*f2[j]->GetParError(0),2)  )  );
      ptave_const_MPF->SetBinContent(j+1,f2[j]->GetParameter(0));
      ptave_const_MPF->SetBinError(j+1,f2[j]->GetParError(0));
    }
    TFile* outputfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_Res_MPF_L1.root","RECREATE");
    Residual_logpt_MPF->Write();
    Residual_const_MPF->Write();
    outputfile->Write();
    outputfile->Close();
    TFile* outputfile2 = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_ptaveConst_MPF_L1.root","RECREATE");
    ptave_const_MPF->Write();
    outputfile2->Write();
    outputfile2->Close();
  }
  else{
    TFile* kfsr_dijet = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_KFSR_DiJet_L1.root","READ");
    TH1D* hist_kfsr_dijet = kfsr_dijet->Get("kfsr_dijet");

    double flat[n_eta-1];
    double loglin[n_eta-1];
    for (int j=0; j<n_eta-1; j++){
      flat[j] = hist_kfsr_dijet->GetBinContent(j+1)*f2[j]->GetParameter(0);
      loglin[j] = hist_kfsr_dijet->GetBinContent(j+1)*(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()) );
    }
    double flat_norm, loglin_norm;
    for (int j=0; j<n_etabarr; j++){
      flat_norm += flat[j];
      loglin_norm += loglin[j];
    }
    flat_norm = flat_norm/n_etabarr;
    loglin_norm = loglin_norm/n_etabarr;
    for (int j=0; j<n_eta-1; j++){
      flat[j] = flat[j]/flat_norm;
      loglin[j] = loglin[j]/loglin_norm;
      //cout << flat[j] << endl;
    }



    TH1D* Residual_logpt_DiJet = new TH1D("res_logpt_dijet","res_logpt_dijet", n_eta-1,eta_bins);
    TH1D* Residual_const_DiJet = new TH1D("res_const_dijet","res_const_dijet", n_eta-1,eta_bins);
    TH1D* ptave_const_DiJet = new TH1D("ptave_const_dijet","ptave_const_dijet", n_eta-1,eta_bins);
    ofstream output, output_loglin;
    output.open("Summer15_25ns_pT_FLAT_L2Residual_v1UHH1_AK4PFchs.txt");
    output_loglin.open("Summer15_25ns_pT_LOGLIN_L2Residual_v1UHH1_AK4PFchs.txt");
    output  << "JetEta (abs)      " << "p[0]" << "       " <<  "kFSR * p[0] " << "  statistical unc" << endl;
    output_loglin  << "JetEta (abs)      "  << "p[0]        "  << "p[1]"  << "       " <<  "kFSR*[p[0]+p[1]*Log(max(ptmin,min(ptmax, x)) )] " << "  statistical unc" << endl;
    for (int j=0; j<n_eta-1; j++){
      output << std::setprecision(5)  << eta_range[j]<< "    " << eta_range[j+1] << "    " <<  f2[j]->GetParameter(0)  << "     " << flat[j] << "        " << sqrt( pow(f2[j]->GetParameter(0)*hist_kfsr_dijet->GetBinError(j+1),2)+pow( hist_kfsr_dijet->GetBinContent(j+1)*f2[j]->GetParError(0),2)  ) / flat_norm  << endl;
      output_loglin << std::setprecision(5)  << eta_range[j]<< "    " << eta_range[j+1] << "    " <<  f1[j]->GetParameter(0)  << "     " << f1[j]->GetParameter(1) << "            " << loglin[j] << "        " << sqrt(  pow(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()),2)*pow(hist_kfsr_dijet->GetBinError(j+1),2)   + pow(hist_kfsr_dijet->GetBinContent(j+1),2)*(pow(f2[j]->GetParError(0),2)+pow(f1[j]->GetParError(1),2)) ) / loglin_norm  << endl;


      Residual_logpt_DiJet->SetBinContent(j+1,hist_kfsr_dijet->GetBinContent(j+1)*(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()) ) );
      Residual_logpt_DiJet->SetBinError(j+1, sqrt(  pow(f1[j]->GetParameter(0)+f1[j]->GetParameter(1)*TMath::Log(ptave_data[j]->GetMean()),2)*pow(hist_kfsr_dijet->GetBinError(j+1),2)   + pow(hist_kfsr_dijet->GetBinContent(j+1),2)*(pow(f2[j]->GetParError(0),2)+pow(f1[j]->GetParError(1),2)) )  );
      Residual_const_DiJet->SetBinContent(j+1,hist_kfsr_dijet->GetBinContent(j+1)*f2[j]->GetParameter(0));
      Residual_const_DiJet->SetBinError(j+1, sqrt( pow(f2[j]->GetParameter(0)*hist_kfsr_dijet->GetBinError(j+1),2)+pow( hist_kfsr_dijet->GetBinContent(j+1)*f2[j]->GetParError(0),2)  )  );
      ptave_const_DiJet->SetBinContent(j+1,f2[j]->GetParameter(0));
      ptave_const_DiJet->SetBinError(j+1,f2[j]->GetParError(0));
    }
    TFile* outputfile = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_Res_DiJet_L1.root","RECREATE");
    Residual_logpt_DiJet->Write();
    Residual_const_DiJet->Write();
    outputfile->Write();
    outputfile->Close();
    TFile* outputfile2 = new TFile("/nfs/dust/cms/user/mstoev/sFrame_new/JEC/run2_output/25ns_0909/Histo_ptaveConst_DiJet_L1.root","RECREATE");
    ptave_const_DiJet->Write();
    outputfile2->Write();
    outputfile2->Close();
  }






}
