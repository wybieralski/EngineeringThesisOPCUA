#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <vector>

#include "ServerFactory.h"

class OPCMessage {
private:
  using Action = std::function<void()>;
  static std::vector<Action> actions;
  static void add(Action action);
  static void manage_recirculating_filter_system(ServerFactory &sf);
  static void manage_recoater(ServerFactory &sf);
  static void manage_turbine(ServerFactory &sf);

public:
  OPCMessage() = default;
  static void continuous_node_updater();
  static void initialize_nodes_updater(ServerFactory &sf);
};
