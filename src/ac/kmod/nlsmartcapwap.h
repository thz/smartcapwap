#ifndef __AC_NLSMARTCAPWAP_HEADER__
#define __AC_NLSMARTCAPWAP_HEADER__

/* */
#define NLSMARTCAPWAP_GENL_NAME			"smartcapwap_ac"

/* */
#define NLSMARTCAPWAP_FLAGS_TUNNEL_8023			0x00000001

/* */
enum sc_netlink_attrs {
	NLSMARTCAPWAP_ATTR_UNSPEC,

	NLSMARTCAPWAP_ATTR_FLAGS,

	NLSMARTCAPWAP_ATTR_SESSION_ID,

	NLSMARTCAPWAP_ATTR_RADIOID,
	NLSMARTCAPWAP_ATTR_WLANID,
	NLSMARTCAPWAP_ATTR_BINDING,
	NLSMARTCAPWAP_ATTR_MACMODE,
	NLSMARTCAPWAP_ATTR_TUNNELMODE,

	NLSMARTCAPWAP_ATTR_ADDRESS,
	NLSMARTCAPWAP_ATTR_MTU,

	NLSMARTCAPWAP_ATTR_DATA_FRAME,

	NLSMARTCAPWAP_ATTR_IFPHY_NAME,
	NLSMARTCAPWAP_ATTR_IFPHY_INDEX,

	NLSMARTCAPWAP_ATTR_MACADDRESS,
	NLSMARTCAPWAP_ATTR_BSSID,

	NLSMARTCAPWAP_ATTR_VLAN,

	/* Last attribute */
	__NLSMARTCAPWAP_ATTR_AFTER_LAST,
	NLSMARTCAPWAP_ATTR_MAX = __NLSMARTCAPWAP_ATTR_AFTER_LAST - 1
};

/* */
enum sc_netlink_commands {
	NLSMARTCAPWAP_CMD_UNSPEC,

	NLSMARTCAPWAP_CMD_LINK,

	NLSMARTCAPWAP_CMD_ADD_IFACE,
	NLSMARTCAPWAP_CMD_DELETE_IFACE,

	NLSMARTCAPWAP_CMD_BIND,

	NLSMARTCAPWAP_CMD_SEND_KEEPALIVE,
	NLSMARTCAPWAP_CMD_RECV_KEEPALIVE,

	NLSMARTCAPWAP_CMD_NEW_SESSION,
	NLSMARTCAPWAP_CMD_DELETE_SESSION,

	NLSMARTCAPWAP_CMD_ADD_WLAN,
	NLSMARTCAPWAP_CMD_REMOVE_WLAN,

	NLSMARTCAPWAP_CMD_SEND_DATA,
	NLSMARTCAPWAP_CMD_RECV_DATA,

	NLSMARTCAPWAP_CMD_AUTH_STATION,
	NLSMARTCAPWAP_CMD_DEAUTH_STATION,

	/* Last command */
	__NLSMARTCAPWAP_CMD_AFTER_LAST,
	NLSMARTCAPWAP_CMD_MAX = __NLSMARTCAPWAP_CMD_AFTER_LAST - 1
};

#endif /* __AC_NLSMARTCAPWAP_HEADER__ */
