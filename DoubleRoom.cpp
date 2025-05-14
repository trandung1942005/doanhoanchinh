#include "DoubleRoom.h"
DoubleRoom::DoubleRoom(int number, double price) : Room(number, price) {}
string DoubleRoom::getRoomType() const { return "Double"; }
void DoubleRoom::displayInfo() const {}
