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


FLAGS+= -Wall -Wextra -Werror -pedantic -march=native -std=c++14
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
	$(CC) -o $@ $^ $(DEBUGFLAGS) 

$(BUILDDIR)%.o:  $(SRCDIR)%.$(SRCEXT) $(DEPS) 
	$(CC) -c -o $@ $< $(DEBUGFLAGS) 
else 
$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(RUNFLAGS) 

$(BUILDDIR)%.o:  $(SRCDIR)%.$(SRCEXT) $(DEPS) 
	$(CC) -c -o $@ $< $(RUNFLAGS) 

run: $(EXE)
	./$(EXE) $(ARGS)


endif


clean: 
	rm -f $(OBJS) $(EXE) gmon.out prof *.gcov *gcno
new:
	rm -f $(RESULTSDIR)*

plot:
	$(PLOTDIR)plot.sh


.PHONY: plot new clean
