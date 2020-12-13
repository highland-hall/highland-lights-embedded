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

    // Wait for someone to connect to the setup device. Technically there is space for a timing attack here.
    while(WiFi.status() == WL_AP_CONNECTED)
    {
      continue;
    }

    WiFiClient config_client = config_server.available();

    m_wifi_ssid = config_client.readString();
    m_wifi_pass = config_client.readString();

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
