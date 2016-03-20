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
#include<cmath>
#include<functional>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graph_traits.hpp>
#include<utility>
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


void propflow(Graph trg, Graph tg, int lp, vector<EDGE>& potential_edges, int l, const char* outfile)
{	
	clock_t start,end;
	
	start = clock();	
	
	AdjacencyIterator e1,e2,e3,e4;
	
	int i=1;
	
	//cout<<potential_edges.size()<<endl;
	
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
		
		vector<bool> found = vector<bool>( num_vertices(trg) );
		
		vector<long long int> search;
		
		found.at( vertex ) = true;
		
		search.push_back( vertex );
		
		scores.at( vertex ) = 1;
		
		for( int degree = 0; degree < l; ++degree ) 
		{
			vector<long long int> newSearch;
			
			for( vector<long long int>::iterator vertexIterator = search.begin(); vertexIterator != search.end(); ++vertexIterator ) 
			{
				long long int searchVertex = *vertexIterator;
				
				double sourceVertexInput = scores.at( searchVertex );
				
				AdjacencyIterator e1,e2;
				
				tie(e1,e2) = adjacent_vertices(searchVertex,trg);
				
				vector<long long int> neighbors(e2-e1);
				
				copy(e1,e2,neighbors.begin()); 
				
				double totalOutput = neighbors.size();

				for( vector<long long int>::iterator neighborIterator = neighbors.begin(); neighborIterator != neighbors.end(); ++neighborIterator ) 
				{
					long long int neighbor = *neighborIterator;
					
					double output = 1.0;
					
					double probability = sourceVertexInput * (output / totalOutput);
					
					scores.at( neighbor ) += probability;
					
					if( !found.at( neighbor ) ) 
					{
						found.at( neighbor ) = true;
						newSearch.push_back( neighbor );
					}
				}
			}
			search.swap( newSearch );
		}
	
		it->score = scores.at(neighbor);
		
		//Propflow done		
			
	}
	
	sort(potential_edges.begin(),potential_edges.end(),predicate);
	
	end = clock();
	
	compute_result(potential_edges,tg,lp,"PF",outfile);
	
	ofstream myfile;
	
	myfile.open(outfile,ios::app);
	
	myfile<<(end-start)/double(CLOCKS_PER_SEC)<<endl;
	
	myfile.close();
	
	return;
	
} 


