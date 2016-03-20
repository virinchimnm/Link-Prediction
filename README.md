# Link-Prediction

This package consists of link prediction codes in C++ which run on MAC/UBUNTU. One can make modifications for being able to run it on Windows. You can download the lp folder on to any location on your system. Please download Boost C++ library and unzip it into the same folder where lp folder is residing. 


The structure of the lp folder is as follows:

lp  
<ul>
<li>execute.py : run this for executing the package</li>
<li>results.py : converting results stored in .txt files (in this folder) and storing it in results folder as .txt file </li>
<li>datasets : the datasets reside in this folder. The format of the graph file is "node1 node2" (Handles any number of spaces) </li>
<li>results : contains the results as .txt files </li>
<li>plots : contains the result plots as .png files</li>
<li>makefile : make file which is handled in execute.py </li>
<li>src</li>
<ul>
<li>plot.R : handles plotting graphs using the files residing in results folder</li>
<li>lp.cpp : main function of the link prediction cpp file</li>
<li>graph.h : cpp  file handling basic graph operations</li>
<li>result.h : cpp file handling computing the results and storing them as .txt files in lp folder</li>
<li>cn.h, aa.h, ra.h, etc : basic link prediction algorihms. You can add your link prediction algortihms in this folder</li>
</ul>
</ul>



