#! /usr/bin/env python

import subprocess

img_path_base = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/RunBC/plots/control/"

img_path_base_2 = "/nfs/dust/cms/user/garbersc/forBaconJets/2017PromptReco/Residuals/Run17BC_Data/RunBC/plots/"


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

\\title[L2 residual corrections]{L2 residual corrections derived on di-jet events: Controlplots}
\\author[Christoph Garbers]{Anastasia Karavdina, Arne Reimers, Jens Multhaup, \underline{Christoph Garbers}}
\institute[UHH]{University of Hamburg}

\date{\\today}

\\begin{document}

\\begin{frame}
 \\titlepage
\end{frame}

"""

document_end = '\end{document}'

etas = [0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.930,
        2.172, 2.322, 2.500, 2.650, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191]

etas_str = ["00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193",
            "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"]

pt_str = ["73", "95", "129", "163", "230",
          "299", "365", "453", "566", "1000", "2000"]

pic_bases = [  # "alpha_pythia8",
    "A_NormDistribution_DATA_pythia8",
    "A_NormDistribution_MC_pythia8",
    #"B_NormDistribution_DATA_pythia8",
    #"B_NormDistribution_MC_pythia8",
    #"jet3_pt_pythia8",
    #"METoverPt_DATA_pythia8",
    #"MET_pythia8",
    "MPF_Response_pythia8",
    # "Pt_ave_pythia8",
    "Rel_Response_pythia8",
    "probejet_phi_DATA_pythia8",
    "probejet_phi_MC_pythia8",

    "probejet_chEmEF_DATA_pythia8",
    "probejet_chEmEF_MC_pythia8",
    "probejet_chHadEF_DATA_pythia8",
    "probejet_chHadEF_MC_pythia8",
    "probejet_muonEF_DATA_pythia8",
    "probejet_muonEF_MC_pythia8",
    "probejet_neutEmEF_DATA_pythia8",
    "probejet_neutEmEF_MC_pythia8",
    "probejet_neutHadEF_DATA_pythia8",
    "probejet_neutHadEF_MC_pythia8",
    "probejet_photonEF_DATA_pythia8",
    "probejet_photonEF_MC_pythia8",
]

frames_list = []

for i, eta in enumerate(etas[:-1]):
    frames_list.append(
        "\\begin{frame}{" + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases[:6]):
        if j and not j % 3:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\includegraphics[width=0.3\\textwidth]{" + img_path_base + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"
    frames_list.append(
        "\\begin{frame}{" + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    for j, pic_base in enumerate(pic_bases[6:18]):
        if j and not j % 4:
            frames_list[-1] += "\\newline\n\n"
            frames_list[-1] += "\\vspace{-0.65cm}\n"
        frames_list[-1] += "\t\includegraphics[width=0.24\\textwidth]{" + img_path_base + \
            pic_base + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + ".pdf}\n"

    frames_list[-1] += "\end{frame}\n\n"
    frames_list.append(
        "\\begin{frame}{kFSR MPF " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    frames_list[-1] += "\t\includegraphics[width=0.25\\textwidth]{" + img_path_base_2 + \
        "kFSR_MPF" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    for j, pt in enumerate(pt_str[:-1]):
        if not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\\begin{overpic}[width=0.19\\textwidth]{" + img_path_base_2 + \
            "kFSR_MPF" + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + "_pT_" + pt + \
            "_" + pt_str[j + 1] + ".pdf}\n"
        frames_list[-1] += "\put(15,60){\\tiny Pt: " + \
            pt + " - " + pt_str[j + 1] + "}\n"
        frames_list[-1] += "\t\end{overpic}\n"

    frames_list[-1] += "\end{frame}\n\n"
    frames_list.append(
        "\\begin{frame}{kFSR Pt " + str(eta) + " - " + str(etas[i + 1]) + "}\n")

    frames_list[-1] += "\t\includegraphics[width=0.25\\textwidth]{" + img_path_base_2 + \
        "kFSR_Pt" + "_eta_" + etas_str[i] + \
        "_" + etas_str[i + 1] + ".pdf}\n"
    for j, pt in enumerate(pt_str[:-1]):
        if not j % 5:
            frames_list[-1] += "\\newline\n\n"
        frames_list[-1] += "\t\\begin{overpic}[width=0.19\\textwidth]{" + img_path_base_2 + \
            "kFSR_Pt" + "_eta_" + etas_str[i] + \
            "_" + etas_str[i + 1] + "_pT_" + pt + \
            "_" + pt_str[j + 1] + ".pdf}\n"
        frames_list[-1] += "\put(15,60){\\tiny Pt: " + \
            pt + " - " + pt_str[j + 1] + "}\n"
        frames_list[-1] += "\t\end{overpic}\n"

    frames_list[-1] += "\end{frame}\n\n"

with open("controlplotsBC.tex", 'w') as file_:
    file_.write(document_base)
    for frame in frames_list:
        file_.write(frame)
    file_.write(document_end)

print "\ngenerated controlplotsBC.tex\n"

# process = subprocess.Popen(["pdflatex, controlplots.tex"]  # rm controlplots.[tosnla][^e]*
#                            )
# output, error = process.communicate()
# print output
# print error
