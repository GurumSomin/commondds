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
	DDS::DomainId_t id2 = (DDS::DomainId_t) id;
	return id2;
}

DomainId_t OpenDDSDomainId_t::to(const DDS::DomainId_t id) {
	DomainId_t id2 = (DomainId_t) id;
	return id2;
}

DDS::DomainParticipantQos* OpenDDSDomainParticipantQos::from(const DomainParticipantQos* qos) {
	DDS::DomainParticipantQos* qos2 = new DDS::DomainParticipantQos();

	CORBA::ULong maximum = (CORBA::ULong)qos->user_data.value->maximum;
	CORBA::ULong length = (CORBA::ULong)qos->user_data.value->length;
	CORBA::Octet* buffer = (CORBA::Octet*)qos->user_data.value->buffer;

	qos2->user_data.value = DDS::OctetSeq(maximum, length, buffer);
	qos2->entity_factory = *(OpenDDSEntityFactoryQosPolicy::from(&qos->entity_factory));
	return qos2;
}

DomainParticipantQos* OpenDDSDomainParticipantQos::to(const DDS::DomainParticipantQos* qos) {
	DomainParticipantQos* qos2 = new DomainParticipantQos();

	uint8_t* buffer = (uint8_t*)qos->user_data.value.get_buffer();
	uint32_t length = (uint32_t)qos->user_data.value.length();
	//uint32_t maximum = (uint32_t) qos->user_data.value.maximum;

	//TODO sequence maximum constructor added.
	qos2->user_data.value =  new sequence<uint8_t>(buffer, length);
	qos2->entity_factory = *(OpenDDSEntityFactoryQosPolicy::to(&qos->entity_factory));
	return qos2;
}

DDS::PublisherQos* from(const PublisherQos* qos) {
	DDS::PublisherQos* qos2 = new DDS::PublisherQos();

	// DDS::PresentationQosPolicy presentation
	DDS::PresentationQosPolicyAccessScopeKind access_scope
		= (DDS::PresentationQosPolicyAccessScopeKind)qos->presentation.access_scope;
	CORBA::Boolean coherent_access
		= (CORBA::Boolean)qos->presentation.coherent_access;
	CORBA::Boolean ordered_access
		= (CORBA::Boolean)qos->presentation.ordered_access;
    qos2->presentation.access_scope = access_scope;
	qos2->presentation.coherent_access = coherent_access;
	qos2->presentation.ordered_access = ordered_access;

	// DDS::PartitionQosPolicy partition
	CORBA::ULong maximum1 = (CORBA::ULong)qos->partition.name->maximum;
	CORBA::ULong length1 = (CORBA::ULong)qos->partition.name->length;
	CORBA::Char ** buffer1 = (CORBA::Char **)qos->partition.name->buffer;
	qos2->partition.name = DDS::StringSeq(maximum1, length1, buffer1, false);

	// DDS::GroupDataQosPolicy group_data
	CORBA::ULong maximum2 = (CORBA::ULong)qos->group_data.value->maximum;
	CORBA::ULong length2 = (CORBA::ULong)qos->group_data.value->length;
	CORBA::Octet* buffer2 = (CORBA::Octet*)qos->group_data.value->buffer;
	qos2->group_data.value = DDS::OctetSeq(maximum2, length2, buffer2);

    // DDS::EntityFactoryQosPolicy entity_factory
	qos2->entity_factory = *(OpenDDSEntityFactoryQosPolicy::from(&qos->entity_factory));
}

PublisherQos* to(const DDS::PublisherQos* qos) {

}

DDS::EntityFactoryQosPolicy* from(const EntityFactoryQosPolicy* entity_factory) {
	DDS::EntityFactoryQosPolicy* entity_factory2 = new DDS::EntityFactoryQosPolicy();

	CORBA::Boolean inner_entitiy_factory = (CORBA::Boolean)entity_factory->autoenable_created_entities;
	entity_factory2->autoenable_created_entities = inner_entitiy_factory;

	return entity_factory2;

}

EntityFactoryQosPolicy* to(const DDS::EntityFactoryQosPolicy* entity_factory) {
	EntityFactoryQosPolicy* entity_factory2 = new EntityFactoryQosPolicy();

	bool inner_entitiy_factory = (bool)entity_factory->autoenable_created_entities;
	entity_factory2->autoenable_created_entities = inner_entitiy_factory;

	return entity_factory2;
}

DDS::DomainParticipantListener* OpenDDSDomainParticipantListener::from(const DomainParticipantListener* listener) {
	//DomainpartcipantListener --> publisherlistener, subscriberlistener, topiclistener.
	//TODO have to convert functions --> how?
	return NULL;
}

DomainParticipantListener* OpenDDSDomainParticipantListener::to(const DDS::DomainParticipantListener* listener) {
	return NULL;
}

//TODO I think below functions have to be implemented..
//DDS::PublisherListener* OpenDDSPublisherListener::from(const PublisherListener* listener) {
//PublisherListener* OpenDDSPublisherListener::to(const DDS::PublisherListener* listener) {
//
//DDS::SubscriberListener* OpenDDSSubscriberListener::from(const SubscriberListener* listener) {
//SubscriberListener* OpenDDSSubscriberListener::to(const DDS::SubscriberListener* listener) {
//
//DDS::TopicListener* OpenDDSTopicListener::from(const TopicListener* listener) {
//TopicListener* OpenDDSTopicListener::to(const DDS::TopicListener* listener) {

DDS::StatusMask OpenDDSStatusMask::from(const StatusMask mask) {
	DDS::StatusMask mask2 = (DDS::StatusMask) mask;
	return mask2;
}

StatusMask OpenDDSStatusMask::to(const DDS::StatusMask mask) {
	StatusMask mask2 = (StatusMask) mask;
	return mask2;
}

};
