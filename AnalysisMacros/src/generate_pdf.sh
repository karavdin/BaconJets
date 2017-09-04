#!/bin/bash
py_out=$(./generate_tex.py)
pdflatex controlplotsBC.tex
rm controlplotsBC.[tosnla][^e]*
printf "\nOutput of the starting python script was:\n"
echo $py_out
