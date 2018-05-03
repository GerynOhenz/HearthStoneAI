objects = HearthStoneAI.o PowerParser.o LogReader.o

HearthStoneAI.exe: $(objects)
	g++ -o HearthStoneAI.exe $(objects)

HearthStoneAI.o: HearthStoneAI.cpp PowerParser.h LogReader.h
	g++ -c HearthStoneAI.cpp

PowerParser.o: PowerParser.cpp PowerParser.h
	g++ -c PowerParser.cpp

LogReader.o: LogReader.cpp LogReader.h PowerParser.h
	g++ -c LogReader.cpp

clean:
	rm HearthStoneAI.exe $(objects)