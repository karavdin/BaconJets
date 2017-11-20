#! /usr/bin/env python

import subprocess
import sys
import os
import os.path

output_name = "controlplotsC_newPtBinning.tex"
# print len(sys.argv)
# for a in sys.argv:
#     print a

if len(sys.argv) > 1:
    output_name = sys.argv[1] + ".tex"

img_path_base_2 = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/"
if output_name.find("controlplotsBCD") > -1:
    img_path_base_2 = img_path_base_2 + "RunBCD_trgMatchingWOldThresh"
elif output_name.find("controlplotsBC") > -1:
    img_path_base_2 = img_path_base_2 + "RunBC_trgMatchingWOldThresh"
elif output_name.find("controlplotsC") > -1:
    img_path_base_2 = img_path_base_2 + "RunC_trgMatchingWOldThresh"
elif output_name.find("controlplotsB") > -1:
    img_path_base_2 = img_path_base_2 + "RunB_trgMatchingWOldThresh"
elif output_name.find("controlplotsD") > -1:
    img_path_base_2 = img_path_base_2 + "RunD"
else:
    raise RuntimeError("Cant identifiy ouput name %s" % output_name)

img_path_base_2 = img_path_base_2 + "/plots/"

if not os.path.isdir(img_path_base_2):
    raise RuntimeError("Path %s does not exist" % img_path_base_2)

img_path_base = img_path_base_2 + "control/"
img_path_base_B = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/RunB_trgMatchingWOldThresh/plots/control/"
img_path_base_C = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/RunC_trgMatchingWOldThresh/plots/control/"
img_path_baseMain_B = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/RunB_trgMatchingWOldThresh/plots/"
img_path_baseMain_C = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/RunC_trgMatchingWOldThresh/plots/"

etas = [0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.930,
        2.172, 2.322, 2.500, 2.650, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191]

etas_str = ["00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193",
            "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"]

pt_str_full = ["40", "62", "85", "153", "222", "290",
               "359", "443", "486", "536", "1000", "2000"]

pt_str = pt_str_full[1:];

trigger_val = ["40", "60", "80", "140",
               "200", "260", "320", "400", "450", "500"]

pic_bases = [  # "alpha_pythia8",
    "A_NormDistribution_DATA_pythia8",
    # "A_NormDistribution_MC_pythia8",
    "Rel_Response_pythia8",
    "B_NormDistribution_DATA_pythia8",
    # "B_NormDistribution_MC_pythia8",
    #"jet3_pt_pythia8",
    #"METoverPt_DATA_pythia8",
    #"MET_pythia8",
    "MPF_Response_pythia8",
    # "Pt_ave_pythia8",

    # "probejet_phi_DATA_pythia8",
    # "probejet_phi_MC_pythia8",

    "probejet_chEmEF_DATA_pythia8",
    # "probejet_chEmEF_MC_pythia8",
    "probejet_chHadEF_DATA_pythia8",
    # "probejet_chHadEF_MC_pythia8",
    "probejet_muonEF_DATA_pythia8",
    # "probejet_muonEF_MC_pythia8",
    "probejet_neutEmEF_DATA_pythia8",
    # "probejet_neutEmEF_MC_pythia8",
    "probejet_neutHadEF_DATA_pythia8",
    # "probejet_neutHadEF_MC_pythia8",
    "probejet_photonEF_DATA_pythia8",
    # "probejet_photonEF_MC_pythia8",
]

pic_bases_MC = [  # "alpha_pythia8",
    # "A_NormDistribution_DATA_pythia8",
    "A_NormDistribution_MC_pythia8",
    # "Rel_Response_pythia8",
    # "B_NormDistribution_DATA_pythia8",
    "B_NormDistribution_MC_pythia8",
    #"jet3_pt_pythia8",
    #"METoverPt_DATA_pythia8",
    #"MET_pythia8",
    # "MPF_Response_pythia8",
    # "Pt_ave_pythia8",

    # "probejet_phi_DATA_pythia8",
    # "probejet_phi_MC_pythia8",

    # "probejet_chEmEF_DATA_pythia8",
    "probejet_chEmEF_MC_pythia8",
    # "probejet_chHadEF_DATA_pythia8",
    "probejet_chHadEF_MC_pythia8",
    # "probejet_muonEF_DATA_pythia8",
    "probejet_muonEF_MC_pythia8",
    # "probejet_neutEmEF_DATA_pythia8",
    "probejet_neutEmEF_MC_pythia8",
    # "probejet_neutHadEF_DATA_pythia8",
    "probejet_neutHadEF_MC_pythia8",
    # "probejet_photonEF_DATA_pythia8",
    "probejet_photonEF_MC_pythia8",
]


single_pics = [
    "kFSR_AK4PFchs_pythia8",
    "L2Res_kFSRfit_AK4PFchs_pythia8",
    "L2Res_kFSRval_AK4PFchs_pythia8",
    "L2Res_logpt_DiJet_kFSRfit_AK4PFchs_pythia8",
    # "L2Res_logpt_DiJet_kFSRfit_diffAK4PFchs_pythia8",
    "L2Res_logpt_MPF_DiJet_kFSRfitAK4PFchs_pythia8",
    "L2Res_logpt_MPF_kFSRfit_AK4PFchs_pythia8",
    # "L2Res_logpt_MPF_kFSRfit_diffAK4PFchs_pythia8",
]

first_pics = [
    "kFSR_AK4PFchs_pythia8",
    "L2Res_kFSRfit_AK4PFchs_pythia8",
    "L2Res_kFSRval_AK4PFchs_pythia8",
    "L2Res_logpt_MPF_kFSRfit_AK4PFchs_pythia8",
    "L2Res_logpt_DiJet_kFSRfit_AK4PFchs_pythia8",
    "L2Res_logpt_MPF_DiJet_kFSRfitAK4PFchs_pythia8",
]

document_base = """
\documentclass[t,compress]{beamer}
\mode<presentation>{
%\usetheme{CambridgeUS}
\usetheme{Madrid}
\usecolortheme{beaver}
}

\usepackage{graphicx} % Allows including images
\usepackage[percent]{overpic}
\usepackage{hyperref}
\usepackage{booktabs}
\usepackage{amsmath}
\usepackage{upgreek}
%\usepackage{adjustbox}
\usepackage{setspace}

\usepackage{amsmath,amssymb}
\usepackage{color}

\usepackage{xcolor}
\usepackage{pict2e}

\usepackage{overpic}

\\newcommand{\\backupbegin}{
   \\newcounter{finalframe}
   \setcounter{finalframe}{\\value{framenumber}}
}
\\newcommand{\\backupend}{
   \setcounter{framenumber}{\\value{finalframe}}
}



\\title[L2 residual corrections]{2017 L2 residual corrections derived on di-jet events: State in September and Controlplots}
\\author[Christoph Garbers]{Anastasia Karavdina, Arne Reimers, Jens Multhaup, \underline{Christoph Garbers}}
\institute[UHH]{University of Hamburg}

\date{\\today}

\\begin{document}

\\begin{frame}
 \\titlepage
\end{frame}


"""

document_end = '\\backupend\n\end{document}'

frames_list = []

################ main frames #########################

frames_list.append(
    """
    \\begin{frame}{Differences to 2016 data}
    \\begin{itemize}
    \item For RunB and RunC no HLT Di-Jet Trigger available, Single-Jet Trigger (HLT PFJet)  followed by a Di-Jet selectin are used. \n\\newline\nUsed Data: JetH PromptReco RunB and RunC 
    \item Compare to 2016 MC until 2017 is ready. \n\\newline\nUsed MC: Flat QCD pythia8
    \item Used JEC version: Summer16 03Feb2017 V3
    \end{itemize}
trigger object jet matched
    \end{frame}

    """
)


### Run B C #####
################ kFSR #########################


frames_list.append(
    "\\begin{frame}{L2Res with 2017 Run BC}\n")
for i, spic in enumerate(first_pics):
    if i and not i % 3:
        frames_list[-1] += "\\newline\n\n"
    frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
    frames_list[-1] += "\t\\tiny  " + \
        spic.replace("_", " ").replace("pythia8", " ").replace(
            "AK4PFchs", " ").replace("logpt", " ") + "\n \t\\newline\n"
    frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_2 + \
        spic + ".pdf}\n"
    frames_list[-1] += "\end{minipage}\n"
frames_list[-1] += "\end{frame}\n\n"

frames_list.append(
    "\\begin{frame}{L2Res with 2017 Run B}\n")
for i, spic in enumerate(first_pics):
    if i and not i % 3:
        frames_list[-1] += "\\newline\n\n"
    frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
    frames_list[-1] += "\t\\tiny  " + \
        spic.replace("_", " ").replace("pythia8", " ").replace(
            "AK4PFchs", " ").replace("logpt", " ") + "\n \t\\newline\n"
    frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_baseMain_B + \
        spic + ".pdf}\n"
    frames_list[-1] += "\end{minipage}\n"
frames_list[-1] += "\end{frame}\n\n"

frames_list.append(
    "\\begin{frame}{L2Res with 2017 Run C}\n")
for i, spic in enumerate(first_pics):
    if i and not i % 3:
        frames_list[-1] += "\\newline\n\n"
    frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
    frames_list[-1] += "\t\\tiny  " + \
        spic.replace("_", " ").replace("pythia8", " ").replace(
            "AK4PFchs", " ").replace("logpt", " ") + "\n \t\\newline\n"
    frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_baseMain_C + \
        spic + ".pdf}\n"
    frames_list[-1] += "\end{minipage}\n"
frames_list[-1] += "\end{frame}\n\n"


################ thresholds #########################

frames_list.append(
    "\\begin{frame}{Single PF Jet Trigger Thresholds RunBC}\n")
frames_list[-1] += """
\\begin{tabular}{|c|c|c|}
  \hline
  trigger path & 0.95 threshold & threshold 2016 [GeV] \\\\\hline
 HLT\_PFJet40\_v* & 40 & 51 \\\\ \hline
 HLT\_PFJet60\_v* & 62 & 73 \\\\ \hline
 HLT\_PFJet80\_v* & 85 & 95\\\\ \hline
  HLT\_PFJet140\_v* & 153 & 129\\\\ \hline
 HLT\_PFJet200\_v* & 222 & 163\\\\ \hline
 HLT\_PFJet260\_v* & 290 & 230\\\\ \hline
 HLT\_PFJet320\_v* & 359 & 299\\\\ \hline
 HLT\_PFJet400\_v* & 443 & 365\\\\ \hline
  HLT\_PFJet450\_v* & 486 & 453\\\\ \hline
  HLT\_PFJet500\_v* & 536 & 566\\\\ \hline
\end{tabular}
thresholds were derived without the jet matching
"""
frames_list[-1] += "\end{frame}\n\n"


########## Asym Examples ##########


frames_list.append(
    "\\begin{frame}{Not Understood: Asymmetry Distribution}\n")
frames_list[-1] += "\t\scriptsize $A=\\frac{p_t^{tag}-p_t^{probe}}{p_t^{tag}+p_t^{probe}}$, jets are assigned randomly from the two leading jets. Only one trigger is used per pt-bin.\n\\newline\n"
i = 0
j = 2
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run B\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 3
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run B\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 9
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run B\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
frames_list[-1] += "\\newline\n"

i = 0
j = 2
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run C\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 3
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run C\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 9
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run C\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\t\n"
frames_list[-1] += "\end{frame}\n\n"


frames_list.append(
    "\\begin{frame}{Not Understood: Asymmetry Distribution, does not look pile-up dependend}\n")
i = 0
j = 2
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run B\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 3
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run B\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 9
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run B\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
frames_list[-1] += "\\newline\n"

i = 0
j = 2
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run C\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 3
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run C\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\n"
i = 9
j = 8
frames_list[-1] += "\\begin{minipage}{0.3\\textwidth}\n"
frames_list[-1] += "\t\scriptsize Run C\n\t\\newline\n"
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
    "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
    "_" + pt_str_full[j + 1] + ".pdf}\n"
frames_list[-1] += "\end{minipage}\t\n"
frames_list[-1] += "\end{frame}\n\n"


frames_list.append(
    "\\begin{frame}{Jet Properties after Selection for Run B}\n")
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_B +\
    "ControlPlots_Selection_pythia8_jets.pdf} \n"
frames_list[-1] += "\end{frame}\n\n"

frames_list.append(
    "\\begin{frame}{Jet Properties after Selection for Run C}\n")
frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + img_path_base_C +\
    "ControlPlots_Selection_pythia8_jets.pdf} \n"
frames_list[-1] += "\end{frame}\n\n"

################ backup ##################################################

frames_list.append(
    """
    \\backupbegin
    \\begin{frame}
    Backup
    \end{frame}

    """
)


############# eta loop B  #########################

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Run B, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases[:4]):
        if j and not j % 2:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_B + "control/" + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"
    frames_list.append(
        "\\begin{frame}{Run B, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases[4:10]):
        if j and not j % 3:
            frames_list[-1] += "\\newline\n\n"
            frames_list[-1] += "\\vspace{-0.65cm}\n"
        frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_B + "control/" + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"

    frames_list.append(
        "\\begin{frame}{Run B, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    frames_list[-1] += "\t Pt: \includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_B + \
        "kFSR_Pt" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_B + \
        "kFSR_Pt_pythia8" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\\newline\n\n"
    frames_list[-1] += "\t MPF: \includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_B + \
        "kFSR_MPF" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_B + \
        "kFSR_MPF_pythia8" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

    frames_list.append(
        "\\begin{frame}{Run B Jet Pt, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base_B + \
        "fullAsym/jet1_pt_DATA_pythia8_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base_B + \
        "fullAsym/jet2_pt_DATA_pythia8_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base_B + \
        "fullAsym/jet3_pt_DATA_pythia8_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

############# eta loop C  #########################

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Run C, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases[:4]):
        if j and not j % 2:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_C + "control/" + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"
    frames_list.append(
        "\\begin{frame}{Run C, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases[4:10]):
        if j and not j % 3:
            frames_list[-1] += "\\newline\n\n"
            frames_list[-1] += "\\vspace{-0.65cm}\n"
        frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_C + "control/" + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"

    frames_list.append(
        "\\begin{frame}{Run C, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    frames_list[-1] += "\t Pt: \includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_C + \
        "kFSR_Pt" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_C + \
        "kFSR_Pt_pythia8" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\\newline\n\n"
    frames_list[-1] += "\t MPF: \includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_C + \
        "kFSR_MPF" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_baseMain_C + \
        "kFSR_MPF_pythia8" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

    frames_list.append(
        "\\begin{frame}{Run C Jet Pt, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base_C + \
        "fullAsym/jet1_pt_DATA_pythia8_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base_C + \
        "fullAsym/jet2_pt_DATA_pythia8_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base_C + \
        "fullAsym/jet3_pt_DATA_pythia8_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"


############# eta loop MC  #########################

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{MC, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases_MC[:]):
        if j and not j % 4:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.24\\textwidth]{" + img_path_baseMain_C + "control/" + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"


#################### Asymmetry singled out #########################

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Asymmetry Run B, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    for j, pt in enumerate(pt_str_full[:-1]):
        if j and not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.19\\textwidth]{" + img_path_base_B +\
            "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
            "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
            "_" + pt_str_full[j + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Asymmetry Run C, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    for j, pt in enumerate(pt_str_full[:-1]):
        if j and not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.19\\textwidth]{" + img_path_base_C +\
            "fullAsym/A_DATA_pythia8" + "_eta_" + etas_str[i] +\
            "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
            "_" + pt_str_full[j + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"


#################### Put everything together #########################

with open(output_name, 'w') as file_:
    file_.write(document_base)
    for frame in frames_list:
        file_.write(frame)
    file_.write(document_end)

print "\ngenerated " + output_name + "\n"
