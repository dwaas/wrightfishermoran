#simple gnuplot script

reset

set terminal png
set output "WFMFunctions.png"

set title "Wright Fisher and Moran comparison plot"

set grid
set hidden3d

set xlabel "Initial Number"
set ylabel "Timesteps"
set zlabel "Ratio"

set key top


splot "results_WF" title "Wright-Fisher" lt rgb "green" with dots, \
	  "results_M" title "Moran" lt rgb "red" with dots
