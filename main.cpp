#include "DiscreteDifferential.hpp"
#include "Gene.h"
#include "Population.h"

#include <fstream>			//std::ofstream
#include <limits> 			//std::numeric_limits
#include <iomanip>			//std::setprecision
#include <memory> 			//std::unique_ptr()
#include <time.h> 			//time()


//TODO clean code
//TODO documentation
//TODO random
//TODO use gnuplot instead of rootjunk

// FUTURE UPGRADES
//TODO parallelisation
//TODO wrapper class for function that includes domain
//TODO fitting
//TODO argc, argv
//TODO hdr, src folders
//TODO Population polymorphism
//TODO templates in DiscreteDifferential

//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad



int main(int argc,char* argv[])
{
	typedef std::numeric_limits< double > double_limit;
	std::cout.precision(double_limit::digits10);

	// kDeltaNum and kMaxTimesteps should be around the same order of magnitude
	// to make a sensible comparison between WF and M models
	//
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10100, 
				 			kDeltaNum = kInitialNumMax - kInitialNumMin,
				 			kMinTimesteps = 0, kMaxTimesteps = 100,
							kTransient = 40;


	std::cout << "program started" << std::endl;
//initialise populations  
//
	Population wright_fisher(kInitialNumMin, kInitialNumMax,
				 kMaxTimesteps, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);
  
	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimesteps, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );

				selected_gene = rand() % v.size(); // select another random gene
				v.erase( v.begin() + selected_gene ); //gene death
			}
		);


//==========================================================PRINT TO FILE
auto wright_fisherFunction = [&wright_fisher](unsigned n, unsigned t)
			{ 
				return wright_fisher.probability_function(n,t);
			};

auto moranFunction = [&moran](unsigned n, unsigned t)
			{ 
				return moran.probability_function(n,t);
			};


	std::ofstream WF_file("results_WF");
	std::ofstream M_file("results_M");

	if(!WF_file || !M_file)
	{
		std::cerr << "Cannot open all the output files." << std::endl;
		return 1;
	}

	for(unsigned n = kInitialNumMin; n < kInitialNumMax; ++n)
	{	
		for(unsigned t = kMinTimesteps; t < kMaxTimesteps; ++t)
		{
			
			WF_file << n << "\t" << t << "\t" << wright_fisherFunction(n,t) << std::endl;
			M_file  << n << "\t" << t << "\t" << moranFunction(n,t) 		<< std::endl;
		}
	}

	WF_file.close();
	M_file.close();

	std::cout << "data successfully written to files." << std::endl;

//==========================================================FOKKER PLANCK TEST

	
	IsFPESolution(wright_fisherFunction,
			kInitialNumMin, kInitialNumMax, 
			kMinTimesteps, kMaxTimesteps); //TODO implement transient


	std::cout << "program ended" << std::endl;

	return 0;
}
