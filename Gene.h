/*
 * =====================================================================================
 *
 *       Filename:  Gene.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2015 02:28:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  Gene_INC
#define  Gene_INC

#include <time.h> //time(), rand()

#include <iostream> //std::cout
#include <ostream> //std::ostream
#include <vector>// std::vector


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
		Gene () : _allele(rand() % kNumAlleles) {};    /* constructor      */
		Gene ( const Allele &other )  : _allele( other % kNumAlleles) {}; // kindof copy constructor
		Gene ( const Gene &other ) : _allele(other._allele) {};   /* copy constructor */
		~Gene ();                            /* destructor       */


		/* ====================  ACCESSORS     ======================================= */

		Allele allele() const{return _allele; }

		/* ====================  OPERATORS     ======================================= */

		Gene& operator = ( const Gene &other ); /* assignment operator */

	protected:

	private:
		/* ====================  DATA MEMBERS  ======================================= */
	Allele _allele;

		/* ====================  FRIENDSHIP  ======================================= */

	friend std::ostream & operator << ( std::ostream &os, const Gene &obj );
	friend bool operator == (const Gene &a, const Gene &b){ return (a._allele == b._allele); };
	friend bool operator != (const Gene &a, const Gene &b){ return (a._allele != b._allele); };
	

}; /* -----  end of class Gene  ----- */





#endif   /* ----- #ifndef Gene_INC  ----- */
