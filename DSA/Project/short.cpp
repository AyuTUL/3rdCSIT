// Fully Optimized Travel Planner with Enhanced UIHelper and Modular Input/Output
// UI preserved exactly, uses only allowed headers

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<windows.h>
using namespace std;

#define MAX_DESTINATIONS 20
#define MAX_ATTRACTIONS 5
#define INF 999999.0

int *posx, *posy;

class UIHelper {
public:
    static void gotoxy(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            COORD cursorPos = { (SHORT)x, (SHORT)y };
            SetConsoleCursorPosition(hConsole, cursorPos);
        }
    }
    static void centerDash() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            int width = csbi.dwSize.X;
            cout << endl << string(width, '-') << "\n\n";
            fflush(stdout);
        }
    }
    static void printAt(int x, int y, const char* text) {
        gotoxy(x, y);
        cout << text;
    }
    static void header(const char* title, int& x, int& y) {
        system("cls");
        gotoxy(x, y);
        centerDash();
        gotoxy(x, y += 3);
        cout << title;
        gotoxy(x, ++y);
        centerDash();
    }
    static void menuOption(int x, int& y, const char* label) {
        gotoxy(x, ++y); cout << label;
    }
    static void promptInput(int x, int& y, const char* label) {
        gotoxy(x, ++y); cout << label;
    }
};

template<typename T>
bool saveToFile(const T& data, const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file) return false;
    file.write(reinterpret_cast<const char*>(&data), sizeof(T));
    return true;
}

template<typename T>
bool loadFromFile(T& data, const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) return false;
    file.read(reinterpret_cast<char*>(&data), sizeof(T));
    return true;
}

enum TransportType { AIR, BUS, CAR, OTHER };
const char* toStr(TransportType t) {
    switch (t) {
        case AIR: return "Air"; case BUS: return "Bus";
        case CAR: return "Car"; default: return "Other";
    }
}

class Attraction {
    char name[50];
    double cost; int time;
public:
    Attraction(const char* n = "N/A", double c = 0, int t = 0) {
        strncpy(name, n, 49); name[49] = 0; cost = c; time = t;
    }
    double getCost() const { return cost; }
    int getTime() const { return time; }
    const char* getName() const { return name; }
};

class Destination {
    char name[50];
    int stay, count;
    Attraction* attractions[MAX_ATTRACTIONS];
public:
    Destination() : stay(0), count(0) { strcpy(name, "N/A"); for (int i = 0; i < MAX_ATTRACTIONS; i++) attractions[i] = nullptr; }
    ~Destination() { for (int i = 0; i < count; i++) delete attractions[i]; }
    void setName(const char* n) { strncpy(name, n, 49); name[49] = 0; }
    void setStay(int d) { stay = d; }
    void addAttraction(const char* n, double c, int t) {
        if (count < MAX_ATTRACTIONS)
            attractions[count++] = new Attraction(n, c, t);
    }
    double totalCost() const {
        double sum = 0;
        for (int i = 0; i < count; i++) sum += attractions[i]->getCost();
        return sum;
    }
    void display(int& x, int& y) const {
        UIHelper::gotoxy(x, y += 2); cout << "Destination : " << name;
        UIHelper::gotoxy(x, ++y); cout << "Duration of Stay : " << stay << " days";
        UIHelper::gotoxy(x, y += 2); cout << "Attractions :";
        for (int i = 0; i < count; i++) {
            UIHelper::gotoxy(x + 5, ++y); cout << i + 1 << ". " << attractions[i]->getName();
            UIHelper::gotoxy(x + 12, ++y); cout << "Cost : Rs " << attractions[i]->getCost();
            UIHelper::gotoxy(x + 12, ++y); cout << "Time Required : " << attractions[i]->getTime() << " hrs";
        }
        if (count == 0) cout << "No attractions added yet.";
        UIHelper::gotoxy(x, y += 2); cout << "Total Estimated Cost : Rs " << totalCost();
        UIHelper::gotoxy(x, ++y); UIHelper::centerDash(); *posy = y;
    }
};

class Traveller {
    char name[50];
    int age, days; double budget;
public:
    Traveller() : age(0), days(0), budget(0) { name[0] = 0; }
    void input() {
        int x = 45, y = 4;
        UIHelper::header("Traveller Profile : Setup", x, y);
        UIHelper::promptInput(x, y, "Enter your name : ");
        cin.ignore(); cin.getline(name, 50);
        UIHelper::promptInput(x, y, "Enter age : "); cin >> age;
        UIHelper::promptInput(x, y, "Enter budget (Rs): "); cin >> budget;
        UIHelper::promptInput(x, y, "Enter planned days : "); cin >> days;
        saveToFile(*this, "traveller.dat");
    }
    bool load() { return loadFromFile(*this, "traveller.dat"); }
    void display() {
        int x = 45, y = 4;
        UIHelper::header("Traveller Profile : View", x, y);
        if (load()) {
            UIHelper::printAt(x, y += 3, (string("Name : ") + name).c_str());
            UIHelper::gotoxy(x, ++y); cout << "Age : " << age;
            UIHelper::gotoxy(x, ++y); cout << "Budget : Rs " << budget;
            UIHelper::gotoxy(x, ++y); cout << "Planned Days : " << days;
        } else UIHelper::printAt(x, y += 3, "No profile found.");
        *posx = x; *posy = y + 3;
    }
    double getBudget() const { return budget; }
};

int main() {
    int x, y, choice;
    posx = &x; posy = &y;
    Traveller traveller;
    Destination destinations[MAX_DESTINATIONS];
    int destCount = 0;
    bool exit = false;
    while (!exit) {
        UIHelper::header("TOUR PLANNER MENU", x = 45, y = 4);
        UIHelper::menuOption(x, y, "1. Traveller Profile");
        UIHelper::menuOption(x, y, "2. Add Destination");
        UIHelper::menuOption(x, y, "3. View Destinations");
        UIHelper::menuOption(x, y, "4. Exit");
        UIHelper::promptInput(x, y += 2, "Enter choice: "); cin >> choice;

        if (choice == 1) {
            UIHelper::header("Traveller Profile : Options", x = 45, y = 4);
            UIHelper::menuOption(x, y, "1. Setup Profile");
            UIHelper::menuOption(x, y, "2. View Profile");
            UIHelper::promptInput(x, y += 2, "Choice: ");
            int ch; cin >> ch;
            if (ch == 1) traveller.input();
            else if (ch == 2) traveller.display();
        } else if (choice == 2) {
            UIHelper::header("Destinations : Add", x = 45, y = 4);
            char name[50]; int days, attrTime; double attrCost;
            char attrName[50], more = 'Y';
            UIHelper::promptInput(x, y += 3, "Destination name: ");
            cin.ignore(); cin.getline(name, 50);
            UIHelper::promptInput(x, y, "Stay (days): "); cin >> days;
            Destination d; d.setName(name); d.setStay(days);
            while (toupper(more) == 'Y') {
                cin.ignore();
                UIHelper::promptInput(x, y += 2, "Attraction name: "); cin.getline(attrName, 50);
                UIHelper::promptInput(x, y, "Cost (Rs): "); cin >> attrCost;
                UIHelper::promptInput(x, y, "Time (hrs): "); cin >> attrTime;
                d.addAttraction(attrName, attrCost, attrTime);
                UIHelper::promptInput(x, y, "Add more? [Y/N]: "); cin >> more;
            }
            if (destCount < MAX_DESTINATIONS) destinations[destCount++] = d;
            UIHelper::promptInput(x, y += 2, "Destination added.");
        } else if (choice == 3) {
            UIHelper::header("Destinations : View", x = 45, y = 4);
            if (destCount == 0) UIHelper::promptInput(x, y += 3, "No destinations.");
            else for (int i = 0; i < destCount; i++) destinations[i].display(x, y);
        } else exit = true;

        if (!exit) {
            UIHelper::promptInput(x, y += 2, "Return to menu? [Y/N]: ");
            char again; cin >> again;
            if (toupper(again) != 'Y') exit = true;
        }
    }
    UIHelper::header("Thank you for using Tour Planner", x = 40, y = 4);
    return 0;
}
