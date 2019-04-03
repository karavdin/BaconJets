path_Gl=/nfs/dust/cms/user/karavdia/JERC/RunII_102X_v1_TEST/2018/Autumn18V8_L1L2L3/
cd ../src/
./main --run D -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf

# ./main --run F -F -FP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_MadGraph_minJetPt${thr}_minGenJetPt15_qScale15

# ./main --run F -F -aAP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCDPt_pythia8_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_Pythia8_minJetPt${thr}_minGenJetPt15_qScale15

# ./main --run F -F -aAP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.MC.QCD_HT_MadGraph_AK4CHS.root --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching/uhh2.AnalysisModuleRunner.DATA.DATA_RunF_17Nov17_2017.root --outSuffix _EnergyCut_MadGraph_minJetPt${thr}_minGenJetPt15_qScale15

