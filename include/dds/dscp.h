#include <stdint.h>
#include <stdbool.h>

#ifndef __DDS_DSCP_H__
#define __DDS_DSCP_H__

// IDL data types
typedef struct _DDS_sequence {
	uint32_t maximum;
	uint32_t length;
	void* buffer;
} DDS_sequence;

#define DDS_DOMAINID_TYPE_NATIVE		int32_t
#define DDS_HANDLE_TYPE_NATIVE			int32_t
#define DDS_HANDLE_NIL_NATIVE			0
#define DDS_BUILTIN_TOPIC_KEY_TYPE_NATIVE	int32_t

#define DDS_TheParticipantFactory
#define DDS_PARTICIPANT_QOS_DEFAULT
#define DDS_TOPIC_QOS_DEFAULT
#define DDS_PUBLISHER_QOS_DEFAULT
#define DDS_SUBSCRIBER_QOS_DEFAULT
#define DDS_DATAWRITER_QOS_DEFAULT
#define DDS_DATAREADER_QOS_DEFAULT
#define DDS_DATAWRITER_QOS_USE_TOPIC_QOS
#define DDS_DATAREADER_QOS_USE_TOPIC_QOS

typedef DDS_DOMAINID_TYPE_NATIVE DDS_DomainId_t;
typedef DDS_HANDLE_TYPE_NATIVE DDS_InstanceHandle_t;
 
typedef struct _DDS_BuiltinTopicKey_t {
	DDS_BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3];
} DDS_BuiltinTopicKey_t;

typedef DDS_sequence/*<DDS_InstanceHandle_t>*/ DDS_InstanceHandleSeq;

typedef int32_t DDS_ReturnCode_t;
typedef int32_t DDS_QosPolicyId_t;
typedef DDS_sequence/*<char*>*/ DDS_StringSeq;

typedef struct _DDS_Duration_t {
	int32_t sec;
	uint32_t nanosec;
} DDS_Duration_t;

typedef struct _DDS_Time_t {
	int32_t sec;
	uint32_t nanosec;
} _DDS_Time_t;

// ----------------------------------------------------------------------
// Pre-defined values
// ----------------------------------------------------------------------
const DDS_InstanceHandle_t DDS_HANDLE_NIL = DDS_HANDLE_NIL_NATIVE;

const int32_t DDS_LENGTH_UNLIMITED		= -1;

const int32_t DDS_DURATION_INFINITE_SEC		= 0x7fffffff;
const uint32_t DDS_DURATION_INFINITE_NSEC	= 0x7fffffff;

const int32_t DDS_DURATION_ZERO_SEC		= 0;
const uint32_t DDS_DURATION_ZERO_NSEC		= 0;

const int32_t DDS_TIME_INVALID_SEC		= -1;
const uint32_t DDS_TIME_INVALID_NSEC		= 0xffffffff;

// ----------------------------------------------------------------------
// Return codes
// ----------------------------------------------------------------------
const DDS_ReturnCode_t DDS_RETCODE_OK			= 0;
const DDS_ReturnCode_t DDS_RETCODE_ERROR		= 1;
const DDS_ReturnCode_t DDS_RETCODE_UNSUPPORTED		= 2;
const DDS_ReturnCode_t DDS_RETCODE_BAD_PARAMETER	= 3;
const DDS_ReturnCode_t DDS_RETCODE_PRECONDITION_NOT_MET	= 4;
const DDS_ReturnCode_t DDS_RETCODE_OUT_OF_RESOURCES	= 5;
const DDS_ReturnCode_t DDS_RETCODE_NOT_ENABLED		= 6;
const DDS_ReturnCode_t DDS_RETCODE_IMMUTABLE_POLICY	= 7;
const DDS_ReturnCode_t DDS_RETCODE_INCONSISTENT_POLICY	= 8;
const DDS_ReturnCode_t DDS_RETCODE_ALREADY_DELETED	= 9;
const DDS_ReturnCode_t DDS_RETCODE_TIMEOUT		= 10;
const DDS_ReturnCode_t DDS_RETCODE_NO_DATA		= 11;
const DDS_ReturnCode_t DDS_RETCODE_ILLEGAL_OPERATION	= 12;

// ----------------------------------------------------------------------
// Status to support listeners and conditions
// ----------------------------------------------------------------------

typedef uint32_t DDS_StatusKind;
typedef uint32_t DDS_StatusMask;	// bit-mask StatusKind

const DDS_StatusKind DDS_INCONSISTENT_TOPIC_STATUS		= 0x0001 << 0;
const DDS_StatusKind DDS_OFFERED_DEADLINE_MISSED_STATUS		= 0x0001 << 1;
const DDS_StatusKind DDS_REQUESTED_DEADLINE_MISSED_STATUS	= 0x0001 << 2;
const DDS_StatusKind DDS_OFFERED_INCOMPATIBLE_QOS_STATUS	= 0x0001 << 5;
const DDS_StatusKind DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS	= 0x0001 << 6;
const DDS_StatusKind DDS_SAMPLE_LOST_STATUS			= 0x0001 << 7;
const DDS_StatusKind DDS_SAMPLE_REJECTED_STATUS			= 0x0001 << 8;
const DDS_StatusKind DDS_DATA_ON_READERS_STATUS			= 0x0001 << 9;
const DDS_StatusKind DDS_DATA_AVAILABLE_STATUS			= 0x0001 << 10;
const DDS_StatusKind DDS_LIVELINESS_LOST_STATUS			= 0x0001 << 11;
const DDS_StatusKind DDS_LIVELINESS_CHANGED_STATUS		= 0x0001 << 12;
const DDS_StatusKind DDS_PUBLICATION_MATCHED_STATUS		= 0x0001 << 13;
const DDS_StatusKind DDS_SUBSCRIPTION_MATCHED_STATUS		= 0x0001 << 14;

typedef struct _DDS_InconsistentTopicStatus {
	int32_t total_count;
	int32_t total_count_change;
} DDS_InconsistentTopicStatus;

typedef struct _DDS_SampleLostStatus {
	int32_t total_count;
	int32_t total_count_change;
} DDS_SampleLostStatus;

enum DDS_SampleRejectedStatusKind {
	DDS_NOT_REJECTED,
	DDS_REJECTED_BY_INSTANCES_LIMIT,
	DDS_REJECTED_BY_SAMPLES_LIMIT,
	DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
};

typedef struct _DDS_SampleRejectedStatus {
	int32_t				total_count;
	int32_t				total_count_change;
	DDS_SampleRejectedStatusKind	last_reason;
	DDS_InstanceHandle_t		last_instance_handle;
} DDS_SampleRejectedStatus;

typedef struct _DDS_LivelinessLostStatus {
	int32_t	total_count;
	int32_t	total_count_change;
} DDS_LivelinessLostStatus;

typedef struct _DDS_LivelinessChangedStatus {
	int32_t			alive_count;
	int32_t			not_alive_count;
	int32_t			alive_count_change;
	int32_t			not_alive_count_change;
	DDS_InstanceHandle_t	last_publication_handle;
} DDS_LivelinessChangedStatus;

typedef struct _DDS_OfferedDeadlineMissedStatus {
	int32_t			total_count;
	int32_t			total_count_change;
	DDS_InstanceHandle_t	last_instance_handle;
} DDS_OfferedDeadlineMissedStatus;

typedef struct _DDS_RequestedDeadlineMissedStatus {
	int32_t			total_count;
	int32_t			total_count_change;
	DDS_InstanceHandle_t	last_instance_handle;
} DDS_RequestedDeadlineMissedStatus;

typedef struct _DDS_QosPolicyCount {
	DDS_QosPolicyId_t	policy_id;
	int32_t			count;
} DDS_QosPolicyCount;

typedef DDS_sequence/*<DDS_QosPolicyCount>*/ DDS_QosPolicyCountSeq;

typedef struct _DDS_OfferedIncompatibleQosStatus {
	int32_t			total_count;
	int32_t			total_count_change;
	DDS_QosPolicyId_t	last_policy_id;
	DDS_QosPolicyCountSeq	policies;
} DDS_OfferedIncompatibleQosStatus;

typedef struct _DDS_RequestedIncompatibleQosStatus {
	int32_t			total_count;
	int32_t			total_count_change;
	DDS_QosPolicyId_t	last_policy_id;
	DDS_QosPolicyCountSeq	policies;
} DDS_RequestedIncompatibleQosStatus;

typedef struct _DDS_PublicationMatchedStatus {
	int32_t			total_count;
	int32_t			total_count_change;
	int32_t			current_count;
	int32_t			current_count_change;
	DDS_InstanceHandle_t	last_subscription_handle;
} DDS_PublicationMatchedStatus;

typedef struct _DDS_SubscriptionMatchedStatus {
	int32_t			total_count;
	int32_t			total_count_change;
	int32_t			current_count;
	int32_t			current_count_change;
	DDS_InstanceHandle_t	last_publication_handle;
} DDS_SubscriptionMatchedStatus;

// ----------------------------------------------------------------------
// Listeners
// ----------------------------------------------------------------------

typedef struct _DDS_Listener DDS_Listener;
typedef struct _DDS_Entity DDS_Entity;
typedef struct _DDS_TopicDescription DDS_TopicDescription;
typedef struct _DDS_Topic DDS_Topic;
typedef struct _DDS_ContentFilteredTopic DDS_ContentFilteredTopic;
typedef struct _DDS_MultiTopic DDS_MultiTopic;
typedef struct _DDS_DataWriter DDS_DataWriter;
typedef struct _DDS_DataReader DDS_DataReader;
typedef struct _DDS_Subscriber DDS_Subscriber;
typedef struct _DDS_Publisher DDS_Publisher;

typedef DDS_sequence/*<DDS_DataReader>*/ DDS_DataReaderSeq;

struct _DDS_Listener {};

struct _DDS_TopicListener {
	DDS_Listener;
	
	void on_inconsistent_topic(const DDS_Topic* the_topic, 
		const DDS_InconsistentTopicStatus* status);
};

struct _DDS_DataWriterListener {
	DDS_Listener;
	
	void on_offered_deadline_missed(
		const DDS_DataWriter* writer, 
		const DDS_OfferedDeadlineMissedStatus* status);
	void on_offered_incompatible_qos(
		const DDS_DataWriter* writer, 
		const DDS_OfferedIncompatibleQosStatus* status);
	void on_liveliness_lost(
		const DDS_DataWriter* writer, 
		const DDS_LivelinessLostStatus* status);
	void on_publication_matched(
		const DDS_DataWriter* writer, 
		const DDS_PublicationMatchedStatus* status);
};

struct _DDS_PublisherListener {
	DDS_DataWriterListener;
};

struct _DDS_DataReaderListener {
	DDS_Listener;
	
	void on_requested_deadline_missed(
		const DDS_DataReader* the_reader, 
		const DDS_RequestedDeadlineMissedStatus* status);
	void on_requested_incompatible_qos(
		const DDS_DataReader* the_reader, 
		const DDS_RequestedIncompatibleQosStatus* status);
	void on_sample_rejected(
		const DDS_DataReader* the_reader,
		const DDS_SampleRejectedStatus* status);
	void on_liveliness_changed(
		const DDS_DataReader* the_reader,
		const DDS_LivelinessChangedStatus* status);
	void on_data_available(
		const DDS_DataReader* the_reader);
	void on_subscription_matched(
		const DDS_DataReader* the_reader,
		const DDS_SubscriptionMatchedStatus* status);
	void on_sample_lost(
		const DDS_DataReader* the_reader,
		const DDS_SampleLostStatus* status);
};

struct _DDS_SubscriberListener {
	DDS_DataReaderListener;
	
	void on_data_on_readers(const DDS_Subscriber* the_subscriber);
};

struct _DDS_DomainParticipantListener {
	DDS_TopicListener;
	DDS_PublisherListener;
	DDS_SubscriberListener;
};

// ----------------------------------------------------------------------
// Conditions
// ----------------------------------------------------------------------

struct _DDS_Condition {
	bool get_trigger_value();
};

typedef DDS_sequence/*<DDS_Condition>*/ DDS_ConditionSeq;

struct _DDS_WaitSet {
	DDS_ReturnCode_t wait(
		DDS_ConditionSeq* active_conditions,
		const DDS_Duration_t* timeout);
	DDS_ReturnCode_t attach_condition(
		const DDS_Condition* cond);
	DDS_ReturnCode_t detach_condition(
		const DDS_Condition* cond);
	DDS_ReturnCode_t get_conditions(
		DDS_ConditionSeq* attached_conditions);
};

struct _DDS_GuardCondition {
	DDS_Condition;
	
	DDS_ReturnCode_t set_trigger_value(bool value);
};

struct _DDS_StatusCondition {
	DDS_Condition;
	DDS_StatusMask get_enabled_statuses();
	DDS_ReturnCode_t set_enabled_statuses(
		const DDS_StatusMask* mask);
	DDS_Entity get_entity();
};

// Sample states to support reads
typedef uint32_t DDS_SampleStateKind;
const DDS_SampleStateKind DDS_READ_SAMPLE_STATE				= 0x0001 << 0;
const DDS_SampleStateKind DDS_NOT_READ_SAMPLE_STATE			= 0x0001 << 1;

// This is a bit-mask SampleStateKind
typedef uint32_t DDS_SampleStateMask;
const DDS_SampleStateMask DDS_ANY_SAMPLE_STATE				= 0xffff;

// View states to support reads
typedef uint32_t DDS_ViewStateKind;
const DDS_ViewStateKind DDS_NEW_VIEW_STATE				= 0x0001 << 0;
const DDS_ViewStateKind DDS_NOT_NEW_VIEW_STATE				= 0x0001 << 1;

// This is a bit-mask ViewStateKind
typedef uint32_t DDS_ViewStateMask;
const DDS_ViewStateMask DDS_ANY_VIEW_STATE				= 0xffff;

// Instance states to support reads
typedef uint32_t DDS_InstanceStateKind;
const DDS_InstanceStateKind DDS_ALIVE_INSTANCE_STATE			= 0x0001 << 0;
const DDS_InstanceStateKind DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE	= 0x0001 << 1;
const DDS_InstanceStateKind DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE	= 0x0001 << 2;

// This is a bit-mask InstanceStateKind
typedef uint32_t DDS_InstanceStateMask;
const DDS_InstanceStateMask DDS_ANY_INSTANCE_STATE			= 0xffff;
const DDS_InstanceStateMask DDS_NOT_ALIVE_INSTANCE_STATE		= 0x006;

struct _DDS_ReadCondition {
	DDS_Condition;
	
	DDS_SampleStateMask get_sample_state_mask();
	DDS_ViewStateMask get_view_state_mask();
	DDS_InstanceStateMask get_instance_state_mask();
	DDS_DataReader get_datareader();
};

struct _DDS_QueryCondition {
	DDS_ReadCondition;
	
	char* get_query_expression();
	DDS_ReturnCode_t get_query_parameters(
		DDS_StringSeq* query_parameters);
	DDS_ReturnCode_t set_query_parameters(
		const DDS_StringSeq* query_parameters);
};

// ----------------------------------------------------------------------
// Qos
// ----------------------------------------------------------------------
const char* DDS_USERDATA_QOS_POLICY_NAME			= "UserData";
const char* DDS_DURABILITY_QOS_POLICY_NAME			= "Durability";
const char* DDS_PRESENTATION_QOS_POLICY_NAME			= "Presentation";
const char* DDS_DEADLINE_QOS_POLICY_NAME			= "Deadline";
const char* DDS_LATENCYBUDGET_QOS_POLICY_NAME			= "LatencyBudget";
const char* DDS_OWNERSHIP_QOS_POLICY_NAME			= "Ownership";
const char* DDS_OWNERSHIPSTRENGTH_QOS_POLICY_NAME		= "OwnershipStrength";
const char* DDS_LIVELINESS_QOS_POLICY_NAME			= "Liveliness";
const char* DDS_TIMEBASEDFILTER_QOS_POLICY_NAME			= "TimeBasedFilter";
const char* DDS_PARTITION_QOS_POLICY_NAME			= "Partition";
const char* DDS_RELIABILITY_QOS_POLICY_NAME			= "Reliability";
const char* DDS_DESTINATIONORDER_QOS_POLICY_NAME		= "DestinationOrder";
const char* DDS_HISTORY_QOS_POLICY_NAME				= "History";
const char* DDS_RESOURCELIMITS_QOS_POLICY_NAME			= "ResourceLimits";
const char* DDS_ENTITYFACTORY_QOS_POLICY_NAME			= "EntityFactory";
const char* DDS_WRITERDATALIFECYCLE_QOS_POLICY_NAME		= "WriterDataLifecycle";
const char* DDS_READERDATALIFECYCLE_QOS_POLICY_NAME		= "ReaderDataLifecycle";
const char* DDS_TOPICDATA_QOS_POLICY_NAME			= "TopicData";
const char* DDS_GROUPDATA_QOS_POLICY_NAME			= "TransportPriority";
const char* DDS_LIFESPAN_QOS_POLICY_NAME			= "Lifespan";
const char* DDS_DURABILITYSERVICE_POLICY_NAME			= "DurabilityService";
const DDS_QosPolicyId_t DDS_INVALID_QOS_POLICY_ID		= 0;
const DDS_QosPolicyId_t DDS_USERDATA_QOS_POLICY_ID		= 1;
const DDS_QosPolicyId_t DDS_DURABILITY_QOS_POLICY_ID		= 2;
const DDS_QosPolicyId_t DDS_PRESENTATION_QOS_POLICY_ID		= 3;
const DDS_QosPolicyId_t DDS_DEADLINE_QOS_POLICY_ID		= 4;
const DDS_QosPolicyId_t DDS_LATENCYBUDGET_QOS_POLICY_ID		= 5;
const DDS_QosPolicyId_t DDS_OWNERSHIP_QOS_POLICY_ID		= 6;
const DDS_QosPolicyId_t DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID	= 7;
const DDS_QosPolicyId_t DDS_LIVELINESS_QOS_POLICY_ID		= 8;
const DDS_QosPolicyId_t DDS_TIMEBASEDFILTER_QOS_POLICY_ID	= 9;
const DDS_QosPolicyId_t DDS_PARTITION_QOS_POLICY_ID		= 10;
const DDS_QosPolicyId_t DDS_RELIABILITY_QOS_POLICY_ID		= 11;
const DDS_QosPolicyId_t DDS_DESTINATIONORDER_QOS_POLICY_ID	= 12;
const DDS_QosPolicyId_t DDS_HISTORY_QOS_POLICY_ID		= 13;
const DDS_QosPolicyId_t DDS_RESOURCELIMITS_QOS_POLICY_ID	= 14;
const DDS_QosPolicyId_t DDS_ENTITYFACTORY_QOS_POLICY_ID		= 15;
const DDS_QosPolicyId_t DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID	= 16;
const DDS_QosPolicyId_t DDS_READERDATALIFECYCLE_QOS_POLICY_ID	= 17;
const DDS_QosPolicyId_t DDS_TOPICDATA_QOS_POLICY_ID		= 18;
const DDS_QosPolicyId_t DDS_GROUPDATA_QOS_POLICY_ID		= 19;
const DDS_QosPolicyId_t DDS_TRANSPORTPRIORITY_QOS_POLICY_ID	= 20;
const DDS_QosPolicyId_t DDS_LIFESPAN_QOS_POLICY_ID		= 21;
const DDS_QosPolicyId_t DDS_DURABILITYSERVICE_QOS_POLICY_ID	= 22;

typedef struct _DDS_UserDataQosPolicy {
	DDS_sequence/*<uint8_t>*/ value;
} DDS_UserDataQosPolicy;

typedef struct _DDS_TopicDataQosPolicy {
	DDS_sequence/*<uint8_t>*/ value;
} DDS_TopicDataQosPolicy;

typedef struct _DDS_GroupDataQosPolicy {
	DDS_sequence/*<uint8_t>*/ value;
} DDS_GroupDataQosPolicy;

typedef struct _DDS_TransportPriorityQosPolicy {
	int32_t value;
} DDS_TransportPriorityQosPolicy;

typedef struct _DDS_LifespanQosPolicy {
	DDS_Duration_t duration;
} DDS_LifespanQosPolicy;

enum DDS_DurabilityQosPolicyKind {
	DDS_VOLATILE_DURABILITY_QOS,
	DDS_TRANSIENT_LOCAL_DURABILITY_QOS,
	DDS_TRANSIENT_DURABILITY_QOS,
	DDS_PERSISTENT_DURABILITY_QOS
};

typedef struct _DDS_DurabilityQosPolicy {
	DDS_DurabilityQosPolicyKind kind;
} DDS_DurabilityQosPolicy;

enum DDS_PresentationQosPolicyAccessScopeKind {
	DDS_INSTANCE_PRESENTATION_QOS,
	DDS_TOPIC_PRESENTATION_QOS,
	DDS_GROUP_PRESENTATION_QOS
};

typedef struct _DDS_PresentationQosPolicy {
	DDS_PresentationQosPolicyAccessScopeKind access_scope;
	bool coherent_access;
	bool ordered_access;
} DDS_PresentationQosPolicy;

typedef struct _DDS_DeadlineQosPolicy {
	DDS_Duration_t period;
} DDS_DeadlineQosPolicy;

typedef struct _DDS_LatencyBudgetQosPolicy {
	DDS_Duration_t duration;
} DDS_LatencyBudgetQosPolicy;

enum DDS_OwnershipQosPolicyKind {
	DDS_SHARED_OWNERSHIP_QOS,
	DDS_EXCLUSIVE_OWNERSHIP_QOS
};

typedef struct _DDS_OwnershipQosPolicy {
	DDS_OwnershipQosPolicyKind kind;
} DDS_OwnershipQosPolicy;

typedef struct _DDS_OwnershipStrengthQosPolicy {
	int32_t value;
} DDS_OwnershipStrengthQosPolicy;

enum DDS_LivelinessQosPolicyKind {
	DDS_AUTOMATIC_LIVELINESS_QOS,
	DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
	DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS
};

typedef struct _DDS_LivelinessQosPolicy {
	DDS_LivelinessQosPolicyKind kind;
	DDS_Duration_t lease_duration;
} DDS_LivelinessQosPolicy;

typedef struct _DDS_TimeBasedFilterQosPolicy {
	DDS_Duration_t minimum_separation;
} DDS_TimeBasedFilterQosPolicy;

typedef struct _DDS_PartitionQosPolicy {
	DDS_StringSeq name;
} DDS_PartitionQosPolicy;

enum DDS_ReliabilityQosPolicyKind {
	DDS_BEST_EFFORT_RELIABILITY_QOS,
	DDS_RELIABLE_RELIABILITY_QOS
};

typedef struct _DDS_ReliabilityQosPolicy {
	DDS_ReliabilityQosPolicyKind kind;
	DDS_Duration_t max_blocking_time;
} DDS_ReliabilityQosPolicy;

enum DDS_DestinationOrderQosPolicyKind {
	DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
	DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
};

typedef struct _DDS_DestinationOrderQosPolicy {
	DDS_DestinationOrderQosPolicyKind kind;
} DDS_DestinationOrderQosPolicy;

enum DDS_HistoryQosPolicyKind {
	DDS_KEEP_LAST_HISTORY_QOS,
	DDS_KEEP_ALL_HISTORY_QOS
};
 
typedef struct _DDS_HistoryQosPolicy {
	DDS_HistoryQosPolicyKind kind;
	int32_t depth;
} DDS_HistoryQosPolicy;

typedef struct _DDS_ResourceLimitsQosPolicy {
	int32_t max_samples;
	int32_t max_instances;
	int32_t max_samples_per_instance;
} DDS_ResourceLimitsQosPolicy;

typedef struct DDS_EntityFactoryQosPolicy {
	bool autoenable_created_entities;
} DDS_EntityFactoryQosPolicy;

typedef struct _DDS_WriterDataLifecycleQosPolicy {
	bool autodispose_unregistered_instances;
} DDS_WriterDataLifecycleQosPolicy;

typedef struct _DDS_ReaderDataLifecycleQosPolicy {
	DDS_Duration_t autopurge_nowriter_samples_delay;
	DDS_Duration_t autopurge_disposed_samples_delay;
} DDS_ReaderDataLifecycleQosPolicy;

typedef struct _DDS_DurabilityServiceQosPolicy {
	DDS_Duration_t			service_cleanup_delay;
	DDS_HistoryQosPolicyKind	history_kind;
	int32_t				history_depth;
	int32_t				max_samples;
	int32_t				max_instances;
	int32_t				max_samples_per_instance;
} DDS_DurabilityServiceQosPolicy;

typedef struct _DDS_DomainParticipantFactoryQos {
	DDS_EntityFactoryQosPolicy		entity_factory;
} DDS_DomainParticipantFactoryQos;

typedef struct _DDS_DomainParticipantQos {
	DDS_UserDataQosPolicy			user_data;
	DDS_EntityFactoryQosPolicy		entity_factory;
} DDS_DomainParticipantQos;

typedef struct _DDS_TopicQos {
	DDS_TopicDataQosPolicy			topic_data;
	DDS_DurabilityQosPolicy			durability;
	DDS_DurabilityServiceQosPolicy		durability_service;
	DDS_DeadlineQosPolicy			deadline;
	DDS_LatencyBudgetQosPolicy		latency_budget;
	DDS_LivelinessQosPolicy			liveliness;
	DDS_ReliabilityQosPolicy		reliability;
	DDS_DestinationOrderQosPolicy		destination_order;
	DDS_HistoryQosPolicy			history;
	DDS_ResourceLimitsQosPolicy		resource_limits;
	DDS_TransportPriorityQosPolicy		transport_priority;
	DDS_LifespanQosPolicy			lifespan;
	DDS_OwnershipQosPolicy			ownership;
} DDS_TopicQos;

typedef struct _DDS_DataWriterQos {
	DDS_DurabilityQosPolicy			durability;
	DDS_DurabilityServiceQosPolicy		durability_service;
	DDS_DeadlineQosPolicy			deadline;
	DDS_LatencyBudgetQosPolicy		latency_budget;
	DDS_LivelinessQosPolicy			liveliness;
	DDS_ReliabilityQosPolicy		reliability;
	DDS_DestinationOrderQosPolicy		destination_order;
	DDS_HistoryQosPolicy			history;
	DDS_ResourceLimitsQosPolicy		resource_limits;
	DDS_TransportPriorityQosPolicy		transport_priority;
	DDS_LifespanQosPolicy			lifespan;
	DDS_UserDataQosPolicy			user_data;
	DDS_OwnershipQosPolicy			ownership;
	DDS_OwnershipStrengthQosPolicy		ownership_strength;
	DDS_WriterDataLifecycleQosPolicy	writer_data_lifecycle;
} DDS_DataWriterQos;

typedef struct _DDS_PublisherQos {
	DDS_PresentationQosPolicy		presentation;
	DDS_PartitionQosPolicy			partition;
	DDS_GroupDataQosPolicy			group_data;
	DDS_EntityFactoryQosPolicy		entity_factory;
} DDS_PublisherQos;

typedef struct _DDS_DataReaderQos {
	DDS_DurabilityQosPolicy			durability;
	DDS_DeadlineQosPolicy			deadline;
	DDS_LatencyBudgetQosPolicy		latency_budget;
	DDS_LivelinessQosPolicy			liveliness;
	DDS_ReliabilityQosPolicy		reliability;
	DDS_DestinationOrderQosPolicy		destination_order;
	DDS_HistoryQosPolicy			history;
	DDS_ResourceLimitsQosPolicy		resource_limits;
	DDS_UserDataQosPolicy			user_data;
	DDS_OwnershipQosPolicy			ownership;
	DDS_TimeBasedFilterQosPolicy		time_based_filter;
	DDS_ReaderDataLifecycleQosPolicy	reader_data_lifecycle;
} DDS_DataReaderQos;

typedef struct _DDS_SubscriberQos {
	DDS_PresentationQosPolicy		presentation;
	DDS_PartitionQosPolicy			partition;
	DDS_GroupDataQosPolicy			group_data;
	DDS_EntityFactoryQosPolicy		entity_factory;
} DDS_SubscriberQos;

// ----------------------------------------------------------------------
typedef struct _DDS_ParticipantBuiltinTopicData {
	DDS_BuiltinTopicKey_t			key;
	DDS_UserDataQosPolicy			user_data;
} DDS_ParticipantBuiltinTopicData;

typedef struct _DDS_TopicBuiltinTopicData {
	DDS_BuiltinTopicKey_t			key;
	char*					name;
	char*					type_name;
	DDS_DurabilityQosPolicy			durability;
	DDS_DurabilityServiceQosPolicy		durability_service;
	DDS_DeadlineQosPolicy			deadline;
	DDS_LatencyBudgetQosPolicy		latency_budget;
	DDS_LivelinessQosPolicy			liveliness;
	DDS_ReliabilityQosPolicy		reliability;
	DDS_TransportPriorityQosPolicy		transport_priority;
	DDS_LifespanQosPolicy			lifespan;
	DDS_DestinationOrderQosPolicy		destination_order;
	DDS_HistoryQosPolicy			history;
	DDS_ResourceLimitsQosPolicy		resource_limits;
	DDS_OwnershipQosPolicy			ownership;
	DDS_TopicDataQosPolicy			topic_data;
} DDS_TopicBuiltinTopicData;

typedef struct _DDS_PublicationBuiltinTopicData {
	DDS_BuiltinTopicKey_t			key;
	DDS_BuiltinTopicKey_t			participant_key;
	char*					topic_name;
	char*					type_name;
	DDS_DurabilityQosPolicy			durability;
	DDS_DurabilityServiceQosPolicy		durability_service;
	DDS_DeadlineQosPolicy			deadline;
	DDS_LatencyBudgetQosPolicy		latency_budget;
	DDS_LivelinessQosPolicy			liveliness;
	DDS_ReliabilityQosPolicy		reliability;
	DDS_LifespanQosPolicy			lifespan;
	DDS_UserDataQosPolicy			user_data;
	DDS_OwnershipQosPolicy			ownership;
	DDS_OwnershipStrengthQosPolicy		ownership_strength;
	DDS_DestinationOrderQosPolicy		destination_order;
	DDS_PresentationQosPolicy		presentation;
	DDS_PartitionQosPolicy			partition;
	DDS_TopicDataQosPolicy			topic_data;
	DDS_GroupDataQosPolicy			group_data;
} DDS_PublicationBuiltinTopicData;

typedef struct _DDS_SubscriptionBuiltinTopicData {
	DDS_BuiltinTopicKey_t			key;
	DDS_BuiltinTopicKey_t			participant_key;
	char*					topic_name;
	char*					type_name;
	DDS_DurabilityQosPolicy			durability;
	DDS_DeadlineQosPolicy			deadline;
	DDS_LatencyBudgetQosPolicy		latency_budget;
	DDS_LivelinessQosPolicy			liveliness;
	DDS_ReliabilityQosPolicy		reliability;
	DDS_OwnershipQosPolicy			ownership;
	DDS_DestinationOrderQosPolicy		destination_order;
	DDS_UserDataQosPolicy			user_data;
	DDS_TimeBasedFilterQosPolicy		time_based_filter;
	DDS_PresentationQosPolicy		presentation;
	DDS_PartitionQosPolicy			partition;
	DDS_TopicDataQosPolicy			topic_data;
	DDS_GroupDataQosPolicy			group_data;
} DDS_SubscriptionBuiltinTopicData;

// ----------------------------------------------------------------------
struct _DDS_Entity {
	// abstract methods
	DDS_ReturnCode_t set_qos(
		const DDS_EntityQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_EntityQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_Listener* l,
		const DDS_StatusMask* mask);
	DDS_Listener get_listener();
	
	// non-abstract methods
	DDS_ReturnCode_t enable();
	DDS_StatusCondition get_statuscondition();
	DDS_StatusMask get_status_changes();
	DDS_InstanceHandle_t get_instance_handle();
};

// ----------------------------------------------------------------------
struct _DDS_DomainParticipant {
	DDS_Entity;
	
	// Factory interfaces
	DDS_Publisher create_publisher(
		const DDS_PublisherQos* qos,
		const DDS_PublisherListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_ReturnCode_t delete_publisher(
		const DDS_Publisher* p);
	DDS_Subscriber create_subscriber(
		const DDS_SubscriberQos* qos,
		const DDS_SubscriberListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_ReturnCode_t delete_subscriber(
		const DDS_Subscriber* s);
	DDS_Subscriber get_builtin_subscriber();
	DDS_Topic create_topic(
		const char* topic_name,
		const char* type_name,
		const DDS_TopicQos* qos,
		const DDS_TopicListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_ReturnCode_t delete_topic(
		const DDS_Topic* a_topic);
	DDS_Topic find_topic(
		const char* topic_name,
		const DDS_Duration_t* timeout);
	DDS_TopicDescription lookup_topicdescription(
		const char* name);
	DDS_ContentFilteredTopic create_contentfilteredtopic(
		const char* name,
		const DDS_Topic* related_topic,
		const char* filter_expression,
		const DDS_StringSeq* expression_parameters);
	DDS_ReturnCode_t delete_contentfilteredtopic(
		const DDS_ContentFilteredTopic* a_contentfilteredtopic);
	DDS_MultiTopic create_multitopic(
		const char* name,
		const char* type_name,
		const char* subscription_expression,
		const DDS_StringSeq* expression_parameters);
	DDS_ReturnCode_t delete_multitopic(
		const DDS_MultiTopic* a_multitopic);
	DDS_ReturnCode_t delete_contained_entities();
	DDS_ReturnCode_t set_qos(
		const DDS_DomainParticipantQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_DomainParticipantQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_DomainParticipantListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_DomainParticipantListener get_listener();
	DDS_ReturnCode_t ignore_participant(
		DDS_InstanceHandle_t handle);
	DDS_ReturnCode_t ignore_topic(
		DDS_InstanceHandle_t handle);
	DDS_ReturnCode_t ignore_publication(
		DDS_InstanceHandle_t handle);
	DDS_ReturnCode_t ignore_subscription(
		DDS_InstanceHandle_t handle);
	DDS_DomainId_t get_domain_id();
	DDS_ReturnCode_t assert_liveliness();
	DDS_ReturnCode_t set_default_publisher_qos(
		const DDS_PublisherQos* qos);
	DDS_ReturnCode_t get_default_publisher_qos(
		DDS_PublisherQos* qos);
	DDS_ReturnCode_t set_default_subscriber_qos(
		const DDS_SubscriberQos* qos);
	DDS_ReturnCode_t get_default_subscriber_qos(
		DDS_SubscriberQos* qos);
	DDS_ReturnCode_t set_default_topic_qos(
		const DDS_TopicQos* qos);
	DDS_ReturnCode_t get_default_topic_qos(
		DDS_TopicQos* qos);
	DDS_ReturnCode_t get_discovered_participants(
		DDS_InstanceHandleSeq* participant_handles);
	DDS_ReturnCode_t get_discovered_participant_data(
		DDS_ParticipantBuiltinTopicData* participant_data,
		DDS_InstanceHandle_t participant_handle);
	DDS_ReturnCode_t get_discovered_topics(
		DDS_InstanceHandleSeq* topic_handles);
	DDS_ReturnCode_t get_discovered_topic_data(
		DDS_TopicBuiltinTopicData* topic_data,
		DDS_InstanceHandle_t topic_handle);
	bool contains_entity(
		DDS_InstanceHandle_t a_handle);
	DDS_ReturnCode_t get_current_time(
		DDS_Time_t* current_time);
};

struct _DDS_DomainParticipantFactory {
	DDS_DomainParticipant create_participant(
		DDS_DomainId_t domain_id,
		const DDS_DomainParticipantQos* qos,
		const DDS_DomainParticipantListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_ReturnCode_t delete_participant(
		const DDS_DomainParticipant* a_participant);
	DDS_DomainParticipant lookup_participant(
		DDS_DomainId_t domain_id);
	DDS_ReturnCode_t set_default_participant_qos(
		const DDS_DomainParticipantQos* qos);
	DDS_ReturnCode_t get_default_participant_qos(
		DDS_DomainParticipantQos* qos);
	DDS_ReturnCode_t set_qos(
		const DDS_DomainParticipantFactoryQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_DomainParticipantFactoryQos* qos);
};

struct _DDS_TypeSupport {
	// abstract methods
	DDS_ReturnCode_t register_type(
		const DDS_DomainParticipant* domain,
		const char* type_name);
	char* get_type_name();
};

// ----------------------------------------------------------------------
struct _DDS_TopicDescription {
	char* get_type_name();
	char* get_name();
	DDS_DomainParticipant get_participant();
};

struct _DDS_Topic {
	DDS_Entity;
	DDS_TopicDescription;
	
	DDS_ReturnCode_t set_qos(
		const DDS_TopicQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_TopicQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_TopicListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_TopicListener get_listener();
	
	// Access the status
	DDS_ReturnCode_t get_inconsistent_topic_status(
		DDS_InconsistentTopicStatus* a_status);
};

struct _DDS_ContentFilteredTopic {
	DDS_TopicDescription;
	
	char* get_filter_expression();
	
	DDS_ReturnCode_t get_expression_parameters(
		DDS_StringSeq* expression_parameters);
	
	DDS_ReturnCode_t set_expression_parameters(
		const DDS_StringSeq* expression_parameters);
	
	DDS_Topic get_related_topic();
};

struct _DDS_MultiTopic {
	DDS_TopicDescription;
	
	char* get_subscription_expression();
	
	DDS_ReturnCode_t get_expression_parameters(
		DDS_StringSeq* expression_parameters);
	
	DDS_ReturnCode_t set_expression_parameters(
		const DDS_StringSeq* expression_parameters);
};

// ----------------------------------------------------------------------
struct _DDS_Publisher {
	DDS_Entity;
	
	DDS_DataWriter create_datawriter(
		const DDS_Topic* a_topic,
		const DDS_DataWriterQos* qos,
		const DDS_DataWriterListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_ReturnCode_t delete_datawriter(
		const DDS_DataWriter* a_datawriter);
	DDS_DataWriter lookup_datawriter(
		const char* topic_name);
	DDS_ReturnCode_t delete_contained_entities();
	DDS_ReturnCode_t set_qos(
		const DDS_PublisherQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_PublisherQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_PublisherListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_PublisherListener get_listener();
	DDS_ReturnCode_t suspend_publications();
	DDS_ReturnCode_t resume_publications();
	DDS_ReturnCode_t begin_coherent_changes();
	DDS_ReturnCode_t end_coherent_changes();
	DDS_ReturnCode_t wait_for_acknowledgments(
		const DDS_Duration_t* max_wait);
	DDS_DomainParticipant get_participant();
	DDS_ReturnCode_t set_default_datawriter_qos(
		const DDS_DataWriterQos* qos);
	DDS_ReturnCode_t get_default_datawriter_qos(
		DDS_DataWriterQos* qos);
	DDS_ReturnCode_t copy_from_topic_qos(
		DDS_DataWriterQos* a_datawriter_qos,
		const DDS_TopicQos* a_topic_qos);
};

// TODO: Data
typedef void* Data;
struct _DDS_DataWriter {
	DDS_Entity;
	
	// abstract methods
	DDS_InstanceHandle_t register_instance(
		const Data* instance_data);
	DDS_InstanceHandle_t register_instance_w_timestamp(
		const Data* instance_data,
		const DDS_Time_t* source_timestamp);
	DDS_ReturnCode_t unregister_instance(
		const Data* instance_data,
		InstanceHandle_t handle);
	DDS_ReturnCode_t unregister_instance_w_timestamp(
		const Data* instance_data,
		InstanceHandle_t handle,
		const DDS_Time_t* source_timestamp);
	DDS_ReturnCode_t write(
		const Data* instance_data,
		InstanceHandle_t handle);
	DDS_ReturnCode_t write_w_timestamp(
		const Data* instance_data,
		InstanceHandle_t handle,
		const DDS_Time_t* source_timestamp);
	DDS_ReturnCode_t dispose(
		const Data* instance_data,
		InstanceHandle_t instance_handle);
	DDS_ReturnCode_t dispose_w_timestamp(
		const Data* instance_data,
		InstanceHandle_t instance_handle,
		const DDS_Time_t* source_timestamp);
	DDS_ReturnCode_t get_key_value(
		Data* key_holder,
		InstanceHandle_t handle);
	DDS_InstanceHandle_t lookup_instance(
		const Data* instance_data);

	// non-abstract methods
	DDS_ReturnCode_t set_qos(
		const DDS_DataWriterQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_DataWriterQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_DataWriterListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_DataWriterListener get_listener();
	DDS_Topic get_topic();
	DDS_Publisher get_publisher();
	DDS_ReturnCode_t wait_for_acknowledgments(
		const DDS_Duration_t* max_wait);
	// Access the status
	DDS_ReturnCode_t get_liveliness_lost_status(
		DDS_LivelinessLostStatus* status);
	DDS_ReturnCode_t get_offered_deadline_missed_status(
		DDS_OfferedDeadlineMissedStatus* status);
	DDS_ReturnCode_t get_offered_incompatible_qos_status(
		DDS_OfferedIncompatibleQosStatus* status);
	DDS_ReturnCode_t get_publication_matched_status(
		DDS_PublicationMatchedStatus* status);
	DDS_ReturnCode_t assert_liveliness();
	DDS_ReturnCode_t get_matched_subscriptions(
		DDS_InstanceHandleSeq* subscription_handles);
	DDS_ReturnCode_t get_matched_subscription_data(
		DDS_SubscriptionBuiltinTopicData* subscription_data,
		DDS_InstanceHandle_t subscription_handle);
};

// ----------------------------------------------------------------------
struct _DDS_Subscriber {
	DDS_Entity;
	
	DDS_DataReader create_datareader(
		const DDS_TopicDescription* a_topic,
		const DDS_DataReaderQos* qos,
		const DDS_DataReaderListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_ReturnCode_t delete_datareader(
		const DDS_DataReader* a_datareader);
	DDS_ReturnCode_t delete_contained_entities();
	DDS_DataReader lookup_datareader(
		const char* topic_name);
	DDS_ReturnCode_t get_datareaders(
		DDS_DataReaderSeq* readers,
		const DDS_SampleStateMask* sample_states,
		const DDS_ViewStateMask* view_states,
		const DDS_InstanceStateMask* instance_states);
	DDS_ReturnCode_t notify_datareaders();
	DDS_ReturnCode_t set_qos(
		const DDS_SubscriberQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_SubscriberQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_SubscriberListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_SubscriberListener get_listener();
	DDS_ReturnCode_t begin_access();
	DDS_ReturnCode_t end_access();
	DDS_DomainParticipant get_participant();
	DDS_ReturnCode_t set_default_datareader_qos(
		const DDS_DataReaderQos* qos);
	DDS_ReturnCode_t get_default_datareader_qos(
		DDS_DataReaderQos* qos);
	DDS_ReturnCode_t copy_from_topic_qos(
		DDS_DataReaderQos* a_datareader_qos,
		const DDS_TopicQos* a_topic_qos);
};

struct _DDS_DataReader {
	DDS_Entity;
	
	DDS_ReadCondition create_readcondition(
		const DDS_SampleStateMask* sample_states,
		const DDS_ViewStateMask* view_states,
		const DDS_InstanceStateMask* instance_states);
	DDS_QueryCondition create_querycondition(
		const DDS_SampleStateMask* sample_states,
		const DDS_ViewStateMask* view_states,
		const DDS_InstanceStateMask* instance_states,
		const char* query_expression,
		const DDS_StringSeq* query_parameters);
	DDS_ReturnCode_t delete_readcondition(
		const DDS_ReadCondition* a_condition);
	DDS_ReturnCode_t delete_contained_entities();
	DDS_ReturnCode_t set_qos(
		const DDS_DataReaderQos* qos);
	DDS_ReturnCode_t get_qos(
		DDS_DataReaderQos* qos);
	DDS_ReturnCode_t set_listener(
		const DDS_DataReaderListener* a_listener,
		const DDS_StatusMask* mask);
	DDS_DataReaderListener get_listener();
	DDS_TopicDescription get_topicdescription();
	DDS_Subscriber get_subscriber();
	DDS_ReturnCode_t get_sample_rejected_status(
		DDS_SampleRejectedStatus* status);
	DDS_ReturnCode_t get_liveliness_changed_status(
		DDS_LivelinessChangedStatus* status);
	DDS_ReturnCode_t get_requested_deadline_missed_status(
		DDS_RequestedDeadlineMissedStatus* status);
	DDS_ReturnCode_t get_requested_incompatible_qos_status(
		DDS_RequestedIncompatibleQosStatus* status);
	DDS_ReturnCode_t get_subscription_matched_status(
		DDS_SubscriptionMatchedStatus* status);
	DDS_ReturnCode_t get_sample_lost_status(
		DDS_SampleLostStatus* status);
	DDS_ReturnCode_t wait_for_historical_data(
		const DDS_Duration_t* max_wait);
	DDS_ReturnCode_t get_matched_publications(
		DDS_InstanceHandleSeq* publication_handles);
	DDS_ReturnCode_t get_matched_publication_data(
		DDS_PublicationBuiltinTopicData* publication_data,
		DDS_InstanceHandle_t publication_handle);
};

typedef struct _DDS_SampleInfo {
	DDS_SampleStateKind sample_state;
	DDS_ViewStateKind view_state;
	DDS_InstanceStateKind instance_state;
	DDS_Time_t source_timestamp;
	DDS_InstanceHandle_t instance_handle;
	DDS_InstanceHandle_t publication_handle;
	int32_t disposed_generation_count;
	int32_t no_writers_generation_count;
	int32_t sample_rank;
	int32_t generation_rank;
	int32_t absolute_generation_rank;
	bool valid_data;
} DDS_SampleInfo;

typedef DDS_sequence/*<DDS_SampleInfo>*/ DDS_SampleInfoSeq;

#endif /* __DDS_DSCP_H__ */
