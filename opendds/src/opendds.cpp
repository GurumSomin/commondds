#include <dds/opendds.h>
#include <stdio.h>
#include <stdlib.h>

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
	DDS::DomainId_t id2 = (DDS::DomainId_t) id;
	return id2;
}

DomainId_t OpenDDSDomainId_t::to(const DDS::DomainId_t id) {
	DomainId_t id2 = (DomainId_t) id;
	return id2;
}

DDS::DomainParticipantQos* OpenDDSDomainParticipantQos::from(const DomainParticipantQos* qos) {
	DDS::DomainParticipantQos* qos2 = new DDS::DomainParticipantQos();

	CORBA::ULong maximum = (CORBA::ULong) qos->user_data.value->maximum;
	CORBA::ULong length = (CORBA::ULong) qos->user_data.value->length;
	CORBA::Octet* buffer = (CORBA::Octet*) qos->user_data.value->buffer;
	CORBA::Boolean inner_entitiy_factory = (CORBA::Boolean) qos->entity_factory.autoenable_created_entities;

	qos2->user_data.value = DDS::OctetSeq(maximum, length, buffer);
	qos2->entity_factory.autoenable_created_entities = inner_entitiy_factory;
	return qos2;
}

DomainParticipantQos* OpenDDSDomainParticipantQos::to(const DDS::DomainParticipantQos* qos) {
	DomainParticipantQos* qos2 = new DomainParticipantQos();

	uint32_t length = (uint32_t) qos->user_data.value.length();
	uint8_t* buffer = (uint8_t*) qos->user_data.value.get_buffer();
	bool inner_entitiy_factory = (bool) qos->entity_factory.autoenable_created_entities;

	qos2->user_data.value =  new sequence<uint8_t>(buffer, length);
	qos2->entity_factory.autoenable_created_entities = inner_entitiy_factory;
	return qos2;
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
