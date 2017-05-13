#include <stddef.h>
#include <malloc.h>

#include <dds/dcps.h>

#define DEBUG	1

#if DEBUG
#include <iostream>
#endif

namespace dds {

BuiltinTopicKey_t::BuiltinTopicKey_t() {
	for(int i = 0; i < 3; i++)
		this->value[i] = 0;
}

BuiltinTopicKey_t::BuiltinTopicKey_t(BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3]) {
	for(int i = 0; i < 3; i++)
		this->value[i] = value[i];
}

BuiltinTopicKey_t::~BuiltinTopicKey_t() {
}

Duration_t::Duration_t() {
	Duration_t(0, 0);
}

Duration_t::Duration_t(int32_t sec, uint32_t nanosec) {
	this->sec = sec;
	this->nanosec = nanosec;
}

Duration_t::~Duration_t() {
}

Time_t::Time_t() {
	Time_t(0, 0);
}

Time_t::Time_t(int32_t sec, uint32_t nanosec) {
	this->sec = sec;
	this->nanosec = nanosec;
}

Time_t::~Time_t() {
}

InconsistentTopicStatus::InconsistentTopicStatus() {
	InconsistentTopicStatus(0, 0);
}

InconsistentTopicStatus::InconsistentTopicStatus(int32_t total_count, int32_t total_count_change) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
}

InconsistentTopicStatus::~InconsistentTopicStatus() {
}

SampleLostStatus::SampleLostStatus() {
	SampleLostStatus(0, 0);
}

SampleLostStatus::SampleLostStatus(int32_t total_count, int32_t total_count_change) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
}

SampleLostStatus::~SampleLostStatus() {
}

SampleRejectedStatus::SampleRejectedStatus() {
	SampleRejectedStatus(0, 0, NOT_REJECTED, HANDLE_NIL);
}

SampleRejectedStatus::SampleRejectedStatus(
	int32_t total_count, int32_t total_count_change, 
	SampleRejectedStatusKind last_reason, InstanceHandle_t last_instance_handle) {
	
	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->last_reason = last_reason;
	this->last_instance_handle = last_instance_handle;
}

SampleRejectedStatus::~SampleRejectedStatus() {
}

LivelinessLostStatus::LivelinessLostStatus() {
	LivelinessLostStatus(0, 0);
}

LivelinessLostStatus::LivelinessLostStatus(int32_t total_count, int32_t total_count_change) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
}

LivelinessLostStatus::~LivelinessLostStatus() {
}

LivelinessChangedStatus::LivelinessChangedStatus() {
	LivelinessChangedStatus(0, 0, 0, 0, HANDLE_NIL);
}

LivelinessChangedStatus::LivelinessChangedStatus(int32_t alive_count, int32_t not_alive_count, 
	int32_t alive_count_change, int32_t not_alive_count_change, InstanceHandle_t last_publication_handle) {
	
	this->alive_count = alive_count;
	this->not_alive_count = not_alive_count;
	this->alive_count_change = alive_count_change;
	this->not_alive_count_change = not_alive_count_change;
	this->last_publication_handle = last_publication_handle;
}

LivelinessChangedStatus::~LivelinessChangedStatus() {
}

OfferedDeadlineMissedStatus::OfferedDeadlineMissedStatus() {
	OfferedDeadlineMissedStatus(0, 0, HANDLE_NIL);
}

OfferedDeadlineMissedStatus::OfferedDeadlineMissedStatus(int32_t total_count, 
	int32_t total_count_change, InstanceHandle_t last_instance_handle) {

	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->last_instance_handle = last_instance_handle;
}

OfferedDeadlineMissedStatus::~OfferedDeadlineMissedStatus() {
}

RequestedDeadlineMissedStatus::RequestedDeadlineMissedStatus() {
	RequestedDeadlineMissedStatus(0, 0, HANDLE_NIL);
}

RequestedDeadlineMissedStatus::RequestedDeadlineMissedStatus(int32_t total_count, 
	int32_t total_count_change, InstanceHandle_t last_instance_handle) {
	
	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->last_instance_handle = last_instance_handle;
}

RequestedDeadlineMissedStatus::~RequestedDeadlineMissedStatus() {
}

QosPolicyCount::QosPolicyCount() {
	QosPolicyCount(0, 0);
}

QosPolicyCount::QosPolicyCount(QosPolicyId_t policy_id, int32_t count) {
	this->policy_id = policy_id;
	this->count = count;
}

QosPolicyCount::~QosPolicyCount() {
}

OfferedIncompatibleQosStatus::OfferedIncompatibleQosStatus() {
	OfferedIncompatibleQosStatus(0, 0, 0, NULL);
}

OfferedIncompatibleQosStatus::OfferedIncompatibleQosStatus(
	int32_t total_count, int32_t total_count_change, 
	QosPolicyId_t last_policy_id, QosPolicyCountSeq* policies) {
	
	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->last_policy_id = last_policy_id;
	this->policies = policies;
}

OfferedIncompatibleQosStatus::~OfferedIncompatibleQosStatus() {
}

RequestedIncompatibleQosStatus::RequestedIncompatibleQosStatus() {
	RequestedIncompatibleQosStatus(0, 0, 0, NULL);
}

RequestedIncompatibleQosStatus::RequestedIncompatibleQosStatus(
	int32_t total_count, int32_t total_count_change,
	QosPolicyId_t last_policy_id, QosPolicyCountSeq* policies) {
	
	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->last_policy_id = last_policy_id;
	this->policies = policies;
}

RequestedIncompatibleQosStatus::~RequestedIncompatibleQosStatus() {
}

PublicationMatchedStatus::PublicationMatchedStatus() {
	PublicationMatchedStatus(0, 0, 0, 0, HANDLE_NIL);
}

PublicationMatchedStatus::PublicationMatchedStatus(int32_t total_count, int32_t total_count_change,
	int32_t current_count, int32_t current_count_change, InstanceHandle_t last_subscription_handle) {
	
	total_count = total_count;		  
	total_count_change = total_count_change;
	current_count = current_count;
	current_count_change = current_count_change;
	last_subscription_handle = last_subscription_handle;
}

PublicationMatchedStatus::~PublicationMatchedStatus() {
}

SubscriptionMatchedStatus::SubscriptionMatchedStatus() {
	SubscriptionMatchedStatus(0, 0, 0, 0, HANDLE_NIL);
}

SubscriptionMatchedStatus::SubscriptionMatchedStatus(
	int32_t total_count, int32_t total_count_change, int32_t current_count,
	int32_t current_count_change, InstanceHandle_t last_publication_handle) {
	
	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->current_count = current_count;
	this->current_count_change = current_count_change;
	this->last_publication_handle = last_publication_handle;
}

SubscriptionMatchedStatus::~SubscriptionMatchedStatus() {
}

Listener::Listener() {
}

Listener::~Listener() {
}

TopicListener::TopicListener() {
}

TopicListener::~TopicListener() {
}

void TopicListener::on_inconsistent_topic(const Topic* the_topic, const InconsistentTopicStatus* status) {
}

DataWriterListener::DataWriterListener() {
}

DataWriterListener::~DataWriterListener() {
}

void DataWriterListener::on_offered_deadline_missed(
	const DataWriter* writer, 
	const OfferedDeadlineMissedStatus* status) {
}

void DataWriterListener::on_offered_incompatible_qos(
	const DataWriter* writer, 
	const OfferedIncompatibleQosStatus* status) {
}

void DataWriterListener::on_liveliness_lost(
	const DataWriter* writer, 
	const LivelinessLostStatus* status) {
}

void DataWriterListener::on_publication_matched(
	const DataWriter* writer, 
	const PublicationMatchedStatus* status) {
}

PublisherListener::PublisherListener() {
}

PublisherListener::~PublisherListener() {
}

DataReaderListener::DataReaderListener() {
}

DataReaderListener::~DataReaderListener() {
}

void DataReaderListener::on_requested_deadline_missed(
	const DataReader* the_reader, 
	const RequestedDeadlineMissedStatus* status) {
}

void DataReaderListener::on_requested_incompatible_qos(
	const DataReader* the_reader, 
	const RequestedIncompatibleQosStatus* status) {
}

void DataReaderListener::on_sample_rejected(
	const DataReader* the_reader,
	const SampleRejectedStatus* status) {
}

void DataReaderListener::on_liveliness_changed(
	const DataReader* the_reader,
	const LivelinessChangedStatus* status) {
}

void DataReaderListener::on_data_available(
	const DataReader* the_reader) {
}

void DataReaderListener::on_subscription_matched(
	const DataReader* the_reader,
	const SubscriptionMatchedStatus* status) {
}

void DataReaderListener::on_sample_lost(
	const DataReader* the_reader,
	const SampleLostStatus* status) {
}

SubscriberListener::SubscriberListener() {
}

SubscriberListener::~SubscriberListener() {
}

void SubscriberListener::on_data_on_readers(const Subscriber* the_subscriber) {
}

DomainParticipantListener::DomainParticipantListener() {
}

DomainParticipantListener::~DomainParticipantListener() {
}

const char* USERDATA_QOS_POLICY_NAME			= "UserData";
const char* DURABILITY_QOS_POLICY_NAME			= "Durability";
const char* PRESENTATION_QOS_POLICY_NAME		= "Presentation";
const char* DEADLINE_QOS_POLICY_NAME			= "Deadline";
const char* LATENCYBUDGET_QOS_POLICY_NAME		= "LatencyBudget";
const char* OWNERSHIP_QOS_POLICY_NAME			= "Ownership";
const char* OWNERSHIPSTRENGTH_QOS_POLICY_NAME		= "OwnershipStrength";
const char* LIVELINESS_QOS_POLICY_NAME			= "Liveliness";
const char* TIMEBASEDFILTER_QOS_POLICY_NAME		= "TimeBasedFilter";
const char* PARTITION_QOS_POLICY_NAME			= "Partition";
const char* RELIABILITY_QOS_POLICY_NAME			= "Reliability";
const char* DESTINATIONORDER_QOS_POLICY_NAME		= "DestinationOrder";
const char* HISTORY_QOS_POLICY_NAME			= "History";
const char* RESOURCELIMITS_QOS_POLICY_NAME		= "ResourceLimits";
const char* ENTITYFACTORY_QOS_POLICY_NAME		= "EntityFactory";
const char* WRITERDATALIFECYCLE_QOS_POLICY_NAME		= "WriterDataLifecycle";
const char* READERDATALIFECYCLE_QOS_POLICY_NAME		= "ReaderDataLifecycle";
const char* TOPICDATA_QOS_POLICY_NAME			= "TopicData";
const char* GROUPDATA_QOS_POLICY_NAME			= "TransportPriority";
const char* LIFESPAN_QOS_POLICY_NAME			= "Lifespan";
const char* DURABILITYSERVICE_POLICY_NAME		= "DurabilityService";

}
