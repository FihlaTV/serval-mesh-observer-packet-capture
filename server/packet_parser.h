//
// A collection of functions to parse raw 802.11 packets
// captured by libpcap
//

#ifndef MESHOBSERVER_PACKET_CAPTURE_PACKET_PARSER_H
#define MESHOBSERVER_PACKET_CAPTURE_PACKET_PARSER_H

// Represents an 802.11 frame header
// Trimmed down to the frame control field for our purposes
typedef struct header_80211
{
    unsigned char frame_type;
    unsigned char frame_version;
    unsigned char frame_subtype;
    unsigned char to_ds;
    unsigned char from_ds;
    unsigned char source[6];
    unsigned char dest[6];
} header_80211;

// Represents an 802.11 LLC header
// Trimmed down to the OUI and type fields
typedef struct header_llc
{
    unsigned int   org_code;
    unsigned short type;
} header_llc;

// Represents an IPv4 packet header
// Trimmed down to the IHL and protocol fields
typedef struct header_ipv4
{
    unsigned char  length;
    unsigned char  payload_proto;
    struct in_addr source;
    struct in_addr dest;
} header_ipv4;

// Represents an IPv6 packet header
// Trimmed down to the protocol and address fields
typedef struct header_ipv6
{
    unsigned char   payload_proto;
    struct in6_addr source;
    struct in6_addr dest;
} header_ipv6;

// Represents a UDP packet header
typedef struct header_udp
{
    unsigned short source_port;
    unsigned short dest_port;
    unsigned short length;
    unsigned short payload_length;
} header_udp;

// Represents a Rhizome packet header
typedef struct header_rhizome
{
    unsigned char type;
} header_rhizome;

// Represents a Rhizome Bundle Advertisement Record (BAR)
typedef struct header_bar
{
    unsigned char manifest_prefix[15];
    unsigned char log_length;
    unsigned char lower_version[7];
    int           lat_max;
    int           lat_min;
    int           lon_max;
    int           lon_min;
    unsigned char ttl;

} header_bar;

// A simple enum to determine the highest header we dissected in the final struct
typedef enum highest_header
{
    MAC_80211,
    LLC,
    IPv4,
    IPv6,
    TCP,
    UDP,
    Rhizome
} highest_header;

// Represents a parsed 802.11 packet
// Consists of all parsable headers previously defined
typedef struct parsed_packet
{
    highest_header highest_header;
    header_80211   header_80211;
    header_llc     header_llc;
    header_ipv4    header_ipv4;
    header_ipv6    header_ipv6;
    header_udp     header_udp;
    header_rhizome header_rhizome;
} parsed_packet;

// Massive lookup array for 802.11 frame versions, types, and subtypes
// Plug values like this: wifi_frame_decription[version][type][subtype]
const char* wifi_frame_description[1][4][16];

header_80211 get_header_80211(unsigned char* packet, int* offset, int* trailer_len);
header_llc get_header_llc(unsigned char* packet, int* offset);
header_ipv4 get_header_ipv4(unsigned char* packet, int* offset);
header_ipv6 get_header_ipv6(unsigned char* packet, int* offset);
header_udp get_header_udp(unsigned char* packet, int* offset);
header_rhizome get_header_rhizome(unsigned char* packet, int* offset, int len);
header_bar get_header_bar(unsigned char* packet, int* offset);
parsed_packet parse_packet(unsigned char* packet, int len);


#endif //MESHOBSERVER_PACKET_CAPTURE_PACKET_PARSER_H
