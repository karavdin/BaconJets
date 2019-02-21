path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V32_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_dR04_addLowPtHF_qScale15_minGenJetPt15_minJetPt
for thr in 15
do

./main --run F -F -FP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_Pythia8_minJetPt${thr}_minGenJetPt15_qScale15

./main --run F -F -FP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_MadGraph_minJetPt${thr}_minGenJetPt15_qScale15

./main --run F -F -aAP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_Pythia8_minJetPt${thr}_minGenJetPt15_qScale15

./main --run F -F -aAP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_MadGraph_minJetPt${thr}_minGenJetPt15_qScale15

done