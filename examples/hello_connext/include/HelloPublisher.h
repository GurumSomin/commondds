#ifndef __HELLO_PUBLISHER_H_INCLUDED__
#define __HELLO_PUBLISHER_H_INCLUDED__


#include "ndds/ndds_cpp.h"

extern bool startPublisher(DDSDomainParticipant *participant,
						DDSTopic *topic,
						DDS_Long verbose,
						DDS_Long dataSize,
						DDS_Long sampleCount);

#endif
