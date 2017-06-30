#include <ace/Log_Msg.h>
#include <ace/OS_NS_stdlib.h>
#include <ace/Global_Macros.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsSubscriptionC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>
#include "dds/DCPS/StaticIncludes.h"
#include <dds/DdsDcpsSubscriptionC.h>
#include <dds/DCPS/LocalObject.h>
#include <dds/DCPS/Definitions.h>

#include "HelloTypeSupportC.h"
#include "HelloTypeSupportImpl.h"

#include <iostream>

class HelloListener : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener> {
	public:
		void on_requested_deadline_missed(DDS::DataReader_ptr, const DDS::RequestedDeadlineMissedStatus&){}
		void on_requested_incompatible_qos(DDS::DataReader_ptr, const DDS::RequestedIncompatibleQosStatus&){}
		void on_sample_rejected(DDS::DataReader_ptr, const DDS::SampleRejectedStatus&){}
		void on_liveliness_changed(DDS::DataReader_ptr, const DDS::LivelinessChangedStatus&){}
		void on_subscription_matched(DDS::DataReader_ptr, const DDS::SubscriptionMatchedStatus&) {}
		void on_sample_lost(DDS::DataReader_ptr, const DDS::SampleLostStatus&){}

		void on_data_available(DDS::DataReader_ptr reader) {
			hello::MessageDataReader_var reader_i = hello::MessageDataReader::_narrow(reader);

			if (!reader_i) {
				ACE_ERROR((LM_ERROR,
							ACE_TEXT("ERROR: %N:%l: on_data_available() -")
							ACE_TEXT(" _narrow failed!\n")));
				ACE_OS::exit(-1);
			}

			hello::MessageSeq message;
			DDS::SampleInfoSeq info;

			// 7. Take Data
			DDS::ReturnCode_t error = reader_i->take(message, info,
					DDS::LENGTH_UNLIMITED,
					DDS::ANY_SAMPLE_STATE,
					DDS::ANY_VIEW_STATE,
					DDS::ANY_INSTANCE_STATE);

			if (error != DDS::RETCODE_OK) {
				ACE_ERROR((LM_ERROR,
							ACE_TEXT("ERROR: %N:%l: on_data_available() -")
							ACE_TEXT(" take failed!\n")));
				return;
			}
			for(CORBA::ULong i = 0; i < message.length(); i++) {
				if (info[i].valid_data) {
					std::cout << "=== [Subscriber] message received :" << std::endl;
					std::cout << "seq: " << message[i].seq			<< std::endl;
					std::cout << "time: " << message[i].time		<< std::endl;
					std::cout << "msg: " << message[i].msg		<< std::endl;
				}
			}

		}
};

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
	try {
		// Initialize DomainParticipantFactory(omitted)
		DDS::DomainParticipantFactory_var dpf =
			TheParticipantFactoryWithArgs(argc, argv);

		// 1. Create DomainParticipant
		DDS::DomainParticipant_var participant =
			dpf->create_participant(0,
					PARTICIPANT_QOS_DEFAULT,
					0,
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!participant) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_participant failed!\n")), -1);
		}

		// 2. Create Subscriber
		DDS::Subscriber_var subscriber =
			participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,
					0,
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!subscriber) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_subscriber failed!\n")), -1);
		}


		// 3. Register type to the DomainParticipant
		hello::MessageTypeSupport_var ts = new hello::MessageTypeSupportImpl;

		CORBA::String_var type_name = ts->get_type_name();
		if (ts->register_type(participant, type_name) != DDS::RETCODE_OK) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" register_type failed!\n")), -1);
		}

		// 4. Create Topic
		DDS::Topic_var topic =
			participant->create_topic("Hello CommonDDS",
					type_name,
					TOPIC_QOS_DEFAULT,
					0,
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!topic) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_topic failed!\n")), -1);
		}

		// 5. Create Reader
		DDS::DataReaderListener_var listener(new HelloListener());

		DDS::DataReader_var reader = subscriber->create_datareader(topic,
					DATAREADER_QOS_DEFAULT,
					listener,
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!reader) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_datareader failed!\n")), -1);
		}

		// 6. Casting Reader
		hello::MessageDataReader_var reader_i = hello::MessageDataReader::_narrow(reader);

		if (!reader_i) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" _narrow failed!\n")), -1);
		}

		// Block until Publisher completes(omitted)
		DDS::StatusCondition_var condition = reader->get_statuscondition();
		condition->set_enabled_statuses(DDS::SUBSCRIPTION_MATCHED_STATUS);

		DDS::WaitSet_var ws = new DDS::WaitSet;
		ws->attach_condition(condition);

		while (true) {
			DDS::SubscriptionMatchedStatus matches;
			if (reader->get_subscription_matched_status(matches) != DDS::RETCODE_OK) {
				ACE_ERROR_RETURN((LM_ERROR,
							ACE_TEXT("ERROR: %N:%l: main() -")
							ACE_TEXT(" get_subscription_matched_status failed!\n")), -1);
			}

			if (matches.current_count == 0 && matches.total_count > 0) {
				break;
			}

			DDS::ConditionSeq conditions;
			DDS::Duration_t timeout = { 60, 0 };
			if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
				ACE_ERROR_RETURN((LM_ERROR,
							ACE_TEXT("ERROR: %N:%l: main() -")
							ACE_TEXT(" wait failed!\n")), -1);
			}
		}

		ws->detach_condition(condition);

		// 8. Clean-up
		participant->delete_contained_entities();
		dpf->delete_participant(participant);

		TheServiceParticipant->shutdown();

	} catch (const CORBA::Exception& e) {
		e._tao_print_exception("Exception caught in main():");
		return -1;
	}

	return 0;
}
