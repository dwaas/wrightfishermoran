# wrightfishermoran
test convergence of the two population dynamics' models.

KNOWN BUGS:

1) ratio functions seem to not converge to solutions

2) gnuplot doesn't -persist; ./run.sh pipes output to eog

USAGE:

select initial conditions in src/main.cpp

make run

make plot #plots using gnuplot

make clean # clears compilation files

make new # clears previous results
