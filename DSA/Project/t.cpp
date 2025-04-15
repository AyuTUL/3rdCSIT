#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

// Constants for maximum number of destinations and attractions
#define MAX_DESTINATIONS 20
#define MAX_ATTRACTIONS 5
#define MAX_TRANSPORTATION 3
#define INF 999999.0  // Representing infinity

// Cursor Position
int *posx, *posy;

// UI Helper Functions
void dash() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width, i;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        cout << "Error getting console screen buffer info.";
        return;
    }
    width = csbi.dwSize.X;
    cout << endl;
    for (i = 0; i < width; i++) {
        cout << "-";
    }
    cout << endl << endl;
    fflush(stdout);
}

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole == INVALID_HANDLE_VALUE) {
        cout << "Error getting console handle.";
        exit(1);
    }
    COORD cursorPos;
    cursorPos.X = x;
    cursorPos.Y = y;
    if(!SetConsoleCursorPosition(hConsole, cursorPos)) {
        cout << "Error setting console cursor position.";
        exit(1);
    }
}

char confirm(char s[], int *x, int *y) {
    char c;    
    gotoxy(*x, *y);
    cout << s;
    cin >> c;
    return(c);
}

bool openFile(fstream &file, char* filename, ios::openmode mode) {
    file.open(filename, mode);
    if (file.fail()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }
    return true;
}

// Enumeration for transportation types
enum TransportType {
    AIR,
    TRAIN,
    BUS,
    CAR,
    OTHER
};

// Base class for attractions
class Attraction {
protected:
    char name[50];
    double cost;
    int timeRequired; // in hours
    

public:
    Attraction() {
        strcpy(name, "N/A");
        cost = 0;
        timeRequired = 0;
       
    }

    Attraction(const char* n, double c, int time) {
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        cost = c;
        timeRequired = time;
       
    }

    virtual void displayAttraction() = 0; // Pure virtual function

    // Getters
    double getCost() const { return cost; }
    int getTimeRequired() const { return timeRequired; }
    const char* getName() const { return name; }

    // Setter for updating attraction
    virtual void updateAttraction(const char* newName, double newCost, int newTime) {
        strncpy(name, newName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        cost = newCost;
        timeRequired = newTime;
        
    }

    virtual ~Attraction() {}
};

// Derived attraction type classes
class Historical : public Attraction {
public:
    Historical() : Attraction() {}
    Historical(const char* n, double c, int time) : Attraction(n, c, time) {}

    void displayAttraction() {
        cout << "Historical Site: " << name 
             << ", Cost: $" << cost 
             << ", Time: " << timeRequired << " hrs"
             << "\n";
    }
};

class Natural : public Attraction {
public:
    Natural() : Attraction() {}
    Natural(const char* n, double c, int time) : Attraction(n, c, time) {}

    void displayAttraction() {
        cout << "Natural Attraction: " << name 
             << ", Cost: $" << cost 
             << ", Time: " << timeRequired << " hrs"
             << "\n";
    }
};

class Cultural : public Attraction {
public:
    Cultural() : Attraction() {}
    Cultural(const char* n, double c, int time) : Attraction(n, c, time) {}

    void displayAttraction() {
        cout << "Cultural Attraction: " << name 
             << ", Cost: $" << cost 
             << ", Time: " << timeRequired << " hrs"
             << "\n";
    }
};

class Recreational : public Attraction {
public:
    Recreational() : Attraction() {}
    Recreational(const char* n, double c, int time) : Attraction(n, c, time) {}

    void displayAttraction() {
        cout << "Recreational Activity: " << name 
             << ", Cost: $" << cost 
             << ", Time: " << timeRequired << " hrs\n";
    }
};

// Route class to represent connections between destinations
class Route {
private:
    char from[50];
    char to[50];
    double cost;
    int time;  // in minutes
    TransportType transportType;

public:
    Route() {
        strcpy(from, "");
        strcpy(to, "");
        cost = 0;
        time = 0;
        transportType = OTHER;
    }

    Route(const char* f, const char* t, double c, int tm, TransportType type) {
        strncpy(from, f, sizeof(from) - 1);
        from[sizeof(from) - 1] = '\0';
        strncpy(to, t, sizeof(to) - 1);
        to[sizeof(to) - 1] = '\0';
        cost = c;
        time = tm;
        transportType = type;
    }

    const char* getFrom() const { return from; }
    const char* getTo() const { return to; }
    double getCost() const { return cost; }
    int getTime() const { return time; }
    TransportType getTransportType() const { return transportType; }

    const char* getTypeString() const {
        switch(transportType) {
            case AIR: return "Air";
            case TRAIN: return "Train";
            case BUS: return "Bus";
            case CAR: return "Car";
            case OTHER: return "Other";
            default: return "Unknown";
        }
    }

    void displayRoute() {
        cout << "Route: " << from << " -> " << to
             << " (" << getTypeString() << ")"
             << ", Cost: $" << cost
             << ", Time: " << time / 60 << "h " << time % 60 << "m\n";
    }
};

// Transportation class
class Transportation {
private:
    TransportType type;
    char from[50];
    char to[50];
    double cost;
    int duration; // in minutes

public:
    Transportation() {
        type = OTHER;
        strcpy(from, "N/A");
        strcpy(to, "N/A");
        cost = 0;
        duration = 0;
    }

    Transportation(TransportType t, const char* f, const char* t_dest, double c, int d) {
        type = t;
        strncpy(from, f, sizeof(from) - 1);
        from[sizeof(from) - 1] = '\0';
        strncpy(to, t_dest, sizeof(to) - 1);
        to[sizeof(to) - 1] = '\0';
        cost = c;
        duration = d;
    }

    const char* getTypeString() const {
        switch(type) {
            case AIR: return "Air";
            case TRAIN: return "Train";
            case BUS: return "Bus";
            case CAR: return "Car";
            
            case OTHER: return "Other";
            default: return "Unknown";
        }
    }

    void displayTransportation() {
        cout << getTypeString() << ": " << from << " -> " << to
             << ", Cost: $" << cost
             << ", Duration: " << duration / 60 << "h " << duration % 60 << "m\n";
    }

    double getCost() const { return cost; }
    int getDuration() const { return duration; }
    TransportType getType() const { return type; }
    const char* getFrom() const { return from; }
    const char* getTo() const { return to; }
};


// Destination class
class Destination {
private:
    char name[50];

    int stayDuration; // in days
    Attraction* attractions[MAX_ATTRACTIONS];
    int attractionCount;
    Transportation* transportations[MAX_TRANSPORTATION];
    int transportationCount;
    

public:
    Destination() {
        strcpy(name, "N/A");
    
        stayDuration = 0;
        attractionCount = 0;
        transportationCount = 0;
        for(int i = 0; i < MAX_ATTRACTIONS; i++) {
            attractions[i] = NULL;
        }
        for(int i = 0; i < MAX_TRANSPORTATION; i++) {
            transportations[i] = NULL;
        }
        
    }

    ~Destination() {
        for(int i = 0; i < attractionCount; i++) {
            if(attractions[i]) delete attractions[i];
        }
        for(int i = 0; i < transportationCount; i++) {
            if(transportations[i]) delete transportations[i];
        }
        
    }

    void setName(const char* n) {
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    void setStayDuration(int days) {
        stayDuration = days;
    }

    void addAttraction(Attraction* attraction) {
        if(attractionCount < MAX_ATTRACTIONS) {
            attractions[attractionCount++] = attraction;
        } else {
            cout << "Maximum attractions reached for this destination!\n";
        }
    }

    void addTransportation(Transportation* transport) {
        if(transportationCount < MAX_TRANSPORTATION) {
            transportations[transportationCount++] = transport;
        } else {
            cout << "Maximum transportation options reached for this destination!\n";
        }
    }

    
    double calculateTotalCost() {
        double totalCost = 0;
        
        // Add attraction costs
        for(int i = 0; i < attractionCount; i++) {
            totalCost += attractions[i]->getCost();
        }
        
        // Add transportation costs
        for(int i = 0; i < transportationCount; i++) {
            totalCost += transportations[i]->getCost();
        }
        
        return totalCost;
    }

    void displayDestination() {
        cout << "\n========================================\n";
        cout << "Destination: " << name << "\n";
        cout << "Duration of Stay: " << stayDuration << " days\n";
        cout << "----------------------------------------\n";
        
        // Display attractions
        if(attractionCount > 0) {
            cout << "Attractions:\n";
            for(int i = 0; i < attractionCount; i++) {
                cout << (i+1) << ". ";
                attractions[i]->displayAttraction();
            }
        } else {
            cout << "No attractions added yet.\n";
        }
        cout << "----------------------------------------\n";
        
        // Display transportation options
        if(transportationCount > 0) {
            cout << "Transportation:\n";
            for(int i = 0; i < transportationCount; i++) {
                cout << (i+1) << ". ";
                transportations[i]->displayTransportation();
            }
        } else {
            cout << "No transportation options added yet.\n";
        }
        cout << "----------------------------------------\n";
        
        cout << "----------------------------------------\n";
        cout << "Total Estimated Cost: $" << calculateTotalCost() << "\n";
        cout << "========================================\n";
    }

    const char* getName() const { return name; }
    int getStayDuration() const { return stayDuration; }
    int getAttractionCount() const { return attractionCount; }
    int getTransportationCount() const { return transportationCount; }
    };

// TravellerProfile class
class TravellerProfile {
private:
    char name[50];
    int age;
    char preferences[100]; // Travel preferences/interests
    double budget;
    int plannedDays;
    int x, y;

public:
    TravellerProfile() {
        name[0] = '\0';
        age = 0;
        preferences[0] = '\0';
        budget = 0;
        plannedDays = 0;
    }

    void setProfile() {
        x = 35, y = 1;
        system("cls");
        gotoxy(x, y);
        cout << "Traveller Profile Setup:";
        y += 2;
        gotoxy(x, y);
        cout << "Enter your name: ";
        cin.ignore();
        cin.getline(name, sizeof(name));
        gotoxy(x, ++y);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        gotoxy(x, ++y);
        cout << "Enter travel preferences (e.g., adventure, culture, relaxation): ";
        cin.getline(preferences, sizeof(preferences));
        gotoxy(x, ++y);
        cout << "Enter total travel budget ($): ";
        cin >> budget;
        gotoxy(x, ++y);
        cout << "Enter planned days for travel: ";
        cin >> plannedDays;
        saveProfile();
    }

    void saveProfile() {
        ofstream file("traveller_profile.txt", ios::binary);
        gotoxy(35, y+2);
        if (file.is_open()) {
            file.write((char*)this, sizeof(TravellerProfile));
            file.close();
            cout << "Profile saved successfully!";
        } else {
            cout << "Unable to save profile.";
        }
        (*posy) = y+4;
    }

    void viewProfile() {
        x = 35, y = 4;     
        fstream file;
        openFile(file, "traveller_profile.txt", ios::in|ios::binary);
        if (file.is_open()) {
            system("cls");
            gotoxy(x, y);
            dash();
            y += 3;
            gotoxy(x, y);
            cout << "|\tTraveller Profile\t|";
            gotoxy(x, ++y);
            dash();
            TravellerProfile tempProfile;
            file.read((char*)&tempProfile, sizeof(TravellerProfile));
            y += 3;
            gotoxy(x, y);
            cout << "Name: " << tempProfile.name;
            gotoxy(x, ++y);
            cout << "Age: " << tempProfile.age;
            gotoxy(x, ++y);
            cout << "Preferences: " << tempProfile.preferences;
            gotoxy(x, ++y);
            cout << "Budget: $" << tempProfile.budget;
            gotoxy(x, ++y);
            cout << "Planned Days: " << tempProfile.plannedDays;
            (*posy) = y+2;
            file.close();
        } else {
            gotoxy(35, 22);
            cout << "No profile found. Please set up a profile first.\n";
            (*posy) = 24;
        }    
    }

    double getBudget() const { return budget; }
    int getPlannedDays() const { return plannedDays; }
    const char* getName() const { return name; }
    const char* getPreferences() const { return preferences; }
};

// Graph representation for route planning
class RouteGraph {
private:
    // Adjacency matrix representation of the graph
    double costMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    int timeMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    TransportType transportMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    
    char locations[MAX_DESTINATIONS][50];  // Names of locations
    int locationCount;
    
    Route routes[MAX_DESTINATIONS * MAX_DESTINATIONS];  // All routes
    int routeCount;

public:
    RouteGraph() {
        locationCount = 0;
        routeCount = 0;
        
        // Initialize the matrices
        for(int i = 0; i < MAX_DESTINATIONS; i++) {
            strcpy(locations[i], "");
            for(int j = 0; j < MAX_DESTINATIONS; j++) {
                if(i == j) {
                    costMatrix[i][j] = 0;
                    timeMatrix[i][j] = 0;
                } else {
                    costMatrix[i][j] = INF;
                    timeMatrix[i][j] = INF;
                }
                transportMatrix[i][j] = OTHER;
            }
        }
    }
    
    // Add a location to the graph
    int addLocation(const char* name) {
        // Check if location already exists
        for(int i = 0; i < locationCount; i++) {
            if(strcmp(locations[i], name) == 0) {
                return i;  // Return existing index
            }
        }
        
        // Add new location
        if(locationCount < MAX_DESTINATIONS) {
            strncpy(locations[locationCount], name, 49);
            locations[locationCount][49] = '\0';
            return locationCount++;
        } else {
            cout << "Maximum destinations reached!\n";
            return -1;
        }
    }
    
    // Add a route between two locations
    void addRoute(const char* from, const char* to, double cost, int time, TransportType type) {
        int fromIndex = addLocation(from);
        int toIndex = addLocation(to);
        
        if(fromIndex != -1 && toIndex != -1) {
            costMatrix[fromIndex][toIndex] = cost;
            timeMatrix[fromIndex][toIndex] = time;
            transportMatrix[fromIndex][toIndex] = type;
            
            // Add to routes array for easy reference
            if(routeCount < MAX_DESTINATIONS * MAX_DESTINATIONS) {
                routes[routeCount++] = Route(from, to, cost, time, type);
            }
        }
    }
    
    // Find all locations
    void displayLocations() {
        if(locationCount == 0) {
            cout << "No locations added yet!\n";
            return;
        }
        
        cout << "Available Locations:\n";
        for(int i = 0; i < locationCount; i++) {
            cout << (i+1) << ". " << locations[i] << "\n";
        }
    }
    
    // Display all routes
    void displayRoutes() {
        if(routeCount == 0) {
            cout << "No routes added yet!\n";
            return;
        }
        
        cout << "Available Routes:\n";
        for(int i = 0; i < routeCount; i++) {
            cout << (i+1) << ". ";
            routes[i].displayRoute();
        }
    }
    
    // Find the index of a location by name
    int findLocationIndex(const char* name) {
        for(int i = 0; i < locationCount; i++) {
            if(strcmp(locations[i], name) == 0) {
                return i;
            }
        }
        return -1;  // Not found
    }
    
    // Apply Dijkstra's algorithm to find the shortest path based on cost or time
    void findShortestPath(const char* start, const char* end, bool useCost) {
        int startIndex = findLocationIndex(start);
        int endIndex = findLocationIndex(end);
        
        if(startIndex == -1 || endIndex == -1) {
            cout << "One or both locations not found!\n";
            return;
        }
        
        // Weight matrix - either cost or time based on preference
        double weight[MAX_DESTINATIONS][MAX_DESTINATIONS];
        for(int i = 0; i < locationCount; i++) {
            for(int j = 0; j < locationCount; j++) {
                if(useCost) {
                    weight[i][j] = costMatrix[i][j];
                } else {
                    weight[i][j] = (double)timeMatrix[i][j];
                }
            }
        }
        
        // Distance array
        double dist[MAX_DESTINATIONS];
        // Visited array
        bool visited[MAX_DESTINATIONS];
        // Previous node array
        int prev[MAX_DESTINATIONS];
        
        // Initialize
        for(int i = 0; i < locationCount; i++) {
            dist[i] = INF;
            visited[i] = false;
            prev[i] = -1;
        }
        
        dist[startIndex] = 0;
        
        // Main algorithm
        for(int count = 0; count < locationCount - 1; count++) {
            // Find the minimum distance vertex from the unvisited set
            double min = INF;
            int minIndex = -1;
            
            for(int v = 0; v < locationCount; v++) {
                if(!visited[v] && dist[v] <= min) {
                    min = dist[v];
                    minIndex = v;
                }
            }
            
            // Mark the vertex as visited
            visited[minIndex] = true;
            
            // Update distance values of adjacent vertices
            for(int v = 0; v < locationCount; v++) {
                if(!visited[v] && weight[minIndex][v] != INF && 
                   dist[minIndex] != INF && 
                   dist[minIndex] + weight[minIndex][v] < dist[v]) {
                    dist[v] = dist[minIndex] + weight[minIndex][v];
                    prev[v] = minIndex;
                }
            }
        }
        
        // Print the shortest path
        cout << "\n===== Shortest Path Found =====\n";
        
        if(dist[endIndex] == INF) {
            cout << "No path exists between " << start << " and " << end << "\n";
            return;
        }
        
        // Reconstruct and display the path
        cout << "Path: ";
        
        // Use a temporary array to store path
        int path[MAX_DESTINATIONS];
        int pathLen = 0;
        
        for(int at = endIndex; at != -1; at = prev[at]) {
            path[pathLen++] = at;
        }
        
        // Print in reverse order (start to end)
        for(int i = pathLen - 1; i >= 0; i--) {
            cout << locations[path[i]];
            if(i > 0) cout << " -> ";
        }
        cout << "\n";
        
        // Print total cost/time
        if(useCost) {
            cout << "Total Cost: $" << dist[endIndex] << "\n";
        } else {
            int hours = (int)dist[endIndex] / 60;
            int mins = (int)dist[endIndex] % 60;
            cout << "Total Time: " << hours << "h " << mins << "m\n";
        }
        
        // Print each segment details
        cout << "\nRoute Details:\n";
        for(int i = pathLen - 1; i > 0; i--) {
            int from = path[i];
            int to = path[i-1];
            
            cout << "From: " << locations[from] << " To: " << locations[to] << "\n";
            cout << "  Transport Type: " << getTransportTypeName(transportMatrix[from][to]) << "\n";
            cout << "  Cost: $" << costMatrix[from][to] << "\n";
            cout << "  Time: " << timeMatrix[from][to] / 60 << "h " << timeMatrix[from][to] % 60 << "m\n";
            
            if(i > 1) cout << "---\n";
        }
    }
    
    const char* getTransportTypeName(TransportType type) {
        switch(type) {
            case AIR: return "Air";
            case TRAIN: return "Train";
            case BUS: return "Bus";
            case CAR: return "Car";
          
            case OTHER: return "Other";
            default: return "Unknown";
        }
    }
    
    int getLocationCount() const { return locationCount; }
    int getRouteCount() const { return routeCount; }
    
    const char* getLocationName(int index) const {
        if(index >= 0 && index < locationCount) {
            return locations[index];
        }
        return "";
    }
    
    void saveToFile(const char* filename) {
        ofstream file(filename, ios::binary);
        if(!file.is_open()) {
            cout << "Error opening file for writing: " << filename << "\n";
            return;
        }
        
        // Save location count and locations
        file.write((char*)&locationCount, sizeof(locationCount));
        for(int i = 0; i < locationCount; i++) {
            file.write(locations[i], sizeof(locations[i]));
        }
        
        // Save route count and routes
        file.write((char*)&routeCount, sizeof(routeCount));
        for(int i = 0; i < routeCount; i++) {
            file.write((char*)&routes[i], sizeof(Route));
        }
        
        // Save matrices
        for(int i = 0; i < locationCount; i++) {
            for(int j = 0; j < locationCount; j++) {
                file.write((char*)&costMatrix[i][j], sizeof(double));
                file.write((char*)&timeMatrix[i][j], sizeof(int));
                file.write((char*)&transportMatrix[i][j], sizeof(TransportType));
            }
        }
        
        file.close();
        cout << "Route graph saved to file: " << filename << "\n";
    }
    
    void loadFromFile(const char* filename) {
        ifstream file(filename, ios::binary);
        if(!file.is_open()) {
            cout << "Error opening file for reading: " << filename << "\n";
            return;
        }
        
        // Reset current data
        locationCount = 0;
        routeCount = 0;
        
        // Load location count and locations
        file.read((char*)&locationCount, sizeof(locationCount));
        for(int i = 0; i < locationCount; i++) {
            file.read(locations[i], sizeof(locations[i]));
        }
        
        // Load route count and routes
        file.read((char*)&routeCount, sizeof(routeCount));
        for(int i = 0; i < routeCount; i++) {
            file.read((char*)&routes[i], sizeof(Route));
        }
        
        // Load matrices
        for(int i = 0; i < locationCount; i++) {
            for(int j = 0; j < locationCount; j++) {
                file.read((char*)&costMatrix[i][j], sizeof(double));
                file.read((char*)&timeMatrix[i][j], sizeof(int));
                file.read((char*)&transportMatrix[i][j], sizeof(TransportType));
            
            }
        }
        
        file.close();
        cout << "Route graph loaded from file: " << filename << "\n";
    }
};

// TripPlanner class
class TripPlanner {
private:
    Destination destinations[MAX_DESTINATIONS];
    int destinationCount;
    RouteGraph routeGraph;
    TravellerProfile traveller;
    
public:
    TripPlanner() {
        destinationCount = 0;
    }
    
    ~TripPlanner() {
        // Destinations will be automatically cleaned up by their destructors
    }
    
    void addDestination(const Destination& dest) {
        if(destinationCount < MAX_DESTINATIONS) {
            destinations[destinationCount++] = dest;
        } else {
            cout << "Maximum destinations reached!\n";
        }
    }
    
    void createProfile() {
        traveller.setProfile();
    }
    
    void viewProfile() {
        traveller.viewProfile();
    }
    
    void addRoute() {
        char from[50], to[50];
        double cost;
        int time, transportChoice;
        
        system("cls");
        routeGraph.displayLocations();
        cout << "\nEnter new route details:\n";
        
        cout << "From (location name): ";
        cin.ignore();
        cin.getline(from, sizeof(from));
        
        cout << "To (location name): ";
        cin.getline(to, sizeof(to));
        
        cout << "Transportation Type:\n";
        cout << "1. Air\n";
        cout << "2. Train\n";
        cout << "3. Bus\n";
        cout << "4. Car\n";
        cout << "5. Ship\n";
        cout << "6. Other\n";
        cout << "Enter choice: ";
        cin >> transportChoice;
        cout << "Cost ($): ";
        cin >> cost;
        
        cout << "Time (in minutes): ";
        cin >> time;
        
        
        TransportType type;
        switch(transportChoice) {
            case 1: type = AIR; break;
            case 2: type = TRAIN; break;
            case 3: type = BUS; break;
            case 4: type = CAR; break;
         
            default: type = OTHER;
        }
        
        routeGraph.addRoute(from, to, cost, time, type);
        cout << "\nRoute added successfully!\n";
    }
    
    void displayRoutes() {
        system("cls");
        cout << "========== AVAILABLE ROUTES ==========\n";
        routeGraph.displayRoutes();
    }
    
    void findBestRoute() {
        char from[50], to[50];
        int preference;
        
        system("cls");
        cout << "========== ROUTE PLANNING ==========\n";
        routeGraph.displayLocations();
        
        cout << "\nEnter starting location: ";
        cin.ignore();
        cin.getline(from, sizeof(from));
        
        cout << "Enter destination: ";
        cin.getline(to, sizeof(to));
        
        cout << "Optimization preference:\n";
        cout << "1. Optimize for cost\n";
        cout << "2. Optimize for time\n";
        cout << "Enter choice: ";
        cin >> preference;
        
        bool optimizeForCost = (preference == 1);
        
        routeGraph.findShortestPath(from, to, optimizeForCost);
    }
    
    void saveRoutes() {
        routeGraph.saveToFile("routes.dat");
        cout << "Routes saved successfully!\n";
    }
    
    void loadRoutes() {
        routeGraph.loadFromFile("routes.dat");
        cout << "Routes loaded successfully!\n";
    }
    
    void createItinerary() {
        system("cls");
        cout << "========== CREATE TRAVEL ITINERARY ==========\n";
        
        int days = traveller.getPlannedDays();
        if(days == 0) {
            cout << "Please set up your traveller profile first!\n";
            return;
        }
        
        cout << "Itinerary for " << traveller.getName() << " (" << days << " days):\n\n";
        
        for(int day = 1; day <= days; day++) {
            cout << "Day " << day << ":\n";
            cout << "  Morning: [Activity]\n";
            cout << "  Afternoon: [Activity]\n";
            cout << "  Evening: [Activity]\n";
            }
        
        cout << "This is a template. You can customize it by adding specific activities,\n";
       }
    
    void budgetAnalysis() {
        system("cls");
        cout << "========== BUDGET ANALYSIS ==========\n";
        
        double totalBudget = traveller.getBudget();
        if(totalBudget == 0) {
            cout << "Please set up your traveller profile first!\n";
            return;
        }
        
        double totalCost = 0;
        for(int i = 0; i < destinationCount; i++) {
            totalCost += destinations[i].calculateTotalCost();
        }
        
        cout << "Total Budget: $" << totalBudget << "\n";
        cout << "Estimated Total Cost: $" << totalCost << "\n";
        
        if(totalCost > totalBudget) {
            double deficit = totalCost - totalBudget;
            cout << "Budget Deficit: $" << deficit << "\n";
            cout << "Warning: Your current plan exceeds your budget!\n";
        } else {
            double surplus = totalBudget - totalCost;
            cout << "Budget Surplus: $" << surplus << "\n";
            cout << "Good news! Your plan is within budget.\n";
        }
        
        // Breakdown by category
        cout << "\nCost Breakdown:\n";
        double attractionCost = 0, transportationCost = 0;
        
        // Calculate costs by category - this is simplified
        for(int i = 0; i < destinationCount; i++) {
            // This would require more detailed implementation
            // to separate costs by category within each destination
        }
        
        cout << "  Attractions: $" << attractionCost << "\n";
        cout << "  Transportation: $" << transportationCost << "\n";
        }
    
    void addDestinationDetails() {
        char name[50];
        int days;
        
        system("cls");
        cout << "========== ADD DESTINATION ==========\n";
        
        cout << "Enter destination name: ";
        cin.ignore();
        cin.getline(name, sizeof(name));
        
        cout << "Enter stay duration (days): ";
        cin >> days;
        
        Destination newDest;
        newDest.setName(name);
        
        newDest.setStayDuration(days);
        
        // Add attractions
        char addMore;
        do {
            int attractionType;
            char attractionName[50];
            double cost;
            int time;
            
            cout << "\nAdd an attraction:\n";
            cout << "1. Historical Site\n";
            cout << "2. Natural Attraction\n";
            cout << "3. Cultural Attraction\n";
            cout << "4. Recreational Activity\n";
            cout << "Enter choice: ";
            cin >> attractionType;
            cin.ignore();
            
            cout << "Enter attraction name: ";
            cin.getline(attractionName, sizeof(attractionName));
            
            cout << "Enter cost ($): ";
            cin >> cost;
            
            cout << "Enter time required (hours): ";
            cin >> time;
            
            Attraction* attraction = NULL;
            switch(attractionType) {
                case 1: attraction = new Historical(attractionName, cost, time); break;
                case 2: attraction = new Natural(attractionName, cost, time); break;
                case 3: attraction = new Cultural(attractionName, cost, time); break;
                case 4: attraction = new Recreational(attractionName, cost, time); break;
                default: cout << "Invalid choice!\n";
            }
            
            if(attraction) {
                newDest.addAttraction(attraction);
            }
            
            cout << "Add another attraction? (y/n): ";
            cin >> addMore;
        } while(tolower(addMore) == 'y');
        
        
        
        addDestination(newDest);
        cout << "\nDestination added successfully!\n";
        
        // Also add to route graph
        routeGraph.addLocation(name);
    }
    
    void displayDestinations() {
        system("cls");
        cout << "========== DESTINATIONS ==========\n";
        
        if(destinationCount == 0) {
            cout << "No destinations added yet!\n";
            return;
        }
        
        for(int i = 0; i < destinationCount; i++) {
            destinations[i].displayDestination();
        }
    }
};

// Main function
int main() {
    TripPlanner planner;
    int choice;
    bool exit = false;
    char response;
    int x = 35, y = 4;
    posx = &x;
    posy = &y;

    while(!exit) {
        system("cls");
        gotoxy(35, 4);
        dash();
        gotoxy(42, 6);
        cout << "TRAVEL PLANNER MENU";
        gotoxy(35, 8);
        dash();
        gotoxy(40, 10);
        cout << "1. Setup Traveller Profile";
        gotoxy(40, 11);
        cout << "2. View Traveller Profile";
        gotoxy(40, 12);
        cout << "3. Add Destination";
        gotoxy(40, 13);
        cout << "4. View Destinations";
        gotoxy(40, 14);
        cout << "5. Add Route";
        gotoxy(40, 15);
        cout << "6. View Routes";
        gotoxy(40, 16);
        cout << "7. Find Best Route";
        gotoxy(40, 17);
        cout << "8. Create Itinerary";
        gotoxy(40, 18);
        cout << "9. Budget Analysis";
        gotoxy(40, 19);
        cout << "10. Save Routes";
        gotoxy(40, 20);
        cout << "11. Load Routes";
        gotoxy(40, 21);
        cout << "12. Exit";
        gotoxy(40, 23);
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                planner.createProfile();
                break;
            case 2:
                planner.viewProfile();
                break;
            case 3:
                planner.addDestinationDetails();
                gotoxy(40, 22);
                break;
            case 4:
                planner.displayDestinations();
                break;
            case 5:
                planner.addRoute();
                break;
            case 6:
                planner.displayRoutes();
                break;
            case 7:
                planner.findBestRoute();
                break;
            case 8:
                planner.createItinerary();
                break;
            case 9:
                planner.budgetAnalysis();
                break;
            case 10:
                planner.saveRoutes();
                break;
            case 11:
                planner.loadRoutes();
                break;
            case 12:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        if(!exit) {
            response = confirm("\nReturn to Main Menu? (y/n): ", posx, posy);
            if(tolower(response) != 'y') {
                exit = true;
            }
        }
    }

    gotoxy(40, 24);
    cout << "Thank you for using Travel Planner!\n";
    return 0;
}