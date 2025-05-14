#include "SingleRoom.h"
SingleRoom::SingleRoom(int number, double price) : Room(number, price) {}
string SingleRoom::getRoomType() const { return "Single"; }
void SingleRoom::displayInfo() const {}
