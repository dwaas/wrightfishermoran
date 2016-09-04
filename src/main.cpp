/*
The following simulation wants to show that the relative ratio in a
monoallele function of n and t converges to a solution of the
Fokker Planck equation in both the Wright-Fisher and
Moran Population Dynamics' models.

The program works as following:
1) constructs populations according to the two models,
doing so the relative ratio function is tabulated

2) check whether the tabulated (discrete) functions are
solutions of FPE

3) to see whether they are similar, a gnuplot script
is provided in the main directory
 */

#include <stdlib.h>


#include "../include/DiscreteDifferential.hpp"
#include "../include/Gene.h"
#include "../include/Population.h"

#include <fstream>			//std::ofstream
#include <iomanip>			//std::setprecision
#include <limits> 			//std::numeric_limits
#include <memory> 			//std::unique_ptr()
#include <time.h> 			//time()



// FUTURE UPGRADES
//TODO list instead of vector
//TODO random
//TODO parallelisation
//TODO wrapper class for function that includes domain
//TODO fitting
//TODO argc, argv
//TODO Population polymorphism
//TODO templates in DiscreteDifferential


int main()
{
//definitions useful for numeric handling
	typedef std::numeric_limits< double > double_limit;
	std::cout.precision(double_limit::digits10);

//INITIAL CONDITIONS
	// kInitialNumMax-kInitialNumMin and kMaxTimesteps should be
        // around the same order of magnitude
	// to make a sensible comparison between WF and M models
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10100,
                                kMinTimesteps = 0, kMaxTimesteps = 100,
                                kTransient = 40;

	srand(time(0));

	std::cout << "program started" << std::endl;
//initialise populations

	Population wright_fisher(kInitialNumMin, kInitialNumMax,
				 kMaxTimesteps, [](GeneVec& v)
			{
                                //random gene multiplies
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);

	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimesteps, [](GeneVec& v)
			{
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );

                                // select another random gene
				selected_gene = rand() % v.size();
                                //gene death
				v.erase( v.begin() + selected_gene );
			}
		);


//======================================================PRINT TO FILE
        auto wright_fisherFunction = [&wright_fisher](unsigned n, unsigned t)
                {
                        return wright_fisher.probability_function(n,t);
                };

        auto moranFunction = [&moran](unsigned n, unsigned t)
                {
                        return moran.probability_function(n,t);
                };


	std::ofstream WF_file("results/WF.dat");
	std::ofstream M_file("results/M.dat");

	if(!WF_file || !M_file)
	{
		std::cerr << "Cannot open all the output files." << std::endl;
		return 1;
	}

	for(unsigned n = kInitialNumMin; n < kInitialNumMax; ++n)
	{
		for(unsigned t = kMinTimesteps; t < kMaxTimesteps; ++t)
		{

			WF_file << n << "\t" << t << "\t"
                                << wright_fisherFunction(n,t) << std::endl;

			M_file  << n << "\t" << t << "\t"
                                << moranFunction(n,t) << std::endl;
		}
	}

	WF_file.close();
	M_file.close();

	std::cout << "data successfully written to files." << std::endl;

//=================================================FOKKER PLANCK TEST

//we assume there will be a transient period
	IsFPESolution(wright_fisherFunction,
			kInitialNumMin, kInitialNumMax,
			(kMinTimesteps + kTransient), kMaxTimesteps);

	std::cout << "program ended" << std::endl;

	return 0;
}
