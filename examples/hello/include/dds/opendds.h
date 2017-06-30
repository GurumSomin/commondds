#ifndef __DDS_OPENDDS__
#define __DDS_OPENDDS__

#include <dds/dcps.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DdsDcpsDomainC.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/StaticIncludes.h>

#include <hello/Message_opendds.h>

namespace dds {
	class OpenDDSDomainParticipantFactory : public DomainParticipantFactory {
	private:
		DDS::DomainParticipantFactory* instance;

	public:
		OpenDDSDomainParticipantFactory();
		virtual ~OpenDDSDomainParticipantFactory();

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

	class OpenDDSDomainParticipant : public DomainParticipant {
	private:
		OpenDDSDomainParticipantFactory* factory;
		DDS::DomainParticipant* instance;

	public:
		OpenDDSDomainParticipant(
			OpenDDSDomainParticipantFactory* factory,
			DDS::DomainParticipant* instance);
		virtual ~OpenDDSDomainParticipant();
		
		virtual Publisher* create_publisher(
			const PublisherQos& qos,
			PublisherListener* a_listener,
			const StatusMask mask);
		DDS::DomainParticipant* get_instance();
		/*
		// Factory interfaces
		ReturnCode_t delete_publisher(
			const Publisher* p);
		Subscriber* create_subscriber(
			const SubscriberQos& qos,
			SubscriberListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_subscriber(
			const Subscriber* s);
		Subscriber* get_builtin_subscriber();
		*/
		virtual Topic* create_topic(
			const char* topic_name,
			const char* type_name,
			const TopicQos& qos,
			TopicListener* a_listener,
			const StatusMask mask);
		/*
		ReturnCode_t delete_topic(
			const Topic* a_topic);
		Topic* find_topic(
			const char* topic_name,
			const Duration_t* timeout);
		TopicDescription* lookup_topicdescription(
			const char* name);
		ContentFilteredTopic* create_contentfilteredtopic(
			const char* name,
			const Topic* related_topic,
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
			*/
		virtual ReturnCode_t delete_contained_entities();
		/*
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
		*/
	};


	class OpenDDSDomainParticipantQos {
	public:
		static void convert(const DomainParticipantQos& source, DDS::DomainParticipantQos& target);
		static void convert(const DDS::DomainParticipantQos& source, DomainParticipantQos& target);
	};

	class OpenDDSPublisherQos {
	public:
		static void convert(const PublisherQos& source, DDS::PublisherQos& target);
		static void convert(const DDS::PublisherQos& source, PublisherQos& target);
	};

	class OpenDDSEntityFactoryQosPolicy {
	public:
		static void convert(const EntityFactoryQosPolicy& source, DDS::EntityFactoryQosPolicy& target);
		static void convert(const DDS::EntityFactoryQosPolicy& source, EntityFactoryQosPolicy& target);
	};

	class OpenDDSPresentationQosPolicy {
	public:
		static void convert(const PresentationQosPolicy& source, DDS::PresentationQosPolicy& target);
		static void convert(const DDS::PresentationQosPolicy& source, PresentationQosPolicy& target);
	};

	class OpenDDSPartitionQosPolicy {
	public:
		static void convert(const PartitionQosPolicy& source, DDS::PartitionQosPolicy& target);
		static void convert(const DDS::PartitionQosPolicy& source, PartitionQosPolicy& target);
	};

	class OpenDDSGroupDataQosPolicy {
	public:
		static void convert(const GroupDataQosPolicy& source, DDS::GroupDataQosPolicy& target);
		static void convert(const DDS::GroupDataQosPolicy& source, GroupDataQosPolicy& target);
	};

	class OpenDDSUserDataQosPolicy {
	public:
		static void convert(const UserDataQosPolicy& source, DDS::UserDataQosPolicy& target);
		static void convert(const DDS::UserDataQosPolicy& source, UserDataQosPolicy& target);
	};

	class OpenDDSDomainParticipantListener : public DDS::DomainParticipantListener {
		private:
			dds::DomainParticipantListener* listener;
		public:
			OpenDDSDomainParticipantListener(dds::DomainParticipantListener* l);
			virtual ~OpenDDSDomainParticipantListener();
			dds::DomainParticipantListener* get_listener();

			//topiclistener
			virtual void on_inconsistent_topic(DDS::Topic* the_topic, const DDS::InconsistentTopicStatus& status);

			//TODO generate under functions.
			//datawriterlistener
			virtual void on_offered_deadline_missed(DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status);
			virtual void on_offered_incompatible_qos(DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status);
			virtual void on_liveliness_lost(DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status);
			virtual void on_publication_matched(DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status);

			//subscriberlistener
			virtual void on_data_on_readers(DDS::Subscriber* the_subscriber);

			//datareaderlistener
			virtual void on_requested_deadline_missed(DDS::DataReader* the_reader, const DDS::RequestedDeadlineMissedStatus& status);
			virtual void on_requested_incompatible_qos(DDS::DataReader* the_reader, const DDS::RequestedIncompatibleQosStatus& status);
			virtual void on_sample_rejected(DDS::DataReader* the_reader, const DDS::SampleRejectedStatus& status);
			virtual void on_liveliness_changed(DDS::DataReader* the_reader, const DDS::LivelinessChangedStatus& status);
			virtual void on_data_available(DDS::DataReader* the_reader);
			virtual void on_subscription_matched(DDS::DataReader* the_reader, const DDS::SubscriptionMatchedStatus& status);
			virtual void on_sample_lost(DDS::DataReader* the_reader, const DDS::SampleLostStatus& status);
	};

	class OpenDDSTopic : public Topic {
	private:
		DDS::Topic* topic;

	public:
		OpenDDSTopic(DDS::Topic* topic);
		virtual ~OpenDDSTopic();
		DDS::Topic* get_topic();

		ReturnCode_t set_qos(const TopicQos& qos);
		ReturnCode_t get_qos(TopicQos& qos);
		//TODO generate under functions.
		ReturnCode_t set_listener(TopicListener* a_listener, const StatusMask mask);
		TopicListener* get_listener();
		ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus& a_status);
	};

	class OpenDDSInconsistentTopicStatus {
	public:
		static void convert(const InconsistentTopicStatus& source, DDS::InconsistentTopicStatus& target);
		static void convert(const DDS::InconsistentTopicStatus& source, InconsistentTopicStatus& target);
	};

	class OpenDDSTopicQos {
	public:
		static void convert(const TopicQos& source, DDS::TopicQos& target);
		static void convert(const DDS::TopicQos& source, TopicQos& target);
	};

	class OpenDDSTopicDataQosPolicy {
	public:
		static void convert(const TopicDataQosPolicy& source, DDS::TopicDataQosPolicy& target);
		static void convert(const DDS::TopicDataQosPolicy& source, TopicDataQosPolicy& target);
	};

	class OpenDDSDurabilityQosPolicy {
	public:
		static void convert(const DurabilityQosPolicy& source, DDS::DurabilityQosPolicy& target);
		static void convert(const DDS::DurabilityQosPolicy& source, DurabilityQosPolicy& target);
	};

	class OpenDDSDurabilityServiceQosPolicy {
	public:
		static void convert(const DurabilityServiceQosPolicy& source, DDS::DurabilityServiceQosPolicy& target);
		static void convert(const DDS::DurabilityServiceQosPolicy& source, DurabilityServiceQosPolicy& target);
	};

	class OpenDDSDeadlineQosPolicy {
	public:
		static void convert(const DeadlineQosPolicy& source, DDS::DeadlineQosPolicy& target);
		static void convert(const DDS::DeadlineQosPolicy& source, DeadlineQosPolicy& target);
	};

	class OpenDDSLatencyBudgetQosPolicy {
	public:
		static void convert(const LatencyBudgetQosPolicy& source, DDS::LatencyBudgetQosPolicy& target);
		static void convert(const DDS::LatencyBudgetQosPolicy& source, LatencyBudgetQosPolicy& target);
	};

	class OpenDDSLivelinessQosPolicy {
	public:
		static void convert(const LivelinessQosPolicy& source, DDS::LivelinessQosPolicy& target);
		static void convert(const DDS::LivelinessQosPolicy& source, LivelinessQosPolicy& target);
	};

	class OpenDDSReliabilityQosPolicy {
	public:
		static void convert(const ReliabilityQosPolicy& source, DDS::ReliabilityQosPolicy& target);
		static void convert(const DDS::ReliabilityQosPolicy& source, ReliabilityQosPolicy& target);
	};

	class OpenDDSDestinationOrderQosPolicy {
	public:
		static void convert(const DestinationOrderQosPolicy& source, DDS::DestinationOrderQosPolicy& target);
		static void convert(const DDS::DestinationOrderQosPolicy& source, DestinationOrderQosPolicy& target);
	};

	class OpenDDSHistoryQosPolicy {
	public:
		static void convert(const HistoryQosPolicy& source, DDS::HistoryQosPolicy& target);
		static void convert(const DDS::HistoryQosPolicy& source, HistoryQosPolicy& target);
	};

	class OpenDDSResourceLimitsQosPolicy {
	public:
		static void convert(const ResourceLimitsQosPolicy& source, DDS::ResourceLimitsQosPolicy& target);
		static void convert(const DDS::ResourceLimitsQosPolicy& source, ResourceLimitsQosPolicy& target);
	};

	class OpenDDSTransportPriorityQosPolicy {
	public:
		static void convert(const TransportPriorityQosPolicy& source, DDS::TransportPriorityQosPolicy& target);
		static void convert(const DDS::TransportPriorityQosPolicy& source, TransportPriorityQosPolicy& target);
	};

	class OpenDDSLifespanQosPolicy {
	public:
		static void convert(const LifespanQosPolicy& source, DDS::LifespanQosPolicy& target);
		static void convert(const DDS::LifespanQosPolicy& source, LifespanQosPolicy& target);
	};

	class OpenDDSOwnershipQosPolicy {
	public:
		static void convert(const OwnershipQosPolicy& source, DDS::OwnershipQosPolicy& target);
		static void convert(const DDS::OwnershipQosPolicy& source, OwnershipQosPolicy& target);
	};

	class OpenDDSPublisherListener : public DDS::PublisherListener {
	private:
		dds::PublisherListener* listener;
	public:
		OpenDDSPublisherListener(dds::PublisherListener* p);
		virtual ~OpenDDSPublisherListener();
		dds::PublisherListener* get_listener();
		//TODO generate inherit functions
		virtual void on_offered_deadline_missed(DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status);
		virtual void on_offered_incompatible_qos(DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status);
		virtual void on_liveliness_lost(DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status);
		virtual void on_publication_matched(DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status);
	};

	class OpenDDSPublisher : public Publisher {
	private:
		DDS::Publisher* instance;
		OpenDDSDomainParticipant* parent;
	public:
		OpenDDSPublisher(DDS::Publisher* instance, OpenDDSDomainParticipant* parent);
		virtual ~OpenDDSPublisher();
		DataWriter* create_datawriter(Topic* a_topic, const DataWriterQos& qos, DataWriterListener* a_listener, const StatusMask mask);
		//TODO generate inherit functions
	};

	class OpenDDSTopicListener : public DDS::TopicListener {
	private:
		dds::TopicListener* listener;
	public:
		OpenDDSTopicListener(dds::TopicListener* t);
		virtual ~OpenDDSTopicListener();
		dds::TopicListener* get_listener();
		virtual void on_inconsistent_topic(DDS::Topic* the_topic, const DDS::InconsistentTopicStatus& status);
	};

	class OpenDDSDataWriterQos {
	public:
		static void convert(const DataWriterQos& source, DDS::DataWriterQos& target);
		static void convert(const DDS::DataWriterQos& source, DataWriterQos& target);
	};

	class OpenDDSOwnershipStrengthQosPolicy {
	public:
		static void convert(const OwnershipStrengthQosPolicy& source, DDS::OwnershipStrengthQosPolicy& target);
		static void convert(const DDS::OwnershipStrengthQosPolicy& source, OwnershipStrengthQosPolicy& target);
	};

	class OpenDDSDataWriterListener : public DDS::DataWriterListener {
	private:
		dds::DataWriterListener* listener;
	public:
		OpenDDSDataWriterListener(dds::DataWriterListener* l);
		virtual ~OpenDDSDataWriterListener();
		dds::DataWriterListener* get_listener();

		//TODO generate inherit functions
		virtual void on_offered_deadline_missed(DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status);
		virtual void on_offered_incompatible_qos(DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status);
		virtual void on_liveliness_lost(DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status);
		virtual void on_publication_matched(DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status);
	};

	class OpenDDSWriterDataLifecycleQosPolicy {
	public:
		static void convert(const WriterDataLifecycleQosPolicy& source, DDS::WriterDataLifecycleQosPolicy target);
		static void convert(const DDS::WriterDataLifecycleQosPolicy& source, WriterDataLifecycleQosPolicy target);
	};

};

#endif /* __DDS_OPENDDS__ */
