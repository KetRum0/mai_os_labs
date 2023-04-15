#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "zmqf.h"
using namespace std::chrono;
 
int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3) { 
        std::cout << "Wrong arguments. Not enough parameters!\n";
        exit(1);
    }
    int current_id = std::atoi(argv[1]); 
    int child_id = -1; 
    if (argc == 3) {
        child_id = std::atoi(argv[2]); 
    }
    zmq::context_t context;
    zmq::socket_t parent_socket(context, ZMQ_REP); 
    connect(parent_socket, current_id); 
    zmq::socket_t child_socket(context, ZMQ_REQ); 
    child_socket.setsockopt(ZMQ_SNDTIMEO, 5000); 
    parent_socket.setsockopt(ZMQ_SNDTIMEO, 5000);
    std::string message;
    int flag = 0;
    uint64_t start; 
    uint64_t stop;
    while (1) {
        zmq::message_t message_main;
        message = receive_message(parent_socket); 
        //std::cout << message;
        std::string recieved_message(static_cast<char*>(message_main.data()), message_main.size());
        //std::cout << recieved_message;
        std::istringstream request(message);
        int dest_id;
        request >> dest_id;
        std::string command;
        request >> command; 
        if (dest_id == current_id) {
            if (command == "ping") {
                std::string ans = std::to_string(current_id) + ": Ok"; 
                send_message(parent_socket, ans);

            } else if (command == "pid") { 
                send_message(parent_socket, "OK: " + std::to_string(getpid()));
        
            } else if (command == "create") {
                    int new_child_id;
                    request >> new_child_id; 
                    //std::cout << new_child_id;
                    if (child_id != -1) {
                        unbind(child_socket, child_id); 
                    }
                    bind(child_socket, new_child_id); 
                    pid_t pid = fork(); 
                    if (pid < 0) { 
                        perror("Can't create new process!\n");
                        exit(1);
                    }
                    if (pid == 0) {
                        execl("server", "server", std::to_string(new_child_id).c_str(), std::to_string(child_id).c_str(), NULL);
                        perror("Can't create new process!\n");
                        exit(1);
                    }
                    send_message(child_socket, std::to_string(new_child_id) + "pid");
                    child_id = new_child_id;
                    send_message(parent_socket, receive_message(child_socket)); 

            } else if (command == "remove") { 
                    send_message(parent_socket, "OK"); 
                    disconnect(parent_socket, current_id);
                    break;
            } else if (command == "exec") { 
                    std::string msg = "OK: " + std::to_string(dest_id) + " "; 
                    std::string subcommand;
                    request >> subcommand;
                    if (subcommand == "start"){
                        if(flag == 1){
                            msg += "timer is already started";
                        }        
                        else{
                            flag = 1;
                            msg += "started";
                            start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                        }   
                    } else if(subcommand == "stop") {
                        if(flag == 0) {
                            msg += "timer is not started";
                        }        
                        else {
                            flag = 0;
                            msg += "stopped";   
                        }            
                    } else if(subcommand == "time") {
                        if(flag == 0) {
                            msg += "0";
                        }        
                        else {
                            stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                            msg += std::to_string(stop-start);
                        }      
                    } else {
                        msg += "Error: incorrect subcommand!\n";
                    }    
                    send_message(parent_socket, msg); 
            }
        } else if (child_id != -1) {
            send_message(child_socket, message);
            send_message(parent_socket, receive_message(child_socket));
            if (child_id == dest_id && command == "remove") {
                child_id = -1;
            }
        } else {
            send_message(parent_socket, "Error: node is unavailable!\n"); 
        }
    }
}