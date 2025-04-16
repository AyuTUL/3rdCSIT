#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

#define MAX_DESTINATIONS 20
#define MAX_ATTRACTIONS 5
#define MAX_TRANSPORTATION 3
#define INF 999999.0 

int *posx, *posy;

void dash() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi))
        cout<<"Error getting console screen buffer info.";
    else
    {
    	width=csbi.dwSize.X;
	    cout<<endl;
	    for(int i=0;i<width;i++)
	        cout<<"-";
	    cout<<endl<<endl;
	    fflush(stdout);	
	}
}

void gotoxy(int x, int y) {
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole == INVALID_HANDLE_VALUE)
        cout<<"Error getting console handle.";
    else
    {
    	COORD cursorPos;
	    cursorPos.X=x;
	    cursorPos.Y=y;
	    if(!SetConsoleCursorPosition(hConsole,cursorPos))
	        cout<<"Error setting console cursor position.";
	}
}

char confirm(char s[],int *x,int *y) {
    char c;    
    gotoxy(*x,*y);
    cout<<s;
    cin>>c;
    return(c);
}

template<typename T>
bool saveToFile(const T& data, const char* filename) {
    ofstream file(filename,ios::binary);
    if(!file.is_open()) {
        cout<<"Error opening file for writing: "<<filename<<endl;
        return false;
    }
    file.write(reinterpret_cast<const char*>(&data),sizeof(T));
    file.close();
    return true;
}

template<typename T>
bool loadFromFile(T& data, const char* filename) {
    ifstream file(filename,ios::binary);
    gotoxy(*posx,*posy);
    if(!file.is_open()) {
        cout<<"Error opening file for reading: "<<filename<<endl;
        return false;
    }
    file.read(reinterpret_cast<char*>(&data),sizeof(T));
    file.close();
    return true;
}

enum TransportType {
    AIR,
    BUS,
    CAR,
    OTHER
};

class Attraction {
protected:
    char name[50];
    double cost;
    int timeRequired;

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

    void displayAttraction() const {
        cout << "Attraction: " << name
             << ", Cost: $" << cost
             << ", Time: " << timeRequired << " hrs\n";
    }

    double getCost() const { return cost; }
    int getTimeRequired() const { return timeRequired; }
    const char* getName() const { return name; }

    void updateAttraction(const char* newName, double newCost, int newTime) {
        strncpy(name, newName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        cost = newCost;
        timeRequired = newTime;
    }

    virtual ~Attraction() {}
};

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

class Destination {
private:
    char name[50];
    int stayDuration;
    Attraction* attractions[MAX_ATTRACTIONS];
    int attractionCount;
    
public:
    Destination() {
        strcpy(name, "N/A");
        stayDuration = 0;
        attractionCount = 0;
        
        for(int i = 0; i < MAX_ATTRACTIONS; i++) attractions[i] = NULL;
        
    }

    Destination& operator=(const Destination& other) {
    if (this != &other) {
        strncpy(name, other.name, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        stayDuration = other.stayDuration;

        // Free existing attractions
        for (int i = 0; i < attractionCount; ++i) {
            delete attractions[i];
            attractions[i] = NULL;
        }

        attractionCount = other.attractionCount;

        for (int i = 0; i < MAX_ATTRACTIONS; ++i) {
            if (i < attractionCount && other.attractions[i]) {
                attractions[i] = new Attraction(*other.attractions[i]);
            } else {
                attractions[i] = NULL;
            }
        }
    }
    return *this;
}

    ~Destination() {
        for(int i = 0; i < attractionCount; i++) delete attractions[i];
        
    }
    Attraction* getAttraction(int i) const {
    if (i >= 0 && i < attractionCount) return attractions[i];
    return NULL;
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

    
    
    double calculateTotalCost() {
        double totalCost = 0;
        
        // Add attraction costs
        for(int i = 0; i < attractionCount; i++) {
            totalCost += attractions[i]->getCost();
        }
        
       
        
        return totalCost;
    }

    void displayDestination() {
    	int x=2,y=*posy+1;
        gotoxy(x,y+=2);
        cout<<"Destination : "<<name;
        gotoxy(x,++y);
        cout<<"Duration of Stay : "<<stayDuration<<" days";
        gotoxy(x,y+=2);
        cout<<"Attractions :";
        if(attractionCount>0)     
            for(int i=0;i<attractionCount;i++) {
            	Attraction* a=attractions[i];
            	if (a) {
			        gotoxy(x + 4, ++y);
			        cout << (i + 1) << ". Attraction Name: " << a->getName();
			        gotoxy(x + 6, ++y);
			        cout << "   Cost: Rs " << a->getCost();
			        gotoxy(x + 6, ++y);
			        cout << "   Time Required: " << a->getTimeRequired() << " hrs";
			    }
        } 
		else
            cout<<"No attractions added yet.";
        gotoxy(x,y+=2);
        cout<<"Total Estimated Cost : Rs "<<calculateTotalCost();
        gotoxy(x,++y);
		dash();
		(*posy)=y;
    }

    const char* getName() const { return name; }
    int getStayDuration() const { return stayDuration; }
    int getAttractionCount() const { return attractionCount; }
    
};

struct AttractionData {
    char name[50];
    double cost;
    int timeRequired;
};

struct DestinationRawData {
    char name[50];
    int stayDuration;
    int attractionCount;
    AttractionData attractions[MAX_ATTRACTIONS];
};

struct DestinationData {
    int count;
    DestinationRawData data[MAX_DESTINATIONS];
};

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

struct RouteGraphData {
    int locationCount;
    char locations[MAX_DESTINATIONS][50];
    int routeCount;
    Route routes[MAX_DESTINATIONS * MAX_DESTINATIONS];
    double costMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    int timeMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    TransportType transportMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
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
    RouteGraphData data;
    data.locationCount = locationCount;
    data.routeCount = routeCount;

    for (int i = 0; i < locationCount; ++i) {
        strcpy(data.locations[i], locations[i]);
        for (int j = 0; j < locationCount; ++j) {
            data.costMatrix[i][j] = costMatrix[i][j];
            data.timeMatrix[i][j] = timeMatrix[i][j];
            data.transportMatrix[i][j] = transportMatrix[i][j];
        }
    }

    for (int i = 0; i < routeCount; ++i) {
        data.routes[i] = routes[i];
    }

    if (::saveToFile(data, filename)) {
        cout << "Route graph saved to file: " << filename << "\n";
    } else {
        cout << "Failed to save route graph.\n";
    }
}
    
    void loadFromFile(const char* filename) {
    RouteGraphData data;
    if (!::loadFromFile(data, filename)) {
        cout << "Error opening file for reading: " << filename << "\n";
        return;
    }

    locationCount = data.locationCount;
    routeCount = data.routeCount;

    for (int i = 0; i < locationCount; ++i) {
        strcpy(locations[i], data.locations[i]);
        for (int j = 0; j < locationCount; ++j) {
            costMatrix[i][j] = data.costMatrix[i][j];
            timeMatrix[i][j] = data.timeMatrix[i][j];
            transportMatrix[i][j] = data.transportMatrix[i][j];
        }
    }

    for (int i = 0; i < routeCount; ++i) {
        routes[i] = data.routes[i];
    }

    cout << "Route graph loaded from file: " << filename << "\n";
}
    void dfsAllPaths(int current, int end, bool visited[], int path[], int pathIndex, double currentCost, int currentTime) {
    visited[current] = true;
    path[pathIndex] = current;
    pathIndex++;

    if (current == end) {
        cout << "\nRoute: ";
        for (int i = 0; i < pathIndex; i++) {
            cout << locations[path[i]];
            if (i < pathIndex - 1) cout << " -> ";
        }
        cout << "\n  Total Cost: $" << currentCost;
        cout << "\n  Total Time: " << currentTime / 60 << "h " << currentTime % 60 << "m\n";

        cout << "  Segments:\n";
        for (int i = 0; i < pathIndex - 1; i++) {
            int u = path[i];
            int v = path[i + 1];
            cout << "    " << locations[u] << " -> " << locations[v];
            cout << " | $" << costMatrix[u][v];
            cout << " | " << getTransportTypeName(transportMatrix[u][v]);
            cout << " | " << timeMatrix[u][v] / 60 << "h " << timeMatrix[u][v] % 60 << "m\n";
        }
    } else {
        for (int i = 0; i < locationCount; i++) {
            if (!visited[i] && costMatrix[current][i] != INF) {
                dfsAllPaths(i, end, visited, path, pathIndex,
                            currentCost + costMatrix[current][i],
                            currentTime + timeMatrix[current][i]);
            }
        }
    }

    visited[current] = false;
    pathIndex--;
}

void findAllRoutesWithCost(const char* start, const char* end) {
    int startIndex = findLocationIndex(start);
    int endIndex = findLocationIndex(end);

    if (startIndex == -1 || endIndex == -1) {
        cout << "Invalid locations.\n";
        return;
    }

    bool visited[MAX_DESTINATIONS] = {false};
    int path[MAX_DESTINATIONS];
    int pathIndex = 0;

    cout << "\n=== All Routes from " << start << " to " << end << " ===\n";
    dfsAllPaths(startIndex, endIndex, visited, path, pathIndex, 0.0, 0);
}
};


class TravellerProfile {
private:
    char name[50];
    int age;
    double budget;
    int plannedDays;
    int x, y;

public:
    TravellerProfile() {
        name[0] = '\0';
        age = 0;

        budget = 0;
        plannedDays = 0;
    }

    void setProfile() {
        x=35,y=4;
        system("cls");
    	gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"Traveller Profile : Setup";
        gotoxy(x,++y);
        dash();
        gotoxy(x+=5,y+=3);
        cout<<"Enter your name : ";
        cin.ignore();
        cin.getline(name,sizeof(name));
        gotoxy(x,++y);
        cout<<"Enter age : ";
        cin>>age;
        cin.ignore();
        gotoxy(x,++y);
        cout<<"Enter total travel budget (Rs) : ";
        cin>>budget;
        gotoxy(x,++y);
        cout<<"Enter planned days for travel : ";
        cin>>plannedDays;
        (*posx)=x;
        (*posy)=y+2;
        saveProfile();
    }

    void saveProfile() {
    	gotoxy(*posx,*posy);
        if(saveToFile(*this,"traveller_profile.txt"))
		    cout<<"Profile saved successfully!";
		else 
		    cout<<"Unable to save profile.";
		(*posy)=y+5;
    }

	bool loadProfile() {
    return loadFromFile(*this, "traveller_profile.txt");
}

    void viewProfile() {
    	x=35,y=4;
        system("cls");
    	gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"Traveller Profile : View";
        gotoxy(x,++y);
        dash();
        (*posx)=x-=5;
	    (*posy)=y+=3;
	    if(loadProfile()) {
			gotoxy(x,y-=3);
	        cout<<"Name : "<<name;
	        gotoxy(x,++y);
	        cout<<"Age : "<<age;
	        gotoxy(x,++y);
	        cout<<"Budget : Rs "<<budget;
	        gotoxy(x,++y);
	        cout<<"Planned Days : "<<plannedDays;
	    } else {
	        gotoxy(x,y+=2);
	        cout<<"No profile found. Please set up a profile first.";
	    }
	    (*posx)=40;
		(*posy)=y+3;
	}

    double getBudget() const { return budget; }
    int getPlannedDays() const { return plannedDays; }
    const char* getName() const { return name; }
    
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
    
    void saveDestinations() {
    	char filename[100];
    	int x=35,y=4;
        system("cls");
    	gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"Destinations : Save";
        gotoxy(x,++y);
        dash();
        gotoxy(x,y+=3);
		cout<<"Enter filename to save destinations : ";
		cin>>filename;
    	DestinationData dd;
    	dd.count=destinationCount;
	    for (int i = 0; i < destinationCount; ++i) {
	        Destination& d = destinations[i];
	        DestinationRawData& raw = dd.data[i];
	
	        strcpy(raw.name, d.getName());
	        raw.stayDuration = d.getStayDuration();
	        raw.attractionCount = d.getAttractionCount();
	
	        for (int j = 0; j < raw.attractionCount; ++j) {
	            Attraction* a = d.getAttraction(j);
	            if (a) {
	                strcpy(raw.attractions[j].name, a->getName());
	                raw.attractions[j].cost = a->getCost();
	                raw.attractions[j].timeRequired = a->getTimeRequired();
	            }
	        }
	    }
		gotoxy(x,y+=2);
	    if (::saveToFile(dd,filename)) {
	        cout << "Destinations saved to " << filename << " successfully!";
	    } else {
	        cout << "Failed to save destinations.";
	    }
	    (*posy)=y+=3;
	}

    void loadDestinations() {
    	char filename[100];
    	int x=30,y=4;
        system("cls");
    	gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"Destinations : Load";
        gotoxy(x,++y);
        dash();
        gotoxy(x,y+=3);
		cout<<"Enter filename to load destinations from : ";
		cin>>filename;
        DestinationData dd;
        (*posx)=x;
		(*posy)=y+=2;
	    if (!::loadFromFile(dd, filename))
	    {
	    	gotoxy(x,y+=2);
	    	cout<<"Failed to load destinations.";
		} 
		else
		{
			destinationCount = dd.count;
		    for (int i = 0; i < destinationCount; ++i) {
		        DestinationRawData& raw = dd.data[i];
		        Destination d;
		        d.setName(raw.name);
		        d.setStayDuration(raw.stayDuration);
		
		        for (int j = 0; j < raw.attractionCount; ++j) {
		            AttractionData& a = raw.attractions[j];
		            Attraction* attraction = new Attraction(a.name, a.cost, a.timeRequired);
		            d.addAttraction(attraction);
		        }
		
		        destinations[i] = d;
		        routeGraph.addLocation(d.getName());
		    }
			gotoxy(x,y);
		    cout << "Destinations loaded successfully from " << filename;
		}
		(*posx)=x+=10;
    	(*posy)=y+=3;
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
        cout << "2. Bus\n";
        cout << "3. Car\n";
        cout << "4. Other\n";
        cout << "Enter choice: ";
        cin >> transportChoice;
        cout << "Cost ($): ";
        cin >> cost;
        
        cout << "Time (in minutes): ";
        cin >> time;
        
        
        TransportType type;
        switch(transportChoice) {
            case 1: type = AIR; break;
            case 2: type = BUS; break;
            case 3: type = CAR; break;
         	case 4: type = OTHER; break;
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
    	char filename[100];
		cout << "Enter filename to save routes: ";
		cin >> filename;
    routeGraph.saveToFile(filename);
    cout << "Routes saved to " << filename << " successfully!";
    
}
  void loadRoutes() {
  	char filename[100];
		cout << "Enter filename to load routes from : ";
		cin >> filename;
    routeGraph.loadFromFile(filename);
     cout << "Routes loaded successfully from " << filename << "\n";

}
   
    
    void budgetAnalysis() {
        system("cls");
        cout << "========== BUDGET ANALYSIS ==========" << endl;

        double totalBudget = traveller.getBudget();
        if(totalBudget == 0) {
            cout << "Please set up your traveller profile first!\n";
            return;
        }

        double totalCost = 0;
        double attractionCost = 0;

        for(int i = 0; i < destinationCount; i++) {
            double destCost = destinations[i].calculateTotalCost();
            attractionCost += destCost;
            totalCost += destCost;
        }

        cout << "Total Budget: $" << totalBudget << "\n";
        cout << "Estimated Total Cost: $" << totalCost << "\n";

        if(totalCost > totalBudget) {
            cout << "Budget Deficit: $" << totalCost - totalBudget << "\n";
            cout << "Warning: Your current plan exceeds your budget!\n";
        } else {
            cout << "Budget Surplus: $" << totalBudget - totalCost << "\n";
            cout << "Good news! Your plan is within budget.\n";
        }

        cout << "\nCost Breakdown:\n";
        cout << "  Attractions: $" << attractionCost << "\n";

        // New: show all routes between two points with cost/time
        char start[50], end[50];
        cout << "\nEnter start location for route budget analysis: ";
        cin.ignore();
        cin.getline(start, sizeof(start));

        cout << "Enter destination: ";
        cin.getline(end, sizeof(end));

        routeGraph.findAllRoutesWithCost(start, end);
    }

    void addDestinationDetails() {
        char name[50];
        int days,x=35,y=0;
        system("cls");
    	gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"Destinations : Add";
        gotoxy(x,++y);
        dash();
        gotoxy(x+=5,y+=3);
        cout<<"Enter destination name : ";
        cin.ignore();
        cin.getline(name,sizeof(name));
        gotoxy(x,++y);
        cout<<"Enter stay duration (days) : ";
        cin>>days;
        Destination newDest;
        newDest.setName(name);
        newDest.setStayDuration(days);
        char addMore;
        do {
            char attractionName[50];
            double cost;
            int time;
            cin.ignore();
            gotoxy(x,y+=2);
            cout<<"Enter attraction name : ";
            cin.getline(attractionName,sizeof(attractionName));
            gotoxy(x,++y);
            cout<<"Enter cost (Rs) : ";
            cin>>cost;
            gotoxy(x,++y);
            cout<<"Enter time required (hours) : ";
            cin>>time;
            Attraction* attraction=NULL;
            attraction=new Attraction(attractionName,cost,time);
            if(attraction)
                newDest.addAttraction(attraction);
            gotoxy(x,++y);
            cout<<"Add another attraction? [Y/N] : ";
            cin>>addMore;
        } while(toupper(addMore)=='Y');
        addDestination(newDest);
        gotoxy(x,y+=2);
        cout<<"Destination added successfully!";
        routeGraph.addLocation(name);
   		(*posy)=y+=3; 
	}
     
    void displayDestinations() {
        int x=35,y=0;
        system("cls");
    	gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"Destinations : View";
        gotoxy(x,++y);
        dash();
        (*posy)=y;
        if(destinationCount==0)
        {
        	gotoxy(x+=5,y+=3);
        	cout<<"No destinations added yet!";
		}   
        else
        	
	        for(int i=0;i<destinationCount;i++)
	        {
	        	
	        	destinations[i].displayDestination();
			}
        (*posy)+=3; 
    }
};

int main() {
    TripPlanner planner;
    int choice1,choice2;
    bool exit=false;
    char response;
    int x,y;
    posx=&x;
    posy=&y;
    while(!exit) {
        system("cls");
        x=35,y=4;
        gotoxy(x,y);
        dash();
        gotoxy(42,y+=3);
        cout<<"TOUR PLANNER MENU";
        gotoxy(x,++y);
        dash();
        gotoxy(x+=5,y+=3);
        cout<<"1. Traveller Profile";
        gotoxy(x,++y);
        cout<<"2. Destination";
        gotoxy(x,++y);
        cout<<"3. Route";
        gotoxy(x,++y);
        cout<<"4. Budget Analysis";
        gotoxy(x,++y);
        cout<<"5. Exit";
        gotoxy(x,y+=2);
        cout<<"Enter your choice: ";
        cin>>choice1;
        switch(choice1) {
            case 1:
            	system("cls");
            	gotoxy(x=35,y=4);
		        dash();
		        gotoxy(42,y+=3);
		        cout<<"Traveller Profile : Options";
		        gotoxy(x,++y);
		        dash();
		        gotoxy(x+=5,y+=3);
		        cout<<"1. Setup Traveller Profile";
		        gotoxy(x,++y);
		        cout<<"2. View Traveller Profile";
		        gotoxy(x,y+=2);
		        cout<<"Enter your choice: ";
		        cin>>choice2;
		        if(choice2==1)
                	planner.createProfile();
                else if(choice2==2)
                	planner.viewProfile();
                else
                	cout<<"Invalid choice. Please try again."<<endl;
                break;
            case 2:
            	system("cls");
            	gotoxy(x=35,y=4);
		        dash();
		        gotoxy(42,y+=3);
		        cout<<"Destinations : Options";
		        gotoxy(x,++y);
		        dash();
		        gotoxy(x+=5,y+=3);
		        cout<<"1. Add Destination";
		        gotoxy(x,++y);
		        cout<<"2. View Destinations";
		        gotoxy(x,++y);
		        cout<<"3. Save Destinations";
		        gotoxy(x,++y);
		        cout<<"4. Load Destinations";
		        gotoxy(x,y+=2);
		        cout<<"Enter your choice: ";
		        cin>>choice2;
		        if(choice2==1)
                	planner.addDestinationDetails();
                else if(choice2==2)
                	planner.displayDestinations();
                else if(choice2==3)
					planner.saveDestinations();
                else if(choice2==4)
                	planner.loadDestinations();
                else
                	cout<<"Invalid choice. Please try again."<<endl;
                break;
            case 3:
            	system("cls");
                gotoxy(35,4);
		        dash();
		        gotoxy(42,6);
		        cout<<"Route : Options";
		        gotoxy(35,8);
		        dash();
		        gotoxy(40,10);
		        cout<<"1. Add Route";
		        gotoxy(40,11);
		        cout<<"2. View Route";
		        gotoxy(40,12);
		        cout<<"3. Save Routes";
		        gotoxy(40,13);
		        cout<<"4. Load Routes";
		        gotoxy(40,15);
		        cout<<"Enter your choice: ";
		        cin>>choice2;
		        if(choice2==1)
                	planner.addRoute();
                else if(choice2==2)
                	planner.displayRoutes();
                else if(choice2==3)
					planner.saveRoutes();
                else if(choice2==4)
                	planner.loadRoutes();
                else
                	cout<<"Invalid choice. Please try again."<<endl;
                break;
            case 4:
            	system("cls");
                gotoxy(35,4);
		        dash();
		        gotoxy(42,6);
		        cout<<"Budget Analysis : Options";
		        gotoxy(35,8);
		        dash();
		        gotoxy(40,10);
		        cout<<"1. Find Best Route";
		        gotoxy(40,11);
		        cout<<"2. Budget Analysis";
		        gotoxy(40,12);
		        cout<<"Enter your choice: ";
		        cin>>choice2;
		        if(choice2==1)
                	planner.findBestRoute();
                else if(choice2==2)
					planner.budgetAnalysis();
                else
                	cout<<"Invalid choice. Please try again."<<endl;
                break;
            case 5:
            	system("cls");
                exit=true;
                break;
            default:
                cout<<"Invalid choice. Please try again."<<endl;
        }
        if(!exit) {
            response=confirm("Return to Main Menu? (y/n): ", posx, posy);
            if(tolower(response)!='y')
                exit=true;
        }
    }
    gotoxy(40,24);
    cout<<"Thank you for using Travel Planner!\n";
    return 0;
}
