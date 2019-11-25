//
// Created by lw on 22.03.19.
//

#include "SubscribtionManager.h"


void SubscribtionManager::DataChange(uint32_t handle, const OpcUa::Node &node,
                                     const OpcUa::Variant &val,
                                     OpcUa::AttributeId attr)  {

    std::cout << "Received DataChange event, value of Node " << node
            << " is now: " << val.ToString() << std::endl;
}