file_name=controlplots_DEF_wHF_14Mr
if [ "$#" = "1" ]
   then file_name=controlplots${1}_trgM_31Jan
fi
rm ${file_name}.tex
py_out=$(./generate_texRunDEFL2Res.py "$file_name")
pdflatex ${file_name}.tex
rm ${file_name}.[tosnla][^e]*
echo -e "\nthe python output was:"
echo "$py_out"
