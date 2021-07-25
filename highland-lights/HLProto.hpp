#pragma once
#include <WiFiNINA.h>


#define HIGHLAND_LIGHTS_PROTO_VERSION 0x00

#define HIGHLAND_LIGHTS_NACK             0x00
#define HIGHLAND_LIGHTS_ACK              0x01
#define HIGHLAND_LIGHTS_NET_CONFIG       0x02
#define HIGHLAND_LIGHTS_TEST_STRIP       0x03
#define HIGHLAND_LIGHTS_ADD_STRIP        0x04
#define HIGHLAND_LIGHTS_REMOVE_STRIP     0x05
#define HIGHLAND_LIGHTS_TEST_RANGE       0x06
#define HIGHLAND_LIGHTS_ADD_RANGE        0x07
#define HIGHLAND_LIGHTS_REMOVE_RANGE     0x08
#define HIGHLAND_LIGHTS_GET_CONFIG       0x09
#define HIGHLAND_LIGHTS_FINALIZE_CONFIG  0x0A
#define HIGHLAND_LIGHTS_SET_RANGE_RGB    0x10
#define HIGHLAND_LIGHTS_SET_RANGE_HSV    0x11
#define HIGHLAND_LIGHTS_SET_STRIP_RGB    0x12
#define HIGHLAND_LIGHTS_SET_STRIP_HSV    0x13

namespace highland
{
namespace proto
{
struct NetConfig
{
  char ssid[33] = {};
  char pass[64] = {};
};



bool parseNetConfig(WiFiClient& client, NetConfig* config);

}
}
