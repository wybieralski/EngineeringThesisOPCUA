/// @brief OPC UA Server main.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///
#include <algorithm>
#include <future>
#include <iostream>
#include <time.h>

#include <chrono>
#include <thread>

#include <opc/ua/node.h>
#include <opc/ua/server/server.h>
#include <opc/ua/subscription.h>

#include "../wfa/WFA_server/EventManager.h"

using namespace OpcUa;

void RunServer() {
  ServerFactory sf;
  std::thread th_server([&]() { sf.start_server(); });
    std::this_thread::sleep_for(std::chrono::seconds(1));

  sf.initialize_objects();

  OPCMessage::initialize_nodes_updater(sf);
  EventManager::create_events(sf);

  Node root = sf.m_server.GetRootNode();

  sf.logger->info("Root node is: {}", root);
  sf.logger->info("Children are:");
  for (Node node : root.GetChildren()) {
    sf.logger->info("    {}", node);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::thread th_nodes__data_modifiers(
      [&]() { OPCMessage::continuous_node_updater(); });

  sf.logger->info("Ctrl-C to exit");

  int i = 0;
  while (i < 1000) {

    if (i>5 && i<30) {
        EventManager::display_event("default_event", sf);
        sf.logger->info("Event triggered");

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    i++;
  }

  sf.m_server.Stop();
  th_nodes__data_modifiers.join();
  th_server.join();
}

int main(int argc, char **argv) {
  try {
    RunServer();
  }

  catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }

  return 0;
}
