CC=g++

all: event_handler
	./$<

event_handler: event_handler.t.o
	$(CC) -o $@ $<

%.o: %.cpp
	$(CC) -c $< -std=c++11

clean:
	rm -f $< event_handler
	rm -f *.o
