#ifndef LAB6_ZMQ_F_H
#define LAB6_ZMQ_F_H

#include <iostream>
#include <string>
#include <zmq.hpp>

const int MAIN_PORT = 4040;

void send_message(zmq::socket_t& socket, const std::string& msg); 

std::string receive_message(zmq::socket_t& socket); 

void connect(zmq::socket_t& socket, int id);

void disconnect(zmq::socket_t& socket, int id); 

void bind(zmq::socket_t& socket, int id);

void unbind(zmq::socket_t& socket, int id);

#endif