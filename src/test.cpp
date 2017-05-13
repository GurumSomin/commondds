#include <iostream>
#include <stdio.h>

#include <dds/dcps.h>

int main(int argc, char** argv) {
	dds::sequence<int>* seq = new dds::sequence<int>(10);
	std::cout << seq << std::endl;
	
	return 0;
}
