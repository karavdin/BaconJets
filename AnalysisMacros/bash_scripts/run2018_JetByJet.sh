path_Gl=/nfs/dust/cms/user/karavdia/JERC/RunII_102X_v1/2018/Autumn18V7_L1L2L3_NoJERsmear_JetByJet/

cd ../src

./main --run C -F -CPRecGenCompare --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --outSuffix _Flat2018Pythi8MCakaold_MadGraphDATAakanew_noJERsf
cd ../bash_scripts/