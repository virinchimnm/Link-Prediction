# Link-Prediction

This package consists of link prediction codes in which run on MAC/UBUNTU platform. One can make necessary modifications for running the codes on Windows platform. You can download the lp folder to any location in your system. Please download Boost C++ library and unzip it in the same folder where lp folder is residing on your system. 


**The structure of this package is as follows:**

lp  
|--- execute.py : run this for executing the package <br />
| <br />
|--- calc_results.py : converting results stored in .txt files (in this folder) and storing it in results folder as .txt file <br />
| <br />
|--- datasets : the datasets reside in this folder. The format of the graph file is "node1 node2" (Handles any number of spaces) <br />
| <br />
|--- results : contains the results as .txt files <br />
| <br />
|--- plots : contains the result plots as .png files <br />
| <br />
|--- makefile : make file which is handled in execute.py <br />
| <br />
|--- src <br />
> |--- plot.R : handles plotting graphs using the files residing in results folder <br />
> |--- lp.cpp : main function of the link prediction cpp file <br />
> |--- graph.h : cpp  file handling basic graph operations <br />
> |--- result.h : cpp file handling computing the results and storing them as .txt files in lp folder <br />
> |---- cn.h, aa.h, ra.h, etc : basic link prediction algorihms. You can add your link prediction algortihms in this folder <br />



