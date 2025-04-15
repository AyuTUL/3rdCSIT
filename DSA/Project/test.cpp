// Simplified Travel Planner (Attraction types removed)
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

#define MAX_DESTINATIONS 20
#define MAX_ATTRACTIONS 5
#define MAX_TRANSPORTATION 3
#define INF 999999.0

int *posx, *posy;

void dash() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) return;
    width = csbi.dwSize.X;
    cout << endl;
    for (int i = 0; i < width; i++) cout << "-";
    cout << endl << endl;
    fflush(stdout);
}

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, cursorPos);
}

char confirm(const char s[], int *x, int *y) {
    char c;    
    gotoxy(*x, *y);
    cout << s;
    cin >> c;
    return c;
}

class Attraction {
private:
    char name[50];
    double cost;
    int timeRequired;

public:
    Attraction() {
        strcpy(name, "N/A");
        cost = 0;
        timeRequired = 0;
    }

    Attraction(const char* n, double c, int t) {
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        cost = c;
        timeRequired = t;
    }

    void displayAttraction() const {
        cout << "Attraction: " << name << ", Cost: $" << cost
             << ", Time: " << timeRequired << " hrs\n";
    }

    double getCost() const { return cost; }
};

class Destination {
private:
    char name[50];
    int stayDuration;
    Attraction attractions[MAX_ATTRACTIONS];
    int attractionCount;

public:
    Destination() {
        strcpy(name, "N/A");
        stayDuration = 0;
        attractionCount = 0;
    }

    void setName(const char* n) {
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    void setStayDuration(int days) {
        stayDuration = days;
    }

    void addAttraction(const Attraction& a) {
        if (attractionCount < MAX_ATTRACTIONS)
            attractions[attractionCount++] = a;
        else
            cout << "Maximum attractions reached!\n";
    }

    double calculateTotalCost() {
        double total = 0;
        for (int i = 0; i < attractionCount; i++)
            total += attractions[i].getCost();
        return total;
    }

    void displayDestination() {
        cout << "\n========================================\n";
        cout << "Destination: " << name << "\n";
        cout << "Duration of Stay: " << stayDuration << " days\n";
        cout << "----------------------------------------\n";
        cout << "Attractions:\n";
        for (int i = 0; i < attractionCount; i++) {
            cout << (i+1) << ". ";
            attractions[i].displayAttraction();
        }
        cout << "Total Estimated Cost: $" << calculateTotalCost() << "\n";
        cout << "========================================\n";
    }
};

class TripPlanner {
private:
    Destination destinations[MAX_DESTINATIONS];
    int destinationCount;

public:
    TripPlanner() { destinationCount = 0; }

    void addDestination() {
        char name[50];
        int days;
        cout << "Enter destination name: ";
        cin.ignore();
        cin.getline(name, sizeof(name));
        cout << "Enter stay duration (days): ";
        cin >> days;

        Destination d;
        d.setName(name);
        d.setStayDuration(days);

        char more;
        do {
            char aname[50];
            double cost;
            int time;
            cout << "\nEnter attraction name: ";
            cin.ignore();
            cin.getline(aname, sizeof(aname));
            cout << "Enter cost ($): ";
            cin >> cost;
            cout << "Enter time required (hours): ";
            cin >> time;
            d.addAttraction(Attraction(aname, cost, time));
            cout << "Add another attraction? (y/n): ";
            cin >> more;
        } while(tolower(more) == 'y');

        if (destinationCount < MAX_DESTINATIONS)
            destinations[destinationCount++] = d;
    }

    void displayDestinations() {
        if (destinationCount == 0) {
            cout << "No destinations added.\n";
            return;
        }
        for (int i = 0; i < destinationCount; i++) {
            destinations[i].displayDestination();
        }
    }
};

int main() {
    TripPlanner planner;
    int choice;
    char response;
    int x = 35, y = 4;
    posx = &x; posy = &y;

    do {
        system("cls");
        gotoxy(35, 4); dash();
        gotoxy(42, 6); cout << "TRAVEL PLANNER MENU";
        gotoxy(35, 8); dash();
        gotoxy(40, 10); cout << "1. Add Destination";
        gotoxy(40, 11); cout << "2. View Destinations";
        gotoxy(40, 12); cout << "3. Exit";
        gotoxy(40, 14); cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: planner.addDestination(); break;
            case 2: planner.displayDestinations(); break;
            case 3: return 0;
            default: cout << "Invalid choice!\n";
        }

        response = confirm("\nReturn to Main Menu? (y/n): ", posx, posy);
    } while (tolower(response) == 'y');

    gotoxy(40, 24); cout << "Thank you for using Travel Planner!\n";
    return 0;
}
