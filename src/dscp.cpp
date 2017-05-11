#include <stddef.h>
#include <malloc.h>
#include "dscp.h"

namespace dds {

template<typename T>
sequence<T>::sequence() {
	maximum = 0;
	length = 0;
	buffer = NULL;
}

template<typename T>
sequence<T>::sequence(T* array, uint32_t size) {
	maximum = size;
	length = size;
	buffer = malloc(sizeof(T) * size);
	memcpy(buffer, array, sizeof(T) * size);
}

template<typename T>
sequence<T>::~sequence() {
	free(buffer);
}

template<typename T>
bool sequence<T>::add(T value) {
	if(length < maximum) {
		buffer[length++] = value;
		return true;
	} else {
		return false;
	}
}

template<typename T>
T& sequence<T>::operator[](uint32_t index) {
	return buffer[index];
}

template<typename T>
const T& sequence<T>::operator[](uint32_t index) const {
	return buffer[index];
}

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
	sec = 0;
	nanosec = 0;
}

Duration_t::Duration_t(int32_t sec, uint32_t nanosec) {
	this->sec = sec;
	this->nanosec = nanosec;
}

Duration_t::~Duration_t() {
}

Time_t::Time_t() {
	sec = 0;
	nanosec = 0;
}

Time_t::Time_t(int32_t sec, uint32_t nanosec) {
	this->sec = sec;
	this->nanosec = nanosec;
}

Time_t::~Time_t() {
}

InconsistentTopicStatus::InconsistentTopicStatus() {
	total_count = 0;
	total_count_change = 0;
}

InconsistentTopicStatus::InconsistentTopicStatus(int32_t total_count, int32_t total_count_change) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
}

InconsistentTopicStatus::~InconsistentTopicStatus() {
}

SampleLostStatus::SampleLostStatus() {
	total_count = 0;
	total_count_change = 0;
}

SampleLostStatus::SampleLostStatus(int32_t total_count, int32_t total_count_change) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
}

SampleLostStatus::~SampleLostStatus() {
}

SampleRejectedStatus::SampleRejectedStatus() {
	total_count = 0;
	total_count_change = 0;
	last_reason = NOT_REJECTED;
	last_instance_handle = HANDLE_NIL;
}

SampleRejectedStatus::SampleRejectedStatus(int32_t total_count, int32_t total_count_change, SampleRejectedStatusKind last_reason, InstanceHandle_t last_instance_handle) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
	this->last_reason = last_reason;
	this->last_instance_handle = last_instance_handle;
}

SampleRejectedStatus::~SampleRejectedStatus() {
}

LivelinessLostStatus::LivelinessLostStatus() {
	total_count = 0;
	total_count_change = 0;
}

LivelinessLostStatus::LivelinessLostStatus(int32_t total_count, int32_t total_count_change) {
	this->total_count = total_count;
	this->total_count_change = total_count_change;
}

LivelinessLostStatus::~LivelinessLostStatus() {
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
