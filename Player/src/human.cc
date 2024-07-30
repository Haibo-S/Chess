#include "./../include/human.h"
#include <iostream>
#include <string>

Human::Human(Team tc, Board *b, bool t) : Player(tc, b, t) {}

void Human::turn() {
    std::string command;
    std::cout << "Enter your move: ";
    std::getline(std::cin, command);
    // Assuming you have a method to handle commands in your Game or Board class
    //board->handleCommand(command);
}
