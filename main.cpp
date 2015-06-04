#include "DiscreteDerivative.hpp"
#include "Gene.h"
#include "Population.h"

#include <limits> 			//std::numeric_limits
#include <iomanip>			//std::setprecision
#include <memory> 			//std::unique_ptr()
#include <time.h> 			//time()


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
//TODO fitting
//TODO parallelisation
//TODO start program with different parameters
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
	typedef std::numeric_limits< double > double_limit;
	std::cout.precision(double_limit::digits10);

	// kInitialNumMin and kMaxTimestep should be around the same order of magnitude
	//
	static const unsigned kInitialNumMin = 10000, kInitialNumMax = 10002, 
				 			kMinTimestep = 0, kMaxTimestep = 10000;

	std::cout << "program started" << std::endl;
//initialise populations  
//
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

//==========================================================FOKKER PLANCK TEST
	
//
//	auto testF = [](int arg)
//	{	
//		if(arg < 5){ return 2*arg;}
//		if(arg == 5){return 30;}
//		if(arg > 5){return (-4)*arg;}
//	};
//

	unsigned n = kInitialNumMax - kInitialNumMin - 1, t = 1000;
	

	auto WFTimeFunction = [&wright_fisher, n] (unsigned t)
							{
								return wright_fisher.probability_function(n, t); //FIXME no domain guard 
							};

	std::cout << WFTimeFunction(t) << std::endl;

	DiscreteDerivative d_WF_dt(WFTimeFunction, kMinTimestep, kMaxTimestep);

	std::cout << "DiscreteDerivative constructed with arg_min = " << d_WF_dt.arg_min();
	std::cout << " and arg_max =  " << d_WF_dt.arg_max() << std::endl;

//	std::cout << "WF     in " <<  t-1 << "  = " << std::fixed << WFTimeFunction(t-1) << std::endl;
//	std::cout << "WF     in " <<  t << "  = "   << std::fixed << WFTimeFunction(t) << std::endl;
//	std::cout << "WF     in " <<  t+1 << "  = " << std::fixed << WFTimeFunction(t+1) << std::endl;
	std::cout << "discr der in t = " << t << "  = " << std::fixed << d_WF_dt(t) << std::endl;

	std::cout << "manual dew in " << t << "  = " << std::fixed 
				<< (WFTimeFunction(t+1)- WFTimeFunction(t-1))/2.0 << std::endl;
	
	
	//TODO test from here
	auto WFNumFunction = [&wright_fisher, t] (unsigned n)
						{
							return wright_fisher.probability_function(n, t); 
						};
	DiscreteDerivative d_WF_dn(WFNumFunction, kInitialNumMin, kInitialNumMax);

	auto d_WF_dnFunc = [&d_WF_dn] (unsigned n)
					{
						return d_WF_dn(n);
					};
	
	DiscreteDerivative d2_WF_dn2(d_WF_dnFunc, kInitialNumMin, kInitialNumMax);

	std::cout << "discr der in n = " << n << "  = " << std::fixed << d2_WF_dn2(n) << std::endl;

//=========================================================GRAPHICS
/*
	static const unsigned kDeltaNum = kInitialNumMax - kInitialNumMin;

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
