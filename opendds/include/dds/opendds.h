#ifndef __DDS_OPENDDS__
#define __DDS_OPENDDS__

#include <dds/dcps.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DdsDcpsDomainC.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/StaticIncludes.h>

namespace dds {
	class OpenDDSDomainParticipantFactory : public DomainParticipantFactory {
	private:
		DDS::DomainParticipantFactory* instance;

	public:
		OpenDDSDomainParticipantFactory();
		virtual ~OpenDDSDomainParticipantFactory();

		virtual DomainParticipant* create_participant(
			DomainId_t domain_id,
			const DomainParticipantQos* qos,
			const DomainParticipantListener* a_listener,
			const StatusMask mask);
		virtual ReturnCode_t delete_participant(
			const DomainParticipant* a_participant);
		virtual DomainParticipant* lookup_participant(
			DomainId_t domain_id);
		virtual ReturnCode_t set_default_participant_qos(
			const DomainParticipantQos* qos);
		virtual ReturnCode_t get_default_participant_qos(
			DomainParticipantQos* qos);
		virtual ReturnCode_t set_qos(
			const DomainParticipantFactoryQos* qos);
		virtual ReturnCode_t get_qos(
			DomainParticipantFactoryQos* qos);
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
		
		/*
		// Factory interfaces
		Publisher* create_publisher(
			const PublisherQos* qos,
			const PublisherListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_publisher(
			const Publisher* p);
		Subscriber* create_subscriber(
			const SubscriberQos* qos,
			const SubscriberListener* a_listener,
			const StatusMask mask);
		ReturnCode_t delete_subscriber(
			const Subscriber* s);
		Subscriber* get_builtin_subscriber();
		Topic* create_topic(
			const char* topic_name,
			const char* type_name,
			const TopicQos* qos,
			const TopicListener* a_listener,
			const StatusMask mask);
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
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const DomainParticipantQos* qos);
		ReturnCode_t get_qos(
			DomainParticipantQos* qos);
		ReturnCode_t set_listener(
			const DomainParticipantListener* a_listener,
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
			const PublisherQos* qos);
		ReturnCode_t get_default_publisher_qos(
			PublisherQos* qos);
		ReturnCode_t set_default_subscriber_qos(
			const SubscriberQos* qos);
		ReturnCode_t get_default_subscriber_qos(
			SubscriberQos* qos);
		ReturnCode_t set_default_topic_qos(
			const TopicQos* qos);
		ReturnCode_t get_default_topic_qos(
			TopicQos* qos);
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

	class OpenDDSDomainParticipantListener : public DDS::DomainParticipantListener {
		private:
			dds::DomainParticipantListener* listener;
		public:
			OpenDDSDomainParticipantListener(dds::DomainParticipantListener* l);
			virtual ~OpenDDSDomainParticipantListener();
			dds::DomainParticipantListener* get_listener();

			//topiclistener
			virtual void on_inconsistent_topic(DDS::Topic* the_topic, const DDS::InconsistentTopicStatus& status);

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

};

#endif /* __DDS_OPENDDS__ */
