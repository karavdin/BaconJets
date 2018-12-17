#path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_barrel3rdJet_minGenJetPt15_minJetPt
path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_dR04_addLowPtHF_qScale15_minGenJetPt15_minJetPt
#path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minGenJetPt5_minJetPt
#for thr in 15 25 35 45
#for thr in 15 25 35
#for thr in 0 15 25 35 45
#for thr in 25 35
for thr in 15
#for thr in 5
#for path in /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt15/ /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt25/ /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt35/ /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt45/   
do
# ./main --run F  -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_minPtAve250_minJetPt$thr

# ./main --run F -F -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_minPtAve250_minJetPt$thr

#./main --run F -kFSR --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_minJetPt$thr

#./main --run F -kFSR --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_minJetPt$thr

# ./main --run F -F -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_invertedEnergyEtaCutinFlavor_minJetPt$thr

# ./main --run F -F -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_invertedEnergyEtaCutinFlavor_minJetPt$thr

./main --run F -JEF --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_invertedEnergyEtaCutinFlavor_minJetPt$thr

./main --run F -JEF --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_invertedEnergyEtaCutinFlavor_minJetPt$thr


#./main --run F -F -aAP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_minJetPt$thr

#./main --run F -F -aAP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_minJetPt$thr

# ./main --run F -F -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_barrel3rdJet_minJetPt$thr

# ./main --run F -F -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_barrel3rdJet_minJetPt$thr

done