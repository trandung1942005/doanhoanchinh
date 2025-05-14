#ifndef GUEST_H
#define GUEST_H
#include <string>
using namespace std;

class Guest {
    string name;
    string phone;
public:
    Guest(string n = "", string p = "");
    string getName() const;
    string getPhone() const;
};

#endif
