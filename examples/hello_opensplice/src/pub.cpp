#include <string>
#include <sstream>
#include <iostream>
#include "ccpp_dds_dcps.h"
#include "CheckStatus.h"
#include "ccpp_HelloWorld.h"
#include "os.h"

#include "example_main.h"

using namespace DDS;
using namespace HelloWorldData;

extern "C"
{
	OS_API_EXPORT
	int HelloWorldDataPublisher(int argc, char *argv[]);
}

int HelloWorldDataPublisher(int argc, char *argv[])
{
	os_time delay_1s = { 1, 0 };
	DomainParticipantFactory_var dpf;
	DomainParticipant_var participant;
	Topic_var topic;
	Publisher_var publisher;
	DataWriter_var writer;

	TopicQos reliable_topic_qos;
	PublisherQos pub_qos;
	DataWriterQos dw_qos;

	DomainId_t domain;
	ReturnCode_t status;

	DDS::String_var partition = "HelloWorld example";
	DDS::String_var typeName;
	bool autodispose_unregistered_instances = false;
	char topicName[] = "HelloWorldData_Msg";

	// 1. Create DomainParticipant
	domain = DOMAIN_ID_DEFAULT;
	dpf = DomainParticipantFactory::get_instance();
	checkHandle(dpf.in(), "DDS::DomainParticipantFactory::get_instance");
	participant = dpf->create_participant(
			domain,
			PARTICIPANT_QOS_DEFAULT,
			NULL,
			STATUS_MASK_NONE);
	checkHandle(participant.in(),
		"DDS::DomainParticipantFactory::create_participant");

	// 2. Create Publisher
	status = participant->get_default_publisher_qos(pub_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_publisher_qos");
	pub_qos.partition.name.length(1);
	pub_qos.partition.name[0] = partition;

	publisher = participant->create_publisher(
			pub_qos,
			NULL,
			STATUS_MASK_NONE);
	checkHandle(publisher.in(), "DDS::DomainParticipant::create_publisher");

	// 3. Register type
	MsgTypeSupport_var ts = new MsgTypeSupport();
	typeName = ts->get_type_name();
	status = ts->register_type(participant.in(), typeName);
	checkStatus(status, "register_type");

	// 4. Create Topic
	status = participant->get_default_topic_qos(reliable_topic_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_topic_qos");
	reliable_topic_qos.reliability.kind = RELIABLE_RELIABILITY_QOS;
	reliable_topic_qos.durability.kind = TRANSIENT_DURABILITY_QOS;

	/* Make the tailored QoS the new default. */
	status = participant->set_default_topic_qos(reliable_topic_qos);
	checkStatus(status, "DDS::DomainParticipant::set_default_topic_qos");

	/* Use the changed policy when defining the HelloWorld topic */
	topic = participant->create_topic(
			topicName,
			typeName,
			reliable_topic_qos,
			NULL,
			STATUS_MASK_NONE);
	checkHandle(topic.in(), "DDS::DomainParticipant::create_topic ()");

	// 5. Create DataWriter
	status = publisher->get_default_datawriter_qos(dw_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_publisher_qos");
	status = publisher->copy_from_topic_qos(dw_qos, reliable_topic_qos);
	checkStatus(status, "DDS::Publisher::copy_from_topic_qos");
	dw_qos.writer_data_lifecycle.autodispose_unregistered_instances = autodispose_unregistered_instances;
	writer = publisher->create_datawriter(
			topic.in(),
			dw_qos,
			NULL,
			STATUS_MASK_NONE);
	checkHandle(writer, "DDS::Publisher::create_datawriter");

	// 6. Casting Writer
	MsgDataWriter_var HelloWorldWriter = MsgDataWriter::_narrow(writer);

	// 7. Allocate Data
	Msg msgInstance;
	msgInstance.userID = 1;
	msgInstance.message = DDS::string_dup("Hello World");
	cout << "=== [Publisher] writing a message containing :" << endl;
	cout << "		userID	: " << msgInstance.userID << endl;
	cout << "		Message : \"" << msgInstance.message << "\"" << endl;

	// 8. Write Data
	status = HelloWorldWriter->write(msgInstance, DDS::HANDLE_NIL);
	checkStatus(status, "MsgDataWriter::write");
	os_nanoSleep(delay_1s);

	// 9. Clean up
	status = participant->delete_contained_entities();
	checkStatus(status, "DDS::DomainParticipant::delete_contained_entities ");
	status = dpf->delete_participant(participant.in());
	checkStatus(status, "DDS::DomainParticipant::delete_participant ");

	return 0;
}

int OSPL_MAIN (int argc, char *argv[])
{
	return HelloWorldDataPublisher (argc, argv);
}
