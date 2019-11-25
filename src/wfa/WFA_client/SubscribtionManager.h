//
// Created by lw on 22.03.19.

#include <opc/ua/client/client.h>
#include <opc/ua/subscription.h>
#include <fstream>

#include "DataRecorder.h"

#ifndef FREEOPCUA_SUBSCRIBTIONMANAGER_H
#define FREEOPCUA_SUBSCRIBTIONMANAGER_H



class SubscribtionManager : public OpcUa::SubscriptionHandler {
public:
//    SubClient sclt;
    OpcUa::Subscription::SharedPtr subscribtion;
    OpcUa::Subscription::SharedPtr event_subscribtion;
    uint32_t handle;
    uint32_t event_handle;

    void DataChange(uint32_t handle, const OpcUa::Node &node, const OpcUa::Variant &val,
                    OpcUa::AttributeId attr) override;

};


#endif //FREEOPCUA_SUBSCRIBTIONMANAGER_H
