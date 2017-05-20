#include <dds/connext.h>

namespace dds {

ConnextDomainParticipantFactory::ConnextDomainParticipantFactory() {
}

ConnextDomainParticipantFactory::~ConnextDomainParticipantFactory() {
}

DomainParticipant* ConnextDomainParticipantFactory::create_participant(
	DomainId_t domain_id,
	const DomainParticipantQos* qos,
	const DomainParticipantListener* a_listener,
	const StatusMask* mask) {

	return NULL;
}

ReturnCode_t ConnextDomainParticipantFactory::delete_participant(const DomainParticipant* a_participant) {
	return RETCODE_ERROR;
}

DomainParticipant* ConnextDomainParticipantFactory::lookup_participant(DomainId_t domain_id) {
	return NULL;
}

ReturnCode_t ConnextDomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t ConnextDomainParticipantFactory::get_default_participant_qos(DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t ConnextDomainParticipantFactory::set_qos(const DomainParticipantFactoryQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t ConnextDomainParticipantFactory::get_qos(DomainParticipantFactoryQos* qos) {
	return RETCODE_ERROR;
}

};
