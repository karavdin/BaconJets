#include <cmath>
#include <iostream>
#include "../include/CorrectionObject.h"
#include "../include/parameters.h"
#include <TString.h>

using namespace std;



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
  bool muonCrosscheckEndings = false;
  if(argc==2){
    run_nr=argv[1];
      }
  else if(argc==3){
    run_nr=argv[1];
    TString muonCrosscheckEndings_ = argv[2];
    muonCrosscheckEndings = (muonCrosscheckEndings_=="true" || muonCrosscheckEndings_=="True" || muonCrosscheckEndings_=="1") ;
  }
  else if(argc>3){
    cout<< "main() got to many arguments, continue with default values"<<endl;
  }
  TString generator    = "pythia";
  bool    closure_test    = false;
  bool    trigger_fwd     = false;     //Use for Weight Calc
  bool    trigger_central = true;     //Use for Weight Calc
  TString collection    = "AK4CHS";

  cout<<"Run Nr.: "<<run_nr<<endl;
  if(muonCrosscheckEndings) cout<<"Doing single muon crosscheck plots"<<endl;
  

  TString input_path  = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data";
  if(muonCrosscheckEndings) input_path+="_DeriveThresholds_inclSiMu";
  input_path+="/Run17";
  input_path+= run_nr + (muonCrosscheckEndings ? "_Data_wMu17.root" : "_Data_newPtBinning.root");
  TString weight_path  = "/nfs/dust/cms/user/karavdia/JEC_Summer16_V8_ForWeights/"; 
  TString input_path_MC = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17B_MC16/QCDFlat16.root";
  TString outpath_postfix = muonCrosscheckEndings ? "_wMu17" : "_newPtBinning";//"_noEtaPhiClean";
  
  //eine Klasse: enthaelt Info ueber runnr, Generator, collection, Strings zu MC/DATA-files, memberfunctions: controlPlots, kFSR etc.
    vector<CorrectionObject> Objects;
  
    Objects.emplace_back(CorrectionObject(run_nr, generator,collection, input_path, input_path_MC, weight_path, closure_test, trigger_fwd, trigger_central, outpath_postfix));
 
    cout << "testobject is " << Objects[0] << endl;

      // for(unsigned int i=0; i<Objects.size(); i++) Objects[i].ControlPlots(true);
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
  //     for(unsigned int i=0; i<Objects.size(); i++) Objects[i].FinalControlPlots_CorrectFormulae();
      
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

   if(muonCrosscheckEndings){  
    for(unsigned int i=0; i<Objects.size(); i++) Objects[i].Derive_Thresholds_SiMuCrosscheck("HLT_Mu17");  }

  cout << endl <<"Closing MC and DATA files." << endl;
  for(unsigned int i=0; i<Objects.size(); i++) Objects[i].CloseFiles();
  cout << "Going to return 0 now, cya." << endl << endl;
  return 0;
}
