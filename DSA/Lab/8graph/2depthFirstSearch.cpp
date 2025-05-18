#include<iostream>
#define MAX 100
using namespace std;
void DFS(int g[MAX][MAX],int u,bool visited[MAX],int V,char v[]) {
    visited[u]=true;
    cout<<v[u]<<" ";
    for(int i=0;i<V;i++)
        if(g[u][i]==1 && !visited[i])
            DFS(g,i,visited,V,v);
}
int main() 
{
    int V,g[MAX][MAX]={0},srcIndex=-1;
    char v[MAX],source; 
    cout<<"Enter no. of vertices : ";
    cin>>V;
    cout<<"Enter "<<V<<" vertices : ";
    for(int i=0;i<V;i++)
        cin>>v[i];
    cout<<endl<<"Enter adjacency matrix :"<<endl<<"  ";
    for(int i=0;i<V;i++)
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
    bool visited[MAX]={false};
    cout<<endl<<"DFS traversal : ";
    DFS(g,srcIndex,visited,V,v);
    return 0;
}