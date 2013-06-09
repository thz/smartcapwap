#ifndef __CAPWAP_ELEMENT_RESULTCODE_HEADER__
#define __CAPWAP_ELEMENT_RESULTCODE_HEADER__

#define CAPWAP_ELEMENT_RESULTCODE			33

#define CAPWAP_RESULTCODE_FIRST										0
#define CAPWAP_RESULTCODE_SUCCESS									0
#define CAPWAP_RESULTCODE_FAILURE									1
#define CAPWAP_RESULTCODE_SUCCESS_NAT_DETECTED						2
#define CAPWAP_RESULTCODE_JOIN_FAILURE_UNSPECIFIED					3
#define CAPWAP_RESULTCODE_JOIN_FAILURE_RESOURCE_DEPLETION			4
#define CAPWAP_RESULTCODE_JOIN_FAILURE_UNKNOWN_SOURCE				5
#define CAPWAP_RESULTCODE_JOIN_FAILURE_INCORRECT_DATA				6
#define CAPWAP_RESULTCODE_JOIN_FAILURE_ID_ALREADY_IN_USE			7
#define CAPWAP_RESULTCODE_JOIN_FAILURE_WTP_HARDWARE_NOT_SUPPORTED	8
#define CAPWAP_RESULTCODE_JOIN_FAILURE_BINDING_NOT_SUPPORTED		9
#define CAPWAP_RESULTCODE_RESET_FAILURE_UNABLE_TO_RESET				10
#define CAPWAP_RESULTCODE_RESET_FAILURE_FIRMWARE_WRITE_ERROR		11
#define CAPWAP_RESULTCODE_CONF_FAILURE_SERVICE_PROVIDED_ANYHOW		12
#define CAPWAP_RESULTCODE_CONF_FAILURE_SERVICE_NOT_PROVIDED			13
#define CAPWAP_RESULTCODE_IMAGE_ERROR_INVALID_CHECKSUM				14
#define CAPWAP_RESULTCODE_IMAGE_ERROR_INVALID_DATA_LENGTH			15
#define CAPWAP_RESULTCODE_IMAGE_ERROR_OTHER_ERROR					16
#define CAPWAP_RESULTCODE_IMAGE_ERROR_IMAGE_ALREADY_PRESENT			17
#define CAPWAP_RESULTCODE_MSG_UNEXPECTED_INVALID_CURRENT_STATE		18
#define CAPWAP_RESULTCODE_MSG_UNEXPECTED_UNRECOGNIZED_REQUEST		19
#define CAPWAP_RESULTCODE_FAILURE_MISSING_MANDATORY_MSG_ELEMENT		20
#define CAPWAP_RESULTCODE_FAILURE_UNRECOGNIZED_MESSAGE_ELEMENT		21
#define CAPWAP_RESULTCODE_DATA_TRANSFER_ERROR						22
#define CAPWAP_RESULTCODE_LAST										22
      
struct capwap_resultcode_element {
	uint32_t code;
};

extern struct capwap_message_elements_ops capwap_element_resultcode_ops;

#endif /* __CAPWAP_ELEMENT_RESULTCODE_HEADER__ */
