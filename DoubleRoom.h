#ifndef DOUBLEROOM_H
#define DOUBLEROOM_H

#include "Room.h"

class DoubleRoom : public Room {
public:
    DoubleRoom(int number, double price);
    string getRoomType() const override;
    void displayInfo() const override;
};

#endif
