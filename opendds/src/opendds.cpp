#include <dds/opendds.h>

#include <cstdio>
#include <cstring>

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
	const DomainParticipantQos& qos,
	DomainParticipantListener* a_listener,
	const StatusMask mask) {

	DDS::DomainParticipantQos qos2;

	OpenDDSDomainParticipantQos::convert(qos, qos2);
	OpenDDSDomainParticipantListener* a_listener2 = new OpenDDSDomainParticipantListener(a_listener);

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

void OpenDDSDomainParticipantQos::convert(const DomainParticipantQos& source, DDS::DomainParticipantQos& target) {
	CORBA::ULong maximum = (CORBA::ULong)source.user_data.value.maximum;
	CORBA::ULong length = (CORBA::ULong)source.user_data.value.length;
	CORBA::Octet* buffer = new CORBA::Octet[maximum];
	std::memcpy(buffer, source.user_data.value.buffer, maximum);

	target.user_data.value = DDS::OctetSeq(maximum, length, buffer);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSDomainParticipantQos::convert(const DDS::DomainParticipantQos& source, DomainParticipantQos& target) {
	uint32_t maximum = (uint32_t)source.user_data.value.maximum();
	uint32_t length = (uint32_t)source.user_data.value.length();
	uint8_t* buffer = new uint8_t[maximum];
	std::memcpy(buffer, source.user_data.value.get_buffer(), maximum);

	target.user_data.value(maximum, length, buffer);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSPublisherQos::convert(const PublisherQos& source, DDS::PublisherQos& target) {
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
	CORBA::ULong maximum1 = (CORBA::ULong)source.partition.name.maximum;
	CORBA::ULong length1 = (CORBA::ULong)source.partition.name.length;
	CORBA::Char** buffer1 = new CORBA::Char*[maximum1];
	CORBA::Char** partition_name = source.partition.name.buffer;
	for(uint32_t i = 0; i < maximum1; ++i)
		buffer1[i] = strdup(partition_name[i]);
	target.partition.name = DDS::StringSeq(maximum1, length1, buffer1, false);

	// DDS::GroupDataQosPolicy group_data
	CORBA::ULong maximum2 = (CORBA::ULong)source.group_data.value.maximum;
	CORBA::ULong length2 = (CORBA::ULong)source.group_data.value.length;
	CORBA::Octet* buffer2 = new CORBA::Octet[maximum2];
	std::memcpy(buffer2, source.group_data.value.buffer, maximum2);
	target.group_data.value = DDS::OctetSeq(maximum2, length2, buffer2);

	// DDS::EntityFactoryQosPolicy entity_factory
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSPublisherQos::convert(const DDS::PublisherQos& source, PublisherQos& target) {
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
	char** buffer1 = new char*[maximum1];
	char** partition_name = (char**)source.partition.name.get_buffer();
	for(uint32_t i = 0; i < maximum1; ++i)
		buffer1[i] = strdup(partition_name[i]);
	target.partition.name(maximum1, length1, buffer1);

	// GroupDataQosPolicy group_data
	uint32_t maximum2 = (uint32_t)source.group_data.value.maximum();
	uint32_t length2 = (uint32_t)source.group_data.value.length();
	uint8_t* buffer2 = new uint8_t[maximum2];
	std::memcpy(buffer2, source.group_data.value.get_buffer(), maximum2);
	target.group_data.value(maximum2, length2, buffer2);

	// EntityFactoryQosPolicy entity_factory
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSEntityFactoryQosPolicy::convert(const EntityFactoryQosPolicy& source, DDS::EntityFactoryQosPolicy& target) {
	CORBA::Boolean inner_entitiy_factory = (CORBA::Boolean)source.autoenable_created_entities;
	target.autoenable_created_entities = inner_entitiy_factory;
}

void OpenDDSEntityFactoryQosPolicy::convert(const DDS::EntityFactoryQosPolicy& source, EntityFactoryQosPolicy& target) {
	bool inner_entitiy_factory = (bool)source.autoenable_created_entities;
	target.autoenable_created_entities = inner_entitiy_factory;
}

OpenDDSDomainParticipantListener::OpenDDSDomainParticipantListener(dds::DomainParticipantListener* l) {
	listener = l;
}

OpenDDSDomainParticipantListener::~OpenDDSDomainParticipantListener() {
	delete listener;
}

DomainParticipantListener* OpenDDSDomainParticipantListener::get_listener() {
	return listener;
}

void OpenDDSDomainParticipantListener::on_inconsistent_topic(DDS::Topic* the_topic, const DDS::InconsistentTopicStatus& status) {
	//TODO make converters for Topic and InconsistentTopicStatus
	dds::Topic* topic = new OpenDDSTopic(the_topic);
	const dds::InconsistentTopicStatus t;
	listener->on_inconsistent_topic(topic, t);
}

OpenDDSTopic::OpenDDSTopic(DDS::Topic* the_topic) {
	topic = the_topic;
}

OpenDDSTopic::~OpenDDSTopic() {
	DDS::DomainParticipant* dp = topic->get_participant();
	dp->delete_topic(topic);
}

};
