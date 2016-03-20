#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<ctime>
#include<cstdlib>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<functional>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graph_traits.hpp>
#include<boost/graph/breadth_first_search.hpp>
#include<utility>
#include "statistics.h"
#include <GetOpt.h>
#include "graph.h"
#include "cn.h"
#include "cngf.h"
#include "aa.h"
#include "ra.h"
#include "pa.h"
#include "rwr.h"
#include "katz.h"
#include "propflow.h"
#include "thresholding.h"
#include "la.h"
#include "two_phase.h"
using namespace boost;
using namespace std;


typedef boost::adjacency_list<vecS, vecS, undirectedS> Graph;
typedef Graph::vertex_iterator VertexIterator;
typedef Graph::edge_iterator EdgeIterator;
typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;
typedef Graph::adjacency_iterator AdjacencyIterator;


#define MIN(a,b) a>b?b:a
#define MAX(a,b) a>b?a:b


void usage( const char* binary ) {
	cerr << "Usage: " << binary << " [options] predictor\n";
	cerr << "Options: -g NETWORK     File containing the network in which to predict\n";
	cerr << "         -i ITERATION   The direction of edges to use; must be in {I,O}\n";
	cerr << "         -n DISTANCE    Degree of neighborhood in which to predict\n";
	cerr << "         -c             Specifies that node-pairs for prediction are available at standard input\n";
}


int main(int argc,char* argv[])
{


	char ch;

	const char* infile;

	const char* outfile;

	int iter, dist, lp;

	float sparseness, per;


	while( (ch = getopt( argc, argv, "g:s:l:i:o:n:" )) != EOF )
	{
		if(ch=='g')
		{
			infile = optarg;

		}

		if(ch=='i')
		{
			iter = atoi(optarg);

		}

		if(ch=='s')
		{
			sparseness = atof(optarg);
		}

		if(ch=='l')
		{
			per = atof(optarg);
		}

		if(ch=='o')
		{
			outfile = optarg;
		}

		if(ch=='n')
		{
			dist = atoi(optarg);
		}

	}

	if(argc < optind)
	{
		usage(argv[0]);
		exit(0);
	}

	vector<int> lp_vec;

	for(int i=1;i<=iter;++i)
	{

		Graph tg,trg;

		clock_t start,end;

		vector<EDGE> potential_edges;

		std::unordered_map<long long int,std::unordered_map<int, vector<long long int> > > reachable_nodes;

		cout<<"\n---------------------\n";

		cout<<"Iteration "<<i<<endl;

		cout<<"\n---------------------\n";

		start = clock();

		tg = read_graph(infile);

		end = clock();

		//cout<<"\nGraph Reading Time = "<<(end-start)/double(CLOCKS_PER_SEC)<<" sec"<<endl;

		cout<<"\nGraph reading done\n";

		start = clock();

		trg = sampling_graph(tg,sparseness);

		end = clock();

		//cout<<"\nGraph Sampling Time = "<<(end-start)/double(CLOCKS_PER_SEC)<<" sec"<<endl;

		cout<<"\nGraph sampling done\n";

		//graph_stats(tg);

		//graph_stats(trg);

		start = clock();

		lp = calculate_potential_links(trg,tg,potential_edges,dist);

		lp = lp*per;

		lp_vec.push_back(lp);

		if(i>1)
		{
			lp = lp_vec[0];
		}

		end = clock();


		//cout<<"\nPotential Links Calculation Time = "<<(end-start)/double(CLOCKS_PER_SEC)<<" sec"<<endl;


		common_neighbors(trg,tg,lp,potential_edges,outfile);

		cout<<"\nCN done "<<endl;


		adamic_adar(trg,tg,lp,potential_edges,outfile);

		cout<<"\nAA done "<<endl;


		resource_allocation(trg,tg,lp,potential_edges,outfile);

		cout<<"\nRA done "<<endl;

		preferential_attachment(trg,tg,lp,potential_edges,outfile);

		cout<<"\nPA done "<<endl;

		/*

		cn_gf(trg,tg,lp,potential_edges,outfile);

		cout<<"\nCNGF done "<<endl;

		//random_walk_restart(trg,tg,lp,potential_edges,0.15,outfile);

		//cout<<"\nRWR done "<<endl;



		katz(trg,tg,lp,potential_edges,5,0.005,outfile);

		cout<<"\nKatz done "<<endl;


		propflow(trg,tg,lp,potential_edges,5,outfile);

		cout<<"\nPropflow done "<<endl;




		//Thresholding Based Approach


		thresholding(trg,tg,lp,potential_edges,calculate_threshold(trg),outfile,"MET");

		cout<<"\nMET done "<<endl;



		//LA Approach

		la(trg,tg,lp,potential_edges,1,calc_alpha(trg),outfile,"LA_MLE");

		la(trg,tg,lp,potential_edges,1,calc_alpha(trg),outfile,"LA_PL");

		la(trg,tg,lp,potential_edges,1,calc_alpha(trg),outfile,"LA_E");

		la(trg,tg,lp,potential_edges,1,calc_alpha(trg),outfile,"LA_N");

		cout<<"\nLA done "<<endl;

		*/

		//2 phase approach

		/*

		float j=0.5;

			twophase(trg,tg,lp,potential_edges,outfile,j,"pa","pa","pa+pa"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"cn","cn","cn+cn"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"aa","aa","aa+aa"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"ra","ra","ra+ra"+boost::lexical_cast<string>(j));


			twophase(trg,tg,lp,potential_edges,outfile,j,"pa","cn","pa+cn"+boost::lexical_cast<string>(j));


			twophase(trg,tg,lp,potential_edges,outfile,j,"pa","aa","pa+aa"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"pa","ra","pa+ra"+boost::lexical_cast<string>(j));


			twophase(trg,tg,lp,potential_edges,outfile,j,"cn","pa","cn+pa"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"cn","aa","cn+aa"+boost::lexical_cast<string>(j));


			twophase(trg,tg,lp,potential_edges,outfile,j,"cn","ra","cn+ra"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"aa","pa","aa+pa"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"aa","cn","aa+cn"+boost::lexical_cast<string>(j));
			twophase(trg,tg,lp,potential_edges,outfile,j,"aa","ra","aa+ra"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"ra","pa","ra+pa"+boost::lexical_cast<string>(j));

			twophase(trg,tg,lp,potential_edges,outfile,j,"ra","cn","ra+cn"+boost::lexical_cast<string>(j));


			twophase(trg,tg,lp,potential_edges,outfile,j,"ra","aa","ra+aa"+boost::lexical_cast<string>(j));

		cout<<"\n2 Phase done"<<endl;
		*/
	}


	return 0;
}
