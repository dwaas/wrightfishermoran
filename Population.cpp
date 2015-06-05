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
Population::Population (const unsigned kInitialNumMin, const unsigned kInitialNumMax, 
						const unsigned kMaxTimesteps,
						std::function<void (GeneVec&)> PopEvolution) :

_gene_vec(kInitialNumMin),
_probability_function( (kInitialNumMax - kInitialNumMin), std::vector<double> (kMaxTimesteps) ), 
_kInitialNumMin(kInitialNumMin), _kInitialNumMax(kInitialNumMax), 
_kMaxTimesteps(kMaxTimesteps)

{
//FIXME: processes need absolute n number, matrices need relative ones 
	for(unsigned num = _kInitialNumMin; num < _kInitialNumMax; ++num)
	{
		for (unsigned timestep = 0; timestep < _kMaxTimesteps; ++timestep)
		{
			 PopEvolution(_gene_vec);
			
			 double ratio = std::count(_gene_vec.begin(), _gene_vec.end(), 0) / (double) _gene_vec.size(); // 0 is the value of one allele			 
			 _probability_function[num - kInitialNumMin][timestep] = ratio;

//			 std::cout  << " num = " << num << " t = " << timestep << " Gene ratio is: " << ratio << std::endl;
//			 std::cout  << " num = " << num << " t = " << timestep << " F probabil is: " << probability_function((num - kInitialNumMin), timestep) << std::endl;
		} 
	}
	std::cout << _gene_vec.size() << std::endl; 
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

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  probability_function()
 * Description:  _probability_function getter
 *--------------------------------------------------------------------------------------
 */

	double
Population::probability_function(unsigned num, unsigned timestep) const
{
	if(num < _kInitialNumMin || num > _kInitialNumMax)
	{	
		std::cout << "num = " << num << " is not included in the domain;"; 
		std::cout << " select a valid value." << std::endl;	
		
		return 0;
	}
	if(timestep > _kMaxTimesteps)
	{	
		std::cout << "timestep = " << timestep << " is not included in the domain;"; 
		std::cout << " select a valid value." << std::endl;	
		
		return 0;
	}
	return _probability_function[(num - _kInitialNumMin)][timestep ]; 
}

/* DEBUGGING SNIPPETS
 



//RANGE PRINT MATRIX 	
	for(auto& row: _probability_function)
	{
		for(auto& column: row)
		{
			std::cout << column << "\t" ;
		}
		std::cout << std::endl;
	}

//LAMBDA PRINTVECTOR
//
//
//
 	auto PrintVector = [](std::vector<double> & v)
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



