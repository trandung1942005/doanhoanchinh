#include "Room.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "SuiteRoom.h"
#include <fstream>
#include <sstream>

Room::Room(int number, double price) : roomNumber(number), price(price), isOccupied(false) {}
Room::~Room() {}

int Room::getRoomNumber() const { return roomNumber; }
double Room::getPrice() const { return price; }
bool Room::getOccupancyStatus() const { return isOccupied; }
string Room::getOccupantName() const { return occupantName; }
string Room::getOccupantPhone() const { return occupantPhone; }

void Room::checkIn(const string& name, const string& phone, int days) {
    isOccupied = true;
    occupantName = name;
    occupantPhone = phone;
    soNgayThue = days;
}

void Room::checkOut() {
    isOccupied = false;
    occupantName = "";
    occupantPhone = "";
}

void Room::saveStatus(ostream& out) const {
out << getRoomType() << '|' 
    << roomNumber << '|' 
    << price << '|' 
    << isOccupied << '|' 
    << occupantName << '|' 
    << occupantPhone << '|' 
    << soNgayThue << '\n';

}

vector<Room*> Room::loadRoomsFromFile(const string& filename) {
    vector<Room*> rooms;
    ifstream fin(filename);
    if (!fin) return rooms;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string type, name, phone;
        int number, occupied, days;
        double price;

        getline(ss, type, '|');
        ss >> number; ss.ignore();
        ss >> price; ss.ignore();
        ss >> occupied; ss.ignore();
        getline(ss, name, '|');
        getline(ss, phone, '|');
        ss >> days;

        Room* room = nullptr;
        if (type == "Single") room = new SingleRoom(number, price);
        else if (type == "Double") room = new DoubleRoom(number, price);
        else if (type == "Suite")  room = new SuiteRoom(number, price);

        if (room) {
            if (occupied) room->checkIn(name, phone, days);
            rooms.push_back(room);
        }
    }

    return rooms;
}
