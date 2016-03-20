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


void twophase(Graph trg, Graph tg, int lp, vector<EDGE>& potential_edges, const char* outfile, float lpf,string phase1, string phase2, string str)
{
	clock_t start,end;
	
	start = clock();
	
	AdjacencyIterator e1,e2,e3,e4;
	
	float threshold = calculate_threshold(trg);
	
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
		
		if(phase1=="cn")
		{
			
			it->score=common_set.size();
			
		}
		else if(phase1=="aa")
		{
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				it->score+=(1.0/log10(degree(*it1,trg)));
			}
			
		}
		else if(phase1=="ra")
		{
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				it->score+=(1.0/(degree(*it1,trg)));
			}
			
		}
		else if(phase1=="pa")
		{
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				it->score=degree(it->src,trg)*degree(it->dest,trg);
			}
			
		}
				
			
	}
	
	sort(potential_edges.begin(),potential_edges.end(),predicate);
	
	//Adding Edges of Phase-1 to AUX
	
	Graph aux = trg;
	
	vector<EDGE>::iterator it = potential_edges.begin();
	
	int i=1;
	
	while(i<=int(lpf*lp))
	{
		
		add_edge(it->src,it->dest,aux);
		
		i++;
	}
	
	//Recomputing Predictions Using AUX
	
	threshold = calculate_threshold(aux);
	
	for(vector<EDGE>::iterator it=potential_edges.begin();it!=potential_edges.end();++it)
	{
		
		//if(!(degree(it->src,aux)>threshold&&degree(it->dest,aux)>threshold))
		{
			
			tie(e1,e2) = adjacent_vertices(it->src,aux);
			
			tie(e3,e4) = adjacent_vertices(it->dest,aux);
			
			vector<int> v1(e2-e1),v2(e4-e3);
			
			vector<int> common_set(MAX(degree(it->src,aux),degree(it->dest,aux)));
					
			vector<int>::iterator it1;
			
			copy(e1,e2,v1.begin());
			
			copy(e3,e4,v2.begin());
			
			//the adjacency list is not sorted::could give wrong results in case of set_intersection
			
			sort(v1.begin(),v1.end());
			
			sort(v2.begin(),v2.end());
			
			it1 = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),common_set.begin());
					
			common_set.resize(it1-common_set.begin());
			
			it->score = 0;

			if(phase2=="cn")
			{
				
				it->score=common_set.size();
				
			}
			else if(phase2=="aa")
			{
				for(it1=common_set.begin();it1!=common_set.end();++it1)
				{
					it->score+=(1.0/log10(degree(*it1,aux)));
				}
				
			}
			else if(phase2=="ra")
			{
				for(it1=common_set.begin();it1!=common_set.end();++it1)
				{
					it->score+=(1.0/(degree(*it1,aux)));
				}
				
			}
			else if(phase2=="pa")
			{
				for(it1=common_set.begin();it1!=common_set.end();++it1)
				{
					it->score=degree(it->src,aux)*degree(it->dest,aux);
				}
				
			}
					
			
		}
			
	}

	
	end = clock();
	
	compute_result(potential_edges,tg,lp,str,outfile);
	
	ofstream myfile;
	
	myfile.open(outfile,ios::app);
	
	myfile<<(end-start)/double(CLOCKS_PER_SEC)<<endl;
	
	myfile.close();
	
	return;
	
} 
