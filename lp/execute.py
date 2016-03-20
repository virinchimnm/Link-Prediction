import os
import sys
import subprocess
import random as rn

def main():

	if len(sys.argv)!=6:

	  print "Usage ./run <path to input graph> <frac-of-edges to construct> <frac of edges to predict> <neighborhood-degree> <no-of-iter>"

	  sys.exit(0)

	file_name = sys.argv[1].split(".")[-2].split("\\")[-1].split('/')[-1]+"_"+sys.argv[2]+"_"+sys.argv[3]+"_"+sys.argv[4]+"_"+sys.argv[5]

	if os.path.isfile('./results/'+file_name+'.txt'):

		os.remove('./results/'+file_name+'.txt')

	os.system('make')

	os.system('./run -g '+sys.argv[1]+' -s '+sys.argv[2]+' -l '+sys.argv[3]+' -n '+sys.argv[4]+' -i '+sys.argv[5]+' -o '+'./results/'+file_name+'.txt')

	os.system('Rscript ./src/plot.R '+file_name+' '+sys.argv[5])

	os.system('make clean')

	return

if __name__=="__main__":

	main()
