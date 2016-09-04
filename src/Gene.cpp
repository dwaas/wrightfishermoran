#include "../include/Gene.h"

Gene::~Gene ()
{
}  

std::ostream& 
operator << ( std::ostream &os, const Gene &obj ) 
{
	os << obj.allele() << std::endl;
	return os;
}

Gene&
Gene::operator = ( const Gene &other )
{
	if ( this != &other ) 
	{
		_allele = other._allele;
	}
	return *this;
}  
