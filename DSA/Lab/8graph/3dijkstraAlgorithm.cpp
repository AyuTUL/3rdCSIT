#include<iostream>
#include<iomanip>
#define MAX 100  
#define INF 999999
using namespace std;
int minDistance(int d[],bool visited[],int V) 
{
    int min=INF,minIndex=-1;
    for(int v=0;v<V;v++)
        if(!visited[v] && d[v]<=min) 
        {
        	min=d[v];
			minIndex=v;
		}      
    return(minIndex);
}
char source;
void print(int d[],int V,char v[]) 
{
    cout<<endl<<"+----------+-----------------------------+"<<endl;
    cout<<"|  Vertex  |  Distance from Source ( "<<source<<" ) |";
    cout<<endl<<"+----------+-----------------------------+"<<endl;
    for(int i=0;i<V;i++) 
        cout<<"|"<<setw(5)<<v[i]<<setw(6)<<"|"<<setw(15)<<d[i]<<setw(15)<<"|"<<endl;
    cout<<"+----------+-----------------------------+"<<endl;
}
void dijkstra(int g[MAX][MAX],int src,int V,char v[]) 
{
    int d[MAX]; 
    bool visited[MAX];
    for(int i=0;i<V;i++)
    {
    	d[i]=INF;
		visited[i]=false;
	} 
    d[src]=0;
    for(int i=0;i<V-1;i++) 
	{
        int u=minDistance(d,visited,V);
        visited[u]=true;
        for(int v=0;v<V;v++)
            if(!visited[v] && g[u][v] && d[u]!=INF && d[u]+g[u][v]<d[v]) 
                d[v]=d[u]+g[u][v];
    }
    print(d,V,v);
}
int main() 
{
    int V,g[MAX][MAX]={0},srcIndex=-1;
    char v[MAX]; 
    cout<<"Enter no. of vertices : ";
    cin>>V;
    cout<<"Enter "<<V<<" vertices : ";
    for(int i=0;i<V;i++)
        cin>>v[i];
    cout<<endl<<"Enter adjacency matrix :"<<endl<<"  ";
    for(int i =0;i<V;i++)
        cout<<" "<<v[i];
    cout<<endl;
	for(int i=0;i<V;i++)
    {
    	cout<<" "<<v[i]<<" ";
    	for(int j=0;j<V;j++)
		   cin>>g[i][j]; 
	}
    cout<<endl<<"Enter source vertex : ";
    cin>>source;
    for(int i=0;i<V;i++) 
        if(v[i]==source) 
        {
            srcIndex=i;
            break;
        }
    if(srcIndex==-1) 
    {
        cout<<"Invalid source vertex"<<endl;
        return 1;
    }
    dijkstra(g,srcIndex,V,v);
    return 0;
}