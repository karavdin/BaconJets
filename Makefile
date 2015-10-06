LIBRARY := SUHH2BaconJets
#TEST := 1
#USERCXXFLAGS := -Wno-unused-parameter -Wno-unused-variable -frtti
USERLDFLAGS := -lSUHH2core -lSUHH2common -lSUHH2bacondataformats
PAR := 1
include ../Makefile.common

