#ifndef HOTEL_H
#define HOTEL_H

#include "Room.h"
#include <vector>
using namespace std;

class Hotel {
    vector<Room*> rooms;
    const string filename = "rooms.in";
public:
    void viewHistory();
    void addRoom(Room* room);
    void initializeRooms();
    void saveToFile();
    void showFormattedRooms();
    void checkInRoom();
    void checkOutRoom();
};

#endif
