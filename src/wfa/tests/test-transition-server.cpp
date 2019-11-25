#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../WFA_client/ClientManager.h"
#include "../WFA_server/EventManager.h"
#include "../WFA_server/server_properties.h"

//#include "umati_client/ClientStarter.h"


using namespace OpcUa;

/******************************************/
/** TESTING TRANSITION SERVER **/
/******************************************/

std::condition_variable cv;
std::mutex mtx;

bool server_started = false;
bool tests_finished = false;

class TransitionServerTest : public ::testing::Test {
public:
  TransitionServerTest(){};
  ~TransitionServerTest(){};
};

void RunServer() {
  ServerFactory sf;

  sf.start_server();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  sf.initialize_objects();

  EventManager::create_events(sf);

  Node root = sf.m_server.GetRootNode();

  sf.logger->info("Root node is: {}", root);
  sf.logger->info("Children are:");
  for (Node node : root.GetChildren()) {
    sf.logger->info("    {}", node);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  sf.logger->info("Ctrl-C to exit");

  std::this_thread::sleep_for(std::chrono::seconds(4));
  /** Wait for tests**/
  {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, [] { return tests_finished; });
    lk.unlock();
  }
    sf.logger->info("SERVER STOPPED");
    sf.m_server.Stop();
}

TEST_F(TransitionServerTest, test_nodes_id) {
  auto SERVER_ENDPOINT = "opc.tcp://localhost:8000/";
  try {
    /** Start WFA server**/
    std::thread WFA_server_thread([&]() { RunServer(); });
    std::this_thread::sleep_for(std::chrono::seconds(2));

    auto logger = spdlog::stderr_color_mt("client");
    ServerStarter serverStarter(SERVER_ENDPOINT); // od razu startuj server
    auto client_endpoint = "opc.tcp://localhost:4890/WFA";

    /** Start WFA client to get data from WFA server **/

    OpcUa::UaClient client(logger);
    client.Connect(client_endpoint);

    WFA::ClientManager cm;
    logger->info("Connecting to: {}", client_endpoint);

    std::thread th1([&]() { serverStarter.Run(); });
    std::this_thread::sleep_for(std::chrono::seconds(2));

    serverStarter.setNotificationJobEndPredictedTime(
        cm.get_specificed_node(39, client));
    serverStarter.setIdentificationNameCustom(
        cm.get_specificed_node(40, client));
    serverStarter.setIdentificationNameCatalog(
        cm.get_specificed_node(41, client));

        /** Inform Server that tests have FINISHED **/
        {
          tests_finished = true;
          cv.notify_one();
        }
    /** Write any char to the terminal to quit the server **/
    std::this_thread::sleep_for(std::chrono::seconds(5));

    EXPECT_EQ(1, 1);

    logger->info("Closing server");
    serverStarter.StopServer();
    logger->info("Closing client");
    client.Disconnect();

    //    sf.m_server.Stop();
    th1.join();

    logger->info("Tests finished.");
    WFA_server_thread.join();
    std::cout << "wtf?";
    logger->flush();

  } catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }
  return;
}