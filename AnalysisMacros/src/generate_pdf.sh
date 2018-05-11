file_name=RunFL2_correction_14May
if [ "$#" = "1" ]
   then file_name=controlplots${1}_trgM_31Jan
fi
rm ${file_name}.tex
py_out=$(./generate_tex_4JERCmeet.py "$file_name")
pdflatex ${file_name}.tex
pdflatex ${file_name}.tex #to get slide numbers
rm ${file_name}.[tosnla][^e]*
echo -e "\nthe python output was:"
echo "$py_out"
