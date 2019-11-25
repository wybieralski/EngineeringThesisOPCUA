#include "OPCMessage.h"
#include <opc/ua/server/server.h>

#ifndef FREEOPCUA_EVENTMANAGER_H
#define FREEOPCUA_EVENTMANAGER_H

class EventManager {
private:
  static std::unordered_map<std::string, OpcUa::Event> events_map;
  static void add_event(const std::string &&name, Event &event);

public:
  static void create_events(const ServerFactory &sf);
  static void display_event(const std::string &event_name, ServerFactory &sf);
};

#endif // FREEOPCUA_EVENTMANAGER_H
