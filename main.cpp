#include <iostream>

#include <stdlib.h> //srand()
#include <time.h> //time()
#include <random>


#include "genetic_drift.h"

//TODO documentation
// build functions M(n, t) and WF(n, t)
//const in << operators
//random
//encapsulate print vector functions


int main(int argc,char* argv[])
{
	static const unsigned kMaxTimestep = 100000;

/* 	srand((unsigned)time(0));
	Gene a;
	std::cout << "Gene a = " << a << std::endl;

	Gene b(2);
	std::cout << "Gene b = " << b << std::endl;


	Population test_pop(10);

	std::cout << "The size of test_pop is: " << test_pop.size() << std::endl;

	std::cout << "The contents of test_pop are: ";
	for (auto it = test_pop.begin(); it != test_pop.end(); it++)
		std::cout << *it  << ' ';

	std::cout << '\n';

	std::cout << "The ratio of 0 in test_pop is: " << GeneRatio(test_pop) << std::endl;

	KillGene(test_pop);
	// 	test_pop.push_back(b);

*/

	Population wright_fisher(100), moran(100);
//WF time evolution	
	for (unsigned timestep = 0; timestep < kMaxTimestep; ++timestep)
	{
		ReplicateGene(wright_fisher);
		GeneRatio(wright_fisher); // our datapoint
	}
	
		std::cout << "The ratio of 0 in wright_fisher is: " << GeneRatio(wright_fisher) << std::endl;
//Moran time evolution
	for (unsigned timestep = 0; timestep < kMaxTimestep; ++timestep)
	{
		ReplicateGene(moran);
		KillGene(moran);
		GeneRatio(moran); // our datapoint
	}	

		std::cout << "The ratio of 0 in moran is: " << GeneRatio(moran) << std::endl;

	return 0;
}


