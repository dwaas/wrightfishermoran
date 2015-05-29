/*
 * =====================================================================================
 *
 *       Filename:  Population.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2015 02:21:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 *   Organization:  
 *
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
 *  Description:  
 * =====================================================================================
 */
class Population
{
	public:
	
		typedef	std::vector < std::vector< double > > TwoVarFunc;

		/* ====================  LIFECYCLE     ======================================= */
		Population (const unsigned kInitialNumMin, const unsigned kInitialNumMax, 
					const unsigned kMaxTimesteps,  
					std::function<void (GeneVec &) >PopEvolution);                             /* constructor      */
		
		Population ( const Population &other );   /* copy constructor */
		~Population ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		GeneVec gene_vec() const {return _gene_vec; }
		TwoVarFunc probability_function(){return _probability_function; }
		/* ====================  MUTATORS      ======================================= */
		//no need to manually change neither gene_vec nor probability_function

		/* ====================  OPERATORS     ======================================= */

		Population& operator = ( const Population &other ); /* assignment operator */


	protected:

	private:
		/* ====================  DATA MEMBERS  ======================================= */
		
		GeneVec _gene_vec;
		TwoVarFunc _probability_function;

}; /* -----  end of class Population  ----- */



#endif   /* ----- #ifndef Population_INC  ----- */
