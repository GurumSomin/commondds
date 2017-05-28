#include <iostream>
#include <dds/dcps.h>

#include <ctime>

#include <hello/Message.h>

int main(int argc, char** argv) {
	dds::DomainParticipant* participant = dds::DomainParticipantFactory::get_instance()
		->create_participant(0,	/* domain_id:DomainId_t */
							dds::PARTICIPANT_QOS_DEFAULT, /* qos:DomainParticipantQos* */
							NULL, /* a_listener:DomainParticipantListener* */
							0); /* mask:StatusMask */

	if(participant == NULL) {
		std::cerr << "Cannot create domain participant." << std::endl;
		return 1;
	}

	hello::MessageTypeSupport messageTypeSupport;

	dds::Topic* topic = participant->create_topic(
		"Message", /* topic_name:std::string* */
		messageTypeSupport.get_type_name(), /* type_name:std::string* */
		dds::TOPIC_QOS_DEFAULT, /* qos: TopicQos* */
		NULL, /* a_listener:TopicListener* */
		0); /* mask:StatusMask */

	if(topic == NULL) {
		std::cerr << "Cannot create topic." << std::endl;
		return 2;
	}

	dds::Publisher* publisher = participant->create_publisher(
		dds::PUBLISHER_QOS_DEFAULT, /* qos:PublisherQos* */
		NULL, /* a_listener:PublisherListener* */
		0); /* mask:StatusMask */

	if(publisher == NULL) {
		std::cerr << "Cannot create publisher." << std::endl;
		return 3;
	}

	hello::MessageDataWriter* writer = (hello::MessageDataWriter*)publisher->create_datawriter(
			topic, /* a_topic:Topic* */
			dds::DATAWRITER_QOS_DEFAULT, /* qos:DataWriterQos* qos */
			NULL, /* a_listener:DataWriterListener* */
			0); /* mask:StatusMask */

	if(writer == NULL) {
		std::cerr << "Cannot create data writer." << std::endl;
		return 4;
	}

	hello::Message msg;
	msg.seq = 1;
	msg.time = (unsigned long long)std::time(NULL);
	msg.message = (char*)"Hello, CommonDDS!";

	dds::ReturnCode_t ret = writer->write(
		&msg, /* instance_data:Data* */
		dds::HANDLE_NIL); /* handle:InstanceHandle_t */

	if(ret != dds::RETCODE_OK) {
		std::cerr << "Cannot write message." << std::endl;
		return 5;
	}

	// Clean up
	if(participant != NULL) {
		participant->delete_contained_entities();
		dds::DomainParticipantFactory::get_instance()->delete_participant(participant);
	}
	return 0;
}
