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
}

OpenDDSDomainParticipantFactory::~OpenDDSDomainParticipantFactory() {
}

DomainParticipant* OpenDDSDomainParticipantFactory::create_participant(
	DomainId_t domain_id,
	const DomainParticipantQos& qos,
	DomainParticipantListener* a_listener,
	const StatusMask mask) {

	DDS::DomainParticipantQos qos2;

	DDS::DomainId_t domain_id2 = (DDS::DomainId_t) domain_id;
	OpenDDSDomainParticipantQos::convert(qos, qos2);
	OpenDDSDomainParticipantListener* a_listener2 = new OpenDDSDomainParticipantListener(a_listener);
	DDS::StatusMask mask2 = (DDS::StatusMask) mask;

	DDS::DomainParticipant* dp = instance->create_participant(domain_id2, qos2, a_listener2, mask2);

	return new OpenDDSDomainParticipant(this, dp);
}

ReturnCode_t OpenDDSDomainParticipantFactory::delete_participant(const DomainParticipant* a_participant) {
	OpenDDSDomainParticipant* a_participant2 = (OpenDDSDomainParticipant*) a_participant;
	ReturnCode_t rt = instance->delete_participant(a_participant2->get_instance());
	TheServiceParticipant->shutdown();
	return rt;
}

DomainParticipant* OpenDDSDomainParticipantFactory::lookup_participant(DomainId_t domain_id) {
	return NULL;
}

ReturnCode_t OpenDDSDomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos& qos) {
	return RETCODE_ERROR;
}

ReturnCode_t OpenDDSDomainParticipantFactory::get_default_participant_qos(DomainParticipantQos& qos) {
	return RETCODE_ERROR;
}

ReturnCode_t OpenDDSDomainParticipantFactory::set_qos(const DomainParticipantFactoryQos& qos) {
	return RETCODE_ERROR;
}

ReturnCode_t OpenDDSDomainParticipantFactory::get_qos(DomainParticipantFactoryQos& qos) {
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

Publisher* OpenDDSDomainParticipant::create_publisher(const PublisherQos& qos, PublisherListener* a_listener, const StatusMask mask) {
	DDS::PublisherQos qos2;
	OpenDDSPublisherListener* a_listener2 = new OpenDDSPublisherListener(a_listener);
	DDS::StatusMask mask2;

	OpenDDSPublisherQos::convert(qos, qos2);
	mask2 = (DDS::StatusMask) mask;

	DDS::Publisher* publisher = this->instance->create_publisher(qos2, a_listener2, mask2);
	OpenDDSPublisher* publisher2 = new OpenDDSPublisher(publisher, this);

	return publisher2;
}

Topic* OpenDDSDomainParticipant::create_topic(const char* topic_name, const char* type_name, const TopicQos& qos, TopicListener* a_listener, const StatusMask mask) {
	DDS::TopicQos qos2;
	OpenDDSTopicQos::convert(qos, qos2);
	OpenDDSTopicListener* a_listener2 = new OpenDDSTopicListener(a_listener);
	DDS::StatusMask mask2 = (DDS::StatusMask) mask;

	DDS::Topic* topic = instance->create_topic(topic_name, type_name, qos2, a_listener2, mask2);
	OpenDDSTopic* topic2 = new OpenDDSTopic(topic);

	return topic2;
}

DDS::DomainParticipant* OpenDDSDomainParticipant::get_instance() {
	return instance;
}

ReturnCode_t OpenDDSDomainParticipant::delete_contained_entities() { //TODO: should find the method to delete instances of OpenDDS prefixed classes
	return (ReturnCode_t)instance->delete_contained_entities();
}

void OpenDDSDomainParticipantQos::convert(const DomainParticipantQos& source, DDS::DomainParticipantQos& target) {
	OpenDDSUserDataQosPolicy::convert(source.user_data, target.user_data);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSDomainParticipantQos::convert(const DDS::DomainParticipantQos& source, DomainParticipantQos& target) {
	OpenDDSUserDataQosPolicy::convert(source.user_data, target.user_data);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSPublisherQos::convert(const PublisherQos& source, DDS::PublisherQos& target) {
	OpenDDSPresentationQosPolicy::convert(source.presentation, target.presentation);
	OpenDDSPartitionQosPolicy::convert(source.partition, target.partition);
	OpenDDSGroupDataQosPolicy::convert(source.group_data, target.group_data);
	OpenDDSEntityFactoryQosPolicy::convert(source.entity_factory, target.entity_factory);
}

void OpenDDSPublisherQos::convert(const DDS::PublisherQos& source, PublisherQos& target) {
	OpenDDSPresentationQosPolicy::convert(source.presentation, target.presentation);
	OpenDDSPartitionQosPolicy::convert(source.partition, target.partition);
	OpenDDSGroupDataQosPolicy::convert(source.group_data, target.group_data);
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

void OpenDDSPresentationQosPolicy::convert(const PresentationQosPolicy& source, DDS::PresentationQosPolicy& target) {
	DDS::PresentationQosPolicyAccessScopeKind access_scope = (DDS::PresentationQosPolicyAccessScopeKind)source.access_scope;
	CORBA::Boolean coherent_access = (CORBA::Boolean)source.coherent_access;
	CORBA::Boolean ordered_access = (CORBA::Boolean)source.ordered_access;
	target.access_scope = access_scope;
	target.coherent_access = coherent_access;
	target.ordered_access = ordered_access;
}

void OpenDDSPresentationQosPolicy::convert(const DDS::PresentationQosPolicy& source, PresentationQosPolicy& target) {
	PresentationQosPolicyAccessScopeKind access_scope = (PresentationQosPolicyAccessScopeKind)source.access_scope;
	bool coherent_access = (bool)source.coherent_access;
	bool ordered_access = (bool)source.ordered_access;
	target.access_scope = access_scope;
	target.coherent_access = coherent_access;
	target.ordered_access = ordered_access;
}

void OpenDDSPartitionQosPolicy::convert(const PartitionQosPolicy& source, DDS::PartitionQosPolicy& target) {
	CORBA::ULong maximum1 = (CORBA::ULong)source.name.maximum;
	CORBA::ULong length1 = (CORBA::ULong)source.name.length;
	CORBA::Char** buffer1 = new CORBA::Char*[maximum1];
	CORBA::Char** partition_name = source.name.buffer;
	for(uint32_t i = 0; i < maximum1; ++i)
		buffer1[i] = strdup(partition_name[i]);
	target.name = DDS::StringSeq(maximum1, length1, buffer1, false);
}

void OpenDDSPartitionQosPolicy::convert(const DDS::PartitionQosPolicy& source, PartitionQosPolicy& target) {
	uint32_t maximum1 = (uint32_t)source.name.maximum();
	uint32_t length1 = (uint32_t)source.name.length();
	char** buffer1 = new char*[maximum1];
	char** partition_name = (char**)source.name.get_buffer();
	for(uint32_t i = 0; i < maximum1; ++i)
		buffer1[i] = strdup(partition_name[i]);
	target.name(maximum1, length1, buffer1);
}

void OpenDDSGroupDataQosPolicy::convert(const GroupDataQosPolicy& source, DDS::GroupDataQosPolicy& target) {
	CORBA::ULong maximum2 = (CORBA::ULong)source.value.maximum;
	CORBA::ULong length2 = (CORBA::ULong)source.value.length;
	CORBA::Octet* buffer2 = new CORBA::Octet[maximum2];
	std::memcpy(buffer2, source.value.buffer, maximum2);
	target.value = DDS::OctetSeq(maximum2, length2, buffer2);
}

void OpenDDSGroupDataQosPolicy::convert(const DDS::GroupDataQosPolicy& source, GroupDataQosPolicy& target) {
	uint32_t maximum2 = (uint32_t)source.value.maximum();
	uint32_t length2 = (uint32_t)source.value.length();
	uint8_t* buffer2 = new uint8_t[maximum2];
	std::memcpy(buffer2, source.value.get_buffer(), maximum2);
	target.value(maximum2, length2, buffer2);
}

void OpenDDSUserDataQosPolicy::convert(const UserDataQosPolicy& source, DDS::UserDataQosPolicy& target) {
	CORBA::ULong maximum = (CORBA::ULong)source.value.maximum;
	CORBA::ULong length = (CORBA::ULong)source.value.length;
	CORBA::Octet* buffer = new CORBA::Octet[maximum];
	std::memcpy(buffer, source.value.buffer, maximum);
	target.value = DDS::OctetSeq(maximum, length, buffer);
}
void OpenDDSUserDataQosPolicy::convert(const DDS::UserDataQosPolicy& source, UserDataQosPolicy& target) {
	uint32_t maximum = (uint32_t)source.value.maximum();
	uint32_t length = (uint32_t)source.value.length();
	uint8_t* buffer = new uint8_t[maximum];
	std::memcpy(buffer, source.value.get_buffer(), maximum);
	target.value(maximum, length, buffer);
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
	OpenDDSTopic topic(the_topic);
	dds::InconsistentTopicStatus t;
	OpenDDSInconsistentTopicStatus::convert(status, t);
	listener->on_inconsistent_topic(&topic, t);
}

void OpenDDSDomainParticipantListener::on_offered_deadline_missed(DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status) {
}
void OpenDDSDomainParticipantListener::on_offered_incompatible_qos(DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status) {
}
void OpenDDSDomainParticipantListener::on_liveliness_lost(DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status) {
}
void OpenDDSDomainParticipantListener::on_publication_matched(DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status) {
}
void OpenDDSDomainParticipantListener::on_data_on_readers(DDS::Subscriber* the_subscriber) {
}
void OpenDDSDomainParticipantListener::on_requested_deadline_missed(DDS::DataReader* the_reader, const DDS::RequestedDeadlineMissedStatus& status) {
}
void OpenDDSDomainParticipantListener::on_requested_incompatible_qos(DDS::DataReader* the_reader, const DDS::RequestedIncompatibleQosStatus& status) {
}
void OpenDDSDomainParticipantListener::on_sample_rejected(DDS::DataReader* the_reader, const DDS::SampleRejectedStatus& status) {
}
void OpenDDSDomainParticipantListener::on_liveliness_changed(DDS::DataReader* the_reader, const DDS::LivelinessChangedStatus& status) {
}
void OpenDDSDomainParticipantListener::on_data_available(DDS::DataReader* the_reader) {
}
void OpenDDSDomainParticipantListener::on_subscription_matched(DDS::DataReader* the_reader, const DDS::SubscriptionMatchedStatus& status) {
}
void OpenDDSDomainParticipantListener::on_sample_lost(DDS::DataReader* the_reader, const DDS::SampleLostStatus& status) {
}

OpenDDSTopic::OpenDDSTopic(DDS::Topic* the_topic) {
	topic = the_topic;
}

OpenDDSTopic::~OpenDDSTopic() {
	DDS::DomainParticipant* dp = topic->get_participant();
	dp->delete_topic(topic);
}

DDS::Topic* OpenDDSTopic::get_topic() {
	return this->topic;
}

ReturnCode_t OpenDDSTopic::set_qos(const TopicQos& qos) {
	DDS::TopicQos qos2;
	OpenDDSTopicQos::convert(qos, qos2);
	return (dds::ReturnCode_t) topic->set_qos(qos2);
}

ReturnCode_t OpenDDSTopic::get_qos(TopicQos& qos) {
	DDS::TopicQos qos2;
	ReturnCode_t rc = (dds::ReturnCode_t) topic->get_qos(qos2);
	OpenDDSTopicQos::convert(qos2, qos);
	return rc;
}

void OpenDDSInconsistentTopicStatus::convert(const InconsistentTopicStatus& source, DDS::InconsistentTopicStatus& target) {
	target.total_count = (CORBA::Long) source.total_count_change;
	target.total_count_change = (CORBA::Long) source.total_count_change;
}

void OpenDDSInconsistentTopicStatus::convert(const DDS::InconsistentTopicStatus& source, InconsistentTopicStatus& target) {
	target.total_count = (int32_t) source.total_count_change;
	target.total_count_change = (int32_t) source.total_count_change;
}

void OpenDDSTopicQos::convert(const TopicQos& source, DDS::TopicQos& target) {
	OpenDDSTopicDataQosPolicy::convert(source.topic_data, target.topic_data);
	OpenDDSDurabilityQosPolicy::convert(source.durability, target.durability);
	OpenDDSDurabilityServiceQosPolicy::convert(source.durability_service, target.durability_service);
	OpenDDSDeadlineQosPolicy::convert(source.deadline, target.deadline);
	OpenDDSLatencyBudgetQosPolicy::convert(source.latency_budget, target.latency_budget);
	OpenDDSLivelinessQosPolicy::convert(source.liveliness, target.liveliness);
	OpenDDSReliabilityQosPolicy::convert(source.reliability, target.reliability);
	OpenDDSResourceLimitsQosPolicy::convert(source.resource_limits, target.resource_limits);
	OpenDDSDestinationOrderQosPolicy::convert(source.destination_order, target.destination_order);
	OpenDDSHistoryQosPolicy::convert(source.history, target.history);
	OpenDDSLifespanQosPolicy::convert(source.lifespan, target.lifespan);
	OpenDDSOwnershipQosPolicy::convert(source.ownership, target.ownership);
	OpenDDSTransportPriorityQosPolicy::convert(source.transport_priority, target.transport_priority);
}

void OpenDDSTopicQos::convert(const DDS::TopicQos& source, TopicQos& target) {
	OpenDDSTopicDataQosPolicy::convert(source.topic_data, target.topic_data);
	OpenDDSDurabilityQosPolicy::convert(source.durability, target.durability);
	OpenDDSDurabilityServiceQosPolicy::convert(source.durability_service, target.durability_service);
	OpenDDSDeadlineQosPolicy::convert(source.deadline, target.deadline);
	OpenDDSLatencyBudgetQosPolicy::convert(source.latency_budget, target.latency_budget);
	OpenDDSLivelinessQosPolicy::convert(source.liveliness, target.liveliness);
	OpenDDSReliabilityQosPolicy::convert(source.reliability, target.reliability);
	OpenDDSResourceLimitsQosPolicy::convert(source.resource_limits, target.resource_limits);
	OpenDDSDestinationOrderQosPolicy::convert(source.destination_order, target.destination_order);
	OpenDDSHistoryQosPolicy::convert(source.history, target.history);
	OpenDDSLifespanQosPolicy::convert(source.lifespan, target.lifespan);
	OpenDDSOwnershipQosPolicy::convert(source.ownership, target.ownership);
	OpenDDSTransportPriorityQosPolicy::convert(source.transport_priority, target.transport_priority);
}

void OpenDDSTopicDataQosPolicy::convert(const TopicDataQosPolicy& source, DDS::TopicDataQosPolicy& target) {
	CORBA::ULong maximum = (CORBA::ULong)source.value.maximum;
	CORBA::ULong length = (CORBA::ULong)source.value.length;
	CORBA::Octet* buffer = new CORBA::Octet[maximum];
	std::memcpy(buffer, source.value.buffer, maximum);
	target.value = DDS::OctetSeq(maximum, length, buffer);
}

void OpenDDSTopicDataQosPolicy::convert(const DDS::TopicDataQosPolicy& source, TopicDataQosPolicy& target) {
	uint32_t maximum = (uint32_t)source.value.maximum();
	uint32_t length = (uint32_t)source.value.length();
	uint8_t* buffer = new uint8_t[maximum];
	std::memcpy(buffer, source.value.get_buffer(), maximum);
	target.value(maximum, length, buffer);
}
void OpenDDSDurabilityQosPolicy::convert(const DurabilityQosPolicy& source, DDS::DurabilityQosPolicy& target) {
	target.kind = (DDS::DurabilityQosPolicyKind) source.kind;
}

void OpenDDSDurabilityQosPolicy::convert(const DDS::DurabilityQosPolicy& source, DurabilityQosPolicy& target) {
	target.kind = (DurabilityQosPolicyKind) source.kind;
}

void OpenDDSDurabilityServiceQosPolicy::convert(const DurabilityServiceQosPolicy& source, DDS::DurabilityServiceQosPolicy& target) {
	target.service_cleanup_delay.sec = (CORBA::Long) source.service_cleanup_delay.sec;
	target.service_cleanup_delay.nanosec = (CORBA::ULong) source.service_cleanup_delay.nanosec;
	target.history_kind = (DDS::HistoryQosPolicyKind) source.history_kind;
	target.history_depth = (CORBA::Long) source.history_depth;
	target.max_samples = (CORBA::Long) source.max_samples;
	target.max_instances = (CORBA::Long) source.max_instances;
	target.max_samples_per_instance = (CORBA::Long) source.max_samples_per_instance;
}

void OpenDDSDurabilityServiceQosPolicy::convert(const DDS::DurabilityServiceQosPolicy& source, DurabilityServiceQosPolicy& target) {
	target.service_cleanup_delay.sec = (int32_t)source.service_cleanup_delay.sec;
	target.service_cleanup_delay.nanosec = (int32_t)source.service_cleanup_delay.nanosec;
	target.history_kind = (HistoryQosPolicyKind)source.history_kind;
	target.history_depth = (int32_t)source.history_depth;
	target.max_samples = (int32_t)source.max_samples;
	target.max_instances = (int32_t)source.max_instances;
	target.max_samples_per_instance = (int32_t)source.max_samples_per_instance;
}

void OpenDDSDeadlineQosPolicy::convert(const DeadlineQosPolicy& source, DDS::DeadlineQosPolicy& target) {
	target.period.sec = (CORBA::Long) source.period.sec;
	target.period.nanosec = (CORBA::ULong) source.period.nanosec;
}

void OpenDDSDeadlineQosPolicy::convert(const DDS::DeadlineQosPolicy& source, DeadlineQosPolicy& target) {
	target.period.sec = (int32_t)source.period.sec;
	target.period.nanosec = (int32_t)source.period.nanosec;
}

void OpenDDSLatencyBudgetQosPolicy::convert(const LatencyBudgetQosPolicy& source, DDS::LatencyBudgetQosPolicy& target) {
	target.duration.sec = (CORBA::Long) source.duration.sec;
	target.duration.nanosec = (CORBA::ULong) source.duration.nanosec;
}

void OpenDDSLatencyBudgetQosPolicy::convert(const DDS::LatencyBudgetQosPolicy& source, LatencyBudgetQosPolicy& target) {
	target.duration.sec = (int32_t)source.duration.sec;
	target.duration.nanosec = (uint32_t)source.duration.nanosec;
}

void OpenDDSLivelinessQosPolicy::convert(const LivelinessQosPolicy& source, DDS::LivelinessQosPolicy& target) {
	target.kind = (DDS::LivelinessQosPolicyKind) source.kind;
	target.lease_duration.sec = (CORBA::Long) source.lease_duration.sec;
	target.lease_duration.nanosec = (CORBA::ULong) source.lease_duration.nanosec;
}

void OpenDDSLivelinessQosPolicy::convert(const DDS::LivelinessQosPolicy& source, LivelinessQosPolicy& target) {
	target.kind = (LivelinessQosPolicyKind)source.kind;
	target.lease_duration.sec = (int32_t)source.lease_duration.sec;
	target.lease_duration.nanosec = (uint32_t)source.lease_duration.nanosec;
}

void OpenDDSReliabilityQosPolicy::convert(const ReliabilityQosPolicy& source, DDS::ReliabilityQosPolicy& target) {
	target.kind = (DDS::ReliabilityQosPolicyKind) source.kind;
	target.max_blocking_time.sec = (CORBA::Long) source.max_blocking_time.sec;
	target.max_blocking_time.nanosec = (CORBA::ULong) source.max_blocking_time.nanosec;
}

void OpenDDSReliabilityQosPolicy::convert(const DDS::ReliabilityQosPolicy& source, ReliabilityQosPolicy& target) {
	target.kind = (ReliabilityQosPolicyKind)source.kind;
	target.max_blocking_time.sec = (int32_t)source.max_blocking_time.sec;
	target.max_blocking_time.nanosec = (int32_t)source.max_blocking_time.nanosec;
}

void OpenDDSDestinationOrderQosPolicy::convert(const DestinationOrderQosPolicy& source, DDS::DestinationOrderQosPolicy& target) {
	target.kind = (DDS::DestinationOrderQosPolicyKind) source.kind;
}

void OpenDDSDestinationOrderQosPolicy::convert(const DDS::DestinationOrderQosPolicy& source, DestinationOrderQosPolicy& target) {
	target.kind = (DestinationOrderQosPolicyKind) source.kind;
}

void OpenDDSHistoryQosPolicy::convert(const HistoryQosPolicy& source, DDS::HistoryQosPolicy& target) {
	target.kind = (DDS::HistoryQosPolicyKind) source.kind;
	target.depth = (CORBA::Long) source.depth;
}

void OpenDDSHistoryQosPolicy::convert(const DDS::HistoryQosPolicy& source, HistoryQosPolicy& target) {
	target.kind = (HistoryQosPolicyKind) source.kind;
	target.depth = (int32_t) source.depth;
}

void OpenDDSResourceLimitsQosPolicy::convert(const ResourceLimitsQosPolicy& source, DDS::ResourceLimitsQosPolicy& target) {
	target.max_samples = (CORBA::Long) source.max_samples;
	target.max_instances = (CORBA::Long) source.max_instances;
	target.max_samples_per_instance = (CORBA::Long) source.max_samples_per_instance;
}

void OpenDDSResourceLimitsQosPolicy::convert(const DDS::ResourceLimitsQosPolicy& source, ResourceLimitsQosPolicy& target) {
	target.max_samples = (int32_t)source.max_samples;
	target.max_instances = (int32_t)source.max_instances;
	target.max_samples_per_instance = (int32_t)source.max_samples_per_instance;
}

void OpenDDSTransportPriorityQosPolicy::convert(const TransportPriorityQosPolicy& source, DDS::TransportPriorityQosPolicy& target) {
	target.value = (CORBA::Long) source.value;
}

void OpenDDSTransportPriorityQosPolicy::convert(const DDS::TransportPriorityQosPolicy& source, TransportPriorityQosPolicy& target) {
	target.value = (int32_t)source.value;
}

void OpenDDSLifespanQosPolicy::convert(const LifespanQosPolicy& source, DDS::LifespanQosPolicy& target) {
	target.duration.sec = (CORBA::Long) source.duration.sec;
	target.duration.nanosec = (CORBA::ULong) source.duration.nanosec;
}

void OpenDDSLifespanQosPolicy::convert(const DDS::LifespanQosPolicy& source, LifespanQosPolicy& target) {
	target.duration.sec = (int32_t)source.duration.sec;
	target.duration.nanosec = (uint32_t)source.duration.nanosec;
}

void OpenDDSOwnershipQosPolicy::convert(const OwnershipQosPolicy& source, DDS::OwnershipQosPolicy& target) {
	target.kind = (DDS::OwnershipQosPolicyKind) source.kind;
}

void OpenDDSOwnershipQosPolicy::convert(const DDS::OwnershipQosPolicy& source, OwnershipQosPolicy& target) {
	target.kind = (OwnershipQosPolicyKind) source.kind;
}

OpenDDSPublisherListener::OpenDDSPublisherListener(dds::PublisherListener* p) {
	this->listener = p;
}

OpenDDSPublisherListener::~OpenDDSPublisherListener() {
	delete listener;
}

dds::PublisherListener* OpenDDSPublisherListener::get_listener() {
	return listener;
}

void OpenDDSPublisherListener::on_offered_deadline_missed(DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status) {
}
void OpenDDSPublisherListener::on_offered_incompatible_qos(DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status) {
}
void OpenDDSPublisherListener::on_liveliness_lost(DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status) {
}
void OpenDDSPublisherListener::on_publication_matched(DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status) {
}
OpenDDSPublisher::OpenDDSPublisher(DDS::Publisher* instance, OpenDDSDomainParticipant* parent) {
	this->instance = instance;
	this->parent = parent;
}

OpenDDSPublisher::~OpenDDSPublisher() {
	parent->get_instance()->delete_publisher(instance);
}

DataWriter* OpenDDSPublisher::create_datawriter(Topic* a_topic, const DataWriterQos& qos, DataWriterListener* a_listener, const StatusMask mask) {
	OpenDDSTopic* topic = (OpenDDSTopic*)a_topic;
	DDS::Topic* a_topic2 = topic->get_topic();
	DDS::DataWriterQos qos2;
	OpenDDSDataWriterQos::convert(qos, qos2);
	OpenDDSDataWriterListener* a_listener2 = new OpenDDSDataWriterListener(a_listener);
	DDS::StatusMask mask2 = (DDS::StatusMask) mask;

	DDS::DataWriter* datawriter = instance->create_datawriter(a_topic2, qos2, a_listener2, mask2);
	Hello::MessageDataWriter* datawriter2 = new Hello::MessageDataWriter(datawriter);
	return datawriter2;
}

OpenDDSTopicListener::OpenDDSTopicListener(dds::TopicListener* t) {
	listener = t;
}

OpenDDSTopicListener::~OpenDDSTopicListener() {
	delete listener;
}

dds::TopicListener* OpenDDSTopicListener::get_listener() {
	return listener;
}

void OpenDDSTopicListener::on_inconsistent_topic(DDS::Topic* the_topic, const DDS::InconsistentTopicStatus& status) {
	OpenDDSTopic topic(the_topic);
	dds::InconsistentTopicStatus t;
	OpenDDSInconsistentTopicStatus::convert(status, t);
	listener->on_inconsistent_topic(&topic, t);
}


void OpenDDSDataWriterQos::convert(const DataWriterQos& source, DDS::DataWriterQos& target) {
	OpenDDSDurabilityQosPolicy::convert(source.durability, target.durability);
	OpenDDSDurabilityServiceQosPolicy::convert(source.durability_service, target.durability_service);
	OpenDDSDeadlineQosPolicy::convert(source.deadline, target.deadline);
	OpenDDSLatencyBudgetQosPolicy::convert(source.latency_budget, target.latency_budget);
	OpenDDSLivelinessQosPolicy::convert(source.liveliness, target.liveliness);
	OpenDDSReliabilityQosPolicy::convert(source.reliability, target.reliability);
	OpenDDSDestinationOrderQosPolicy::convert(source.destination_order, target.destination_order);
	OpenDDSHistoryQosPolicy::convert(source.history, target.history);
	OpenDDSResourceLimitsQosPolicy::convert(source.resource_limits, target.resource_limits);
	OpenDDSTransportPriorityQosPolicy::convert(source.transport_priority, target.transport_priority);
	OpenDDSLifespanQosPolicy::convert(source.lifespan, target.lifespan);
	OpenDDSUserDataQosPolicy::convert(source.user_data, target.user_data);
	OpenDDSOwnershipQosPolicy::convert(source.ownership, target.ownership);
	OpenDDSOwnershipStrengthQosPolicy::convert(source.ownership_strength, target.ownership_strength);
	OpenDDSWriterDataLifecycleQosPolicy::convert(source.writer_data_lifecycle, target.writer_data_lifecycle);
}

void OpenDDSDataWriterQos::convert(const DDS::DataWriterQos& source, DataWriterQos& target) {
	OpenDDSDurabilityQosPolicy::convert(source.durability, target.durability);
	OpenDDSDurabilityServiceQosPolicy::convert(source.durability_service, target.durability_service);
	OpenDDSDeadlineQosPolicy::convert(source.deadline, target.deadline);
	OpenDDSLatencyBudgetQosPolicy::convert(source.latency_budget, target.latency_budget);
	OpenDDSLivelinessQosPolicy::convert(source.liveliness, target.liveliness);
	OpenDDSReliabilityQosPolicy::convert(source.reliability, target.reliability);
	OpenDDSDestinationOrderQosPolicy::convert(source.destination_order, target.destination_order);
	OpenDDSHistoryQosPolicy::convert(source.history, target.history);
	OpenDDSResourceLimitsQosPolicy::convert(source.resource_limits, target.resource_limits);
	OpenDDSTransportPriorityQosPolicy::convert(source.transport_priority, target.transport_priority);
	OpenDDSLifespanQosPolicy::convert(source.lifespan, target.lifespan);
	OpenDDSUserDataQosPolicy::convert(source.user_data, target.user_data);
	OpenDDSOwnershipQosPolicy::convert(source.ownership, target.ownership);
	OpenDDSOwnershipStrengthQosPolicy::convert(source.ownership_strength, target.ownership_strength);
	OpenDDSWriterDataLifecycleQosPolicy::convert(source.writer_data_lifecycle, target.writer_data_lifecycle);
}

void OpenDDSOwnershipStrengthQosPolicy::convert(const OwnershipStrengthQosPolicy& source, DDS::OwnershipStrengthQosPolicy& target) {
	target.value = (CORBA::Long) source.value;
}

void OpenDDSOwnershipStrengthQosPolicy::convert(const DDS::OwnershipStrengthQosPolicy& source, OwnershipStrengthQosPolicy& target) {
	target.value = (int32_t) source.value;
}

void OpenDDSWriterDataLifecycleQosPolicy::convert(const WriterDataLifecycleQosPolicy& source, DDS::WriterDataLifecycleQosPolicy target) {
	CORBA::Boolean b = (CORBA::Boolean)source.autodispose_unregistered_instances;
	target.autodispose_unregistered_instances = b;
}
void OpenDDSWriterDataLifecycleQosPolicy::convert(const DDS::WriterDataLifecycleQosPolicy& source, WriterDataLifecycleQosPolicy target) {
	bool b = (bool)source.autodispose_unregistered_instances;
	target.autodispose_unregistered_instances = b;
}
OpenDDSDataWriterListener::OpenDDSDataWriterListener(dds::DataWriterListener* l) {
	listener = l;
}

OpenDDSDataWriterListener::~OpenDDSDataWriterListener() {
	delete listener;
}

dds::DataWriterListener* OpenDDSDataWriterListener::get_listener() {
	return listener;
}

void OpenDDSDataWriterListener::on_offered_deadline_missed(DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status) {
}
void OpenDDSDataWriterListener::on_offered_incompatible_qos(DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status) {
}
void OpenDDSDataWriterListener::on_liveliness_lost(DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status) {
}
void OpenDDSDataWriterListener::on_publication_matched(DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status) {
}
};
