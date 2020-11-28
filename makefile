OBJS	= main.o IQueue.o memory.o pipeline.o ReorderBuffer.o Statistics.o TFO_qu.o instruction.o ALU.o
SOURCE	= main.cpp IQueue.cpp memory.cpp pipeline.cpp ReorderBuffer.cpp statistics.cpp TFO_qu.cpp instruction.cpp ALU.cpp
HEADER  = IQueue.h memory.h pipeline.h ReorderBuffer.h TFO_qu.h instruction.h ALU.h
OUT	    = tool
CC	    = g++
FLAGS	= -g -c 
LFLAGS  = -lstdc++

all: $(OBJS)
		$(CC) -o $(OUT) $(OBJS)

main.o: main.cpp
		$(CC) $(FLAGS) main.cpp
IQueue.o: IQueue.cpp
		$(CC) $(FLAGS) IQueue.cpp
memory.o: memory.cpp
		$(CC) $(FLAGS) memory.cpp
pipeline.o: pipeline.cpp
		$(CC) $(FLAGS) pipeline.cpp
ReorderBuffer.o: ReorderBuffer.cpp
		$(CC) $(FLAGS) ReorderBuffer.cpp
statistics.o: statistics.cpp
		$(CC) $(FLAGS) statistics.cpp
TFO_qu.o: TFO_qu.cpp
		$(CC) $(FLAGS) TFO_qu.cpp
instruction.o: instruction.cpp
		$(CC) $(FLAGS) instruction.cpp
ALU.o: ALU.cpp
		$(CC) $(FLAGS) ALU.cpp

clean:
		rm -f $(OBJS) $(OUT)