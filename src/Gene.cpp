/*
 * =====================================================================================
 *
 *       Filename:  Gene.cpp
 *
 *    Description: 	Monoallelic Gene locus 
 *
 *        Version:  1.0
 *        Created:  05/29/2015 02:30:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Devin Waas (), dsc.waas@gmail.com
 * =====================================================================================
 */

#include "../include/Gene.h"

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
operator << ( std::ostream &os, const Gene &obj ) 
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
		_allele = other._allele;
	}
	return *this;
}  /* -----  end of method Gene::operator =  (assignment operator)  ----- */

