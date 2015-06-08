#Makefile 
# 5 - 04 - 2015
# USAGE:
#
#
# MAKE CLEAN
# MAKE NEW
# MAKE PROF
# MAKE DEBUG debug=1
# MAKE
# 
#
#TODO  use this $(addprefix $(SRCDIR), SRCEXT) instead of $(SRCDIR).%$(SRCEXT)

CC=g++
SRCEXT= cpp

SRCDIR= src/
BUILDDIR= build/
EXECDIR= bin/
INCLUDEDIR= include/
RESULTSDIR= results/
PLOTDIR= plot/

ROOTLIBS= `root-config --libs`
ROOTCFLAGS= `root-config --cflags`

FLAGS+= -Wall -Wextra -pedantic -march=native -std=c++11# -pg -ftree-loop-im -fprofile-arcs -ftest-coverage #-funroll-loops 

DEBUGFLAGS= -O0 -g $(FLAGS)
RUNFLAGS= -O3 $(FLAGS)
debug=0



OBJS = $(addprefix $(BUILDDIR), main.o Gene.o Population.o)
DEPS = $(addprefix $(INCLUDEDIR), Gene.h Population.h DiscreteDifferential.hpp )
EXE = $(addprefix $(EXECDIR), WFM )
ARGS= .

###################################################makefile begin

ifneq ($(debug), 0)
debug: clean new $(EXE)
	gdb --args ./$(EXE) $(ARGS)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(DEBUGFLAGS) $(ROOTLIBS)

$(BUILDDIR)%.o:  $(SRCDIR)%.$(SRCEXT) $(DEPS) 
	$(CC) -c -o $@ $< $(DEBUGFLAGS) $(ROOTCFLAGS)
else 
$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(RUNFLAGS) $(ROOTLIBS)

$(BUILDDIR)%.o:  $(SRCDIR)%.$(SRCEXT) $(DEPS) 
	$(CC) -c -o $@ $< $(RUNFLAGS) $(ROOTCFLAGS)

run: $(EXE)
	./$(EXE) $(ARGS)


endif

#all:
#	$(CC) $(FLAGS) $(SRCDIR)%.$(SRCEXT) -o $(EXE)

clean: 
	rm -f $(OBJS) $(EXE) gmon.out prof *.gcov *gcno
new:
	rm -f $(RESULTSDIR)*

plot:
	$(PLOTDIR)plot.sh


.PHONY: plot new clean

#PROFILING and DEBUGGING
#prof:
#	gprof $(EXE) gmon.out > prof


#FLAGS=  -O3 -ipo -static  -c 
#MAINFLAG=  -O3 -ipo -static

#FLAGS= -openmp -parallel -O3 -ipo -static -c 
#MAINFLAG= -openmp -parallel -O3 -ipo -static

#FLAGS= -openmp -parallel -fast  -c
#MAINFLAG= -openmp -parallel -fast 



