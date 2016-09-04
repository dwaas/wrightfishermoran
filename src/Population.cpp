#include "../include/Population.h"

Population::Population (const unsigned kInitialNumMin,
                        const unsigned kInitialNumMax,
                        const unsigned kMaxTimesteps,
                        std::function<void (GeneVec&)> PopEvolution):

_gene_vec(kInitialNumMin),
_probability_function( (kInitialNumMax - kInitialNumMin + 1),
std::vector<double> (kMaxTimesteps + 1)),
_kInitialNumMin(kInitialNumMin),
_kInitialNumMax(kInitialNumMax),
_kMaxTimesteps(kMaxTimesteps)

{
	for(unsigned num = _kInitialNumMin; num < _kInitialNumMax; ++num)
	{
		for (unsigned timestep = 0; timestep < _kMaxTimesteps; ++timestep)
		{
			 PopEvolution(_gene_vec);

                         //count allele 0
			 double ratio = std::count(_gene_vec.begin(), _gene_vec.end(), 0)
                                        / (double) _gene_vec.size();

			 _probability_function[num - kInitialNumMin][timestep] = ratio;
		}
	}
	std::cout << _gene_vec.size() << std::endl;
	std::cout << "population was succesfully initialised." << std::endl;
}


Population::Population ( const Population &other )
{
	_gene_vec = other._gene_vec;
	_probability_function = other._probability_function;

}

Population::~Population ()
{
}

Population&
Population::operator = ( const Population &other )
{
	if ( this != &other )
	{
		_gene_vec = other._gene_vec;
		_probability_function = other._probability_function;
	}

	return *this;
}

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
