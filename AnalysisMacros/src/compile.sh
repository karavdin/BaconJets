g++ -std=c++0x -Wall -o main main.C CorrectionObject.cc CalculateMCWeights.cc ControlPlots.cc kFSR.cc kFSR_CorrectFormulae.cc Pt_Extrapolation.cc Pt_Extrapolation_Alternative.cc Pt_Extrapolation_Alternative_CorrectFormulae.cc  L2ResOutput.cc L2ResAllRuns.cc L2ResOverlay.cc InputForGlobalFit.cc InputForGlobalFit_eta_0_13.cc  FinalControlPlots.cc FinalControlPlots_CorrectFormulae.cc useful_functions.cc tdrstyle_mod15.C `root-config  --cflags --evelibs`