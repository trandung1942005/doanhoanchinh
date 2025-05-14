#include "SuiteRoom.h"
SuiteRoom::SuiteRoom(int number, double price) : Room(number, price) {}
string SuiteRoom::getRoomType() const { return "Suite"; }
void SuiteRoom::displayInfo() const {}
