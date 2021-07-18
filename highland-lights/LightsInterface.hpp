#ifndef HIGHLAND_LIGHTS_INTERFACE_HPP
#define HIGHLAND_LIGHTS_INTERFACE_HPP

#include <cstdint>
#include "SecretUtils.hpp"
#include "LightController.hpp"
#include "EEPROM.hpp"
#include "EEPROMI2C.hpp"
#include "HLProto.hpp"
#include <WiFiNINA.h>
#include <ArduinoMDNS.h>

namespace highland
{

enum InterfaceState
{
  START,
  WAITING_FOR_WIFI_CONFIG,
  WIFI_CONFIGURED,
  SERVICE_STARTED,
  WAITING_FOR_LIGHTS_CONFIG,
  LIGHTS_CONFIGURED  
};
  

  
class LightsInterface
{
 public:
  LightsInterface(LightController* controller, EEPROM<EEPROMI2C, 128000>* eeprom);

  void initialize();
  
  void handleConnection();
 private:

  InterfaceState checkForWifiConfig();

  InterfaceState checkForLightConfig();
  
  InterfaceState configureWifi();

  InterfaceState registerService();

  InterfaceState configureLights();

  LightController* m_controller; //< Controller pointer to issue commands through

  EEPROM<EEPROMI2C, 128000>* m_eeprom;

  WiFiServer m_server{8989};

  WiFiUDP m_udp;
  
  MDNS m_mdns;
  
  // Access point details
  String config_ssid = HIGHLAND_STR(HIGHLAND_CONFIG_SSID);
  String config_pass = HIGHLAND_STR(HIGHLAND_CONFIG_PASS);

  proto::NetConfig m_net_config;
  
  InterfaceState m_state = START;
};

} // namespace highland
#endif // HIGHLAND_LIGHTS_INTERFACE_HPP
