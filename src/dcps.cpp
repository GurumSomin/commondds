#include <stddef.h>
#include <malloc.h>

#include <cstdlib>
#include <fstream>
#include <stdexcept>

#include <json/json.h>

#include <dds/dcps.h>
#include <dds/connext.h>

#define DEBUG	1

#if DEBUG
#include <stdio.h>
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

StatusMask StatusCondition::get_enabled_statuses() {
	return 0;
}

ReturnCode_t StatusCondition::set_enabled_statuses(const StatusMask mask) {
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

std::string* QueryCondition::get_query_expression() {
	return NULL;
}

ReturnCode_t QueryCondition::get_query_parameters(StringSeq* query_parameters) {
	return RETCODE_ERROR;
}

ReturnCode_t QueryCondition::set_query_parameters(const StringSeq* query_parameters) {
	return RETCODE_ERROR;
}

const std::string* USERDATA_QOS_POLICY_NAME				= new std::string("UserData");
const std::string* DURABILITY_QOS_POLICY_NAME			= new std::string("Durability");
const std::string* PRESENTATION_QOS_POLICY_NAME			= new std::string("Presentation");
const std::string* DEADLINE_QOS_POLICY_NAME				= new std::string("Deadline");
const std::string* LATENCYBUDGET_QOS_POLICY_NAME		= new std::string("LatencyBudget");
const std::string* OWNERSHIP_QOS_POLICY_NAME			= new std::string("Ownership");
const std::string* OWNERSHIPSTRENGTH_QOS_POLICY_NAME	= new std::string("OwnershipStrength");
const std::string* LIVELINESS_QOS_POLICY_NAME			= new std::string("Liveliness");
const std::string* TIMEBASEDFILTER_QOS_POLICY_NAME		= new std::string("TimeBasedFilter");
const std::string* PARTITION_QOS_POLICY_NAME			= new std::string("Partition");
const std::string* RELIABILITY_QOS_POLICY_NAME			= new std::string("Reliability");
const std::string* DESTINATIONORDER_QOS_POLICY_NAME		= new std::string("DestinationOrder");
const std::string* HISTORY_QOS_POLICY_NAME				= new std::string("History");
const std::string* RESOURCELIMITS_QOS_POLICY_NAME		= new std::string("ResourceLimits");
const std::string* ENTITYFACTORY_QOS_POLICY_NAME		= new std::string("EntityFactory");
const std::string* WRITERDATALIFECYCLE_QOS_POLICY_NAME	= new std::string("WriterDataLifecycle");
const std::string* READERDATALIFECYCLE_QOS_POLICY_NAME	= new std::string("ReaderDataLifecycle");
const std::string* TOPICDATA_QOS_POLICY_NAME			= new std::string("TopicData");
const std::string* GROUPDATA_QOS_POLICY_NAME			= new std::string("TransportPriority");
const std::string* LIFESPAN_QOS_POLICY_NAME				= new std::string("Lifespan");
const std::string* DURABILITYSERVICE_POLICY_NAME		= new std::string("DurabilityService");

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

DeadlineQosPolicy::DeadlineQosPolicy() {
	DeadlineQosPolicy(0, 0);
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

LivelinessQosPolicy::~LivelinessQosPolicy() {
	delete lease_duration;
}

TimeBasedFilterQosPolicy::TimeBasedFilterQosPolicy() {
	minimum_separation = new Duration_t();
}

TimeBasedFilterQosPolicy::TimeBasedFilterQosPolicy(Duration_t* minimum_separation) {
	this->minimum_separation = minimum_separation;
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

DomainParticipantFactoryQos::DomainParticipantFactoryQos() {
	entity_factory = new EntityFactoryQosPolicy();
}

DomainParticipantFactoryQos::DomainParticipantFactoryQos(EntityFactoryQosPolicy* entity_factory) {
	this->entity_factory = entity_factory;
}

DomainParticipantFactoryQos::~DomainParticipantFactoryQos() {
}

DomainParticipantQos::DomainParticipantQos() {
	user_data = new UserDataQosPolicy();
	entity_factory = new EntityFactoryQosPolicy();
}

DomainParticipantQos::DomainParticipantQos(UserDataQosPolicy* user_data, EntityFactoryQosPolicy* entity_factory) {
	this->user_data = user_data;
	this->entity_factory = entity_factory;
}

DomainParticipantQos::~DomainParticipantQos() {
	delete entity_factory;
	delete user_data;
}

TopicQos::TopicQos() {
	topic_data = new TopicDataQosPolicy();
	durability = new DurabilityQosPolicy();
	durability_service = new DurabilityServiceQosPolicy();
	deadline = new DeadlineQosPolicy();
	latency_budget = new LatencyBudgetQosPolicy();
	liveliness = new LivelinessQosPolicy();
	reliability = new ReliabilityQosPolicy();
	destination_order = new DestinationOrderQosPolicy();
	history = new HistoryQosPolicy();
	resource_limits = new ResourceLimitsQosPolicy();
	transport_priority = new TransportPriorityQosPolicy();
	lifespan = new LifespanQosPolicy();
	ownership = new OwnershipQosPolicy();
}

TopicQos::TopicQos(
	TopicDataQosPolicy* topic_data,
	DurabilityQosPolicy* durability,
	DurabilityServiceQosPolicy* durability_service,
	DeadlineQosPolicy* deadline,
	LatencyBudgetQosPolicy* latency_budget,
	LivelinessQosPolicy* liveliness,
	ReliabilityQosPolicy* reliability,
	DestinationOrderQosPolicy* destination_order,
	HistoryQosPolicy* history,
	ResourceLimitsQosPolicy* resource_limits,
	TransportPriorityQosPolicy* transport_priority,
	LifespanQosPolicy* lifespan,
	OwnershipQosPolicy* ownership) {
	
	this->topic_data = topic_data;
	this->durability = durability;
	this->durability_service = durability_service;
	this->deadline = deadline;
	this->latency_budget = latency_budget;
	this->liveliness = liveliness;
	this->reliability = reliability;
	this->destination_order = destination_order;
	this->history = history;
	this->resource_limits = resource_limits;
	this->transport_priority = transport_priority;
	this->lifespan = lifespan;
	this->ownership = ownership;
}

TopicQos::~TopicQos() {
	delete topic_data;
	delete durability;
	delete durability_service;
	delete deadline;
	delete latency_budget;
	delete liveliness;
	delete reliability;
	delete destination_order;
	delete history;
	delete resource_limits;
	delete transport_priority;
	delete lifespan;
	delete ownership;
}

DataWriterQos::DataWriterQos() {
	durability = new DurabilityQosPolicy();
	durability_service = new DurabilityServiceQosPolicy();
	deadline = new DeadlineQosPolicy();
	latency_budget = new LatencyBudgetQosPolicy();
	liveliness = new LivelinessQosPolicy();
	reliability = new ReliabilityQosPolicy();
	destination_order = new DestinationOrderQosPolicy();
	history = new HistoryQosPolicy();
	resource_limits = new ResourceLimitsQosPolicy();
	transport_priority = new TransportPriorityQosPolicy();
	lifespan = new LifespanQosPolicy();
	user_data = new UserDataQosPolicy();
	ownership = new OwnershipQosPolicy();
	ownership_strength = new OwnershipStrengthQosPolicy();
	writer_data_lifecycle = new WriterDataLifecycleQosPolicy();
}

DataWriterQos::DataWriterQos(
	DurabilityQosPolicy* durability,
	DurabilityServiceQosPolicy* durability_service,
	DeadlineQosPolicy* deadline,
	LatencyBudgetQosPolicy* latency_budget,
	LivelinessQosPolicy* liveliness,
	ReliabilityQosPolicy* reliability,
	DestinationOrderQosPolicy* destination_order,
	HistoryQosPolicy* history,
	ResourceLimitsQosPolicy* resource_limits,
	TransportPriorityQosPolicy* transport_priority,
	LifespanQosPolicy* lifespan,
	UserDataQosPolicy* user_data,
	OwnershipQosPolicy* ownership,
	OwnershipStrengthQosPolicy* ownership_strength,
	WriterDataLifecycleQosPolicy* writer_data_lifecycle) {
	
	this->durability = durability;
	this->durability_service = durability_service;
	this->deadline = deadline;
	this->latency_budget = latency_budget;
	this->liveliness = liveliness;
	this->reliability = reliability;
	this->destination_order = destination_order;
	this->history = history;
	this->resource_limits = resource_limits;
	this->transport_priority = transport_priority;
	this->lifespan = lifespan;
	this->user_data = user_data;
	this->ownership = ownership;
	this->ownership_strength = ownership_strength;
	this->writer_data_lifecycle = writer_data_lifecycle;
}

DataWriterQos::~DataWriterQos() {
	delete durability;
	delete durability_service;
	delete deadline;
	delete latency_budget;
	delete liveliness;
	delete reliability;
	delete destination_order;
	delete history;
	delete resource_limits;
	delete transport_priority;
	delete lifespan;
	delete user_data;
	delete ownership;
	delete ownership_strength;
	delete writer_data_lifecycle;
}

PublisherQos::PublisherQos() {
	presentation = new PresentationQosPolicy();
	partition = new PartitionQosPolicy();
	group_data = new GroupDataQosPolicy();
	entity_factory = new EntityFactoryQosPolicy();
}

PublisherQos::PublisherQos(
	PresentationQosPolicy* presentation,
	PartitionQosPolicy* partition,
	GroupDataQosPolicy* group_data,
	EntityFactoryQosPolicy* entity_factory) {
	
	this->presentation = presentation;
	this->partition = partition;
	this->group_data = group_data;
	this->entity_factory = entity_factory;
}

PublisherQos::~PublisherQos() {
	delete presentation;
	delete partition;
	delete group_data;
	delete entity_factory;
}

DataReaderQos::DataReaderQos() {
	durability = new DurabilityQosPolicy();
	deadline = new DeadlineQosPolicy();
	latency_budget = new LatencyBudgetQosPolicy();
	liveliness = new LivelinessQosPolicy();
	reliability = new ReliabilityQosPolicy();
	destination_order = new DestinationOrderQosPolicy();
	history = new HistoryQosPolicy();
	resource_limits = new ResourceLimitsQosPolicy();
	user_data = new UserDataQosPolicy();
	ownership = new OwnershipQosPolicy();
	time_based_filter = new TimeBasedFilterQosPolicy();
	reader_data_lifecycle = new ReaderDataLifecycleQosPolicy();
}

DataReaderQos::DataReaderQos(
	DurabilityQosPolicy* durability,
	DeadlineQosPolicy* deadline,
	LatencyBudgetQosPolicy* latency_budget,
	LivelinessQosPolicy* liveliness,
	ReliabilityQosPolicy* reliability,
	DestinationOrderQosPolicy* destination_order,
	HistoryQosPolicy* history,
	ResourceLimitsQosPolicy* resource_limits,
	UserDataQosPolicy* user_data,
	OwnershipQosPolicy* ownership,
	TimeBasedFilterQosPolicy* time_based_filter,
	ReaderDataLifecycleQosPolicy* reader_data_lifecycle) {
	
	this->durability = durability;
	this->deadline = deadline;
	this->latency_budget = latency_budget;
	this->liveliness = liveliness;
	this->reliability = reliability;
	this->destination_order = destination_order;
	this->history = history;
	this->resource_limits = resource_limits;
	this->user_data = user_data;
	this->ownership = ownership;
	this->time_based_filter = time_based_filter;
	this->reader_data_lifecycle = reader_data_lifecycle;
}

DataReaderQos::~DataReaderQos() {
	delete durability;
	delete deadline;
	delete latency_budget;
	delete liveliness;
	delete reliability;
	delete destination_order;
	delete history;
	delete resource_limits;
	delete user_data;
	delete ownership;
	delete time_based_filter;
	delete reader_data_lifecycle;
}

SubscriberQos::SubscriberQos() {
	presentation = new PresentationQosPolicy();
	partition = new PartitionQosPolicy();
	group_data = new GroupDataQosPolicy();
	entity_factory = new EntityFactoryQosPolicy();
}

SubscriberQos::SubscriberQos(
	PresentationQosPolicy* presentation,
	PartitionQosPolicy* partition,
	GroupDataQosPolicy* group_data,
	EntityFactoryQosPolicy* entity_factory) {
	
	this->presentation = presentation;
	this->partition = partition;
	this->group_data = group_data;
	this->entity_factory = entity_factory;
}

SubscriberQos::~SubscriberQos() {
	delete presentation;
	delete partition;
	delete group_data;
	delete entity_factory;
}

ParticipantBuiltinTopicData::ParticipantBuiltinTopicData() {
	key = HANDLE_NIL;
	user_data = new UserDataQosPolicy();
}

ParticipantBuiltinTopicData::ParticipantBuiltinTopicData(
	BuiltinTopicKey_t key,
	UserDataQosPolicy* user_data) {

	this->key = key;
	this->user_data = user_data;
}

ParticipantBuiltinTopicData::~ParticipantBuiltinTopicData() {
	delete user_data;
}

TopicBuiltinTopicData::TopicBuiltinTopicData() {
	key = HANDLE_NIL;
	name = NULL;
	type_name = NULL;
	durability = new DurabilityQosPolicy();
	durability_service = new DurabilityServiceQosPolicy();
	deadline = new DeadlineQosPolicy();
	latency_budget = new LatencyBudgetQosPolicy();
	liveliness = new LivelinessQosPolicy();
	reliability = new ReliabilityQosPolicy();
	transport_priority = new TransportPriorityQosPolicy();
	lifespan = new LifespanQosPolicy();
	destination_order = new DestinationOrderQosPolicy();
	history = new HistoryQosPolicy();
	resource_limits = new ResourceLimitsQosPolicy();
	ownership = new OwnershipQosPolicy();
	topic_data = new TopicDataQosPolicy();
}

TopicBuiltinTopicData::TopicBuiltinTopicData(
	BuiltinTopicKey_t key,
	std::string* name,
	std::string* type_name,
	DurabilityQosPolicy* durability,
	DurabilityServiceQosPolicy* durability_service,
	DeadlineQosPolicy* deadline,
	LatencyBudgetQosPolicy* latency_budget,
	LivelinessQosPolicy* liveliness,
	ReliabilityQosPolicy* reliability,
	TransportPriorityQosPolicy* transport_priority,
	LifespanQosPolicy* lifespan,
	DestinationOrderQosPolicy* destination_order,
	HistoryQosPolicy* history,
	ResourceLimitsQosPolicy* resource_limits,
	OwnershipQosPolicy* ownership,
	TopicDataQosPolicy* topic_data) {
	
	this->key = key;
	this->name = name;
	this->type_name = type_name;
	this->durability = durability;
	this->durability_service = durability_service;
	this->deadline = deadline;
	this->latency_budget = latency_budget;
	this->liveliness = liveliness;
	this->reliability = reliability;
	this->transport_priority = transport_priority;
	this->lifespan = lifespan;
	this->destination_order = destination_order;
	this->history = history;
	this->resource_limits = resource_limits;
	this->ownership = ownership;
	this->topic_data = topic_data;
}

TopicBuiltinTopicData::~TopicBuiltinTopicData() {
	delete durability;
	delete durability_service;
	delete deadline;
	delete latency_budget;
	delete liveliness;
	delete reliability;
	delete transport_priority;
	delete lifespan;
	delete destination_order;
	delete history;
	delete resource_limits;
	delete ownership;
	delete topic_data;
}

PublicationBuiltinTopicData::PublicationBuiltinTopicData() {
	key = HANDLE_NIL;
	participant_key = HANDLE_NIL;
	topic_name = NULL;
	type_name = NULL;
	durability = new DurabilityQosPolicy();
	durability_service = new DurabilityServiceQosPolicy();
	deadline = new DeadlineQosPolicy();
	latency_budget = new LatencyBudgetQosPolicy();
	liveliness = new LivelinessQosPolicy();
	reliability = new ReliabilityQosPolicy();
	lifespan = new LifespanQosPolicy();
	user_data = new UserDataQosPolicy();
	ownership = new OwnershipQosPolicy();
	ownership_strength = new OwnershipStrengthQosPolicy();
	destination_order = new DestinationOrderQosPolicy();
	presentation = new PresentationQosPolicy();
	partition = new PartitionQosPolicy();
	topic_data = new TopicDataQosPolicy();
	group_data = new GroupDataQosPolicy();
}

PublicationBuiltinTopicData::PublicationBuiltinTopicData(
	BuiltinTopicKey_t key,
	BuiltinTopicKey_t participant_key,
	std::string* topic_name,
	std::string* type_name,
	DurabilityQosPolicy* durability,
	DurabilityServiceQosPolicy* durability_service,
	DeadlineQosPolicy* deadline,
	LatencyBudgetQosPolicy* latency_budget,
	LivelinessQosPolicy* liveliness,
	ReliabilityQosPolicy* reliability,
	LifespanQosPolicy* lifespan,
	UserDataQosPolicy* user_data,
	OwnershipQosPolicy* ownership,
	OwnershipStrengthQosPolicy* ownership_strength,
	DestinationOrderQosPolicy* destination_order,
	PresentationQosPolicy* presentation,
	PartitionQosPolicy* partition,
	TopicDataQosPolicy* topic_data,
	GroupDataQosPolicy* group_data) {
	
	this->key = key;
	this->participant_key = participant_key;
	this->topic_name = topic_name;
	this->type_name = type_name;
	this->durability = durability;
	this->durability_service = durability_service;
	this->deadline = deadline;
	this->latency_budget = latency_budget;
	this->liveliness = liveliness;
	this->reliability = reliability;
	this->lifespan = lifespan;
	this->user_data = user_data;
	this->ownership = ownership;
	this->ownership_strength = ownership_strength;
	this->destination_order = destination_order;
	this->presentation = presentation;
	this->partition = partition;
	this->topic_data = topic_data;
	this->group_data = group_data;
}

PublicationBuiltinTopicData::~PublicationBuiltinTopicData() {
	delete durability;
	delete durability_service;
	delete deadline;
	delete latency_budget;
	delete liveliness;
	delete reliability;
	delete lifespan;
	delete user_data;
	delete ownership;
	delete ownership_strength;
	delete destination_order;
	delete presentation;
	delete partition;
	delete topic_data;
	delete group_data;
}

SubscriptionBuiltinTopicData::SubscriptionBuiltinTopicData() {
	key = HANDLE_NIL;
	participant_key = HANDLE_NIL;
	topic_name = NULL;
	type_name = NULL;
	durability = new DurabilityQosPolicy();
	deadline = new DeadlineQosPolicy();
	latency_budget = new LatencyBudgetQosPolicy();
	liveliness = new LivelinessQosPolicy();
	reliability = new ReliabilityQosPolicy();
	ownership = new OwnershipQosPolicy();
	destination_order = new DestinationOrderQosPolicy();
	user_data = new UserDataQosPolicy();
	time_based_filter = new TimeBasedFilterQosPolicy();
	presentation = new PresentationQosPolicy();
	partition = new PartitionQosPolicy();
	topic_data = new TopicDataQosPolicy();
	group_data = new GroupDataQosPolicy();
}

SubscriptionBuiltinTopicData::SubscriptionBuiltinTopicData(
	BuiltinTopicKey_t key,
	BuiltinTopicKey_t participant_key,
	std::string* topic_name,
	std::string* type_name,
	DurabilityQosPolicy* durability,
	DeadlineQosPolicy* deadline,
	LatencyBudgetQosPolicy* latency_budget,
	LivelinessQosPolicy* liveliness,
	ReliabilityQosPolicy* reliability,
	OwnershipQosPolicy* ownership,
	DestinationOrderQosPolicy* destination_order,
	UserDataQosPolicy* user_data,
	TimeBasedFilterQosPolicy* time_based_filter,
	PresentationQosPolicy* presentation,
	PartitionQosPolicy* partition,
	TopicDataQosPolicy* topic_data,
	GroupDataQosPolicy* group_data) {

	this->key = key;
	this->participant_key = participant_key;
	this->topic_name = topic_name;
	this->type_name = type_name;
	this->durability = durability;
	this->deadline = deadline;
	this->latency_budget = latency_budget;
	this->liveliness = liveliness;
	this->reliability = reliability;
	this->ownership = ownership;
	this->destination_order = destination_order;
	this->user_data = user_data;
	this->time_based_filter = time_based_filter;
	this->presentation = presentation;
	this->partition = partition;
	this->topic_data = topic_data;
	this->group_data = group_data;
}

SubscriptionBuiltinTopicData::~SubscriptionBuiltinTopicData() {
	delete durability;
	delete deadline;
	delete latency_budget;
	delete liveliness;
	delete reliability;
	delete ownership;
	delete destination_order;
	delete user_data;
	delete time_based_filter;
	delete presentation;
	delete partition;
	delete topic_data;
	delete group_data;
}

Entity::Entity() {
}

Entity::~Entity() {
}

ReturnCode_t Entity::enable() {
	return RETCODE_ERROR;
}

StatusCondition* Entity::get_statuscondition() {
	return NULL;
}

StatusMask Entity::get_status_changes() {
	return 0;
}

InstanceHandle_t Entity::get_instance_handle() {
	return HANDLE_NIL;
}

DomainParticipant::DomainParticipant() {
}

DomainParticipant::~DomainParticipant() {
}


Publisher* DomainParticipant::create_publisher(
	const PublisherQos* qos,
	const PublisherListener* a_listener,
	const StatusMask mask) {

	return NULL;
}

ReturnCode_t DomainParticipant::delete_publisher(const Publisher* p) {
	return RETCODE_ERROR;
}

Subscriber* DomainParticipant::create_subscriber(
	const SubscriberQos* qos,
	const SubscriberListener* a_listener,
	const StatusMask mask) {

	return NULL;
}

ReturnCode_t DomainParticipant::delete_subscriber(const Subscriber* s) {
	return RETCODE_ERROR;
}

Subscriber* DomainParticipant::get_builtin_subscriber() {
	return NULL;
}

Topic* DomainParticipant::create_topic(
	const std::string* topic_name,
	const std::string* type_name,
	const TopicQos* qos,
	const TopicListener* a_listener,
	const StatusMask mask) {

	return NULL;
}

ReturnCode_t DomainParticipant::delete_topic(const Topic* a_topic) {
	return RETCODE_ERROR;
}

Topic* DomainParticipant::find_topic(const std::string* topic_name, const Duration_t* timeout) {
	return NULL;
}

TopicDescription* DomainParticipant::lookup_topicdescription(const std::string* name) {
	return NULL;
}

ContentFilteredTopic* DomainParticipant::create_contentfilteredtopic(
	const std::string* name,
	const Topic* related_topic,
	const std::string* filter_expression,
	const StringSeq* expression_parameters) {
	return NULL;
}

ReturnCode_t DomainParticipant::delete_contentfilteredtopic(const ContentFilteredTopic* a_contentfilteredtopic) {
	return RETCODE_ERROR;
}

MultiTopic* DomainParticipant::create_multitopic(
	const std::string* name,
	const std::string* type_name,
	const std::string* subscription_expression,
	const StringSeq* expression_parameters) {

	return NULL;
}

ReturnCode_t DomainParticipant::delete_multitopic(const MultiTopic* a_multitopic) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::delete_contained_entities() {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::set_qos(const DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_qos(DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::set_listener(const DomainParticipantListener* a_listener, const StatusMask mask) {
	return RETCODE_ERROR;
}

DomainParticipantListener* DomainParticipant::get_listener() {
	return NULL;
}

ReturnCode_t DomainParticipant::ignore_participant(InstanceHandle_t handle) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::ignore_topic(InstanceHandle_t handle) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::ignore_publication(InstanceHandle_t handle) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::ignore_subscription(InstanceHandle_t handle) {
	return RETCODE_ERROR;
}

DomainId_t DomainParticipant::get_domain_id() {
	return HANDLE_NIL;
}

ReturnCode_t DomainParticipant::assert_liveliness() {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::set_default_publisher_qos(const PublisherQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_default_publisher_qos(PublisherQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::set_default_subscriber_qos(const SubscriberQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_default_subscriber_qos(SubscriberQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::set_default_topic_qos(const TopicQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_default_topic_qos(TopicQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_discovered_participants(InstanceHandleSeq* participant_handles) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_discovered_participant_data(
	ParticipantBuiltinTopicData* participant_data,
	InstanceHandle_t participant_handle) {

	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_discovered_topics(InstanceHandleSeq* topic_handles) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipant::get_discovered_topic_data(TopicBuiltinTopicData* topic_data, InstanceHandle_t topic_handle) {
	return RETCODE_ERROR;
}

bool DomainParticipant::contains_entity(InstanceHandle_t a_handle) {
	return false;
}

ReturnCode_t DomainParticipant::get_current_time(Time_t* current_time) {
	return RETCODE_ERROR;
}

DomainParticipantFactory* DomainParticipantFactory::instance = NULL;
std::string* DomainParticipantFactory::home_path = NULL;
std::string* DomainParticipantFactory::config_path = NULL;
void* DomainParticipantFactory::config = NULL;

DomainParticipantFactory* DomainParticipantFactory::get_instance() {
	if(DomainParticipantFactory::instance == NULL) {
		char* h = std::getenv("COMMONDDS_HOME");
		std::string& home = *new std::string("");
		if(h != NULL) {
			home += h;
		} else {
#if _WIN32 || _WIN64
			home += std::getenv("USERPROFILE");
			home += "\\.commondds";
#else
			home += std::getenv("HOME");
			home += "/.commondds";
#endif
		}

#if _WIN32 || _WIN64
		std::string& config = *new std::string(home);
		config += "\\config.json";
#else
		std::string& config = *new std::string(home);
		config += "/config.json";
#endif
		
#if DEBUG
		std::cout << "home_path: " << home << std::endl;
		std::cout << "config_path: " << config << std::endl;
#endif

		Json::Value& root = *new Json::Value();
		Json::Reader reader;
		try {
			std::ifstream is(config.data());
			reader.parse(is, root);
			is.close();
		} catch(std::ifstream::failure& e) {
#if DEBUG
			std::cout << "exception: " << e.what() << std::endl;
#endif
		}

#if DEBUG
		std::cout << "config: " << root << std::endl;
#endif

		// Set static variables
		DomainParticipantFactory::home_path = &home;
		DomainParticipantFactory::config_path = &config;
		DomainParticipantFactory::config = &root;

		// Instantiate
		// Check primitive configurations
		if(root["middleware"]["type"].isNull()) {
			throw std::runtime_error("config.json: cannot find middleware.type");
		}

		if(!root["middleware"]["type"].isString()) {
			throw std::runtime_error("config.json: middleware.type's type is not a string");
		}

		std::string type = root["middleware"]["type"].asString();
		if(!(type == "connext" || type == "opensplice")) {
			throw std::runtime_error("config.json: illegal middleware.type: " + type);
		}

		if(type == "connext") {
			DomainParticipantFactory::instance = new ConnextDomainParticipantFactory();
		}
		// Check optional configurations
	}

	return DomainParticipantFactory::instance;
}

DomainParticipantFactory::DomainParticipantFactory() {
}

DomainParticipantFactory::~DomainParticipantFactory() {
}

DomainParticipant* DomainParticipantFactory::create_participant(
	DomainId_t domain_id,
	const DomainParticipantQos* qos,
	const DomainParticipantListener* a_listener,
	const StatusMask mask) {

	return NULL;
}

ReturnCode_t DomainParticipantFactory::delete_participant(const DomainParticipant* a_participant) {
	return RETCODE_ERROR;
}

DomainParticipant* DomainParticipantFactory::lookup_participant(DomainId_t domain_id) {
	return NULL;
}

ReturnCode_t DomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipantFactory::get_default_participant_qos(DomainParticipantQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipantFactory::set_qos(const DomainParticipantFactoryQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DomainParticipantFactory::get_qos(DomainParticipantFactoryQos* qos) {
	return RETCODE_ERROR;
}

TypeSupport::TypeSupport() {
}

TypeSupport::~TypeSupport() {
}

TopicDescription::TopicDescription() {
}

TopicDescription::~TopicDescription() {
}

std::string* TopicDescription::get_type_name() {
	return NULL;
}

std::string* TopicDescription::get_name() {
	return NULL;
}

DomainParticipant* TopicDescription::get_participant() {
	return NULL;
}

Topic::Topic() {
}

Topic::~Topic() {
}

ReturnCode_t Topic::set_qos(const TopicQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Topic::get_qos(TopicQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Topic::set_listener(const TopicListener* a_listener, const StatusMask mask) {
	return RETCODE_ERROR;
}

TopicListener* Topic::get_listener() {
	return NULL;
}

ReturnCode_t Topic::get_inconsistent_topic_status(InconsistentTopicStatus* a_status) {
	return RETCODE_ERROR;
}

ContentFilteredTopic::ContentFilteredTopic() {
}

ContentFilteredTopic::~ContentFilteredTopic() {
}

std::string* ContentFilteredTopic::get_filter_expression() {
	return NULL;
}

ReturnCode_t ContentFilteredTopic::get_expression_parameters(StringSeq* expression_parameters) {
	return RETCODE_ERROR;
}

ReturnCode_t ContentFilteredTopic::set_expression_parameters(const StringSeq* expression_parameters) {
	return RETCODE_ERROR;
}

Topic* ContentFilteredTopic::get_related_topic() {
	return NULL;
}

MultiTopic::MultiTopic() {
}

MultiTopic::~MultiTopic() {
}

std::string* MultiTopic::get_subscription_expression() {
	return NULL;
}

ReturnCode_t MultiTopic::get_expression_parameters(StringSeq* expression_parameters) {
	return RETCODE_ERROR;
}

ReturnCode_t MultiTopic::set_expression_parameters(const StringSeq* expression_parameters) {
	return RETCODE_ERROR;
}

Publisher::Publisher() {
}

Publisher::~Publisher() {
}

DataWriter* Publisher::create_datawriter(
	const Topic* a_topic,
	const DataWriterQos* qos,
	const DataWriterListener* a_listener,
	const StatusMask mask) {

	return NULL;
}

ReturnCode_t Publisher::delete_datawriter(const DataWriter* a_datawriter) {
	return RETCODE_ERROR;
}

DataWriter* Publisher::lookup_datawriter(const std::string* topic_name) {
	return NULL;
}

ReturnCode_t Publisher::delete_contained_entities() {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::set_qos(const PublisherQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::get_qos(PublisherQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::set_listener(const PublisherListener* a_listener, const StatusMask mask) {
	return RETCODE_ERROR;
}

PublisherListener* Publisher::get_listener() {
	return NULL;
}

ReturnCode_t Publisher::suspend_publications() {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::resume_publications() {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::begin_coherent_changes() {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::end_coherent_changes() {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::wait_for_acknowledgments(const Duration_t* max_wait) {
	return RETCODE_ERROR;
}

DomainParticipant* Publisher::get_participant() {
	return NULL;
}

ReturnCode_t Publisher::set_default_datawriter_qos(const DataWriterQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::get_default_datawriter_qos(DataWriterQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Publisher::copy_from_topic_qos(DataWriterQos* a_datawriter_qos, const TopicQos* a_topic_qos) {
	return RETCODE_ERROR;
}

DataWriter::DataWriter() {
}

DataWriter::~DataWriter() {
}

ReturnCode_t DataWriter::set_qos(const DataWriterQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_qos(DataWriterQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::set_listener(const DataWriterListener* a_listener, const StatusMask mask) {
	return RETCODE_ERROR;
}

DataWriterListener* DataWriter::get_listener() {
	return NULL;
}

Topic* DataWriter::get_topic() {
	return NULL;
}

Publisher* DataWriter::get_publisher() {
	return NULL;
}

ReturnCode_t DataWriter::wait_for_acknowledgments(const Duration_t* max_wait) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_liveliness_lost_status(LivelinessLostStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_offered_deadline_missed_status(OfferedDeadlineMissedStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_offered_incompatible_qos_status(OfferedIncompatibleQosStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_publication_matched_status(PublicationMatchedStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::assert_liveliness() {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_matched_subscriptions(InstanceHandleSeq* subscription_handles) {
	return RETCODE_ERROR;
}

ReturnCode_t DataWriter::get_matched_subscription_data(SubscriptionBuiltinTopicData* subscription_data, InstanceHandle_t subscription_handle) {
	return RETCODE_ERROR;
}

Subscriber::Subscriber() {
}

Subscriber::~Subscriber() {
}

DataReader* Subscriber::create_datareader(
	const TopicDescription* a_topic,
	const DataReaderQos* qos,
	const DataReaderListener* a_listener,
	const StatusMask mask) {

	return NULL;
}

ReturnCode_t Subscriber::delete_datareader(const DataReader* a_datareader) {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::delete_contained_entities() {
	return RETCODE_ERROR;
}

DataReader* Subscriber::lookup_datareader(const std::string* topic_name) {
	return NULL;
}

ReturnCode_t Subscriber::get_datareaders(
	DataReaderSeq* readers,
	const SampleStateMask* sample_states,
	const ViewStateMask* view_states,
	const InstanceStateMask* instance_states) {

	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::notify_datareaders() {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::set_qos(const SubscriberQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::get_qos(SubscriberQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::set_listener(const SubscriberListener* a_listener, const StatusMask mask) {
	return RETCODE_ERROR;
}

SubscriberListener* Subscriber::get_listener() {
	return NULL;
}

ReturnCode_t Subscriber::begin_access() {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::end_access() {
	return RETCODE_ERROR;
}

DomainParticipant* Subscriber::get_participant() {
	return NULL;
}

ReturnCode_t Subscriber::set_default_datareader_qos(const DataReaderQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::get_default_datareader_qos(DataReaderQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t Subscriber::copy_from_topic_qos(DataReaderQos* a_datareader_qos, const TopicQos* a_topic_qos) {
	return RETCODE_ERROR;
}

DataReader::DataReader() {
}

DataReader::~DataReader() {
}

ReadCondition* DataReader::create_readcondition(
	const SampleStateMask* sample_states,
	const ViewStateMask* view_states,
	const InstanceStateMask* instance_states) {

	return NULL;
}

QueryCondition* DataReader::create_querycondition(
	const SampleStateMask* sample_states,
	const ViewStateMask* view_states,
	const InstanceStateMask* instance_states,
	const std::string* query_expression,
	const StringSeq* query_parameters) {

	return NULL;
}

ReturnCode_t DataReader::delete_readcondition(const ReadCondition* a_condition) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::delete_contained_entities() {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::set_qos(const DataReaderQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_qos(DataReaderQos* qos) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::set_listener(const DataReaderListener* a_listener, const StatusMask mask) {
	return RETCODE_ERROR;
}

DataReaderListener* DataReader::get_listener() {
	return NULL;
}

TopicDescription* DataReader::get_topicdescription() {
	return NULL;
}

Subscriber* DataReader::get_subscriber() {
	return NULL;
}

ReturnCode_t DataReader::get_sample_rejected_status(SampleRejectedStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_liveliness_changed_status(LivelinessChangedStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_requested_deadline_missed_status(RequestedDeadlineMissedStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_requested_incompatible_qos_status(RequestedIncompatibleQosStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_subscription_matched_status(SubscriptionMatchedStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_sample_lost_status(SampleLostStatus* status) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::wait_for_historical_data(const Duration_t* max_wait) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_matched_publications(InstanceHandleSeq* publication_handles) {
	return RETCODE_ERROR;
}

ReturnCode_t DataReader::get_matched_publication_data(PublicationBuiltinTopicData* publication_data, InstanceHandle_t publication_handle) {
	return RETCODE_ERROR;
}

SampleInfo::SampleInfo() {
	sample_state = READ_SAMPLE_STATE;
	view_state = NEW_VIEW_STATE;
	instance_state = HANDLE_NIL;
	source_timestamp = new Time_t();
	instance_handle = HANDLE_NIL;
	publication_handle = HANDLE_NIL;
	disposed_generation_count = 0;
	no_writers_generation_count = 0;
	sample_rank = 0;
	generation_rank = 0;
	absolute_generation_rank = 0;
	valid_data = false;
}

SampleInfo::SampleInfo(
	SampleStateKind sample_state,
	ViewStateKind view_state,
	InstanceStateKind instance_state,
	Time_t* source_timestamp,
	InstanceHandle_t instance_handle,
	InstanceHandle_t publication_handle,
	int32_t disposed_generation_count,
	int32_t no_writers_generation_count,
	int32_t sample_rank,
	int32_t generation_rank,
	int32_t absolute_generation_rank,
	bool valid_data) {

	this->sample_state = sample_state;
	this->view_state = view_state;
	this->instance_state = instance_state;
	this->source_timestamp = source_timestamp;
	this->instance_handle = instance_handle;
	this->publication_handle = publication_handle;
	this->disposed_generation_count = disposed_generation_count;
	this->no_writers_generation_count = no_writers_generation_count;
	this->sample_rank = sample_rank;
	this->generation_rank = generation_rank;
	this->absolute_generation_rank = absolute_generation_rank;
	this->valid_data = valid_data;
}

SampleInfo::~SampleInfo() {
	delete source_timestamp;
}

}
