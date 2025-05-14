#include "Hotel.h"
#include <iostream>
#include <list>
#include<vector>
#include"Employee.h"
using namespace std;
list<Employee> employees;


void loadEmployees() {
    ifstream infile("passwords.in");
    string id, password;
    while (infile >> id >> password) {
        employees.push_back(Employee(id, password));
    }
    infile.close();
}

bool login(string id, string password) {
    for (const auto& emp : employees) {
        if (emp.getId() == id && emp.getPassword() == password) {
            std::cout << "Access granted" << std::endl;
            return true;
        }
    }
    std::cout << "Login failed!" << std::endl;
    return false;
}

void changePassword(string id) {
    string oldPassword, newPassword;
    std::cout << "Enter current password: ";
    std::cin >> oldPassword;
    if (login(id, oldPassword)) {
        std::cout << "Enter new password: ";
        std::cin >> newPassword;
        for (auto& emp : employees) {
            if (emp.getId() == id) {
                emp.setPassword(newPassword);
                // Cập nhật mật khẩu trong file
                std::vector<Employee> updatedEmployees(employees.begin(), employees.end());
                std::ofstream outfile("passwords.in");
                if (outfile) {
                    for (const auto& e : updatedEmployees) {
                        outfile << e.getId() << " " << e.getPassword() << std::endl;
                    }
                    outfile.close();
                    std::cout << "Password changed and saved successfully!" << std::endl;
                }
                else {
                    std::cerr << "Failed to open password file for writing." << std::endl;
                }
                return;
            }
        }
    }
}

void addEmployee() {
    string id, password;
    std::cout << "Enter new employee ID: ";
    std::cin >> id;
    std::cout << "Enter new employee password: ";
    std::cin >> password;
    Employee newEmployee(id, password);
    employees.push_back(newEmployee);
    newEmployee.saveEmployeeInfo(); // Save new employee info to passwords.in
    std::cout << "Employee added successfully!" << std::endl;
}

void removeEmployee() {
    string id;
    std::cout << "Enter employee ID to remove: ";
    std::cin >> id;

    // Xóa nhân viên khỏi danh sách employees
    employees.remove_if([&id](const Employee& emp) { return emp.getId() == id; });

    // Đọc toàn bộ nội dung file passwords.in vào một vector tạm thời
    std::vector<Employee> updatedEmployees;
    std::ifstream infile("passwords.in");
    string empId, empPassword;
    while (infile >> empId >> empPassword) {
        if (empId != id) { // Chỉ thêm những nhân viên không bị xóa
            updatedEmployees.push_back(Employee(empId, empPassword));
        }
    }
    infile.close();

    // Ghi lại toàn bộ nội dung đã cập nhật vào file passwords.in
    std::ofstream outfile("passwords.in");
    if (outfile) {
        for (const auto& e : updatedEmployees) {
            outfile << e.getId() << " " << e.getPassword() << std::endl;
        }
        outfile.close();
        std::cout << "Employee removed successfully!" << std::endl;
    }
    else {
        std::cerr << "Failed to open password file for writing." << std::endl;
    }
}







int main() {
    loadEmployees();
    Hotel hotel;
    hotel.initializeRooms();
    int choice;
    string id, password;
    std::cout << "Enter your employee ID: ";
    std::cin >> id;
    std::cout << "Enter your password: ";
    std::cin >> password;
    if (login(id, password)) {
        do {
            cout << "\n===== QUẢN LÝ KHÁCH SẠN =====\n";
            cout << "1. Xem trạng thái phòng\n";
            cout << "2. Đặt phòng (Check-in)\n";
            cout << "3. Trả phòng (Check-out)\n";
            cout << "4. Xem lịch sử\n";
            cout << "5. Đổi mật khẩu\n";
            cout << "6. Thêm nhân viên\n";
            cout << "7. Xóa nhân viên\n";
            cout << "8. Thoát\n";
            cout << "Chọn: ";
            cin >> choice;

            switch (choice) {
            case 1:
                hotel.showFormattedRooms();
                break;
            case 2:
                hotel.checkInRoom();
                break;
            case 3:
                hotel.checkOutRoom();
                break;
            case 4:
                hotel.viewHistory();
                break;
            case 5:
                changePassword(id);
                break;
            case 6:
                addEmployee();
                break;
            case 7:
                removeEmployee();
                break;
            case 8:
                cout << "Tạm biệt!\n";
                break;
            default:
                cout << "⚠️ Lựa chọn không hợp lệ.\n";
            }
        } while (choice != 8);
        return 0;
    }
}