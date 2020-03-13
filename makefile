
build:
	g++ -std=c++14 -o a.exe Range.cpp RangeManager.cpp RangeManagerTest.cpp Util.cpp main.cpp

clean:
	rm -f *.o a.exe
