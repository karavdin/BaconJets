#!/bin/bash

##This is a simple example of a SGE batch script
##Use home server with scientific linux 6 
#$ -l os=sld6 
#$ -l site=hh 
#$ -cwd
##You need to set up sframe
#$ -V 
##email Notification
#$ -m as
#$ -M xxx@desy.de
##running in local mode with 8-12 cpu slots
##$ -pe local 8-12
##CPU memory
#$ -l h_vmem=4G
##DISK memory
#$ -l h_fsize=3G   
cd DataBC_deriveThresholds_noDiJetCut_SiWithMatching_wMultTrgCheck
sframe_main DATA_RunC_promptReco_2017_24.xml

