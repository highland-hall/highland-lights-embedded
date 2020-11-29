#ifndef HIGHLAND_LIGHTS_INTERFACE_HPP
#define HIGHLAND_LIGHTS_INTERFACE_HPP

#include <cstdint>
#include "SecretUtils.hpp"
#include "LightController.hpp"

namespace highland
{

enum InterfaceState
{
  START,
  WAITING_FOR_WIFI_CONFIG,
  WIFI_CONFIGURED,
  WAITING_FOR_LIGHTS_CONFIG,
  LIGHTS_CONFIGURED  
};
  

  
class LightsInterface
{
 public:
  LightsInterface(LightController* controller);

  void initialize()
  
  void parseCommand();
 private:

  InterfaceState checkForWifiConfig();

  InterfaceState checkForLightConfig();
  
  InterfaceState configureWifi();

  InterfaceState configureLights();

  LightController* m_controller; //< Controller pointer to issue commands through

  // Access point details
  const char config_ssid[33] = HIGHLAND_STR(HIGHLAND_CONFIG_SSID);
  const char config_pass[64] = HIGHLAND_STR(HIGHLAND_CONFIG_PASS);

  char m_wifi_ssid[33];
  char m_wifi_pass[64];

  InterfaceState m_state = START;
};

} // namespace highland
#endif // HIGHLAND_LIGHTS_INTERFACE_HPP
