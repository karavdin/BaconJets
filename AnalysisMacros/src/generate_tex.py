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

img_path_base_2 = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/"
if output_name.find("controlplotsBCD") > -1:
    if output_name.find("newPtBinning") > -1:
        img_path_base_2 = img_path_base_2 + "RunBCD_newPtBinning"
    else:
        img_path_base_2 = img_path_base_2 + "RunBCD"
elif output_name.find("controlplotsBC") > -1:
    if output_name.find("newPtBinning") > -1:
        img_path_base_2 = img_path_base_2 + "RunBC_newPtBinning"
    else:
        img_path_base_2 = img_path_base_2 + "RunBC"
elif output_name.find("controlplotsC") > -1:
    if output_name.find("newPtBinning") > -1:
        img_path_base_2 = img_path_base_2 + "RunC_newPtBinning"
    else:
        img_path_base_2 = img_path_base_2 + "RunC"
elif output_name.find("controlplotsB") > -1:
    if output_name.find("newPtBinning") > -1:
        img_path_base_2 = img_path_base_2 + "RunB_newPtBinning"
    else:
        img_path_base_2 = img_path_base_2 + "RunB"
elif output_name.find("controlplotsD") > -1:
    if output_name.find("newPtBinning") > -1:
        img_path_base_2 = img_path_base_2 + "RunD_newPtBinning"
    else:
        img_path_base_2 = img_path_base_2 + "RunD"

else:
    raise RuntimeError("Cant identifiy ouput name %s" % output_name)

img_path_base_2 = img_path_base_2 + "/plots/"

if not os.path.isdir(img_path_base_2):
    raise RuntimeError("Path %s does not exist" % img_path_base_2)

img_path_base = img_path_base_2 + "control/"

img_path_base_B = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/RunB/plots/control/"

img_path_base_C = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/RunC/plots/control/"

img_path_baseMain_B = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/RunB/plots/"

img_path_baseMain_C = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/RunC/plots/"


img_path_base_th = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data_DeriveThresholds_noDiJCut/RunC/plots/thresholds/"


etas = [0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.930,
        2.172, 2.322, 2.500, 2.650, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191]

etas_str = ["00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193",
            "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"]

pt_str = ["70", "99", "164", "238", "306",
          "369", "459", "487", "537", "1000", "2000"]

pt_str_full = ["41", "70", "99", "164", "238", "306",
               "369", "459", "487", "537", "1000", "2000"]

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
    \end{frame}

    """
)

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
    "\\begin{frame}{Single PF Jet Trigger Thresholds}\n")
frames_list[-1] += "\tThresholds taken out of Run C, agrees with Run B.\n\\newline\n\\newline"

frames_list[-1] += """
\\begin{tabular}{|c|c|c|}
  \hline
  trigger & 0.95 threshold [GeV] & threshold 2016 [GeV] \\\\\hline
  40 & 41 & 51 \\\\ \hline
  60 & 70 & 73 \\\\ \hline
  80 & 99 & 95\\\\ \hline
  140 & 164 & 129\\\\ \hline
  200 & 238 & 163\\\\ \hline
  260 & 306 & 230\\\\ \hline
  320 & 369 & 299\\\\ \hline
  400 & 459 & 365\\\\ \hline
  450 & 487 & 453\\\\ \hline
  500 & 537 & 566\\\\ \hline
\end{tabular}
"""
frames_list[-1] += "\end{frame}\n\n"

frames_list.append(
    "\\begin{frame}{Single PF Jet Trigger Thresholds}\n")
frames_list[-1] += "\t\scriptsize shown is $\\varepsilon = \\frac{N(\\text{low and high trg})}{N(\\text{low trg})}$, dotted (full) line marks 0.9 (0.95) of plateau\n\t\\newline\n"

for i, th in enumerate(trigger_val[1:]):
    if i and not i % 4:
        frames_list[-1] += "\t\\newline\n\n"
    frames_list[-1] += "\\begin{minipage}{0.24\\textwidth}\n"
    frames_list[-1] += "\t\\tiny HLT " + th + "\n \\newline\n"
    frames_list[-1] += "\t\includegraphics[width=\\textwidth]{" + \
        img_path_base_th + "HLT_PFJet"
    frames_list[-1] += th
    frames_list[-1] += ".pdf}\n"
    frames_list[-1] += "\end{minipage}\n"
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


#################### Asymmetry Cut stuff #########################

# for i, eta in enumerate(etas[:-1]):
#     frames_list.append(
#         "\\begin{frame}{with abs(A)$<$0.05 cut " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

#     for j, pic_base in enumerate(pic_bases[:8]):
#         if j and not j % 4:
#             frames_list[-1] += "\\newline\n\n"
#         frames_list[-1] += "\t\includegraphics[width=0.24\\textwidth]{" + img_path_base + \
#             pic_base + "_eta_" + etas_str[i] + \
#             "_" + etas_str[i + 1] + "_wAsymCut.pdf}\n"

#     frames_list[-1] += "\end{frame}\n\n"
#     frames_list.append(
#         "\\begin{frame}{with abs(A)$<$" + str(eta) + " - " + str(etas[i + 1]) + "}\n")

#     for j, pic_base in enumerate(pic_bases[8:20]):
#         if j and not j % 4:
#             frames_list[-1] += "\\newline\n\n"
#             frames_list[-1] += "\\vspace{-0.65cm}\n"
#         frames_list[-1] += "\t\includegraphics[width=0.24\\textwidth]{" + img_path_base + \
#             pic_base + "_eta_" + etas_str[i] + \
#             "_" + etas_str[i + 1] + "_wAsymCut.pdf}\n"

#     frames_list[-1] += "\end{frame}\n\n"


#################### Put everything together #########################

with open(output_name, 'w') as file_:
    file_.write(document_base)
    for frame in frames_list:
        file_.write(frame)
    file_.write(document_end)

print "\ngenerated " + output_name + "\n"
