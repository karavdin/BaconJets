path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V32_noClosure_noJER_slimmedMETs_CHSPFMETjetRaw50GeV_dR04_addLowPtHF_qScale12_minGenJetPt15_minJetPt
for thr in 15
do

#  ./main --run DE -GenResponse --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_noJERSFs

   ./main --run DE -CPHadrons --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_noJERSFs

  # ./main --run DE -F -FP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_noJERSFs

#    ./main --run DE -FlavorP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_noJERSFs
  #  ./main --run DE -F -aAP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_noJERSFs

done



# path_Gl=/nfs/dust/cms/user/karavdia/JERC/17Nov2017/Residuals/Run17DEF_Data_JEC_V32_noClosure_wJER_slimmedMETs_CHSPFMETjetRaw50GeV_dR04_addLowPtHF_qScale12_minGenJetPt15_minJetPt
# for thr in 15
# do
#    ./main --run DE -F -FP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_JERSFsMadGraph
#    ./main --run DE -CPHadrons --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_JERSFsMadGraph
#    ./main --run DE -FlavorP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_JERSFsMadGraph
#    ./main --run DE -F -aAP --inputMC $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.MC.QCD_Pt15to7000_Herwig_AK4CHS_v10.root --Generator herwig --input $path_Gl${thr}_EnergyEtaCut_fixedFlavorMatching_PFcontent_Energy_HadGendR04_addExampleHadronEtaHists_fixedTriggerTh/uhh2.AnalysisModuleRunner.DATA.DATA_RunDE_17Nov17_2017.root --outSuffix _EnergyCut_HerwigppV10_minJetPt${thr}_minGenJetPt15_qScale12_JERSFsMadGraph

# done


