#include <dds/opendds.h>
#include <stdio.h>

namespace dds {

extern "C" {
	DomainParticipantFactory* create_DomainParticipantFactory() {
		return new OpenDDSDomainParticipantFactory();
	}
}

OpenDDSDomainParticipantFactory::OpenDDSDomainParticipantFactory() {
	instance = TheParticipantFactory;
	printf("OpenDDS instance: %p\n", instance);
}

OpenDDSDomainParticipantFactory::~OpenDDSDomainParticipantFactory() {
}

DomainParticipant* OpenDDSDomainParticipantFactory::create_participant(
	DomainId_t domain_id,
	const DomainParticipantQos* qos,
	const DomainParticipantListener* a_listener,
	const StatusMask mask) {

	DDS::DomainId_t domain_id2 = OpenDDSDomainId_t::from(domain_id);
	DDS::DomainParticipantQos* qos2 = OpenDDSDomainParticipantQos::from(qos);
	DDS::DomainParticipantListener* a_listener2 = OpenDDSDomainParticipantListener::from(a_listener);
	DDS::StatusMask mask2 = OpenDDSStatusMask::from(mask);

	DDS::DomainParticipant* dp = instance->create_participant(domain_id2, *qos2, a_listener2, mask2);

	return new OpenDDSDomainParticipant(this, dp);
}

ReturnCode_t OpenDDSDomainParticipantFactory::delete_participant(const DomainParticipant* a_participant) {
	return RETCODE_ERROR;
}

DomainParticipant* OpenDDSDomainParticipantFactory::lookup_participant(DomainId_t domain_id) {
	return NULL;
}

ReturnCode_t OpenDDSDomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t OpenDDSDomainParticipantFactory::get_default_participant_qos(DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t OpenDDSDomainParticipantFactory::set_qos(const DomainParticipantFactoryQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t OpenDDSDomainParticipantFactory::get_qos(DomainParticipantFactoryQos* qos) {
	return RETCODE_ERROR;
}

OpenDDSDomainParticipant::OpenDDSDomainParticipant(
	OpenDDSDomainParticipantFactory* factory,
	DDS::DomainParticipant* instance) {

	this->factory = factory;
	this->instance = instance;
}

OpenDDSDomainParticipant::~OpenDDSDomainParticipant() {
}

DDS::DomainId_t OpenDDSDomainId_t::from(const DomainId_t id) {
	return id;
}

DomainId_t OpenDDSDomainId_t::to(const DDS::DomainId_t id) {
	return id;
}

DDS::DomainParticipantQos* OpenDDSDomainParticipantQos::from(const DomainParticipantQos* qos) {
	return NULL;
}

DomainParticipantQos* OpenDDSDomainParticipantQos::to(const DDS::DomainParticipantQos* qos) {
	return NULL;
}

DDS::DomainParticipantListener* OpenDDSDomainParticipantListener::from(const DomainParticipantListener* listener) {
	return NULL;
}

DomainParticipantListener* OpenDDSDomainParticipantListener::to(const DDS::DomainParticipantListener* listener) {
	return NULL;
}

DDS::StatusMask OpenDDSStatusMask::from(const StatusMask mask) {
	return mask;
}

StatusMask OpenDDSStatusMask::to(const DDS::StatusMask mask) {
	return mask;
}

};
