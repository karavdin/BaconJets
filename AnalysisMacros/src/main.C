#include <cmath>
#include <iostream>
#include "../include/CorrectionObject.h"
#include "../include/parameters.h"
#include <TString.h>

using namespace std;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> [VARIABLE]\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t--mode\t\tMode in which the plots was created, used in the input path.\n"
              << "\t--dname\t\tSuffix for the input and putput path.\n"
              << "\t--run\t\tRun Nr, default is B, used in the input path\n"
	      << "\t-FP\t\tRun all main control plots.\n"
 	      << "\t-FCP\t\tRun all final control plots.\n"     
	      << "\t-tCP\t\tRun control plots of the jet pt, eta and count for all trigger separately.\n"
      	      << "\t-lFCP\t\tRun final control plots for all lumi bins separately.\n"
	      <<"\t-aFCP\t\tRun final control plots and plot all data asymetrie histograms seperaty."
    	      << "\t-derThresh\t\tDerive the trigger thresholds.\n"
    	      << "\t-LP\t\tPlot the luminosities.\n"
  	      << "\t-mu\t\tDo the single muon threshold crosscheck.\n"
	      << "\t--muTrg\t\tTrigger name used for the single muon threshold crosscheck.\n"
	      << "\t--asym_cut\t\tCut Value with which some of the final control plots will be made.\n"
	      <<"\t--input\t\tPath to the input data, if none is giveb following is used:\n"
	      << "\tThe input path is created as /nfs/dust/cms/user/"<<getenv("USER")<<"/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data <_mode> /Run17 <run> _Data <_dname> .root\n\tThe completion script assumes the same file structure."	    
              << std::endl;
}


int main(int argc,char *argv[]){
  //************************************************************
  //
  // Declare file directories 
  // Coose objects witch will be processed (Different Run eras) 
  // 
  // Coose analysis macros 
  // Use *_eta() to take into account negative eta dependency
  // To execute all, choose FullCycle_CorrectFormulae
  //
  //************************************************************

  cout << "Hello from main(). What am I going to do?\nWill it involve dead regions and high jetiness?\n13371n6 1n 7h3 57uff" << endl << endl;

   // cout<<argc<<endl;

  // for(int i=0;i<argc;i++){
  //   cout<<argv[i]<<endl;
  // }

  TString run_nr = "B";
  TString dataname_end = "";
  bool muonCrosscheck = false;
  TString muonTriggerName = "HLT_Mu17";
  TString mode ="";
  bool do_fullPlots=false;
  bool do_trgControlPlots=false;
  bool do_lumiControlPlots=false;
  bool do_asymControlPlots=false;
  bool do_deriveThresholds=false;
  bool do_lumi_plot=false;
  bool do_finalControlPlots = false;
  TString input_path_="";
  double asym_cut = 0.;
  for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
	if(arg=="-h"||arg=="--help"){
	  show_usage(argv[0]);
	    return 0;
	  }

	if(arg[0]=='-'){
	  
	  if(arg=="-FP"){
	       do_fullPlots=true;
	  }
	  else if(arg=="-FCP"){
	    do_finalControlPlots=true;
	  }
	  else if(arg=="-tCP"){
	    do_trgControlPlots=true;
	  }
	  else if(arg=="-lFCP"){
	    do_lumiControlPlots=true;
	  }
	  else if(arg=="-aFCP"){
	    do_asymControlPlots=true;
	  }	  
	  else if(arg=="-derThresh"){
	    do_deriveThresholds=true;
	  }	    
	  else if(arg=="-mu"){
	    muonCrosscheck=true;
	  }
	  else if(arg=="-LP"){
	    do_lumi_plot=true;
	  }
	  
	  else if(arg[1]=='-'){
	      
	      if(arg=="--mode"){
	       mode = argv[i+1];
	      }
	      else if(arg=="--dname"){
		dataname_end = argv[i+1];
	      }
	      else if(arg=="--run"){
		run_nr = argv[i+1];
	      }
	    	    
	      else if(arg=="--muTrg"){
		muonTriggerName = argv[i+1];
	      }
	      else if(arg=="--asym_cut"){
		asym_cut = stod(argv[i+1]);
	      }
	      else if(arg=="--input"){
		input_path_ = argv[i+1];
	      }
	  }
	}
  }

  if(not (do_fullPlots or do_trgControlPlots or do_lumiControlPlots or do_asymControlPlots or do_deriveThresholds or muonCrosscheck or asym_cut or do_lumi_plot or do_finalControlPlots)){
    cout<<"No plots were specified! Only the existing of the files will be checked."<<endl;
    show_usage(argv[0]);
  }
  
  TString generator    = "pythia";
  bool    closure_test    = false;
  bool    trigger_fwd     = false;     //Use for Weight Calc
  bool    trigger_central = true;     //Use for Weight Calc
  TString collection    = "AK4CHS";

  cout<<"Run Nr.: "<<run_nr<<endl;
  // cout<<dataname_end<<mode<<endl;
  if(muonCrosscheck) cout<<"Doing single muon crosscheck plots"<<endl;

  TString input_path;
  if(input_path_!=""){
    input_path=input_path_;
  }
  else{
      input_path  = "/nfs/dust/cms/user/"+(string)getenv("USER")+"/forBaconJets/2017PromptReco/Residuals/Run17BCD";
  // if(muonCrosscheck) input_path+="D";
  input_path+="_Data";
  if(mode!="") input_path+="_";
  input_path+=mode + "/Run17";
  input_path+= run_nr + "_Data";
  if(dataname_end!="") input_path+="_";
  input_path += dataname_end + ".root";
  }
  
  TString weight_path  = "/nfs/dust/cms/user/karavdia/JEC_Summer16_V8_ForWeights/"; 
  TString input_path_MC = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17B_MC16/QCDFlat16.root";
  TString outpath_postfix = (dataname_end!="") ? "_" : "";
  outpath_postfix  +=  dataname_end; 
  
  //eine Klasse: enthaelt Info ueber runnr, Generator, collection, Strings zu MC/DATA-files, memberfunctions: controlPlots, kFSR etc.
    vector<CorrectionObject> Objects;
  
    Objects.emplace_back(CorrectionObject(run_nr, generator,collection, input_path, input_path_MC, weight_path, closure_test, trigger_fwd, trigger_central, outpath_postfix));
 
    cout << "testobject is " << Objects[0] << endl;

    if(do_fullPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FullCycle_CorrectFormulae();
    
    if(do_trgControlPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].ControlPlots(true);
    

    if(do_deriveThresholds) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds();
 
    if(muonCrosscheck) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_SiMuCrosscheck(muonTriggerName);
    
    if(do_finalControlPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae();
    
    if(asym_cut) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(asym_cut);

    if(do_asymControlPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(0.,true);  
    
    if(do_lumiControlPlots){
      if(run_nr=="B"){
	for(int lumibin_ : lumibins_B ){
	  cout << "\nStart lumi bin" << lumibin_<<endl;
	  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(0.,false,lumibin_);}}
      else if(run_nr=="C"){
	for(int lumibin_ : lumibins_C ){
	  cout << "\nStart lumi bin" << lumibin_<<endl;
	  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(0.,false,lumibin_);}}
      else{
	for(int lumibin_ : lumibins_BC ){
	  cout << "\nStart lumi bin " << lumibin_<<endl;	  
	  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(0.,false,lumibin_);}}
    } 

    if(do_lumi_plot) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Lumi_Plots();

     // // // //Macros to compare different Runs 
// // //    // Objects[0].L2ResAllRuns();
// // //    // Objects[0].L2ResOverlay(true);
// // //    // Objects[0].L2ResOverlay(false);

// // // //Compare up/nominal/down Variations of JER
// // //    // Objects[0].L2Res_JEC();

  cout << endl <<"Closing MC and DATA files." << endl;
  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].CloseFiles();
  cout << "Going to return 0 now, cya." << endl << endl;
  return 0;
}

// Have you heard that entropy isn't what it used to be? 
