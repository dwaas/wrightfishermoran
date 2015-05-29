/*
 * =====================================================================================
 *
 *       Filename:  Population.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2015 02:35:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Population.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  Population
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
// temporarily only WF
Population::Population (const unsigned kInitialNumMin, const unsigned kInitialNumMax, 
						const unsigned kMaxTimestep,
						std::function<void (GeneVec&)> PopEvolution)
: _gene_vec(kInitialNumMin)
{
/* 	auto PrintVector = [](std::vector<double> & v)
	{
		if(v.size() == 0)
		{ 
			std::cout << " empty vector" << std::endl;
			return;
		}
		for(auto & itr : v)
		{
			std::cout<< itr << std::endl;
		}
	};
*/

	for(unsigned num = kInitialNumMin; num < kInitialNumMax; ++num)
	{
		std::vector< double > t_row; // row with a given a fixed num
//		std::cout << "t_row is:" << std::endl;
//		PrintVector(t_row);

		for (unsigned timestep = 0; timestep < kMaxTimestep; ++timestep)
		{
			 PopEvolution(_gene_vec);
			 double ratio = std::count(_gene_vec.begin(), _gene_vec.end(), 0) / (double) _gene_vec.size(); // 0 is the value of one allele
			 std::cout  << " num = " << num << " t = " << timestep << " Gene ratio is: " << ratio << std::endl;

			 t_row.push_back(ratio);

		} 

		_probability_function.push_back(t_row);
	}
	std::cout << _gene_vec.size() << std::endl;
 		

	std::cout << "population was succesfully initialised." << std::endl;
	/*
	for(auto& row: _probability_function)
	{
		for(auto& column: row)
		{
			std::cout << column << "\t" ;
		}
		std::cout << std::endl;
	}

	*/
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
	_gene_vec = other._gene_vec;
	_probability_function = other._probability_function;
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
		_gene_vec = other._gene_vec;
		_probability_function = other._probability_function;
	}
	return *this;
}  /* -----  end of method Population::operator =  (assignment operator)  ----- */





