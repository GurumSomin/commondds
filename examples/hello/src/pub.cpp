#include <iostream>
#include <dds/dcps.h>

#include <ctime>

#include <hello/Message.h>

int main(int argc, char** argv) {
	int error_code = 0;

	dds::DomainParticipant* participant = NULL;
	dds::Publisher* publisher = NULL;
	dds::Topic* topic = NULL;
	hello::MessageDataWriter* writer = NULL;
	dds::ReturnCode_t ret = 0;

	// 1. Create DomainParticipant
	participant = dds::DomainParticipantFactory::get_instance()
		->create_participant(0,	/* domain_id:DomainId_t */
							dds::PARTICIPANT_QOS_DEFAULT, /* qos:DomainParticipantQos* */
							NULL, /* a_listener:DomainParticipantListener* */
							0); /* mask:StatusMask */

	if(participant == NULL) {
		std::cerr << "Cannot create domain participant." << std::endl;
		error_code = 1;
		goto error;
	}

	// 2. Create Publisher
	publisher = participant->create_publisher(
		dds::PUBLISHER_QOS_DEFAULT, /* qos:PublisherQos* */
		NULL, /* a_listener:PublisherListener* */
		0); /* mask:StatusMask */

	if(publisher == NULL) {
		std::cerr << "Cannot create publisher." << std::endl;
		error_code = 2;
		goto error;
	}

	// 3. Register type to the DomainParticipant
	ret = hello::MessageTypeSupport::register_type(
		participant, /* domain:dds::DomainParticipant* */
		hello::MessageTypeSupport::get_type_name()); /* type_name:char* */

	if(ret != dds::RETCODE_OK) {
		std::cerr << "Cannot register type to participant: " << 
			hello::MessageTypeSupport::get_type_name() << std::endl;
		error_code = 3;
		goto error;
	}

	// 4. Create Topic
	topic = participant->create_topic(
		"Hello CommonDDS", /* topic_name:char* */
		hello::MessageTypeSupport::get_type_name(), /* type_name:char* */
		dds::TOPIC_QOS_DEFAULT, /* qos: TopicQos* */
		NULL, /* a_listener:TopicListener* */
		0); /* mask:StatusMask */

	if(topic == NULL) {
		std::cerr << "Cannot create topic." << std::endl;
		error_code = 4;
		goto error;
	}

	// 5. Create DataWriter
	writer = (hello::MessageDataWriter*)publisher->create_datawriter(
			topic, /* a_topic:Topic* */
			dds::DATAWRITER_QOS_DEFAULT, /* qos:DataWriterQos* qos */
			NULL, /* a_listener:DataWriterListener* */
			0); /* mask:StatusMask */

	if(writer == NULL) {
		std::cerr << "Cannot create data writer." << std::endl;
		error_code = 5;
		goto error;
	}

	// 6. Allocate Data
	hello::Message msg;
	msg.seq = 1;
	msg.time = (unsigned long long)std::time(NULL);
	msg.message = (char*)"Hello, CommonDDS!";

	// 7. Write the Data
	ret = writer->write(
		&msg, /* instance_data:Data* */
		dds::HANDLE_NIL); /* handle:InstanceHandle_t */

	if(ret != dds::RETCODE_OK) {
		std::cerr << "Cannot write message." << std::endl;
		error_code = 6;
		goto error;
	}

error:

	// Clean up
	if(participant != NULL) {
		participant->delete_contained_entities();
		dds::DomainParticipantFactory::get_instance()->delete_participant(participant);
	}

	return error_code;
}
