#include <FastLED.h>
#include "LightsInterface.hpp"
#include "HLProto.hpp"
#include <WiFiNINA.h>

#define NET_CONFIG_ADDRESS   2000
#define LIGHT_CONFIG_ADDRESS 5000

namespace highland
{
LightsInterface::LightsInterface(LightController* controller,  EEPROM<EEPROMI2C, 128000>* eeprom):
  m_controller{controller},
  m_eeprom{eeprom},
  m_server{8989}
{
  
}

void LightsInterface::initialize()
{
  checkForWifiConfig();
  if(m_state != WIFI_CONFIGURED)
  {
    configureWifi();
  }

  m_server.begin();
  
  checkForLightConfig();
  while(m_state != LIGHTS_CONFIGURED)
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
    Serial.println("Net config stored, retrieving");
    m_eeprom->read<proto::NetConfig>(NET_CONFIG_ADDRESS + sizeof(bool), &config);
  }
  else
  {
    Serial.println("Net config not stored going for AP config");
    return InterfaceState::WAITING_FOR_WIFI_CONFIG;
  }
  
  int status = WiFi.begin(config.ssid, config.pass);
  delay(5000);

  if(status == WL_CONNECTED)
  {
    Serial.println("Config correct, wifi configured from EEPROM");
    Serial.println(WiFi.localIP());
    m_net_config = config;
    m_state = InterfaceState::WIFI_CONFIGURED;
  }
  else
  {
    Serial.println("Config failed, will go for AP config");
    WiFi.end();
    m_eeprom->write<bool>(NET_CONFIG_ADDRESS, false);
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
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.println(mac[0],HEX);
    Serial.println(WiFi.reasonCode());
    // Clear wifi connection this is probably not necessary.
    WiFi.end();
    // Setup config server 
    WiFiServer config_server(8989);
    WiFi.beginAP(config_ssid.c_str(), config_pass.c_str());
    Serial.println("Started AP with SSID: ");
    Serial.println(config_ssid);
    Serial.println(WiFi.localIP());
    
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.println(mac[0],HEX);
    Serial.println(WiFi.reasonCode());
    
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

    // @todo error handling
    uint8_t msg_type;
    config_client.readBytes(&msg_type, 1);
    if(msg_type != HIGHLAND_LIGHTS_NET_CONFIG)
    {
      // @todo return nack
      continue;
    }
    
    proto::NetConfig config;
    bool got_config = proto::parseNetConfig(config_client , &config);
    if(!got_config)
    {
      // @todo return nack
      continue;
    }
    m_net_config = config;
    Serial.println("Got Config");
    Serial.println(config.pass);
    Serial.println(config.ssid);
    Serial.println(m_net_config.pass);
    Serial.println(m_net_config.ssid);
    
    // TODO save wifi config.
    m_eeprom->write<bool>(NET_CONFIG_ADDRESS, true);
    m_eeprom->write<proto::NetConfig>(NET_CONFIG_ADDRESS + sizeof(bool), config);

    WiFi.end(); // End the access point and attempt to connect to the given router.

    
    // Attempt to connect to the wifi server.
    //status = WiFi.begin(m_net_config.ssid, m_net_config.pass);
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
  // Get config connection
  WiFiClient config_client;
  do
  {
    config_client = m_server.available();
  } while(!config_client);
  Serial.println("Got light config client");
  
  // Execute lights actions in loop until we get a finalize
  while(true)
  {
    if(!config_client.available())
    {
      continue;
    }
    

    // @todo error handling
    uint8_t version;
    config_client.readBytes(&version, 1);
    if(version != HIGHLAND_LIGHTS_PROTO_VERSION)
    {
      // @todo return nack and disconnect.
      continue;
    }
    Serial.println("Got Version");

    
    // @todo error handling
    uint8_t msg_type;
    config_client.readBytes(&msg_type, 1);

    // Predeclare vars for no good reason
    uint8_t strip_index;
    uint16_t num_leds;
    size_t range_index;
    bool finalized = false;
    switch(msg_type)
    {
     case HIGHLAND_LIGHTS_TEST_STRIP :
       Serial.println("Got test strip");
       Serial.println(sizeof(size_t));
       config_client.readBytes(&strip_index, 1);

       m_controller->setAllInStrip(strip_index, CRGB::White);
       m_controller->show();
       delay(5000);
       m_controller->setAllInStrip(strip_index, CRGB::Black);
       m_controller->show();
       break;
     case HIGHLAND_LIGHTS_ADD_STRIP :
       Serial.println("Got add strip");
       config_client.readBytes(&strip_index, 1);
       config_client.readBytes((char*) &num_leds, 2);

       m_controller->addStrip(strip_index, num_leds);
       break;
     case HIGHLAND_LIGHTS_TEST_RANGE:
       Serial.println("Got test range");
       config_client.readBytes((char*) &range_index, sizeof(size_t));

       m_controller->setColorRange(range_index, CRGB::White);
       m_controller->show();
       delay(5000);
       m_controller->setColorRange(range_index, CRGB::Black);
       m_controller->show();
       break;
     case HIGHLAND_LIGHTS_ADD_RANGE:
       LEDRange range;
       Serial.println("Got add range");
       config_client.readBytes((char*) &range, sizeof(range));

       // @todo this function does 0 error checking. Please stop doing this once the crunch is over.
       m_controller->addRange(range);
       break;
     case HIGHLAND_LIGHTS_FINALIZE_CONFIG:
       // @todo finalize write
       finalized = true;
       break;
    }
    if(finalized)
    {
      m_state = InterfaceState::LIGHTS_CONFIGURED;
      config_client.stop();
      break;
    }
  }
  return m_state;
}


void LightsInterface::handleConnection()
{
  WiFiClient client;
  do
  {
    client = m_server.available();
  } while(!client);

  while(client.connected())
  {
    if(!client.available())
    {
      continue;
    }
    

    // @todo error handling
    uint8_t version;
    client.readBytes(&version, 1);
    if(version != HIGHLAND_LIGHTS_PROTO_VERSION)
    {
      // @todo return nack and disconnect.
      continue;
    }
    Serial.println("Got Version");

    
    // @todo error handling
    uint8_t msg_type;
    client.readBytes(&msg_type, 1);

    size_t range_index;
    uint8_t red, green, blue, hue, saturation,value;
    
    switch(msg_type)
    {
     case HIGHLAND_LIGHTS_SET_RANGE_RGB:
       Serial.println("Got test range");
       client.readBytes((char*) &range_index, sizeof(size_t));
       client.readBytes(&red, 1);
       client.readBytes(&green, 1);
       client.readBytes(&blue, 1);
       
       m_controller->setColorRange(range_index, CRGB(red,green,blue));
       break;
     case HIGHLAND_LIGHTS_SET_RANGE_HSV :
       Serial.println("Got test range");
       client.readBytes((char*) &range_index, sizeof(size_t));
       client.readBytes(&hue, 1);
       client.readBytes(&saturation, 1);
       client.readBytes(&value, 1);
       
       m_controller->setColorRange(range_index, CHSV(hue,saturation,value));
       break;
    }
    m_controller->show();
    
  }
}
}
