#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <math.h>
#include <functional>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
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

class EDGE
{
	public:
	int src,dest;

	double score;

};

bool predicate(const EDGE& a, const EDGE& b)
{
    return a.score > b.score;
}


//Assuming undirected graphs

Graph read_graph(const char* filename)
{

	Graph g;

	ifstream infile;

	long long int a,b,i=0;

	std::unordered_map<long long int,long long int> node_map;

	std::unordered_map<long long int, std::unordered_map<long long int, bool> > adjlist;

	//reading the graph

	infile.open(filename,ios::in);

	if(infile.is_open())
	{
		while(infile>>a>>b)
		{


			if(node_map.find(a)==node_map.end())
			{
				node_map[a] = i++;
			}

			if(node_map.find(b)==node_map.end())
			{
				node_map[b] = i++;
			}

			adjlist[node_map[a]][node_map[b]] = true;

			adjlist[node_map[b]][node_map[a]] = true;


		}
	}

	infile.close();


	//adding egdes to the graph

	std::unordered_map<long long int, std::unordered_map<long long int, bool> >::iterator src_it;

	for(src_it=adjlist.begin();src_it!=adjlist.end();++src_it)
	{

		std::unordered_map<long long int, bool>::iterator dest_it;

		for(dest_it = src_it->second.begin();dest_it != src_it->second.end();++dest_it)
		{

			//removing self loops

			if(src_it->first<dest_it->first)
			{
				add_edge(src_it->first,dest_it->first,g);

			}
		}


	}


	return g;
}


void graph_stats(Graph g)
{

	cout<<"#vertices = ";

	VertexIterator v1,v2;

	long long int c=0;

	tie(v1,v2) = vertices(g);

	for(;v1!=v2;++v1)
	{
		if(degree(*v1,g)!=0)
		{
			c++;
		}
	}

	cout<<c<<endl;


	//cout<<"#vertices = "<<num_vertices(g)<<endl;

	cout<<"#edges = "<<num_edges(g)<<endl;

	return;

}

double calc_alpha(Graph g)
{

	double alpha=1, sum=0;

	VertexIterator v1,v2;

	tie(v1,v2) = vertices(g);

	int counter=0 ;

	for(;v1!=v2;++v1)
	{

		if(degree(*v1,g)>0)
		{

			counter++;

			sum+=log(degree(*v1,g));
		}

	}

	alpha+=(counter/sum);

	return alpha;
}




Graph sampling_graph(Graph tg, float per)
{

	Graph g;

	long long int m = num_edges(tg);

	long long int total = m*per, i=0, index;

	std::unordered_map<long long int, vector<long long int> > test_edges(m);

	std::unordered_map<long long int, bool > marked(m);

	EdgeIterator e1,e2;

	tie(e1,e2) = edges(tg);

	for(;e1!=e2;++e1)
	{

		test_edges[i].push_back(source(*e1,tg));

		test_edges[i].push_back(target(*e1,tg));

		i++;

	}



	//random sampling of edges

	srand(time(NULL));

	i=0;

	while(i<total)
	{

		index = (abs(rand()*rand())%m);

		if(!marked[index])
		{
			add_edge(test_edges[index][0],test_edges[index][1],g);

			marked[index] = true;

			i++;

		}


	}



	return g;
}

long long int calculate_potential_links(Graph g, Graph tg, vector<EDGE>& map1, int deg)
{

	int depth=deg;

	long long int c=0;

	std::unordered_map<long long int, std::unordered_map<long long int,bool> > check_map;

	VertexIterator v1,v2;

	//calculating nodes upto depth

	for(tie(v1,v2)=vertices(g);v1!=v2;++v1)
	{

		if(degree(*v1,g)>0)
		{
			long long int vertex = *v1;

			vector<bool> found = vector<bool>( num_vertices(g) );

			vector<long long int> search;

			found.at( vertex ) = true;

			search.push_back( vertex );

			for(int i = 0; i < depth; ++i)
			{

				vector<long long int> newSearch;

				for( vector<long long int>::iterator vertexIterator = search.begin(); vertexIterator != search.end(); ++vertexIterator )
				{
					long long int searchVertex = *vertexIterator;

					AdjacencyIterator e1,e2;

					tie(e1,e2) = adjacent_vertices(searchVertex,g);

					vector<long long int> neighbors(e2-e1);

					copy(e1,e2,neighbors.begin());


					for( vector<long long int>::iterator neighborIterator = neighbors.begin(); neighborIterator != neighbors.end(); ++neighborIterator )
					{
						long long int neighbor = *neighborIterator;

						if( !found.at( neighbor ) )
						{
							found.at( neighbor ) = true;
							newSearch.push_back( neighbor );
						}
					}
				}

				search.swap( newSearch );


				if(search.size()==0)
				{
					break;
				}


			}
			//Done BFS all levels for node *v1

			//Add elements of search to Potential links with node source as *v1

			for(vector<long long int>::iterator it = search.begin();it!=search.end();++it)
			{

				if(!check_map[*v1][*it])
				{
					check_map[*v1][*it] = true;

					EDGE e;

					e.src = *v1;

					e.dest = *it;

					e.score = 0;



					bool val;

					Edge e1;

					tie(e1,val) = edge(e.src,e.dest,g);

					//push the potential link only if it is not present in trg

					if(!val)
					{

						//check if this edge is present in tg
						tie(e1,val) = edge(e.src,e.dest,tg);

						if(val)
						{
							c++;
						}

						map1.push_back(e);
					}

				}
			}

		}

	}

	return c;

}
