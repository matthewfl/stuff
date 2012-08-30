CXXFLAGS= -O0 -ggdb -Wall -fmessage-length=0

SRCS= main.cc

TARGET= test

LIBS= -lAsmJit

OBJS= $(patsubst %.cc, %.o, $(SRCS))

CC=g++
LD=g++

.cc.o: $*.cc
	$(CC) $(CXXFLAGS) -c -o $@ $*.cc

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(TARGET)