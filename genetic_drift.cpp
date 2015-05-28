#include "genetic_drift.h"




/*
 *--------------------------------------------------------------------------------------
 *       Class:  Gene
 *      Method:  ~Gene
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */

Gene::~Gene ()
{
}  /* -----  end of method Gene::~Gene  (destructor)  ----- */




/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  operator <<
 * Description:  output stream operator
 *--------------------------------------------------------------------------------------
 */
	std::ostream& 
operator << ( std::ostream &os, Gene &obj ) 
{
	os << obj.allele() << std::endl;
	return os;
}		/* -----  end of function operator <<  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Gene
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	Gene&
Gene::operator = ( const Gene &other )
{
	if ( this != &other ) 
	{
		m_allele = other.m_allele;
	}
	return *this;
}  /* -----  end of method Gene::operator =  (assignment operator)  ----- */






/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  Population
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
// temporarily only WF
Population::Population ( const unsigned kInitialNum, const unsigned kMaxTimestep,
		std::function<void (GeneVec&)> PopEvolution)
: m_gene_vec(kInitialNum)
{
/*  	std::for_each(m_gene_vec.begin(), m_gene_vec.end(), [](Gene val)
			{
				std::cout << val << std::endl;
			}
			);
*/

	for (unsigned timestep = 0; timestep < kMaxTimestep; ++timestep)
	{
		 PopEvolution(m_gene_vec);
		 double ratio = std::count(m_gene_vec.begin(), m_gene_vec.end(), 0) / (double) m_gene_vec.size(); // 0 is the value of one allele
		 std::cout  << " num = " << kInitialNum << " t = " << timestep << " Gene ratio is: " << ratio << std::endl;

	} //TODO better OOP naming for PopEvolution

 	 std::cout << m_gene_vec.size() << std::endl;
 		

	std::cout << "population was succesfully initialised." << std::endl;
}  /* -----  end of method Population::Population  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  Population
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Population::Population ( const Population &other )
{
	m_gene_vec = other.m_gene_vec;
	m_probability_function = other.m_probability_function;
//check whether general function HAS assignment operator


}  /* -----  end of method Population::Population  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  ~Population
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Population::~Population ()
{
}  /* -----  end of method Population::~Population  (destructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	Population&
Population::operator = ( const Population &other )
{
	if ( this != &other ) 
	{
		m_gene_vec = other.m_gene_vec;
		m_probability_function = other.m_probability_function;
	}
	return *this;
}  /* -----  end of method Population::operator =  (assignment operator)  ----- */





