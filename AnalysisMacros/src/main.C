#include <cmath>
#include <iostream>
#include "../include/CorrectionObject.h"
#include "../include/parameters.h"
#include <TString.h>
#include <vector>
#include <algorithm>

using namespace std;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> [VARIABLE]\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t--mode\t\tMode in which the plots was created, used in the input path.\n"
              << "\t--dname\t\tSuffix for the input and output path.\n"
	      << "\t--outSuffix\t\Additional output suffix.\n"
              << "\t--run\t\tRun Nr, default is B, used in the input path\n"
	      << "\t-FP\t\tRun all main control plots.\n"
 	      << "\t-FPeta\t\tRun all main control plots with signed eta.\n"     
 	      << "\t-FCP\t\tRun all final control plots.\n"     
	      << "\t-tCP\t\tRun control plots of the jet pt, eta and count for all trigger separately.\n"
      	      << "\t-lFCP\t\tRun final control plots for all lumi bins separately.\n"
	      << "\t-aFCP\t\tRun final control plots and plot all data asymetrie histograms seperaty.\n"
      	      << "\t-JEF\t\tDo Jet energy fractions plots.\n"
	      << "\t-aAP\t\tDo asymmetry plots for all abs(eta) and pt bins sepertely.\n"
      	      << "\t-aAPef\t\tDo asymmetry plots for all eta and pt bins sepertely.\n"
	      <<"\t-mon\t\tDo Monitoring Plots.\n"
      	      << "\t-NPVEta\t\tDo eta to NPV plots.\n"      
    	      << "\t-derThreshSi\t\tDerive the trigger thresholds for single jet trigger.\n"
      	      << "\t-derThreshSi_ptCheck\t\tDerive the trigger efficiency distributions for the jet 1 and 2 pt as crosscheck for single jet trigger.\n"
	      << "\t-derThreshDi\t\tDerive the trigger thresholds for di jet trigger.\n"
      	      << "\t-derThreshDi_ptCheck\t\tDerive the trigger efficiency distributions for the jet 1 and 2 pt as crosscheck for di jet trigger.\n"
    	      << "\t-LP\t\tPlot the luminosities.\n"
     	      << "\t-MP\t\tPlot the matching jet ids.\n"
	      << "\t-OORP\t\tPlot on/off jet pt response  jet.\n"
      	      << "\t-MPd\t\tPlot the matching jet ids for the dijet trg. \n"
	      << "\t-OORPd\t\tPlot on/off jet pt response  jet for the dijet trg.\n"     
	      << "\t-TEC\t\tCheck if the trigger are really exclusive.\n"
 	      << "\t-BC\t\tUse the older BC directory instead of the BCD directory.\n"
       	      << "\t-D\t\tUse the D directory instead of the BCD directory.\n"
       	      << "\t-E\t\tUse the E directory instead of the BCD directory.\n"
	      << "\t-DE\t\tUse the E directory instead of the BCD directory.\n"
       	      << "\t-F\t\tUse the F directory instead of the BCD directory.\n"      
  	      << "\t-mu\t\tDo the single muon threshold crosscheck.\n"
      	      << "\t-useHF\t\tIncludes the HF trigger.\n"
	      << "\t--muTrg\t\tTrigger name used for the single muon threshold crosscheck.\n"
	      << "\t--asym_cut\t\tCut Value with which some of the final control plots will be made.\n"
      	      <<"\t--input\t\tPath to the input data, if none is given following is used:\n"
	      << "\tThe input path is created as /nfs/dust/cms/user/"<<getenv("USER")<<"/forBaconJets/17Nov2017/Residuals/Run17BCD_Data <_mode> /Run17 <run><_dname> .root\n\tThe completion script assumes the same file structure."	    
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

  std::vector<std::string> argl = {"-FP" ,
				   "-FPeta",
				   "-FCP",
				   "-tCP",
				   "-lFCP",
				   "-aFCP",
				   "-derThreshSi",
				   "-derThreshSi_ptCheck",
				   "-derThreshDi",
				   "-derThreshDi_ptCheck",
				   "-BC",
				   "-D",
				   "-E",
				   "-DE",
				   "-F" ,
				   "-LP",
				   "-MP",
				   "-OORP" ,
				   "-MPd",
				   "-OORPd" ,
				   "-aAP",
				   "-aAPef",
				   "-TEC",
				   "-mu",
				   "--mode",
				   "--dname",
				   "--run",
				   "--muTrg",
				   "--asym_cut" ,
				   "-JEF",
				   "--input",
				   "--outSuffix",
				   "-useHF",
				   "-NPVEta",
				   "-mon"};
  
  TString run_nr = "B";
  TString dataname_end = "17Nov17_2017";
  TString outSuf = "";
  bool muonCrosscheck = false;
  TString muonTriggerName = "HLT_Mu17";
  TString mode ="";
  bool do_fullPlots=false;
  bool do_fullPlotsef=false;
  bool do_trgControlPlots=false;
  bool do_lumiControlPlots=false;
  bool do_asymControlPlots=false;
  bool do_deriveThresholdsSi=false;
  bool do_deriveThresholdsSi_ptCheck=false; 
  bool do_deriveThresholdsDi=false;
  bool do_deriveThresholdsDi_ptCheck=false;
  bool do_lumi_plot=false;
  bool do_matchtrg_plot=false;
  bool do_oor_plot=false; 
  bool do_matchtrg_plotdi=false;
  bool do_oor_plotdi=false; 
  bool do_finalControlPlots = false;
  bool do_addAsymPlots = false;
  bool do_addAsymPlotsef = false;  
  bool do_triggerEx = false;
  bool do_NPVEtaPlot = false;
  bool do_JEF = false;
  bool use_BC = false;
  bool use_D = false;
  bool use_E = false;
  bool use_DE = false;  
  bool use_F = false;
  bool useHF = false;
  bool do_mon = false;
  TString input_path_="";
  double asym_cut = 0.;
  for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
	if(arg=="-h"||arg=="--help"){
	  show_usage(argv[0]);
	  // return 0;
	  }

	if(arg[0]=='-'){
	  if(std::find(argl.begin(), argl.end(), arg) == argl.end()){
	    cout<<"Unknown option "<<arg<<endl;
	    show_usage(argv[0]);
	    // return 0;	    
	  } 
	  else if(arg=="-FP"){
	       do_fullPlots=true;
	  } 
	  else if(arg=="-FPeta"){
	       do_fullPlotsef=true;
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
	  else if(arg=="-NPVEta"){
	    do_NPVEtaPlot=true;
	  }
	  else if(arg=="-aFCP"){
	    do_asymControlPlots=true;
	  }
	  else if(arg=="-TEC"){
	    do_triggerEx=true;
	  }
	  else if(arg=="-JEF"){
	    do_JEF=true;
	  }	  
	  else if(arg=="-useHF"){
	    useHF=true;
	  }	  
	  else if(arg=="-derThreshSi"){
	    do_deriveThresholdsSi=true;
	  }
	  else if(arg=="-derThreshSi_ptCheck"){
	    do_deriveThresholdsSi_ptCheck=true;
	  }	  	    	  
	  else if(arg=="-derThreshDi"){
	    do_deriveThresholdsDi=true;
	  }
	  else if(arg=="-derThreshDi_ptCheck"){
	    do_deriveThresholdsDi_ptCheck=true;
	  }	  
	  else if(arg=="-mu"){
	    muonCrosscheck=true;
	  }
	  else if(arg=="-LP"){
	    do_lumi_plot=true;
	  }
	  else if(arg=="-MP"){
	    do_matchtrg_plot=true;
	  }
	  else if(arg=="-OORP"){
	    do_oor_plot=true;
	  }
	  else if(arg=="-MPd"){
	    do_matchtrg_plotdi=true;
	  }
	  else if(arg=="-OORPd"){
	    do_oor_plotdi=true;
	  }
	  else if(arg=="-aAP"){
	    do_addAsymPlots=true;
	  }else if(arg=="-aAPef"){
	    do_addAsymPlotsef=true;
	  }
	  else if(arg=="-mon"){
	    do_mon=true;
	  }
	  else if(arg=="-BC"){
	    use_BC=true;
	  }
	  else if(arg=="-D"){
	    use_D=true;
	  }
	  else if(arg=="-E"){
	    use_E=true;
	  }
	  else if(arg=="-DE"){
	    use_DE=true;
	  }
	  else if(arg=="-F"){
	    use_F=true;
	  }	  
	  else if(arg[1]=='-'){
	    if(arg=="--mode"){
	       mode = argv[i+1];
	      }
	      else if(arg=="--dname"){
		dataname_end = argv[i+1];
	      }
	      else if(arg=="--outSuffix"){
		outSuf = argv[i+1];
	      }	    
	      else if(arg=="--run"){
		run_nr = argv[i+1];
	      }
	    	    
	      else if(arg=="--muTrg"){
		muonTriggerName = argv[i+1];
		muonCrosscheck=true;
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

  if(not (do_fullPlots or do_fullPlotsef or do_trgControlPlots or do_lumiControlPlots or do_asymControlPlots or do_deriveThresholdsSi or do_deriveThresholdsSi_ptCheck or do_deriveThresholdsDi or do_deriveThresholdsDi_ptCheck or muonCrosscheck or asym_cut or do_lumi_plot  or do_matchtrg_plot or do_finalControlPlots or do_addAsymPlots or do_addAsymPlotsef or do_triggerEx or do_oor_plot or do_matchtrg_plotdi or do_oor_plotdi or do_NPVEtaPlot or do_JEF)){
    cout<<"No plots were specified! Only the existing of the files will be checked."<<endl;
    show_usage(argv[0]);
  }
  
  TString generator    = "pythia";
  bool    closure_test    = false;
  bool    trigger_fwd     = false;     //Use for Weight Calc
  bool    trigger_central = true;     //Use for Weight Calc
  TString collection    = "AK4CHS";

  cout<<"Run Nr.: "<<run_nr<<endl;
  cout<<dataname_end<<mode<<endl;
  if(muonCrosscheck) cout<<"Doing single muon crosscheck plots"<<endl;

  TString input_path;
  if(input_path_!=""){
    input_path=input_path_;
  }
  else{
      input_path  = "/nfs/dust/cms/user/"+(string)getenv("USER")+"/forBaconJets/17Nov2017/Residuals/Run17";
      if(use_BC) input_path+="BC";
      if(use_D) input_path+="D";
      if(use_E) input_path+="E";
      if(use_DE) input_path+="DE";      
      if(use_F) input_path+="F";      
      if(not(use_BC or use_D or use_E or use_DE or use_F)) input_path+="BCD";
  // if(muonCrosscheck) input_path+="D";
  input_path+="_Data";
  if(mode!="") input_path+="_";
  input_path+=mode + "/Run";
  input_path+= run_nr;
  if(muonCrosscheck) input_path +="_"+ muonTriggerName;
  if(dataname_end!="") input_path+="_";
  input_path += dataname_end + ".root";
  }
  
  TString weight_path  = "/nfs/dust/cms/user/karavdia/JEC_Summer16_V8_ForWeights/"; 
  TString input_path_MC = "/nfs/dust/cms/user/karavdia/JERC/Fall17_17Nov_V4_L2ResTest_PUpthat/uhh2.AnalysisModuleRunner.MC.QCDPt15to7000.root";
  
  TString outpath_postfix = (dataname_end!="") ? "_" : "";
  outpath_postfix  +=  dataname_end;
  if(outSuf!="") outpath_postfix += "_";
  outpath_postfix += outSuf;
  
  //eine Klasse: enthaelt Info ueber runnr, Generator, collection, Strings zu MC/DATA-files, memberfunctions: controlPlots, kFSR etc.
    vector<CorrectionObject> Objects;
  
    Objects.emplace_back(CorrectionObject(run_nr, generator,collection, input_path, input_path_MC, weight_path, closure_test, trigger_fwd, trigger_central, outpath_postfix));
 
    cout << "testobject is " << Objects[0] << endl;

    if(do_fullPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FullCycle_CorrectFormulae();
    if(do_fullPlots or do_JEF) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].JetEnergyFractions();

    
    if(do_fullPlotsef) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FullCycle_CorrectFormulae_eta();    
    if(do_trgControlPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].ControlPlots(true);
    

    if(do_deriveThresholdsSi) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_SiJet(false,useHF);
    if(do_deriveThresholdsSi_ptCheck) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_SiJet(true,useHF);

    if(do_deriveThresholdsDi) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_DiJet(false,useHF);
    if(do_deriveThresholdsDi_ptCheck) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_DiJet(true,useHF);    
 
    if(muonCrosscheck) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_SiJet();
    
    if(do_finalControlPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae();
    
    if(asym_cut) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(asym_cut);

    if(do_asymControlPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae(0.,true);

      if(do_NPVEtaPlot) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].NPVtoEtaPlots();  
    
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
    if(do_mon) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Monitoring();
    if(do_matchtrg_plot) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].JetMatching_Plots();
    if(do_oor_plot) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].OnOffResp_Plots();
   if(do_matchtrg_plotdi) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].JetMatching_PlotsDi();
    if(do_oor_plotdi) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].OnOffResp_PlotsDi(useHF);
    if(do_addAsymPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].AdditionalAsymmetryPlots();
    if(do_addAsymPlotsef) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].AdditionalAsymmetryPlots(false);
    if(do_triggerEx) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].triggerExclusivityCheck();

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
