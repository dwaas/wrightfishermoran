#ifndef GENETIC_DRIFT_INCLUDED
#define GENETIC_DRIFT_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <time.h> //time()

#include <vector>// std::vector
#include <algorithm> // std::count
#include <ostream> //std::ostream


static const unsigned kNumAlleles = 2;
typedef unsigned Allele; // no negative numbers allowed


class Gene
{
 public:
	
	Allele allele(){return allele_; }

	Gene(Allele anAllele) { allele_ = anAllele % kNumAlleles; } // modulus guards against bad numbers
	Gene() { allele_ = rand() % kNumAlleles; } // generate either 0 or 1

 protected:
	
 private:
	Allele allele_;

};

std::ostream & operator << ( std::ostream &os, Gene &obj );




/*
 * =====================================================================================
 *        Class:  Population
 *  Description: wrapper for vector of Genes 
 * =====================================================================================
 */

typedef std::vector < Gene > Population;

void ReplicateGene (Population &pop);
void KillGene (Population &pop);
//tested

//double GeneRatio (Population const &pop);


#endif // GENETIC_DRIFT_INCLUDED
