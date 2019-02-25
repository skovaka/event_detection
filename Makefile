LIBS=-lz -lm -lstdc++ -ldl -lhdf5
CC=g++
CFLAGS=-Wall -std=c++11 -O3
INCLUDE=-I./fast5/include #${BOOST_INCLUDE}

all: detect_events

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE) $(HDF5_INCLUDE) 

detect_events: detect_events.o event_detector.o
	$(CC) $(CFLAGS) detect_events.o event_detector.o -o detect_events $(HDF5_LIB) $(LIBS) $(INCLUDE)

clean:
	rm *.o
