#ifndef FREEOPCUA_CLIENTMANAGER_H
#define FREEOPCUA_CLIENTMANAGER_H

#include "SubscribtionManager.h"
#include "client_properties.h"
#include <map>
#include <opc/ua/client/client.h>
#include <string>
#include <vector>


namespace WFA {

    class ClientManager {
    private:
        SubscribtionManager subscribtionManager;

    public:
        std::map<unsigned short, std::vector<std::string>> map_of_nodes;
        std::map<unsigned short, std::vector<std::string>> map_of_nodes2;

        void fill_map_of_nodes(
                std::map<unsigned short, std::vector<std::string>> &variables_map);
        void fill_map_of_nodes2(
                std::map<std::string, std::vector<std::string>> &variables_map);

        template <typename T>
        std::string get_specificed_node(T node,
                                 OpcUa::UaClient &client);

        void subscribe_operator(
                std::ofstream &csv_file, OpcUa::Node myvar,
                std::pair<unsigned short, std::vector<std::string>> varpath,
                OpcUa::Node &root, SubscribtionManager subMan,
                const std::shared_ptr<spdlog::logger> &logger, OpcUa::UaClient &client);

        void get_data(const std::string &endpoint,
                      const std::shared_ptr<spdlog::logger> &logger,
                      OpcUa::UaClient &client);
    };

    template <typename T>
    std::string ClientManager::get_specificed_node(T node,
                                                   OpcUa::UaClient &client){
        static_assert(
                std::is_same<int,T>::value
                ||  std::is_same<std::string,T>::value ,
                "Must be eithr string or int"
        );

        OpcUa::Node root = client.GetRootNode();
        OpcUa::Node objects = client.GetObjectsNode();
        OpcUa::Node nsnode = client.GetNode(OpcUa::ObjectId::Server_NamespaceArray);
        OpcUa::Variant ns = nsnode.GetValue();
        OpcUa::Node current_node;
        fill_map_of_nodes(map_of_nodes);

        std::vector<std::string> varpath;

        if (std::is_same<int,T>::value){
             varpath = map_of_nodes[node];
        } else if (std::is_same<std::string,T>::value){
             varpath = map_of_nodes2[node];
        }

        subscribtionManager.subscribtion = client.CreateSubscription(20, subscribtionManager);
        auto myvar = root.GetChild(varpath);

        subscribtionManager.handle = subscribtionManager.subscribtion->SubscribeDataChange(myvar);
        auto retval = myvar.GetDataValue().Value.ToString();
        return retval;
    }

}
#endif // FREEOPCUA_CLIENTMANAGER_H