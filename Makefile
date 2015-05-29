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
# change .c to .whateverYourExtension
# change variables
#



CC=g++
ROOTLIBS= `root-config --libs`
ROOTCFLAGS= `root-config --cflags`
FLAGS+= -Wall -Wextra -pedantic -march=native -pg -std=c++11#-ftree-loop-im -fprofile-arcs -ftest-coverage #-funroll-loops 
OBJS=main.o Gene.o Population.o
DEPS= Gene.h Population.h
DEBUGFLAGS= -O0 -g $(FLAGS)
RUNFLAGS= -O3 $(FLAGS)
debug=0

EXE= WFM
ARGS= .

ifneq ($(debug), 0)
debug: clean new $(EXE)
	gdb --args ./$(EXE) $(ARGS)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(DEBUGFLAGS) $(ROOTLIBS)

%.o:  %.cpp $(DEPS) 
	$(CC) -c -o $@ $< $(DEBUGFLAGS) $(ROOTCFLAGS)
else 
$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(RUNFLAGS) $(ROOTLIBS)

%.o:  %.cpp $(DEPS) 
	$(CC) -c -o $@ $< $(RUNFLAGS) $(ROOTCFLAGS)
endif

#all:
#	$(CC) $(FLAGS) %.cpp -o $(EXE)

clean: 
	rm -f *.o $(EXE) gmon.out prof *.gcov *gcno
new:
	rm -f *.S output.dat *.pos

#PROFILING and DEBUGGING
prof:
	gprof $(EXE) gmon.out > prof


#FLAGS=  -O3 -ipo -static  -c 
#MAINFLAG=  -O3 -ipo -static

#FLAGS= -openmp -parallel -O3 -ipo -static -c 
#MAINFLAG= -openmp -parallel -O3 -ipo -static

#FLAGS= -openmp -parallel -fast  -c
#MAINFLAG= -openmp -parallel -fast 



