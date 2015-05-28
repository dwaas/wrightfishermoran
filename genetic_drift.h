/*
 * =====================================================================================
 *
 *       Filename:  genetic_drift.h
 *
 *    Description:  jump to line40 for Gene; last line for Population
 *
 *        Version:  1.0
 *        Created:  05/26/2015 05:35:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef GENETIC_DRIFT_INCLUDED
#define GENETIC_DRIFT_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <time.h> //time()

#include <vector>// std::vector
#include <algorithm> // std::count
#include <functional> // std::function

#include <ostream> //std::ostream



/*
 * =====================================================================================
 *        Class:  Gene
 *  Description:  
 * =====================================================================================
 */
class Gene
{
	public:

		static const unsigned kNumAlleles = 2;
		typedef unsigned Allele; // no negative numbers allowed

	/* ====================  LIFECYCLE     ======================================= */
		Gene () : m_allele(rand() % kNumAlleles) {};    /* constructor      */
		Gene ( const Allele &other )  : m_allele( other % kNumAlleles) {}; // kindof copy constructor
		Gene ( const Gene &other ) : m_allele(other.m_allele) {};   /* copy constructor */
		~Gene ();                            /* destructor       */


		/* ====================  ACCESSORS     ======================================= */

		Allele allele() const{return m_allele; }

		/* ====================  OPERATORS     ======================================= */

		Gene& operator = ( const Gene &other ); /* assignment operator */

	protected:

	private:
		/* ====================  DATA MEMBERS  ======================================= */
	Allele m_allele;

		/* ====================  FRIENDSHIP  ======================================= */

	friend std::ostream & operator << ( std::ostream &os, Gene &obj );
	friend bool operator == (const Gene &a, const Gene &b){ return (a.m_allele == b.m_allele); };
	friend bool operator != (const Gene &a, const Gene &b){ return (a.m_allele != b.m_allele); };
	

}; /* -----  end of class Gene  ----- */




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
		GeneVec gene_vec() const {return m_gene_vec; }
		TwoVarFunc probability_function(){return m_probability_function; }
		/* ====================  MUTATORS      ======================================= */
		//no need to manually change neither gene_vec nor probability_function

		/* ====================  OPERATORS     ======================================= */

		Population& operator = ( const Population &other ); /* assignment operator */


	protected:

	private:
		/* ====================  DATA MEMBERS  ======================================= */
		
		GeneVec m_gene_vec;
		TwoVarFunc m_probability_function;

}; /* -----  end of class Population  ----- */

#endif // GENETIC_DRIFT_INCLUDED
