#include <iostream>
#include <memory>
#include <stdlib.h>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/EventHelper.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/L1Jet.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Selection.h"
#include "../include/JECAnalysisHists.h"
#include "../include/JECCrossCheckHists.h"
#include "../include/JECRunnumberHists.h"

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/LumiSelection.h> //includes also LuminosityHists.h
#include <UHH2/common/include/TriggerSelection.h>
#include "UHH2/common/include/CleaningModules.h"
#include <UHH2/common/include/NSelections.h> 
#include <UHH2/common/include/MuonIds.h> 
#include <UHH2/common/include/ElectronIds.h>
#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/NSelections.h"

#include "UHH2/BaconJets/include/selection.h"
#include "UHH2/BaconJets/include/constants.h"

#include "UHH2/BaconJets/include/LumiHists.h"

#include "TClonesArray.h"
#include "TString.h"
#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2Poly.h"

#include <stdexcept>



using namespace std;
using namespace uhh2;

class AnalysisModule_SiJetTrg: public uhh2::AnalysisModule {

  public:
    explicit AnalysisModule_SiJetTrg(uhh2::Context&);
    virtual bool process(uhh2::Event&) override;
    ~AnalysisModule_SiJetTrg();
    
  protected:
    // correctors
    std::unique_ptr<JetCorrector> jet_corrector;
    std::unique_ptr<JetCorrector>   jet_corrector_B, jet_corrector_C, jet_corrector_D, jet_corrector_E, jet_corrector_F;
    std::unique_ptr<GenericJetResolutionSmearer> jetER_smearer; 

  // cleaners
   std::unique_ptr<JetLeptonCleaner> jetleptoncleaner;
   std::unique_ptr<JetLeptonCleaner>  JLC_B, JLC_C, JLC_D, JLC_E, JLC_F;
   std::unique_ptr<JetCleaner> jetcleaner;
   std::unique_ptr<AnalysisModule>     muoSR_cleaner;   
   std::unique_ptr<AnalysisModule> eleSR_cleaner;

    // selections
    std::unique_ptr<uhh2::Selection> lumi_sel;
    std::unique_ptr<uhh2::AndSelection> metfilters_sel;     

    std::unique_ptr<uhh2::Selection> triggerSiMu_sel;

    std::unique_ptr<uhh2::Selection> trigger40_sel;
    std::unique_ptr<uhh2::Selection> trigger60_sel;
    std::unique_ptr<uhh2::Selection> trigger80_sel;
    std::unique_ptr<uhh2::Selection> trigger140_sel;
    std::unique_ptr<uhh2::Selection> trigger200_sel;
    std::unique_ptr<uhh2::Selection> trigger260_sel;
    std::unique_ptr<uhh2::Selection> trigger320_sel;
    std::unique_ptr<uhh2::Selection> trigger400_sel;
    std::unique_ptr<uhh2::Selection> trigger450_sel;
    std::unique_ptr<uhh2::Selection> trigger500_sel;

    std::unique_ptr<uhh2::Selection> trigger40_HFJEC_sel; 
    std::unique_ptr<uhh2::Selection> trigger60_HFJEC_sel; 
    std::unique_ptr<uhh2::Selection> trigger80_HFJEC_sel; 
    std::unique_ptr<uhh2::Selection> trigger140_HFJEC_sel;
    std::unique_ptr<uhh2::Selection> trigger200_HFJEC_sel;
    std::unique_ptr<uhh2::Selection> trigger260_HFJEC_sel;
    std::unique_ptr<uhh2::Selection> trigger320_HFJEC_sel;
    std::unique_ptr<uhh2::Selection> trigger400_HFJEC_sel;
    std::unique_ptr<uhh2::Selection> trigger450_HFJEC_sel;
    std::unique_ptr<uhh2::Selection> trigger500_HFJEC_sel;
  
    std::unique_ptr<LumiHists> h_monitoring_final;
  
    //// Data/MC scale factors
    std::unique_ptr<uhh2::AnalysisModule> pileupSF;
    unique_ptr<AnalysisModule>  Jet_printer, GenParticles_printer;

    Event::Handle<float> tt_jet1_ptGen;  Event::Handle<float> tt_jet2_ptGen;  Event::Handle<float> tt_jet3_ptGen;
    Event::Handle<float> tt_gen_pthat; Event::Handle<float> tt_gen_weight;  Event::Handle<float> tt_gen_PUpthat;

 //Different energy fractions in jets
    Event::Handle<float> tt_probejet_neutEmEF; Event::Handle<float> tt_probejet_neutHadEF; 
    Event::Handle<float> tt_probejet_chEmEF; Event::Handle<float> tt_probejet_chHadEF; 
    Event::Handle<float> tt_probejet_photonEF; Event::Handle<float> tt_probejet_muonEF; 

    Event::Handle<float> tt_jet1_pt;     Event::Handle<float> tt_jet2_pt;     Event::Handle<float> tt_jet3_pt;
  Event::Handle<float> tt_jet3_eta;
    Event::Handle<float> tt_jet1_ptRaw;  Event::Handle<float> tt_jet2_ptRaw;  Event::Handle<float> tt_jet3_ptRaw;
  Event::Handle<float> tt_jet1_pt_onoff_Resp;     Event::Handle<float> tt_jet2_pt_onoff_Resp;
    Event::Handle<int> tt_nvertices;
    Event::Handle<float> tt_probejet_eta;  Event::Handle<float> tt_probejet_phi; Event::Handle<float> tt_probejet_pt; Event::Handle<float> tt_probejet_ptRaw;
    Event::Handle<float> tt_barreljet_eta;  Event::Handle<float> tt_barreljet_phi; Event::Handle<float> tt_barreljet_pt; Event::Handle<float> tt_barreljet_ptRaw;
    Event::Handle<float> tt_probejet_ptgen;         Event::Handle<float> tt_barreljet_ptgen;
  
    Event::Handle<float> tt_probejet_ptptcl;         Event::Handle<float> tt_barreljet_ptptcl;   
    Event::Handle<int> tt_probejet_statusptcl;         Event::Handle<int> tt_barreljet_statusptcl;   Event::Handle<int> tt_jet3_statusptcl;   
    Event::Handle<int> tt_jet1_genID;     Event::Handle<int> tt_jet2_genID;     Event::Handle<int> tt_jet3_genID;
    Event::Handle<int> tt_jet4_genID;     Event::Handle<int> tt_jet5_genID;     Event::Handle<int> tt_jet6_genID;
    Event::Handle<float> tt_probejet_dRminParton;   Event::Handle<float> tt_barreljet_dRminParton;
    Event::Handle<int> tt_parton1_genjetID;
    Event::Handle<int> tt_parton2_genjetID;
    Event::Handle<int> tt_parton1_jetID;
    Event::Handle<int> tt_parton2_jetID;
    
    Event::Handle<float> tt_pt_ave;
    Event::Handle<float> tt_alpha;
    Event::Handle<float> tt_rel_r; Event::Handle<float> tt_mpf_r; 
    Event::Handle<float> tt_asymmetry;
    Event::Handle<float> tt_B;
    Event::Handle<float> tt_MET;
    Event::Handle<float> tt_Bgen;
    Event::Handle<float> tt_genMET;
    Event::Handle<int> tt_nPU;
    Event::Handle<int> tt_matchJetId_0;
    Event::Handle<int> tt_matchJetId_1;		
    Event::Handle<float> tt_ev_weight;
    Event::Handle<float> tt_jets_pt;//sum of jets pT
    Event::Handle<int> tt_jet_n;//number of jets
    Event::Handle<int> tt_genjet_n;//number of gen jets
    Event::Handle<int> tt_genptcl_n;//number of partons with pt>0

    Event::Handle<float> tt_rho;//event energy density
    Event::Handle<int> tt_nGoodvertices;
    Event::Handle<int> tt_partonFlavor; //only MC
    Event::Handle<int> tt_flavorBarreljet, tt_flavorProbejet, tt_flavorLeadingjet, tt_flavorSubleadingjet, tt_flavor3rdjet; //only MC
    Event::Handle<float> tt_responseBarreljet, tt_responseProbejet; //only MC
    Event::Handle<float> tt_response_leadingjet;
    Event::Handle<float> tt_had_n_Efrac, tt_had_ch_Efrac, tt_mu_Efrac, tt_ph_Efrac;
    Event::Handle<float> tt_inst_lumi, tt_integrated_lumi_in_bin, tt_integrated_lumi;
    Event::Handle<int> tt_lumibin;
    Event::Handle<int> tt_Nmuon; Event::Handle<float> tt_muon_pt;
    Event::Handle<int> tt_Nele; Event::Handle<float> tt_ele_pt;
    Event::Handle<float> tt_dR_jet3_barreljet;  Event::Handle<float> tt_dR_jet3_probejet;Event::Handle<float> tt_dR_jet3_RECO_GEN;
    Event::Handle<float> tt_dR_GenJet_GenParticle1;   Event::Handle<float> tt_dR_GenJet_GenParticle2; 
  
    Event::Handle<int> tt_triggerSiMu;
    Event::Handle<int> tt_trigger40;
    Event::Handle<int> tt_trigger60;
    Event::Handle<int> tt_trigger80;
    Event::Handle<int> tt_trigger140;
    Event::Handle<int> tt_trigger200;
    Event::Handle<int> tt_trigger260;
    Event::Handle<int> tt_trigger320;
    Event::Handle<int> tt_trigger400;
    Event::Handle<int> tt_trigger450;
    Event::Handle<int> tt_trigger500;
  
    Event::Handle<int> tt_trigger40_HF; 
    Event::Handle<int> tt_trigger60_HF;
    Event::Handle<int> tt_trigger80_HF; 
    Event::Handle<int> tt_trigger140_HF;
    Event::Handle<int> tt_trigger200_HF;
    Event::Handle<int> tt_trigger260_HF;
    Event::Handle<int> tt_trigger320_HF;
    Event::Handle<int> tt_trigger400_HF;
    Event::Handle<int> tt_trigger450_HF;
    Event::Handle<int> tt_trigger500_HF;

    Event::Handle<int> tt_run; 
    Event::Handle<int> tt_evID;
    Event::Handle<int> tt_lumiSec;
  
    Event::Handle<int> tt_jet1_l1bx; 
    Event::Handle<int> tt_jet2_l1bx; 
    Event::Handle<int> tt_jet3_l1bx;  
  
    std::unique_ptr<JECAnalysisHists> h_nocuts, h_sel, h_dijet, h_match, h_final;
    std::unique_ptr<JECAnalysisHists> h_trgSiMu ,h_trg40, h_trg60, h_trg80, h_trg140, h_trg200,h_trg260,h_trg320,h_trg400,h_trg450,h_trg500;
    std::unique_ptr<JECAnalysisHists> h_trgHF40, h_trgHF60, h_trgHF80, h_trgHF140, h_trgHF200,h_trgHF260,h_trgHF320,h_trgHF400,h_trgHF450,h_trgHF500;
    std::unique_ptr<LuminosityHists> h_lumi_nocuts, h_lumi_sel, h_lumi_dijet, h_lumi_match, h_lumi_final;    
    std::unique_ptr<LuminosityHists> h_lumi_TrigSiMu,h_lumi_Trig40, h_lumi_Trig60, h_lumi_Trig80, h_lumi_Trig140, h_lumi_Trig200, h_lumi_Trig260, h_lumi_Trig320, h_lumi_Trig400,h_lumi_Trig450, h_lumi_Trig500;
    std::unique_ptr<LuminosityHists> h_lumi_TrigHF40, h_lumi_TrigHF60, h_lumi_TrigHF80, h_lumi_TrigHF140, h_lumi_TrigHF200, h_lumi_TrigHF260, h_lumi_TrigHF320, h_lumi_TrigHF400,h_lumi_TrigHF450, h_lumi_TrigHF500;
    std::unique_ptr<JECRunnumberHists> h_runnr_input;
    std::unique_ptr<JECCrossCheckHists> h_input,h_lumisel, h_beforeCleaner,h_afterCleaner,h_2jets,h_beforeJEC,h_afterJEC,h_afterJER,h_afterMET,h_beforeTriggerData,h_afterTriggerData,h_beforeFlatFwd,h_afterFlatFwd,h_afterPtEtaReweight,h_afterLumiReweight,h_afterUnflat,h_afternVts;
    uhh2bacon::Selection sel;

    bool debug;  
    bool isMC, split_JEC_DATA, split_JEC_MC, ClosureTest, apply_weights, apply_lumiweights, apply_unflattening, apply_smear, apply_METoverPt_cut, apply_EtaPhi_cut, trigger_central, trigger_fwd, ts, onlyBtB, apply_L1seed_from_bx1_filter;
    double lumiweight;
    string jetLabel;
  TString dataset_version, JEC_Version, MC_SF_JER_name;
    JetId Jet_PFID;
    int n_evt;
    std::unique_ptr<TFile> f_weights;
    
    std::map<run_lumi, double> rl2lumi;
    std::map<run_lumi, double> rl2intlumi;
    TBranch * brun ;
    TBranch * blumiblock;
    TBranch * bilumi;
    double integrated_lumi;
    vector<run_lumi> upper_binborders_runnrs;
    vector<double> lumi_in_bins;

    double L1METptThresh;
    double eta_thresh_low;
    double eta_thresh_high;

  std::vector<uhh2bacon::run_lumi_ev>  unprefirableSummary;
    bool useUnprefireable;

  uhh2::GenericEvent::Handle<std::vector<L1Jet>> handle_l1jet_seeds;
  
  };

  AnalysisModule_SiJetTrg::AnalysisModule_SiJetTrg(uhh2::Context & ctx) :
		  sel(ctx)
  {
    try{
      debug = ctx.get("Debug") == "true";
    }
    catch(const runtime_error& error){
      debug = false;
    }
    
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

    cout << "start" << endl;

    
    try{
      useUnprefireable = ctx.get("UseUnprefirable") == "true";
    }
    catch(const runtime_error& error){
      useUnprefireable = false;
    }
    if(useUnprefireable){
      cout<<"prepare the list of unprefireable events"<<endl;
      string unprefFile="/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggersExamination/data/UnprefirableEventList_JetHT_Run2017BtoF.root";
	cout<<"  will use the file "<< unprefFile <<endl;

	TFile* file_FilteredEvents = new TFile(unprefFile.c_str(),"READ","unprefirableEventSummary");
      TTree * filtered_tree = dynamic_cast<TTree*>(file_FilteredEvents->Get("tree"));
      // fetch branches we need
      TBranch * brun = filtered_tree->GetBranch("run");
      TBranch * blumiblock = filtered_tree->GetBranch("lumi");
      TBranch * beventid = filtered_tree->GetBranch("event");
      
      uhh2bacon::run_lumi_ev rle;
      brun->SetAddress(&rle.run);
      blumiblock->SetAddress(&rle.lumiblock);
      beventid->SetAddress(&rle.event);

      auto ientries = filtered_tree->GetEntries();
      for(auto ientry = 0l; ientry < ientries; ientry++){
	for(auto b : {brun, blumiblock, beventid}){
	  b->GetEntry(ientry);
	}
	unprefirableSummary.push_back(rle);
      }
      cout<<"list of unprefireable events is prepared, found "<<unprefirableSummary.size()<<" events"<<endl;
    }

    isMC = (ctx.get("dataset_type") == "MC");
    
    //// COMMON MODULES
    
    L1METptThresh = stod(ctx.get("L1METptThresh"));
    eta_thresh_low = stod(ctx.get("eta_thresh_low"));
      
    if(!isMC) lumi_sel.reset(new LumiSelection(ctx));
    /* MET filters */ 
    metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters")); 
    metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices"); 
    metfilters_sel->add<TriggerSelection>("globalSuperTightHalo2016Filter", "Flag_globalSuperTightHalo2016Filter"); 
    metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");        
    metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
    metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter"); 
    // metfilters_sel->add<TriggerSelection>("CSCTightHalo2016Filter", "Flag_CSCTightHalo2016Filter"); 
    metfilters_sel->add<TriggerSelection>("BadPFMuonFilter", "Flag_BadPFMuonFilter");
    metfilters_sel->add<TriggerSelection>("BadChargedCandidateFilter", "Flag_BadChargedCandidateFilter");
    metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
    metfilters_sel->add<TriggerSelection>("ecalBadCalibFilter","Flag_ecalBadCalibFilter");
   
    Jet_PFID = JetPFID(JetPFID::WP_TIGHT);
    jetcleaner.reset(new JetCleaner(ctx, Jet_PFID));
    
//Lepton cleaner
    MuonId muoSR;
    muoSR = AndId<Muon>(MuonID(Muon::CutBasedIdTight),PtEtaCut  (15.0, 2.4));
    const ElectronId eleSR(AndId<Electron>(ElectronID_MVA_Fall17_loose_noIso , PtEtaSCCut(15.0, 2.4)));
    muoSR_cleaner.reset(new     MuonCleaner(muoSR));
    eleSR_cleaner.reset(new ElectronCleaner(eleSR)); 

//#############################################  Trigger  #########################################################
    trigger_central = (ctx.get("Trigger_Central") == "true");
    trigger_fwd     = (ctx.get("Trigger_FWD") == "true");
    ts  = (ctx.get("Trigger_Single") == "true"); //if true use single jet trigger, if false di jet trigger TODO collapse the SiJet and DiJEt AnalysisModules into one
    // ts = true;
    onlyBtB = (ctx.get("Only_BtB") == "true");
    if(debug) cout<<"onlyBtb is "<<onlyBtB<<endl;
    
#define GET_RESET_TRIGGER(trg_name)       \
  const std::string& trg_name = ctx.get( #trg_name , "NULL"); \     
  if ( trg_name != "NULL") trg_name##_sel.reset(new TriggerSelection( trg_name ));\
  else trg_name##_sel.reset(new uhh2::AndSelection(ctx)); \
    
    if(!isMC){
    const std::string& triggerSiMu = ctx.get("triggerSiMu", "NULL");

      if(triggerSiMu != "NULL") triggerSiMu_sel.reset(new TriggerSelection(triggerSiMu));
      else triggerSiMu_sel.reset(new uhh2::AndSelection(ctx));
      
        GET_RESET_TRIGGER(trigger40)
	GET_RESET_TRIGGER(trigger60)
	GET_RESET_TRIGGER(trigger80)
	GET_RESET_TRIGGER(trigger140)
	GET_RESET_TRIGGER(trigger200)
	GET_RESET_TRIGGER(trigger260)
	GET_RESET_TRIGGER(trigger320)
	GET_RESET_TRIGGER(trigger400)
	GET_RESET_TRIGGER(trigger450)
	GET_RESET_TRIGGER(trigger500)
	  
        GET_RESET_TRIGGER(trigger40_HFJEC)
	GET_RESET_TRIGGER(trigger60_HFJEC)
	GET_RESET_TRIGGER(trigger80_HFJEC)
	GET_RESET_TRIGGER(trigger140_HFJEC)
	GET_RESET_TRIGGER(trigger200_HFJEC)
	GET_RESET_TRIGGER(trigger260_HFJEC)
	GET_RESET_TRIGGER(trigger320_HFJEC)
	GET_RESET_TRIGGER(trigger400_HFJEC)
	GET_RESET_TRIGGER(trigger450_HFJEC)
	GET_RESET_TRIGGER(trigger500_HFJEC)
    }

    //new
    jetLabel = ctx.get("JetLabel");
    dataset_version = ctx.get("dataset_version");
    ClosureTest = (ctx.get("ClosureTest") == "true");
    apply_METoverPt_cut = (ctx.get("METoverPt_cut") == "true");
    apply_EtaPhi_cut = (ctx.get("EtaPhi_cut") == "true");
    JEC_Version = ctx.get("JEC_Version");

    apply_L1seed_from_bx1_filter =  (ctx.get("Apply_L1Seed_From_BX1_Filter") == "true" && !isMC);

    split_JEC_MC   = false; //Different MC corrections only existed for Spring16_25ns_V8* 
    split_JEC_DATA = true; //TODO check the JEC!!!

     if(debug) std::cout<<"isMC: "<<isMC<<"  split_JEC_MC: "<<split_JEC_MC<<"  split_JEC_DATA: "<<split_JEC_DATA <<"   ClosureTest: "<<ClosureTest<<std::endl;   
    
    std::vector<std::string> JEC_corr;
    std::vector<std::string> JEC_corr_L1RC;
    std::vector<std::string> JEC_corr_B, JEC_corr_C, JEC_corr_D, JEC_corr_E, JEC_corr_F;
    std::vector<std::string> JEC_corr_B_L1RC, JEC_corr_C_L1RC, JEC_corr_D_L1RC, JEC_corr_E_L1RC, JEC_corr_F_L1RC;
   
#define IF_MAKE_JEC_VARS_MC(jecv)				    \
  if(JEC_Version == #jecv){			    \
  JEC_corr               = JERFiles::jecv##_L123_AK4PFchs_MC; \
				       				\
  JEC_corr_L1RC          = JERFiles::jecv##_L1RC_AK4PFchs_MC;	\
	\
  }
    
    if(isMC){
      //for MC
      if(jetLabel == "AK4CHS"){
	IF_MAKE_JEC_VARS_MC(Fall17_17Nov2017_V11)
	  else IF_MAKE_JEC_VARS_MC(Fall17_17Nov2017_V23)
       }

	  else throw runtime_error("In AnalysisModule_SiJetTrg.cxx: Invalid JEC_Version for deriving residuals on AK4CHS, MC specified ("+JEC_Version+") ");
	}
    else {

#define IF_MAKE_JEC_VARS_CLOSURE(jecv)				    \
  if(JEC_Version == #jecv){			    \
  JEC_corr_B               = JERFiles::jecv##_B_L123_AK4PFchs_DATA; \
  JEC_corr_C               = JERFiles::jecv##_C_L123_AK4PFchs_DATA; \
  JEC_corr_D               = JERFiles::jecv##_D_L123_AK4PFchs_DATA; \
  JEC_corr_E               = JERFiles::jecv##_E_L123_AK4PFchs_DATA; \
  JEC_corr_F               = JERFiles::jecv##_F_L123_AK4PFchs_DATA; \
				       				\
  JEC_corr_B_L1RC          = JERFiles::jecv##_B_L1RC_AK4PFchs_DATA;	\
  JEC_corr_C_L1RC          = JERFiles::jecv##_C_L1RC_AK4PFchs_DATA;	\
  JEC_corr_D_L1RC          = JERFiles::jecv##_D_L1RC_AK4PFchs_DATA;	\
  JEC_corr_E_L1RC          = JERFiles::jecv##_E_L1RC_AK4PFchs_DATA;	\
  JEC_corr_F_L1RC          = JERFiles::jecv##_F_L1RC_AK4PFchs_DATA;	\
  }									\


#define IF_MAKE_JEC_VARS_NO_CLOSURE(jecv)					\
  if(JEC_Version == #jecv){			    \
  JEC_corr_B               = JERFiles::jecv##_B_L123_noRes_AK4PFchs_DATA; \
  JEC_corr_C               = JERFiles::jecv##_C_L123_noRes_AK4PFchs_DATA; \
  JEC_corr_D               = JERFiles::jecv##_D_L123_noRes_AK4PFchs_DATA; \
  JEC_corr_E               = JERFiles::jecv##_E_L123_noRes_AK4PFchs_DATA; \
  JEC_corr_F               = JERFiles::jecv##_F_L123_noRes_AK4PFchs_DATA; \
				       				\
  JEC_corr_B_L1RC          = JERFiles::jecv##_B_L1RC_AK4PFchs_DATA;	\
  JEC_corr_C_L1RC          = JERFiles::jecv##_C_L1RC_AK4PFchs_DATA;	\
  JEC_corr_D_L1RC          = JERFiles::jecv##_D_L1RC_AK4PFchs_DATA;	\
  JEC_corr_E_L1RC          = JERFiles::jecv##_E_L1RC_AK4PFchs_DATA;	\
  JEC_corr_F_L1RC          = JERFiles::jecv##_F_L1RC_AK4PFchs_DATA;	\
  }\
      
      //for DATA
      if(jetLabel == "AK4CHS"){
	if(!ClosureTest){
	  //residuals
	  IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V11) 
	  else IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V23) 
	    else IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V24)
	    else IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V25) 
	    else IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V26) 
	    else IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V27)  
	    else IF_MAKE_JEC_VARS_NO_CLOSURE(Fall17_17Nov2017_V28)   
	    else throw runtime_error("In AnalysisModule_SiJetTrg.cxx: Invalid JEC_Version for deriving residuals on AK4CHS, DATA specified.");
	}
	else{
	  IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V11)  
	  else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V23) 
	  else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V24) 
	  else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V25) 
	    else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V26) 
	      else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V27)
	      else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V28) 
	      else IF_MAKE_JEC_VARS_CLOSURE(Fall17_17Nov2017_V31)      		   		
	 else throw runtime_error("In AnalysisModule_SiJetTrg.cxx: Invalid JEC_Version for closure test on AK4CHS, DATA specified.");
	}
      }
    }
      
	//DATA
	if(!isMC){
	  if(split_JEC_DATA){
	    jet_corrector_B.reset(new JetCorrector(ctx, JEC_corr_B, JEC_corr_B_L1RC));
	    JLC_B.reset(new JetLeptonCleaner(ctx, JEC_corr_B));
	    jet_corrector_C.reset(new JetCorrector(ctx, JEC_corr_C, JEC_corr_C_L1RC));
	    JLC_C.reset(new JetLeptonCleaner(ctx, JEC_corr_C));
	    jet_corrector_D.reset(new JetCorrector(ctx, JEC_corr_D, JEC_corr_D_L1RC));
	    JLC_D.reset(new JetLeptonCleaner(ctx, JEC_corr_D));
	    jet_corrector_E.reset(new JetCorrector(ctx, JEC_corr_E, JEC_corr_E_L1RC));
	    JLC_E.reset(new JetLeptonCleaner(ctx, JEC_corr_E));
	    jet_corrector_F.reset(new JetCorrector(ctx, JEC_corr_F, JEC_corr_F_L1RC));
	    JLC_F.reset(new JetLeptonCleaner(ctx, JEC_corr_F));
	  }
	  else{
	    jet_corrector.reset(new JetCorrector(ctx, JEC_corr, JEC_corr_L1RC));
	    jetleptoncleaner.reset(new JetLeptonCleaner(ctx, JEC_corr));
	  }
	}
	//MC
	else if(isMC){
	  jet_corrector.reset(new JetCorrector(ctx, JEC_corr, JEC_corr_L1RC));
	    jetleptoncleaner.reset(new JetLeptonCleaner(ctx, JEC_corr));
	    cout << "setting up jet_corrector and JLC for MC, non-split JEC." << endl;
	}
    
//JER Smearing for corresponding JEC-Version
      if(isMC){
	// else if(JEC_Version == "Fall17_17Nov2017_V27") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets",  JERSmearing::SF_13TeV_Summer16_25nsV1,"Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"));
	// else if(JEC_Version == "Fall17_17Nov2017_V11") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets",  JERSmearing::SF_13TeV_Fall17,"Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt"));
	if(JEC_Version == "Fall17_17Nov2017_V23"){
	  if(MC_SF_JER_name == "Fall17_V2_RunBC") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets",  JERSmearing::SF_13TeV_Fall17_V2_RunBC,"Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt"));
	  else if(MC_SF_JER_name == "Fall17_V2_RunDE") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets",  JERSmearing::SF_13TeV_Fall17_V2_RunDE,"Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt"));
	  else if(MC_SF_JER_name == "Fall17_V2_RunF") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets",  JERSmearing::SF_13TeV_Fall17_V2_RunF,"Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt"));
	  else jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets",  JERSmearing::SF_13TeV_Fall17_V2_RunBCDEF,"Fall17_25nsV1_MC_PtResolution_AK4PFchs.txt"));
	}
	else cout << "In AnalysisModule_SiJetTrg.cxx: When setting up JER smearer, invalid 'JEC_Version' was specified."<<endl;
      }
     
    //output
    ctx.undeclare_all_event_output();   
    // //pileup (define it after undeclaring all other variables to keep the weights in the output)
    // pileupSF.reset(new MCPileupReweight(ctx));

    //    tt_dijet_event = ctx.declare_event_output<dijet_event>("dijet");
    //Store only vars needed for the dijet analysis

    tt_gen_pthat = ctx.declare_event_output<float>("gen_pthat");
    tt_gen_PUpthat = ctx.declare_event_output<float>("gen_PUpthat");
    tt_gen_weight = ctx.declare_event_output<float>("gen_weight");
    tt_jet1_pt = ctx.declare_event_output<float>("jet1_pt");
    tt_jet2_pt = ctx.declare_event_output<float>("jet2_pt");
    tt_jet3_pt = ctx.declare_event_output<float>("jet3_pt");
    tt_jet3_eta = ctx.declare_event_output<float>("jet3_eta");
    tt_jet1_ptRaw = ctx.declare_event_output<float>("jet1_ptRaw");
    tt_jet2_ptRaw = ctx.declare_event_output<float>("jet2_ptRaw");
    tt_jet3_ptRaw = ctx.declare_event_output<float>("jet3_ptRaw");
    tt_jet1_ptGen = ctx.declare_event_output<float>("jet1_ptGen");
    tt_jet2_ptGen = ctx.declare_event_output<float>("jet2_ptGen");
    tt_jet3_ptGen = ctx.declare_event_output<float>("jet3_ptGen");

    tt_jet1_pt_onoff_Resp = ctx.declare_event_output<float>("jet1_pt_onoff_Resp");
    tt_jet2_pt_onoff_Resp = ctx.declare_event_output<float>("jet2_pt_onoff_Resp");

    tt_probejet_neutEmEF = ctx.declare_event_output<float>("probejet_neutEmEF");
    tt_probejet_neutHadEF = ctx.declare_event_output<float>("probejet_neutHadEF");
    tt_probejet_chEmEF = ctx.declare_event_output<float>("probejet_chEmEF");
    tt_probejet_chHadEF = ctx.declare_event_output<float>("probejet_chHadEF");
    tt_probejet_photonEF = ctx.declare_event_output<float>("probejet_photonEF");
    tt_probejet_muonEF = ctx.declare_event_output<float>("probejet_muonEF");

    tt_nvertices = ctx.declare_event_output<int>("nvertices");
    tt_nGoodvertices = ctx.declare_event_output<int>("nGoodvertices");
    tt_probejet_eta = ctx.declare_event_output<float>("probejet_eta");
    tt_probejet_phi = ctx.declare_event_output<float>("probejet_phi");
    tt_probejet_pt = ctx.declare_event_output<float>("probejet_pt");
    tt_probejet_ptgen = ctx.declare_event_output<float>("probejet_ptgen");
    tt_probejet_ptRaw = ctx.declare_event_output<float>("probejet_ptRaw");
    tt_probejet_ptptcl = ctx.declare_event_output<float>("probejet_ptptcl");
    tt_barreljet_eta = ctx.declare_event_output<float>("barreljet_eta");
    tt_barreljet_phi = ctx.declare_event_output<float>("barreljet_phi");
    tt_barreljet_pt = ctx.declare_event_output<float>("barreljet_pt");
    tt_barreljet_ptgen = ctx.declare_event_output<float>("barreljet_ptgen");
    tt_barreljet_ptRaw = ctx.declare_event_output<float>("barreljet_ptRaw");
    tt_barreljet_ptptcl = ctx.declare_event_output<float>("barreljet_ptptcl");
    tt_barreljet_statusptcl = ctx.declare_event_output<int>("barreljet_status_ptcl");
    tt_probejet_statusptcl = ctx.declare_event_output<int>("probejet_status_ptcl");
    tt_jet3_statusptcl = ctx.declare_event_output<int>("jet3_status_ptcl");
    tt_probejet_dRminParton = ctx.declare_event_output<float>("probejet_dRminParton");
    tt_barreljet_dRminParton = ctx.declare_event_output<float>("barreljet_dRminParton");
    tt_pt_ave = ctx.declare_event_output<float>("pt_ave");
    tt_alpha = ctx.declare_event_output<float>("alpha");
    tt_rel_r = ctx.declare_event_output<float>("rel_r");
    tt_mpf_r = ctx.declare_event_output<float>("mpf_r");
    tt_asymmetry = ctx.declare_event_output<float>("asymmetry");
    tt_B = ctx.declare_event_output<float>("B");
    tt_MET = ctx.declare_event_output<float>("MET");
    tt_Bgen = ctx.declare_event_output<float>("genB");
    tt_genMET = ctx.declare_event_output<float>("genMET");
    tt_nPU = ctx.declare_event_output<int>("nPU");
    tt_matchJetId_0 = ctx.declare_event_output<int>("matchJetId_0");
    tt_matchJetId_1 = ctx.declare_event_output<int>("matchJetId_1");   
    tt_ev_weight = ctx.declare_event_output<float>("weight");
    tt_jets_pt= ctx.declare_event_output<float>("sum_jets_pt");
    tt_jet_n= ctx.declare_event_output<int>("Njet");
    tt_genjet_n= ctx.declare_event_output<int>("Ngenjet");
    tt_genptcl_n = ctx.declare_event_output<int>("Nptcl");
    tt_rho = ctx.declare_event_output<float>("rho");
    tt_partonFlavor = ctx.declare_event_output<int>("partonFlavor");
    tt_flavorBarreljet = ctx.declare_event_output<int>("flavorBarreljet");
    tt_flavor3rdjet = ctx.declare_event_output<int>("flavor3rdjet");
    tt_responseBarreljet = ctx.declare_event_output<float>("responseBarreljet_genp");
    tt_flavorProbejet = ctx.declare_event_output<int>("flavorProbejet");
    tt_responseProbejet = ctx.declare_event_output<float>("responseProbejet_genp");
    tt_flavorLeadingjet = ctx.declare_event_output<int>("flavorLeadingjet");
    tt_flavorSubleadingjet = ctx.declare_event_output<int>("flavorSubleadingjet");
    tt_response_leadingjet = ctx.declare_event_output<float>("leadingjet_response");
    tt_inst_lumi = ctx.declare_event_output<float>("instantaneous_lumi");
    tt_integrated_lumi_in_bin = ctx.declare_event_output<float>("integrated_lumi_in_bin");
    tt_lumibin = ctx.declare_event_output<int>("lumibin");
    tt_Nmuon = ctx.declare_event_output<int>("Nmuon");
    tt_muon_pt = ctx.declare_event_output<float>("muon_pt");
    tt_ele_pt = ctx.declare_event_output<float>("electron_pt");
    tt_Nele = ctx.declare_event_output<int>("Nelectron");
    tt_integrated_lumi = ctx.declare_event_output<float>("integrated_lumi");

    tt_jet1_genID =  ctx.declare_event_output<int>("jet1_genID");
    tt_jet2_genID =  ctx.declare_event_output<int>("jet2_genID");
    tt_jet3_genID =  ctx.declare_event_output<int>("jet3_genID");
    tt_jet4_genID =  ctx.declare_event_output<int>("jet4_genID");
    tt_jet5_genID =  ctx.declare_event_output<int>("jet5_genID");
    tt_jet6_genID =  ctx.declare_event_output<int>("jet6_genID");

    tt_parton1_genjetID =  ctx.declare_event_output<int>("parton1_genjetID");
    tt_parton2_genjetID =  ctx.declare_event_output<int>("parton2_genjetID");
    tt_parton1_jetID =  ctx.declare_event_output<int>("parton1_jetID");
    tt_parton2_jetID =  ctx.declare_event_output<int>("parton2_jetID");

    tt_run = ctx.declare_event_output<int>("run");
    tt_evID = ctx.declare_event_output<int>("eventID");
    tt_lumiSec = ctx.declare_event_output<int>("lumi_sec");

    tt_jet1_l1bx = ctx.declare_event_output<int>("jet1_l1bx");
    tt_jet2_l1bx = ctx.declare_event_output<int>("jet1_l2bx");
    tt_jet3_l1bx = ctx.declare_event_output<int>("jet1_l3bx");
    
    tt_triggerSiMu = ctx.declare_event_output<int>("triggerSiMu");

    tt_trigger40 = ctx.declare_event_output<int>("trigger40");
    tt_trigger60 = ctx.declare_event_output<int>("trigger60");
    tt_trigger80 = ctx.declare_event_output<int>("trigger80");
    tt_trigger140 = ctx.declare_event_output<int>("trigger140");
    tt_trigger200 = ctx.declare_event_output<int>("trigger200");
    tt_trigger260 = ctx.declare_event_output<int>("trigger260");
    tt_trigger320 = ctx.declare_event_output<int>("trigger320");
    tt_trigger400 = ctx.declare_event_output<int>("trigger400");
    tt_trigger450 = ctx.declare_event_output<int>("trigger450");
    tt_trigger500 = ctx.declare_event_output<int>("trigger500");

    tt_trigger40_HF = ctx.declare_event_output<int>("trigger40_HF");
    tt_trigger60_HF = ctx.declare_event_output<int>("trigger60_HF");
    tt_trigger80_HF = ctx.declare_event_output<int>("trigger80_HF");
    tt_trigger140_HF = ctx.declare_event_output<int>("trigger140_HF");
    tt_trigger200_HF = ctx.declare_event_output<int>("trigger200_HF");
    tt_trigger260_HF = ctx.declare_event_output<int>("trigger260_HF");
    tt_trigger320_HF = ctx.declare_event_output<int>("trigger320_HF");
    tt_trigger400_HF = ctx.declare_event_output<int>("trigger400_HF");
    tt_trigger450_HF = ctx.declare_event_output<int>("trigger450_HF");
    tt_trigger500_HF = ctx.declare_event_output<int>("trigger500_HF");

    
    tt_dR_jet3_barreljet = ctx.declare_event_output<float>("dR_jet3_barreljet");
    tt_dR_jet3_probejet = ctx.declare_event_output<float>("dR_jet3_probejet");
    tt_dR_jet3_RECO_GEN = ctx.declare_event_output<float>("dR_jet3_RECO_GEN");
    tt_dR_GenJet_GenParticle1 = ctx.declare_event_output<float>("dR_GenJet_GenParticle1"); 
    tt_dR_GenJet_GenParticle2 = ctx.declare_event_output<float>("dR_GenJet_GenParticle2");

    h_runnr_input.reset(new JECRunnumberHists(ctx,"Runnr_input"));
    h_input.reset(new JECCrossCheckHists(ctx,"CrossCheck_input"));
    h_lumisel.reset(new JECCrossCheckHists(ctx,"CrossCheck_lumisel"));
    h_beforeCleaner.reset(new JECCrossCheckHists(ctx,"CrossCheck_beforeCleaner"));
    h_afterCleaner.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterCleaner"));
    h_2jets.reset(new JECCrossCheckHists(ctx,"CrossCheck_2jets"));
    h_beforeJEC.reset(new JECCrossCheckHists(ctx,"CrossCheck_beforeJEC"));
    h_afterJEC.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterJEC"));
    h_afterJER.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterJER"));
    h_afterMET.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterMET"));
    h_beforeTriggerData.reset(new JECCrossCheckHists(ctx,"CrossCheck_beforeTriggerData"));
    h_afterTriggerData.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterTriggerData"));
    h_beforeFlatFwd.reset(new JECCrossCheckHists(ctx,"CrossCheck_beforeFlatFwd"));
    h_afterFlatFwd.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterFlatFwd"));
    h_afterPtEtaReweight.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterPtEtaReweight"));
    h_afterLumiReweight.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterLumiReweight"));
    h_afterUnflat.reset(new JECCrossCheckHists(ctx,"CrossCheck_afterUnflat"));
    h_afternVts.reset(new JECCrossCheckHists(ctx,"CrossCheck_afternVts"));
    h_nocuts.reset(new JECAnalysisHists(ctx,"NoCuts"));
    h_dijet.reset(new JECAnalysisHists(ctx,"diJet"));
    h_match.reset(new JECAnalysisHists(ctx,"JetMatching"));
    h_sel.reset(new JECAnalysisHists(ctx,"Selection"));
    h_final.reset(new JECAnalysisHists(ctx,"Final"));
   
    //Single Jet Trigger Studies
    
    h_trgSiMu.reset(new JECAnalysisHists(ctx,ctx.get("triggerSiMu_DirName", "NULL")));

    h_trg40.reset(new JECAnalysisHists(ctx,"HLT_PFJet40"));
    h_trg60.reset(new JECAnalysisHists(ctx,"HLT_PFJet60"));
    h_trg80.reset(new JECAnalysisHists(ctx,"HLT_PFJet80"));
    h_trg140.reset(new JECAnalysisHists(ctx,"HLT_PFJet140"));
    h_trg200.reset(new JECAnalysisHists(ctx,"HLT_PFJet200"));
    h_trg260.reset(new JECAnalysisHists(ctx,"HLT_PFJet260"));
    h_trg320.reset(new JECAnalysisHists(ctx,"HLT_PFJet320"));
    h_trg400.reset(new JECAnalysisHists(ctx,"HLT_PFJet400"));
    h_trg450.reset(new JECAnalysisHists(ctx,"HLT_PFJet450"));
    h_trg500.reset(new JECAnalysisHists(ctx,"HLT_PFJet500"));
 
    h_trgHF40.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet40_HFJEC"));
    h_trgHF60.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet60_HFJEC"));
    h_trgHF80.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet80_HFJEC"));
    h_trgHF140.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet140_HFJEC"));
    h_trgHF200.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet200_HFJEC"));
    h_trgHF260.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet260_HFJEC"));
    h_trgHF320.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet320_HFJEC"));
    h_trgHF400.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet400_HFJEC"));
    h_trgHF450.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet450_HFJEC"));
    h_trgHF500.reset(new JECAnalysisHists(ctx,"HLT_DiPFJet500_HFJEC"));  
    
    h_lumi_nocuts.reset(new LuminosityHists(ctx,"Lumi_noCuts"));  
    h_lumi_sel.reset(new LuminosityHists(ctx,"Lumi_Selection"));
    h_lumi_dijet.reset(new LuminosityHists(ctx,"Lumi_diJet"));
    h_lumi_match.reset(new LuminosityHists(ctx,"Lumi_JetMatching"));
    h_lumi_final.reset(new LuminosityHists(ctx,"Lumi_Final"));

    h_lumi_TrigSiMu.reset(new LuminosityHists(ctx,"Lumi_TrigSiMu"));   
     
    h_lumi_Trig40.reset(new LuminosityHists(ctx,"Lumi_Trig40"));  
    h_lumi_Trig60.reset(new LuminosityHists(ctx,"Lumi_Trig60")); 
    h_lumi_Trig80.reset(new LuminosityHists(ctx,"Lumi_Trig80")); 
    h_lumi_Trig140.reset(new LuminosityHists(ctx,"Lumi_Trig140")); 
    h_lumi_Trig200.reset(new LuminosityHists(ctx,"Lumi_Trig200")); 
    h_lumi_Trig260.reset(new LuminosityHists(ctx,"Lumi_Trig260")); 
    h_lumi_Trig320.reset(new LuminosityHists(ctx,"Lumi_Trig320")); 
    h_lumi_Trig400.reset(new LuminosityHists(ctx,"Lumi_Trig400")); 
    h_lumi_Trig450.reset(new LuminosityHists(ctx,"Lumi_Trig450"));
    h_lumi_Trig500.reset(new LuminosityHists(ctx,"Lumi_Trig500"));
     
    h_lumi_TrigHF40.reset(new LuminosityHists(ctx,"Lumi_TriHF40"));  
    h_lumi_TrigHF60.reset(new LuminosityHists(ctx,"Lumi_TriHF60")); 
    h_lumi_TrigHF80.reset(new LuminosityHists(ctx,"Lumi_TriHF80")); 
    h_lumi_TrigHF140.reset(new LuminosityHists(ctx,"Lumi_TrigHF140")); 
    h_lumi_TrigHF200.reset(new LuminosityHists(ctx,"Lumi_TrigHF200")); 
    h_lumi_TrigHF260.reset(new LuminosityHists(ctx,"Lumi_TrigHF260")); 
    h_lumi_TrigHF320.reset(new LuminosityHists(ctx,"Lumi_TrigHF320")); 
    h_lumi_TrigHF400.reset(new LuminosityHists(ctx,"Lumi_TrigHF400")); 
    h_lumi_TrigHF450.reset(new LuminosityHists(ctx,"Lumi_TrigHF450"));
    h_lumi_TrigHF500.reset(new LuminosityHists(ctx,"Lumi_TrigHF500"));

    h_monitoring_final.reset(new LumiHists(ctx, "Monitoring_Final"));
    
    Jet_printer.reset(new JetPrinter("Jet-Printer", 0));
    GenParticles_printer.reset(new GenParticlesPrinter(ctx));
 
    n_evt = 0;
    TString name_weights = ctx.get("MC_Weights_Path");
    apply_weights = (ctx.get("Apply_Weights") == "true" && isMC);
    if (debug) cout<<"Apply Weights: "<<apply_weights<<endl;
    if(apply_weights){
      if(isMC && dataset_version.Contains("RunB")){
    	  name_weights += "MC_ReWeights_RunB_17Nov17_2017_withL1BXsaved_METCorrectionCorrected__ptBinned.root";
      }
      else if(isMC && dataset_version.Contains("RunC")){
    	  name_weights += "MC_ReWeights_RunC_17Nov17_2017_withL1BXsaved_METCorrectionCorrected__ptBinned.root";
      }
      else if(isMC && dataset_version.Contains("RunD")){
    	  name_weights += "MC_ReWeights_RunD_17Nov17_2017_withL1BXsaved_METCorrectionCorrected__ptBinned.root";
      }
      else if(isMC && dataset_version.Contains("RunE")){
    	  name_weights += "MC_ReWeights_RunE_17Nov17_2017_withL1BXsaved_METCorrectionCorrected__ptBinned.root";
      }
      else if(isMC && dataset_version.Contains("RunF")){
	if(dataset_version.Contains("QCDPt15to7000")){
    	  name_weights += "MC_ReWeights_RunF.root";
	}
	else  name_weights += "MC_ReWeights_RunF_17Nov17_2017_withL1BXsaved_METCorrectionCorrected__ptBinned.root";
      }
      else{
	cout<<"No MC weights found? dataset_version is "<<dataset_version<<endl;
      }
      cout<<"Using MC weights from "<<name_weights<<endl;
      f_weights.reset(new TFile(name_weights,"READ"));
    }
    
    apply_lumiweights = (ctx.get("Apply_Lumiweights") == "true" && isMC);
    apply_unflattening = (ctx.get("Apply_Unflattening") == "true" && isMC);
    apply_smear = (ctx.get("Apply_MC_Smear")=="true" && isMC);
    
    MC_SF_JER_name = ctx.get("MC_Sf_Jer");
    
    if(apply_weights && apply_lumiweights) throw runtime_error("In AnalysisModule_SiJetTrg.cxx: 'apply_weights' and 'apply_lumiweights' are set 'true' simultaneously. This won't work, please decide on one");
    if(isMC){
      lumiweight = string2double(ctx.get("dataset_lumi")); //TODO this is not the lumiweight but lust the lumi, normalisation to it is commented out at the moment
      cout<<"will be scaled my lumi "<<lumiweight<<endl;
    }

    
    string lumifile = ctx.get("lumi_file");
    std::unique_ptr<TFile> file(TFile::Open(lumifile.c_str(), "read"));
    TTree * tree = dynamic_cast<TTree*>(file->Get("AnalysisTree"));
    if(!tree){
      throw runtime_error("LuminosityHists: Did not find TTree 'AnalysisTree' in file ;" + lumifile + "'");
    }
    // only fetch branches we really need:
    brun = tree->GetBranch("run");
    blumiblock = tree->GetBranch("luminosityBlock");
    bilumi = tree->GetBranch("intgRecLumi");

    run_lumi rl;
    double ilumi;
    double intlumi_pb = 0;
    brun->SetAddress(&rl.run);
    blumiblock->SetAddress(&rl.lumiblock);
    bilumi->SetAddress(&ilumi);

    //loop over all lumiblocks to save the map between run/lumiblock and stored lumi of the lumiblock (to be divided by 23s)
    auto ientries = tree->GetEntries();
    for(auto ientry = 0l; ientry < ientries; ientry++){
      for(auto b : {brun, blumiblock, bilumi}){
	b->GetEntry(ientry);
      }
      double ilumi_pb = ilumi * 1e-6; // convert units in file (microbarn) to pb.
      intlumi_pb += ilumi_pb;
      rl2lumi.insert(make_pair(rl, ilumi_pb));
      rl2intlumi.insert(make_pair(rl, intlumi_pb));
    }
    
    double ilumi_current_bin = 0.0;
    run_lumi last_entry;
    for(const auto & rl : rl2lumi){
      ilumi_current_bin += rl.second;
      if(ilumi_current_bin >= 2000){
	upper_binborders_runnrs.push_back(rl.first);
	lumi_in_bins.push_back(ilumi_current_bin - rl.second);
	ilumi_current_bin = ilumi_current_bin - 2000;
      }
      last_entry = rl.first;
    }
    upper_binborders_runnrs.push_back(last_entry); //this is not exactly an UPPER limit because it is equal to the highest possible entry, not greater than it...created exception for this case.
    lumi_in_bins.push_back(ilumi_current_bin);

    handle_l1jet_seeds = ctx.declare_event_input< vector< L1Jet>>("L1Jet_seeds");
  };


  AnalysisModule_SiJetTrg::~AnalysisModule_SiJetTrg() {}

  bool AnalysisModule_SiJetTrg::process(Event & event) {
 //###############################################################
    //
    //Selection Module for L2 Residual Calculation  
    //
    //Select Di-Jet Events 
    //Define Barrel and Probe Jet
    //Use possible third Jet to estimate alpha
    //Apply MC-Weights for Reweighting (Second Iteration)
    //
    //###############################################################

    n_evt++;
    if(debug){
      cout << endl << "++++++++++ NEW EVENT +++++++++" << endl << endl;
      cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl;
    }
    if(debug) cout<<"before first fill\n";   
    //Dump Input
    h_input->fill(event);

        
    //LEPTON selection

    if(debug) cout<<"before muon cleaning\n";
    muoSR_cleaner->process(event);
    if(debug) cout<<"after muon cleaning\n";
        
    sort_by_pt<Muon>(*event.muons); 
    if(debug) std::cout<<"#muons = "<<event.muons->size()<<std::endl;

    eleSR_cleaner->process(event);
    sort_by_pt<Electron>(*event.electrons);
    if(debug)  std::cout<<"#electrons = "<<event.electrons->size()<<std::endl;

    if (event.electrons->size()>0 || event.muons->size()>0) return false; 

    h_runnr_input->fill(event);

    /* CMS-certified luminosity sections */
    if(event.isRealData){
      if(!lumi_sel->passes(event)){
	if(debug) std::cout<<"Event not in lumi selection!"<<std::endl;
	return false;
      }
      else  h_lumisel->fill(event);
    }    
 
    // MET filters   
    if(!isMC && !metfilters_sel->passes(event)) return false;   

    int event_in_lumibin = -1;
    double fill_event_integrated_lumi = 0;
    double inst_lumi = -1;
    double int_lumi_event = -1;
    if(event.isRealData){
      run_lumi rl_event{event.run, event.luminosityBlock};
      double lumiblock_lumi = rl2lumi[rl_event];
      inst_lumi = lumiblock_lumi/23; //FIXME why /23 ???
      int_lumi_event = rl2intlumi[rl_event];

      vector<run_lumi>::iterator it;
      if(!(rl_event < upper_binborders_runnrs.back())){
	if(upper_binborders_runnrs.back() < rl_event) throw runtime_error("AnalysisModule_SiJetTrg: run_lumi of event greater than largest bin-border.");
	else it = prev(upper_binborders_runnrs.end()); //force the entries with the highest run_lumi to enter the last bin instead of overflow.
      }
      else it = upper_bound(upper_binborders_runnrs.begin(), upper_binborders_runnrs.end(), rl_event); //find the first entry in the vector of binborders that is greater than rl_event
      
      event_in_lumibin = distance(upper_binborders_runnrs.begin(), it); //find how many elements of the vector of binborders are smaller than 'it', this is the bin to be filled
      fill_event_integrated_lumi = lumi_in_bins.at(event_in_lumibin);
    }
    
    h_beforeCleaner->fill(event);

//############### Jet Cleaner and First Selection (N_Jets >=2) ##############################
    unsigned int n_jets_beforeCleaner = event.jets->size();
    //JetID
    if(jetLabel == "AK4CHS" || jetLabel == "AK8CHS") jetcleaner->process(event);
    unsigned int n_jets_afterCleaner = event.jets->size();
    //discard events if not all jets fulfill JetID instead of just discarding single jets
    if (n_jets_beforeCleaner != n_jets_afterCleaner) return false;

    h_afterCleaner->fill(event);

    const int jet_n = event.jets->size();
    if(jet_n<2) return false;
    h_2jets->fill(event);
//###########################################################################################
  
//####################  Select and Apply proper JEC-Versions for every Run ##################


    bool apply_global = false;
    
    bool apply_B = false;
    bool apply_C = false;
    bool apply_D = false;
    bool apply_E = false;
    bool apply_F = false;

    if(debug) cout<<"before run splitting\n";
    //residuals
    if(!isMC){
      //DATA
      if(split_JEC_DATA){ 
	//split JEC
	if(event.run <= s_runnr_B)         apply_B = true;
	else if(event.run <= s_runnr_C)         apply_C = true;
	else if(event.run <= s_runnr_D)         apply_D = true;
	else if(event.run <= s_runnr_E)         apply_E = true;
	else if(event.run <= s_runnr_F)         apply_F = true;	
	else throw runtime_error("AnalysisModule: run number not covered by if-statements in process-routine.");
      }
      else{
	//not split JEC
	apply_global = true;
      }
    }     
    else if(isMC){
      //MC
	//not split JEC
	apply_global = true;
    }
    

    // if(apply_BCD+apply_EFearly+apply_FlateG+apply_H+apply_global != 1) throw runtime_error("In TestModule.cxx: Sum of apply_* when applying JECs is not == 1. Fix this.");

    
    h_beforeJEC->fill(event);
    if(debug) std::cout <<" before jetleptoncleaner  "<<std::endl;
    if(debug) std::cout <<"jetlepton cleaner is 0: "<<(jetleptoncleaner==0)<<std::endl;    
    // if(debug) std::cout <<jetleptoncleaner<<std::endl;
    
    std::cout<< std::flush;
    
    if(debug) std::cout <<" before jet corrector "<<std::endl;

    
    if(apply_B){
      JLC_B->process(event);
      jet_corrector_B->process(event);
    }
    if(apply_C){
      JLC_C->process(event);
      jet_corrector_C->process(event);
    }
    if(apply_D){
      if(debug) std::cout <<" in apply D jet corrector "<<std::endl;    
      JLC_D->process(event);
      if(debug) std::cout <<" after D JLC "<<std::endl;       
      jet_corrector_D->process(event);
    }
    if(apply_E){
      JLC_E->process(event);
      jet_corrector_E->process(event);
    }
    if(apply_F){
      JLC_F->process(event);
      jet_corrector_F->process(event);
    }     
    if(apply_global){
      if(debug)	std::cout <<"in apply global"<<std::endl;
      jetleptoncleaner->process(event);
      if(debug)	std::cout <<"after jetleptoncleaner"<<std::endl;      
      jet_corrector->process(event);
    }
   

    //DEBUG
    if(debug){
      std::cout <<" after jetleptoncleaner  "<<std::endl;
    }
      
    h_afterJEC->fill(event);

    
//##############################################################################################
    
//################################  Apply JER and MET  #########################################

    //Apply JER to all jet collections
    if(apply_smear) if(jetER_smearer.get()) jetER_smearer->process(event);
    h_afterJER->fill(event); 

    if(eta_thresh_low==1.) eta_thresh_high=2.;
    else if(eta_thresh_low==0.) eta_thresh_high=1.;
    else  if(eta_thresh_low==2.) eta_thresh_high=2.7;
    else  if(eta_thresh_low==2.650) eta_thresh_high=3.139;
    else  if(eta_thresh_low==2.7) eta_thresh_high=3;
    else  if(eta_thresh_low==3.) eta_thresh_high=5.;
    else{
      eta_thresh_low=0.;
      eta_thresh_high=10.;
    }
    //correct MET only AFTER smearing the jets
    if(apply_B){
      jet_corrector_B->correct_met(event,true,L1METptThresh,  eta_thresh_low, eta_thresh_high);
    }
    if(apply_C){
      jet_corrector_C->correct_met(event,true,L1METptThresh,  eta_thresh_low, eta_thresh_high);
    }
    if(apply_D){
      jet_corrector_D->correct_met(event,true,L1METptThresh,  eta_thresh_low, eta_thresh_high);
    }
    if(apply_E){
      jet_corrector_E->correct_met(event,true,L1METptThresh,  eta_thresh_low, eta_thresh_high);
    }
    if(apply_F){
      jet_corrector_F->correct_met(event,true,L1METptThresh,  eta_thresh_low, eta_thresh_high);
    }     
    if(apply_global){
      jet_corrector->correct_met(event,true,L1METptThresh,  eta_thresh_low, eta_thresh_high);
    }

    h_afterMET->fill(event); 
//##############################################################################################

    int jetid_0 = 0;
    int jetid_1 = 1;
    int jetid_2 = 2;

    int jetid_0_last = 0;
    int jetid_1_last = 1;
    int jetid_2_last = 2;   
  
 //Calculate pt_ave
   Jet* jet1 = &event.jets->at(0);// leading jet
   Jet* jet2 = &event.jets->at(1);// sub-leading jet
   float jet1_pt = jet1->pt();
   float jet2_pt = jet2->pt();
   float pt_ave = (jet1_pt + jet2_pt)/2.;    
    
////###############################################  Trigger  ##################################
 
    int triggerSiMu  = 0;
  
    int trigger40  = 0;
    int trigger60  = 0;
    int trigger80  = 0;
    int trigger140 = 0;
    int trigger200 = 0;
    int trigger260 = 0;
    int trigger320 = 0;
    int trigger400 = 0;
    int trigger450 = 0;
    int trigger500 = 0;
  
     int trigger40_HF  = 0;
     int trigger60_HF  = 0;
     int trigger80_HF  = 0;
    int trigger140_HF = 0;
    int trigger200_HF = 0;
    int trigger260_HF = 0;
    int trigger320_HF = 0;
    int trigger400_HF = 0;
    int trigger450_HF = 0;
    int trigger500_HF = 0;

    
    bool pass_triggerSiMu=false;

    bool pass_trigger40=false; bool pass_trigger60=false; bool pass_trigger80=false;
    bool pass_trigger140=false; bool pass_trigger200=false; bool pass_trigger260=false;
    bool pass_trigger320=false; bool pass_trigger400=false; bool pass_trigger450=false;  bool pass_trigger500=false;

    bool pass_trigger40_HFJEC=false; bool pass_trigger60_HFJEC=false; bool pass_trigger80_HFJEC=false;
    bool pass_trigger140_HFJEC=false; bool pass_trigger200_HFJEC=false; bool pass_trigger260_HFJEC=false;
    bool pass_trigger320_HFJEC=false; bool pass_trigger400_HFJEC=false; bool pass_trigger450_HFJEC=false;  bool pass_trigger500_HFJEC=false;

    double trg_thresh[10] = {s_Pt_Ave40_cut,s_Pt_Ave60_cut,s_Pt_Ave80_cut,s_Pt_Ave140_cut,s_Pt_Ave200_cut,s_Pt_Ave260_cut,s_Pt_Ave320_cut,s_Pt_Ave400_cut, s_Pt_Ave450_cut, s_Pt_Ave500_cut};

    double trgHF_thresh[10] = {s_Pt_Ave40_cut,s_Pt_Ave60_cut,s_Pt_Ave80_cut,s_Pt_Ave140_cut,s_Pt_Ave200_cut,s_Pt_Ave260_cut,s_Pt_Ave320_cut,s_Pt_Ave400_cut, s_Pt_Ave450_cut, s_Pt_Ave500_cut};//{s_Pt_Ave40HF_cut,s_Pt_Ave60HF_cut,s_Pt_Ave80HF_cut,s_Pt_Ave140HF_cut,s_Pt_Ave200HF_cut,s_Pt_Ave260HF_cut,s_Pt_Ave320HF_cut,s_Pt_Ave400HF_cut, s_Pt_Ave450HF_cut, s_Pt_Ave500HF_cut};


    Jet* jet_probe = jet1;
    Jet* jet_barrel = jet2;
    int ran = rand();
    int numb = ran % 2;
    if(numb==0){
	jet_probe = jet2;
	jet_barrel = jet1;
    }    
    if ((fabs(jet1->eta())<s_eta_barr)&&(fabs(jet2->eta())<s_eta_barr)) {
      ran = rand();
      numb = ran % 2;
      if(numb==0){
	jet_probe = jet2;
	jet_barrel = jet1;
      }
      else{
	jet_probe = jet1;
	jet_barrel = jet2;	
      }
    } 
    else if ((fabs(jet1->eta())<s_eta_barr)||(fabs(jet2->eta())<s_eta_barr)){
      if(fabs(jet1->eta())<s_eta_barr){
	jet_probe = jet2;
	jet_barrel = jet1;
      }
      else{
	jet_probe = jet1;
	jet_barrel = jet2;
      }
    }

    
    if(debug) cout<<"before trigger pass checks\n";
    if(event.isRealData){
      float pt_ave_ = pt_ave;
      float probejet_eta = jet_probe->eta();

      bool eta_cut_bool = abs(probejet_eta) <  eta_cut;     
      if(!trigger_fwd) eta_cut_bool = true;
            
      bool eta_cut_bool_HF = abs(probejet_eta) >=  eta_cut;
      if(!trigger_central) eta_cut_bool_HF = true;      

	pass_trigger40 = (trigger40_sel->passes(event) && pt_ave>trg_thresh[0]   && pt_ave<trg_thresh[1] && (eta_cut_bool));
	pass_trigger60 = (trigger60_sel->passes(event) && pt_ave>trg_thresh[1]   && pt_ave<trg_thresh[2] && (eta_cut_bool));
	pass_trigger80 = (trigger80_sel->passes(event) && pt_ave>trg_thresh[2]   && pt_ave<trg_thresh[3] && (eta_cut_bool)); 
	pass_trigger140 = (trigger140_sel->passes(event) && pt_ave>trg_thresh[3] && pt_ave<trg_thresh[4] && (eta_cut_bool));
	pass_trigger200 = (trigger200_sel->passes(event) && pt_ave>trg_thresh[4] && pt_ave<trg_thresh[5] && (eta_cut_bool));
	pass_trigger260 = (trigger260_sel->passes(event) && pt_ave>trg_thresh[5] && pt_ave<trg_thresh[6] && (eta_cut_bool)); 
	pass_trigger320 = (trigger320_sel->passes(event) && pt_ave>trg_thresh[6] && pt_ave<trg_thresh[7] && (eta_cut_bool)); 
	pass_trigger400 = (trigger400_sel->passes(event) && pt_ave>trg_thresh[7] && pt_ave<trg_thresh[8] && (eta_cut_bool));
	pass_trigger450 = (trigger450_sel->passes(event) && pt_ave>trg_thresh[8] && pt_ave<trg_thresh[9] && (eta_cut_bool));
	pass_trigger500 = (trigger500_sel->passes(event) && pt_ave>trg_thresh[9] && (eta_cut_bool));
      
	pass_trigger40_HFJEC = (trigger40_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[0]   && pt_ave<trgHF_thresh[1] && (eta_cut_bool_HF));
	pass_trigger60_HFJEC = (trigger60_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[1]   && pt_ave<trgHF_thresh[2] && (eta_cut_bool_HF));
	pass_trigger80_HFJEC = (trigger80_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[2]   && pt_ave<trgHF_thresh[3] && (eta_cut_bool_HF)); 
	pass_trigger140_HFJEC = (trigger140_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[3] && pt_ave<trgHF_thresh[4] && (eta_cut_bool_HF));
	pass_trigger200_HFJEC = (trigger200_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[4] && pt_ave<trgHF_thresh[5] && (eta_cut_bool_HF));
	pass_trigger260_HFJEC = (trigger260_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[5] && pt_ave<trgHF_thresh[6] && (eta_cut_bool_HF)); 
	pass_trigger320_HFJEC = (trigger320_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[6] && pt_ave<trgHF_thresh[7] && (eta_cut_bool_HF)); 
	pass_trigger400_HFJEC = (trigger400_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[7] && pt_ave<trgHF_thresh[8] && (eta_cut_bool_HF));
	pass_trigger450_HFJEC = (trigger450_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[8] && pt_ave<trgHF_thresh[9] && (eta_cut_bool_HF));
	pass_trigger500_HFJEC = (trigger500_HFJEC_sel ->passes(event) && pt_ave>trgHF_thresh[9] && (eta_cut_bool_HF));

	
      bool pass_trigger = false;
	if(eta_cut_bool) pass_trigger =  pass_trigger40 || pass_trigger60 || pass_trigger80 || pass_trigger140 || pass_trigger200  || pass_trigger260 || pass_trigger320 || pass_trigger400 || pass_trigger450 || pass_trigger500;
	else pass_trigger =  pass_trigger40_HFJEC || pass_trigger60_HFJEC || pass_trigger80_HFJEC || pass_trigger140_HFJEC || pass_trigger200_HFJEC || pass_trigger260_HFJEC || pass_trigger320_HFJEC || pass_trigger400_HFJEC || pass_trigger450_HFJEC || pass_trigger500_HFJEC;

    
      if(debug){
	cout << "before triggers: " << endl;
	cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl;
      }
      h_beforeTriggerData->fill(event);

      if(!pass_trigger){
	return false;
      }
    }
        //Count Events passed Trigger
      int n_trig = 0;
      if(pass_trigger40){ n_trig++; trigger40 = 1;}
      if(pass_trigger60){ n_trig++; trigger60 = 1;}
      if(pass_trigger80){ n_trig++; trigger80 = 1;}
      if(pass_trigger140){ n_trig++; trigger140 = 1;}
      if(pass_trigger200){ n_trig++; trigger200 = 1;}
      if(pass_trigger260){ n_trig++; trigger260 = 1;}
      if(pass_trigger320){ n_trig++; trigger320 = 1;}
      if(pass_trigger400){ n_trig++; trigger400 = 1;}
      if(pass_trigger500){ n_trig++; trigger500 = 1;}
      if(pass_trigger450){ n_trig++; trigger450 = 1;}
      
       if(pass_trigger40_HFJEC){ n_trig++;  trigger40_HF = 1;}
       if(pass_trigger60_HFJEC){ n_trig++;  trigger60_HF = 1;}
       if(pass_trigger80_HFJEC){ n_trig++;  trigger80_HF = 1;}
      if(pass_trigger140_HFJEC){ n_trig++; trigger140_HF = 1;}
      if(pass_trigger200_HFJEC){ n_trig++; trigger200_HF = 1;}
      if(pass_trigger260_HFJEC){ n_trig++; trigger260_HF = 1;}
      if(pass_trigger320_HFJEC){ n_trig++; trigger320_HF = 1;}
      if(pass_trigger400_HFJEC){ n_trig++; trigger400_HF = 1;}
      if(pass_trigger500_HFJEC){ n_trig++; trigger500_HF = 1;}
      if(pass_trigger450_HFJEC){ n_trig++; trigger450_HF = 1;}

    h_afterTriggerData->fill(event);
    if(debug) cout<<"after triggering: njet: "<<event.jets->size()<<endl;
    
    
    if(onlyBtB){
     //turn jet2 around and check dR to jet1
     float eta1 = jet1->eta();
     float eta2 = -1.*jet2->eta();
     float phi1 = jet1->phi();
     float phi2 = TVector2::Phi_mpi_pi(jet2->phi()+3.14159265358979f);
     
     float deta = eta1 - eta2;
     float dphi =  TVector2::Phi_mpi_pi(phi1 - phi2);
     float dR = TMath::Sqrt( deta*deta + dphi*dphi );

     if(debug) cout<<"in BtB if with dR "<<dR<<endl;
     
     if(dR>0.4) return false;
   }

//###############################  Declare Probe and Barrel Jet  ###############################
    
  
    if(debug) cout<<"Declare Probe and Barrel Jet\n";

    double dR_jet3_barreljet = -1;
    double dR_jet3_probejet = -1;
    if(event.jets->size()>2){
      dR_jet3_barreljet = deltaR(event.jets->at(2), *jet_barrel);
      dR_jet3_probejet = deltaR(event.jets->at(2), *jet_probe);
    }
//##############################################################################################

    if(debug) cout<<"After Declare Probe and Barrel Jet\n";
    
    //read or calculated values for dijet events
    float gen_pthat = 0; //pt hat (from QCD simulation)
    float gen_weight = 0;
    if(!event.isRealData){
      gen_weight = event.weight;
      // gen_pthat = event.genInfo->binningValues()[0];// only for pythia8 samples //todo: for herwig, madgraph FIXME: commnted out for madgraph
    }
    float nvertices = event.pvs->size(); 
    float nPU = 0 ;//todo for data?
    // if(!event.isRealData) nPU = event.genInfo->pileup_TrueNumInteractions(); FIXME: commnted out for madgraph

    float matchJetId_0 = -10.;
    float matchJetId_1 = -10.;
    
    float genjet1_pt = 0;
    float genjet2_pt = 0;
    float genjet3_pt = 0;
    float dR_jet3_RECO_GEN = -100;
    if(isMC){
      if(event.genjets->size()>0)genjet1_pt = event.genjets->at(0).pt();
      if(event.genjets->size()>1)genjet2_pt = event.genjets->at(1).pt();
      if(event.genjets->size()>2)genjet3_pt = event.genjets->at(2).pt();
      if(event.genjets->size()>2 && event.jets->size()>2)
	dR_jet3_RECO_GEN =  deltaR(event.jets->at(2), event.genjets->at(2));
    }

    auto factor_raw1 = jet1->JEC_factor_raw();
    auto factor_raw2 = jet2->JEC_factor_raw();
    float jet1_ptRaw = jet1_pt*factor_raw1;
    float jet2_ptRaw = jet2_pt*factor_raw2;
    float probejet_eta = jet_probe->eta(); 
    float  probejet_phi = jet_probe->phi(); 
    float  probejet_pt = jet_probe->pt(); 
    auto factor_raw_probe = jet_probe->JEC_factor_raw();
    float probejet_ptRaw = probejet_pt*factor_raw_probe;
    float barreljet_eta = jet_barrel->eta(); 
    float  barreljet_phi = jet_barrel->phi(); 
    float  barreljet_pt = jet_barrel->pt(); 
    auto factor_raw_barrel = jet_barrel->JEC_factor_raw();
    float barreljet_ptRaw = barreljet_pt*factor_raw_barrel;

//##########################  Get third Jet for alpha, asymmetry calculation  ##################
    if(debug) cout<<"calculate asymmetry\n";
    
   float jet3_pt = -1; float jet3_ptRaw = -1; float jet3_eta = -100;
    if(jet_n>2){
      Jet* jet3 = &event.jets->at(2);
      jet3_pt = jet3->pt();
      jet3_eta = jet3->eta();
      auto factor_raw3 = jet3->JEC_factor_raw();
      jet3_ptRaw = jet3_pt*factor_raw3;
    }
    float alpha = jet3_pt/pt_ave;
    float asymmetry = (probejet_pt - barreljet_pt)/(probejet_pt + barreljet_pt);
    float rel_r = (1+asymmetry)/(1-asymmetry);
    TVector2 pt, met;
    met.Set(event.met->pt() * cos(event.met->phi()),event.met->pt() * sin(event.met->phi()));
    pt.Set(barreljet_pt * cos(barreljet_phi),barreljet_pt* sin(barreljet_phi));
    float mpf_r = 1 + (met.Px()*pt.Px() + met.Py()*pt.Py())/(pt.Px()*pt.Px() + pt.Py()*pt.Py());
    float B = (met.Px()*pt.Px() + met.Py()*pt.Py())/((probejet_pt + barreljet_pt) * sqrt(pt.Px()*pt.Px() + pt.Py()*pt.Py())); //vec_MET*vec_ptbarr/(2ptave*ptbarr)

    float jets_pt = 0;
    for(int i=2;i<jet_n;i++){
      jets_pt += ((Jet*)&event.jets->at(i))->pt();
    }
    
    
//##############################################################################################

//###########################################  Obtain weights from MC reweighting  ###############################
    if(apply_weights && isMC){
      if(debug) cout<<"in apply weights\n";
      if(debug) cout<<"  weight before: "<<event.weight<<endl;      
      
      // TH2D* h_weights = (TH2D*)f_weights->Get("pt_ave_data");
      // int idx_x=0;
      // int idx_y=0;
      // while(pt_ave > idx_x*5) idx_x++;
      // while(fabs(probejet_eta) > eta_range[idx_y]) idx_y++;
      // event.weight *= h_weights->GetBinContent(idx_x, idx_y);

      // TH1D* h_weights = (TH1D*)f_weights->Get("pt_ave_binned_data");
      TH2Poly* h_weights = (TH2Poly*)f_weights->Get("pt_ave_binned_data");

      // int idx=0;
      // int idy=0;
      // double eta_bins[5] = {-5.2,-2.853,0,2.853,5.2};
      // while(probejet_eta > eta_bins[idy]) idy++;
      bool eta_cut_bool = fabs(probejet_eta)>eta_cut;
      // while(pt_ave > (eta_cut_bool?pt_bins_HF:pt_bins)[idx]) idx++;
     
      // if(idx == 0) return false;
      if(pt_ave < (eta_cut_bool?pt_bins_HF:pt_bins)[0]) return false;
      if(h_weights->FindBin(pt_ave<2000?pt_ave:(2000-1e-7)<0,probejet_eta)<0.){
	if(debug) cout<<"did not found the MC reweighting bin for pt_ave/eta "<<pt_ave<<"/"<<probejet_eta<<endl;
	return false;}
      event.weight *= h_weights->GetBinContent(h_weights->FindBin(pt_ave<2000?pt_ave:(2000-1e-7),probejet_eta));
      if(debug) cout<<"  weight after: "<<event.weight<<endl;  
    }

    // h_afterPtEtaReweight->fill(event);
//################################################################################################################
//#############################################  scale to Lumi  ##############################################
    if(isMC && (lumiweight != 0)){
      if(debug) cout<<"in apply lumiweights\n";
      if(debug) cout<<"  weight before: "<<event.weight<<endl;      
      event.weight *= 1./lumiweight;
      if(debug) cout<<"  weight after: "<<event.weight<<endl;  
    }


    if(debug) cout<<"before afterUnflat fill: njet: "<<event.jets->size()<<endl;
    
   h_afterUnflat->fill(event);
    
    int flavor = 0;
    float onoffDummy =0.;
    
 //fill that containers!
    double pu_pthat = -1;

    if(debug) cout<<"before the main event.set's\n";
    
    // if(!event.isRealData) pu_pthat = event.genInfo->PU_pT_hat_max(); FIXME: commnted out for madgraph
    event.set(tt_matchJetId_0,-10.);
    event.set(tt_matchJetId_1,-10.);

    if(debug) cout<<"set pts\n";
    
    event.set(tt_gen_pthat,gen_pthat);
       if(debug) cout<<"set pts1\n";
    event.set(tt_gen_PUpthat,pu_pthat);
       if(debug) cout<<"set pts2\n";
    event.set(tt_gen_weight,gen_weight);
       if(debug) cout<<"set pts3\n";
    event.set(tt_jet1_pt,jet1_pt);
       if(debug) cout<<"set pts4\n";
    event.set(tt_jet2_pt,jet2_pt);
       if(debug) cout<<"set pts5\n";
    event.set(tt_jet3_pt,jet3_pt);
       if(debug) cout<<"set pts6\n";
    event.set(tt_jet3_eta,jet3_eta);
       if(debug) cout<<"set pts7\n";
    event.set(tt_jet1_ptRaw,jet1_ptRaw);
    event.set(tt_jet2_ptRaw,jet2_ptRaw);
    event.set(tt_jet3_ptRaw,jet3_ptRaw);
       if(debug) cout<<"set pts8\n";
    event.set(tt_jet1_ptGen,genjet1_pt);
    event.set(tt_jet2_ptGen,genjet2_pt);
    event.set(tt_jet3_ptGen,genjet3_pt);
       if(debug) cout<<"set pts9\n";
    event.set(tt_jet1_pt_onoff_Resp,onoffDummy);
    event.set(tt_jet2_pt_onoff_Resp,onoffDummy);
       if(debug) cout<<"set pts10\n";
    event.set(tt_nvertices,nvertices);

     if(debug) cout<<"set EFs\n";

     event.set(tt_probejet_neutEmEF,jet_probe->neutralEmEnergyFraction());
    event.set(tt_probejet_neutHadEF,jet_probe->neutralHadronEnergyFraction());
    event.set(tt_probejet_chEmEF,jet_probe->chargedEmEnergyFraction());
    event.set(tt_probejet_chHadEF,jet_probe->chargedHadronEnergyFraction());
    event.set(tt_probejet_photonEF,jet_probe->photonEnergyFraction());
    event.set(tt_probejet_muonEF,jet_probe->muonEnergyFraction());

     if(debug) cout<<"set eta-phis\n";

     event.set(tt_probejet_eta,probejet_eta);
    event.set(tt_probejet_phi,probejet_phi);
    event.set(tt_probejet_pt,probejet_pt);
    event.set(tt_probejet_ptRaw,probejet_ptRaw);
    event.set(tt_barreljet_eta,barreljet_eta);
    event.set(tt_barreljet_phi,barreljet_phi);
    event.set(tt_barreljet_pt,barreljet_pt);
    event.set(tt_barreljet_ptRaw,barreljet_ptRaw);
    event.set(tt_pt_ave,pt_ave);
    event.set(tt_alpha,alpha);
    event.set(tt_asymmetry,asymmetry);
    event.set(tt_B,B);
    event.set(tt_MET,event.met->pt());
    event.set(tt_rel_r,rel_r);
    event.set(tt_mpf_r,mpf_r);
    event.set(tt_nPU,nPU);
    event.set(tt_ev_weight,event.weight);
    event.set(tt_jets_pt,jets_pt);
    event.set(tt_jet_n,jet_n);
    event.set(tt_rho,event.rho);    
    event.set(tt_partonFlavor,flavor);
   
    event.set(tt_dR_jet3_barreljet,dR_jet3_barreljet);
    event.set(tt_dR_jet3_probejet,dR_jet3_probejet);

    event.set(tt_inst_lumi,inst_lumi);
    event.set(tt_integrated_lumi_in_bin,fill_event_integrated_lumi);
    event.set(tt_lumibin,event_in_lumibin);
    event.set(tt_integrated_lumi,int_lumi_event);
    
    if(debug) cout<<"set central triggers\n";
     
    event.set(tt_triggerSiMu, triggerSiMu);    
    event.set(tt_trigger40 , trigger40);
    event.set(tt_trigger60 , trigger60);
    event.set(tt_trigger80 , trigger80);
    event.set(tt_trigger140, trigger140);
    event.set(tt_trigger200, trigger200);
    event.set(tt_trigger260, trigger260);
    event.set(tt_trigger320, trigger320);
    event.set(tt_trigger400, trigger400);
    event.set(tt_trigger450, trigger450);
    event.set(tt_trigger500, trigger500);
    
      if(debug) cout<<"set HF triggers\n";
      
     event.set(tt_trigger40_HF,  trigger40_HF);
     event.set(tt_trigger60_HF,  trigger60_HF);
     event.set(tt_trigger80_HF,  trigger80_HF);
    event.set(tt_trigger140_HF, trigger140_HF);
    event.set(tt_trigger200_HF, trigger200_HF);
    event.set(tt_trigger260_HF, trigger260_HF);
    event.set(tt_trigger320_HF, trigger320_HF);
    event.set(tt_trigger400_HF, trigger400_HF);
    event.set(tt_trigger450_HF, trigger450_HF);
    event.set(tt_trigger500_HF, trigger500_HF);

    if(debug) cout<<"set event to selection object\n";

    sel.SetEvent(event);
    
//##################################################   Advanced Selections   ###################
    //good primary vertex
    int nGoodVts = sel.goodPVertex();

    if(debug){
      cout << "debug is on" << endl;
      cout << "before good vertex selection : " << endl;
      cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl;
    }

    if(nGoodVts<=0) return false;
    if(debug) cout << "after good vertex selection " << endl;
    event.set(tt_nGoodvertices, nGoodVts);
    if(debug) cout << "after good vertex set " << endl;      
    h_afternVts->fill(event);
    if(debug) cout << "after good vertex fill " << endl;
    
    //DiJet-Events      
    if(!sel.DiJet()) return false;
    if(debug) cout << "after diJet sel" << endl;
    h_nocuts->fill(event);
    h_lumi_nocuts->fill(event);

//Pu_pt_hat/pt_hat Selection 
    if(isMC){
      //FIXME
      // cout<<"PUpthat selction skipped for Madgraph MC\n";
      if(!sel.PUpthat()) return false;
    }
    // h_nocuts->fill(event);
    // h_lumi_nocuts->fill(event);

    //MET/pt - Cut
    if(apply_METoverPt_cut && event.get(tt_MET)/(event.get(tt_jets_pt)+event.get(tt_barreljet_pt)+event.get(tt_probejet_pt))>0.2) return false; //skip events with large MET contribution  

    //PhiEta Region cleaning
    if(apply_EtaPhi_cut && (!sel.EtaPhiCleaning() || !sel.EtaPhi()) ) return false;

    if(!isMC){
          // if(! sel.EtaPtCut(event)) return false;
	  if(! sel.ChEMFrakCut()) return false;
    }

    if(debug) cout << "after etaPhi sel" << endl;
    // event.set(tt_run,0);
    // event.set(tt_evID,0);
    // event.set(tt_lumiSec,0);
    event.set(tt_run,event.run);
    event.set(tt_evID,event.event);
    event.set(tt_lumiSec,event.luminosityBlock);
       
       //Advanced Selection: DiJet Events
    if(!sel.DiJetAdvanced()) return false;   
    h_dijet->fill(event);
    h_lumi_dijet->fill(event);
    h_match->fill(event);
    h_lumi_match->fill(event);
    
    if(debug) cout << "after advanced sel" << endl;
    
   if(event.isRealData){
      if(pass_trigger40 ) {h_trg40->fill(event); h_lumi_Trig40->fill(event);}
      if(pass_trigger60 ) {h_trg60->fill(event); h_lumi_Trig60->fill(event);} 
      if(pass_trigger80 ) {h_trg80->fill(event); h_lumi_Trig80->fill(event);}
      if(pass_trigger140) {h_trg140->fill(event); h_lumi_Trig140->fill(event);}
      if(pass_trigger200) {h_trg200->fill(event); h_lumi_Trig200->fill(event);}
      if(pass_trigger260) {h_trg260->fill(event); h_lumi_Trig260->fill(event);}
      if(pass_trigger320) {h_trg320->fill(event); h_lumi_Trig320->fill(event);} 
      if(pass_trigger400) {h_trg400->fill(event); h_lumi_Trig400->fill(event);}
      if(pass_trigger450) {h_trg450->fill(event); h_lumi_Trig450->fill(event);}
      if(pass_trigger500) {h_trg500->fill(event); h_lumi_Trig500->fill(event);}

      if( pass_trigger40_HFJEC) {h_trgHF40->fill(event);  h_lumi_TrigHF40->fill(event);}
      if( pass_trigger60_HFJEC) {h_trgHF60->fill(event);  h_lumi_TrigHF60->fill(event);} 
      if( pass_trigger80_HFJEC) {h_trgHF80->fill(event);  h_lumi_TrigHF80->fill(event);}
      if(pass_trigger140_HFJEC) {h_trgHF140->fill(event); h_lumi_TrigHF140->fill(event);}
      if(pass_trigger200_HFJEC) {h_trgHF200->fill(event); h_lumi_TrigHF200->fill(event);}
      if(pass_trigger260_HFJEC) {h_trgHF260->fill(event); h_lumi_TrigHF260->fill(event);}
      if(pass_trigger320_HFJEC) {h_trgHF320->fill(event); h_lumi_TrigHF320->fill(event);} 
      if(pass_trigger400_HFJEC) {h_trgHF400->fill(event); h_lumi_TrigHF400->fill(event);}
      if(pass_trigger450_HFJEC) {h_trgHF450->fill(event); h_lumi_TrigHF450->fill(event);}
      if(pass_trigger500_HFJEC) {h_trgHF500->fill(event); h_lumi_TrigHF500->fill(event);}
   }
    else{    
      if(!sel.PtMC()) return false; // For MC only one Pt threshold
   }
       if(debug) cout << "after trg fills" << endl;
//###############################################################################################

       if(useUnprefireable){
	 if(!sel.Unprefirable(unprefirableSummary)) return false;
       }

    // L1 jet seed cleaning
    if(apply_L1seed_from_bx1_filter){
      if(debug) cout << "before the L1 seed filter" << endl;
      if(!sel.L1JetBXcleanSmart()){
      if(debug) cout << "L1 seed filtered" << endl;
    	return false;
      }
      if(debug) cout << "after the first L1 seed filter" << endl;
    }

    //get the corresponding L1 Jet and save the bx
    std::vector< L1Jet>* l1jets = &event.get(handle_l1jet_seeds);

    if(debug) cout << "declared L1Jet seeds" << endl;
    
    int jet1_l1bx, jet2_l1bx, jet3_l1bx;
    
    unsigned int n_l1jets =l1jets->size();
    if(debug) cout << "l1jets size is "<<n_l1jets<<endl;
    if(n_l1jets>0){
      double dRmin = 100.;
      int dRmin_seed_idx = -1;
      float dR;
      if(debug) cout << "before first L1Jet seeds dR loop" << endl;
      for(unsigned int i = 0; i<n_l1jets; i++){
	dR=uhh2::deltaR(l1jets->at(i),event.jets->at(0));

	if(dR < dRmin){
	  dRmin=dR;
	  dRmin_seed_idx = i;
	}
      }
      if( ( l1jets->at(dRmin_seed_idx).pt() / event.jets->at(0).pt() ) < 0.2 ) jet1_l1bx = -10;
      else jet1_l1bx = l1jets->at(dRmin_seed_idx).bx();
    }
    else jet1_l1bx = 10;
    
    if(n_l1jets>1){
      double dRmin = 100.;
      int dRmin_seed_idx = -1;
      float dR;
      for(unsigned int i = 0; i<n_l1jets; i++){
	dR=uhh2::deltaR(l1jets->at(i),event.jets->at(1));

	if(dR < dRmin){
	  dRmin=dR;
	  dRmin_seed_idx = i;
	}
      }
      if( ( l1jets->at(dRmin_seed_idx).pt() / event.jets->at(0).pt() ) < 0.2 ) jet2_l1bx = -10;
      else jet2_l1bx = l1jets->at(dRmin_seed_idx).bx();
    }
    else jet2_l1bx = 10;

    if(event.jets->size()>2){
    if(n_l1jets>2){
      double dRmin = 100.;
      int dRmin_seed_idx = -1;
      float dR;
      for(unsigned int i = 0; i<n_l1jets; i++){
	dR=uhh2::deltaR(l1jets->at(i),event.jets->at(2));

	if(dR < dRmin){
	  dRmin=dR;
	  dRmin_seed_idx = i;
	}
      }
      if( ( l1jets->at(dRmin_seed_idx).pt() / event.jets->at(0).pt() ) < 0.2 ) jet3_l1bx = -10;
      else jet3_l1bx = l1jets->at(dRmin_seed_idx).bx();
    }
    else jet3_l1bx = 10;
    }
    else jet3_l1bx = 10;

    event.set(tt_jet1_l1bx,jet1_l1bx);
    event.set(tt_jet2_l1bx,jet2_l1bx);
    event.set(tt_jet3_l1bx,jet3_l1bx);

//###############################################################################################


    
    if (event.get(tt_alpha) < 0.3) {
      h_sel->fill(event);
      // h_lumi_sel->fill(event);
    }
    
    if(debug) cout<<"before the final histogram fill\n";
    h_final->fill(event);

    h_lumi_final->fill(event);

    h_monitoring_final->fill(event);
    
    event.set(tt_Nmuon,event.muons->size());
    if(event.muons->size()>0)  
      event.set(tt_muon_pt,event.muons->at(0).pt());
    else 
      event.set(tt_muon_pt,0);
    event.set(tt_Nele,event.electrons->size());
    if(event.electrons->size()>0)  
      event.set(tt_ele_pt,event.electrons->at(0).pt());
    else 
      event.set(tt_ele_pt,0);
    
    if(debug) cout << "after lep fills" << endl;
    
    if(isMC){    
      double dr_cut = 0;
      if(jetLabel == "AK4CHS" || jetLabel == "AK4PUPPI") dr_cut = 0.2;
      else if (jetLabel == "AK8CHS" || jetLabel == "AK8PUPPI")dr_cut = 0.4;
      else throw runtime_error("TestModule.cxx: Invalid jet-label specified.");

      double dR_GenJet_GenParticle1;
      double dR_GenJet_GenParticle2;
      double flavor_barreljet = 0;
      int flavor_3rdjet = 0;
      double response_barreljet = 0;
      double flavor_probejet = 0;
      double response_probejet = 0;
      double flavor_leadingjet = 0;
      double flavor_subleadingjet = 0;
      const unsigned int genjets_n = event.genjets->size();
      int idx_jet_matching_genjet[genjets_n];
      double probejet_ptgen = -1; 
      double barreljet_ptgen = -1; 
      double probejet_drminparton=100;
      double barreljet_drminparton=100; 
      double barreljet_phigen = -1; 
      double probejet_ptptcl = -1; 
      double barreljet_ptptcl = -1; 
      int probejet_statusptcl = -1;
      int barreljet_statusptcl = -1;
      int jet3_statusptcl = -1;
      //match genp to gen-jets
      int idx_j=0;
      int idx_genp_min = -1;
      //this array contains one idx for each jet in the event. If -1: unmatched, else: idx of the closest genpart with dR<=0.2
      int idx_matched_jets[jet_n];
      int idx_matched_RecoGenjets[jet_n]; //for each reco store macthed gen jet id
      for(int i=0; i<jet_n; i++){
    	idx_matched_jets[i] = -1;
 	idx_matched_RecoGenjets[i] = -1;
      }
      int idx_parton_genJet[4]; int idx_parton_recoJet[4];
      for(int i=0; i<4; i++){
 	idx_parton_genJet[i]=-1; 
 	idx_parton_recoJet[i]=-1;
      }

      //matching gen- and reco-jets
      for(unsigned int i=0; i<event.genjets->size(); i++){
    	double dR_min = 99999; int idx_matching_jet = -1;
    	for(unsigned int j=0; j<event.jets->size(); j++){
    	  double dR = deltaR(event.jets->at(j), event.genjets->at(i));
    	  if(debug) cout << "dR between GenJet " << i << " and RecoJet " << j << ": " << dR << endl;
    	  if(dR<dR_min){
    	    dR_min = dR; 
    	    if(dR_min<dr_cut) idx_matching_jet = j;
    	  }
    	}
    	idx_jet_matching_genjet[i] = idx_matching_jet;
 	idx_matched_RecoGenjets[idx_matching_jet] = i;
	idx_matched_jets[idx_jet_matching_genjet[i]] = -1;

    	if(debug) cout << "the jet matching the genjet no. " << i << " is jet no. " << idx_matching_jet << endl;
      }
      /////////////////////

      for(Particle & genj : *event.genjets){
    	double dr_min = 99999;
    	double dr_cut = 0;
    	if(jetLabel == "AK4CHS" || jetLabel == "AK4PUPPI") dr_cut = 0.8;
    	else if (jetLabel == "AK8CHS" || jetLabel == "AK8PUPPI")dr_cut = 1.6;
    	else throw runtime_error("AnalysisModule_SiJetTrg.cxx: Invalid jet-label specified.");

    	int idx_g = 0;
    	for(GenParticle & genp: *event.genparticles){
    	  double dr = deltaR(genj,genp);
    	  if(dr < dr_min && genp.status()>1){
    	    dr_min = dr;
    	    idx_genp_min = idx_g;	
    	  }	
    	  if(debug) cout << "dr between genjet " << idx_j << " and genp (flavor: " << genp.flavor() << ") " << idx_g << "= " << dr << endl;
    	  idx_g++;
    	}
    	if(dr_min <= dr_cut && idx_genp_min>-1) {
    	  if(debug) cout << "genjet " << idx_j << " is matched to genparticle " << idx_genp_min << " of flavor " << event.genparticles->at(idx_genp_min).flavor() << " within dR = " << dr_min << ". " <<  endl; 
 	  if(idx_genp_min<4) idx_parton_genJet[idx_genp_min] = idx_j;
    	  if(idx_jet_matching_genjet[idx_j] >= 0) idx_matched_jets[idx_jet_matching_genjet[idx_j]] = idx_genp_min;
    	}
    	idx_j++;
      }
      //only consider jets that could be matched to a genparticle, these shall take the partons flavor by definition
 	for (int i=0; i<jet_n; i++){
 	  if(idx_matched_jets[i] != -1){
 	    if(debug)	    cout << "Jet no. " << i << " is matching genpart no. " << idx_matched_jets[i] << endl;
 	    if(idx_matched_jets[i]<4) idx_parton_recoJet[idx_matched_jets[i]] = i;
 	  }
 	}
      if(debug && event.genjets->size() <2) cout << "WARNING: GENjets size < 2" << endl;

      //only consider the barreljet, is it leading or sub-leading jet?
      int idx_barreljet = -1;
      if(fabs(jet1->pt() - jet_barrel->pt()) < 0.001) idx_barreljet = 0;
      else if (fabs(jet2->pt() - jet_barrel->pt()) < 0.001) idx_barreljet = 1;
      else throw runtime_error("first two jets are not the barrel jets, how could this happen?");
    
      //obtain flavor of the barreljet
      //-1: unmatched, 0: alpha too large, >0: flavor of matching genparticle 
      if(idx_matched_jets[idx_barreljet] != -1){	
    	flavor_barreljet = fabs(event.genparticles->at(idx_matched_jets[idx_barreljet]).flavor());
    	response_barreljet = jet_barrel->pt() / event.genparticles->at(idx_matched_jets[idx_barreljet]).pt();
        barreljet_ptptcl = event.genparticles->at(idx_matched_jets[idx_barreljet]).pt(); 
        barreljet_ptgen = event.genparticles->at(idx_matched_jets[idx_barreljet]).pt();
        barreljet_phigen = event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]).phi(); 
 	barreljet_statusptcl = event.genparticles->at(idx_matched_jets[idx_barreljet]).status();
	if(event.genparticles->size()>4){
	  dR_GenJet_GenParticle1 = deltaR(event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]),event.genparticles->at(2));
	  dR_GenJet_GenParticle2 = deltaR(event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]),event.genparticles->at(3));
	}
	else{
	dR_GenJet_GenParticle1 = -1; 
 	dR_GenJet_GenParticle2 = -1;
	} 
      }
      else if(idx_matched_RecoGenjets[idx_barreljet] !=-1){
	if(debug) cout<<"idx_matched_RecoGenjets[idx_barreljet] = "<<idx_matched_RecoGenjets[idx_barreljet]<<endl;
        barreljet_ptgen = event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]).pt();
	barreljet_phigen = event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]).phi(); 
 	flavor_barreljet = -1;
 	response_barreljet = -1;
        barreljet_ptptcl = -1;
 	dR_GenJet_GenParticle1 = -1; //deltaR(event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]),event.genparticles->at(2));
 	dR_GenJet_GenParticle2 = -1; //deltaR(event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]),event.genparticles->at(3));
      }      
      else{
    	flavor_barreljet = -1;
    	response_barreljet = -1;
        barreljet_ptgen = -1;
        barreljet_phigen = -1;
 	barreljet_statusptcl  = -1;
 	barreljet_drminparton = -1;
	dR_GenJet_GenParticle1 = -1; 
 	dR_GenJet_GenParticle2 = -1;
      }
      if(debug) cout << "barreljet is jet no. " << idx_barreljet << ", alpha = " << event.get(tt_alpha) << ", flavor of barreljet = " << flavor_barreljet << endl;
    

      //also for probe jets
      int idx_probejet = fabs(idx_barreljet - 1);
      //obtain flavor of the probejet
      //-1: unmatched,  >0: flavor of matching genparticle 
      if(idx_matched_jets[idx_probejet] != -1){
    	flavor_probejet = fabs(event.genparticles->at(idx_matched_jets[idx_probejet]).flavor());
    	response_probejet = jet_probe->pt() / event.genparticles->at(idx_matched_jets[idx_probejet]).pt();
    	probejet_ptgen = event.genparticles->at(idx_matched_jets[idx_probejet]).pt();
 	probejet_ptptcl = event.genparticles->at(idx_matched_jets[idx_probejet]).pt();
 	probejet_statusptcl = event.genparticles->at(idx_matched_jets[idx_probejet]).status(); 
 	probejet_ptgen = event.genjets->at(idx_matched_RecoGenjets[idx_probejet]).pt();
      }
      else if(idx_matched_RecoGenjets[idx_probejet] !=-1){
 	flavor_probejet = -1;
 	response_probejet = -1;
        probejet_ptptcl = -1;
 	probejet_ptgen = event.genjets->at(idx_matched_RecoGenjets[idx_probejet]).pt();
	probejet_statusptcl = -1;
 	probejet_drminparton = -1;
	//	if(debug) cout<<" probejet_ptgen = "<<probejet_ptgen<<endl;
      }
      else{ 
 	flavor_probejet = -1;
 	response_probejet = -1;
        probejet_ptptcl = -1;
        probejet_ptgen = -1;
 	probejet_statusptcl = -1;
 	probejet_drminparton = -1;
      } 

      if(debug) cout << "probejet is jet no. " << idx_probejet << ", alpha = " << event.get(tt_alpha) << ", flavor of probejet = " << flavor_probejet << endl;

      if(event.genparticles){
      for(GenParticle & genp: *event.genparticles){  
 	if(idx_matched_RecoGenjets[idx_probejet]!=-1){
 	  double dr = deltaR(event.genjets->at(idx_matched_RecoGenjets[idx_probejet]),genp);
 	  if(probejet_drminparton>dr) probejet_drminparton = dr;       
 	}
 	if(idx_matched_RecoGenjets[idx_barreljet]!=-1){
 	  double dr = deltaR(event.genjets->at(idx_matched_RecoGenjets[idx_barreljet]),genp);
 	  if(barreljet_drminparton>dr) barreljet_drminparton = dr;   
 	}
      }
      }
      else{
	probejet_drminparton = -1; barreljet_drminparton = -1;
      }      
      
      //same for leading jet
      //-1: unmatched, 0: alpha too large, >0: flavor of matching genparticle 
      if(idx_matched_jets[0] != -1) flavor_leadingjet = fabs(event.genparticles->at(idx_matched_jets[0]).flavor());
      else flavor_leadingjet = -1;
      if(debug) cout << "leadingjet is jet no. " << 0 << ", alpha = " << event.get(tt_alpha) << ", flavor of leadingjet = " << flavor_leadingjet << endl;
      

      //same for subleading jet
      //-1: unmatched, 0: alpha too large, >0: flavor of matching genparticle 
      if(idx_matched_jets[1] != -1) flavor_subleadingjet = fabs(event.genparticles->at(idx_matched_jets[1]).flavor());
      else flavor_subleadingjet = -1;
      if(debug) cout << "subleadingjet is jet no. " << 1 << ", alpha = " << event.get(tt_alpha) << ", flavor of subleadingjet = " << flavor_subleadingjet << endl;
      
     //same for 3rd jet
      //-1: unmatched, 0: alpha too large, >0: flavor of matching genparticle 
      if(jet_n>2){
 	if(idx_matched_jets[2] != -1) {
 	  flavor_3rdjet = fabs(event.genparticles->at(idx_matched_jets[2]).flavor());
 	  jet3_statusptcl = event.genparticles->at(idx_matched_jets[2]).status();
 	}
 	else{
 	  flavor_3rdjet = -1;
 	  jet3_statusptcl = -1;
 	}
 	if(debug) cout << "3rd is jet no. " << idx_matched_jets[2] << ", alpha = " << event.get(tt_alpha) << ", flavor of the 3rd jet = " << flavor_3rdjet <<", status = "<<jet3_statusptcl<< endl;
      }
      else{
 	flavor_3rdjet = -1;  
	jet3_statusptcl = -1;
      }
      //      i
      event.set(tt_flavor3rdjet,flavor_3rdjet);   
      event.set(tt_flavorBarreljet,flavor_barreljet);   
      event.set(tt_responseBarreljet,response_barreljet);
      event.set(tt_barreljet_ptgen,barreljet_ptgen); 
      event.set(tt_barreljet_ptptcl,barreljet_ptptcl); 
      event.set(tt_flavorProbejet,flavor_probejet);  
      event.set(tt_responseProbejet,response_probejet);   
      event.set(tt_flavorLeadingjet,flavor_leadingjet);  
      event.set(tt_flavorSubleadingjet,flavor_subleadingjet);
      event.set(tt_probejet_ptgen,probejet_ptgen);  
      event.set(tt_probejet_ptptcl,probejet_ptptcl);  
     

      event.set(tt_barreljet_statusptcl,barreljet_statusptcl);
      event.set(tt_probejet_statusptcl,probejet_statusptcl);
      event.set(tt_jet3_statusptcl,jet3_statusptcl);
      // if(debug) cout<<"NOW WE almost DONE with FLOATS!"<<endl;
      // if(debug)  cout<<"probejet_drminparton = "<<probejet_drminparton<<endl;
      // if(debug) cout<<"barreljet_drminparton = "<<barreljet_drminparton<<endl;
      event.set(tt_probejet_dRminParton,probejet_drminparton);
      event.set(tt_barreljet_dRminParton,barreljet_drminparton);
      //      if(barreljet_ptgen<0 || probejet_ptgen<0) return false;// TEST store only matched events   
      //      if(debug) cout<<"NOW WE DONE with FLOATS!"<<endl;

      if (debug) cout << "probejet_ptgen = "<<probejet_ptgen<<" barreljet_ptgen = "<<barreljet_ptgen<< " probejet_ptptcl = "<<probejet_ptptcl<<" barreljet_ptptcl = "<<barreljet_ptptcl<<endl;
      //response of leading jet
      //find corresponding genjet
      int idx_corresponding_genjet = -1;
      for(unsigned int i=0; i<event.genjets->size(); i++){
 	if(debug) cout << idx_jet_matching_genjet[i] << endl;
 	if(idx_jet_matching_genjet[i] == 0) idx_corresponding_genjet = i;
      }
      double response_jet1 = -1;
      if(idx_corresponding_genjet != -1) response_jet1 = event.jets->at(0).pt() / event.genjets->at(idx_corresponding_genjet).pt();
      event.set(tt_response_leadingjet,response_jet1);  
     
      event.set(tt_dR_GenJet_GenParticle1, dR_GenJet_GenParticle1);
      event.set(tt_dR_GenJet_GenParticle2, dR_GenJet_GenParticle2);
      event.set(tt_dR_jet3_RECO_GEN,dR_jet3_RECO_GEN);
      // event.set(tt_jet1_ptclID,-1);
      // event.set(tt_jet2_ptclID,-1);
      // event.set(tt_jet3_ptclID,-1);
      // event.set(tt_jet4_ptclID,-1);
      // event.set(tt_jet5_ptclID,-1);
      // event.set(tt_jet6_ptclID,-1);
      event.set(tt_jet1_genID,-1);
      event.set(tt_jet2_genID,-1);
      event.set(tt_jet3_genID,-1);
      event.set(tt_jet4_genID,-1);
      event.set(tt_jet5_genID,-1);
      event.set(tt_jet6_genID,-1);

      for(unsigned int idgen=0; idgen<event.genjets->size(); idgen++){
    	// if(debug) cout << idx_jet_matching_genjet[i] << endl;
 	if(idx_jet_matching_genjet[idgen]==0)  event.set(tt_jet1_genID,idgen);
 	if(idx_jet_matching_genjet[idgen]==1)  event.set(tt_jet2_genID,idgen);
 	if(idx_jet_matching_genjet[idgen]==2)  event.set(tt_jet3_genID,idgen);
 	if(idx_jet_matching_genjet[idgen]==3)  event.set(tt_jet4_genID,idgen);
 	if(idx_jet_matching_genjet[idgen]==4)  event.set(tt_jet5_genID,idgen);
 	if(idx_jet_matching_genjet[idgen]==5)  event.set(tt_jet6_genID,idgen);
      }
      event.set(tt_parton1_jetID,idx_parton_recoJet[2]);
      event.set(tt_parton2_jetID,idx_parton_recoJet[3]);
      event.set(tt_parton1_genjetID,idx_parton_genJet[2]);
      event.set(tt_parton2_genjetID,idx_parton_genJet[3]);

      
      event.set(tt_genjet_n,event.genjets->size());
      if(debug) cout<<"N genjets: "<<event.genjets->size()<<endl;
      int genptcl_n = 0;
      if(event.genparticles){
	for(GenParticle & genp: *event.genparticles){
	  //      if(genp.status()<2) continue;//TEST it does not make sense to look at status 1 particles, since we know nothing about them
	  if(genp.pt()>0) genptcl_n++;
	}
      }
      if(debug) cout<<"Number of gen particles with pt>0: "<< genptcl_n<<endl;
      event.set(tt_genptcl_n,genptcl_n);

    //calculate B from GEN jets and MET
    TVector2 ptgen, genmet;
    if(event.genmet) genmet.Set(event.genmet->pt() * cos(event.genmet->phi()),event.genmet->pt() * sin(event.genmet->phi()));
    else{
      if(debug) cout<<" event.genmet is not availble! "<<endl;
    }
    ptgen.Set(barreljet_ptgen * cos(barreljet_phigen),barreljet_ptgen* sin(barreljet_phigen));
    float Bgen = (genmet.Px()*ptgen.Px() + genmet.Py()*ptgen.Py())/((probejet_ptgen + barreljet_ptgen) * sqrt(ptgen.Px()*ptgen.Px() + ptgen.Py()*ptgen.Py())); //vec_MET*vec_ptbarr/(2ptave*ptbarr)
    event.set(tt_Bgen,Bgen);
    if(event.genmet) event.set(tt_genMET,event.genmet->pt());
    else event.set(tt_genMET,-1);
    if(debug){
      if(event.genmet){
 	cout<<" genMET: pt = "<<event.genmet->pt()<<endl;
 	genmet.Print();
      }
      cout<<" ptGen: "<<endl;
      ptgen.Print();
    }
    if(debug) cout<<" B_gen = "<<Bgen<<" B_reco = "<<event.get(tt_B)<<endl;

    } //isMC

    else{
      if(debug) cout << "before dummy gen stuff sets" << endl;
      event.set(tt_flavor3rdjet,-1);   
      event.set(tt_flavorBarreljet,-1);   
      event.set(tt_responseBarreljet,-1);   
      event.set(tt_flavorProbejet,-1);  
      event.set(tt_responseProbejet,-1);  
      event.set(tt_flavorLeadingjet,-1);  
      event.set(tt_flavorSubleadingjet,-1);  
      event.set(tt_response_leadingjet,-1);
      if(debug) cout << "in dummy gen stuff sets 1" << endl;
      event.set(tt_probejet_ptgen,-1);  
      event.set(tt_probejet_ptptcl,-1);   
      event.set(tt_barreljet_ptgen,-1);   
      event.set(tt_barreljet_ptptcl,-1); 
      event.set(tt_dR_jet3_RECO_GEN,-1);
      event.set(tt_dR_GenJet_GenParticle1, -1);
      event.set(tt_dR_GenJet_GenParticle2, -1);
      event.set(tt_genptcl_n,-1);
      event.set(tt_genjet_n,-1);
      if(debug) cout << "in dummy gen stuff sets 2" << endl;
      event.set(tt_probejet_statusptcl,-1);
      event.set(tt_barreljet_statusptcl,-1);
      event.set(tt_jet3_statusptcl,-1);
      // event.set(tt_jet1_ptclID,-1);
      // event.set(tt_jet2_ptclID,-1);
      // event.set(tt_jet3_ptclID,-1);
      // event.set(tt_jet4_ptclID,-1);
      // event.set(tt_jet5_ptclID,-1);
      // event.set(tt_jet6_ptclID,-1);
      if(debug) cout << "in dummy gen stuff sets 3" << endl;
      event.set(tt_jet1_genID,-1);
      event.set(tt_jet2_genID,-1);
      event.set(tt_jet3_genID,-1);
      event.set(tt_jet4_genID,-1);
      event.set(tt_jet5_genID,-1);
      event.set(tt_jet6_genID,-1);
      if(debug) cout << "in dummy gen stuff sets 4" << endl;
      event.set(tt_Bgen,-1);
      event.set(tt_genMET,-1);
      event.set(tt_parton1_genjetID,-1);
      event.set(tt_parton2_genjetID,-1);
      event.set(tt_parton1_jetID,-1);                                                                                                               
      event.set(tt_parton2_jetID,-1);                                                                                                               
      event.set(tt_probejet_dRminParton,-1);
      event.set(tt_barreljet_dRminParton,-1);
    }


    
   
    if(debug) {
      cout<<"After full Selection!!"<<endl;
      cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl<<endl;
    }
 
    event.set(tt_dR_jet3_barreljet,dR_jet3_barreljet);
    event.set(tt_dR_jet3_probejet,dR_jet3_probejet);   
    if(debug) cout<<"parton - GEN jet "<<event.get(tt_parton1_genjetID)<<" "<<event.get(tt_parton2_genjetID)<<" parton - RECO jet "<<event.get(tt_parton1_jetID)<<" "<<event.get(tt_parton2_jetID)<<endl;

   return true;
  }
	     
  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ExampleModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(AnalysisModule_SiJetTrg)
// XD XD XD XD XD XD XD XD XD
// // https://xkcd.com/530/
    
