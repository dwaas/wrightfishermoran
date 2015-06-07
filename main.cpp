#include "DiscreteDifferential.hpp"
#include "Gene.h"
#include "Population.h"

#include <limits> 			//std::numeric_limits
#include <iomanip>			//std::setprecision
#include <memory> 			//std::unique_ptr()
#include <time.h> 			//time()


//root
#include "TApplication.h"
#include "TAxis.h"
#include "TAxis3D.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TStyle.h"
#include "TView.h"

//TODO clean code
//TODO documentation
//TODO random
//TODO use gnuplot instead of rootjunk

// FUTURE UPGRADES
//TODO parallelisation
//TODO wrapper class for function that includes domain
//TODO fitting
//TODO argc, argv
//TODO hdr, src folders
//TODO Population polymorphism
//TODO templates in DiscreteDifferential

//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad



int main(int argc,char* argv[])
{
	typedef std::numeric_limits< double > double_limit;
	std::cout.precision(double_limit::digits10);

	// kDeltaNum and kMaxTimesteps should be around the same order of magnitude
	// to make a sensible comparison between WF and M models
	//
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10100, 
				 			kDeltaNum = kInitialNumMax - kInitialNumMin,
				 			kMinTimesteps = 0, kMaxTimesteps = 100,
							kTransient = 40;


	std::cout << "program started" << std::endl;
//initialise populations  
//
	Population wright_fisher(kInitialNumMin, kInitialNumMax,
				 kMaxTimesteps, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);
/*  
	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimesteps, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );

				selected_gene = rand() % v.size(); // select another random gene
				v.erase( v.begin() + selected_gene ); //gene death
			}
		);
*/

//==========================================================FOKKER PLANCK TEST

	
	IsFPESolution([&wright_fisher](unsigned n, unsigned t)
			{ 
				return wright_fisher.probability_function(n,t);
			}, 
			kInitialNumMin, kInitialNumMax, 
			kMinTimesteps, kMaxTimesteps); //TODO implement transient



//=========================================================GRAPHICS
/*

	std::unique_ptr<TApplication> app( new TApplication("App", &argc, argv));

//	std::unique_ptr<TAxis3D> axes( new TAxis3D);
//	std::unique_ptr<TStyle> style( new TStyle);
//	std::unique_ptr<TView> view( new TView(1));

//	axes->ToggleRulers();
//	axes->Draw();
	
	std::unique_ptr<TCanvas> canvas( new TCanvas("canvas","Surfaces Drawing Options",
													200,10,700,900));
	canvas -> Divide(2,1,0,0);

	std::unique_ptr<TGraph2D> wright_fisher_graph( new TGraph2D(kDeltaNum*kMaxTimesteps));
	wright_fisher_graph-> SetName("WF");
	
	std::unique_ptr<TGraph2D> moran_graph( new TGraph2D(kDeltaNum*kMaxTimesteps));
	moran_graph-> SetName("M");

	unsigned point_num = 0;
	//Fill TGraph2D
	for (unsigned num = 0; num < kDeltaNum; ++num)
	{
		for (unsigned timestep = kMinTimesteps; timestep < kMaxTimesteps; ++timestep)
		{
			wright_fisher_graph->SetPoint(point_num, num, timestep, moran.probability_function(num,timestep));
			moran_graph->SetPoint(point_num, num, timestep, moran.probability_function(num,timestep));
			++point_num;
		}
		std::cout << "set all timestep for num =  " << num << std::endl;
	}
	std::cout << "point num = " << ++point_num << std::endl;
	std::cout << "point num product = " << kDeltaNum * kMaxTimesteps << std::endl;

	//FIXME point_num is 1 more than the product

//wf plot
	wright_fisher_graph->SetMarkerColor(kGreen);

	wright_fisher_graph->SetTitle("Wright Fisher graph");                          //axis' titles

	wright_fisher_graph->GetXaxis() -> SetTitle("initial number of Genes");
	wright_fisher_graph->GetXaxis() -> SetRangeUser(kInitialNumMin, kInitialNumMax);

	wright_fisher_graph->GetYaxis() -> SetTitle("timesteps");
	wright_fisher_graph->GetYaxis() -> SetRangeUser(kMinTimesteps, kMaxTimesteps);

	wright_fisher_graph->GetZaxis() -> SetTitle("gene0/ total Genes");
	wright_fisher_graph->GetZaxis() -> SetRangeUser(0.0, 1.0);

	canvas -> cd(1);
	wright_fisher_graph->Draw("P.");

//moran plot	
  
	moran_graph->SetMarkerColor(kRed);

	moran_graph->SetTitle("Moran graph");                          //axis' titles

	moran_graph->GetXaxis() -> SetTitle("initial number of Genes");
	moran_graph->GetXaxis() -> SetRangeUser(kInitialNumMin, kInitialNumMax);

	moran_graph->GetYaxis() -> SetTitle("timesteps");
	moran_graph->GetYaxis() -> SetRangeUser(kMinTimesteps, kMaxTimesteps);

	moran_graph->GetZaxis() -> SetTitle("gene0/ total Genes");
	moran_graph->GetZaxis() -> SetRangeUser(0.0, 1.0);

	canvas -> cd(2);
	moran_graph->Draw("P.");

	app->Run();

*/	
	std::cout << "program ended" << std::endl;

	return 0;
}
