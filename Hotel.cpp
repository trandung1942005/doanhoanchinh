#include "Hotel.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "SuiteRoom.h"
#include <iostream>
#include <iomanip>
#include <limits>
void Hotel::addRoom(Room* room) {
    rooms.push_back(room);
}
void Hotel::initializeRooms() {
    ifstream test(filename);
    if (test.good() && test.peek() != EOF) {
        test.close();
        rooms = Room::loadRoomsFromFile(filename);
        return;
    }
    if (rooms.empty()) {
    for (int i = 100; i < 110; ++i) this->addRoom(new SingleRoom(i, 100.00));
    for (int i = 200; i < 210; ++i) this->addRoom(new DoubleRoom(i, 150.00));
    for (int i = 300; i < 310; ++i) this->addRoom(new SuiteRoom(i, 200.00));
    saveToFile();
}
}

void Hotel::saveToFile() {
    ofstream fout(filename);
    for (Room* room : rooms) room->saveStatus(fout);
}

void Hotel::showFormattedRooms() {
    vector<string> types = {"Single", "Double", "Suite"};
    for (const string& type : types) {
        cout << "==============================\n";
        cout << "Danh sách phòng " << type << "\n";
        cout << "==============================\n";
        cout << left
                << setw(14) << "Loại Phòng"     << "|"
                << setw(12) << "Số Phòng"       << "|"
                << setw(12) << "Giá Phòng"      << "|"
                << setw(14) << "Trạng Thái"     << "|"
                << setw(25) << "Tên Khách Hàng" << "|"
                << setw(23) << "Số Điện Thoại"  << "|"
                << setw(13) << "Số Ngày"        << "|"
                << setw(15) << "Tổng Tiền"      << "" 
                <<endl;

        cout<< string(11, '-') << "|"
            << string(9, '-') << "|"
            << string(10, '-') << "|"
            << string(11, '-') << "|"
            << string(22, '-') << "|"
            << string(16, '-') << "|"
            << string(10, '-') << "|"
            << string(11, '-') << endl;

        for (Room* r : rooms) {
            if (r->getRoomType() == type) {
                int soNgay = r->getOccupancyStatus() ? r->getSoNgayThue() : 0;
                double tongTien = soNgay * r->getPrice();

                cout << left
                        << setw(11) << r->getRoomType()     << "|"
                        << setw(9) << r->getRoomNumber()   << "|"
                        << setw(10) << fixed << setprecision(2) << r->getPrice() << "|"
                        << setw(13) << (r->getOccupancyStatus() ? "Đã có khách" : "Trống") << "|"
                        << setw(22) << (r->getOccupancyStatus() ? r->getOccupantName() : "") << "|"
                        << setw(16) << (r->getOccupancyStatus() ? r->getOccupantPhone() : "") << "|"
                        << setw(10) << (r->getOccupancyStatus() ? to_string(soNgay) : "") << "|"
                        << setw(20) << (r->getOccupancyStatus() ? to_string((int)tongTien) : "") << endl;
            }
        }
    }
}

void Hotel::checkInRoom() {
    int number, days;
    string name, phone;
    cout << "Nhập số phòng muốn đặt: "; cin >> number;
    if (cin.fail()) {
    cin.clear(); // xóa trạng thái lỗi
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Lỗi: Vui lòng nhập số phòng hợp lệ!\n";
    return;
}
    for (Room* room : rooms) {
        if (room->getRoomNumber() == number) {
            if (room->getOccupancyStatus()) {
                cout << "Phòng đã có khách.\n"; return;
            }
            cout << "Tên khách: "; cin.ignore(); getline(cin, name);
            cout << "SĐT khách: "; getline(cin, phone);
            cout << "Số ngày thuê: ";
            cin >> days;

            if (cin.fail() || days <= 0) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << " Số ngày không hợp lệ.\n";
                return;
            }

            room->checkIn(name, phone, days);
            saveToFile();
            double tongTien = days * room->getPrice();
            ofstream log("history.txt", ios::app);
            log << "Check-in | Phòng: " << number 
                << " | Tên: " << name 
                << " | SĐT: " << phone 
                << " | Ngày: " << days 
                << " | Tổng tiền: " << tongTien 
                << " | Trạng thái: Chưa thanh toán" << endl;
            cout << "Đặt phòng thành công!\n";
            return;
        }
    }
    cout << "Phòng không tồn tại.\n";
}

void Hotel::checkOutRoom() {
    int number;
    cout << "Nhập số phòng muốn trả: "; cin >> number;
    if (cin.fail()) {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Lỗi: Vui lòng nhập số phòng hợp lệ!\n";
    return;
}
    for (Room* room : rooms) {
        if (room->getRoomNumber() == number) {
            if (!room->getOccupancyStatus()) {
                cout << "Phòng đang trống.\n"; return;
            }
            double tongTien = room->getSoNgayThue() * room->getPrice();
            ofstream log("history.txt", ios::app);
            log << "Check-out | Phòng: " << number 
                << " | Đã thanh toán: " << tongTien << endl;

            room->checkOut();
            saveToFile();
            cout << "Trả phòng thành công!\n";
            return;
        }
    }
    cout << "Phòng không tồn tại.\n";
}

void Hotel::viewHistory() {
    ifstream fin("history.txt");
    if (!fin.is_open()) {
        cout << "⚠️ Không thể mở file lịch sử.\n";
        return;
    }

    cout << "\n========= LỊCH SỬ CHECK-IN/CHECK-OUT =========\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    cout << "==============================================\n";
    fin.close();
}