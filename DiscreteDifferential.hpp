/*
 * =====================================================================================
 *
 *       Filename:  DiscreteDifferential.hpp
 *
 *    Description:  contains DiscreteDerivative ad IsFPESolution()
 *
 *        Version:  1.0
 *        Created:  06/03/2015 12:21:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DISCRETEDIFFERENTIAL_INC
#define  DISCRETEDIFFERENTIAL_INC


#include <cmath>				//std::abs, std::max()
#include <functional>			//std::function
#include <iostream> 			//std::cout
#include <limits> 				//std::numeric_limits<T>::epsilon

/* 
 * =====================================================================================
 *        Class:  DiscreteDerivative
 *  Description:  
 * =====================================================================================
 */

class DiscreteDerivative
{
	public:
		typedef std::function< double (int arg) > functor_type;

		// ====================  LIFECYCLE     =======================================
		DiscreteDerivative (functor_type f, int arg_min, int arg_max) : 
		_f(f), _arg_min(arg_min), _arg_max(arg_max) {};               /* constructor      */
	//FIXME Assumes that arg_min<arg_max	
		DiscreteDerivative ( const DiscreteDerivative &other ) :
		_f(other._f), _arg_min(other._arg_min), _arg_max(other._arg_max) {}; /* copy constructor */
		
		~DiscreteDerivative () {};                          /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		functor_type f() const { return _f;}
		int arg_min() const {return _arg_min;}
		int arg_max() const {return _arg_max;}

		/* ====================  MUTATORS      ======================================= */

		/* ====================  OPERATORS     ======================================= */
		double operator ()(int arg);

	protected:
	
	private:
		/* ====================  DATA MEMBERS  ======================================= */
		functor_type _f;
		int	_arg_min;
		int	_arg_max;

}; /* -----  end of  class DiscreteDerivative  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Population
 *      Method:  operator () ()
 * Description:  derivation operator
 *--------------------------------------------------------------------------------------
 */
double DiscreteDerivative::operator ()(int arg)
{
	if(arg < _arg_min || arg > _arg_max) // out of domain case
	{	
		std::cout << arg << " is not included in the domain;"; 
		std::cout << " select a valid value." << std::endl;	
		
		return 0;
	}
	
	if(arg == _arg_min && arg == _arg_max) // degenerate case
	{	
		std::cout << " the function has only one data point;";
		std::cout << " discrete derivative does not make sense." << std::endl;	
		
		return 0;
	}
	
	if(arg != _arg_min && arg != _arg_max)// centered derivative
	{
		return (double) ((_f(arg + 1) - _f( arg - 1 )) / 2.0) ;//assumes that discrete steps = 1
	}
	
	if(arg == _arg_min) // forward derivative
	{
		return (double) (_f(arg + 1) - _f( arg )) ;
	}
	
	if(arg == _arg_max) // backward derivative
	{
		return (double) (_f(arg) - _f( arg - 1 )) ;
	}


	return 0;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  IsFPESolution
 *  Description:  
 * =====================================================================================
 */
bool
IsFPESolution(std::function<double (int x, unsigned t)> f, 
		int x_min, int x_max,
		unsigned t_min, unsigned t_max)
{
	for(int x = x_min; x < x_max; ++x)// timestep = x_max segfaults //FIXME
	{
		for(unsigned timestep = t_min ; timestep < t_max; ++timestep)
		{
			auto f_t = [&f, x] (unsigned timestep) { return f(x, timestep); }; //bind one parameter
			auto f_x = [&f, timestep] (unsigned x) { return f(x, timestep); };
			
			DiscreteDerivative df_dt(f_t, t_min, t_max);
			
			DiscreteDerivative df_dx(f_x, x_min, x_max);
			DiscreteDerivative d2f_dx2([&df_dx] (unsigned x) { return df_dx(x); }, 
					x_min, x_max);// lambda as delegate

		
			auto IsNumericallyEqual = [](double a, double b)
			{
				static const double eps = std::numeric_limits<double>::epsilon();
				static const unsigned eps_multiplier = 1024;
				
				std::cout << "a = " << a << std::endl;
				std::cout << "b = " << b << std::endl;

				std::cout << "abs(a - b) = " << std::abs(a - b) << std::endl;
				std::cout << "max(a,b) = " << eps_multiplier*eps*std::max(a, b) << std::endl;
				
				return std::abs(a - b) < eps_multiplier * eps * std::max(a,b);
			};

			if( !( IsNumericallyEqual(df_dt(timestep), 0.5* d2f_dx2(x) )) )
			{
				std::cout << " Not a solution for FPE! " << std::endl;
				std::cout << " x = " << x << " timestep = " << timestep << std::endl;
			
				return false;
			}
			else
			{
				std::cout << " Congratulations !! " << std::endl;
				std::cout << " You found the FPE solution " << std::endl;

				return true;
			}
		}
	}

	return 0;
}

#endif   /* ----- #ifndef DISCRETEDIFFERENTIAL_INC  ----- */

