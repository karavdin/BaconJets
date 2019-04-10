path_Gl=/nfs/dust/cms/user/karavdia/JERC/RunII_102X_v1/2018/Autumn18V7_L1L2L3_NoJERsmear_FixCS/
cd ../src/

./main --run A -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunA_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

./main --run A -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunA_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

./main --run A -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunA_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 

./main --run A -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunA_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 


./main --run B -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunB_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

./main --run B -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunB_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

./main --run B -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunB_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 

./main --run B -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunB_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 


./main --run D -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

./main --run D -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

./main --run D -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 

./main --run D -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 


# ./main --run C -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunC_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

# ./main --run C -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunC_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

# ./main --run C -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunC_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 

# ./main --run C -F -aAP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunC_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 


#./main --run D -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_MadGraph --Generator madgraph

#./main --run D -F -FP --inputMC $path_Gl/uhh2.AnalysisModuleRunner.MC.QCD_Flat2018_pythia8_2018_AK4CHS.root --input $path_Gl/uhh2.AnalysisModuleRunner.DATA.DATA_RunD_2018_AK4CHS.root --outSuffix _Flat2018_noJERsf_Pythia8 


