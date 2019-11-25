#include "ServerFactory.h"
#include "server_properties.h"

#include <algorithm>
#include <iostream>
#include <opc/ua/node.h>
#include <opc/ua/server/server.h>
#include <opc/ua/subscription.h>
#include <time.h>

using namespace OpcUa;

ServerFactory::ServerFactory()
    : logger(spdlog::stderr_color_mt("server")),
      m_server(OpcUa::UaServer(logger)) {
  m_server.SetEndpoint(ServerProperties::ENDPOINT);
  m_server.SetServerURI(ServerProperties::URI);
}

void ServerFactory::start_server() {
  m_server.Start(); // to separate function on another thread
  m_server.EnableEventNotification();
  midx = m_server.RegisterNamespace(ServerProperties::NAMESPACE);
  objects = m_server.GetObjectsNode();
}

void ServerFactory::initialize_objects() {
  WFA_node = objects.AddObject(WFA_nodeid, WFA_qn);
  machine_node = WFA_node.AddObject(machine_nodeid, machine_qn);
  CurrentJob = machine_node.AddObject(current_job_nodeid, current_job_qn);
  Environment = machine_node.AddObject(environment_nodeid, enviroment_qn);
  Info = machine_node.AddObject(info_nodeid, info_qn);
  Sensors = machine_node.AddObject(sensors_nodeid, sensors_qn);
  AlarmsAndEvents = machine_node.AddObject(alamrsandevents_nodeid, AlarmsAndEvents_qn);
  // CURRENT JOB
  Id = CurrentJob.AddVariable("s=WFA.Printer.CurrentJob.Id","Id", Variant("SI120190225085144"));
  LayerCountCurrent = CurrentJob.AddVariable(
      "s=WFA.Printer.CurrentJob.LayerCountCurrent", "LayerCountCurrent",
      Variant(layer_count_current)); // ++
  LayerCountTarget =
      CurrentJob.AddVariable("s=WFA.Printer.CurrentJob.LayerCountTarget",
                             "LayerCountTarget", layer_count_current);
  MaterialName = CurrentJob.AddVariable("s=WFA.Printer.CurrentJob.MaterialName",
                                        "MaterialName", Variant("MP1_1"));
  OrderId = CurrentJob.AddVariable("s=WFA.Printer.CurrentJob.OrderId",
                                   "OrderId", Variant("None"));

  Times = CurrentJob.AddObject(times_nodeid, times_qn);

    // CURRENT JOB -> TIMES
  build_start_time_mins = 4;
  cool_down_time_min = 24;
  end_time_min = 28;

  build_start_time =
      DateTime::FromTimeT(time(0) + (60 * build_start_time_mins));
  cool_down_time = DateTime::FromTimeT(time(0) + (60 * cool_down_time_min));
  end_time = DateTime::FromTimeT(time(0) + (60 * end_time_min));

  StartTime = Times.AddVariable("s=WFA.Printer.CurrentJob.Times.BuildStart",
                                 "BuildStart", Variant(build_start_time));

  EndTime = Times.AddVariable("s=WFA.Printer.CurrentJob.Times.JobEnd", "JobEnd",
                             Variant(end_time));

  // Environment
  HumidityRelative = Environment.AddVariable(
      "s=WFA.Printer.Environment.HumidityRelative", "HumidityRelative",
      Variant(environment_humidity_relative));
  EnvironmentTemperature =
      Environment.AddVariable("s=WFA.Printer.Environment.Temperature",
                              "Temperature", Variant(environment_temperature));

  // Info
  Brand = Info.AddVariable(
      "s=WFA.Printer.Info.Brand", "Brand",
      Variant(brand));
  InfoId =
          Info.AddVariable("s=WFA.Printer.Info.Id",
                              "Temperature", Variant(info));
  Model = Info.AddVariable(
      "s=WFA.Printer.Info.Model", "Model",
      Variant(model));
  Time =
          Info.AddVariable("s=WFA.Printer.Info.Time",
                              "Time", Variant(end_time));
  Type = Info.AddVariable(
      "s=WFA.Printer.Info.Type", "Type",
      Variant(type));

  // BUILDING PLATFORM
  BuildingPlatform = Sensors.AddObject(building_platform_nodeid, builder_qn);

  BuildingPlatformPosition = BuildingPlatform.AddVariable(
      "s=WFA.Printer.Sensors.BuildingPlatform.Position", "Position",
      Variant(building_platform_position));
  Speed = BuildingPlatform.AddVariable(
      "s=WFA.Printer.Sensors.BuildingPlatform.Speed", "Speed",
      Variant(building_platform_speed));
  Temperature = BuildingPlatform.AddVariable(
      "s=WFA.Printer.Sensors.BuildingPlatform.Temperature", "Temperature",
      Variant(building_platform_temperature));

}