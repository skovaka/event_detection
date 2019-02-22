LIBS=-lz -lm -lstdc++ -ldl -lhdf5
#HDF5_LIB=-L/home-4/skovaka1@jhu.edu/software/lib /home-4/skovaka1@jhu.edu/software/lib/libhdf5.a
#BWA_LIB=-L/home-4/skovaka1@jhu.edu/code/nanopore_aligner/bwa /home-4/skovaka1@jhu.edu/code/nanopore_aligner/bwa/libbwa.a
#HDF5_INCLUDE=-I/home-4/skovaka1@jhu.edu/software/include
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
