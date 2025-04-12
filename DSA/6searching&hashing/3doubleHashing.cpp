#include<iostream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>
using namespace std;
class DoubleHashing 
{
	private:
	    int *hashTable,size,prime,count; // number of elements
	    int smallerPrime(int n) 
		{
	        for(int i=n-1;i>=2;i--) 
			{
	            bool isPrime=true;
	            for (int j=2;j<=sqrt(i);j++) 
				{
	                if(i%j==0) 
					{
	                    isPrime = false;
	                    break;
	                }
	            }
	            if(isPrime)
	                return i;
	        }
	        return 2;
	    }
	public:
	    DoubleHashing() 
		{
	        cout<<"Enter initial hash table size : ";
	        cin>>size;
			createTable();
	    }
		~DoubleHashing() 
		{
	        delete[] hashTable;
	    }
	    void createTable()
	    {
	    	hashTable=new int[size];
	        for(int i=0;i<size;i++)
	            hashTable[i]=-1;
	        prime=smallerPrime(size);
	        count=0;
		}
	    int h1(int key) 
		{
	        return (key%size);
	    }
	    int h2(int key) 
		{
	        return (prime-(key%prime));
	    }
	    void insert(int key) 
		{
	        if(count==size)
	            cout<<endl<<"Table full. Rehash required.";
	        else
	        {
	        	int index=h1(key),step=h2(key),i=0,oldIndex=index,finalIndex=(index+i*step)%size;
				while(hashTable[finalIndex]!=-1 && i<size)
	            	i++;
		        if(i<size) 
				{
		            if(i>0)
				        cout<<endl<<"Collision occurred at index "<<oldIndex<<endl<<"After collision resolution using double hashing: "<<endl;
					hashTable[finalIndex]=key;
		            count++;
		            cout<<endl<<"Inserted " <<key<< " at index "<<finalIndex<<endl;
		        } 
				else
		            cout<<endl<<"Couldn't insert. Rehash may be needed."<<endl;
			}  
	    }
	    int search(int key) 
		{
	        int index=h1(key),step=h2(key),i=0,finalIndex=(index+i*step)%size;
	        while(hashTable[finalIndex]!=-1 && i<size)
			{
	            int currentIndex=finalIndex;
	            if(hashTable[currentIndex]==key)
	                return currentIndex;
	            i++;
	        }
	        return -1;
	    }
	    void display() 
		{
		    cout<<endl<<"Hash Table :"<<endl;
		    cout<<"\t+------------+------------+"<<endl;
		    cout<<"\t|   Index    |    Key     |"<<endl;
		    cout<<"\t+------------+------------+"<<endl;
		    for(int i=0;i<size;i++) 
			{
		        cout<<"\t|"<<setw(10)<<i<< "  |";
		        if(hashTable[i]!=-1)
		            cout<<setw(10)<<hashTable[i]<<"  |"<<endl;
		        else
		            cout<<setw(10)<<"-"<<"  |"<<endl;
		    }
		    cout<<"\t+------------+------------+"<< endl;
		}
	    void rehash() 
		{
	        int oldSize=size,*oldTable=hashTable;
	        size=2*oldSize;
	        prime=smallerPrime(size);
	        createTable();
	        for(int i=0;i<oldSize;i++)
	            if(oldTable[i]!=-1)
	                insert(oldTable[i]);
	        delete[] oldTable;
	        cout<<endl<<"Rehashing complete.\nNew table size : " <<size<<endl<<"New prime : "<<prime<<endl;
	    }	    
};
int main() 
{
    DoubleHashing ht;
    int ch,key;
    char c;
	do
	{
		cout<<"Hashing Operations :\n1. Insert key\n2. Search key\n3. Display hash table\n4. Rehash\n5. Exit\nEnter your choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<endl<<"Enter key to insert : ";
                cin>>key;
                ht.insert(key);
                break;
			case 2:
				{
					cout<<endl<<"Enter key to be searched : ";
	                cin>>key;
	                int index=ht.search(key);
	                if(index==-1)
	                	cout<<endl<<"Key "<<key<<" not found in hash table"<<endl;
	                else
	                	cout<<endl<<"Key "<<key<<" found at index "<<index<<endl;
					break;	
				}
			case 3:
				ht.display();
				break;
			case 4:
				ht.rehash();
				break;
			case 5:
				cout<<"Exiting program";
				return 0;
			default:
				cout<<endl<<"Invalid input"<<endl;	
		}
		cout<<endl<<"Again? (Y/N) : ";
		cin>>c;
		system("cls");
	}while(c=='y' || c=='Y');
	return 0;
}