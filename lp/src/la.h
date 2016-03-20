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


void la(Graph trg, Graph tg, int lp, vector<EDGE>& potential_edges, int depth, double alpha_g, const char* outfile,string str)
{
	
	clock_t start,end;
	
	start = clock();
	
	AdjacencyIterator e1,e2,e3,e4;
	
	for(vector<EDGE>::iterator it=potential_edges.begin();it!=potential_edges.end();++it)
	{

		std::unordered_map<long long int,bool> map1,map2;

		vector<int> v1,v2;


		//calculating the reachable nodes till depth levels 

		for(int i=0;i<depth;++i)
		{

			tie(e1,e2) = adjacent_vertices(it->src,trg);

			for(;e1!=e2;++e1)
			{

				if(map1.find(*e1)==map1.end())
				{

					map1[*e1]=true;

					v1.push_back(*e1);
				}

			}

			tie(e1,e2) = adjacent_vertices(it->dest,trg);

			for(;e1!=e2;++e1)
			{

				if(map2.find(*e1)==map2.end())
				{

					map2[*e1]=true;

					v2.push_back(*e1);

				}

			}

		}



		
		
		
		vector<int> common_set(MAX(v1.size(),v2.size()));
				
		vector<int>::iterator it1;
		
		
		//the adjacency list is not sorted::could give wrong results in case of set_intersection
		
		sort(v1.begin(),v1.end());
		
		sort(v2.begin(),v2.end());
		
		it1 = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),common_set.begin());
				
		common_set.resize(it1-common_set.begin());
		
		it->score = 0;
		
		double alpha_l = 0.0;
		
		if(str=="LA_MLE")
		{
			double kval=0;
			double sum=0;
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				if(degree(*it1,trg)>0)
				{
					kval++;
					sum+=(log(degree(*it1,trg)));
				}
			}
			alpha_l=1.0+(kval/sum);
		}
	
		else if(str=="LA_PL")
		{
			double alpha1=2.0;
			double kval=0;
			double sum=0;
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				if(degree(*it1,trg)>0)
				{
					kval++;
					sum+=(log(degree(*it1,trg)));
				}
			}
			
			double z1 = (kval+sum-alpha1);
			
			
			
			alpha_l=(z1+sqrt(z1*z1+4*alpha1*sum))/(2.0*sum);
			
		}

		else if(str=="LA_E")
		{
			double alpha1=2.0;
			double kval=0;
			double sum=0;
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				if(degree(*it1,trg)>0)
				{
					kval++;
					sum+=(log(degree(*it1,trg)));
				}
			}
			alpha_l=1.0+(kval/(sum+alpha1));
		}

		else if(str=="LA_N")
		{
			double alpha1=2.0;
			double sigma1=1.0;
			double kval=0;
			double sum=0;
			for(it1=common_set.begin();it1!=common_set.end();++it1)
			{
				if(degree(*it1,trg)>0)
				{
					kval++;
					sum+=(log(degree(*it1,trg)));
				}
			}
			
			double k3 = sigma1*sigma1*sum;
			
			double z3 = k3-1-alpha1;
				
			alpha_l = (-z3+sqrt(z3*z3-4*(alpha1-k3-kval*sigma1*sigma1)))/2.0;
						
		}


		//cout<<2*alpha_l<<" "<<alpha_g<<endl;

		for(it1=common_set.begin();it1!=common_set.end();++it1)
		{
			
			it->score+=(1.0/pow(degree(*it1,trg),alpha_l/alpha_g));
			
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
