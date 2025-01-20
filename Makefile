CXX = g++
CXXFLAGS = -std=c++14 -Wall -w -MMD -g
EXEC = monopoly
OBJECTS = academicbuildings.o board.o boardDisplay.o buildings.o game.o gyms.o main.o nonproperty.o observer.o player.o residences.o squares.o subject.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
