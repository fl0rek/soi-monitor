#include "FMultiQueue.hh"
#include <iostream>
#include <string>
#include <thread>
#include <functional>

#define MAX_PRIORITY 10

int main(int argc, char** argv) {
	FMultiQueue<std::string*, 10, MAX_PRIORITY> fq;

	// producer from now on
	std::cout << ("I am the producer now.\n");

	auto f = [&fq](unsigned myid) {
		printf("consumer %u\n", myid);
		while(1) {

			usleep(100000);
			std::cout << "PRE \n" << 
				fq.print_debug();
			std::string *msg = fq.recv();

			std::cout << "received " << myid << " : " << *msg << std::endl;
			std::cout << "POST \n" << 
				fq.print_debug();
			delete msg;
		}
	};

	std::thread t1(f, 1);
	t1.detach();
	std::thread t2(f, 2);
	t2.detach();
	std::thread t3(f, 3);
	t3.detach();

	unsigned it = 9;
	while(1) {
		usleep(20003);

		std::string msg = "foo " + std::to_string(it);
		std::string *m = new std::string(msg);

		std::cout << "sending " << msg << std::endl;

		fq.send(std::move(m), it++% MAX_PRIORITY);
		//fq.send(m, it++% MAX_PRIORITY);
		//QPrintQueue();
	}
}
