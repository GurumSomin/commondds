#ifndef __DDS_CONNEXT__
#define __DDS_CONNEXT__

#include <dds/dcps.h>

namespace dds {
	class ConnextDomainParticipantFactory : public DomainParticipantFactory {
	public:
		ConnextDomainParticipantFactory();
		virtual ~ConnextDomainParticipantFactory();
	
		virtual DomainParticipant* create_participant(
			DomainId_t domain_id,
			const DomainParticipantQos* qos,
			const DomainParticipantListener* a_listener,
			const StatusMask* mask);
		virtual ReturnCode_t delete_participant(
			const DomainParticipant* a_participant);
		virtual DomainParticipant* lookup_participant(
			DomainId_t domain_id);
		virtual ReturnCode_t set_default_participant_qos(
			const DomainParticipantQos* qos);
		virtual ReturnCode_t get_default_participant_qos(
			DomainParticipantQos* qos);
		virtual ReturnCode_t set_qos(
			const DomainParticipantFactoryQos* qos);
		virtual ReturnCode_t get_qos(
			DomainParticipantFactoryQos* qos);
	};
};

#endif /* __DDS_CONNEXT__ */
