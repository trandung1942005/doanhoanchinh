#ifndef SINGLEROOM_H
#define SINGLEROOM_H

#include "Room.h"

class SingleRoom : public Room {
public:
    SingleRoom(int number, double price);
    string getRoomType() const override;
    void displayInfo() const override;
};

#endif
