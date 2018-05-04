objects = HearthStoneAI.o PowerParser.o LogReader.o Table.o
header = PowerParser.h LogReader.h Table.h

HearthStoneAI.exe: $(objects)
	g++ -o HearthStoneAI.exe $(objects)

HearthStoneAI.o: HearthStoneAI.cpp $(header)
	g++ -c HearthStoneAI.cpp

Table.o: Table.cpp Table.h
	g++ -c Table.cpp -std=c++11

PowerParser.o: PowerParser.cpp PowerParser.h
	g++ -c PowerParser.cpp -std=c++11

LogReader.o: LogReader.cpp LogReader.h PowerParser.h
	g++ -c LogReader.cpp -std=c++11

clean:
	rm HearthStoneAI.exe $(objects)