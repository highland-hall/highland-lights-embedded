#include "LightsInterface.hpp"
#include <WiFiNINA.h>


namespace highland
{
LightsInterface::LightsInterface(LightController* controller):
  m_controller{controller}
{
  
}

void LightsInterface::initialize()
{
  check_for_wifi_config();
  if(m_state != WIFI_CONFIGURED)
  {
    configure_wifi();
  }
  check_for_light_config();
  if(m_state != LIGHTS_CONFIGURED)
  {
    configure_lights();
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
  do
  {
    // Clear wifi connection this is probably not necessary.
    WiFi.end()
    // Setup config server 
    WiFiServer config_server(8989);
    WiFi.beginAP(config_ssid, config_pass);

    // Wait for someone to connect to the setup device. Technically there is space for a timing attack here.
    while(WiFiStatus == WL_AP_CONNECTED)
    {
      continue;
    }

    WiFiClient config_client = config_server.availiable();

    config_client.findUntil(m_wifi_ssid, '\0');
    config_client.findUntil(m_wifi_pass, '\0');

    // TODO save wifi config.

    WiFi.end(); // End the access point and attempt to connect to the given router.

    // Attempt to connect to the wifi server.
    int status = WiFi.begin(m_wifi_ssid, m_wifi_pass);
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
