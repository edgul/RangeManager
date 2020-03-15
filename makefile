CC=g++
STD=-std=c++17
TARGET=rangeManager
MODULES=Range.cpp RangeManager.cpp RangeManagerLinear.cpp Util.cpp main.cpp

test:
	$(CC) $(STD) -DTEST_BUILD -o $(TARGET) $(MODULES)

build:
	$(CC) $(STD) -o $(TARGET) $(MODULES)

clean:
	rm -f *.o $(TARGET)
