#include "Gene.h"
#include "Population.h"

#include <memory> // std::unique_ptr()
#include <time.h> //time()


//root
#include "TCanvas.h"
#include "TGraph2D.h"

//TODO documentation
//TODO cvim style formatting/ comments
//TODO random
//TODO inline funcs
//TODO check consts
//TODO fitting
//TODO parallelisatio
//TODO indentation
//TODO start program with different parameters
//TODO plot functions
//TODO derivation
//TODO FPE function
//TODO files in different folders
//TODO use polymorphism for wright_fisher and moran
//

//
//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad


int main(int argc,char* argv[])
{
	// kInitialNumMin and kMaxTimestep should be around the same order of magnitude
	static const unsigned kInitialNumMin = 1000, kInitialNumMax = 1002, 
				 			kMaxTimestep = 1000;

	std::cout << "program started" << std::endl;
/*  	Population wright_fisher(kInitialNumMin,kInitialNumMax,
				 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);
*/
	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );

				selected_gene = rand() % v.size(); // select another random gene
				v.erase( v.begin() + selected_gene ); //gene death
			}
		);
//	Gene a;
//	std::cout << "a = " << a << std::endl;
//	std::cout << "program ended" << std::endl;
	
	static const unsigned kDeltaNum = kInitialNumMax - kInitialNumMin;

	std::unique_ptr<TCanvas> canvas( new TCanvas("c1","Surfaces Drawing Options",
													200,10,700,900));
	std::unique_ptr<TGraph2D> moran_graph( new TGraph2D(kDeltaNum*kMaxTimestep));
	
	unsigned point_num = 0;
	//Fill TGraph2D
	for (unsigned n = 0; n < kDeltaNum; ++n)
	{
		for (unsigned t = 0; t < kMaxTimestep; ++t)
		{
			moran_graph->SetPoint(point_num, n, t, moran.probability_function(n,t));
			++point_num;
		}
	}
	std::cout << "point num = " << ++point_num << std::endl;
	std::cout << "point num product = " << kDeltaNum * kMaxTimestep << std::endl;

	return 0;
}
