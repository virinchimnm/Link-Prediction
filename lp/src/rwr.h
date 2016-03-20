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
#include<utility>
#include "statistics.h"
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


void random_walk_restart(Graph trg, Graph tg, int lp, vector<EDGE>& potential_edges, double alpha, const char* outfile)
{
	
	clock_t start,end;
	
	start = clock();	
	
	AdjacencyIterator e1,e2,e3,e4;
	
	int i=1;
	
	for(vector<EDGE>::iterator it=potential_edges.begin();it!=potential_edges.end();++it)
	{
		
		
		/*if(i%1000==0)
		{
			cout<<i<<endl;
		}
		
		i++;
		*/

		
		long long int vertex = it->src;
		
		long long int neighbor = it->dest;
		
		
		vector<double> scores = vector<double>( num_vertices(trg) );
		
		vector<double> oldPageRanks = vector<double>( num_vertices(trg) );
		
		long long int currentVertex = vertex;
		
		scores.at( currentVertex )++;
		
	
		for( unsigned int step = 1; true ; step++ ) 
		{
			
			AdjacencyIterator e1,e2;
			
			tie(e1,e2) = adjacent_vertices(currentVertex,trg);
			
			vector<long long int> neighbors(e2-e1);
			
			copy(e1,e2,neighbors.begin()); 
			
			
			if( neighbors.size() < 1 || (double)rand()/RAND_MAX < alpha ) 
			{
				currentVertex = vertex;
			} 
			else 
			{					
				long long int randomNeighbor = rand() % neighbors.size();
				currentVertex = neighbors.at( randomNeighbor );
			}
			
			scores.at( currentVertex )++;
			
			
			if( step == 100 ) 
			{
				oldPageRanks = scores;
			} 
			else if( step % 100 == 0 ) 
			{
				double r = Statistics<double>::sampleCorrelationCoefficient( oldPageRanks, scores );
//				cerr << r << "\n";
				if( r > 0.9999 ) 
				{
					break;
					//return this->scores.at( neighbor );
				} 
				else 
				{
					oldPageRanks = scores;
				}
			}
			
		}
	
		it->score = scores.at(neighbor);
		
		//RWR done		
			
	}
	
	sort(potential_edges.begin(),potential_edges.end(),predicate);
	
	end = clock();
	
	compute_result(potential_edges,tg,lp,"RWR",outfile);
	
	ofstream myfile;
	
	myfile.open(outfile,ios::app);
	
	myfile<<(end-start)/double(CLOCKS_PER_SEC)<<endl;
	
	myfile.close();
	
	return;
	
} 


