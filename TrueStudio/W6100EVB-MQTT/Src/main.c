#include <stdio.h>
#include "wizchip_conf.h"
#include "board_init.h"
#include "AddressAutoConfig.h"
#include "dns.h"
#include "MQTTClient.h"

#define PUBLISH_MYSELF 0

wiz_NetInfo gWIZNETINFO = { .mac = {
								0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
								},
							.ip = {
								192, 168, 100, 140
							},
							.sn = {
								255, 255, 255, 0
							},
							.gw = {
								192, 168, 100, 1
							},
							.dns = {
								192, 168, 100, 1
							},
							.lla={
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0
							},
							.gua={
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0
							},
							.sn6={
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0
							},
							.gw6={
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0,
								0, 0, 0, 0
							}
};

wiz_NetInfo gWIZNETINFO_M = { .mac = {0x00,0x08,0xdc,0xFF,0xFF,0xFF},
							.ip = {192,168,177,25},
							.sn = {255, 255, 255, 0},
							.gw = {192, 168, 177, 1},
							.dns = {168, 126, 63, 1},
							//.dhcp = NETINFO_STATIC,
							.lla={0xfe,0x80,0x00,0x00,
									0x00,0x00, 0x00,0x00,
									0x02,0x08, 0xdc,0xff,
									0xfe,0x57, 0x57,0x25},   ///< Source Link Local Address
							.gua={0x00,0x00,0x00,0x00,
									0x00,0x00,0x00,0x00,
									0x00,0x00,0x00,0x00,
									0x00,0x00,0x00,0x00},   ///< Source Global Unicast Address
							.sn6={0xff,0xff,0xff,0xff,
									0xff,0xff,0xff,0xff,
									0x00,0x00,0x00, 0x00,
									0x00,0x00,0x00,0x00 },   ///< IPv6 Prefix
							.gw6={0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x00,
									0x00,0x00,0x00,0x00,
									0x00, 0x00, 0x00, 0x00}   ///< Gateway IPv6 Address
};

uint8_t WIZ_Dest_IP_virtual[4] = {192, 168, 0, 230};                  //DST_IP Address
uint8_t WIZ_Dest_IP_Google[4] = {216, 58, 200, 174};              //DST_IP Address

uint8_t mcastipv4_0[4] ={239,1,2,3};
uint8_t mcastipv4_1[4] ={239,1,2,4};
uint8_t mcastipv4_2[4] ={239,1,2,5};
uint8_t mcastipv4_3[4] ={239,1,2,6};

uint16_t WIZ_Dest_PORT = 15000;                                 //DST_IP port

uint8_t MO_flag;

#define ETH_MAX_BUF_SIZE	1024

uint8_t  remote_ip[4] = {192,168,177,200};                      //
uint16_t remote_port = 8080;

unsigned char ethBuf0[ETH_MAX_BUF_SIZE];
unsigned char ethBuf1[ETH_MAX_BUF_SIZE];
unsigned char ethBuf2[ETH_MAX_BUF_SIZE];
unsigned char ethBuf3[ETH_MAX_BUF_SIZE];
unsigned char ethBuf4[ETH_MAX_BUF_SIZE];
unsigned char ethBuf5[ETH_MAX_BUF_SIZE];
unsigned char ethBuf6[ETH_MAX_BUF_SIZE];
unsigned char ethBuf7[ETH_MAX_BUF_SIZE];

uint8_t bLoopback = 1;
uint8_t bRandomPacket = 0;
uint8_t bAnyPacket = 0;
uint16_t pack_size = 0;

static uint8_t data_buf[2048] ={0,};
const uint8_t URL[] = "test.mosquitto.org";
uint8_t dns_server_ip[4] = {168,126,63,1};
uint8_t dns_server_ip6[16] = {0x20,0x01,0x48,0x60,
								0x48,0x60,0x00,0x00,
								0x00,0x00,0x00,0x00,
								0x00,0x00,0x88,0x88
};

void print_network_information(void);

uint8_t IP_TYPE;

const uint8_t MQTT_TOPIC[]="W6100";

unsigned char targetIP[16] = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
}; // mqtt server IP

unsigned int targetPort = 1883; // mqtt server port

unsigned char tempBuffer[1024*2] = {};

struct opts_struct
{
	char* clientid;
	int nodelimiter;
	char* delimiter;
	enum QoS qos;
	char* username;
	char* password;
	char* host;
	int port;
	int showtopics;
} opts ={ (char*)"stdout-subscriber", 0, (char*)"\n", QOS0, NULL, NULL, targetIP, 1883, 0 };

// @brief messageArrived callback function
void messageArrived(MessageData* md)
{
	unsigned char testbuffer[100];
	uint32_t rd_size;
	uint32_t rd_pt;
	uint32_t rdmore_size;

	MQTTMessage* message = md->message;
	MQTTString* topic = md->topicName;

	rdmore_size = (int)topic->lenstring.len;
	rd_pt = 0;

	while(rdmore_size != 0)
	{
		if(rdmore_size > sizeof(testbuffer) - 1)
		{
			rd_size = sizeof(testbuffer) - 1;			
		}
		else
		{
			rd_size = rdmore_size;
		}

		memset(testbuffer, 0, rd_size + 1);

		memcpy(testbuffer, ((char*)topic->lenstring.data) + rd_pt, rd_size);
		printf("Topic : %s\r\n", testbuffer);

		rd_pt += rd_size;
		rdmore_size -= rd_size;
	}

	if (opts.nodelimiter)
	{
		printf("Message : %.*s\r\n", (int)message->payloadlen, (char*)message->payload);
	}
	else
	{
		printf("Message : %.*s%s\r\n", (int)message->payloadlen, (char*)message->payload, opts.delimiter);
	}
}

int main(void)
{
	volatile int i;
	volatile int j,k;
	uint16_t ver=0;
 	uint16_t curr_time = 0;
 	uint8_t result_aac=0;
 	uint8_t dnsclient_ip[16] = {0,};
	uint8_t syslock = SYS_NET_LOCK;
	uint8_t svr_ipv4[4] = {192, 168, 177, 235};
	uint8_t svr_ipv6[16] = {0xfe, 0x80, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00,
							0xc1, 0x0b, 0x0a, 0xdf,
							0xea, 0xf4, 0xf4, 0x2d};

	int rc = 0;
	uint8_t buf[100];
	uint8_t pubbuf[100];

	BoardInitialze();

	// Set Mac and IPv4
	ctlwizchip(CW_SYS_UNLOCK, &syslock);
	ctlnetwork(CN_SET_NETINFO, &gWIZNETINFO);

	// Auto Set IPv6
	if(1 != AddressAutoConfig_Init(&gWIZNETINFO))
	{
		printf("AddressAutoConfig_Init Manual!\r\n");
		// Manual Set IPv6
		gWIZNETINFO = gWIZNETINFO_M;
		ctlnetwork(CN_SET_NETINFO, &gWIZNETINFO);
	}

	// Get My Address
	printf("Register value after W6100 initialize!\r\n");
	print_network_information();
	DNS_init(ethBuf0);

	IP_TYPE = 0x1c;
	while (DNS_run(0, dns_server_ip6, URL, dnsclient_ip, AS_IPV6) != 1);
	printf("> Translated %s to %.2x%.2x:%.2x%.2x:%.2x%.2x:%.2x%.2x:%.2x%.2x:%.2x%.2x:%.2x%.2x:%.2x%.2x\r\n", URL, dnsclient_ip[0], dnsclient_ip[1], dnsclient_ip[2], dnsclient_ip[3]
																											,dnsclient_ip[4],dnsclient_ip[5],dnsclient_ip[6],dnsclient_ip[7]
																											,dnsclient_ip[8],dnsclient_ip[9],dnsclient_ip[10],dnsclient_ip[11]
																											,dnsclient_ip[12],dnsclient_ip[13],dnsclient_ip[14],dnsclient_ip[15]);
	
	Network n;
	MQTTClient c;
	MQTTMessage m;
	uint32_t ck_timer;

	NewNetwork(&n, 0);
	ConnectNetwork(&n, dnsclient_ip, targetPort, AS_IPV6);
	MQTTClientInit(&c, &n, 1000, buf, sizeof(buf), tempBuffer, sizeof(tempBuffer));

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = opts.clientid;
	data.username.cstring = opts.username;
	data.password.cstring = opts.password;

	data.keepAliveInterval = 60;
	data.cleansession = 1;

	rc = MQTTConnect(&c, &data);
	printf("Connected %d\r\n", rc);
	opts.showtopics = 1;

	printf("Subscribing to %s\r\n", MQTT_TOPIC);
	rc = MQTTSubscribe(&c, MQTT_TOPIC, opts.qos, messageArrived);
	printf("Subscribed %d\r\n", rc);

#if PUBLISH_MYSELF == 1
	m.qos = QOS0;
	m.retained = 0;
	m.dup = 0;

	ck_timer = TIM2_gettimer();
#endif

	while(1)
	{
		MQTTYield(&c, data.keepAliveInterval);

#if PUBLISH_MYSELF == 1
		if(ck_timer + 10000 < TIM2_gettimer())
		{
			ck_timer = TIM2_gettimer();

			//printf("Publishing to %s\r\n", MQTT_TOPIC);

			sprintf(pubbuf, "Hello, W6100! @ck_timer(%d)", ck_timer);
			m.payload = pubbuf;
			m.payloadlen = strlen(pubbuf);

			rc = MQTTPublish(&c, MQTT_TOPIC, &m);
			//printf("Published %d\r\n", rc);
		}
#endif
	}
}

void delay(unsigned int count)
{
	// 10 ms

	int temp;
	temp = count + TIM2_gettimer();
	temp *= 10;
	while(temp > TIM2_gettimer()){}
}

void print_network_information(void)
{
	wizchip_getnetinfo(&gWIZNETINFO);

	printf("Mac address: %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	printf("IP address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
	printf("SM Mask	   : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	printf("Gate way   : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	printf("DNS Server : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);

	print_ipv6_addr("GW6 ", gWIZNETINFO.gw6);
	print_ipv6_addr("LLA ", gWIZNETINFO.lla);
	print_ipv6_addr("GUA ", gWIZNETINFO.gua);
	print_ipv6_addr("SUB6", gWIZNETINFO.sn6);

	printf("\r\nNETCFGLOCK : %x\r\n", getNETLCKR());
}

void print_ipv6_addr(uint8_t* name, uint8_t* ip6addr)
{
	printf("%s : ", name);
	printf("%04X:%04X", ((uint16_t)ip6addr[0] << 8) | ((uint16_t)ip6addr[1]), ((uint16_t)ip6addr[2] << 8) | ((uint16_t)ip6addr[3]));
	printf(":%04X:%04X", ((uint16_t)ip6addr[4] << 8) | ((uint16_t)ip6addr[5]), ((uint16_t)ip6addr[6] << 8) | ((uint16_t)ip6addr[7]));
	printf(":%04X:%04X", ((uint16_t)ip6addr[8] << 8) | ((uint16_t)ip6addr[9]), ((uint16_t)ip6addr[10] << 8) | ((uint16_t)ip6addr[11]));
	printf(":%04X:%04X\r\n", ((uint16_t)ip6addr[12] << 8) | ((uint16_t)ip6addr[13]), ((uint16_t)ip6addr[14] << 8) | ((uint16_t)ip6addr[15]));
}
