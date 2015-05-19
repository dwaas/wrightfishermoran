#include <iostream>

#include <stdlib.h> //srand()
#include <time.h> //time()
#include <random>


#include "genetic_drift.h"

//TODO documentation
// build functions M(n, t) and WF(n, t)
//const in << operators
//random
//


int main(int argc,char* argv[])
{
	srand((unsigned)time(0));
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

	KillGene(test_pop);
	// 	test_pop.push_back(b);

	std::cout << "The size of test_pop is: " << test_pop.size() << std::endl;

	std::cout << "The contents of test_pop are: ";
	for (auto it = test_pop.begin(); it != test_pop.end(); it++)
		std::cout << *it  << ' ';

	std::cout << '\n';


	return 0;
}
