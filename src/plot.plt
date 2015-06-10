#simple gnuplot script

reset

set terminal x11
set output "results/WFMFunctions.png"

set title "Wright Fisher and Moran comparison plot"

set grid
set hidden3d

set xlabel "Initial Number"
set ylabel "Timesteps"
set zlabel "Ratio"

set key top


splot "results/WF.dat" title "Wright-Fisher" lt rgb "green" with dots, \
	  "results/M.dat" title "Moran" lt rgb "red" with dots
