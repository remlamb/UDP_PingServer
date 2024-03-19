#include <SFML/Network.hpp>
#include <chrono>
#include <iostream>

#include "message.h"

int main() {
  sf::IpAddress serverAddress = "localhost";
  unsigned short serverPort = 12345;

  sf::UdpSocket socket;
  sf::Clock timer;

  while (true) {
    Message messageSent;
    std::cout << "Enter message: ";
    std::cin >> messageSent.content;

    sf::Packet request;
    request << messageSent;

    timer.restart();
    if (socket.send(request, serverAddress, serverPort) != sf::Socket::Done) {
      std::cerr << "Could not send message to server \n";
      return EXIT_FAILURE;
    }

    sf::IpAddress senderAddress;
    unsigned short senderPort;
    sf::Packet answer;
    if (socket.receive(answer, senderAddress, senderPort) != sf::Socket::Done) {
      std::cerr << "Could not receive answer from server\n";
      return EXIT_FAILURE;
    }

    auto timeForTransmission = timer.getElapsedTime();
    std::string answerMsg;
    answer >> answerMsg;
    answerMsg += " in " + std::to_string(timeForTransmission.asMicroseconds()) +
                 "MicroSec";

    std::cout << "Server answered: " << answerMsg << '\n';
  }
}
