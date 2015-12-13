#include "FMultiQueue.hh"
#include <iostream>
#include <string>

#define MAX_PRIORITY 10

typedef void(* consumer_function)(unsigned);

#define CONSUMER_NUMBER 100


int main(int argc, char** argv) {
	FMultiQueue<std::string, 10, MAX_PRIORITY> fq;

	// producer from now on
	std::cout << ("I am the producer now.\n");
	
	unsigned it = 9;
	while(1) {
		usleep(20003);

		std::string msg = "foo " + std::to_string(it);

		std::cout << "sending " << msg << std::endl;

		fq.send(std::move(msg), it++% MAX_PRIORITY);
		//QPrintQueue();
	}
}
