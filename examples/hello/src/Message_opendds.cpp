#include <hello/Message_opendds.h>
#include <dds/DCPS/WaitSet.h>

namespace Hello {

MessageTypeSupport::MessageTypeSupport() {
	dds::TypeSupport();
}

MessageTypeSupport::~MessageTypeSupport() {
}

dds::ReturnCode_t MessageTypeSupport::register_type(
	const dds::DomainParticipant* domain,
	const char* type_name) {
	dds::OpenDDSDomainParticipant* domain2 = (dds::OpenDDSDomainParticipant*) domain;
	hello::MessageTypeSupport_var ts = new hello::MessageTypeSupportImpl;
	dds::ReturnCode_t rt = ts->register_type(domain2->get_instance(), type_name);
	return rt;
}

const char* MessageTypeSupport::get_type_name() {
	return "hello::Message";
}

MessageDataWriter::MessageDataWriter(DDS::DataWriter* g) {
	this->ginstance = g;
	instance = hello::MessageDataWriter::_narrow(g);
	DDS::StatusCondition* condition = ginstance->get_statuscondition();
	condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

	// Wait connection with sub
	// This part is nessaccery publish data
	DDS::WaitSet* ws = new DDS::WaitSet;
	ws->attach_condition(condition);

	while (true) {
		DDS::PublicationMatchedStatus matches;

		if (ginstance->get_publication_matched_status(matches) != DDS::RETCODE_OK) {
			std::cout<< "get_publication_matched_status error" << std::endl;
		}

		if (matches.current_count >= 1) {
			break;
		}

		DDS::ConditionSeq conditions;
		DDS::Duration_t timeout = { 60, 0 };

		if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
			std::cout<<"wait failed"<< std::endl;
		}
	}

	ws->detach_condition(condition);
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
	// DO NOT use value; It occur segmentation fault
	hello::Message_var msg = new hello::Message();
	msg->seq = instance_data->seq;
	msg->time = instance_data->time;
	msg->msg = instance_data->msg;
	return (dds::ReturnCode_t) instance->write(*msg, (DDS::InstanceHandle_t)handle);
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
