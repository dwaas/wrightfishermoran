#ifndef  Gene_INC
#define  Gene_INC

#include <time.h> //time(), rand()

#include <iostream> //std::cout
#include <ostream> //std::ostream
#include <vector>// std::vector


 //The class models a monoallelic Gene; the allele type is an unsigned int instead of the widely used char.
class Gene
{
public:

        static const unsigned kNumAlleles = 2;
        typedef unsigned Allele; 

        Gene () : _allele(rand() % kNumAlleles) {};    							
        Gene (const Allele &other)  : _allele(other % kNumAlleles) {}; 	
        Gene (const Gene &other) : _allele(other._allele) {};   				
        ~Gene ();                            									

        Allele allele() const{return _allele;}

        Gene& operator = (const Gene &other);

private:
        Allele _allele;

        friend std::ostream & operator << (std::ostream &os, const Gene &obj);
        friend bool operator == (const Gene &a, const Gene &b){ return (a._allele == b._allele); };
        friend bool operator != (const Gene &a, const Gene &b){ return (a._allele != b._allele); };

}; 

#endif
