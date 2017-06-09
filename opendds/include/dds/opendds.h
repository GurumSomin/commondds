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

	class OpenDDSDomainId_t {
	public:
		static DDS::DomainId_t from(const DomainId_t id);
		static DomainId_t to(const DDS::DomainId_t id);
	};

	class OpenDDSDomainParticipantQos {
	public:
		static DDS::DomainParticipantQos* from(const DomainParticipantQos* qos);
		static DomainParticipantQos* to(const DDS::DomainParticipantQos* qos);
	};

	class OpenDDSPublisherQos {
	public:
		static DDS::PublisherQos* from(const PublisherQos* qos);
		static PublisherQos* to(const DDS::PublisherQos* qos);
	};

	class OpenDDSEntityFactoryQosPolicy {
	public:
		static DDS::EntityFactoryQosPolicy* from(const EntityFactoryQosPolicy* entity_factory);
		static EntityFactoryQosPolicy* to(const DDS::EntityFactoryQosPolicy* entity_factory);
	};

	class OpenDDSDomainParticipantListener {
	//private:
		// TODO I don't know what to do
		//DDS::DomainParticipantListener instance;
		//OpenDDSDomainParticipantListener(DDS::DomainParticipantListener instance);
	public:
		static DDS::DomainParticipantListener* from(const DomainParticipantListener* listener);
		static DomainParticipantListener* to(const DDS::DomainParticipantListener* listener);
	};

	class OpenDDSStatusMask {
	public:
		static DDS::StatusMask from(const StatusMask mask);
		static StatusMask to(const DDS::StatusMask mask);
	};
};

#endif /* __DDS_OPENDDS__ */
