#include "DiscreteDerivative.hpp"
#include "Gene.h"
#include "Population.h"

#include <functional> //std::bind, std::placeholders::_1
#include <memory> // std::unique_ptr()
#include <time.h> //time()


//root
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TAxis3D.h"
#include "TStyle.h"
#include "TView.h"

//TODO order headers alphabetically
//TODO documentation
//TODO random
//TODO inline funcs
//TODO check consts
//TODO fitting
//TODO parallelisation
//TODO indentation
//TODO start program with different parameters
//TODO plot functions
//TODO derivation
//TODO FPE function
//TODO files in different folders
//TODO use polymorphism for wright_fisher and moran
//TODO use gnuplot instead of rootjunk
//TODO template DiscreteDerivative

//
//HYPOTHESES:
//1) discrete derivative
//2) discrete > continuous model(omitted fitting)
//3) gegenbauer is bad


int main(int argc,char* argv[])
{
	using namespace std::placeholders;

	// kInitialNumMin and kMaxTimestep should be around the same order of magnitude
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10002, 
				 			kInitialTimestep = 0, kMaxTimestep = 10000;

	std::cout << "program started" << std::endl;
  
	Population wright_fisher(kInitialNumMin, kInitialNumMax,
				 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );
			}
		);
/*  
	Population moran(kInitialNumMin, kInitialNumMax,
			 kMaxTimestep, [](GeneVec& v)
			{		
				unsigned selected_gene = rand() % v.size();
				v.push_back( v[selected_gene] );

				selected_gene = rand() % v.size(); // select another random gene
				v.erase( v.begin() + selected_gene ); //gene death
			}
		);
*/


//	Gene a;
//	std::cout << "a = " << a << std::endl;
	
	static const unsigned kDeltaNum = kInitialNumMax - kInitialNumMin;
//
//	auto testF = [](int arg)
//	{	
//		if(arg < 5){ return 2*arg;}
//		if(arg == 5){return 30;}
//		if(arg > 5){return (-4)*arg;}
//	};
//

	int n = kInitialNumMax - kInitialNumMin - 1, t = 0;
	//TODO shorter way to write this
	

	//auto WFTimeFunction = std::bind([&wright_fisher](int n, int t)
	//								{
	//									return wright_fisher.probability_function(n, t);
	//								}, kInitialNumMin, _1);
	auto WFTimeFunction = [&wright_fisher, n] (int t)
							{ 
								return wright_fisher.probability_function(n, t); 
							};

	std::cout << WFTimeFunction(t) << std::endl;

	DiscreteDerivative d_WF_dt(WFTimeFunction, kInitialTimestep, kMaxTimestep);

	std::cout << "DiscreteDerivative constructed with arg_min = " << d_WF_dt.arg_min();
	std::cout << " and arg_max =  " << d_WF_dt.arg_max() << std::endl;

	std::cout << "WF     in " <<  t-1 << "  = " << WFTimeFunction(t-1) << std::endl;
	std::cout << "WF     in " <<  t << "  = " << WFTimeFunction(t) << std::endl;
	std::cout << "WF     in " <<  t+1 << "  = " << WFTimeFunction(t+1) << std::endl;
	std::cout << "discr der in " << t << "  = " << d_WF_dt(t) << std::endl;

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

	std::unique_ptr<TGraph2D> wright_fisher_graph( new TGraph2D(kDeltaNum*kMaxTimestep));
	wright_fisher_graph-> SetName("WF");
	
	std::unique_ptr<TGraph2D> moran_graph( new TGraph2D(kDeltaNum*kMaxTimestep));
	moran_graph-> SetName("M");

	unsigned point_num = 0;
	//Fill TGraph2D
	for (unsigned n = 0; n < kDeltaNum; ++n)
	{
		for (unsigned t = 0; t < kMaxTimestep; ++t)
		{
			wright_fisher_graph->SetPoint(point_num, n, t, moran.probability_function(n,t));
			moran_graph->SetPoint(point_num, n, t, moran.probability_function(n,t));
			++point_num;
		}
		std::cout << "set all t for n =  " << n << std::endl;
	}
	std::cout << "point num = " << ++point_num << std::endl;
	std::cout << "point num product = " << kDeltaNum * kMaxTimestep << std::endl;

	//FIXME point_num is 1 more than the product

//wf plot
	wright_fisher_graph->SetMarkerColor(kGreen);

	wright_fisher_graph->SetTitle("Wright Fisher graph");                          //axis' titles

	wright_fisher_graph->GetXaxis() -> SetTitle("initial number of Genes");
	wright_fisher_graph->GetXaxis() -> SetRangeUser(kInitialNumMin, kInitialNumMax);

	wright_fisher_graph->GetYaxis() -> SetTitle("timesteps");
	wright_fisher_graph->GetYaxis() -> SetRangeUser(0, kMaxTimestep);

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
	moran_graph->GetYaxis() -> SetRangeUser(0, kMaxTimestep);

	moran_graph->GetZaxis() -> SetTitle("gene0/ total Genes");
	moran_graph->GetZaxis() -> SetRangeUser(0.0, 1.0);

	canvas -> cd(2);
	moran_graph->Draw("P.");

	app->Run();

*/	
	std::cout << "program ended" << std::endl;

	return 0;
}
