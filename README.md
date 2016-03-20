# Link-Prediction

This package consists of link prediction codes in C++ which run on MAC/UBUNTU. One can make modifications for being able to run it on Windows. You can download the lp folder on to any location on your system. Please download Boost C++ library and unzip it into the same folder where lp folder is residing. 


The structure of the lp folder is as follows:

lp  
|---- execute.py : run this for executing the package
|
|---- results.py : converting results stored in .txt files (in this folder) and storing it in results folder as .txt file.
|
|---- datasets : the datasets reside in this folder. The format of the graph file is "node1 node2" (Handles any number of spaces).
| 
|---- results : contains the results as .txt files 
|
|---- plots : contains the result plots as .png files
|
|---- makefile : make file which is handled in execute.py
|
|---- src
      |---- plot.R : handles plotting graphs using the files residing in results folder.
      |
      |---- lp.cpp : main function of the link prediction cpp file
      |
      |---- graph.h : cpp  file handling basic graph operations
      |
      |---- result.h : cpp file handling computing the results and storing them as .txt files in lp folder.
      |
      |---- cn.h, aa.h, ra.h, etc : basic link prediction algorihms. You can add your link prediction algortihms in this folder.
