
file_name=L2Res_RunDEF_V23_SFJERV2timeDependent
# QCDPtBinned_METCorrectionCorrected
if [ "$#" = "1" ]
   then file_name=controlplots${1}_trgM_31Jan
fi
rm ${file_name}.tex
# py_out=$(./generate_texRunBCDEFL2Res_Sicentral.py "$file_name")
# py_out=$(./generate_texRunBCDEF_closureCheck.py "$file_name")
# py_out=$(./generate_tex_time.py "$file_name")
py_out=$(./generate_texRunDEFL2Res.py "$file_name")
# py_out=$(./generate_texRunFL2Res_rerecoCheck.py "$file_name")
pdflatex ${file_name}.tex
pdflatex ${file_name}.tex #to get slide numbers
rm ${file_name}.[tosnla][^e]*
echo -e "\nthe python output was:"
echo "$py_out"
