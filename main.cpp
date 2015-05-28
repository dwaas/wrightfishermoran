#include <time.h> //time()
#include <random>


#include "genetic_drift.h"


//TODO documentation
//TODO cvim style formatting/ comments
//TODO const in << operators
//TODO random
//TODO encapsulate print vector functions
//TODO inline funcs
//TODO check consts
//TODO names
//TODO fitting
//TODO parallelisatio
//TODO indentation
//TODO start program with different parameters
//TODO better OOP naming for PopEvolution
//
//
//
//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad


int main(int argc,char* argv[])
{
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10002, kMaxTimestep = 10000;// kInitialNumMin and kMaxTimestep should be around the same order of magnitude

	std::cout << "program started" << std::endl;
	Population wright_fisher(kInitialNumMin,kInitialNumMax,
				 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);

	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
				v.erase( v.begin() + selected_gene ); //gene death
			}
		);

	std::cout << "program ended" << std::endl;
	return 0;
}


