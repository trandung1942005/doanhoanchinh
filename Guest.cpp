#include "Guest.h"

Guest::Guest(string n, string p) : name(n), phone(p) {}

string Guest::getName() const { return name; }
string Guest::getPhone() const { return phone; }
