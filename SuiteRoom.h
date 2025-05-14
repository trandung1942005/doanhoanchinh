#ifndef SUITEROOM_H
#define SUITEROOM_H

#include "Room.h"

class SuiteRoom : public Room {
public:
    SuiteRoom(int number, double price);
    string getRoomType() const override;
    void displayInfo() const override;
};

#endif
