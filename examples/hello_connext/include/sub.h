#ifndef __HELLO_SUBSCRIBER_H_INCLUDED__
#define __HELLO_SUBSCRIBER_H_INCLUDED__


#include "ndds/ndds_cpp.h"

extern bool startSubscriber(DDSDomainParticipant *participant,
					   DDSTopic *topic,
					   DDS_Long verbose,
					   DDS_Long sampleCount);


#endif
