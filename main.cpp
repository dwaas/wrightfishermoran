#include <iostream>
#include <stdlib.h> //srand()
#include <time.h> //time()

#include "genetic_drift.h"

//TODO documentation
// build functions M(n, t) and WF(n, t)
//const in << operators
//


int main(int argc,char* argv[])
{
	srand((unsigned)time(0));
	Gene a;
	std::cout << "Gene a = " << a << std::endl;
	
	Gene b(2);
	std::cout << "Gene b = " << b << std::endl;


	
//passed the tests

	Population test_pop(10);
 
  std::cout << "The contents of test_pop are: ";
    for (std::vector< Gene >::iterator it = test_pop.begin(); it != test_pop.end(); it++)
		    std::cout << *it  << ' ';

	  std::cout << '\n';

	return 0;
}
