#include "LightsInterface.hpp"
#include <WiFiNINA.h>

#define SSID_ADDRESS 2000
#define PASS_ADDRESS 3000


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
  bool ssid_stored = false;
  bool pass_stored = false;
  char ssid[33];
  char pass[64];

  m_eeprom->read<bool>(SSID_ADDRESS, &ssid_stored);
  m_eeprom->read<bool>(SSID_ADDRESS, &pass_stored);

  // This is insecure :( but honestly it's a one off. If this gets put somewhere else I'll fix it. 
  if(ssid_stored && pass_stored)
  {
    m_eeprom->read(SSID_ADDRESS + sizeof(bool), ssid, 33);
    m_eeprom->read(SSID_ADDRESS + sizeof(bool), pass, 64);
  }
  else
  {
    return InterfaceState::WAITING_FOR_WIFI_CONFIG;
  }

  int status = WiFi.begin(ssid, pass);
  delay(5000);

  if(status == WL_CONNECTED)
  {
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
    // Wait for someone to connect to the setup device. Technically there is space for a timing attack here.
    while(WiFi.status() != WL_AP_CONNECTED)
    {
      continue;
    }

    WiFiClient config_client = config_server.available();

    Serial.println("Got connection");

    while(!config_client.available())
    {
      continue;
    }
    m_wifi_ssid = config_client.readString();
    Serial.println("Read ssid");

    while(!config_client.available())
    {
      continue;
    }
    m_wifi_pass = config_client.readString();
    Serial.println("Read pass");
    
    // TODO save wifi config.

    WiFi.end(); // End the access point and attempt to connect to the given router.

    // Attempt to connect to the wifi server.
    status = WiFi.begin(m_wifi_ssid.c_str(), m_wifi_pass.c_str());
    delay(5000);
  } while(status != WL_CONNECTED);

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
