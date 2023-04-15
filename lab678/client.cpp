#include <unistd.h>
#include <iostream>
#include <vector>
#include <zmq.hpp>
#include <sstream>
#include "topology.h"
#include "zmqf.h"

int main() {
    Topology network;
    std::vector<zmq::socket_t> branches;
    zmq::context_t context;
    std::string command; 
    zmq::socket_t main_socket(context, ZMQ_REP);
    std::string message;
    std::cout << "> ";

    while (std::cin >> command) {
        if (command == "create") {
            int node_id, parent_id;
            std::cin >> node_id >> parent_id; 
            if (network.Find(node_id) != -1) { 
                std::cout << "Error: already exists!\n"; 
            } else if (parent_id == -1) { 
                pid_t pid = fork(); 
                if (pid < 0) {
                    perror("Can't create new process!\n");
                    exit(EXIT_FAILURE);
                } 
                if (pid == 0) {
                    execl("server", "server", std::to_string(node_id).c_str(), NULL);
                    perror("Can't execute new process!\n");
                    exit(EXIT_FAILURE);
                }
                branches.emplace_back(context, ZMQ_REQ); 
                branches[branches.size() - 1].setsockopt(ZMQ_SNDTIMEO, 5000); 
                bind(branches[branches.size() - 1], node_id); 
                send_message(branches[branches.size() - 1], std::to_string(node_id) + "pid");
                std::string reply = receive_message(branches[branches.size() - 1]); 
                std::cout << reply << "\n"; 
                network.Insert(node_id, parent_id);
            } else if (network.Find(parent_id) == -1) { 
                std::cout << "Error: parent not found!\n";
            } else {
                int branch = network.Find(parent_id);
                send_message(branches[branch], std::to_string(parent_id) + " create " + std::to_string(node_id));
                std::string reply = receive_message(branches[branch]); 
                std::cout << reply << "\n"; 
                network.Insert(node_id, parent_id); 
            }

        } else if (command == "remove") { 
            int id;
            std::cin >> id; 
            int branch = network.Find(id); 
            if (branch == -1) {
                std::cout << "Error: incorrect node id!\n";
            } else {
                bool is_first = (network.GetFirstId(branch) == id); 
                send_message(branches[branch], std::to_string(id) + " remove"); 
                std::string reply = receive_message(branches[branch]);
                std::cout << reply << std::endl; 
                network.Erase(id); 
                if (is_first) {
                    unbind(branches[branch], id); 
                    branches.erase(std::next(branches.begin(), branch)); 
                }
            }

        } else if (command == "exec") { 
            size_t count = 0;
            int destId;
            std::cin >> destId;
            int branch = network.Find(destId); 
            if (branch == -1) {
                std::cout << "Error: incorrect node id!\n";
            } else {
                std::string subcommand;
                std::cin >> subcommand; 
                send_message(branches[branch], std::to_string(destId) + "exec " + subcommand);
                std::string reply = receive_message(branches[branch]);
                std::cout << reply << "\n"; 
            }

        } else if (command == "ping") { 
            int destId;
            std::cin >> destId; 
            int branch = network.Find(destId); 
            if (branch == -1) {
                std::cout << "Error: incorrect node id!\n";
            } else {
                send_message(branches[branch], std::to_string(destId) + "ping");
                std::string reply = receive_message(branches[branch]);
                std::cout << reply << "\n"; 
            }

        } else if (command == "exit") { 
            for (size_t i = 0; i < branches.size(); ++i) { 
                int first_node_id = network.GetFirstId(i); 
                send_message(branches[i], std::to_string(first_node_id) + " remove"); 
                std::string reply = receive_message(branches[i]); 
                if (reply != "OK") {
                    std::cout << reply << "\n";
                } else {
                    unbind(branches[i], first_node_id); 
                }
            }
            exit(0);

        } else {
            std::cout << "Incorrect command: " << command << "<!\n"; 
        }

        std::cout << "> ";

    }
}