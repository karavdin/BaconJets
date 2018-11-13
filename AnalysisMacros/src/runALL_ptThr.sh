path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt
for thr in 15 25 35 45
#for path in /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt15/ /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt25/ /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt35/ /nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V23_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_minJetPt45/   
do

./main --run F  -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_Pythia8_minJetPt$thr

./main --run F -F -FP --inputMC $path_Gl$thr/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl$thr/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _GenStudy_MadGraph_minJetPt$thr

done