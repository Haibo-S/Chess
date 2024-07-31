#include "./../include/human.h"
#include <iostream>
#include <string>
#include "./../../game.h"


void Human::turn() {
    std::string command;
    std::getline(std::cin, command);
    game->commandHandler(command);
}
