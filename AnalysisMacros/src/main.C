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
	      << "\t--FP\t\tRun all main control plots.\n"
	      << "\t--tCP\t\tRun control plots of the jet pt, eta and count for all trigger separately.\n"
    	      << "\t--derThresh\t\tDerive the trigger thresholds.\n"
	      << "\t--mu\t\tDo the single muon threshold crosscheck.\n"
	      << "\t--muTrg\t\tTrigger name used for the single muon threshold crosscheck.\n"
	      << "\n\tThe input path is created as /nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC <D for single muon crosscheck> _Data <_mode> /Run17 <run> _Data <_dname> .root" 
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

  //TODO at some point do --help
  
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
  bool do_trgControlPlolts=false;
  bool do_deriveThresholds=false; 
  for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
	if(arg=="-h"||arg=="--help"){
	  show_usage(argv[0]);
	    return 0;
	  }

	if(arg[0]=='-'){
	  if(arg[1]=='-'){
	    if(arg=="--mode"){
	       mode = argv[i+1];
	       muonCrosscheck = (mode=="mu"); 
	       if(muonCrosscheck) mode = "DeriveThresholds_inclSiMu";
	    }
	    else if(arg=="--dname"){
	       dataname_end = argv[i+1];
	    }
	    else if(arg=="--run"){
	       run_nr = argv[i+1];
	    }
	    else if(arg=="--FP"){
	       do_fullPlots=true;
	    }
	    else if(arg=="--tCP"){
	       do_trgControlPlolts=true;
	    }
	    else if(arg=="--derThresh"){
	       do_deriveThresholds=true;
	    }	    
	    else if(arg=="--mu"){
	       muonCrosscheck=true;
	    }	    
	    else if(arg=="--muTrg"){
	      muonTriggerName = argv[i+1];
	    }
	  }
	}
  }

  if(not (do_fullPlots or do_trgControlPlolts or do_deriveThresholds or muonCrosscheck)){  //TODO at some point do --help
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

  TString input_path  = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC";
  if(muonCrosscheck) input_path+="D";
  input_path+="_Data";
  if(mode!="") input_path+="_";
  input_path+=mode + "/Run17";
  input_path+= run_nr + "_Data";
  if(dataname_end!="") input_path+="_";
  input_path += dataname_end + ".root";
  TString weight_path  = "/nfs/dust/cms/user/karavdia/JEC_Summer16_V8_ForWeights/"; 
  TString input_path_MC = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17B_MC16/QCDFlat16.root";
  TString outpath_postfix = (dataname_end!="") ? "_" : "";
  outpath_postfix  +=  dataname_end; 
  
  //eine Klasse: enthaelt Info ueber runnr, Generator, collection, Strings zu MC/DATA-files, memberfunctions: controlPlots, kFSR etc.
    vector<CorrectionObject> Objects;
  
    Objects.emplace_back(CorrectionObject(run_nr, generator,collection, input_path, input_path_MC, weight_path, closure_test, trigger_fwd, trigger_central, outpath_postfix));
 
    cout << "testobject is " << Objects[0] << endl;

    if(do_fullPlots) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae();
    
    if(do_trgControlPlolts) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].ControlPlots(true);
    

    if(do_deriveThresholds) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds();
 
    if(muonCrosscheck) for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_SiMuCrosscheck(muonTriggerName);  

      // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].kFSR_CorrectFormulae();
      //  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].kFSR_CorrectFormulae_eta();  //extended eta range to negative Values 

// std::cout<<"\nStarting Pt_Extrapolation_Alternative_CorrectFormulae(true)\n"<<std::endl;
    //   for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Pt_Extrapolation_Alternative_CorrectFormulae(true);   //MPF method
    // std::cout<<"\nStarting Pt_Extrapolation_Alternative_CorrectFormulae(false)\n"<<std::endl;
    //   for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Pt_Extrapolation_Alternative_CorrectFormulae(false);  //pT bal method

    // // // //       //for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Pt_Extrapolation_Alternative_CorrectFormulae_eta(true); //extended eta range to negative Values 
// // // //       //for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Pt_Extrapolation_Alternative_CorrectFormulae_eta(false); //extended eta range to negative Values
      
  // std::cout<<"\nStarting L2ResOutput()\n"<<std::endl;
      // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].L2ResOutput();

// //       // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].L2ResOutput_eta();
// //    // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].InputForGlobalFit(); //Mikkos Macro 
// //    // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].InputForGlobalFit_eta_0_13(); //Mikkos Macro

  // std::cout<<"\nStarting FinalControlPlots_CorrectFormulae()\n"<<std::endl;

      
//      for(unsigned int i=0; i<Objects.size(); i++) Objects[i].MatchingPlots();

   // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae_eta(); //extended eta range to negative Values

     
// // //Run all macros to calculate L2Res corrections 
   // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FullCycle_CorrectFormulae();
         // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FullCycle_CorrectFormulae_eta();  //For Closure Test
     
// // // //Macros to compare different Runs 
// // //    // Objects[0].L2ResAllRuns();
// // //    // Objects[0].L2ResOverlay(true);
// // //    // Objects[0].L2ResOverlay(false);

// // // //Compare up/nominal/down Variations of JER
// // //    // Objects[0].L2Res_JEC();

    // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds();


  cout << endl <<"Closing MC and DATA files." << endl;
  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].CloseFiles();
  cout << "Going to return 0 now, cya." << endl << endl;
  return 0;
}

// Have you heard that entropy isn't what it used to be? 
