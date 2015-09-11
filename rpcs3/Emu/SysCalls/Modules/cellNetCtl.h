#pragma once

namespace vm { using namespace ps3; }

// Error Codes
enum
{
	CELL_NET_CTL_ERROR_NOT_INITIALIZED         = 0x80130101,
	CELL_NET_CTL_ERROR_NOT_TERMINATED          = 0x80130102,
	CELL_NET_CTL_ERROR_HANDLER_MAX             = 0x80130103,
	CELL_NET_CTL_ERROR_ID_NOT_FOUND            = 0x80130104,
	CELL_NET_CTL_ERROR_INVALID_ID              = 0x80130105,
	CELL_NET_CTL_ERROR_INVALID_CODE            = 0x80130106,
	CELL_NET_CTL_ERROR_INVALID_ADDR            = 0x80130107,
	CELL_NET_CTL_ERROR_NOT_CONNECTED           = 0x80130108,
	CELL_NET_CTL_ERROR_NOT_AVAIL               = 0x80130109,
	CELL_NET_CTL_ERROR_INVALID_TYPE            = 0x8013010a,
	CELL_NET_CTL_ERROR_INVALID_SIZE            = 0x8013010b,
	CELL_NET_CTL_ERROR_NET_DISABLED            = 0x80130181,
	CELL_NET_CTL_ERROR_NET_NOT_CONNECTED       = 0x80130182,
	CELL_NET_CTL_ERROR_NP_NO_ACCOUNT           = 0x80130183,
	CELL_NET_CTL_ERROR_NP_RESERVED1            = 0x80130184,
	CELL_NET_CTL_ERROR_NP_RESERVED2            = 0x80130185,
	CELL_NET_CTL_ERROR_NET_CABLE_NOT_CONNECTED = 0x80130186,
	CELL_NET_CTL_ERROR_DIALOG_CANCELED         = 0x80130190,
	CELL_NET_CTL_ERROR_DIALOG_ABORTED          = 0x80130191,

	CELL_NET_CTL_ERROR_WLAN_DEAUTHED                 = 0x80130137,
	CELL_NET_CTL_ERROR_WLAN_KEYINFO_EXCHNAGE_TIMEOUT = 0x8013013d,
	CELL_NET_CTL_ERROR_WLAN_ASSOC_FAILED             = 0x8013013e,
	CELL_NET_CTL_ERROR_WLAN_AP_DISAPPEARED           = 0x8013013f,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_INIT            = 0x80130409,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_NO_PADO         = 0x8013040a,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_NO_PADS         = 0x8013040b,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_GET_PADT        = 0x8013040d,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_SERVICE_NAME    = 0x8013040f,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_AC_SYSTEM       = 0x80130410,
	CELL_NET_CTL_ERROR_PPPOE_SESSION_GENERIC         = 0x80130411,
	CELL_NET_CTL_ERROR_PPPOE_STATUS_AUTH             = 0x80130412,
	CELL_NET_CTL_ERROR_PPPOE_STATUS_NETWORK          = 0x80130413,
	CELL_NET_CTL_ERROR_PPPOE_STATUS_TERMINATE        = 0x80130414,
	CELL_NET_CTL_ERROR_DHCP_LEASE_TIME               = 0x80130504,
};

// Network connection states
enum
{
	CELL_NET_CTL_STATE_Disconnected = 0,
	CELL_NET_CTL_STATE_Connecting   = 1,
	CELL_NET_CTL_STATE_IPObtaining  = 2,
	CELL_NET_CTL_STATE_IPObtained   = 3,
};

// Transition connection states
enum
{
	CELL_NET_CTL_EVENT_CONNECT_REQ       = 0,
	CELL_NET_CTL_EVENT_ESTABLISH         = 1,
	CELL_NET_CTL_EVENT_GET_IP            = 2,
	CELL_NET_CTL_EVENT_DISCONNECT_REQ    = 3,
	CELL_NET_CTL_EVENT_ERROR             = 4,
	CELL_NET_CTL_EVENT_LINK_DISCONNECTED = 5,
	CELL_NET_CTL_EVENT_AUTO_RETRY        = 6,
};

// Network connection devices
enum
{
	CELL_NET_CTL_DEVICE_WIRED    = 0,
	CELL_NET_CTL_DEVICE_WIRELESS = 1,
};

// Cable connection types
enum
{
	CELL_NET_CTL_LINK_TYPE_AUTO          = 0,
	CELL_NET_CTL_LINK_TYPE_10BASE_HALF   = 1,
	CELL_NET_CTL_LINK_TYPE_10BASE_FULL   = 2,
	CELL_NET_CTL_LINK_TYPE_100BASE_HALF  = 3,
	CELL_NET_CTL_LINK_TYPE_100BASE_FULL  = 4,
	CELL_NET_CTL_LINK_TYPE_1000BASE_HALF = 5,
	CELL_NET_CTL_LINK_TYPE_1000BASE_FULL = 6,
};

// Link connection states
enum
{
	CELL_NET_CTL_LINK_DISCONNECTED = 0,
	CELL_NET_CTL_LINK_CONNECTED    = 1,
};

// Wireless connection security measures
enum
{
	CELL_NET_CTL_WLAN_SECURITY_NOAUTH      = 0,
	CELL_NET_CTL_WLAN_SECURITY_WEP         = 1,
	CELL_NET_CTL_WLAN_SECURITY_WPAPSK_TKIP = 2,
	CELL_NET_CTL_WLAN_SECURITY_WPAPSK_AES  = 3,
	CELL_NET_CTL_WLAN_SECURITY_UNSUPPORTED = 4,
};

// 802.1X settings
enum
{
	CELL_NET_CTL_8021X_NONE    = 0,
	CELL_NET_CTL_8021X_EAP_MD5 = 1,
};

// IP settings
enum
{
	CELL_NET_CTL_IP_DHCP   = 0,
	CELL_NET_CTL_IP_STATIC = 1,
	CELL_NET_CTL_IP_PPPOE  = 2,
};

// HTTP proxy settings
enum
{
	CELL_NET_CTL_HTTP_PROXY_OFF = 0,
	CELL_NET_CTL_HTTP_PROXY_ON  = 1,
};

// UPnP settings
enum
{
	CELL_NET_CTL_UPNP_ON  = 0,
	CELL_NET_CTL_UPNP_OFF = 1,
};

// Codes for information
enum
{
	CELL_NET_CTL_INFO_DEVICE            = 1,
	CELL_NET_CTL_INFO_ETHER_ADDR        = 2,
	CELL_NET_CTL_INFO_MTU               = 3,
	CELL_NET_CTL_INFO_LINK              = 4,
	CELL_NET_CTL_INFO_LINK_TYPE         = 5,
	CELL_NET_CTL_INFO_BSSID             = 6,
	CELL_NET_CTL_INFO_SSID              = 7,
	CELL_NET_CTL_INFO_WLAN_SECURITY     = 8,
	CELL_NET_CTL_INFO_8021X_TYPE        = 9,
	CELL_NET_CTL_INFO_8021X_AUTH_NAME   = 10,
	CELL_NET_CTL_INFO_RSSI              = 11,
	CELL_NET_CTL_INFO_CHANNEL           = 12,
	CELL_NET_CTL_INFO_IP_CONFIG         = 13,
	CELL_NET_CTL_INFO_DHCP_HOSTNAME     = 14,
	CELL_NET_CTL_INFO_PPPOE_AUTH_NAME   = 15,
	CELL_NET_CTL_INFO_IP_ADDRESS        = 16,
	CELL_NET_CTL_INFO_NETMASK           = 17,
	CELL_NET_CTL_INFO_DEFAULT_ROUTE     = 18,
	CELL_NET_CTL_INFO_PRIMARY_DNS       = 19,
	CELL_NET_CTL_INFO_SECONDARY_DNS     = 20,
	CELL_NET_CTL_INFO_HTTP_PROXY_CONFIG = 21,
	CELL_NET_CTL_INFO_HTTP_PROXY_SERVER = 22,
	CELL_NET_CTL_INFO_HTTP_PROXY_PORT   = 23,
	CELL_NET_CTL_INFO_UPNP_CONFIG       = 24,
};

// Network start dialogs
enum
{
	CELL_NET_CTL_NETSTART_TYPE_NET = 0,
	CELL_NET_CTL_NETSTART_TYPE_NP  = 1,
};

// Network start dialog statuses
enum
{
	CELL_SYSUTIL_NET_CTL_NETSTART_LOADED   = 0x0801,
	CELL_SYSUTIL_NET_CTL_NETSTART_FINISHED = 0x0802,
	CELL_SYSUTIL_NET_CTL_NETSTART_UNLOADED = 0x0803,
};

// UPnP NAT statuses
enum
{
	CELL_NET_CTL_NATINFO_UPNP_UNCHECKED = 0,
	CELL_NET_CTL_NATINFO_UPNP_NO        = 1,
	CELL_NET_CTL_NATINFO_UPNP_USED      = 2,
};

// STUN NAT statuses
enum
{
	CELL_NET_CTL_NATINFO_STUN_UNCHECKED = 0,
	CELL_NET_CTL_NATINFO_STUN_FAILED    = 1,
	CELL_NET_CTL_NATINFO_STUN_OK        = 2,
};

// NAT types
enum
{
	CELL_NET_CTL_NATINFO_NAT_TYPE_1 = 1,
	CELL_NET_CTL_NATINFO_NAT_TYPE_2 = 2,
	CELL_NET_CTL_NATINFO_NAT_TYPE_3 = 3,
};

struct CellNetCtlEtherAddr
{
	u8 data[6];
	u8 padding[2];
};

struct CellNetCtlSSID
{
	u8 data[32];
	u8 term;
	u8 padding[3];
};

union CellNetCtlInfo
{
	be_t<u32> device;
	CellNetCtlEtherAddr ether_addr;
	be_t<u32> mtu;
	be_t<u32> link;
	be_t<u32> link_type;
	CellNetCtlEtherAddr bssid;
	CellNetCtlSSID ssid;
	be_t<u32> wlan_security;
	be_t<u32> auth_8021x_type;
	s8 auth_8021x_auth_name[128];
	u8 rssi;
	u8 channel;
	be_t<u32> ip_config;
	s8 dhcp_hostname[256];
	s8 pppoe_auth_name[128];
	char ip_address[16];
	s8 netmask[16];
	s8 default_route[16];
	s8 primary_dns[16];
	s8 secondary_dns[16];
	be_t<u32> http_proxy_config;
	s8 http_proxy_server[256];
	be_t<u16> http_proxy_port;
	be_t<u32> upnp_config;
};

struct CellNetCtlNetStartDialogParam
{
	be_t<u32> size;
	be_t<s32> type;
	be_t<u32> cid; // Unused
};

struct CellNetCtlNetStartDialogResult
{
	be_t<u32> size;
	be_t<s32> result;
};

struct CellNetCtlNatInfo
{
	be_t<u32> size;
	be_t<s32> upnp_status;
	be_t<s32> stun_status;
	be_t<s32> nat_type;
	be_t<u32> mapped_addr;
};

typedef void(cellNetCtlHandler)(s32 prev_state, s32 new_state, s32 event, s32 error_code, vm::ptr<u32> arg);

enum SignInDialogState
{
	signInDialogNone,
	signInDialogInit,
	signInDialogOpen,
	signInDialogClose,
	signInDialogAbort,
};

struct SignInDialogInstance
{
	std::atomic<SignInDialogState> state;

	s32 status;

	SignInDialogInstance();
	virtual ~SignInDialogInstance() = default;

	virtual void Close();

	virtual void Create() = 0;
	virtual void Destroy() = 0;
};

inline static const char* InfoCodeToName(s32 code)
{
	switch (code)
	{
	case CELL_NET_CTL_INFO_DEVICE:             return "INFO_DEVICE";
	case CELL_NET_CTL_INFO_ETHER_ADDR:         return "INFO_ETHER_ADDR";
	case CELL_NET_CTL_INFO_MTU:                return "INFO_MTU";
	case CELL_NET_CTL_INFO_LINK:               return "INFO_LINK";
	case CELL_NET_CTL_INFO_LINK_TYPE:          return "INFO_LINK_TYPE";
	case CELL_NET_CTL_INFO_BSSID:              return "INFO_BSSID";
	case CELL_NET_CTL_INFO_SSID:               return "INFO_SSID";
	case CELL_NET_CTL_INFO_WLAN_SECURITY:      return "INFO_WLAN_SECURITY";
	case CELL_NET_CTL_INFO_8021X_TYPE:         return "INFO_8021X_TYPE";
	case CELL_NET_CTL_INFO_8021X_AUTH_NAME:    return "INFO_8021X_AUTH_NAME";
	case CELL_NET_CTL_INFO_RSSI:               return "INFO_RSSI";
	case CELL_NET_CTL_INFO_CHANNEL:            return "INFO_CHANNEL";
	case CELL_NET_CTL_INFO_IP_CONFIG:          return "INFO_IP_CONFIG";
	case CELL_NET_CTL_INFO_DHCP_HOSTNAME:      return "INFO_DHCP_HOSTNAME";
	case CELL_NET_CTL_INFO_PPPOE_AUTH_NAME:    return "INFO_PPPOE_AUTH_NAME";
	case CELL_NET_CTL_INFO_IP_ADDRESS:         return "INFO_IP_ADDRESS";
	case CELL_NET_CTL_INFO_NETMASK:            return "INFO_NETMASK";
	case CELL_NET_CTL_INFO_DEFAULT_ROUTE:      return "INFO_DEFAULT_ROUTE";
	case CELL_NET_CTL_INFO_PRIMARY_DNS:        return "INFO_PRIMARY_DNS";
	case CELL_NET_CTL_INFO_SECONDARY_DNS:      return "INFO_SECONDARY_DNS";
	case CELL_NET_CTL_INFO_HTTP_PROXY_CONFIG:  return "INFO_HTTP_PROXY_CONFIG";
	case CELL_NET_CTL_INFO_HTTP_PROXY_SERVER:  return "INFO_HTTP_PROXY_SERVER";
	case CELL_NET_CTL_INFO_HTTP_PROXY_PORT:    return "INFO_HTTP_PROXY_PORT";
	case CELL_NET_CTL_INFO_UPNP_CONFIG:        return "INFO_UPNP_CONFIG";
	default: return "???";
	}
}
