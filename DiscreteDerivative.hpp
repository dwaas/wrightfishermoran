/*
 * =====================================================================================
 *
 *       Filename:  DiscreteDerivative.hpp
 *
 *    Description:  
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

#ifndef  DISCRETEDERIVATIVE_INC
#define  DISCRETEDERIVATIVE_INC



#include <functional>			//std::function
#include <iostream> 			//std::cout

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

}; /* -----  end of template class DiscreteDerivative  ----- */


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




#endif   /* ----- #ifndef DISCRETEDERIVATIVE_INC  ----- */

