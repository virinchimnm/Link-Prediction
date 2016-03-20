import os
import sys
import subprocess
import random as rn

def main():

	if len(sys.argv)!=2:

	  print "Usage run.exe <path to result file>"

	  sys.exit(0)

	file_name = sys.argv[1]

	f = open(file_name)

	data = f.readlines()

	auc = {}

	time = {}

	for line in data:

		auc[line.split(',')[0]] = []

		time[line.split(',')[0]] = []


	for line in data:

		auc[line.split(',')[0]].append(float(line.split(',')[-2]))


		time[line.split(',')[0]].append(float(line.split(',')[-1].split('\n')[0]))


	for key in auc.keys():

		auc[key] = sum(auc[key])/len(auc[key])

	for key in time.keys():

		time[key] = sum(time[key])/len(time[key])


	print "PA",":",auc["PA"]

	print "CN",":",auc["CN"]

	print "AA",":",auc["AA"]

	print "RA",":",auc["RA"]

	print "PA_PA",":",auc["pa+pa0.5"]

	print "PA_CN",":",auc["pa+cn0.5"]

	print "PA_AA",":",auc["pa+aa0.5"]

	print "PA_RA",":",auc["pa+ra0.5"]


	print "CN_PA",":",auc["cn+pa0.5"]

	print "CN_CN",":",auc["cn+cn0.5"]

	print "CN_AA",":",auc["cn+aa0.5"]

	print "CN_RA",":",auc["cn+ra0.5"]


	print "AA_PA",":",auc["aa+pa0.5"]

	print "AA_CN",":",auc["aa+cn0.5"]

	print "AA_AA",":",auc["aa+aa0.5"]

	print "AA_RA",":",auc["aa+ra0.5"]


	print "RA_PA",":",auc["ra+pa0.5"]

	print "RA_CN",":",auc["ra+cn0.5"]

	print "RA_AA",":",auc["ra+aa0.5"]

	print "RA_RA",":",auc["ra+ra0.5"]

	return

if __name__=="__main__":

	main()
