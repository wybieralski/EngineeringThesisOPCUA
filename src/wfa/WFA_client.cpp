#include <opc/ua/client/client.h>
#include <opc/ua/node.h>
#include <opc/ua/subscription.h>

#include <opc/common/logger.h>

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <thread>
#include <fstream>

#include "../wfa/WFA_client/ClientManager.h"
#include "../wfa/WFA_server/server_properties.h"

using namespace OpcUa;

int main(int argc, char **argv) {
    auto logger = spdlog::stderr_color_mt("client");
    try {
        auto endpoint = ServerProperties::ENDPOINT;
//        auto endpoint = "opc.tcp://10.0.0.100:4843";
        WFA::ClientManager cm;
        if (argc > 1) {
            endpoint = argv[1];
        }
        logger->info("Connecting to: {}", endpoint);
        OpcUa::UaClient client(logger);
        client.Connect(endpoint);

        // Process with data
        cm.get_data(endpoint, logger, client);

        logger->info("Disconnecting");
        client.Disconnect();
        logger->flush();
        return 0;
    }

    catch (const std::exception &exc) {
        logger->error("Error: {}", exc.what());
    }

    catch (...) {
        logger->error("Unknown error.");
    }

    return -1;
}
