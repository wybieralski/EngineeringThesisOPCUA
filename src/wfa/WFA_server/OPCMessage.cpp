#include "OPCMessage.h"

std::vector<OPCMessage::Action> OPCMessage::actions;

void OPCMessage::manage_recirculating_filter_system(ServerFactory &sf) {
    sf.recirculating_filter_system_pressure +=1;
//    sf.RecirculatingFilterSystemPressure.SetValue(Variant(sf.recirculating_filter_system_pressure));
}
void OPCMessage::manage_recoater(ServerFactory &sf) {
    sf.recoater_position+=1;
    sf.recoater_speed+=1;
    sf.RecoaterPosition.SetValue(Variant(sf.recoater_position));
    sf.RecoaterSpeed.SetValue(Variant(sf.recoater_speed));
}
void OPCMessage::manage_turbine(ServerFactory &sf) {
    sf.turbine_pressure +=5;
//    sf.TurbineFilerPressure.SetValue(Variant(sf.turbine_pressure));
}
void OPCMessage::continuous_node_updater() {
    for (;;) {
        for (auto &&fn : actions) {
//            fn();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void OPCMessage::add(Action action) { actions.emplace_back(std::move(action)); }

void OPCMessage::initialize_nodes_updater(ServerFactory &sf) {
    add([&]() { manage_recirculating_filter_system(sf); });
    add([&]() { manage_recoater(sf); });
    add([&]() { manage_turbine(sf); });
}
