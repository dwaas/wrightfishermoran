/*
 * =====================================================================================
 *       Filename:  Population.h
 *
 *    Description: 	Class that implements population dynamics through a given set of
 *    				instructions that are iterated.
 *
 *        Version:  1.0
 *        Created:  05/29/2015 02:21:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 * =====================================================================================
 */

#ifndef  Population_INC
#define  Population_INC

#include "Gene.h"

#include <time.h> 		// time()

#include <algorithm>	// std::count
#include <functional> 	// std::function
#include <iostream> 	// std::cout
#include <vector> 		// std::vector





typedef std::vector < Gene > GeneVec;

/*
 * =====================================================================================
 *        Class:  Population
 *  Description:  Class that implements population dynamics through a given set of
 *    				instructions that are iterated for different timesteps and initial nums
 * =====================================================================================
 */
class Population
{
	public:
	
		typedef	std::vector < std::vector< double > > TwoVarFunc;

		/* ====================  LIFECYCLE     ======================================= */
		Population (const unsigned kInitialNumMin, const unsigned kInitialNumMax, 
					const unsigned kMaxTimesteps,  
					std::function<void (GeneVec &) > PopEvolution);                             /* constructor      */
		
		Population ( const Population &other );   /* copy constructor */
		~Population ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		GeneVec gene_vec() const {return _gene_vec; }
		double probability_function (unsigned num, unsigned timestep) const; 
		unsigned kInitialNumMin () const {return _kInitialNumMin;}
		unsigned kInitialNumMax () const {return _kInitialNumMax;}
		unsigned kMaxTimesteps  () const {return _kMaxTimesteps;}

		/* ====================  OPERATORS     ======================================= */

		Population& operator = ( const Population &other ); /* assignment operator */


	protected:

	private:
		/* ====================  DATA MEMBERS  ======================================= */
		
		GeneVec _gene_vec;
		TwoVarFunc _probability_function;
		unsigned _kInitialNumMin;
		unsigned _kInitialNumMax;
		unsigned _kMaxTimesteps; 

}; /* -----  end of class Population  ----- */


#endif   /* ----- #ifndef Population_INC  ----- */
