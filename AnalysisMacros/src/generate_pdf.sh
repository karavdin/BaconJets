file_name=controlplotsBC_trgM_21Nov
if [ "$#" = "1" ]
   then file_name=controlplots${1}_trgM_21Nov
fi
rm ${file_name}.tex
py_out=$(./generate_tex_trgMatched.py "$file_name")
pdflatex ${file_name}.tex
rm ${file_name}.[tosnla][^e]*
echo -e "\nthe python output was:"
echo "$py_out"
