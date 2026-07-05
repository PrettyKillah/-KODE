#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <windows.h>

using namespace std;

struct Object {
    string name;
    double x;
    double y;
    string type;
    double time;
};

double distanceFromOrigin(const Object& obj) {
    return sqrt(obj.x * obj.x + obj.y * obj.y);
}

string getDistanceGroup(double dist) {
    if (dist <= 100) return "До 100 ед.";
    else if (dist <= 1000) return "До 1000 ед.";
    else if (dist <= 10000) return "До 10000 ед.";
    else return "Слишком далеко";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<Object> objects;

    ifstream file("objects.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл objects.txt" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Object obj;
        ss >> obj.name >> obj.x >> obj.y >> obj.type >> obj.time;
        objects.push_back(obj);
    }
    file.close();

    cout << "Загружено объектов: " << objects.size() << endl;

    char addMore;
    cout << "Хотите добавить объект? (y/n): ";
    cin >> addMore;
    if (addMore == 'y' || addMore == 'Y') {
        Object newObj;
        cout << "Введите имя: ";
        cin >> newObj.name;
        cout << "Введите X: ";
        cin >> newObj.x;
        cout << "Введите Y: ";
        cin >> newObj.y;
        cout << "Введите тип: ";
        cin >> newObj.type;
        cout << "Введите время (число): ";
        cin >> newObj.time;
        objects.push_back(newObj);
        cout << "Объект добавлен!" << endl;
    }

    vector<string> groups = { "До 100 ед.", "До 1000 ед.", "До 10000 ед.", "Слишком далеко" };

    for (const string& groupName : groups) {
        vector<Object> group;
        for (const Object& obj : objects) {
            double dist = distanceFromOrigin(obj);
            if (getDistanceGroup(dist) == groupName) {
                group.push_back(obj);
            }
        }

        sort(group.begin(), group.end(), [](const Object& a, const Object& b) {
            return distanceFromOrigin(a) < distanceFromOrigin(b);
            });

        cout << "\n=== " << groupName << " (" << group.size() << " объектов) ===" << endl;
        for (const Object& obj : group) {
            cout << obj.name << " (" << obj.type << ") "
                << "расстояние: " << distanceFromOrigin(obj) << endl;
        }
    }

    ofstream outFile("result.txt");
    if (outFile.is_open()) {
        for (const string& groupName : groups) {
            vector<Object> group;
            for (const Object& obj : objects) {
                double dist = distanceFromOrigin(obj);
                if (getDistanceGroup(dist) == groupName) {
                    group.push_back(obj);
                }
            }
            sort(group.begin(), group.end(), [](const Object& a, const Object& b) {
                return distanceFromOrigin(a) < distanceFromOrigin(b);
                });
            outFile << "\n=== " << groupName << " (" << group.size() << " объектов) ===" << endl;
            for (const Object& obj : group) {
                outFile << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.time << endl;
            }
        }
        outFile.close();
        cout << "\nРезультат сохранён в result.txt" << endl;
    }

    return 0;
}