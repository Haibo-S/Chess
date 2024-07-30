#include "player.h"

Player::Player(Team tc, Board *board, Game *g, bool turn) : team(tc), board(board), game(g), turnActive(turn) {}

Player::~Player() {}

bool Player::getTurn() {
    return turnActive;
}

Team Player::getTeam() {
    return team;
}

void Player::setTeam(Team tc) {
    team = tc;
}

void Player::setTurn(bool turn) {
    turnActive = turn;
}
