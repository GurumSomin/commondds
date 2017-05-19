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

Condition::Condition() {
}

Condition::~Condition() {
}

bool Condition::get_trigger_value() {
}

WaitSet::WaitSet() {
}

WaitSet::~WaitSet() {
}

ReturnCode_t WaitSet::wait(ConditionSeq* active_conditions, const Duration_t* timeout) {
	return RETCODE_ERROR;
}

ReturnCode_t WaitSet::attach_condition(const Condition* cond) {
	return RETCODE_ERROR;
}

ReturnCode_t WaitSet::detach_condition(const Condition* cond) {
	return RETCODE_ERROR;
}

ReturnCode_t WaitSet::get_conditions(ConditionSeq* attached_conditions) {
	return RETCODE_ERROR;
}

GuardCondition::GuardCondition() {
}

GuardCondition::~GuardCondition() {
}

ReturnCode_t GuardCondition::set_trigger_value(bool value) {
	return RETCODE_ERROR;
}

StatusCondition::StatusCondition() {
}

StatusCondition::~StatusCondition() {
}

StatusMask* StatusCondition::get_enabled_statuses() {
	return NULL;
}

ReturnCode_t StatusCondition::set_enabled_statuses(const StatusMask* mask) {
	return RETCODE_ERROR;
}

Entity* StatusCondition::get_entity() {
	return NULL;
}

ReadCondition::ReadCondition() {
}

ReadCondition::~ReadCondition() {
}

SampleStateMask* ReadCondition::get_sample_state_mask() {
	return NULL;
}

ViewStateMask* ReadCondition::get_view_state_mask() {
	return NULL;
}

InstanceStateMask* ReadCondition::get_instance_state_mask() {
	return NULL;
}

DataReader* ReadCondition::get_datareader() {
	return NULL;
}

QueryCondition::QueryCondition() {
}

QueryCondition::~QueryCondition() {
}

char* QueryCondition::get_query_expression() {
	return NULL;
}

ReturnCode_t QueryCondition::get_query_parameters(StringSeq* query_parameters) {
	return RETCODE_ERROR;
}

ReturnCode_t QueryCondition::set_query_parameters(const StringSeq* query_parameters) {
	return RETCODE_ERROR;
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

UserDataQosPolicy::UserDataQosPolicy() {
	value = new sequence<uint8_t>();
}

UserDataQosPolicy::UserDataQosPolicy(sequence<uint8_t>* value) {
	this->value = value;
}

UserDataQosPolicy::UserDataQosPolicy(uint8_t* array, uint32_t size) {
	this->value = new sequence<uint8_t>(array, size);
}

UserDataQosPolicy::~UserDataQosPolicy() {
	delete value;
}

TopicDataQosPolicy::TopicDataQosPolicy() {
	value = new sequence<uint8_t>();
}

TopicDataQosPolicy::TopicDataQosPolicy(sequence<uint8_t>* value) {
	this->value = value;
}

TopicDataQosPolicy::TopicDataQosPolicy(uint8_t* array, uint32_t size) {
	this->value = new sequence<uint8_t>(array, size);
}

TopicDataQosPolicy::~TopicDataQosPolicy() {
	delete value;
}

GroupDataQosPolicy::GroupDataQosPolicy() {
	value = new sequence<uint8_t>();
}

GroupDataQosPolicy::GroupDataQosPolicy(sequence<uint8_t>* value) {
	this->value = value;
}

GroupDataQosPolicy::GroupDataQosPolicy(uint8_t* array, uint32_t size) {
	this->value = new sequence<uint8_t>(array, size);
}

GroupDataQosPolicy::~GroupDataQosPolicy() {
	delete value;
}

TransportPriorityQosPolicy::TransportPriorityQosPolicy() {
	value = 0;
}

TransportPriorityQosPolicy::TransportPriorityQosPolicy(int32_t value) {
	this->value = value;
}

TransportPriorityQosPolicy::~TransportPriorityQosPolicy() {
}

LifespanQosPolicy::LifespanQosPolicy() {
	duration = new Duration_t();
}

LifespanQosPolicy::LifespanQosPolicy(Duration_t* duration) {
	this->duration = duration;
}

LifespanQosPolicy::LifespanQosPolicy(int32_t sec, uint32_t nanosec) {
	this->duration = new Duration_t(sec, nanosec);
}

LifespanQosPolicy::~LifespanQosPolicy() {
	delete duration;
}

DurabilityQosPolicy::DurabilityQosPolicy() {
	kind = VOLATILE_DURABILITY_QOS;
}

DurabilityQosPolicy::DurabilityQosPolicy(DurabilityQosPolicyKind kind) {
	this->kind = kind;
}

DurabilityQosPolicy::~DurabilityQosPolicy() {
}

PresentationQosPolicy::PresentationQosPolicy() {
	access_scope = INSTANCE_PRESENTATION_QOS;
	coherent_access = false;
	ordered_access = false;
}

PresentationQosPolicy::PresentationQosPolicy(PresentationQosPolicyAccessScopeKind access_scope, bool coherent_access, bool ordered_access) {
	this->access_scope = access_scope;
	this->coherent_access = coherent_access;
	this->ordered_access = ordered_access;
}

PresentationQosPolicy::~PresentationQosPolicy() {
}

DeadlineQosPolicy::DeadlineQosPolicy(Duration_t* period) {
	this->period = period;
}

DeadlineQosPolicy::DeadlineQosPolicy(int32_t sec, uint32_t nanosec) {
	this->period = new Duration_t(sec, nanosec);
}

DeadlineQosPolicy::~DeadlineQosPolicy() {
	delete period;
}

LatencyBudgetQosPolicy::LatencyBudgetQosPolicy() {
	duration = new Duration_t();
}

LatencyBudgetQosPolicy::LatencyBudgetQosPolicy(Duration_t* duration) {
	this->duration = duration;
}

LatencyBudgetQosPolicy::LatencyBudgetQosPolicy(int32_t sec, uint32_t nanosec) {
	this->duration = new Duration_t(sec, nanosec);
}

LatencyBudgetQosPolicy::~LatencyBudgetQosPolicy() {
	delete duration;
}

OwnershipQosPolicy::OwnershipQosPolicy() {
	kind = SHARED_OWNERSHIP_QOS;
}

OwnershipQosPolicy::OwnershipQosPolicy(OwnershipQosPolicyKind kind) {
	this->kind = kind;
}

OwnershipQosPolicy::~OwnershipQosPolicy() {
}

OwnershipStrengthQosPolicy::OwnershipStrengthQosPolicy() {
	value = 0;
}

OwnershipStrengthQosPolicy::OwnershipStrengthQosPolicy(int32_t value) {
	this->value = value;
}

OwnershipStrengthQosPolicy::~OwnershipStrengthQosPolicy() {
}

LivelinessQosPolicy::LivelinessQosPolicy() {
	kind = AUTOMATIC_LIVELINESS_QOS;
	lease_duration = new Duration_t();
}

LivelinessQosPolicy::LivelinessQosPolicy(LivelinessQosPolicyKind kind, Duration_t* lease_duration) {
	this->kind = kind;
	this->lease_duration = lease_duration;
}

LivelinessQosPolicy::LivelinessQosPolicy(LivelinessQosPolicyKind kind, int32_t lease_duration_sec, uint32_t lease_duration_nanosec) {
	this->kind = kind;
	this->lease_duration = new Duration_t(lease_duration_sec, lease_duration_nanosec);
}

LivelinessQosPolicy::~LivelinessQosPolicy() {
	delete lease_duration;
}

TimeBasedFilterQosPolicy::TimeBasedFilterQosPolicy() {
	minimum_separation = new Duration_t();
}

TimeBasedFilterQosPolicy::TimeBasedFilterQosPolicy(Duration_t* minimum_separation) {
	this->minimum_separation = minimum_separation;
}

TimeBasedFilterQosPolicy::TimeBasedFilterQosPolicy(int32_t minimum_separation_sec, int32_t minimum_separation_nanosec) {
	this->minimum_separation = new Duration_t(minimum_separation_sec, minimum_separation_nanosec);
}

TimeBasedFilterQosPolicy::~TimeBasedFilterQosPolicy() {
	delete minimum_separation;
}

PartitionQosPolicy::PartitionQosPolicy() {
	name = new StringSeq();
}

PartitionQosPolicy::PartitionQosPolicy(StringSeq* name) {
	this->name = name;
}

PartitionQosPolicy::~PartitionQosPolicy() {
	delete name;
}

ReliabilityQosPolicy::ReliabilityQosPolicy() {
	kind = BEST_EFFORT_RELIABILITY_QOS;
	max_blocking_time = new Duration_t();
}

ReliabilityQosPolicy::ReliabilityQosPolicy(ReliabilityQosPolicyKind kind, Duration_t* max_blocking_time) {
	this->kind = kind;
	this->max_blocking_time = max_blocking_time;
}

ReliabilityQosPolicy::ReliabilityQosPolicy(ReliabilityQosPolicyKind kind, int32_t max_blocking_time_sec, int32_t max_blocking_time_nanosec) {
	this->kind = kind;
	this->max_blocking_time = new Duration_t(max_blocking_time_sec, max_blocking_time_nanosec);
}

ReliabilityQosPolicy::~ReliabilityQosPolicy() {
	delete max_blocking_time;
}

DestinationOrderQosPolicy::DestinationOrderQosPolicy() {
	kind = BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
}

DestinationOrderQosPolicy::DestinationOrderQosPolicy(DestinationOrderQosPolicyKind kind) {
	this->kind = kind;
}

DestinationOrderQosPolicy::~DestinationOrderQosPolicy() {
}

HistoryQosPolicy::HistoryQosPolicy() {
	kind = KEEP_LAST_HISTORY_QOS;
	depth = 0;
}

HistoryQosPolicy::HistoryQosPolicy(HistoryQosPolicyKind kind, int32_t depth) {
	this->kind = kind;
	this->depth = depth;
}

HistoryQosPolicy::~HistoryQosPolicy() {
}

ResourceLimitsQosPolicy::ResourceLimitsQosPolicy() {
	max_samples = 0;
	max_instances = 0;
	max_samples_per_instance = 0;
}

ResourceLimitsQosPolicy::ResourceLimitsQosPolicy(int32_t max_samples, int32_t max_instances, int32_t max_samples_per_instance) {
	this->max_samples = max_samples;
	this->max_instances = max_instances;
	this->max_samples_per_instance = max_samples_per_instance;
}

ResourceLimitsQosPolicy::~ResourceLimitsQosPolicy() {
}

EntityFactoryQosPolicy::EntityFactoryQosPolicy() {
	autoenable_created_entities = false;
}

EntityFactoryQosPolicy::EntityFactoryQosPolicy(bool autoenable_created_entities) {
	this->autoenable_created_entities = autoenable_created_entities;
}

EntityFactoryQosPolicy::~EntityFactoryQosPolicy() {
}

WriterDataLifecycleQosPolicy::WriterDataLifecycleQosPolicy() {
	autodispose_unregistered_instances = false;
}

WriterDataLifecycleQosPolicy::WriterDataLifecycleQosPolicy(bool autoenable_unregistered_instances) {
	this->autodispose_unregistered_instances = autodispose_unregistered_instances;
}

WriterDataLifecycleQosPolicy::~WriterDataLifecycleQosPolicy() {
}

ReaderDataLifecycleQosPolicy::ReaderDataLifecycleQosPolicy() {
	autopurge_nowriter_samples_delay = new Duration_t();
	autopurge_disposed_samples_delay = new Duration_t();
}

ReaderDataLifecycleQosPolicy::ReaderDataLifecycleQosPolicy(
	Duration_t* autopurge_nowriter_samples_delay,
	Duration_t* autopurge_disposed_samples_delay) {
	
	this->autopurge_nowriter_samples_delay = autopurge_nowriter_samples_delay;
	this->autopurge_disposed_samples_delay = autopurge_disposed_samples_delay;
}

ReaderDataLifecycleQosPolicy::ReaderDataLifecycleQosPolicy(
	int32_t autopurge_nowriter_samples_delay_sec,
	int32_t autopurge_nowriter_samples_delay_nanosec,
	int32_t autopurge_disposed_samples_delay_sec,
	int32_t autopurge_disposed_samples_delay_nanosec) {
	
	this->autopurge_nowriter_samples_delay = new Duration_t(
		autopurge_nowriter_samples_delay_sec, 
		autopurge_nowriter_samples_delay_nanosec);
	this->autopurge_disposed_samples_delay = new Duration_t(
		autopurge_disposed_samples_delay_sec,
		autopurge_disposed_samples_delay_nanosec);
}

ReaderDataLifecycleQosPolicy::~ReaderDataLifecycleQosPolicy() {
	delete autopurge_nowriter_samples_delay;
	delete autopurge_disposed_samples_delay;
}

DurabilityServiceQosPolicy::DurabilityServiceQosPolicy() {
	service_cleanup_delay = new Duration_t();
	history_kind = KEEP_LAST_HISTORY_QOS,
	history_depth = 0;
	max_samples = 0;
	max_instances = 0;
	max_samples_per_instance = 0;
}

DurabilityServiceQosPolicy::DurabilityServiceQosPolicy(
	Duration_t* service_cleanup_delay,
	HistoryQosPolicyKind history_kind,
	int32_t history_depth,
	int32_t max_samples,
	int32_t max_instances,
	int32_t max_samples_per_instance) {
	
	this->service_cleanup_delay  = service_cleanup_delay;
	this->history_kind  = history_kind;
	this->history_depth = history_depth;
	this->max_samples = max_samples;
	this->max_instances = max_instances;
	this->max_samples_per_instance = max_samples_per_instance;
}

DurabilityServiceQosPolicy::~DurabilityServiceQosPolicy() {
	delete service_cleanup_delay;
}


}
