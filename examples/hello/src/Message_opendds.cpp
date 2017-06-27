#include <hello/Message_opendds.h>

namespace Hello {

MessageTypeSupport::MessageTypeSupport() {
	dds::TypeSupport();
}

MessageTypeSupport::~MessageTypeSupport() {
}

dds::ReturnCode_t MessageTypeSupport::register_type(
	const dds::DomainParticipant* domain,
	const char* type_name) {
	return dds::RETCODE_ERROR;
}

const char* MessageTypeSupport::get_type_name() {
	return "hello::Message";
}

MessageDataWriter::MessageDataWriter(DDS::DataWriter* g) {
	this->ginstance = g;
	instance = hello::MessageDataWriter::_narrow(g);
}

MessageDataWriter::~MessageDataWriter() {
}
/*
dds::InstanceHandle_t MessageDataWriter::register_instance(
	const Message* instance_data) {
}

dds::InstanceHandle_t MessageDataWriter::register_instance_w_timestamp(
	const Message* instance_data,
	const dds::Time_t* source_timestamp) {
}

dds::ReturnCode_t MessageDataWriter::unregister_instance(
	const Message* instance_data,
	dds::InstanceHandle_t handle) {
}

dds::ReturnCode_t MessageDataWriter::unregister_instance_w_timestamp(
	const Message* instance_data,
	dds::InstanceHandle_t handle,
	const dds::Time_t* source_timestamp) {
}
*/
dds::ReturnCode_t MessageDataWriter::write(
	const Message* instance_data,
	dds::InstanceHandle_t handle) {
	//TODO write data using hello::MessageDataWriter
}
/*
dds::ReturnCode_t MessageDataWriter::write_w_timestamp(
	const Message* instance_data,
	dds::InstanceHandle_t handle,
	const dds::Time_t* source_timestamp) {
}

dds::ReturnCode_t MessageDataWriter::dispose(
	const Message* instance_data,
	dds::InstanceHandle_t instance_handle) {
}

dds::ReturnCode_t MessageDataWriter::dispose_w_timestamp(
	const Message* instance_data,
	dds::InstanceHandle_t instance_handle,
	const dds::Time_t* source_timestamp) {
}

dds::ReturnCode_t MessageDataWriter::get_key_value(
	Message* key_holder,
	dds::InstanceHandle_t handle) {
}

dds::InstanceHandle_t MessageDataWriter::lookup_instance(
	const Message* instance_data) {
}
*/
};
