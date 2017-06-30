#ifndef __DDS_DSCP_H__
#define __DDS_DSCP_H__

#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <iostream>

namespace dds {
	typedef int32_t	DOMAINID_TYPE_NATIVE;
	typedef int32_t HANDLE_TYPE_NATIVE;
	typedef int32_t BUILTIN_TOPIC_KEY_TYPE_NATIVE;

	extern const HANDLE_TYPE_NATIVE HANDLE_NIL_NATIVE;
	
	struct DomainParticipantQos;
	struct TopicQos;
	struct PublisherQos;
	struct SubscriberQos;
	struct DataWriterQos;
	struct DataReaderQos;

	extern class DomainParticipantFactory* DDSParticipantFactory;
	extern const DomainParticipantQos PARTICIPANT_QOS_DEFAULT;
	extern const TopicQos TOPIC_QOS_DEFAULT;
	extern const PublisherQos PUBLISHER_QOS_DEFAULT;
	extern const SubscriberQos SUBSCRIBER_QOS_DEFAULT;
	extern const DataWriterQos DATAWRITER_QOS_DEFAULT;
	extern const DataReaderQos DATAREADER_QOS_DEFAULT;
	extern const DataWriterQos DATAWRITER_QOS_USE_TOPIC_QOS;
	extern const DataReaderQos DATAREADER_QOS_USE_TOPIC_QOS;

	// IDL
	template<typename T>
	struct sequence {
		uint32_t maximum;
		uint32_t length;
		
		T* buffer;
		
		sequence operator()(uint32_t max, uint32_t size, T* array) {
			maximum = max;
			length = size;
			buffer = array;
		}

		sequence() {
			maximum = 0;
			length = 0;
			buffer = NULL;
		}
		
		sequence(uint32_t size) {
			maximum = size;
			length = 0;
			buffer = (T*)malloc(sizeof(T) * size);
		}
		
		sequence(T* array, uint32_t size) {
			maximum = size;
			length = size;
			buffer = (T*)malloc(sizeof(T) * size);
			memcpy(buffer, array, sizeof(T) * size);
		}

		sequence(uint32_t max, uint32_t size, T* array) {
			maximum = max;
			length = size;
			buffer = (T*)malloc(sizeof(T) * size);
			memcpy(buffer, array, sizeof(T) * size);
		}

		~sequence() {
			free(buffer);
		}
		
		bool add(T value) {
			if(length < maximum) {
				buffer[length++] = value;
				return true;
			} else {
				return false;
			}
		}
		
		T& operator[](uint32_t index) {
			return buffer[index];
		}
		
		const T& operator[](uint32_t index) const {
			return buffer[index];
		}
		
		friend std::ostream& operator<<(std::ostream& os, const sequence<T>& seq) {
			os << &seq;
			return os;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const sequence<T>* seq) {
			os << "sequence[maximum=" << seq->maximum << ", length=" << seq->length << "]";
			return os;
		}
	};
	
	typedef DOMAINID_TYPE_NATIVE DomainId_t;
	typedef HANDLE_TYPE_NATIVE InstanceHandle_t;
	 
	struct BuiltinTopicKey_t {
		BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3];
		
		BuiltinTopicKey_t();
		BuiltinTopicKey_t(BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3]);
		virtual ~BuiltinTopicKey_t();
	};
	
	typedef sequence<InstanceHandle_t> InstanceHandleSeq;
	
	typedef int32_t ReturnCode_t;
	typedef int32_t QosPolicyId_t;
	typedef sequence<char*> StringSeq;
	
	struct Duration_t {
		int32_t sec;
		uint32_t nanosec;
		
		Duration_t();
		Duration_t operator()(int32_t sec, uint32_t nanosec);
		Duration_t(int32_t sec, uint32_t nanosec);
		virtual ~Duration_t();
	};
	
	struct Time_t {
		int32_t sec;
		uint32_t nanosec;
		
		Time_t();
		Time_t(int32_t sec, uint32_t nanosec);
		virtual ~Time_t();
	};
	
	// ----------------------------------------------------------------------
	// Pre-defined values
	// ----------------------------------------------------------------------
	extern const InstanceHandle_t HANDLE_NIL;
	
	extern const int32_t LENGTH_UNLIMITED;
	
	extern const int32_t DURATION_INFINITE_SEC;
	extern const uint32_t DURATION_INFINITE_NSEC;
	
	extern const int32_t DURATION_ZERO_SEC;
	extern const uint32_t DURATION_ZERO_NSEC;
	
	extern const int32_t TIME_INVALID_SEC;
	extern const uint32_t TIME_INVALID_NSEC;
	
	// ----------------------------------------------------------------------
	// Return codes
	// ----------------------------------------------------------------------
	extern const ReturnCode_t RETCODE_OK;
	extern const ReturnCode_t RETCODE_ERROR;
	extern const ReturnCode_t RETCODE_UNSUPPORTED;
	extern const ReturnCode_t RETCODE_BAD_PARAMETER;
	extern const ReturnCode_t RETCODE_PRECONDITION_NOT_MET;
	extern const ReturnCode_t RETCODE_OUT_OF_RESOURCES;
	extern const ReturnCode_t RETCODE_NOT_ENABLED;
	extern const ReturnCode_t RETCODE_IMMUTABLE_POLICY;
	extern const ReturnCode_t RETCODE_INCONSISTENT_POLICY;
	extern const ReturnCode_t RETCODE_ALREADY_DELETED;
	extern const ReturnCode_t RETCODE_TIMEOUT;
	extern const ReturnCode_t RETCODE_NO_DATA;
	extern const ReturnCode_t RETCODE_ILLEGAL_OPERATION;
	
	// ----------------------------------------------------------------------
	// Status to support listeners and conditions
	// ----------------------------------------------------------------------
	
	typedef uint32_t StatusKind;
	typedef uint32_t StatusMask;	// bit-mask StatusKind
	
	extern const StatusKind INCONSISTENT_TOPIC_STATUS;
	extern const StatusKind OFFERED_DEADLINE_MISSED_STATUS;
	extern const StatusKind REQUESTED_DEADLINE_MISSED_STATUS;
	extern const StatusKind OFFERED_INCOMPATIBLE_QOS_STATUS;
	extern const StatusKind REQUESTED_INCOMPATIBLE_QOS_STATUS;
	extern const StatusKind SAMPLE_LOST_STATUS;
	extern const StatusKind SAMPLE_REJECTED_STATUS;
	extern const StatusKind DATA_ON_READERS_STATUS;
	extern const StatusKind DATA_AVAILABLE_STATUS;
	extern const StatusKind LIVELINESS_LOST_STATUS;
	extern const StatusKind LIVELINESS_CHANGED_STATUS;
	extern const StatusKind PUBLICATION_MATCHED_STATUS;
	extern const StatusKind SUBSCRIPTION_MATCHED_STATUS;
	
	struct InconsistentTopicStatus {
		int32_t total_count;
		int32_t total_count_change;
		
		InconsistentTopicStatus();
		InconsistentTopicStatus(int32_t total_count, int32_t total_count_change);
		virtual ~InconsistentTopicStatus();
	};
	
	struct SampleLostStatus {
		int32_t total_count;
		int32_t total_count_change;
		
		SampleLostStatus();
		SampleLostStatus(int32_t total_count, int32_t total_count_change);
		virtual ~SampleLostStatus();
	};
	
	enum SampleRejectedStatusKind {
		NOT_REJECTED,
		REJECTED_BY_INSTANCES_LIMIT,
		REJECTED_BY_SAMPLES_LIMIT,
		REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
	};
	
	struct SampleRejectedStatus {
		int32_t						total_count;
		int32_t						total_count_change;
		SampleRejectedStatusKind	last_reason;
		InstanceHandle_t			last_instance_handle;
		
		SampleRejectedStatus();
		SampleRejectedStatus(
			int32_t total_count, 
			int32_t total_count_change, 
			SampleRejectedStatusKind last_reason, 
			InstanceHandle_t last_instance_handle);
		virtual ~SampleRejectedStatus();
	};
	
	struct LivelinessLostStatus {
		int32_t	total_count;
		int32_t	total_count_change;
		
		LivelinessLostStatus();
		LivelinessLostStatus(int32_t total_count, int32_t total_count_change);
		virtual ~LivelinessLostStatus();
	};
	
	struct LivelinessChangedStatus {
		int32_t				alive_count;
		int32_t				not_alive_count;
		int32_t				alive_count_change;
		int32_t				not_alive_count_change;
		InstanceHandle_t	last_publication_handle;
		
		LivelinessChangedStatus();
		LivelinessChangedStatus(
			int32_t alive_count, 
			int32_t not_alive_count, 
			int32_t alive_count_change, 
			int32_t not_alive_count_change, 
			InstanceHandle_t last_publication_handle);
		virtual ~LivelinessChangedStatus();
	};
	
	struct OfferedDeadlineMissedStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		InstanceHandle_t	last_instance_handle;
		
	 	OfferedDeadlineMissedStatus();
	 	OfferedDeadlineMissedStatus(
			int32_t total_count,
			int32_t total_count_change,
			InstanceHandle_t last_instance_handle);
	 	virtual ~OfferedDeadlineMissedStatus();
	};
	
	struct RequestedDeadlineMissedStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		InstanceHandle_t	last_instance_handle;
		
		RequestedDeadlineMissedStatus();
		RequestedDeadlineMissedStatus(
			int32_t total_count,
			int32_t total_count_change,
			InstanceHandle_t last_instance_handle);
		virtual ~RequestedDeadlineMissedStatus();
	};
	
	struct QosPolicyCount {
		QosPolicyId_t	policy_id;
		int32_t			count;
		
		QosPolicyCount();
		QosPolicyCount(
			QosPolicyId_t policy_id,
			int32_t count);
		virtual ~QosPolicyCount();
	};
	
	typedef sequence<QosPolicyCount> QosPolicyCountSeq;
	
	struct OfferedIncompatibleQosStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		QosPolicyId_t		last_policy_id;
		QosPolicyCountSeq*	policies;
		
		OfferedIncompatibleQosStatus();
		OfferedIncompatibleQosStatus(
			int32_t total_count,
			int32_t total_count_change,
			QosPolicyId_t last_policy_id,
			QosPolicyCountSeq* policies);
		virtual ~OfferedIncompatibleQosStatus();
	};
	
	struct RequestedIncompatibleQosStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		QosPolicyId_t		last_policy_id;
		QosPolicyCountSeq*	policies;
		
		RequestedIncompatibleQosStatus();
		RequestedIncompatibleQosStatus(
			int32_t total_count,
			int32_t total_count_change,
			QosPolicyId_t last_policy_id,
			QosPolicyCountSeq* policies);
		virtual ~RequestedIncompatibleQosStatus();
	};
	
	struct PublicationMatchedStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		int32_t				current_count;
		int32_t				current_count_change;
		InstanceHandle_t	last_subscription_handle;
		
		PublicationMatchedStatus();
		PublicationMatchedStatus(
			int32_t total_count,
			int32_t total_count_change,
			int32_t current_count,
			int32_t current_count_change,
			InstanceHandle_t last_subscription_handle);
		virtual ~PublicationMatchedStatus();
	};
	
	struct SubscriptionMatchedStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		int32_t				current_count;
		int32_t				current_count_change;
		InstanceHandle_t	last_publication_handle;
		
		SubscriptionMatchedStatus();
		SubscriptionMatchedStatus(
			int32_t total_count,
			int32_t total_count_change,
			int32_t current_count,
			int32_t current_count_change,
			InstanceHandle_t last_publication_handle);
		virtual ~SubscriptionMatchedStatus();
	};
	
	// ----------------------------------------------------------------------
	// Listeners
	// ----------------------------------------------------------------------
	
	class Listener;
	class Entity;
	class TopicDescription;
	class Topic;
	class ContentFilteredTopic;
	class MultiTopic;
	class DataWriter;
	class DataReader;
	class Subscriber;
	class Publisher;
	
	typedef sequence<DataReader> DataReaderSeq;
	
	class Listener {
	public:
		Listener();
		virtual ~Listener();
	};
	
	class TopicListener : public Listener {
	public:
		TopicListener();
		virtual ~TopicListener();
		
		virtual void on_inconsistent_topic(Topic* the_topic, 
			const InconsistentTopicStatus& status);
	};
	
	class DataWriterListener : public Listener {
	public:
		DataWriterListener();
		virtual ~DataWriterListener();
		
		virtual void on_offered_deadline_missed(
			DataWriter* writer, 
			const OfferedDeadlineMissedStatus& status);
		virtual void on_offered_incompatible_qos(
			DataWriter* writer, 
			const OfferedIncompatibleQosStatus& status);
		virtual void on_liveliness_lost(
			DataWriter* writer, 
			const LivelinessLostStatus& status);
		virtual void on_publication_matched(
			DataWriter* writer, 
			const PublicationMatchedStatus& status);
	};
	
	class PublisherListener : public DataWriterListener {
	public:
		PublisherListener();
		virtual ~PublisherListener();
	};
	
	class DataReaderListener : public Listener {
	public:
		DataReaderListener();
		virtual ~DataReaderListener();
		
		virtual void on_requested_deadline_missed(
			DataReader* the_reader, 
			const RequestedDeadlineMissedStatus& status);
		virtual void on_requested_incompatible_qos(
			DataReader* the_reader, 
			const RequestedIncompatibleQosStatus& status);
		virtual void on_sample_rejected(
			DataReader* the_reader,
			const SampleRejectedStatus& status);
		virtual void on_liveliness_changed(
			DataReader* the_reader,
			const LivelinessChangedStatus& status);
		virtual void on_data_available(
			DataReader* the_reader);
		virtual void on_subscription_matched(
			DataReader* the_reader,
			const SubscriptionMatchedStatus& status);
		virtual void on_sample_lost(
			DataReader* the_reader,
			const SampleLostStatus& status);
	};
	
	class SubscriberListener : public DataReaderListener {
	public:
		SubscriberListener();
		virtual ~SubscriberListener();
		
		virtual void on_data_on_readers(
			Subscriber* the_subscriber);
	};
	
	class DomainParticipantListener : public TopicListener,
					public PublisherListener,
					public SubscriberListener {
	public:
		DomainParticipantListener();
		virtual ~DomainParticipantListener();
	};
	
	// ----------------------------------------------------------------------
	// Conditions
	// ----------------------------------------------------------------------
	
	class Condition {
	public:
		Condition();
		virtual ~Condition();
		
		virtual bool get_trigger_value();
	};
	
	typedef sequence<Condition> ConditionSeq;
	
	class WaitSet {
	public:
		WaitSet();
		virtual ~WaitSet();
		
		ReturnCode_t wait(
			ConditionSeq* active_conditions,
			const Duration_t* timeout);
		ReturnCode_t attach_condition(
			const Condition* cond);
		ReturnCode_t detach_condition(
			const Condition* cond);
		ReturnCode_t get_conditions(
			ConditionSeq* attached_conditions);
	};
	
	class GuardCondition : public Condition {
	public:
		GuardCondition();
		virtual ~GuardCondition();
		
		ReturnCode_t set_trigger_value(
			bool value);
	};
	
	class StatusCondition : public Condition {
	public:
		StatusCondition();
		virtual ~StatusCondition();
		
		StatusMask get_enabled_statuses();
		ReturnCode_t set_enabled_statuses(
			const StatusMask mask);
		Entity* get_entity();
	};
	
	// Sample states to support reads
	typedef uint32_t SampleStateKind;
	extern const SampleStateKind READ_SAMPLE_STATE;
	extern const SampleStateKind NOT_READ_SAMPLE_STATE;
	
	// This is a bit-mask SampleStateKind
	typedef uint32_t SampleStateMask;
	extern const SampleStateMask ANY_SAMPLE_STATE;
	
	// View states to support reads
	typedef uint32_t ViewStateKind;
	extern const ViewStateKind NEW_VIEW_STATE;
	extern const ViewStateKind NOT_NEW_VIEW_STATE;
	
	// This is a bit-mask ViewStateKind
	typedef uint32_t ViewStateMask;
	extern const ViewStateMask ANY_VIEW_STATE;
	
	// Instance states to support reads
	typedef uint32_t InstanceStateKind;
	extern const InstanceStateKind ALIVE_INSTANCE_STATE;
	extern const InstanceStateKind NOT_ALIVE_DISPOSED_INSTANCE_STATE;
	extern const InstanceStateKind NOT_ALIVE_NO_WRITERS_INSTANCE_STATE;
	
	// This is a bit-mask InstanceStateKind
	typedef uint32_t InstanceStateMask;
	extern const InstanceStateMask ANY_INSTANCE_STATE;
	extern const InstanceStateMask NOT_ALIVE_INSTANCE_STATE;
	
	class ReadCondition : public Condition {
	public:
		ReadCondition();
		virtual ~ReadCondition();
		
		SampleStateMask* get_sample_state_mask();
		ViewStateMask* get_view_state_mask();
		InstanceStateMask* get_instance_state_mask();
		DataReader* get_datareader();
	};
	
	class QueryCondition : public ReadCondition {
	public:
		QueryCondition();
		virtual ~QueryCondition();
		
		const char* get_query_expression();
		ReturnCode_t get_query_parameters(
			StringSeq* query_parameters);
		ReturnCode_t set_query_parameters(
			const StringSeq* query_parameters);
	};
	
	// ----------------------------------------------------------------------
	// Qos
	// ----------------------------------------------------------------------
	extern const char* USERDATA_QOS_POLICY_NAME;
	extern const char* DURABILITY_QOS_POLICY_NAME;
	extern const char* PRESENTATION_QOS_POLICY_NAME;
	extern const char* DEADLINE_QOS_POLICY_NAME;
	extern const char* LATENCYBUDGET_QOS_POLICY_NAME;
	extern const char* OWNERSHIP_QOS_POLICY_NAME;
	extern const char* OWNERSHIPSTRENGTH_QOS_POLICY_NAME;
	extern const char* LIVELINESS_QOS_POLICY_NAME;
	extern const char* TIMEBASEDFILTER_QOS_POLICY_NAME;
	extern const char* PARTITION_QOS_POLICY_NAME;
	extern const char* RELIABILITY_QOS_POLICY_NAME;
	extern const char* DESTINATIONORDER_QOS_POLICY_NAME;
	extern const char* HISTORY_QOS_POLICY_NAME;
	extern const char* RESOURCELIMITS_QOS_POLICY_NAME;
	extern const char* ENTITYFACTORY_QOS_POLICY_NAME;
	extern const char* WRITERDATALIFECYCLE_QOS_POLICY_NAME;
	extern const char* READERDATALIFECYCLE_QOS_POLICY_NAME;
	extern const char* TOPICDATA_QOS_POLICY_NAME;
	extern const char* GROUPDATA_QOS_POLICY_NAME;
	extern const char* LIFESPAN_QOS_POLICY_NAME;
	extern const char* DURABILITYSERVICE_POLICY_NAME;
	
	extern const QosPolicyId_t INVALID_QOS_POLICY_ID;
	extern const QosPolicyId_t USERDATA_QOS_POLICY_ID;
	extern const QosPolicyId_t DURABILITY_QOS_POLICY_ID;
	extern const QosPolicyId_t PRESENTATION_QOS_POLICY_ID;
	extern const QosPolicyId_t DEADLINE_QOS_POLICY_ID;
	extern const QosPolicyId_t LATENCYBUDGET_QOS_POLICY_ID;
	extern const QosPolicyId_t OWNERSHIP_QOS_POLICY_ID;
	extern const QosPolicyId_t OWNERSHIPSTRENGTH_QOS_POLICY_ID;
	extern const QosPolicyId_t LIVELINESS_QOS_POLICY_ID;
	extern const QosPolicyId_t TIMEBASEDFILTER_QOS_POLICY_ID;
	extern const QosPolicyId_t PARTITION_QOS_POLICY_ID;
	extern const QosPolicyId_t RELIABILITY_QOS_POLICY_ID;
	extern const QosPolicyId_t DESTINATIONORDER_QOS_POLICY_ID;
	extern const QosPolicyId_t HISTORY_QOS_POLICY_ID;
	extern const QosPolicyId_t RESOURCELIMITS_QOS_POLICY_ID;
	extern const QosPolicyId_t ENTITYFACTORY_QOS_POLICY_ID;
	extern const QosPolicyId_t WRITERDATALIFECYCLE_QOS_POLICY_ID;
	extern const QosPolicyId_t READERDATALIFECYCLE_QOS_POLICY_ID;
	extern const QosPolicyId_t TOPICDATA_QOS_POLICY_ID;
	extern const QosPolicyId_t GROUPDATA_QOS_POLICY_ID;
	extern const QosPolicyId_t TRANSPORTPRIORITY_QOS_POLICY_ID;
	extern const QosPolicyId_t LIFESPAN_QOS_POLICY_ID;
	extern const QosPolicyId_t DURABILITYSERVICE_QOS_POLICY_ID;
	
	struct UserDataQosPolicy {
		sequence<uint8_t> value;
		
		UserDataQosPolicy();
		UserDataQosPolicy(sequence<uint8_t>& value);
		UserDataQosPolicy(uint8_t* array, uint32_t size);
		virtual ~UserDataQosPolicy();
	};
	
	struct TopicDataQosPolicy {
		sequence<uint8_t> value;
		
		TopicDataQosPolicy();
		TopicDataQosPolicy(sequence<uint8_t>& value);
		TopicDataQosPolicy(uint8_t* array, uint32_t size);
		virtual ~TopicDataQosPolicy();
	};
	
	struct GroupDataQosPolicy {
		sequence<uint8_t> value;
		
		GroupDataQosPolicy();
		GroupDataQosPolicy(sequence<uint8_t>& value);
		GroupDataQosPolicy(uint8_t* array, uint32_t size);
		virtual ~GroupDataQosPolicy();
	};
	
	struct TransportPriorityQosPolicy {
		int32_t value;
		
		TransportPriorityQosPolicy();
		TransportPriorityQosPolicy(int32_t value);
		virtual ~TransportPriorityQosPolicy();
	};
	
	struct LifespanQosPolicy {
		Duration_t duration;
		
		LifespanQosPolicy();
		LifespanQosPolicy(Duration_t& duration);
		LifespanQosPolicy(int32_t sec, uint32_t nanosec);
		virtual ~LifespanQosPolicy();
	};
	
	enum DurabilityQosPolicyKind {
		VOLATILE_DURABILITY_QOS,
		TRANSIENT_LOCAL_DURABILITY_QOS,
		TRANSIENT_DURABILITY_QOS,
		PERSISTENT_DURABILITY_QOS
	};
	
	struct DurabilityQosPolicy {
		DurabilityQosPolicyKind kind;
		
		DurabilityQosPolicy();
		DurabilityQosPolicy(DurabilityQosPolicyKind kind);
		virtual ~DurabilityQosPolicy();
	};
	
	enum PresentationQosPolicyAccessScopeKind {
		INSTANCE_PRESENTATION_QOS,
		TOPIC_PRESENTATION_QOS,
		GROUP_PRESENTATION_QOS
	};
	
	struct PresentationQosPolicy {
		PresentationQosPolicyAccessScopeKind access_scope;
		bool coherent_access;
		bool ordered_access;
		
		PresentationQosPolicy();
		PresentationQosPolicy(
			PresentationQosPolicyAccessScopeKind access_scope,
			bool coherent_access,
			bool ordered_access);
		virtual ~PresentationQosPolicy();
	};
	
	struct DeadlineQosPolicy {
		Duration_t period;
		
		DeadlineQosPolicy();
		DeadlineQosPolicy(Duration_t& period);
		DeadlineQosPolicy(int32_t sec, uint32_t nanosec);
		virtual ~DeadlineQosPolicy();
	};
	
	struct LatencyBudgetQosPolicy {
		Duration_t duration;
		
		LatencyBudgetQosPolicy();
		LatencyBudgetQosPolicy(Duration_t& duration);
		LatencyBudgetQosPolicy(int32_t sec, uint32_t nanosec);
		virtual ~LatencyBudgetQosPolicy();
	};
	
	enum OwnershipQosPolicyKind {
		SHARED_OWNERSHIP_QOS,
		EXCLUSIVE_OWNERSHIP_QOS
	};
	
	struct OwnershipQosPolicy {
		OwnershipQosPolicyKind kind;
		
		OwnershipQosPolicy();
		OwnershipQosPolicy(OwnershipQosPolicyKind kind);
		virtual ~OwnershipQosPolicy();
	};
	
	struct OwnershipStrengthQosPolicy {
		int32_t value;
		
		OwnershipStrengthQosPolicy();
		OwnershipStrengthQosPolicy(int32_t value);
		virtual ~OwnershipStrengthQosPolicy();
	};
	
	enum LivelinessQosPolicyKind {
		AUTOMATIC_LIVELINESS_QOS,
		MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
		MANUAL_BY_TOPIC_LIVELINESS_QOS
	};
	
	struct LivelinessQosPolicy {
		LivelinessQosPolicyKind kind;
		Duration_t lease_duration;
		
		LivelinessQosPolicy();
		LivelinessQosPolicy(
			LivelinessQosPolicyKind kind,
			Duration_t& lease_duration);
		virtual ~LivelinessQosPolicy();
	};
	
	struct TimeBasedFilterQosPolicy {
		Duration_t minimum_separation;
		
		TimeBasedFilterQosPolicy();
		TimeBasedFilterQosPolicy(Duration_t& minimum_separation);
		virtual ~TimeBasedFilterQosPolicy();
	};
	
	struct PartitionQosPolicy {
		StringSeq name;
		
		PartitionQosPolicy();
		PartitionQosPolicy(StringSeq name);
		virtual ~PartitionQosPolicy();
	};
	
	enum ReliabilityQosPolicyKind {
		BEST_EFFORT_RELIABILITY_QOS,
		RELIABLE_RELIABILITY_QOS
	};
	
	struct ReliabilityQosPolicy {
		ReliabilityQosPolicyKind kind;
		Duration_t max_blocking_time;
		
		ReliabilityQosPolicy();
		ReliabilityQosPolicy(
			ReliabilityQosPolicyKind kind,
			Duration_t& max_blocking_time);
		virtual ~ReliabilityQosPolicy();
	};
	
	enum DestinationOrderQosPolicyKind {
		BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
		BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
	};
	
	struct DestinationOrderQosPolicy {
		DestinationOrderQosPolicyKind kind;
		
		DestinationOrderQosPolicy();
		DestinationOrderQosPolicy(DestinationOrderQosPolicyKind kind);
		virtual ~DestinationOrderQosPolicy();
	};
	
	enum HistoryQosPolicyKind {
		KEEP_LAST_HISTORY_QOS,
		KEEP_ALL_HISTORY_QOS
	};
	 
	struct HistoryQosPolicy {
		HistoryQosPolicyKind kind;
		int32_t depth;
		
		HistoryQosPolicy();
		HistoryQosPolicy(
			HistoryQosPolicyKind kind,
			int32_t depth);
		virtual ~HistoryQosPolicy();
	};
	
	struct ResourceLimitsQosPolicy {
		int32_t max_samples;
		int32_t max_instances;
		int32_t max_samples_per_instance;
		
		ResourceLimitsQosPolicy();
		ResourceLimitsQosPolicy(
			int32_t max_samples,
			int32_t max_instances,
			int32_t max_samples_per_instance);
		virtual ~ResourceLimitsQosPolicy();
	};
	
	struct EntityFactoryQosPolicy {
		bool autoenable_created_entities;
		
		EntityFactoryQosPolicy();
		EntityFactoryQosPolicy(bool autoenable_created_entities);
		virtual ~EntityFactoryQosPolicy();
	};
	
	struct WriterDataLifecycleQosPolicy {
		bool autodispose_unregistered_instances;
		
		WriterDataLifecycleQosPolicy();
		WriterDataLifecycleQosPolicy(bool autodispose_unregistered_instances);
		virtual ~WriterDataLifecycleQosPolicy();
	};
	
	struct ReaderDataLifecycleQosPolicy {
		Duration_t autopurge_nowriter_samples_delay;
		Duration_t autopurge_disposed_samples_delay;
		
		ReaderDataLifecycleQosPolicy();
		ReaderDataLifecycleQosPolicy(
			Duration_t& autopurge_nowriter_samples_delay,
			Duration_t& autopurge_disposed_samples_delay);
		virtual ~ReaderDataLifecycleQosPolicy();
	};
	
	struct DurabilityServiceQosPolicy {
		Duration_t				service_cleanup_delay;
		HistoryQosPolicyKind	history_kind;
		int32_t					history_depth;
		int32_t					max_samples;
		int32_t					max_instances;
		int32_t					max_samples_per_instance;
		
		DurabilityServiceQosPolicy();
		DurabilityServiceQosPolicy(
			Duration_t& service_cleanup_delay,
			HistoryQosPolicyKind history_kind,
			int32_t history_depth,
			int32_t max_samples,
			int32_t max_instances,
			int32_t max_samples_per_instance);
		virtual ~DurabilityServiceQosPolicy();
	};

	struct DomainParticipantFactoryQos {
		EntityFactoryQosPolicy entity_factory;

		DomainParticipantFactoryQos();
		DomainParticipantFactoryQos(EntityFactoryQosPolicy& entity_factory);
		virtual ~DomainParticipantFactoryQos();
	};

	struct DomainParticipantQos {
		UserDataQosPolicy		user_data;
		EntityFactoryQosPolicy	entity_factory;

		DomainParticipantQos();
		DomainParticipantQos(
			UserDataQosPolicy& user_data,
			EntityFactoryQosPolicy& entity_factory);
		virtual ~DomainParticipantQos();
	};

	struct TopicQos {
		TopicDataQosPolicy			topic_data;
		DurabilityQosPolicy		durability;
		DurabilityServiceQosPolicy	durability_service;
		DeadlineQosPolicy			deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		DestinationOrderQosPolicy	destination_order;
		HistoryQosPolicy			history;
		ResourceLimitsQosPolicy	resource_limits;
		TransportPriorityQosPolicy	transport_priority;
		LifespanQosPolicy			lifespan;
		OwnershipQosPolicy			ownership;
		
		TopicQos();
		TopicQos(
			TopicDataQosPolicy& topic_data,
			DurabilityQosPolicy& durability,
			DurabilityServiceQosPolicy& durability_service,
			DeadlineQosPolicy& deadline,
			LatencyBudgetQosPolicy& latency_budget,
			LivelinessQosPolicy& liveliness,
			ReliabilityQosPolicy& reliability,
			DestinationOrderQosPolicy& destination_order,
			HistoryQosPolicy& history,
			ResourceLimitsQosPolicy& resource_limits,
			TransportPriorityQosPolicy& transport_priority,
			LifespanQosPolicy& lifespan,
			OwnershipQosPolicy& ownership);
		virtual ~TopicQos();
	};
	
	struct DataWriterQos {
		DurabilityQosPolicy			durability;
		DurabilityServiceQosPolicy		durability_service;
		DeadlineQosPolicy				deadline;
		LatencyBudgetQosPolicy			latency_budget;
		LivelinessQosPolicy			liveliness;
		ReliabilityQosPolicy			reliability;
		DestinationOrderQosPolicy		destination_order;
		HistoryQosPolicy				history;
		ResourceLimitsQosPolicy		resource_limits;
		TransportPriorityQosPolicy		transport_priority;
		LifespanQosPolicy				lifespan;
		UserDataQosPolicy				user_data;
		OwnershipQosPolicy				ownership;
		OwnershipStrengthQosPolicy		ownership_strength;
		WriterDataLifecycleQosPolicy	writer_data_lifecycle;

		DataWriterQos();
		DataWriterQos(
			DurabilityQosPolicy& durability,
			DurabilityServiceQosPolicy& durability_service,
			DeadlineQosPolicy& deadline,
			LatencyBudgetQosPolicy& latency_budget,
			LivelinessQosPolicy& liveliness,
			ReliabilityQosPolicy& reliability,
			DestinationOrderQosPolicy& destination_order,
			HistoryQosPolicy& history,
			ResourceLimitsQosPolicy& resource_limits,
			TransportPriorityQosPolicy& transport_priority,
			LifespanQosPolicy& lifespan,
			UserDataQosPolicy& user_data,
			OwnershipQosPolicy& ownership,
			OwnershipStrengthQosPolicy& ownership_strength,
			WriterDataLifecycleQosPolicy& writer_data_lifecycle);
		virtual ~DataWriterQos();
	};
	
	struct PublisherQos {
		PresentationQosPolicy		presentation;
		PartitionQosPolicy			partition;
		GroupDataQosPolicy			group_data;
		EntityFactoryQosPolicy		entity_factory;
		
		PublisherQos();
		PublisherQos(
			PresentationQosPolicy& presentation,
			PartitionQosPolicy& partition,
			GroupDataQosPolicy& group_data,
			EntityFactoryQosPolicy& entity_factory);
		virtual ~PublisherQos();
	};
	
	struct DataReaderQos {
		DurabilityQosPolicy			durability;
		DeadlineQosPolicy				deadline;
		LatencyBudgetQosPolicy			latency_budget;
		LivelinessQosPolicy			liveliness;
		ReliabilityQosPolicy			reliability;
		DestinationOrderQosPolicy		destination_order;
		HistoryQosPolicy				history;
		ResourceLimitsQosPolicy		resource_limits;
		UserDataQosPolicy				user_data;
		OwnershipQosPolicy				ownership;
		TimeBasedFilterQosPolicy		time_based_filter;
		ReaderDataLifecycleQosPolicy	reader_data_lifecycle;
		
		DataReaderQos();
		DataReaderQos(
			DurabilityQosPolicy& durability,
			DeadlineQosPolicy& deadline,
			LatencyBudgetQosPolicy& latency_budget,
			LivelinessQosPolicy& liveliness,
			ReliabilityQosPolicy& reliability,
			DestinationOrderQosPolicy& destination_order,
			HistoryQosPolicy& history,
			ResourceLimitsQosPolicy& resource_limits,
			UserDataQosPolicy& user_data,
			OwnershipQosPolicy& ownership,
			TimeBasedFilterQosPolicy& time_based_filter,
			ReaderDataLifecycleQosPolicy& reader_data_lifecycle);
		virtual ~DataReaderQos();
	};
	
	struct SubscriberQos {
		PresentationQosPolicy		presentation;
		PartitionQosPolicy			partition;
		GroupDataQosPolicy			group_data;
		EntityFactoryQosPolicy		entity_factory;
		
		SubscriberQos();
		SubscriberQos(
			PresentationQosPolicy& presentation,
			PartitionQosPolicy& partition,
			GroupDataQosPolicy& group_data,
			EntityFactoryQosPolicy& entity_factory);
		virtual ~SubscriberQos();
	};
	
	// ----------------------------------------------------------------------
	struct ParticipantBuiltinTopicData {
		BuiltinTopicKey_t		key;
		UserDataQosPolicy*		user_data;
		
		ParticipantBuiltinTopicData();
		ParticipantBuiltinTopicData(
			BuiltinTopicKey_t key,
			UserDataQosPolicy* user_data);
		virtual ~ParticipantBuiltinTopicData();
	};
	
	struct TopicBuiltinTopicData {
		BuiltinTopicKey_t			key;
		char*						name;
		char*						type_name;
		DurabilityQosPolicy*		durability;
		DurabilityServiceQosPolicy*	durability_service;
		DeadlineQosPolicy*			deadline;
		LatencyBudgetQosPolicy*		latency_budget;
		LivelinessQosPolicy*		liveliness;
		ReliabilityQosPolicy*		reliability;
		TransportPriorityQosPolicy*	transport_priority;
		LifespanQosPolicy*			lifespan;
		DestinationOrderQosPolicy*	destination_order;
		HistoryQosPolicy*			history;
		ResourceLimitsQosPolicy*	resource_limits;
		OwnershipQosPolicy*			ownership;
		TopicDataQosPolicy*			topic_data;
		
		TopicBuiltinTopicData();
		TopicBuiltinTopicData(
			BuiltinTopicKey_t key,
			const char* name,
			const char* type_name,
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
			TopicDataQosPolicy* topic_data);
		virtual ~TopicBuiltinTopicData();
	};
	
	struct PublicationBuiltinTopicData {
		BuiltinTopicKey_t			key;
		BuiltinTopicKey_t			participant_key;
		char*						topic_name;
		char*						type_name;
		DurabilityQosPolicy*		durability;
		DurabilityServiceQosPolicy*	durability_service;
		DeadlineQosPolicy*			deadline;
		LatencyBudgetQosPolicy*		latency_budget;
		LivelinessQosPolicy*		liveliness;
		ReliabilityQosPolicy*		reliability;
		LifespanQosPolicy*			lifespan;
		UserDataQosPolicy*			user_data;
		OwnershipQosPolicy*			ownership;
		OwnershipStrengthQosPolicy*	ownership_strength;
		DestinationOrderQosPolicy*	destination_order;
		PresentationQosPolicy*		presentation;
		PartitionQosPolicy*			partition;
		TopicDataQosPolicy*			topic_data;
		GroupDataQosPolicy*			group_data;
		
		PublicationBuiltinTopicData();
		PublicationBuiltinTopicData(
			BuiltinTopicKey_t key,
			BuiltinTopicKey_t participant_key,
			const char* topic_name,
			const char* type_name,
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
			GroupDataQosPolicy* group_data);
		virtual ~PublicationBuiltinTopicData();
	};
	
	struct SubscriptionBuiltinTopicData {
		BuiltinTopicKey_t			key;
		BuiltinTopicKey_t			participant_key;
		char*						topic_name;
		char*						type_name;
		DurabilityQosPolicy*		durability;
		DeadlineQosPolicy*			deadline;
		LatencyBudgetQosPolicy*		latency_budget;
		LivelinessQosPolicy*		liveliness;
		ReliabilityQosPolicy*		reliability;
		OwnershipQosPolicy*			ownership;
		DestinationOrderQosPolicy*	destination_order;
		UserDataQosPolicy*			user_data;
		TimeBasedFilterQosPolicy*	time_based_filter;
		PresentationQosPolicy*		presentation;
		PartitionQosPolicy*			partition;
		TopicDataQosPolicy*			topic_data;
		GroupDataQosPolicy*			group_data;
		
		SubscriptionBuiltinTopicData();
		SubscriptionBuiltinTopicData(
			BuiltinTopicKey_t key,
			BuiltinTopicKey_t participant_key,
			const char* topic_name,
			const char* type_name,
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
			GroupDataQosPolicy* group_data);
		virtual ~SubscriptionBuiltinTopicData();
	};
	
	// ----------------------------------------------------------------------
	class Entity {
	public:
		Entity();
		virtual ~Entity();
		
		// abstract ReturnCode_t set_qos(
		// 	const EntityQos* qos);
		// abstract ReturnCode_t get_qos(
		// 	EntityQos* qos);
		// abstract ReturnCode_t set_listener(
		// 	const Listener* l,
		// 	const StatusMask mask);
		// abstract Listener* get_listener();
		
		virtual ReturnCode_t enable();
		virtual StatusCondition* get_statuscondition();
		virtual StatusMask get_status_changes();
		virtual InstanceHandle_t get_instance_handle();
	};
	
	// ----------------------------------------------------------------------
	class DomainParticipant : public Entity {
	public:
		DomainParticipant();
		virtual ~DomainParticipant();
		
		// Factory interfaces
		virtual Publisher* create_publisher(
			const PublisherQos& qos,
			PublisherListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_publisher(
			const Publisher* p);
		Subscriber* create_subscriber(
			const SubscriberQos& qos,
			SubscriberListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_subscriber(
			const Subscriber* s);
		Subscriber* get_builtin_subscriber();
		virtual Topic* create_topic(
			const char* topic_name,
			const char* type_name,
			const TopicQos& qos,
			TopicListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_topic(
			Topic* a_topic);
		Topic* find_topic(
			const char* topic_name,
			const Duration_t* timeout);
		TopicDescription* lookup_topicdescription(
			const char* name);
		ContentFilteredTopic* create_contentfilteredtopic(
			const char* name,
			Topic* related_topic,
			const char* filter_expression,
			const StringSeq* expression_parameters);
		ReturnCode_t delete_contentfilteredtopic(
			const ContentFilteredTopic* a_contentfilteredtopic);
		MultiTopic* create_multitopic(
			const char* name,
			const char* type_name,
			const char* subscription_expression,
			const StringSeq* expression_parameters);
		ReturnCode_t delete_multitopic(
			const MultiTopic* a_multitopic);
		virtual ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const DomainParticipantQos& qos);
		ReturnCode_t get_qos(
			DomainParticipantQos& qos);
		ReturnCode_t set_listener(
			DomainParticipantListener* a_listener,
			const StatusMask mask);
		DomainParticipantListener* get_listener();
		ReturnCode_t ignore_participant(
			InstanceHandle_t handle);
		ReturnCode_t ignore_topic(
			InstanceHandle_t handle);
		ReturnCode_t ignore_publication(
			InstanceHandle_t handle);
		ReturnCode_t ignore_subscription(
			InstanceHandle_t handle);
		DomainId_t get_domain_id();
		ReturnCode_t assert_liveliness();
		ReturnCode_t set_default_publisher_qos(
			const PublisherQos& qos);
		ReturnCode_t get_default_publisher_qos(
			PublisherQos& qos);
		ReturnCode_t set_default_subscriber_qos(
			const SubscriberQos& qos);
		ReturnCode_t get_default_subscriber_qos(
			SubscriberQos& qos);
		ReturnCode_t set_default_topic_qos(
			const TopicQos& qos);
		ReturnCode_t get_default_topic_qos(
			TopicQos& qos);
		ReturnCode_t get_discovered_participants(
			InstanceHandleSeq* participant_handles);
		ReturnCode_t get_discovered_participant_data(
			ParticipantBuiltinTopicData* participant_data,
			InstanceHandle_t participant_handle);
		ReturnCode_t get_discovered_topics(
			InstanceHandleSeq* topic_handles);
		ReturnCode_t get_discovered_topic_data(
			TopicBuiltinTopicData* topic_data,
			InstanceHandle_t topic_handle);
		bool contains_entity(
			InstanceHandle_t a_handle);
		ReturnCode_t get_current_time(
			Time_t* current_time);
	};
	
	class DomainParticipantFactory {
	private:
		static DomainParticipantFactory*	instance;
		static char*						home_path;
		static char*						config_path;
		static void*						config;
		static void*						dl_handle;

	public:
		static DomainParticipantFactory* get_instance();
		static void* get_dl_handle();

	protected:
		DomainParticipantFactory();
		virtual ~DomainParticipantFactory();
		
	public:
		virtual DomainParticipant* create_participant(
			DomainId_t domain_id,
			const DomainParticipantQos& qos,
			DomainParticipantListener* a_listener,
			const StatusMask mask);
		virtual ReturnCode_t delete_participant(
			const DomainParticipant* a_participant);
		virtual DomainParticipant* lookup_participant(
			DomainId_t domain_id);
		virtual ReturnCode_t set_default_participant_qos(
			const DomainParticipantQos& qos);
		virtual ReturnCode_t get_default_participant_qos(
			DomainParticipantQos& qos);
		virtual ReturnCode_t set_qos(
			const DomainParticipantFactoryQos& qos);
		virtual ReturnCode_t get_qos(
			DomainParticipantFactoryQos& qos);
	};
	
	class TypeSupport {
	public:
		TypeSupport();
		virtual ~TypeSupport();
		
		// abstract ReturnCode_t register_type(
		// 	const DomainParticipant* domain,
		// 	const char* type_name);
		// abstract const char* get_type_name();
	};
	
	// ----------------------------------------------------------------------
	class TopicDescription {
	public:
		TopicDescription();
		virtual ~TopicDescription();
		
		const char* get_type_name();
		const char* get_name();
		DomainParticipant* get_participant();
	};
	
	class Topic : public Entity, public TopicDescription {
	public:
		Topic();
		virtual ~Topic();
		
		ReturnCode_t set_qos(
			const TopicQos& qos);
		ReturnCode_t get_qos(
			TopicQos& qos);
		ReturnCode_t set_listener(
			TopicListener* a_listener,
			const StatusMask mask);
		TopicListener* get_listener();
		
		// Access the status
		ReturnCode_t get_inconsistent_topic_status(
			InconsistentTopicStatus& a_status);
	};
	
	class ContentFilteredTopic : public TopicDescription {
	public:
		ContentFilteredTopic();
		virtual ~ContentFilteredTopic();
		
		const char* get_filter_expression();
		
		ReturnCode_t get_expression_parameters(
			StringSeq* expression_parameters);
		
		ReturnCode_t set_expression_parameters(
			const StringSeq* expression_parameters);
		
		Topic* get_related_topic();
	};
	
	class MultiTopic : public TopicDescription {
	public:
		MultiTopic();
		virtual ~MultiTopic();
		
		const char* get_subscription_expression();
		
		ReturnCode_t get_expression_parameters(
			StringSeq* expression_parameters);
		
		ReturnCode_t set_expression_parameters(
			const StringSeq* expression_parameters);
	};
	
	// ----------------------------------------------------------------------
	class Publisher : public Entity {
	public:
		Publisher();
		virtual ~Publisher();
		
		virtual DataWriter* create_datawriter(
			Topic* a_topic,
			const DataWriterQos& qos,
			DataWriterListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_datawriter(
			DataWriter* a_datawriter);
		DataWriter* lookup_datawriter(
			const char* topic_name);
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const PublisherQos& qos);
		ReturnCode_t get_qos(
			PublisherQos& qos);
		ReturnCode_t set_listener(
			PublisherListener* a_listener,
			const StatusMask mask);
		PublisherListener* get_listener();
		ReturnCode_t suspend_publications();
		ReturnCode_t resume_publications();
		ReturnCode_t begin_coherent_changes();
		ReturnCode_t end_coherent_changes();
		ReturnCode_t wait_for_acknowledgments(
			const Duration_t* max_wait);
		DomainParticipant* get_participant();
		ReturnCode_t set_default_datawriter_qos(
			const DataWriterQos& qos);
		ReturnCode_t get_default_datawriter_qos(
			DataWriterQos& qos);
		ReturnCode_t copy_from_topic_qos(
			DataWriterQos& a_datawriter_qos,
			const TopicQos& a_topic_qos);
	};
	
	class DataWriter : public Entity {
	public:
		DataWriter();
		virtual ~DataWriter();
		
		// abstract InstanceHandle_t register_instance(
		// 	const Data* instance_data);
		// abstract InstanceHandle_t register_instance_w_timestamp(
		// 	const Data* instance_data,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t unregister_instance(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle);
		// abstract ReturnCode_t unregister_instance_w_timestamp(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t write(
		//  const Data* instance_data,
		//  InstanceHandle_t handle);
		// abstract ReturnCode_t write_w_timestamp(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t dispose(
		// 	const Data* instance_data,
		// 	InstanceHandle_t instance_handle);
		// abstract ReturnCode_t dispose_w_timestamp(
		// 	const Data* instance_data,
		// 	InstanceHandle_t instance_handle,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t get_key_value(
		// 	Data* key_holder,
		// 	InstanceHandle_t handle);
		// abstract InstanceHandle_t lookup_instance(
		// 	const Data* instance_data);
		
		ReturnCode_t set_qos(
			const DataWriterQos& qos);
		ReturnCode_t get_qos(
			DataWriterQos& qos);
		ReturnCode_t set_listener(
			DataWriterListener* a_listener,
			const StatusMask mask);
		DataWriterListener* get_listener();
		Topic* get_topic();
		Publisher* get_publisher();
		ReturnCode_t wait_for_acknowledgments(
			const Duration_t* max_wait);
		// Access the status
		ReturnCode_t get_liveliness_lost_status(
			LivelinessLostStatus& status);
		ReturnCode_t get_offered_deadline_missed_status(
			OfferedDeadlineMissedStatus& status);
		ReturnCode_t get_offered_incompatible_qos_status(
			OfferedIncompatibleQosStatus& status);
		ReturnCode_t get_publication_matched_status(
			PublicationMatchedStatus& status);
		ReturnCode_t assert_liveliness();
		ReturnCode_t get_matched_subscriptions(
			InstanceHandleSeq* subscription_handles);
		ReturnCode_t get_matched_subscription_data(
			SubscriptionBuiltinTopicData* subscription_data,
			InstanceHandle_t subscription_handle);
	};
	
	// ----------------------------------------------------------------------
	class Subscriber : public Entity {
	public:
		Subscriber();
		virtual ~Subscriber();
		
		DataReader* create_datareader(
			const TopicDescription* a_topic,
			const DataReaderQos& qos,
			DataReaderListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_datareader(
			DataReader* a_datareader);
		ReturnCode_t delete_contained_entities();
		DataReader* lookup_datareader(
			const char* topic_name);
		ReturnCode_t get_datareaders(
			DataReaderSeq* readers,
			const SampleStateMask* sample_states,
			const ViewStateMask* view_states,
			const InstanceStateMask* instance_states);
		ReturnCode_t notify_datareaders();
		ReturnCode_t set_qos(
			const SubscriberQos& qos);
		ReturnCode_t get_qos(
			SubscriberQos& qos);
		ReturnCode_t set_listener(
			SubscriberListener* a_listener,
			const StatusMask mask);
		SubscriberListener* get_listener();
		ReturnCode_t begin_access();
		ReturnCode_t end_access();
		DomainParticipant* get_participant();
		ReturnCode_t set_default_datareader_qos(
			const DataReaderQos& qos);
		ReturnCode_t get_default_datareader_qos(
			DataReaderQos& qos);
		ReturnCode_t copy_from_topic_qos(
			DataReaderQos& a_datareader_qos,
			const TopicQos& a_topic_qos);
	};
	
	class DataReader : public Entity {
	public:
		DataReader();
		virtual ~DataReader();
		
		// abstract ReturnCode_t read(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t take(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t read_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t take_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t read_next_sample(
		// 	Data* data_values,
		// 	SampleInfo* sample_info);
		// abstract ReturnCode_t take_next_sample(
		// 	Data* data_values,
		// 	SampleInfo* sample_info);
		// abstract ReturnCode_t read_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t a_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t take_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t a_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t read_next_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t take_next_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t read_next_instance_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t take_next_instance_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t return_loan(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos);
		// abstract ReturnCode_t get_key_value(
		// 	Data* key_holder,
		// 	InstanceHandle_t handle);
		// abstract InstanceHandle_t lookup_instance(
		// 	const Data* instance_data);
		
		ReadCondition* create_readcondition(
			const SampleStateMask* sample_states,
			const ViewStateMask* view_states,
			const InstanceStateMask* instance_states);
		QueryCondition* create_querycondition(
			const SampleStateMask* sample_states,
			const ViewStateMask* view_states,
			const InstanceStateMask* instance_states,
			const char* query_expression,
			const StringSeq* query_parameters);
		ReturnCode_t delete_readcondition(
			const ReadCondition* a_condition);
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const DataReaderQos& qos);
		ReturnCode_t get_qos(
			DataReaderQos& qos);
		ReturnCode_t set_listener(
			DataReaderListener* a_listener,
			const StatusMask mask);
		DataReaderListener* get_listener();
		TopicDescription* get_topicdescription();
		Subscriber* get_subscriber();
		ReturnCode_t get_sample_rejected_status(
			SampleRejectedStatus& status);
		ReturnCode_t get_liveliness_changed_status(
			LivelinessChangedStatus& status);
		ReturnCode_t get_requested_deadline_missed_status(
			RequestedDeadlineMissedStatus& status);
		ReturnCode_t get_requested_incompatible_qos_status(
			RequestedIncompatibleQosStatus& status);
		ReturnCode_t get_subscription_matched_status(
			SubscriptionMatchedStatus& status);
		ReturnCode_t get_sample_lost_status(
			SampleLostStatus& status);
		ReturnCode_t wait_for_historical_data(
			const Duration_t* max_wait);
		ReturnCode_t get_matched_publications(
			InstanceHandleSeq* publication_handles);
		ReturnCode_t get_matched_publication_data(
			PublicationBuiltinTopicData* publication_data,
			InstanceHandle_t publication_handle);
	};
	
	struct SampleInfo {
		SampleStateKind		sample_state;
		ViewStateKind		view_state;
		InstanceStateKind	instance_state;
		Time_t*				source_timestamp;
		InstanceHandle_t	instance_handle;
		InstanceHandle_t	publication_handle;
		int32_t				disposed_generation_count;
		int32_t				no_writers_generation_count;
		int32_t				sample_rank;
		int32_t				generation_rank;
		int32_t				absolute_generation_rank;
		bool				valid_data;
		
		SampleInfo();
		SampleInfo(
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
			bool valid_data);
		virtual ~SampleInfo();
	};
	
	typedef sequence<SampleInfo> SampleInfoSeq;
};

#endif /* __DDS_DSCP_H__ */
