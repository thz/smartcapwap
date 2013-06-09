#include "wtp.h"
#include "capwap_dfa.h"
#include "capwap_element.h"
#include "capwap_array.h"
#include "capwap_list.h"
#include "wtp_dfa.h"

/* */
static unsigned long wtp_configure_ac(struct capwap_parsed_packet* packet) {
	struct capwap_timers_element* timers;

	/* TODO: gestione richiesta */

	/* */
	timers = (struct capwap_timers_element*)capwap_get_message_element_data(packet, CAPWAP_ELEMENT_TIMERS);
	g_wtp.dfa.rfcMaxDiscoveryInterval = timers->discovery;
	g_wtp.dfa.rfcEchoInterval = timers->echorequest;

	return CAPWAP_CONFIGURE_TO_DATA_CHECK_STATE;
}

/* */
int wtp_dfa_state_configure(struct capwap_parsed_packet* packet, struct timeout_control* timeout) {
	int status = WTP_DFA_ACCEPT_PACKET;
	
	ASSERT(timeout != NULL);

	if (packet) {
		if (!capwap_compare_ip(&g_wtp.acctrladdress, &packet->connection->remoteaddr)) {
			unsigned short binding;
			
			/* */
			binding = GET_WBID_HEADER(packet->rxmngpacket->header);
			if (packet->rxmngpacket->isctrlpacket && (binding == g_wtp.binding) && (packet->rxmngpacket->ctrlmsg.type == CAPWAP_CONFIGURATION_STATUS_RESPONSE) && ((g_wtp.localseqnumber - 1) == packet->rxmngpacket->ctrlmsg.seq)) {
				/* Valid packet, free request packet */
				wtp_free_reference_last_request();

				/* Parsing response values */
				wtp_dfa_change_state(wtp_configure_ac(packet));
				status = WTP_DFA_NO_PACKET;
			}
		}
	} else {
		/* No Configuration status response received */
		g_wtp.dfa.rfcRetransmitCount++;
		if (g_wtp.dfa.rfcRetransmitCount >= g_wtp.dfa.rfcMaxRetransmit) {
			/* Timeout join state */
			wtp_free_reference_last_request();
			wtp_dfa_change_state(CAPWAP_CONFIGURE_TO_DTLS_TEARDOWN_STATE);
			status = WTP_DFA_NO_PACKET;
		} else {
			/* Retransmit configuration status request */	
			if (!capwap_crypt_sendto_fragmentpacket(&g_wtp.ctrldtls, g_wtp.acctrlsock.socket[g_wtp.acctrlsock.type], g_wtp.requestfragmentpacket, &g_wtp.wtpctrladdress, &g_wtp.acctrladdress)) {
				capwap_logging_debug("Warning: error to send configuration status request packet");
			}

			/* Update timeout */
			capwap_set_timeout(g_wtp.dfa.rfcRetransmitInterval, timeout, CAPWAP_TIMER_CONTROL_CONNECTION);
		}
	}

	return status;
}

int wtp_dfa_state_configure_to_datacheck(struct capwap_parsed_packet* packet, struct timeout_control* timeout) {
	struct capwap_header_data capwapheader;
	struct capwap_packet_txmng* txmngpacket;
	int status = WTP_DFA_NO_PACKET;
	struct capwap_resultcode_element resultcode = { .code = CAPWAP_RESULTCODE_SUCCESS };

	ASSERT(timeout != NULL);
	ASSERT(packet == NULL);

	/* Build packet */
	capwap_header_init(&capwapheader, CAPWAP_RADIOID_NONE, g_wtp.binding);
	txmngpacket = capwap_packet_txmng_create_ctrl_message(&capwapheader, CAPWAP_CHANGE_STATE_EVENT_REQUEST, g_wtp.localseqnumber++, g_wtp.mtu);

	/* Add message element */
	wtp_create_radioopsstate_element(txmngpacket);
	capwap_packet_txmng_add_message_element(txmngpacket, CAPWAP_ELEMENT_RESULTCODE, &resultcode);
	/* CAPWAP_CREATE_VENDORSPECIFICPAYLOAD_ELEMENT */	/* TODO */

	/* Change State Event request complete, get fragment packets */
	wtp_free_reference_last_request();
	capwap_packet_txmng_get_fragment_packets(txmngpacket, g_wtp.requestfragmentpacket, g_wtp.fragmentid);
	if (g_wtp.requestfragmentpacket->count > 1) {
		g_wtp.fragmentid++;
	}

	/* Free packets manager */
	capwap_packet_txmng_free(txmngpacket);

	/* Send Change State Event request to AC */
	if (capwap_crypt_sendto_fragmentpacket(&g_wtp.ctrldtls, g_wtp.acctrlsock.socket[g_wtp.acctrlsock.type], g_wtp.requestfragmentpacket, &g_wtp.wtpctrladdress, &g_wtp.acctrladdress)) {
		g_wtp.dfa.rfcRetransmitCount = 0;
		capwap_set_timeout(g_wtp.dfa.rfcRetransmitInterval, timeout, CAPWAP_TIMER_CONTROL_CONNECTION);
		wtp_dfa_change_state(CAPWAP_DATA_CHECK_STATE);
		status = WTP_DFA_ACCEPT_PACKET;
	} else {
		/* Error to send packets */
		capwap_logging_debug("Warning: error to send change state event request packet");
		wtp_free_reference_last_request();
		wtp_dfa_change_state(CAPWAP_DATA_CHECK_TO_DTLS_TEARDOWN_STATE);
	}

	return status;
}

/* */
int wtp_dfa_state_configure_to_dtlsteardown(struct capwap_parsed_packet* packet, struct timeout_control* timeout) {
	ASSERT(packet == NULL);
	ASSERT(timeout != NULL);

	return wtp_teardown_connection(timeout);
}
