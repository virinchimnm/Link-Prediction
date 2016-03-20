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

float calculate_threshold(Graph g)
{
	float threshold,sum=0.0;
	
	int max = 0,c=0;
	
	VertexIterator v1,v2;
	
	tie(v1,v2) = vertices(g);

	vector<int> deg_vec(num_vertices(g));
	
	for(;v1!=v2;++v1)
	{
		
		sum+=degree(*v1,g);

		if(degree(*v1,g)>0)
		{

			c++;

			deg_vec.push_back(degree(*v1,g));
		}
			

		
		if(degree(*v1,g)>max)
			
			max = degree(*v1,g);
	}
	
	
	threshold = sum/(c*0.1);


	return threshold;

}


void thresholding(Graph trg, Graph tg, int lp, vector<EDGE>& potential_edges, float threshold, const char* outfile,string str)
{
	
	clock_t start,end;
	
	start = clock();
	
	AdjacencyIterator e1,e2,e3,e4;
	
	for(vector<EDGE>::iterator it=potential_edges.begin();it!=potential_edges.end();++it)
	{
		
		tie(e1,e2) = adjacent_vertices(it->src,trg);
		
		tie(e3,e4) = adjacent_vertices(it->dest,trg);
		
		vector<int> v1(e2-e1),v2(e4-e3);
		
		vector<int> common_set(MAX(degree(it->src,trg),degree(it->dest,trg)));
				
		vector<int>::iterator it1;
		
		copy(e1,e2,v1.begin());
		
		copy(e3,e4,v2.begin());
		
		//the adjacency list is not sorted::could give wrong results in case of set_intersection
		
		sort(v1.begin(),v1.end());
		
		sort(v2.begin(),v2.end());
		
		it1 = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),common_set.begin());
				
		common_set.resize(it1-common_set.begin());
		
		it->score = 0;
				
		for(it1=common_set.begin();it1!=common_set.end();++it1)
		{
			if(degree(*it1,trg)<=threshold)
			{
				it->score+=(1.0/sqrt(degree(*it1,trg)));
			}
		}
		
		
			
	}
	
	sort(potential_edges.begin(),potential_edges.end(),predicate);
	
	end = clock();
	
	end = clock();
	
	compute_result(potential_edges,tg,lp,str,outfile);
	
	ofstream myfile;
	
	myfile.open(outfile,ios::app);
	
	myfile<<(end-start)/double(CLOCKS_PER_SEC)<<endl;
	
	myfile.close();
	
	return;
	
}
