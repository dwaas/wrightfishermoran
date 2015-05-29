#include "Gene.h"
#include "Population.h"

#include <time.h> //time()
//root
#include "TCanvas.h"


//TODO documentation
//TODO cvim style formatting/ comments
//TODO random
//TODO inline funcs
//TODO check consts
//TODO fitting
//TODO parallelisatio
//TODO indentation
//TODO start program with different parameters
//TODO plot functions
//TODO derivation
//TODO FPE function
//TODO files in different folders
//
//
//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad


int main(int argc,char* argv[])
{
	// kInitialNumMin and kMaxTimestep should be around the same order of magnitude
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10002, 
				 			kMaxTimestep = 10000;

	std::cout << "program started" << std::endl;
/*  	Population wright_fisher(kInitialNumMin,kInitialNumMax,
				 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);
*/
	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );

				selected_gene = rand() % v.size(); // select another random gene
				v.erase( v.begin() + selected_gene ); //gene death
			}
		);
//	Gene a;
//	std::cout << "a = " << a << std::endl;
//	std::cout << "program ended" << std::endl;
	
	return 0;
}


