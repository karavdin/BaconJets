#pragma once

#include <TString.h>
#include <map>
#include <array>

//TODO get everything in a namespace, so that it can be checked against the constants from constants.h

using namespace std;

// const double eta_cut = 2.853-1e-5;
const double eta_cut = 100.; //central only

const int nResponseBins = 100;
const double Response_min = -1.2; //min of asymmetry hist
const double Response_max = 1.2; //max of asymmetry hist

const int n_etabarr=5; // needed for the normalization to 1 in the barrel. ???

const int n_enough_entries = 100;

//Alpha: 
const double alpha_cut = 0.3;
const TString s_alpha_cut = "0.3";
const TString s_alpha_cut_name = "03";
const double jet3pt_min=15;//jets with pt below were disregarded during processing
/* const double alpha_cut = 1.0; */
/* const TString s_alpha_cut = "1.0"; */
/* const TString s_alpha_cut_name = "10"; */



const int n_alpha = 11;
const TString alpha_range[n_alpha] = {"a005", "a010", "a015", "a020", "a025", "a030", "a035", "a040", "a045","a050","a055"};
const double alpha_bins[n_alpha] = {0.050, 0.100, 0.150, 0.200, 0.250, 0.300, 0.350,  0.400, 0.450,0.50,0.55};

//Pt bins:


const int n_triggerDi = 9;
const int n_triggerDi_HF = 6;
const int n_triggerSi = 10;
const int n_triggerSi_HF = 9;
const int triggerValSi[n_triggerSi] = {40, 60, 80, 140, 200, 260, 320, 400, 450, 500};
const int triggerValDi[n_triggerDi] = {40, 60, 80, 140, 200, 260, 320, 400, 500};
const int triggerValDi_HF[n_triggerDi_HF]  = {60,80,100,160,220,300};
const int triggerValSi_HF[n_triggerSi_HF]  = {60,80,140,200,260,320,400,450,500};

// const int n_pt = 11;

const int n_pt = 14;
const int n_pt_Si = 15;


// // //for Si derived trigger
// const TString pt_range[n_pt]= {"40",
// 			       "62",
// 			       "85",
// 			       "153",
// 			       "222",
// 			       "290",
// 			       "359",
// 			       "443",
// 			       "486",
// 			       "536",
// 			       "1000",
// 			       "2000"};




//for Di derived triggers
// const double pt_bins[n_pt] = {51, 51, 74, 96, 148, 214, 285, 346, 426, 525, 1000, 2000};
// const TString pt_range[n_pt]= {"51", "51", "74", "96", "148", "214", "285", "346", "426", "525", "1000", "2000"};

/*
//Brutal cut of pt bins above 307 GeV
const int n_pt = 7;
const double pt_bins[n_pt] = {//TODO check which code assumed the "min Bias" bin
  51,
  73,
  85,
  97,
  179,
  307,1000};

const TString pt_range[n_pt]={
  "51",
  "73",
  "85",
  "97",
  "179",
  "307","1000"};

const int n_pt_HF = 7;

*/
//for Di derived triggers 94X 17Nov2017
//DiJet triggers? -------------


// const double pt_bins[n_pt] = {//TODO check which code assumed the "min Bias" bin
//   51,
//   73,
//   85,
//   97,
//   140,
//   179,
//   240,
//   307,
//   370,
//   434,
//   520,
//   649,1000,2000};

// const TString pt_range[n_pt]={
//   "51",
//   "73",
//   "85",
//   "97",
//   "140",
//   "179",
//   "240",
//   "307",
//   "370",
//   "434",
//   "520",
//   "648","1000","2000"};



// // // //for Di derived triggers 94X 17Nov2017

// const int n_pt_HF = 9;

// const double pt_bins_HF[n_pt_HF] = {
//   51,
//   73,
//   93,
//   113,
//   176,
//   239,
//   318,1000,2000};

// const TString pt_range_HF[n_pt_HF]={"51","73","93","113","176","239","318","1000","2000"};

/* use central instead of HF for consitency check of new HF code */
// const int n_pt_HF = 12;

// const double pt_bins_HF[n_pt_HF] = {
//  51,
//   73,
//   85,
//   97,
//   179,
//   307,
//   370,
//   434,
//   520,
//   649,1000,2000};

// const TString pt_range_HF[n_pt_HF]={
//   "51",
//   "73",
//   "85",
//   "97",
//   "179",
//   "307",
//   "370",
//   "434",
//   "520",
//   "648","1000","2000"};
/*END  use central instead of HF for consitency check of new HF code */

//DiJet triggers? -------------

/* //SingleJet triggers? ------------- */
/*
   siTrg comparisson
RunB      RunC  RunD  highest
40       40     40    40    40
62       65     53    65    40 
70       71     74    74    72 
100      100    94    100   95 
165      160    158   165   160
226      225    222   226   226
285      285    284   285   283
344      346    345   346   344
445      440    443   445   443
566      560    564   566   577
604      608    598   608   606

siTrg HF comparisson
thresh    RunD    RunE    RunC    highest
60 	 50.23    50.80   67.06   67
80       95.41    94.86   95.66   96
140	 154.45   154.88  154.29  155
200	 228.65   229.43  231.21  231
260	 286.16   289.35  295.62  296
320	 366.11   361.42  360     366
400	 430.72   435.49  432.95  436
450 and 500 have too low statistic

const double pt_bins[n_pt] = {
40 ,
65 ,
74  ,
100 ,
165 ,
226 ,
285 ,
346 ,
445 ,
566 ,
608 ,1000,2000};

const TString pt_range[n_pt]={
  "40",
  "65",
  "74",
  "100",
  "165",
  "226",
  "285",
  "346",
  "445",
  "566",
  "608","1000","2000"};

  siTrg comparisson (2nd attempt)
RunB      RunC  RunD  highest
28        33      39    39
72        72      72    72
77        77      95    95
160       159     159  160
226       226     226  226
283       283     281  283
344       343     343  344
443       441     442  443
577       563     567  577
606       603     599  606
*/

const double pt_bins[n_pt_Si] = {
40 ,
72  ,
95 ,
130,
160 ,
190,
226 ,
250,
283 ,
344 ,
443 ,
577 ,
606 ,1000,2000};

const TString pt_range[n_pt_Si]={
  "40" ,
  "72" ,
  "95" ,
  "130",
  "160",
  "190",
  "226",
  "250",
  "283",
  "344",
  "443",
  "577",
  "606","1000","2000"};

const int n_pt_HF = 11;

const double pt_bins_HF[n_pt_HF] = {
 60  ,
 72  ,
 160 ,
 190 ,
 290 ,
 310 ,
 390,
 444,
 480,
  1000,2000};

const TString pt_range_HF[n_pt_HF]={"60",
				    "72",
				    "160",
				    "190",
				    "290",
				    "310",
				    "390",
				    "444",
				    "480","1000","2000"};


/* // [END]SingleJet triggers? ------------- */


// const double pt_bins_Si[n_pt_Si] = {
//  40 ,
//  65 ,
//  74  ,
//  100 ,
//  165 ,
//  226 ,
//  285 ,
//  346 ,
//  445 ,
//  566 ,
//  608 ,1000,2000};





// const double pt_bins_HF[n_pt] = {60,80,100,160,220,300, 1000, 2000};
// const TString pt_range_HF[n_pt]= {"60","80","100","160","220","300", "1000", "2000"};

// di from back to back with trg matching
// 	 50.02 
// 	 70.91 
// 	 91.80 
// 	 161.66 
// 	  240
// 	 278.90 
// 	 343.21 
// 	 425.20 
// 	 523.62 

//Eta bins:

/* const int n_eta = 2; */
/* const TString eta_range[n_eta] = {"0.000", "0.261",}; */
/* const TString eta_range2[n_eta] = {"00", "0261"}; */
/* const double eta_bins[n_eta]     = {0, 0.261}; */

//Abs eta range:

const int n_eta = 19;
const TString eta_range[n_eta] = {"0.000", "0.261", "0.522", "0.783", "1.044", "1.305", "1.479", "1.653", "1.930", "2.172", "2.322", "2.500", "2.650", "2.853", "2.964", "3.139", "3.489", "3.839", "5.191"};
const TString eta_range2[n_eta] = {"00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193", "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"};
const double eta_bins[n_eta]     = {0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};

// const int n_eta = 37;

// const TString eta_range[n_eta] = {
//   "0.000",
//   "0.130",
//   "0.261",
//   "0.391",
//   "0.522",
//   "0.652",
//   "0.783",
//   "0.913",
//   "1.044",
//   "1.194",
//   "1.305",
//   "1.390",
//   "1.479",
//   "1.520",
//   "1.653",
//   "1.783",
//   "1.930",
//   "2.060",
//   "2.172",
//   "2.250",
//   "2.322",
//   "2.452",
//   "2.500",
//   "2.570",
//   "2.650",
//   "2.750",
//   "2.853",
//   "2.900",
//   "2.964",
//   "3.034",
//   "3.139",
//   "3.239",
//   "3.489",
//   "3.619",
//   "3.839",
//   "4.000",
//   "5.191"  
// };

// const TString eta_range2[n_eta] = {
//    "00",
//   "013",
//   "0261",
//   "0391",
//   "0522",
//   "0652",
//   "0783",
//   "0913",
//   "1044",
//   "1194",
//   "1305",
//   "139",
//   "1479",
//   "152",
//   "1653",
//   "1783",
//   "193",
//   "206",
//   "2172",
//   "225",
//   "2322",
//   "2452",
//   "25",
//   "257",
//   "265",
//   "275",
//   "2853",
//   "29",
//   "2964",
//   "3034",
//   "3139",
//   "3239",
//   "3489",
//   "3619",
//   "3839",
//   "4",
//   "5191"  
// };

// const double eta_bins[n_eta]     = {
//   0.000,
//   0.130,
//   0.261,
//   0.391,
//   0.522,
//   0.652,
//   0.783,
//   0.913,
//   1.044,
//   1.194,
//   1.305,
//   1.390,
//   1.479,
//   1.520,
//   1.653,
//   1.783,
//   1.930,
//   2.060,
//   2.172,
//   2.250,
//   2.322,
//   2.452,
//   2.500,
//   2.570,
//   2.650,
//   2.750,
//   2.853,
//   2.900,
//   2.964,
//   3.034,
//   3.139,
//   3.239,
//   3.489,
//   3.619,
//   3.839,
//   4.000,
//   5.191
// };



//Negative Eta Range

const int n_eta_full = 37;

const TString eta_range_full[n_eta_full] = {"-5.191","-3.839","-3.489","-3.139","-2.964","-2.853", "-2.65", "-2.5", "-2.322", "-2.172", "-1.93", "-1.653", "-1.479", "-1.305", "-1.044", "-0.783", "-0.522", "-0.261"," 0.000", "0.261", "0.522", "0.783", "1.044", "1.305", "1.479", "1.653", "1.930", "2.172", "2.322", "2.500", "2.650", "2.853", "2.964", "3.139", "3.489", "3.839", "5.191"};
const TString eta_range2_full[n_eta_full] = {"-5191","-3839","-3489","-3139","-2964","-2853", "-265", "-25", "-2322", "-2172", "-193", "-1653", "-1479", "-1305", "-1044", "-0783", "-0522", "-0261","00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193", "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"};
const double eta_bins_full[n_eta_full]     = {-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522, -0.261, 0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};


const double eta_bins2[19]     = { 0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};

const int n_alpha_common = 4;
const TString alpha_range_common[n_alpha_common] = {"a10","a15", "a20", "a30"};//for Global fit we produce result only in few alpha values
const double alpha_bins_common[n_alpha_common] = {0.100, 0.150, 0.200, 0.300};

const int n_eta_common = 19;
const double eta_common_bins[n_eta_common] ={0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};
const TString eta_common_range[n_eta_common] = {"0.000", "0.261", "0.522", "0.783", "1.044", "1.305", "1.479", "1.653", "1.930", "2.172", "2.322", "2.500", "2.650", "2.853", "2.964", "3.139", "3.489", "3.839", "5.191"};

const TString eta_output[n_eta_common-1] = {"eta_00_03", "eta_03_05","eta_05_08","eta_08_10","eta_10_13","eta_13_15","eta_15_17", "eta_17_19", "eta_19_22", "eta_22_23", "eta_23_25", "eta_25_27", "eta_27_29", "eta_29_30", "eta_30_31", "eta_31_35", "eta_35_38", "eta_38_52"};  

const int n_eta_common_2 = 7;
const double eta_common_bins_2[n_eta_common_2] ={
  0.,
  1.305,
  1.93,
  2.5,
  2.964,
  3.2,
  5.191
};
const TString eta_common_range_2[n_eta_common_2] = {
  "0.000",
  "1.305",
  "1.930",
  "2.500",
  "2.964",
  "3.200",
  "5.191"};

const TString eta_output_2[n_eta_common_2-1] = {"eta_00_13", "eta_13_19","eta_19_25","eta_25_30","eta_30_32","eta_32_52"};


//LumiBins for the Runs
const int lumibins_BC[3] = {0, 1, 2};
const int lumibins_B[2] = {0, 1};
const int lumibins_C[1] = {2};
