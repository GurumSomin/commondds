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
			 DomainParticipantQos* qos,
			 DomainParticipantListener* a_listener,
			 StatusMask mask);
		virtual ReturnCode_t delete_participant(
			 DomainParticipant* a_participant);
		virtual DomainParticipant* lookup_participant(
			DomainId_t domain_id);
		virtual ReturnCode_t set_default_participant_qos(
			 DomainParticipantQos* qos);
		virtual ReturnCode_t get_default_participant_qos(
			DomainParticipantQos* qos);
		virtual ReturnCode_t set_qos(
			 DomainParticipantFactoryQos* qos);
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
			 PublisherQos* qos,
			 PublisherListener* a_listener,
			 StatusMask mask);
		ReturnCode_t delete_publisher(
			 Publisher* p);
		Subscriber* create_subscriber(
			 SubscriberQos* qos,
			 SubscriberListener* a_listener,
			 StatusMask mask);
		ReturnCode_t delete_subscriber(
			 Subscriber* s);
		Subscriber* get_builtin_subscriber();
		Topic* create_topic(
			 char* topic_name,
			 char* type_name,
			 TopicQos* qos,
			 TopicListener* a_listener,
			 StatusMask mask);
		ReturnCode_t delete_topic(
			 Topic* a_topic);
		Topic* find_topic(
			 char* topic_name,
			 Duration_t* timeout);
		TopicDescription* lookup_topicdescription(
			 char* name);
		ContentFilteredTopic* create_contentfilteredtopic(
			 char* name,
			 Topic* related_topic,
			 char* filter_expression,
			 StringSeq* expression_parameters);
		ReturnCode_t delete_contentfilteredtopic(
			 ContentFilteredTopic* a_contentfilteredtopic);
		MultiTopic* create_multitopic(
			 char* name,
			 char* type_name,
			 char* subscription_expression,
			 StringSeq* expression_parameters);
		ReturnCode_t delete_multitopic(
			 MultiTopic* a_multitopic);
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			 DomainParticipantQos* qos);
		ReturnCode_t get_qos(
			DomainParticipantQos* qos);
		ReturnCode_t set_listener(
			 DomainParticipantListener* a_listener,
			 StatusMask mask);
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
			 PublisherQos* qos);
		ReturnCode_t get_default_publisher_qos(
			PublisherQos* qos);
		ReturnCode_t set_default_subscriber_qos(
			 SubscriberQos* qos);
		ReturnCode_t get_default_subscriber_qos(
			SubscriberQos* qos);
		ReturnCode_t set_default_topic_qos(
			 TopicQos* qos);
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
		static void convert(DomainParticipantQos& source, DDS::DomainParticipantQos& target);
		static void convert(DDS::DomainParticipantQos& source, DomainParticipantQos& target);
	};

	class OpenDDSPublisherQos {
	public:
		static void convert(PublisherQos& source, DDS::PublisherQos& target);
		static void convert(DDS::PublisherQos& source, PublisherQos& target);
	};

	class OpenDDSEntityFactoryQosPolicy {
	public:
		static void convert(EntityFactoryQosPolicy& source, DDS::EntityFactoryQosPolicy& target);
		static void convert(DDS::EntityFactoryQosPolicy& source, EntityFactoryQosPolicy& target);
	};

	class OpenDDSDomainParticipantListener {
	//private:
		// TODO I don't know what to do
		//DDS::DomainParticipantListener instance;
		//OpenDDSDomainParticipantListener(DDS::DomainParticipantListener instance);
	public:
		static void convert(DomainParticipantListener& source, DDS::DomainParticipantListener& target);
		static void convert(DDS::DomainParticipantListener& source, DomainParticipantListener& target);
	};

};

#endif /* __DDS_OPENDDS__ */
