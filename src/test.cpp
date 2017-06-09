#include <stdio.h>

#include <iostream>
#include <stdexcept>

#include <dds/dcps.h>

int main(int argc, char** argv) {
	try {
		dds::DomainParticipantFactory* factory = dds::DomainParticipantFactory::get_instance();
		dds::DomainParticipant* participant = factory->create_participant(0, dds::PARTICIPANT_QOS_DEFAULT, NULL, 0);
		std::cout << factory << std::endl;
	} catch(const std::runtime_error& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	} catch(const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	} catch(...) {
		std::cout << "Some exception occurred" << std::endl;
	}

	return 0;
}
