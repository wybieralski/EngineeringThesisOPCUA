
#include <chrono>
#include <thread>

#include <opc/ua/node.h>
#include <opc/ua/server/server.h>
#include <opc/ua/subscription.h>

using namespace OpcUa;

class ServerFactory {
public:
  ServerFactory();

  void start_server();
  void initialize_objects();
  uint32_t midx = 2;
  std::shared_ptr<spdlog::logger> logger;
  OpcUa::UaServer m_server;

  /******************************** NODE IDs ********************************/

  NodeId WFA_nodeid = ToNodeId("ns=2;s=WFA", midx);
  NodeId machine_nodeid = ToNodeId("ns=2;s=WFA.Printer", midx);
  NodeId current_job_nodeid = ToNodeId("ns=2;s=WFA.Printer.CurrentJob", midx);
  NodeId times_nodeid = ToNodeId("ns=2;s=WFA.Printer.CurrentJob.Times", midx);
  NodeId environment_nodeid = ToNodeId("ns=2;s=WFA.Printer.Environment", midx);
  NodeId info_nodeid = ToNodeId("ns=2;s=WFA.Printer.Info", midx);
  NodeId sensors_nodeid = ToNodeId("ns=2;s=WFA.Printer.Sensors", midx);
  NodeId building_platform_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.BuildingPlatform", midx);
  NodeId collector_platform_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.CollectorPlatform", midx);
  NodeId dispenser_nodeid = ToNodeId("ns=2;s=WFA.Printer.Dispenser", midx);
  NodeId exposure_units_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.ExposureUnits", midx);
  NodeId exposure_unit1_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.ExposureUnits.ExposureUnit1", midx);
  NodeId exposure_unit2_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.ExposureUnits.ExposureUnit2", midx);
  NodeId exposure_unit3_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.ExposureUnits.ExposureUnit3", midx);
  NodeId exposure_unit4_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.ExposureUnits.ExposureUnit4", midx);
  NodeId process_chamber_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.ProcessChamber", midx);
  NodeId recirculating_filter_system_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.RecirculatingFilterSystem", midx);
  NodeId alamrsandevents_nodeid = ToNodeId("ns=2;s=WFA.Printer.AlarmsAndEvents", midx);

  NodeId recoater_nodeid =
      ToNodeId("ns=2;s=WFA.Printer.Sensors.Recoater", midx);
  NodeId turbine_nodeid = ToNodeId("ns=2;s=WFA.Printer.Sensors.Turbine", midx);

  Node Recoater;
  Node RecoaterPosition;
  Node RecoaterSpeed;
  NodeId random_id = ToNodeId("ns=2;s=WFA.Printer.Recoater", midx);
  QualifiedName random_qn = QualifiedName("Recoater", midx);

  /******************************** QUALIFIED NAMES
   * ********************************/

  QualifiedName WFA_qn = QualifiedName("WFA", midx);
  QualifiedName machine_qn = QualifiedName("Printer", midx);
  QualifiedName current_job_qn = QualifiedName("CurrentJob", midx);
  QualifiedName times_qn = QualifiedName("Times", midx);
  QualifiedName enviroment_qn = QualifiedName("Environment", midx);
  QualifiedName info_qn = QualifiedName("Info", midx);
  QualifiedName sensors_qn = QualifiedName("Sensors", midx);
  QualifiedName builder_qn = QualifiedName("BuildingPlatform", midx);

  QualifiedName AlarmsAndEvents_qn = QualifiedName("AlarmsAndEvents", midx);

  // browse root node on server side

  /******************************** NODES ********************************/
  /*** Are initialized in initialize_object method ***/
  Node objects;
  Node WFA_node;
  Node machine_node;

  // CurrentJob Nodes
  Node CurrentJob;
  Node LayerCountCurrent;
  Node LayerCountTarget;
  Node Environment;
  Node Info;
  Node Sensors;
  Node AlarmsAndEvents;
  Node Id;
  Node LayerThickness;
  Node MaterialName;
  Node OrderId;
  Node Starter;

  // TIMES
  Node Times;
  DateTime build_start_time;
  DateTime cool_down_time;
  DateTime end_time;

  Node StartTime;
  Node EndTime;

  // ENVIRONMENT
  Node HumidityRelative;
  Node EnvironmentTemperature;

  // INFO
  Node Brand;
  Node HostName;
  Node InfoId;
  Node Model;
  Node ProcessState;
  Node ProcessStateEOS;
  Node ProcessStateSemiE10;
  Node Time;
  Node Type;

  /*            ************* SENSORS *************            */

  // BUILDING PLATFORM
  Node BuildingPlatform;
  Node BuildingPlatformPosition;
  Node Speed;
  Node Temperature;


  /******************** VARIABLES ********************/

  // TIMES
  size_t build_start_time_mins = 4;
  size_t cool_down_time_min = 24;
  size_t end_time_min = 28;
  // CONSTANT VARIABLES

  double layer_count_target = 1280;

  // CHANGING VARIABLESNode

  double recoater_position = 0.30; // various
  double recoater_speed = 0.50;    // or -150
  double layer_count_current = 0;
  double layer_thickness = 0.04;
  double environment_humidity_relative = -12.5;
  double environment_temperature = -25;
  double building_platform_position = 283.040085229219;
  double building_platform_speed = 0.0;
  double building_platform_temperature = 76.0;

  double recirculating_filter_system_pressure = 3;
  double turbine_pressure = 0.57000124; // decreasing

    // INFO
    std::string brand = "WFA_UWR";
    std::string info="Experimental OPC UA server for WFA UWR printer";
    std::string model="2019 3D WFA printer";
    std::string type="Plastic Print";

};