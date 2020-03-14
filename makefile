CC=g++
STD=-std=c++14
TARGET=rangeManager
MODULES=Range.cpp RangeManager.cpp Util.cpp main.cpp

test:
	$(CC) $(STD) -DTEST_BUILD -o $(TARGET) $(MODULES)

build:
	$(CC) $(STD) -o $(TARGET) $(MODULES)

clean:
	rm -f *.o $(TARGET)
