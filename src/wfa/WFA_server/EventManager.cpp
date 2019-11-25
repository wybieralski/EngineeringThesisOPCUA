#include "EventManager.h"

std::unordered_map<std::string, OpcUa::Event> EventManager::events_map;

void EventManager::add_event(const std::string &&name, Event &event) {
  events_map.emplace(std::make_pair(name, event));
}

void EventManager::create_events(const ServerFactory &sf) {

  Event default_event(sf.AlarmsAndEvents);
  default_event.Severity = 10;
  default_event.SourceNode = sf.alamrsandevents_nodeid;
  default_event.SourceName = "ERROR: THE MACHINE IS...";
  default_event.Time = DateTime::Current();
  std::stringstream default_event_ss;
  default_event_ss << "DEFAULT EVENT \n ";
  default_event.Message = LocalizedText(default_event_ss.str());

  Event error(sf.AlarmsAndEvents);
  error.Severity = 10;
  error.SourceNode = sf.alamrsandevents_nodeid;
  error.SourceName = "ERROR: THE MACHINE IS...";
  error.Time = DateTime::Current();
  std::stringstream error_ss;
  error_ss << "WARNING: MACHINE IS OVERHEATING ";
  error.Message = LocalizedText(error_ss.str());

  Event sample(sf.AlarmsAndEvents);
  sample.Severity = 10;
  sample.SourceNode = sf.alamrsandevents_nodeid;
  sample.SourceName = "ERROR: THE MACHINE IS...";
  sample.Time = DateTime::Current();
  std::stringstream sample_ss;
  sample_ss << "SAMPLE ERROR ";
  sample.Message = LocalizedText(error_ss.str());

    EventManager::add_event("default", default_event);
    EventManager::add_event("error", error);
    EventManager::add_event("sample", sample);
}

void EventManager::display_event(const std::string &event_name,
                                 ServerFactory &sf) {
  auto event = events_map["default"];

  if (event_name == "sample") {
    event = events_map.at("sample");
  } else if (event_name == "error") {
    event = events_map.at("error");
  } else if (event_name == "default_event") {
    event = events_map.at("error");
  }
  sf.m_server.TriggerEvent(event);
}
