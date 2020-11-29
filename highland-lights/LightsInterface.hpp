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
  const String config_ssid = HIGHLAND_STR(HIGHLAND_CONFIG_SSID);
  const String config_pass = HIGHLAND_STR(HIGHLAND_CONFIG_PASS);

  String m_wifi_ssid;
  String m_wifi_pass;

  InterfaceState m_state = START;
};

} // namespace highland
#endif // HIGHLAND_LIGHTS_INTERFACE_HPP
