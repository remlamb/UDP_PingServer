#include <SFML/Network.hpp>
#include <iostream>

#include "message.h"

int main() {
  sf::UdpSocket socket;
  if (socket.bind(12345) != sf::Socket::Done) {
    // error...
    std::cerr << "Could not bind to port\n";
    return EXIT_FAILURE;
  }
  std::cout << "Server is running\n";

  while (true) {
    sf::IpAddress clientAddress;
    unsigned short clientPort;
    sf::Packet requestReceived;
    if (socket.receive(requestReceived, clientAddress, clientPort) !=
        sf::Socket::Done) {
      std::cerr << "Did not receive message correctly\n";
      continue;
    }

    Message messageReceived;
    requestReceived >> messageReceived;

    std::cout << "Client " << clientAddress << ':' << clientPort
              << " sent: " << messageReceived.content << '\n';

    std::string text =
        messageReceived.content + " from IP : " + clientAddress.toString();

    sf::Packet answer;
    answer << text;

    if (socket.send(answer, clientAddress, clientPort) != sf::Socket::Done) {
      std::cerr << "Did not send answer message correctly\n";
    }
  }

  return EXIT_SUCCESS;
}