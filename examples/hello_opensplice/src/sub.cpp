#include <string>
#include <sstream>
#include <iostream>
#include "ccpp_dds_dcps.h"
#include "CheckStatus.h"
#include "ccpp_Hello.h"
#include "os.h"
#include "orb_abstraction.h"

#include "example_main.h"

using namespace DDS;
using namespace HelloWorldData;

bool DDS_SHUTDOWN_FLAG = false;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
	OS_API_EXPORT
	int HelloWorldDataSubscriber(int argc, char *argv[]);
}

class HelloListener: public DataReaderListener {
	private:

	public:
		HelloListener(){}

	public:
		void on_requested_deadline_missed (DataReader_ptr reader, const RequestedDeadlineMissedStatus& status){}
		void on_requested_incompatible_qos (DataReader_ptr reader, const RequestedIncompatibleQosStatus& status){}
		void on_sample_rejected (DataReader_ptr reader, const SampleRejectedStatus& status){}
		void on_liveliness_changed (DataReader_ptr reader, const LivelinessChangedStatus& status){}
		void on_subscription_matched (DataReader_ptr reader, const SubscriptionMatchedStatus& status){}
		void on_sample_lost(DataReader_ptr, const SampleLostStatus&){}

		void on_data_available(DataReader_ptr reader) {
			MsgSeq msgList;
			ReturnCode_t status;
			SampleInfoSeq infoSeq;

			// 6. Casting Reader
			MsgDataReader_var HelloWorldReader = MsgDataReader::_narrow(reader);
			checkHandle(HelloWorldReader.in(), "MsgDataReader::_narrow");

			// 7. Take Data
			status = HelloWorldReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
				ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
			checkStatus(status, "msgDataReader::take");
			for (DDS::ULong j = 0; j < msgList.length(); j++)
				{
					cout << "=== [Subscriber] message received :" << endl;
					cout << "		userID	: " << msgList[j].userID << endl;
					cout << "		Message : \"" << msgList[j].message << "\"" << endl;
				}

			// 8. Deallocate Data
				status = HelloWorldReader->return_loan(msgList, infoSeq);
				checkStatus(status, "MsgDataReader::return_loan");
				DDS_SHUTDOWN_FLAG = true;
			}
};

int HelloWorldDataSubscriber(int argc, char *argv[])
{
	os_time delay_2ms = { 0, 2000000 };
	os_time delay_200ms = { 0, 200000000 };
	DomainParticipantFactory_var dpf;
	DomainParticipant_var participant;
	Topic_var topic;
	Publisher_var publisher;
	Subscriber_var subscriber;
	DataWriter_var writer;
	DataReader_var reader;

	TopicQos reliable_topic_qos;
	SubscriberQos sub_qos;

	HelloListener listener;
	DomainId_t domain;
	ReturnCode_t status;

	DDS::String_var partition = "HelloWorld example";
	char topicName[] = "HelloWorldData_Msg";
	DDS::String_var typeName;
	MsgSeq msgList;
	SampleInfoSeq infoSeq;


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

	// 2. Create Subscriber
	status = participant->get_default_subscriber_qos(sub_qos);
	checkStatus(status, "DDS::DomainParticipant::get_default_subscriber_qos");
	sub_qos.partition.name.length(1);
	sub_qos.partition.name[0] = partition;
	subscriber = participant->create_subscriber(
			sub_qos,
			NULL,
			STATUS_MASK_NONE);

	// 3. Register type to the DomainParticipant
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
	checkHandle(topic.in(), "DDS::DomainParticipant::create_topic");

	// 5. Create Reader
	reader = subscriber->create_datareader(
			topic.in(),
			DATAREADER_QOS_USE_TOPIC_QOS,
			&listener,
			DATA_AVAILABLE_STATUS);
	checkHandle(reader, "DDS::Subscriber::create_datareader");

	cout << "=== [Subscriber] Ready ..." << endl;

	//  polling for take...
	status = -1;
	for (;;)
	{
		os_nanoSleep(delay_200ms);
		if(DDS_SHUTDOWN_FLAG) {
			break;
		}
	}

	os_nanoSleep(delay_2ms);

	// 9. cleanup
	status = participant->delete_contained_entities();
	checkStatus(status, "DDS::DomainParticipant::delete_contained_entities ");
	status = dpf->delete_participant(participant.in());
	checkStatus(status, "DDS::DomainParticipant::delete_participant ");

	return 0;
}

int OSPL_MAIN (int argc, char *argv[])
{
	return HelloWorldDataSubscriber (argc, argv);
}
