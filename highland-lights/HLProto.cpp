#include"HLProto.hpp"
#include"WiFiNINA.h"

namespace highland
{
namespace proto
{

bool parseNetConfig(WiFiClient& client, NetConfig* config)
{
  if(!client.connected() || ! client.available())
  {
    return false; // Perhaps fail loudly here?
  }

  uint8_t ssid_len = client.read();
  if(ssid_len > 32)
  {
    return false;
  }

  uint8_t read_bytes = client.readBytes(config->ssid, ssid_len);
  if(read_bytes != ssid_len)
  {
    return false;
  }
  
  uint8_t pass_len = client.read();
  if(pass_len > 63)
  {
    return false;
  }

  read_bytes = client.readBytes(config->pass, pass_len);
  if(read_bytes != pass_len)
  {
    return false;
  }

  return true;
}

}
}
