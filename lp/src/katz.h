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
#include<boost/lexical_cast.hpp>
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


void katz(Graph trg, Graph tg, int lp, vector<EDGE>& potential_edges, int l, double beta, const char* outfile)
{
	
	
	vector<double> lookup(vector<double>(l+1));
	
	for( unsigned int degree = 0; degree <= l; ++degree ) 
	{
		lookup.at( degree ) = pow( beta, degree );
	}
	
	
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
		
		vector<long long int> oldSearch;
		
		vector<long long int> oldHits( num_vertices(trg) );
		
		oldSearch.push_back( vertex );
		
		oldHits.at( vertex ) = 1;
		
		for( int degree = 1; degree <= l; ++degree ) 
		{
			vector<long long int> newHits( num_vertices(trg) );
			
			vector<bool> found( num_vertices(trg) );
			
			vector<long long int> newSearch;
			
			for( vector<long long int>::iterator vertexIterator = oldSearch.begin(); vertexIterator != oldSearch.end(); ++vertexIterator ) 
			{ 
				long long int searchVertex = *vertexIterator;
				
				AdjacencyIterator e1,e2;
				
				tie(e1,e2) = adjacent_vertices(searchVertex,trg);
				
				vector<long long int> neighbors(e2-e1);
				
				copy(e1,e2,neighbors.begin()); 
			
				for( vector<long long int>::iterator neighborIterator = neighbors.begin(); neighborIterator != neighbors.end(); ++neighborIterator ) 
				{
					long long int neighborVertex = *neighborIterator;
					
					newHits.at( neighborVertex ) += oldHits.at( searchVertex );
					
					if( !found.at( neighborVertex ) ) 
					{
						found.at( neighborVertex ) = true;
						
						newSearch.push_back( neighborVertex );
					}
				}
			}
			
			double factor = lookup.at( degree );
			
			for( int i = 0; i < scores.size(); ++i ) 
			{
				scores.at( i ) += factor * newHits.at( i );
			}
			
			oldSearch.swap( newSearch );
			
			oldHits.swap( newHits );

		}
	
		it->score = scores.at(neighbor);
			
		//Katz done		
			
	}
	
	sort(potential_edges.begin(),potential_edges.end(),predicate);
	
	end = clock();
	
	compute_result(potential_edges,tg,lp,"Katz"+boost::lexical_cast<std::string>(l),outfile);
	
	ofstream myfile;
	
	myfile.open(outfile,ios::app);
	
	myfile<<(end-start)/double(CLOCKS_PER_SEC)<<endl;
	
	myfile.close();
	
	return;
	
} 


