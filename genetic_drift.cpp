#include "genetic_drift.h"

	std::ostream &
operator << ( std::ostream &os, Gene &obj ) 
{
	os << obj.allele() << std::endl;
	return os;
}		/* -----  end of function operator <<  ----- */



/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  Population
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
// temporarily only WF
Population::Population (const unsigned kMaxTimestep, const unsigned kInitialNum)
{
	for (unsigned timestep = 0; timestep < kMaxTimestep; ++timestep)
	{
		unsigned selected_gene = rand() % pop.size(); 
//implement with lambda		
		m_gene_vec.push_back( m_gene_vec[selected_gene] ); //gene reproduction
		m_gene_vec.erase( m_gene_vec.begin() + selected_gene ); //gene death


	}
//make more readable
	double ratio = std::count(m_gene_vec.begin(), m_gene_vec.end(), 0) / (double) m_gene_vec.size();

	std::cout << "WF population was succesfully initialised." << std::endl;
	std::cout << "Gene ratio is:" << ratio << std::endl;

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





