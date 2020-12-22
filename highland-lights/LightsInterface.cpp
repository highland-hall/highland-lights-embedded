#include "LightsInterface.hpp"
#include "HLProto.hpp"
#include <WiFiNINA.h>

#define NET_CONFIG_ADDRESS 2000


namespace highland
{
LightsInterface::LightsInterface(LightController* controller,  EEPROM<EEPROMI2C, 128000>* eeprom):
  m_controller{controller},
  m_eeprom{eeprom}
{
  
}

void LightsInterface::initialize()
{
  checkForWifiConfig();
  if(m_state != WIFI_CONFIGURED)
  {
    configureWifi();
  }
  checkForLightConfig();
  if(m_state != LIGHTS_CONFIGURED)
  {
    configureLights();
  }
}

InterfaceState LightsInterface::checkForWifiConfig()
{
  bool config_stored = false;
  proto::NetConfig config;

  m_eeprom->read<bool>(NET_CONFIG_ADDRESS, &config_stored);

  // This is insecure :( but honestly it's a one off. If this gets put somewhere else I'll fix it. 
  if(config_stored)
  {
    m_eeprom->read<proto::NetConfig>(NET_CONFIG_ADDRESS + sizeof(bool), &config);
  }
  else
  {
    return InterfaceState::WAITING_FOR_WIFI_CONFIG;
  }

  int status = WiFi.begin(config.ssid, config.pass);
  delay(5000);

  if(status == WL_CONNECTED)
  {
    m_net_config = config;
    m_state = InterfaceState::WIFI_CONFIGURED;
  }
  else
  {
    WiFi.end();
  }
  
  return m_state;
}

InterfaceState LightsInterface::checkForLightConfig()
{
  
}

InterfaceState LightsInterface::configureWifi()
{
  int status;
  do
  {
    // Clear wifi connection this is probably not necessary.
    WiFi.end();
    // Setup config server 
    WiFiServer config_server(8989);
    WiFi.beginAP(config_ssid.c_str(), config_pass.c_str());
    Serial.println("Started AP with SSID: ");
    Serial.println(config_ssid);
    Serial.println(WiFi.localIP());
    config_server.begin();
    // Wait for someone to connect to the setup device. Technically there is space for a timing attack here.
    while(WiFi.status() != WL_AP_CONNECTED)
    {
      continue;
    }

    WiFiClient config_client;
    do
    {
      config_client = config_server.available();
    } while(!config_client);
    
    Serial.println("Got connection");

    while(!config_client.available())
    {
      continue;
    }

    // @todo error handling
    uint8_t version;
    config_client.readBytes(&version, 1);
    if(version != HIGHLAND_LIGHTS_PROTO_VERSION)
    {
      // @todo return nack
      continue;
    }
    Serial.println("Got Version");

    // @todo error handling
    uint8_t msg_type;
    config_client.readBytes(&msg_type, 1);
    if(msg_type != HIGHLAND_LIGHTS_NET_CONFIG)
    {
      // @todo return nack
      continue;
    }
    Serial.println("Got Message Type");
    
    proto::NetConfig config;
    bool got_config = proto::parseNetConfig(config_client , &config);
    if(!got_config)
    {
      // @todo return nack
      continue;
    }
    m_net_config = config;
    Serial.println("Got Config");
    
    // TODO save wifi config.

    WiFi.end(); // End the access point and attempt to connect to the given router.

    // Attempt to connect to the wifi server.
    status = WiFi.begin(m_net_config.ssid, m_net_config.pass);
    delay(5000);
  } while(status != WL_CONNECTED);

  Serial.println("Wifi is configured");
  // Yay we succesfully configured wifi.
  m_state = WIFI_CONFIGURED;
  return m_state;
}

InterfaceState LightsInterface::configureLights()
{

}


// @todo(apozharski) This one is hard :(
void LightsInterface::parseCommand()
{
  
}
}
