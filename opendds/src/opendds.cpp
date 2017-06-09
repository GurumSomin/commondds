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

	DDS::DomainId_t domain_id2;
	DDS::DomainParticipantQos qos2;
	DDS::DomainParticipantListener *a_listener2 = NULL;
	DDS::StatusMask mask2;

	OpenDDSDomainParticipantQos::convert(*qos, qos2);

	DDS::DomainParticipant* dp = instance->create_participant(domain_id, qos2, a_listener2, mask);

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

void OpenDDSDomainParticipantQos::convert(DomainParticipantQos& source, DDS::DomainParticipantQos& target) {
	CORBA::ULong maximum = (CORBA::ULong)source.user_data.value->maximum;
	CORBA::ULong length = (CORBA::ULong)source.user_data.value->length;
	CORBA::Octet* buffer = (CORBA::Octet*)source.user_data.value->buffer;

	target.user_data.value = DDS::OctetSeq(maximum, length, buffer);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSDomainParticipantQos::convert(DDS::DomainParticipantQos& source, DomainParticipantQos& target) {
	uint32_t maximum = (uint32_t)source.user_data.value.maximum();
	uint32_t length = (uint32_t)source.user_data.value.length();
	uint8_t* buffer = (uint8_t*)source.user_data.value.get_buffer();

	target.user_data.value =  new sequence<uint8_t>(maximum, length, buffer);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSPublisherQos::convert(PublisherQos& source, DDS::PublisherQos& target) {
	// DDS::PresentationQosPolicy presentation
	DDS::PresentationQosPolicyAccessScopeKind access_scope
		= (DDS::PresentationQosPolicyAccessScopeKind)source.presentation.access_scope;
	CORBA::Boolean coherent_access
		= (CORBA::Boolean)source.presentation.coherent_access;
	CORBA::Boolean ordered_access
		= (CORBA::Boolean)source.presentation.ordered_access;
    target.presentation.access_scope = access_scope;
	target.presentation.coherent_access = coherent_access;
	target.presentation.ordered_access = ordered_access;

	// DDS::PartitionQosPolicy partition
	CORBA::ULong maximum1 = (CORBA::ULong)source.partition.name->maximum;
	CORBA::ULong length1 = (CORBA::ULong)source.partition.name->length;
	CORBA::Char ** buffer1 = (CORBA::Char **)source.partition.name->buffer;
	target.partition.name = DDS::StringSeq(maximum1, length1, buffer1, false);

	// DDS::GroupDataQosPolicy group_data
	CORBA::ULong maximum2 = (CORBA::ULong)source.group_data.value->maximum;
	CORBA::ULong length2 = (CORBA::ULong)source.group_data.value->length;
	CORBA::Octet* buffer2 = (CORBA::Octet*)source.group_data.value->buffer;
	target.group_data.value = DDS::OctetSeq(maximum2, length2, buffer2);

    // DDS::EntityFactoryQosPolicy entity_factory
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSPublisherQos::convert(DDS::PublisherQos& source, PublisherQos& target) {
	// PresentationQosPolicy presentation
	PresentationQosPolicyAccessScopeKind access_scope
		= (PresentationQosPolicyAccessScopeKind)source.presentation.access_scope;
	bool coherent_access
		= (bool)source.presentation.coherent_access;
	bool ordered_access
		= (bool)source.presentation.ordered_access;
    target.presentation.access_scope = access_scope;
	target.presentation.coherent_access = coherent_access;
	target.presentation.ordered_access = ordered_access;

	// PartitionQosPolicy partition
	uint32_t maximum1 = (uint32_t)source.partition.name.maximum();
	uint32_t length1 = (uint32_t)source.partition.name.length();
	char ** buffer1 = (char **)(source.partition.name.get_buffer());
	target.partition.name = new StringSeq(maximum1, length1, buffer1);

	// GroupDataQosPolicy group_data
	uint32_t maximum2 = (uint32_t)source.group_data.value.maximum();
	uint32_t length2 = (uint32_t)source.group_data.value.length();
	uint8_t* buffer2 = (uint8_t*)source.group_data.value.get_buffer();

	target.group_data.value = new sequence<uint8_t>(maximum2, length2, buffer2);

    // EntityFactoryQosPolicy entity_factory
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSEntityFactoryQosPolicy::convert(EntityFactoryQosPolicy& source, DDS::EntityFactoryQosPolicy& target) {
	CORBA::Boolean inner_entitiy_factory = (CORBA::Boolean)source.autoenable_created_entities;
	target.autoenable_created_entities = inner_entitiy_factory;
}

void OpenDDSEntityFactoryQosPolicy::convert(DDS::EntityFactoryQosPolicy& source, EntityFactoryQosPolicy& target) {
	bool inner_entitiy_factory = (bool)source.autoenable_created_entities;
	target.autoenable_created_entities = inner_entitiy_factory;
}

void OpenDDSDomainParticipantListener::convert(DomainParticipantListener& source, DDS::DomainParticipantListener& target) {
	//DomainpartcipantListener --> publisherlistener, subscriberlistener, topiclistener.
	//TODO have to convert functions --> how?
}

void OpenDDSDomainParticipantListener::convert(DDS::DomainParticipantListener& source, DomainParticipantListener& target) {
}

//TODO I think below functions have to be implemented..
//DDS::PublisherListener* OpenDDSPublisherListener::convert(PublisherListener* listener) {
//PublisherListener* OpenDDSPublisherListener::convert(DDS::PublisherListener* listener) {
//
//DDS::SubscriberListener* OpenDDSSubscriberListener::convert(SubscriberListener* listener) {
//SubscriberListener* OpenDDSSubscriberListener::convert(DDS::SubscriberListener* listener) {
//
//DDS::TopicListener* OpenDDSTopicListener::convert(TopicListener* listener) {
//TopicListener* OpenDDSTopicListener::convert(DDS::TopicListener* listener) {

};
