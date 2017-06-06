#ifndef __hello_Message_h__
#define __hello_Message_h__

#include <stdint.h>
#include <dds/dcps.h>

namespace hello {
	class Message {
	public:
		uint32_t	seq;
		uint64_t	time;
		char*		message;
	};

	class MessageTypeSupport : dds::TypeSupport {
	private:
		MessageTypeSupport();
		virtual ~MessageTypeSupport();
		
	public:
		static dds::ReturnCode_t register_type(
			const dds::DomainParticipant* domain,
			const char* type_name);
		static const char* get_type_name();
	};

	class MessageDataWriter : dds::DataWriter {
	public:
		MessageDataWriter();
		virtual ~MessageDataWriter();

		dds::InstanceHandle_t register_instance(
			const Message* instance_data);
		dds::InstanceHandle_t register_instance_w_timestamp(
			const Message* instance_data,
			const dds::Time_t* source_timestamp);
		dds::ReturnCode_t unregister_instance(
			const Message* instance_data,
			dds::InstanceHandle_t handle);
		dds::ReturnCode_t unregister_instance_w_timestamp(
			const Message* instance_data,
			dds::InstanceHandle_t handle,
			const dds::Time_t* source_timestamp);
		dds::ReturnCode_t write(
			const Message* instance_data,
			dds::InstanceHandle_t handle);
		dds::ReturnCode_t write_w_timestamp(
			const Message* instance_data,
			dds::InstanceHandle_t handle,
			const dds::Time_t* source_timestamp);
		dds::ReturnCode_t dispose(
			const Message* instance_data,
			dds::InstanceHandle_t instance_handle);
		dds::ReturnCode_t dispose_w_timestamp(
			const Message* instance_data,
			dds::InstanceHandle_t instance_handle,
			const dds::Time_t* source_timestamp);
		dds::ReturnCode_t get_key_value(
			Message* key_holder,
			dds::InstanceHandle_t handle);
		dds::InstanceHandle_t lookup_instance(
			const Message* instance_data);
	};
};

#endif /* __hello_Message_h__ */
