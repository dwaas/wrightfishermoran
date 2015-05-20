#include "genetic_drift.h"


	std::ostream &
operator << ( std::ostream &os, Gene &obj ) 
{
	os << obj.allele() << std::endl;
	return os;
}		/* -----  end of function operator <<  ----- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ReplicateGene
 *  Description:  randomly pick one population element and reproduce it
 * =====================================================================================
 */

	void
ReplicateGene (Population &pop)
{
	unsigned selected_gene = rand() % pop.size();
	pop.push_back( pop[selected_gene] );

	return;
}		/* -----  end of function ReplicateGene  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  KillGene
 *  Description: randomly pick one population element and kill it
 * =====================================================================================
 */
	void
KillGene ( Population &pop)
{
	unsigned selected_gene = rand() % pop.size();
	pop.erase( pop.begin() + selected_gene );

	return;
}		/* -----  end of function KillGene  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GeneRatio
 *  Description: returns the ratio of alleles = 0 over the population
 * =====================================================================================
 */
	double
GeneRatio (Population const &pop)
{
	double ratio = std::count(pop.begin(), pop.end(), 0) / (double) pop.size();
	return ratio;
}		/* -----  end of function GeneRatio  ----- */



