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
//TODO parallelisation


//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad


int main(int argc,char* argv[])
{
	static const unsigned kMaxTimestep = 10000, kInitialNum = 100, kMaxNum = 10000;

	for(unsigned num = kInitialNum; num < kMaxNum; ++num)
	{
		Population wright_fisher(num, kMaxTimestep, [](GeneVec& v)
				{		
					unsigned selected_gene = rand() % v.size();
					v.push_back( v[selected_gene] );
				}
			);

		Population moran(num, kMaxTimestep, [](GeneVec& v)
				{		
					unsigned selected_gene = rand() % v.size();
					v.push_back( v[selected_gene] );
					v.erase( v.begin() + selected_gene ); //gene death
				}
			);
	}
		
/* 
//WF time evolution	
	
		std::cout << "The ratio of 0 in wright_fisher is: " << GeneRatio(wright_fisher) << std::endl;
//Moran time evolution
	for (unsigned timestep = 0; timestep < kMaxTimestep; ++timestep)
	{
		ReplicateGene(moran);
		KillGene(moran);
		GeneRatio(moran); // our datapoint
	}	

		std::cout << "The ratio of 0 in moran is: " << GeneRatio(moran) << std::endl;
*/
	return 0;
}


