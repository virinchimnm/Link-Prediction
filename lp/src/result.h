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

void compute_result(vector<EDGE> score_list, Graph tg, int lp, string str, const char* outfile)
{
	
	//Calculating Precision
	int i=1,c=0;
	
	vector<EDGE>::iterator it = score_list.begin();

	Edge e;
		
	bool val;
	
	vector<float> positive_edges,negative_edges;
	
	vector<int> labels;
	
	while(i<=lp)
	{
		
		tie(e,val)=edge(it->src,it->dest,tg);
		
		if(val)
		{
			c++;
			positive_edges.push_back(it->score);
			labels.push_back(1);
		}
		else 
		{
			negative_edges.push_back(it->score);
			labels.push_back(0);
		}
		i++;
		it++;
	}
	
	ofstream myfile1;
	
	myfile1.open (outfile,ios::app);
	
	myfile1<<str<<","<<float(c*100.0/lp)<<",";
	
	vector<int> tp,fp,fn,tn;
	
	tp.push_back(c);
	
	fp.push_back(lp-c);
	
	tn.push_back(0);
	
	fn.push_back(0);
	
	
	
	//Calculating AUC
	
	c = 0;
	i=1;
	
	srand(time(NULL));
	
	int iter = 10000;
	
	int pos = positive_edges.size();
	
	int neg = negative_edges.size();
	
	while(i<=iter)
	{
		
		int pos_index = rand()%pos;
		
		int neg_index = rand()%neg;		
		
		
		if(positive_edges[pos_index]>negative_edges[neg_index])
		{
			c++;
		}	
		else if(positive_edges[pos_index]==negative_edges[neg_index])
		{
			c=c+0.5;
		}
		
		i++;
	}
	
	myfile1<<float(c*100.0/iter)<<",";
	
	myfile1.close();
	
	//ROC curve plotting
	
	int tp_c, fp_c, tn_c, fn_c;
	
	tp_c = tp[0];
	
	fp_c = fp[0];
	
	tn_c = tn[0];
	
	fn_c = fn[0];
	
	for( i = labels.size()-2;i > -1; i--)
	{
		if(labels[i+1]==1)
		{
			tp_c--;
			fn_c++;
		}
		else if(labels[i+1]==0)
		{
			fp_c--;
			tn_c++;
		}
		
		tp.push_back(tp_c);
		fp.push_back(fp_c);
		tn.push_back(tn_c);
		fn.push_back(fn_c);
	}
	
	ofstream myfile;
	
	string file_name = str+".txt";
	
	myfile.open (file_name.c_str(),ios::app);
	
	for(i=0;i<lp;i++)
	{
		
		myfile<<tp[i]<<","<<fp[i]<<","<<tn[i]<<","<<fn[i]<<"\n";
		
	}
	
	myfile.close();
	
	return;

}
