OBJS = lp.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)


#Linking Command
run : $(OBJS)
		@$(CC) $(LFLAGS) $(OBJS) -o run


#Compilation Command
lp.o: ./src/graph.h ./src/cn.h ./src/cngf.h ./src/aa.h ./src/ra.h ./src/pa.h ./src/rwr.h ./src/katz.h ./src/propflow.h ./src/result.h ./src/thresholding.h ./src/la.h ./src/two_phase.h
		@$(CC) $(CFLAGS) -std=c++0x -I ../ ./src/lp.cpp

clean:
		@rm *.o ./run *.txt
