#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "HelloSubscriber.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"

#define POLL_PERIOD_SEC         1

DDS_Boolean DDS_SHUTDOWN_FLAG = DDS_BOOLEAN_FALSE;

class HelloListener: public DDSDataReaderListener {
private:

public:
	HelloListener(){}

public:
    void on_data_available(DDSDataReader* reader) {
        HelloWorldData_MsgSeq dataSeq;
        DDS_SampleInfoSeq infoSeq;
        DDS_ReturnCode_t rc;

        HelloWorldData_MsgDataReader *helloReader = HelloWorldData_MsgDataReader::narrow(reader);
        if (helloReader == NULL) {
            std::cerr << "! Unable to narrow data reader" << std::endl;
            return;
        }

        rc = helloReader->take(
                            dataSeq,
                            infoSeq,
                            DDS_LENGTH_UNLIMITED,
                            DDS_ANY_SAMPLE_STATE,
                            DDS_ANY_VIEW_STATE,
                            DDS_ANY_INSTANCE_STATE);

        if (rc == DDS_RETCODE_NO_DATA) {
            return;
        } else if (rc != DDS_RETCODE_OK) {
            std::cerr << "! Unable to take data from data reader, error "
                      << rc << std::endl;
            return;
        }

        for (int i = 0; i < dataSeq.length(); ++i) {
            if (infoSeq[i].valid_data) {
				printf("id: %d, message: %s\n", dataSeq[i].userId, dataSeq[i].message);
			}
        }

        rc = helloReader->return_loan(dataSeq, infoSeq);
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! Unable to return loan, error "
                      << rc << std::endl;
        }

        DDS_SHUTDOWN_FLAG = DDS_BOOLEAN_TRUE;

    }
};

int main(int argc, const char **argv) {
	const char* topicName = "Hello IDL";
    DDSDomainParticipant *participant = NULL;
    DDSTopic *topic = NULL;
    DDS_Long domainId = 0;
    DDSSubscriber *subscriber = NULL;
    DDSDataReader *dataReader = NULL;
    DDS_Duration_t poll_period = {POLL_PERIOD_SEC, 0};
    HelloListener listener;
    DDS_Duration_t disc_period = {1, 0};
    DDS_ReturnCode_t rc;

    participant = DDSDomainParticipantFactory::get_instance()->create_participant(
          domainId,
          DDS_PARTICIPANT_QOS_DEFAULT,
          NULL,
          DDS_STATUS_MASK_NONE);

    if(participant == NULL) {
        std::cerr << "! Unable to create DDS participant" << std::endl;
       return false;
    }

    subscriber = participant->create_subscriber(
                        DDS_SUBSCRIBER_QOS_DEFAULT,
                        NULL,
                        DDS_STATUS_MASK_NONE);

    if (subscriber == NULL) {
        std::cerr << "! Unable to create DDS subscriber" << std::endl;
        return false;
    }
    rc = HelloWorldData_MsgTypeSupport::register_type(participant, HelloWorldData_MsgTypeSupport::get_type_name());

    if(rc != DDS_RETCODE_OK ) {
        std::cerr << "! Unable to register type" << std::endl;
        return false;
    }

    topic = participant->create_topic(
			topicName,
            HelloWorldData_MsgTypeSupport::get_type_name(),
            DDS_TOPIC_QOS_DEFAULT,
            NULL,
            DDS_STATUS_MASK_NONE);

    if(topic == NULL) {
        std::cerr << "! Unable to create DDS topic" << std::endl;
        return false;
    }

    dataReader = subscriber->create_datareader(
                        topic,
                        DDS_DATAREADER_QOS_DEFAULT,
                        &listener,
                        DDS_STATUS_MASK_ALL);

    if (dataReader == NULL) {
        std::cerr << "! Unable to create DDS data reader" << std::endl;
        return false;
    }

    NDDSUtility::sleep(disc_period);

	for(;;) {
		NDDS_Utility_sleep(&poll_period);
        if(DDS_SHUTDOWN_FLAG){
            break;
        }
    }

    /* --- Clean Up ------------------------------------------------------- */ 
    int main_result = 0;

    std::cout << "Exiting..." << std::endl;
    dataReader->set_listener(NULL);
    if (participant != NULL) {
         DDS_ReturnCode_t rc = participant->delete_contained_entities();
         if (rc != DDS_RETCODE_OK) {
            std::cerr << "Deletion failed." << std::endl;
            main_result = 1;
         }

         rc = DDSDomainParticipantFactory::get_instance()->
                         delete_participant(participant);
         if (rc != DDS_RETCODE_OK) {
             std::cerr << "Deletion failed." << std::endl;
             main_result = 1;
         }
   }

     return main_result;
}
