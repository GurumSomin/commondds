#include <iostream>
#include <string>
#include <cstdlib>

#include "HelloPublisher.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"

int main(int argc, const char **argv) {
	const char* topicName = "Hello IDL";
    DDSDomainParticipant *participant = NULL;
    DDSTopic *topic = NULL;
    DDS_Long domainId = 0;
    DDSPublisher *publisher              = NULL;
    DDSDataWriter *dataWriter            = NULL;
    HelloWorldData_MsgDataWriter *helloWriter    = NULL;
    HelloWorldData_Msg *instance                 = NULL;
    bool returnValue                     = true;
    DDS_ReturnCode_t rc;
	const int SAMPLE_LENGTH = 10;
    DDS_Duration_t send_period = {0,4}; /* time (sec, usec) to pause between bursts of 10,000 samples */
    DDS_Duration_t disc_period = {1,0};

	participant = DDSDomainParticipantFactory::get_instance()->create_participant(
                        domainId,
                        DDS_PARTICIPANT_QOS_DEFAULT,
                        NULL,
                        DDS_STATUS_MASK_NONE);

    if(participant == NULL) {
        std::cerr << "! Unable to create DDS participant" << std::endl;
        goto exitFn;
    }

    publisher = participant->create_publisher(
                        DDS_PUBLISHER_QOS_DEFAULT,
                        NULL,
                        DDS_STATUS_MASK_NONE);

    rc = HelloWorldData_MsgTypeSupport::register_type(participant, HelloWorldData_MsgTypeSupport::get_type_name());

    if(rc != DDS_RETCODE_OK ) {
        std::cerr << "! Unable to register type" << std::endl;
        goto exitFn;
    }

    topic = participant->create_topic(
			topicName,
            HelloWorldData_MsgTypeSupport::get_type_name(),
            DDS_TOPIC_QOS_DEFAULT,
            NULL,
            DDS_STATUS_MASK_NONE);

    if(topic == NULL) {
        std::cerr << "! Unable to create DDS topic" << std::endl;
        goto exitFn;
    }

    dataWriter = publisher->create_datawriter(
                        topic,
                        DDS_DATAWRITER_QOS_DEFAULT,
                        NULL,
                        DDS_STATUS_MASK_NONE);

    if (dataWriter == NULL) {
        std::cerr << "! Unable to create DDS data writer" << std::endl;
        goto exitFn;
    }

	NDDSUtility::sleep(disc_period);

    helloWriter = HelloWorldData_MsgDataWriter::narrow(dataWriter);
    if (helloWriter == NULL) {
        goto exitFn;
    }

    instance = HelloWorldData_MsgTypeSupport::create_data_ex(DDS_BOOLEAN_FALSE);
    if (instance == NULL) {
        goto exitFn;
    }

    std::cout << "Sending data..." << std::endl;
	for(int i = 0; i < SAMPLE_LENGTH ; i++ ) {
		instance->userId = i;
		sprintf(instance->message, "Hello World");

		rc = helloWriter->write(*instance, DDS_HANDLE_NIL);
		std::cout << "id: "<< instance->userId << ", message: " << instance->message << std::endl;
	}
	std::cout << "done!" << std::endl;

    /* --- Clean Up ------------------------------------------------------- */ 
	if (rc != DDS_RETCODE_OK) {
		std::cerr << "! Write error " <<  rc << std::endl;
	}
	NDDSUtility::sleep(send_period);

	rc = participant->delete_contained_entities();
	if (rc != DDS_RETCODE_OK) {
		std::cerr << "Deletion failed." << std::endl;
		returnValue = false;
	}

	rc = DDSDomainParticipantFactory::get_instance()->delete_participant(participant);
	if (rc != DDS_RETCODE_OK) {
		std::cerr << "Deletion failed." << std::endl;
		returnValue = false;
	}

exitFn:
	if (instance != NULL) {
		HelloWorldData_MsgTypeSupport::delete_data_ex(
				instance,
                DDS_BOOLEAN_FALSE);
		instance = NULL;
    }

    return returnValue;
}

