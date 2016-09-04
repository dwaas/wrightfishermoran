#ifndef  Population_INC
#define  Population_INC

#include "Gene.h"

#include <time.h> 	// time()

#include <algorithm>	// std::count
#include <functional> 	// std::function
#include <iostream> 	// std::cout
#include <vector> 	// std::vector





typedef std::vector < Gene > GeneVec;

//  Description:  Class that implements population dynamics through a given set of
//instructions that are iterated for different timesteps and initial nums

class Population
{
public:
        typedef	std::vector < std::vector< double > > TwoVarFunc;

        Population (const unsigned kInitialNumMin, const unsigned kInitialNumMax,
                    const unsigned kMaxTimesteps,
                    std::function<void (GeneVec &) > PopEvolution);

        Population ( const Population &other );
        ~Population ();


        GeneVec gene_vec() const {return _gene_vec; }
        double probability_function (unsigned num, unsigned timestep) const;
        unsigned kInitialNumMin () const {return _kInitialNumMin;}
        unsigned kInitialNumMax () const {return _kInitialNumMax;}
        unsigned kMaxTimesteps  () const {return _kMaxTimesteps;}

        Population& operator = ( const Population &other );

private:
        GeneVec _gene_vec;
        TwoVarFunc _probability_function;
        unsigned _kInitialNumMin;
        unsigned _kInitialNumMax;
        unsigned _kMaxTimesteps;

};

#endif
