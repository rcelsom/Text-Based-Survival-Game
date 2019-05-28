####################################################################
#Program Name:Makefile
#Author: Robert Elsom
#Date: 3/6/2019
#Description: Makefile for Final Project
####################################################################

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall			#turns on all warnings
CXXFLAGS += -pedantic-errors		#strictly enforce standard and generate errors if violated
CXXFLAGS += -g         			#debugging information
#CXXFLAGS += -03			#OPTIMIZATION MODE, LEAVE OFF	
LDFLAGS = -lboost_date_time


EXECUTABLE_NAME = final

OBJS = Space.o Tree.o Grass.o Cabin.o Creek.o main.o Game.o Board.o validInt.o validStr.o

SRCS = Space.cpp Tree.cpp  Grass.cpp  Cabin.cpp  Creek.cpp main.cpp Game.cpp Board.cpp validInt.cpp validStr.cpp

HEADERS = Space.hpp Tree.hpp  Grass.hpp  Cabin.hpp  Creek.hpp  Game.hpp Board.hpp validInt.hpp validStr.hpp




$(EXECUTABLE_NAME): ${OBJS} ${HEADERS} 
	${CXX} ${CXXFLAGS} ${OBJS} -o $(EXECUTABLE_NAME)


#takes any cpp file and build a .o file , @: is wildcard for every file name
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

#Clean
clean: 
	rm $(OBJS) $(EXECUTABLE_NAME)



#would have to input every dependecy like this of not using code above
#main.o: main.cpp
#	$(CXX) -c main.cpp

#determinate.o: determinate.cpp determinate.hpp
#	$(CXX) -c determinate.cpp



