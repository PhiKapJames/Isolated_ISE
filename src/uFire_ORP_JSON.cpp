#ifdef __has_include
#if __has_include("ArduinoJson.h")
#include "uFire_ORP_JSON.h"
#include <ArduinoJson.h>

void uFire_ORP_JSON::begin(ISE_ORP *p_orp)
{
  orp = p_orp;
  orp->begin();
  emptyPlaceholder = "-";
}

String uFire_ORP_JSON::processJSON(String rx_string)
{
  String cmd = rx_string.substring(0, rx_string.indexOf(" ", 0));
  cmd.trim();
  rx_string.remove(0, rx_string.indexOf(" ", 0));
  rx_string.trim();
  String parameter = rx_string.substring(0, rx_string.indexOf(" ", 0));
  parameter.trim();

  String value = "";
  if (cmd == "oc")            value = orp_connected();
  if (cmd == "o")             value = orp_measure();
  if (cmd == "oo")            value = orp_offset(parameter);
  if (cmd == "or")            value = orp_reset();
  if (cmd == "op")            value = orp_potential(parameter);
  if (cmd == "ot")            value = orp_temp();

  if (value != "")
  {
    this->value = value.toFloat();
    return value;
  } else
  {
    this->value = -1;
    return "";
  }
}

String uFire_ORP_JSON::orp_reset()
{
  String output;
  const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
  DynamicJsonDocument doc(bufferSize);
  doc["or"] = "or";
  orp->reset();
  serializeJson(doc, output);
  return output;
}

String uFire_ORP_JSON::orp_connected()
{
  String output;
  const size_t bufferSize = JSON_OBJECT_SIZE(5) + 20;
  DynamicJsonDocument doc(bufferSize);
  doc["oc"] = orp->connected();
  serializeJson(doc, output);
  return output;
}

String uFire_ORP_JSON::orp_measure()
{
  String output;
  const size_t bufferSize = JSON_OBJECT_SIZE(5) + 20;
  DynamicJsonDocument doc(bufferSize);
  doc["o"] = floor(orp->measuremV() * 100.0 + 0.5) / 100.0;
  serializeJson(doc, output);
  return output;
}

String uFire_ORP_JSON::orp_offset(String parameter)
{
  String output;
  const size_t bufferSize = JSON_OBJECT_SIZE(5) + 20;
  DynamicJsonDocument doc(bufferSize);

  if (parameter.length())
  {
    orp->calibrateSingle(parameter.toFloat());
  }

  float offset = orp->getCalibrateOffset();
  if (isnan(offset)) {
    doc["oo"]  = emptyPlaceholder;
  }
  else {
    doc["oo"]  = offset;
  }
  serializeJson(doc, output);
  return output;
}

String uFire_ORP_JSON::orp_potential(String parameter)
{
  String output;
  const size_t bufferSize = JSON_OBJECT_SIZE(5) + 20;
  DynamicJsonDocument doc(bufferSize);

  if (parameter.length())
  {
    orp->setProbePotential(parameter.toFloat());
  }

  float potential = orp->getProbePotential();
  if (isnan(potential)) {
    doc["op"]  = emptyPlaceholder;
  }
  else {
    doc["op"]  = potential;
  }
  serializeJson(doc, output);
  return output;
}

String uFire_ORP_JSON::orp_temp()
{
  String output;
  const size_t bufferSize = JSON_OBJECT_SIZE(5) + 20;
  DynamicJsonDocument doc(bufferSize);
  doc["ot"] = floor(orp->measureTemp());
  serializeJson(doc, output);
  return output;
}
#endif
#endif