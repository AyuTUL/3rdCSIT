#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
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
void drawHeader(const char* title,int& x,int& y) {
    system("cls");
	gotoxy(x,y);
    dash();
    gotoxy(x,y+=3);
    cout << title;
    gotoxy(x, ++y);
    dash();
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
	        strcpy(name,"N/A");
	        cost=0;
	        timeRequired=0;
	    }
	    Attraction(const char* n,double c,int time) {
	        strncpy(name,n,sizeof(name)-1);
	        name[sizeof(name)-1]='\0';
	        cost=c;
	        timeRequired=time;
	    }
	    double getCost() const { return cost; }
	    int getTimeRequired() const { return timeRequired; }
	    const char* getName() const { return name; }
	    void updateAttraction(const char* newName,double newCost,int newTime) {
	        strncpy(name,newName,sizeof(name)-1);
	        name[sizeof(name)-1]='\0';
	        cost=newCost;
	        timeRequired=newTime;
	    }
	    virtual ~Attraction() {}
};
class Transportation {
	private:
	    TransportType type;
	    char from[50],to[50];
	    double cost;
	    int duration;
	public:
	    Transportation() {
	        type=OTHER;
	        strcpy(from,"N/A");
	        strcpy(to,"N/A");
	        cost=0;
	        duration=0;
	    }
	    Transportation(TransportType t,const char* f,const char* t_dest,double c,int d) {
	        type=t;
	        strncpy(from,f,sizeof(from)-1);
	        from[sizeof(from)-1]='\0';
	        strncpy(to,t_dest,sizeof(to)-1);
	        to[sizeof(to)-1]='\0';
	        cost=c;
	        duration=d;
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
	    double getCost() const { return cost; }
	    int getDuration() const { return duration; }
	    TransportType getType() const { return type; }
	    const char* getFrom() const { return from; }
	    const char* getTo() const { return to; }
};
class Destination {
	private:
	    char name[50];
	    int stayDuration,attractionCount,x,y;
	    Attraction* attractions[MAX_ATTRACTIONS];
	public:
	    Destination() {
	        strcpy(name,"N/A");
	        stayDuration=0;
	        attractionCount=0;
	        for(int i=0;i<MAX_ATTRACTIONS;i++) 
				attractions[i]=NULL;
	    }
	    Destination& operator=(const Destination& other) {
		    if(this!=&other) {
		        strncpy(name,other.name,sizeof(name)-1);
		        name[sizeof(name)-1]='\0';
		        stayDuration=other.stayDuration;
		        for(int i=0;i<attractionCount;++i) {
		            delete attractions[i];
		            attractions[i]=NULL;
		        }
		        attractionCount=other.attractionCount;
		        for(int i=0;i<MAX_ATTRACTIONS;++i) 
		            if(i< attractionCount && other.attractions[i])
		                attractions[i]=new Attraction(*other.attractions[i]);
		            else 
		                attractions[i]=NULL;
		    }
		    return *this;
		}
	    ~Destination() {
	        for(int i=0;i<attractionCount;i++) 
				delete attractions[i];
	    }
	    Attraction* getAttraction(int i) const {
		    if (i>=0 && i<attractionCount) 
				return attractions[i];
		    return NULL;
		}
		void setName(const char* n) {
	        strncpy(name,n,sizeof(name)-1);
	        name[sizeof(name)-1]='\0';
	    }
	    void setStayDuration(int days) {
	        stayDuration=days;
		}
	    void addAttraction(Attraction* attraction) {
	        if(attractionCount < MAX_ATTRACTIONS)
	            attractions[attractionCount++]=attraction;
	        else
	            cout << "Maximum attractions reached for this destination.";
	    }
	    double calculateTotalCost() {
	        double totalCost=0;
	        for(int i=0;i<attractionCount;i++)
	            totalCost+=attractions[i]->getCost();
	        return totalCost;
	    }
	    void displayDestination() {
	    	x=10;
			y=*posy+1;
	        gotoxy(x,y+=2);
	        cout<<"Destination : "<<name;
	        gotoxy(x,++y);
	        cout<<"Duration of Stay : "<<stayDuration<<" days";
	        gotoxy(x,y+=2);
	        cout<<"Attractions :";
	        if(attractionCount>0)     
	            for(int i=0;i<attractionCount;i++) {
	            	Attraction* a=attractions[i];
	            	if(a) {
				        gotoxy(x+5,++y);
				        cout<<i+1<<". Attraction : "<< a->getName();
				        gotoxy(x+12,++y);
				        cout<<"Cost : Rs "<< a->getCost();
				        gotoxy(x+12,++y);
				        cout<<"Time Required : " <<a->getTimeRequired()<<" hrs";
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
    int stayDuration,attractionCount;
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
	    int time,x,y;
	    TransportType transportType;
	public:
	    Route() {
	        strcpy(from,"");
	        strcpy(to,"");
	        cost=0;
	        time=0;
	        transportType=OTHER;
	    }
	    Route(const char* f,const char* t,double c,int tm,TransportType type) {
	        strncpy(from,f,sizeof(from)-1);
	        from[sizeof(from)-1]='\0';
	        strncpy(to,t,sizeof(to)-1);
	        to[sizeof(to)-1]='\0';
	        cost=c;
	        time=tm;
	        transportType=type;
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
	    	x=10;
			y=*posy+1;
	        gotoxy(x,y+=2);
	        cout<<" Route : "<<from<<" -> "<<to;
	        gotoxy(x+3,++y);
	        cout<<"\tTransport Type : "<<getTypeString();
	        gotoxy(x+3,++y);
	        cout<<"\tCost : Rs "<<cost;
	        gotoxy(x+3,++y);
	        cout<<"\tTravel Time : "<<time/60<<" hrs "<<time%60<<" min";
			gotoxy(x,++y);
			dash();
			(*posy)=y;
		}
};
struct RouteGraphData {
    int locationCount,routeCount,timeMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    char locations[MAX_DESTINATIONS][50];
    Route routes[MAX_DESTINATIONS*MAX_DESTINATIONS];
    double costMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
    TransportType transportMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
};
class RouteGraph {
	private:
	    double costMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
	    int timeMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS],locationCount,routeCount,x,y;
	    TransportType transportMatrix[MAX_DESTINATIONS][MAX_DESTINATIONS];
	    char locations[MAX_DESTINATIONS][50];
	    Route routes[MAX_DESTINATIONS * MAX_DESTINATIONS];
	public:
	    RouteGraph() {
	        locationCount=0;
	        routeCount=0;
	        for(int i=0;i<MAX_DESTINATIONS;i++) {
	            strcpy(locations[i],"");
	            for(int j=0;j<MAX_DESTINATIONS;j++) {
	                if(i==j) {
	                    costMatrix[i][j]=0;
	                    timeMatrix[i][j]=0;
	                } else {
	                    costMatrix[i][j]=INF;
	                    timeMatrix[i][j]=INF;
	                }
	                transportMatrix[i][j]= OTHER;
	            }
	        }
	    }
	    int addLocation(const char* name) {
	        for(int i = 0; i < locationCount; i++)
	            if(strcmp(locations[i], name) == 0)
	                return i;
	        if(locationCount<MAX_DESTINATIONS) {
	            strncpy(locations[locationCount],name,49);
	            locations[locationCount][49]='\0';
	            return locationCount++;
	        } else {
	            cout<<"Maximum destinations reached.";
	            return -1;
	        }
	    }
	    void addRoute(const char* from,const char* to,double cost,int time,TransportType type) {
	        int fromIndex=addLocation(from),toIndex=addLocation(to);
	        if(fromIndex!=-1 && toIndex!=-1) {
	            costMatrix[fromIndex][toIndex]=cost;
	            timeMatrix[fromIndex][toIndex]=time;
	            transportMatrix[fromIndex][toIndex]=type;
	            if(routeCount<MAX_DESTINATIONS*MAX_DESTINATIONS)
	                routes[routeCount++]=Route(from,to,cost,time,type);
	        }
	    }
	    void displayLocations() {
	    	x=*posx;
			y=*posy;
	    	gotoxy(x,y+=3);
	        if(locationCount==0)
	            cout<<"No locations added yet.";
	        else
	        {
	        	cout<<"Available Locations :";
	        	for(int i=0;i<locationCount;i++) 
	        	{
	        		gotoxy(x+5,++y);
	        		cout<<i+1<<". "<<locations[i];
				}	
			}
			(*posx)=x;
			(*posy)=y+=1;
	    }
	    void displayRoutes() {
	    	x=*posx;
			y=*posy;
	        if(routeCount==0) {
	        	gotoxy(x+=5,y+=3);
	            cout<<"No routes added yet.";
	        }
	        else
	        	for(int i=0;i<routeCount;i++) {
	            	cout<<"\t"<<i+1<<". ";
	            	routes[i].displayRoute();
				}
			(*posy)+=3;
	    }
	    int findLocationIndex(const char* name) {
	        for(int i=0;i<locationCount;i++)
	            if(strcmp(locations[i],name)==0) 
	                return i;
	        return -1;
	    }
	    void findShortestPath(const char* start,const char* end,bool useCost) {
	        int startIndex=findLocationIndex(start),endIndex=findLocationIndex(end);
	        drawHeader("Budget Analysis : Least Expensive Path",x=45,y=0);
	        if(startIndex==-1 || endIndex==-1) 
	        {
	        	gotoxy(x=44,y+=3);
	        	cout<<"One or both locations not found.";
	        	(*posy)=y;
			}
			else
			{
				double weight[MAX_DESTINATIONS][MAX_DESTINATIONS];
		        for(int i=0;i<locationCount;i++)
		            for(int j=0;j<locationCount;j++)
		                if(useCost)
		                    weight[i][j]=costMatrix[i][j];
		                else
		                    weight[i][j]=(double)timeMatrix[i][j];
		        double dist[MAX_DESTINATIONS];
		        bool visited[MAX_DESTINATIONS];
		        int prev[MAX_DESTINATIONS];
		        for(int i=0;i<locationCount;i++) {
		            dist[i]=INF;
		            visited[i]=false;
		            prev[i]=-1;
		        }
		        dist[startIndex]=0;
	            for(int count=0;count<locationCount-1; count++) {
		            double min=INF;
		            int minIndex=-1;
		            for(int v = 0; v < locationCount; v++)
		                if(!visited[v] && dist[v]<=min) {
		                    min=dist[v];
		                    minIndex=v;
		                }
		            visited[minIndex]=true;
		            for(int v=0;v<locationCount;v++)
		                if(!visited[v] && weight[minIndex][v]!=INF && dist[minIndex]!=INF && dist[minIndex]+weight[minIndex][v]<dist[v]) {
		                    dist[v]=dist[minIndex]+weight[minIndex][v];
		                    prev[v]=minIndex;
		                }
		    	}
		        if(dist[endIndex]==INF)
		        	cout<<"No path exists between "<<start<<" and "<<end;
		        else
		    	{
			        cout<<"\tLeast Expensive Path : "<<endl;
			        int path[MAX_DESTINATIONS];
			        int pathLen=0;
			        for(int at=endIndex;at!=-1;at=prev[at])
			            path[pathLen++]=at;
			        cout<<"\t\t";
			        for(int i=pathLen-1;i>=0;i--) {
			            cout<<locations[path[i]];
			            if(i>0)cout<<" -> ";
			        }
			        cout<<endl;
			        if(useCost)
			            cout<<"\t\tTotal Cost : Rs "<<dist[endIndex]<<endl;
			        else {
			            int hours=(int)dist[endIndex]/60;
			            int mins=(int)dist[endIndex]%60;
			            cout<<"\t\tTotal Time : "<< hours<<" hrs "<<mins<<" min"<<endl;
			        }
			        y=6;
					cout<<endl<<"\tRoute Details :"<<endl;
			        for(int i=pathLen-1;i>0;i--) {
			            int from=path[i];
			            int to=path[i-1];
			            cout<<"\t\t"<<locations[from]<<" -> " << locations[to]<<endl;
			            cout<<"\t\tTransport Type : "<<getTransportTypeName(transportMatrix[from][to])<<endl;
			            cout<<"\t\tCost : Rs "<<costMatrix[from][to]<<endl;
			            cout<<"\t\tTime : "<<timeMatrix[from][to]/60<<" hrs "<<timeMatrix[from][to]%60<<" min"<<endl;
			            if(i>1) cout<<"\t    ----------"<<endl;
			            y+=6;
			        }
			        dash();
				}
				(*posy)=y+=3;
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
	        if(index>=0 && index<locationCount)
	            return locations[index];
	        return "";
	    }
	    void saveToFile(const char* filename) {
	    	int x=*posx,y=*posy;
		    RouteGraphData data;
		    data.locationCount=locationCount;
		    data.routeCount=routeCount;
		    for(int i=0;i<locationCount;++i) {
		        strcpy(data.locations[i],locations[i]);
		        for(int j=0;j<locationCount;++j) {
		            data.costMatrix[i][j]=costMatrix[i][j];
		            data.timeMatrix[i][j]=timeMatrix[i][j];
		            data.transportMatrix[i][j]=transportMatrix[i][j];
		        }
		    }
		    for(int i=0;i<routeCount;++i)
		        data.routes[i]=routes[i];
		    gotoxy(x-5,y+=2);
		    if(::saveToFile(data,filename))
		        cout<<"Routes saved to file "<<filename<<" successfully";
		    else
		        cout<<"Failed to save route graph.";
		}
	    void loadFromFile(const char* filename) {
	    	(*posy)-=3;
			int x=30,y=*posy;
		    RouteGraphData data;
		    (*posx)=x;
		    if(::loadFromFile(data,filename)) {
			    locationCount=data.locationCount;
			    routeCount=data.routeCount;
			    for (int i=0;i<locationCount;++i) {
			        strcpy(locations[i],data.locations[i]);
			        for (int j=0;j<locationCount;++j) {
			            costMatrix[i][j]=data.costMatrix[i][j];
			            timeMatrix[i][j]=data.timeMatrix[i][j];
			            transportMatrix[i][j]=data.transportMatrix[i][j];
			        }
			    }
			    for(int i=0;i<routeCount;++i)
			        routes[i]=data.routes[i];
			    cout<<"Routes loaded successfully from "<<filename;
			}
		}
	    void dfsAllPaths(int current,int end,bool visited[],int path[],int pathIndex,double currentCost,int currentTime) {
	    	x=10;
			visited[current]=true;
	    	path[pathIndex]=current;
	    	pathIndex++;
	    	if(current==end) {
	    		(*posy)+=1;
	        	y=*posy;
	    		gotoxy(x,++y);
	        	cout<<"Path : ";
	        	for(int i=0;i<pathIndex;i++) {
	            	cout<<locations[path[i]];
	            	if(i<pathIndex-1) 
						cout<<" -> ";
	        	}
	        	gotoxy(x+3,++y);
	        	cout<<"Total Cost : Rs "<<currentCost;
	        	gotoxy(x+3,++y);
	        	cout<<"Total Time : "<<currentTime/60<< " hrs "<<currentTime%60<<" min";
				gotoxy(x+3,++y);
	        	cout<<"Routes : ";
	        	gotoxy(x,++y);
	        	cout<<"+------------------+------------------+----------+-------------+-----------+";
	        	gotoxy(x,++y);
	        	cout<<"| From             | To               | Cost     | Transport   | Time      |";
	        	gotoxy(x,++y);
	        	cout<<"+------------------+------------------+----------+-------------+-----------+";
	        	for(int i=0;i<pathIndex-1;i++) {
	            	int u=path[i],v=path[i + 1];
	            	gotoxy(x,++y);
	            	cout<<"| "<<left<<setw(16)<<locations[u]<<" | "<<left<<setw(16)<<locations[v]<<" | $"<<right<<setw(7)<<costMatrix[u][v]<< " | "<<left<<setw(11)<<getTransportTypeName(transportMatrix[u][v])<<" | "<<right<<setw(2)<<timeMatrix[u][v]/60<<" h "<<right<<setw(2)<<timeMatrix[u][v]%60<<" m |";
	        	}
		        gotoxy(x,++y);
		        cout<<"+------------------+------------------+----------+-------------+-----------+";
		    	(*posy)=++y;
	    	} 
			else {
		        for(int i=0;i<locationCount;i++)
		            if(!visited[i] && costMatrix[current][i]!=INF)
		                dfsAllPaths(i,end,visited,path,pathIndex,currentCost+costMatrix[current][i],currentTime+timeMatrix[current][i]);
	    	}
		    visited[current]=false;
		    pathIndex--;
		}
		void findAllRoutesWithCost(const char* start,const char* end) {
	    	int startIndex=findLocationIndex(start),endIndex=findLocationIndex(end);
	        drawHeader("Budget Analysis : All Paths",x=45,y=0);
	    	if (startIndex == -1 || endIndex == -1) {
	    		gotoxy(x,y+=2);
	        	cout<<"Invalid locations.";
	    	}
	    	else
	    	{
	    		bool visited[MAX_DESTINATIONS]={false};
	    		int path[MAX_DESTINATIONS],pathIndex=0;
	    		gotoxy(10,y+=3);
	    		cout<<"All Paths from "<<start<<" to "<<end<<" :";
	    		(*posy)=++y;
	    		dfsAllPaths(startIndex,endIndex,visited,path,pathIndex,0.0,0);
			}
			gotoxy(x,*posy);
				dash();
			(*posy)+=3;
		}
};
class TravellerProfile {
	private:
	    char name[50];
	    int age,plannedDays,x,y;
	    double budget;
	public:
	    TravellerProfile() {
	        name[0]='\0';
	        age=0;
	        budget=0;
	        plannedDays=0;
	    }
	    void setProfile() {
	        drawHeader("Traveller Profile : Setup",x=45,y=4);
	        gotoxy(x=44,y+=3);
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
	    	return loadFromFile(*this,"traveller_profile.txt");
		}
	    void viewProfile() {
	        drawHeader("Traveller Profile : View",x=45,y=4);
	        (*posx)=x-=10;
		    (*posy)=y+=3;
		    if(loadProfile()) {
				gotoxy(x=44,y-=3);
		        cout<<"Name : "<<name;
		        gotoxy(x,++y);
		        cout<<"Age : "<<age;
		        gotoxy(x,++y);
		        cout<<"Budget : Rs "<<budget;
		        gotoxy(x,++y);
		        cout<<"Planned Days : "<<plannedDays;
		    } else {
		        gotoxy(x,y+=3);
		        cout<<"No profile found. Please set up a profile first.";
		    }
		    (*posx)=44;
			(*posy)=y+3;
		}
	    double getBudget() const { return budget; }
	    int getPlannedDays() const { return plannedDays; }
	    const char* getName() const { return name; }
};
class TripPlanner {
	private:
	    Destination destinations[MAX_DESTINATIONS];
	    int destinationCount,x,y;
	    RouteGraph routeGraph;
	    TravellerProfile traveller;
	public:
	    TripPlanner() {
	        destinationCount = 0;
	    }
	    void saveDestinations() {
	    	char filename[100];
	        drawHeader("Destinations : Save",x=45,y=4);
	        gotoxy(x=35,y+=3);
			cout<<"Enter filename to save destinations : ";
			cin>>filename;
	    	DestinationData dd;
	    	dd.count=destinationCount;
		    for (int i=0;i<destinationCount;++i) {
		        Destination& d=destinations[i];
		        DestinationRawData& raw=dd.data[i];
		        strcpy(raw.name,d.getName());
		        raw.stayDuration=d.getStayDuration();
		        raw.attractionCount=d.getAttractionCount();
		        for(int j=0;j<raw.attractionCount;++j) {
		            Attraction* a=d.getAttraction(j);
		            if(a) {
		                strcpy(raw.attractions[j].name,a->getName());
		                raw.attractions[j].cost=a->getCost();
		                raw.attractions[j].timeRequired=a->getTimeRequired();
		            }
		        }
		    }
			gotoxy(x,y+=2);
		    if(::saveToFile(dd,filename))
		        cout<<"Destinations saved to "<<filename<<" successfully!";
		    else
		        cout<<"Failed to save destinations.";
		    (*posy)=y+=3;
		}
	    void loadDestinations() {
	    	char filename[100];
	        drawHeader("Destinations : Load",x=45,y=4);
	        gotoxy(x=30,y+=3);
			cout<<"Enter filename to load destinations from : ";
			cin>>filename;
	        DestinationData dd;
	        (*posx)=x;
			(*posy)=y+=2;
		    if (!::loadFromFile(dd,filename))
		    {
		    	gotoxy(x,y+=2);
		    	cout<<"Failed to load destinations.";
			} 
			else
			{
				destinationCount=dd.count;
			    for (int i=0;i<destinationCount;++i) {
			        DestinationRawData& raw=dd.data[i];
			        Destination d;
			        d.setName(raw.name);
			        d.setStayDuration(raw.stayDuration);
			        for (int j=0;j<raw.attractionCount;++j) {
			            AttractionData& a=raw.attractions[j];
			            Attraction* attraction=new Attraction(a.name, a.cost, a.timeRequired);
			            d.addAttraction(attraction);
			        }
			        destinations[i]=d;
			        routeGraph.addLocation(d.getName());
			    }
				gotoxy(x,y);
			    cout<<"Destinations loaded successfully from "<<filename;
			}
			(*posx)=x+=10;
	    	(*posy)=y+=3;
		}
	    void addDestination(const Destination& dest) {
	        if(destinationCount<MAX_DESTINATIONS)
	            destinations[destinationCount++]=dest;
	        else
	            cout<<"Maximum destinations reached.";
	    }
	    void createProfile() {
	        traveller.setProfile();
	    }
	    void viewProfile() {
	        traveller.viewProfile();
	    }
	    void addRoute() {
	        char from[50],to[50];
	        double cost;
	        int time,transportChoice;
	        drawHeader("Routes : Add",x=45,y=0);
	        (*posx)=x-3;
	        (*posy)=y;
	        routeGraph.displayLocations();
	        x=(*posx);
	        y=(*posy);
	        gotoxy(x,++y);
	        cout<<"Enter new route details :";
	        gotoxy(x,++y);
	        cout<<"Enter source name : ";
	        cin.ignore();
	        cin.getline(from,sizeof(from));
	        gotoxy(x,++y);
	        cout<<"Enter destination name : ";
	        cin.getline(to,sizeof(to));
	        gotoxy(x,y+=2);
	        cout<<"Transportation Type :";
	        gotoxy(x,++y);
	        cout<<"1. Air";
	        gotoxy(x,++y);
	        cout<<"2. Bus";
	        gotoxy(x,++y);
	        cout<<"3. Car";
	        gotoxy(x,++y);
	        cout<<"4. Other";
	        gotoxy(x,++y);
	        cout<<"Enter choice : ";
			cin>>transportChoice;
			gotoxy(x,y+=2);
			cout<<"Cost (Rs) : ";
	        cin>>cost;
	        gotoxy(x,++y);
	        cout<<"Time (in minutes) : ";
	        cin>>time;
	        TransportType type;
	        switch(transportChoice) {
	            case 1: type=AIR; break;
	            case 2: type=BUS; break;
	            case 3: type=CAR; break;
	         	case 4: type=OTHER; break;
	            default: type=OTHER;
	        }
	        routeGraph.addRoute(from,to,cost,time,type);
	        gotoxy(x,y+=2);
	        cout<<"Route added successfully.";
	        (*posy)=y+=3;
	    }
	    void displayRoutes() {
	        drawHeader("Routes : View",x=35,y=0);
	        (*posy)=y;
	        routeGraph.displayRoutes();
	    }
	    void findBestRoute() {
	        char from[50],to[50];
	        int preference;
	        drawHeader("Budget Analysis : For Best Path",x=45,y=0);
	        (*posy)=y;
	        routeGraph.displayLocations();
	        y=*posy;
			gotoxy(x,++y);
			cout<<"Enter source : ";
	        cin.ignore();
	        cin.getline(from,sizeof(from));
	        gotoxy(x,++y);
	        cout<<"Enter destination : ";
	        cin.getline(to,sizeof(to));
	        gotoxy(x,y+=2);
	        cout<<"Optimization preference :";
	        gotoxy(x,++y);
	        cout<<"1. Optimize for cost";
	        gotoxy(x,++y);
	        cout<<"2. Optimize for time";
	        gotoxy(x,++y);
	        cout<<"Enter your choice : ";
	        cin>>preference;
	        bool optimizeForCost=(preference==1);
	        routeGraph.findShortestPath(from,to,optimizeForCost);
			(*posy)+=3;    
		}
	    void saveRoutes() {
	    	char filename[100];
	        drawHeader("Routes : Save",x=45,y=4);
	        gotoxy(x=35,y+=3);
			cout<<"Enter filename to save routes : ";
			cin>>filename;
			(*posx)=x+5;
			(*posy)=y;
	    	routeGraph.saveToFile(filename);
			(*posx)=x;
			(*posy)=y+5;
	    }
	  	void loadRoutes() {
	  		char filename[100];
	        drawHeader("Routes : Load",x=45,y=4);
	        gotoxy(x=30,y+=3);
			cout<<"Enter filename to load routes from : ";
			cin>>filename;
	    	routeGraph.loadFromFile(filename);
			(*posy)+=3;
		} 
	    void budgetAnalysis() {
	        drawHeader("Budget Analysis : All Paths",x=45,y=4);
	        double totalBudget=traveller.getBudget();
	        if(totalBudget==0)
	        {
	        	gotoxy(x=44,y+=3);
	        	cout<<"Please set up your traveller profile first.";
			}
	        else
	        {
	        	double totalCost=0;
		        double attractionCost=0;
		        for(int i=0;i<destinationCount;i++) {
		            double destCost=destinations[i].calculateTotalCost();
		            attractionCost+=destCost;
		            totalCost+=destCost;
		        }
		        cout<<"\tTotal Budget : Rs "<<totalBudget<<endl;
		        cout<<"\tEstimated Total Cost : Rs "<<totalCost<<endl;
		        if(totalCost>totalBudget)
		            cout<<"\tBudget Deficit : Rs "<<totalCost-totalBudget<<endl<<"\tWarning: Your current plan exceeds your budget."<<endl;
		        else
		            cout<<"\tBudget Surplus: Rs "<<totalBudget-totalCost<<endl<<"\tGood news! Your plan is within budget."<<endl;
		        cout<<endl<<"\tCost Breakdown for All Paths :"<<endl;
		        cout<<"\t\tTotal cost for visiting all attractions : Rs "<<attractionCost<<endl;
		        char start[50],end[50];
		        cout<<endl<<"\t\tEnter source : ";
		        cin.ignore();
		        cin.getline(start, sizeof(start));
		        cout<<"\t\tEnter destination : ";
		        cin.getline(end, sizeof(end));
		        routeGraph.findAllRoutesWithCost(start,end);
			}
	    }
	    void addDestinationDetails() {
	        char name[50];
	        int days;
	        drawHeader("Destinations : Add",x=45,y=4);
	        gotoxy(x=44,y+=3);
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
	        drawHeader("Destinations : View",x=45,y=0);
	        if(destinationCount==0) {
	        	gotoxy(x=44,y+=3);
	        	(*posy)=y;
	        	cout<<"No destinations added yet!";
			}   
	        else {
	        	(*posy)=y;
	        	for(int i=0;i<destinationCount;i++)
		        	destinations[i].displayDestination();
			}
	        (*posy)+=3; 
	    }
};
int main() {
    TripPlanner planner;
    int choice1,choice2,x,y;
    bool exit=false;
    char response;
    posx=&x;
    posy=&y;
    while(!exit) {
        drawHeader("TOUR PLANNER MENU",x=45,y=4);
        gotoxy(x=44,y+=3);
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
            	drawHeader("Traveller Profile : Options",x=45,y=4);
		        gotoxy(x=44,y+=3);
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
            	drawHeader("Destinations : Options",x=45,y=4);
		        gotoxy(x=44,y+=3);
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
            	drawHeader("Routes : Options",x=45,y=4);
		        gotoxy(x=44,y+=3);
		        cout<<"1. Add Routes";
		        gotoxy(x,++y);
		        cout<<"2. View Routes";
		        gotoxy(x,++y);
		        cout<<"3. Save Routes";
		        gotoxy(x,++y);
		        cout<<"4. Load Routes";
		        gotoxy(x,y+=2);
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
            	drawHeader("Budget Analysis : Options",x=45,y=4);
		        gotoxy(x=44,y+=3);
		        cout<<"1. For Best Path";
		        gotoxy(x,++y);
		        cout<<"2. For All Paths";
		        gotoxy(x,y+=2);
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
			gotoxy(*posx,*posy);
			cout<<"Return to Main Menu? [Y/N] : ";
			cin>>response;
            if(toupper(response)!='Y')
                exit=true;
        }
    }
    drawHeader("Thank you for using Tour Planner",x=40,y=4);
    return 0;
}
