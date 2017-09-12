file_name=controlplotsBC_newPtBinning
if [ "$#" = "1" ]
   then file_name=controlplots${1}_newPtBinning
fi
py_out=$(./generate_tex.py "$file_name")
pdflatex ${file_name}.tex
rm ${file_name}.[tosnla][^e]*
echo -e "\nthe python output was:"
echo "$py_out"
