#include "./../include/player.h"

Player::Player(Team tc, Board *board, bool turn) : team(tc), board(board), turnActive(turn) {}

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
