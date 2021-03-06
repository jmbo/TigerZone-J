﻿#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

class Client {
public:
  Client(std::string hostname, std::string port);
  ~Client();

  void connectToServer();
  void sendMessage(std::string message);
  std::string receiveMessage();
  void closeConnection();

private:
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[1000];
  void error(const char *msg);
};

#endif
