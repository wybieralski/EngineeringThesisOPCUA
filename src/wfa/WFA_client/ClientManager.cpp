//
// Created by lw on 20.03.19.
//

#include "ClientManager.h"
#include "DataRecorder.h"

namespace WFA {


    void ClientManager::get_data(const std::string &endpoint,
                                 const std::shared_ptr<spdlog::logger> &logger,
                                 OpcUa::UaClient &client) {

        OpcUa::Node root = client.GetRootNode();
        OpcUa::Node objects = client.GetObjectsNode();
        OpcUa::Node nsnode = client.GetNode(OpcUa::ObjectId::Server_NamespaceArray);
        OpcUa::Variant ns = nsnode.GetValue();
        OpcUa::Node current_node;
        OpcUa::Node myvar;

        std::ofstream csv_file;
        csv_file.open(ClientProperties::CLIENT_LOG, std::ios::app);
        DataRecorder::init_columns(csv_file);
        fill_map_of_nodes(map_of_nodes);

        logger->info("Root node is: {}", root);

        // get and browse Objects node
        logger->info("Child of objects node are:");

        for (OpcUa::Node node : objects.GetChildren()) {
            logger->info("    {}", node);
        }

        // get a node from standard namespace using objectId
        logger->info("NamespaceArray is:");

        for (std::string d : ns.As<std::vector<std::string>>()) {
            logger->info("    {}", d);
        }

        bool loop_condition = true;
        for (int i = 0; i < 2; i++) {
            //  while (loop_condition) {
            for (auto const &varpath : ClientManager::map_of_nodes) {
                subscribe_operator(csv_file, current_node, varpath, root,
                                   subscribtionManager, logger, client);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void ClientManager::subscribe_operator(
            std::ofstream &csv_file, OpcUa::Node myvar,
            std::pair<unsigned short, std::vector<std::string>> varpath,
            OpcUa::Node &root, SubscribtionManager subMan,
            const std::shared_ptr<spdlog::logger> &logger, OpcUa::UaClient &client) {

        subMan.subscribtion = client.CreateSubscription(20, subMan);
        myvar = root.GetChild(varpath.second);
        subMan.handle = subMan.subscribtion->SubscribeDataChange(myvar);
        logger->info("Got sub handle: {}, node number: {}, node value: {}",
                     subMan.handle, varpath.first,
                     myvar.GetDataValue().Value.ToString());
        DataRecorder::write_to_row(csv_file, myvar,
                                   myvar.GetDataValue()); // logging
        subMan.subscribtion->Delete();
    }

    void ClientManager::fill_map_of_nodes(
            std::map<unsigned short, std::vector<std::string>> &variables_map) {
        ;
        variables_map.insert(
                {0, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:Time"}});
        variables_map.insert(
                {1, {"Objects", "2:WFA", "2:Machine", "2:CurrentJob", "2:Id"}});
        variables_map.insert({2,
                              {"Objects", "2:WFA", "2:Machine", "2:CurrentJob",
                               "2:LayerCountCurrent"}});
        variables_map.insert({3,
                              {"Objects", "2:WFA", "2:Machine", "2:CurrentJob",
                               "2:LayerCountTarget"}});
        variables_map.insert(
                {4,
                 {"Objects", "2:WFA", "2:Machine", "2:CurrentJob", "2:LayerThickness"}});
        variables_map.insert(
                {5, {"Objects", "2:WFA", "2:Machine", "2:CurrentJob", "2:MaterialName"}});
        variables_map.insert(
                {6, {"Objects", "2:WFA", "2:Machine", "2:CurrentJob", "2:OrderId"}});
        variables_map.insert(
                {7, {"Objects", "2:WFA", "2:Machine", "2:CurrentJob", "2:Starter"}});
        variables_map.insert({8,
                              {"Objects", "2:WFA", "2:Machine", "2:CurrentJob",
                               "2:Times", "2:BuildStart"}});
        variables_map.insert({9,
                              {"Objects", "2:WFA", "2:Machine", "2:CurrentJob",
                               "2:Times", "2:CoolDownStart"}});
        variables_map.insert({10,
                              {"Objects", "2:WFA", "2:Machine", "2:CurrentJob",
                               "2:Times", "2:JobEnd"}});
        variables_map.insert(
                {11, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:Brand"}});
        variables_map.insert(
                {12, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:HostName"}});
        variables_map.insert(
                {13, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:Id"}});
        variables_map.insert(
                {14, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:Model"}});
        variables_map.insert(
                {15, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:ProcessState"}});
        variables_map.insert(
                {16, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:ProcessStateWFA"}});
        variables_map.insert(
                {17,
                 {"Objects", "2:WFA", "2:Machine", "2:Info", "2:ProcessStateSemiE10"}});
        variables_map.insert(
                {18, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:Time"}});
        variables_map.insert(
                {19, {"Objects", "2:WFA", "2:Machine", "2:Info", "2:Type"}});
        variables_map.insert({20,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:BuildingPlatform", "2:Position"}});
        variables_map.insert({21,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:BuildingPlatform", "2:Speed"}});
        variables_map.insert({22,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:BuildingPlatform", "2:Temperature"}});
        variables_map.insert({23,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:CollectorPlatform", "2:Position"}});
        variables_map.insert({24,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Dispenser", "2:FillLevel"}});
        variables_map.insert({25,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Dispenser", "2:LastDosingCount"}});
        variables_map.insert({26,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Dispenser", "2:Position"}});
        variables_map.insert({27,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Dispenser", "2:Speed"}});

        variables_map.insert(
                {28,
                 {"Objects", "2:WFA", "2:Machine", "2:Sensors", "2:ExposureUnits",
                  "2:ExposureUnit1", "2:Temperature"}});
        variables_map.insert(
                {29,
                 {"Objects", "2:WFA", "2:Machine", "2:Sensors", "2:ExposureUnits",
                  "2:ExposureUnit2", "2:Temperature"}});
        variables_map.insert(
                {30,
                 {"Objects", "2:WFA", "2:Machine", "2:Sensors", "2:ExposureUnits",
                  "2:ExposureUnit3", "2:Temperature"}});
        variables_map.insert(
                {31,
                 {"Objects", "2:WFA", "2:Machine", "2:Sensors", "2:ExposureUnits",
                  "2:ExposureUnit4", "2:Temperature"}});

        variables_map.insert({32,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:ProcessChamber", "2:InertGasType"}});
        variables_map.insert({33,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:ProcessChamber", "2:O2ConcentrationBottom"}});
        variables_map.insert({34,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:ProcessChamber", "2:O2ConcentrationTop"}});
        variables_map.insert({35,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:ProcessChamber", "2:RelativePressure"}});
        variables_map.insert({36,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:ProcessChamber", "2:Temperature"}});
        variables_map.insert({37,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:RecirculatingFilterSystem", "2:O2Concentration"}});
        variables_map.insert({38,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:RecirculatingFilterSystem",
                               "2:FilterPressure"}});
        variables_map.insert({39,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Recoater", "2:Position"}});
        variables_map.insert({40,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Recoater", "2:Speed"}});
        variables_map.insert({41,
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Turbine", "2:Pressure"}});
        variables_map.insert({42,
                              {"Objects", "2:WFA", "2:Machine", "2:Environment",
                               "2:HumidityRelative"}});
        variables_map.insert(
                {43,
                 {"Objects", "2:WFA", "2:Machine", "2:Environment", "2:Temperature"}});
    }

void ClientManager::fill_map_of_nodes2(
            std::map<std::string, std::vector<std::string>> &variables_map) {
        variables_map.insert({"RecirculatingFilterSystemFilterPressure",
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:RecirculatingFilterSystem",
                               "2:FilterPressure"}});
        variables_map.insert({"RecoaterPosition",
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Recoater", "2:Position"}});
        variables_map.insert({"RecoaterSpeed",
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Recoater", "2:Speed"}});
        variables_map.insert({"TurbinePressure",
                              {"Objects", "2:WFA", "2:Machine", "2:Sensors",
                               "2:Turbine", "2:Pressure"}});
    }
}
