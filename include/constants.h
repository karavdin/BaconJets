#pragma once

#ifndef  CONSTANTS_H
#define  CONSTANTS_H

const double eta_cut = 2.853-1e-5;
  
const int n_eta_full = 37;

const TString eta_range_full[n_eta_full] = {"-5.191","-3.839","-3.489","-3.139","-2.964","-2.853", "-2.65", "-2.5", "-2.322", "-2.172", "-1.93", "-1.653", "-1.479", "-1.305", "-1.044", "-0.783", "-0.522", "-0.261"," 0.000", "0.261", "0.522", "0.783", "1.044", "1.305", "1.479", "1.653", "1.930", "2.172", "2.322", "2.500", "2.650", "2.853", "2.964", "3.139", "3.489", "3.839", "5.191"};

const double eta_bins_full[n_eta_full]     = {-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522, -0.261, 0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};

const int n_pt = 12;

const double pt_bins[n_pt] = {
  51,
  73,
  85,
  97,
  179,
  307,
  370,
  434,
  520,
  649,1000,2000};

const TString pt_range[n_pt]={
  "51",
  "73",
  "85",
  "97",
  "179",
  "307",
  "370",
  "434",
  "520",
  "648","1000","2000"};


const int n_pt_HF = 8;

const double pt_bins_HF[n_pt_HF] = {
  73 ,
  93 ,
  113,
  176,
  239,
  318,
  1000,2000};

const TString pt_range_HF[n_pt_HF]={
  "73",
  "93",
  "113",
  "176",
  "239",
  "318",
  "1000","2000"};


const int n_pt_Si = 12;

/* //SingleJet triggers highest double checked with combined BCDEF------------- */
const double pt_bins_Si[n_pt_Si] = {
  40 ,
  72 ,
  95 ,
  160,
  226,
  283,
  344,
  443,
  577,
  606,1000,2000};

const TString pt_range_Si[n_pt_Si]={
  "40",
  "72",
  "95",
  "160",
  "226",
  "283",
  "344",
  "443",
  "577",
  "606","1000","2000"};

/* //SingleJet triggers highest End------------- */

//19 bin edges, 18 actual bins
constexpr static int n_eta = 19;
static std::vector<double>   eta_range  =  {0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};
static std::vector<double>   eta_range_mikko  = {0, 0.783, 1.305, 1.93, 2.5, 2.964, 3.2, 5.191};

static std::vector<double>   alpha_range= {0., 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25};

/** \brief Dijet event selection **/
// barrel region (|eta| < 1.3)
constexpr static float s_eta_barr = 1.3;
// two back-to-back leading jets (delta_phi(j1,j2) = min(|phi1 - phi2|, 2PI - |phi2 - phi1|) > 2.9)
constexpr static float s_delta_phi = 2.7;
// cut on the asymmetry for events with two jets  |(j2->pt - j1->pt /(j2->pt + j1->pt)| < 0.70
// constexpr static float s_asymm = 0.7;

constexpr static float s_asymm = 1.; //FIXME change back to 0.7?

 // cut on the asymmetry for events with two jets  |(j2->pt - j1->pt /(j2->pt + j1->pt)| < 0.2
/* constexpr static float s_asymm = 0.2; */
// relative third jet fraction pt_rel = 2*j3_pt/(j1_pt + j2_pt) < 0.2
constexpr static float s_pt_rel = 0.4;

/** \brief good Primary Vertex reconstruction **/
// more than four tracks
constexpr static float s_n_PvTracks = 4;
// PV is located within 24cm in z vertex
constexpr static float s_n_Pv_z = 24.0;
// PV is located within 2cm in xy direction from the nominal interaction point
constexpr static float s_n_Pv_xy = 2.0;


/** \brief The trigger thresholds of pt_ave **/


constexpr static int n_pt_bins = 9;


//from 94X max RunB to RunD
 constexpr static float s_Pt_AveMC_cut   =40;
 constexpr static float s_Pt_Ave40_cut   =40 ;
 constexpr static float s_Pt_Ave60_cut   =72 ;
 constexpr static float s_Pt_Ave80_cut   =95 ;
 constexpr static float s_Pt_Ave140_cut  =160;
 constexpr static float s_Pt_Ave200_cut  =226;
 constexpr static float s_Pt_Ave260_cut  =283;
 constexpr static float s_Pt_Ave320_cut  =344;
 constexpr static float s_Pt_Ave400_cut  =443;
 constexpr static float s_Pt_Ave450_cut  =577;
 constexpr static float s_Pt_Ave500_cut  =606;

//FIXME check the numbers below, are copy of central triggers atm
  constexpr static float s_Pt_Ave40HF_cut  =40 ;
  constexpr static float s_Pt_Ave60HF_cut  =60 ;
  constexpr static float s_Pt_Ave80HF_cut  =72 ;
 constexpr static float s_Pt_Ave140HF_cut  =160;
 constexpr static float s_Pt_Ave200HF_cut  =190;
 constexpr static float s_Pt_Ave260HF_cut  =290;
 constexpr static float s_Pt_Ave320HF_cut  =310;
 constexpr static float s_Pt_Ave400HF_cut  =390;
 constexpr static float s_Pt_Ave450HF_cut  =444;
 constexpr static float s_Pt_Ave500HF_cut  =480;   

//from Di triggers 94X 17Nov2017
 constexpr static float d_Pt_AveMC_cut   =  51;
 constexpr static float d_Pt_Ave40_cut   =  73;
 constexpr static float d_Pt_Ave60_cut   =  85;
 constexpr static float d_Pt_Ave80_cut   =  97;
 constexpr static float d_Pt_Ave140_cut  = 179;
 constexpr static float d_Pt_Ave200_cut  = 307;
 constexpr static float d_Pt_Ave260_cut  = 370;
 constexpr static float d_Pt_Ave320_cut  = 434;
 constexpr static float d_Pt_Ave400_cut  = 520;
 constexpr static float d_Pt_Ave500_cut  = 649;

//2017
//from Si triggers
constexpr static int trg_vals_Si[10]  = {40,60,80,140,200,260,320,400,450,500};
constexpr static int trg_vals_Sifwd[7]  = {60,80,140,200,260,320,400};
constexpr static int trg_vals_Si_plusfwd[17]  = {40,60,80,140,200,260,320,400,450,500,60,80,140,200,260,320,400};
//from Di triggersint trg_val
constexpr static int trg_vals_Di[9]  = {40,60,80,140,200,260,320,400,500};
constexpr static int trg_vals_HF[6]  = {60,80,100,160,220,300};
constexpr static int trg_vals_Di_plusHF[15]  = {40,60,80,140,200,260,320,400,500,60,80,100,160,220,300};

// 2017 94X 17Nov2017
constexpr static float d_Pt_Ave60HF_cut   = 73 ;
constexpr static float d_Pt_Ave80HF_cut   = 93 ;
constexpr static float d_Pt_Ave100HF_cut  = 113;
constexpr static float d_Pt_Ave160HF_cut  = 176;
constexpr static float d_Pt_Ave220HF_cut  = 239;
constexpr static float d_Pt_Ave300HF_cut  = 318;
//2017
// taken from https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2017Analysis
constexpr static int s_runnr_B = 299329; //up to this one, including this one
constexpr static int s_runnr_C = 302029; //up to this one, including this one
constexpr static int s_runnr_D = 303434; //up to this one, including this one
constexpr static int s_runnr_E = 304826; //up to this one, including this one
constexpr static int s_runnr_F = 306462; //up to this one, including this one


constexpr static float s_lumi_HF_60 = 19.605;
constexpr static float s_lumi_HF_80 = 28.773;
constexpr static float s_lumi_HF_100 = 98.341;
constexpr static float s_lumi_HF_160 = 561.485;
constexpr static float s_lumi_HF_220 = 28983.619;
constexpr static float s_lumi_HF_300 = 35672.846;

// 2017 RunB PromptReco, not completly filled, not used if apply lumi weights is false
//Lumi recorded by different triggers in pb-1
constexpr static float s_lumi_cent_40 = 0.09;
constexpr static float s_lumi_cent_60 = 0.024;
constexpr static float s_lumi_cent_80 = 0.;
constexpr static float s_lumi_cent_140 = 27.769;
constexpr static float s_lumi_cent_200 = 139.732;
constexpr static float s_lumi_cent_260 = 521.863;
constexpr static float s_lumi_cent_320 = 2965.774;
constexpr static float s_lumi_cent_400 = 9021.331;
constexpr static float s_lumi_cent_450 = 29280.311;
constexpr static float s_lumi_cent_500 = 29280.311;

/** \brief Jet Resolution Smearering **/
// doing the matching from GEN to RECO
constexpr static float s_delta_R   = 0.3; 
//constant numberstaken from https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
// from 8TeV JER measurement.
constexpr const size_t n = 7;
//static float eta_hi[n]    = {0.5, 1.1, 1.7, 2.3, 2.8, 3.2, 5.0};
constexpr static float eta_hi[n]    = {0.8, 1.3, 1.9, 2.5, 3.0, 3.2, 5.0}; ///RunII
//static float c_nominal[n] = {1.079, 1.099, 1.121, 1.208, 1.254, 1.395, 1.056};
// static float c_up[n]      = {1.105, 1.127, 1.150, 1.254, 1.316, 1.458, 1.247};
// static float c_down[n]    = {1.053, 1.071, 1.092, 1.162, 1.192, 1.332, 0.865};

constexpr static float c_nominal[n] = {1.061, 1.088, 1.106, 1.126, 1.343, 1.303, 1.320};///RunII official for 13 TeV, 25ns collisions 23/11/15

constexpr static float c_err_nominal[n] = {0.023, 0.029, 0.030, 0.094, 0.123, 0.111, 0.286};///RunII official for 13 TeV, 25ns collisions 23/11/15




/** \brief Dijet event weighting **/
// in each pt-region defined by the trigger thresholds # of events in MC and in data should equal

///Asympt Mc
constexpr static float scale_factor_noJERA[] = {3153, 11221.4, 10024.6, 9616.32, 465256, 667300, 4.138e+06, 1.43267e+07, 1.69729e+07};//run2 69000 V6 Asym
constexpr static float scale_factor_centrA[] = {3001.18, 10864.1, 9891.95, 9607.91, 464409, 667504, 4.1411e+06, 1.43601e+07, 1.69549e+07};//run2 69000 V6, cent.smear Asym
constexpr static float scale_factor_upA[] = {2896.24, 10658.4, 9750.38, 9567.18, 462895, 665397, 4.1283e+06, 1.43305e+07, 1.6918e+07};//run2 69000 V6, up.smear Asym
constexpr static float scale_factor_downA[] = {3097.2, 11091.8, 9998.62, 9635.96, 466336, 669405, 4.15346e+06, 1.43912e+07, 1.6992e+07};//run2 69000 V6, down.smear Asym
constexpr static float scale_factor_centrA_PU80[] = {3415.88, 11734.9, 10368.5, 10024.6, 483457, 693496, 4.28772e+06, 1.49127e+07, 1.76746e+07};//run2 80000 V6, cent.smear Asym

constexpr static float scale_factor_centrA_PU69_set1[] = {1119.55, 3035.73, 2778.49, 2689.78, 69284.6, 99612, 612942, 1.89493e+06, 1.83119e+06};//69mb V6, cent. Asym set1
constexpr static float scale_factor_centrA_PU69_set2[] = {424.986, 1632.72, 1493.05, 1433.51, 63826.9, 91486.2, 542606, 1.97444e+06, 1.9212e+06};//69mb V6, cent. Asym set2
constexpr static float scale_factor_centrA_PU69_set3[] = {383.799, 1531.58, 1362.94, 1349.3, 58697.6, 87290.4, 519621, 2.02935e+06, 1.9623e+06};//69mb V6, cent. Asym set3
constexpr static float scale_factor_centrA_PU69_set4[] = {302.178, 1239.91, 1109.87, 1082.25, 52135.2, 74471.4, 448186, 1.77749e+06, 1.72852e+06};//69mb V6, cent. Asym set4
constexpr static float scale_factor_centrA_PU69_set5[] = {190.486, 817.24, 742.009, 760.26, 45077.2, 65552.7, 405774, 1.50184e+06, 1.74933e+06};//69mb V6, cent. Asym set5
constexpr static float scale_factor_centrA_PU69_set6[] = {113.783, 537.28, 497.731, 477.569, 40197.2, 57013.3, 377918, 1.14542e+06, 1.84246e+06};//69mb V6, cent. Asym set6
constexpr static float scale_factor_centrA_PU69_set7[] = {260.369, 1026.12, 971.377, 927.87, 49901.1, 69802.7, 435178, 1.3947e+06, 1.6765e+06};//69mb V6, cent. Asym set7
constexpr static float scale_factor_centrA_PU69_set8[] = {127.443, 601.259, 542.876, 510.048, 46458.6, 66212.6, 435145, 1.46857e+06, 2.16278e+06};//69mb V6, cent. Asym set8
constexpr static float scale_factor_centrA_PU69_set9[] = {78.5873, 442.229, 393.594, 377.323, 38830.2, 56062.8, 363732, 1.17338e+06, 2.08058e+06};//69mb V6, cent. Asym set9


///Flat MC
//constexpr static float scale_factor_noJERF[] = {2543.11, 9228.77, 8404.76, 7916.86, 385342, 550228, 3.42556e+06, 1.17561e+07, 1.41737e+07};//run2 69000 V6 Flat
//constexpr static float scale_factor_centrF[] = {2413.77, 8916.56, 8200.09, 7844.02, 382407, 544738, 3.39795e+06, 1.17032e+07, 1.40901e+07};//run2 69000 V6, cent.smear Flat

constexpr static float scale_factor_noJERF[] = {1.99956, 3.13126, 0.774701, 0.163565, 1.20852, 0.724814, 1.5932, 2.06871, 1.32797};//run2, 76X, with pile-up reweigting

constexpr static float scale_factor_centrF[] = {2.39658,3.42565,0.750234,0.144745,1.18348,0.647537,1.684,2.22249,1.42624};//TMP!!!

//static float scale_factor1[] = {2.14563, 4.27422,7.57198,  10.7035,17.899, 15.6095, 4.64629};//run1
// static float scale_factor2[] = {242.617, 3514.77, 49549.8, 180540, 693177, 1.83449e+06, 1.63241e+07};//run1


#endif

//};
//}
