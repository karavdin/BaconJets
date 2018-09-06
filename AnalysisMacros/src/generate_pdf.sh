file_name=RunBCDEF_L2Res_V23_noClosure_effectOfL1BXcleaning
# QCDPtBinned_METCorrectionCorrected
if [ "$#" = "1" ]
   then file_name=controlplots${1}_trgM_31Jan
fi
rm ${file_name}.tex
# py_out=$(./generate_texRunBCDEFL2Res_Sicentral.py "$file_name")
py_out=$(./generate_texRunC_L2Res.py "$file_name")
# py_out=$(./generate_texRunDEFL2Res.py "$file_name")
pdflatex ${file_name}.tex
pdflatex ${file_name}.tex #to get slide numbers
rm ${file_name}.[tosnla][^e]*
echo -e "\nthe python output was:"
echo "$py_out"
