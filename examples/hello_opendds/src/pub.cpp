#include <ace/Log_Msg.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include "dds/DCPS/StaticIncludes.h"
#include "HelloWorldTypeSupportImpl.h"

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
	try {
		// Initialize DomainParticipantFactory
		DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);

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

		// 2. Create Publisher
		DDS::Publisher_var publisher = participant->create_publisher(PUBLISHER_QOS_DEFAULT,
				0,
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		if (!publisher) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_publisher failed!\n")), -1);
		}

		// 3. Register type to the DomainParticipant
		HelloWorldData::MsgTypeSupport_var ts = new HelloWorldData::MsgTypeSupportImpl;

		if (ts->register_type(participant, "") != DDS::RETCODE_OK) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" register_type failed!\n")), -1);
		}

		// 4. Create Topic
		CORBA::String_var type_name = ts->get_type_name();
		DDS::Topic_var topic = participant->create_topic("HelloWorld example",
				type_name,
				TOPIC_QOS_DEFAULT,
				0,
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!topic) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_topic failed!\n")), -1);
		}

		// 5. Create Writer
		DDS::DataWriter_var writer = publisher->create_datawriter(topic,
				DATAWRITER_QOS_DEFAULT,
				0,
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		if (!writer) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" create_datawriter failed!\n")), -1);
		}

		// 6. Casting Writer
		HelloWorldData::MsgDataWriter_var message_writer = HelloWorldData::MsgDataWriter::_narrow(writer);
		if (!message_writer) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" _narrow failed!\n")), -1);
		}

		// Block until Subscriber is available (omitted)
		DDS::StatusCondition_var condition = writer->get_statuscondition();
		condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

		DDS::WaitSet_var ws = new DDS::WaitSet;
		ws->attach_condition(condition);

		while (true) {
			DDS::PublicationMatchedStatus matches;

			if (writer->get_publication_matched_status(matches) != ::DDS::RETCODE_OK) {
				ACE_ERROR_RETURN((LM_ERROR,
							ACE_TEXT("ERROR: %N:%l: main() -")
							ACE_TEXT(" get_publication_matched_status failed!\n")), -1);
			}

			if (matches.current_count >= 1) {
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

		for (int i = 0; i < 10; ++i) {
			// 6. Allocate Data
			HelloWorldData::Msg message;
			message.userId = i;
			message.message	= "Hello World";

			// 7. Write samples
			DDS::ReturnCode_t error = message_writer->write(message, DDS::HANDLE_NIL);
			if (error != DDS::RETCODE_OK) {
				ACE_ERROR((LM_ERROR,
							ACE_TEXT("ERROR: %N:%l: main() -")
							ACE_TEXT(" write returned %d!\n"), error));
			}
		}

		// Wait for samples to be acknowledged(omitted)
		DDS::Duration_t timeout = { 30, 0 };
		if (message_writer->wait_for_acknowledgments(timeout) != DDS::RETCODE_OK) {
			ACE_ERROR_RETURN((LM_ERROR,
						ACE_TEXT("ERROR: %N:%l: main() -")
						ACE_TEXT(" wait_for_acknowledgments failed!\n")), -1);
		}

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
