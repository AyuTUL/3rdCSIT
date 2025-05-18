#include<iostream>
#define MAX 100
using namespace std;
class Queue 
{
    private:
        int a[MAX],rear,front;
    public:
        Queue()
        {
            rear=front=-1;
        }
        bool isEmpty()
        {
            return(front==-1 && rear==-1);
        }
        void enqueue(int item)
        {
            if(rear==MAX-1)
                cout<<endl<<"Queue overflow"<<endl;
            else
            {
                if(isEmpty())
                    rear=front=0;
                else
                    rear++;
                a[rear]=item;
            }
        }
        int dequeue()
        {
            if(isEmpty())
            {
                cout<<endl<<"Queue underflow"<<endl;
                return -1;
            }
            else
            {
                int item=a[front];
                if(rear==front)
                    rear=front=-1;
                else
                    front++;
                return item;    
            }           
        }
};
void BFS(int g[MAX][MAX],int src,int V,char v[]) 
{
    bool visited[MAX]={false};
    Queue q;
    visited[src]=true;
    q.enqueue(src);
    cout<<endl<<"BFS traversal : ";
    while(!q.isEmpty()) 
    {
        int u=q.dequeue();
        cout<<v[u]<<" ";
        for(int i=0;i<V;i++) 
            if(g[u][i]==1 && !visited[i]) 
            {
                visited[i]=true;
                q.enqueue(i);
            }
    }
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
    BFS(g,srcIndex,V,v);
    return 0;
}