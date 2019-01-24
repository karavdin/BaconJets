g++ -std=c++0x -Wall -o main main.C CorrectionObject.cc Derive_Thresholds_DiJet.cc Derive_Thresholds_SiJet.cc Derive_Thresholds_SiMuCrosscheck.cc CalculateMCWeights_TriggerThresholds.cc CalculateMCWeights.cc ControlPlots.cc ControlPlotsHadrons.cc kFSR_CorrectFormulae.cc kFSR_CorrectFormulae_eta.cc Pt_Extrapolation_Alternative_CorrectFormulae.cc Pt_Extrapolation_Alternative_CorrectFormulae_eta.cc L2ResOutput.cc L2ResOutput_eta.cc L2ResAllRuns.cc L2ResOverlay.cc  L2ResOverlay_JEC.cc  InputForGlobalFit.cc InputForGlobalFit_eta_0_13.cc FinalControlPlots_CorrectFormulae.cc FinalControlPlots_CorrectFormulae_eta.cc MatchingPlots.cc Lumi_Plots.cc JetMatching_Plots.cc OnOffResp_Plots.cc JetMatching_PlotsDi.cc OnOffResp_PlotsDi.cc NPVtoEtaPlots.cc  AdditionalAsymmetryPlots.cc JetEnergyFractions.cc triggerExclusivityCheck.cc useful_functions.cc tdrstyle_mod15.C Monitoring.cc trigger_study_data_run2_L1_data_corr.cxx genJetLinearity.cc MakeEtaPhiCleanTxt.cc FlavorCorrection_TTree.cc GenResponsePlots.cc GenResponsePlots_AllPtbinningOnePlot.cc Flavor_JetPFFractions.cc `root-config  --cflags --evelibs` -w
source .main_completion.sh

