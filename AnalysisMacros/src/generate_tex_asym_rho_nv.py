#! /usr/bin/env python

import subprocess
import sys
import os
import os.path

output_name = "ControlPlotsBC_AddAsym.tex"

img_path_base_B = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/RunB/plots/control/"

img_path_base_C = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BCD_Data/RunC/plots/control/"


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



\\title[L2 residual corrections]{Additional Asymmetry Controlplots}
\\author[Christoph Garbers]{Anastasia Karavdina, Arne Reimers, Jens Multhaup, \underline{Christoph Garbers}}
\institute[UHH]{University of Hamburg}

\date{\\today}

\\begin{document}

\\begin{frame}
 \\titlepage
\end{frame}


"""

document_end = '\end{document}'

frames_list = []

#################### Asymmetry singled out #########################

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Asymmetry to n vertices Run B, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    for j, pt in enumerate(pt_str_full[:-1]):
        if j and not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.19\\textwidth]{" + img_path_base_B +\
            "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
            "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
            "_" + pt_str_full[j + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Asymmetry Run C to n vertices, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    for j, pt in enumerate(pt_str_full[:-1]):
        if j and not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.19\\textwidth]{" + img_path_base_C +\
            "fullAsym/A_nvert_DATA_pythia8" + "_eta_" + etas_str[i] +\
            "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
            "_" + pt_str_full[j + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Asymmetry to rho Run B, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    for j, pt in enumerate(pt_str_full[:-1]):
        if j and not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.19\\textwidth]{" + img_path_base_B +\
            "fullAsym/A_rho_DATA_pythia8" + "_eta_" + etas_str[i] +\
            "_" + etas_str[i + 1] + "_pt_" + pt_str_full[j] +\
            "_" + pt_str_full[j + 1] + ".pdf}\n"
    frames_list[-1] += "\end{frame}\n\n"

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{Asymmetry Run C to rho, Eta Bin " + str(eta) + " - " + str(etas[i + 1]) + "}\n")
    for j, pt in enumerate(pt_str_full[:-1]):
        if j and not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.19\\textwidth]{" + img_path_base_C +\
            "fullAsym/A_rho_DATA_pythia8" + "_eta_" + etas_str[i] +\
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
