#include<iostream>
#include<bitset>
#include<iomanip>
#include<string>
#include<cmath>
using namespace std;
const char *HR="+----+--------+-------+----+-----------------+\n";

void row(int n,int A,int Q,int Q_1,int bits,const string &comment) {
    cout<<"| "<<setw(2)<<n<<" | "<<bitset<16>(A).to_string().substr(16-bits,bits)<<"  | "<<bitset<16>(Q).to_string().substr(16-bits,bits)<<" | "<<Q_1<<"  | "<<left<<setw(16)<<comment.substr(0,16)<<"|\n"<<right;
}

void ars(int &A,int &Q,int &Q_1,int bits) {
    int Q0=Q&1;
    int signA=A&(1<<(bits-1));
    int signQ=Q&(1<<(bits-1));

    Q>>=1;
    if(A&1)
        Q|=(1<<(bits-1));

    A>>=1;
    if(signA)
        A|=(1<<(bits-1));

    Q_1=Q0;

    A&=((1<<bits)-1);
    Q&=((1<<bits)-1);
}

int toTwosComplement(int num,int bits) {
    if(num<0)
        return ((1<<bits)+num);
    return num;
}

int fromTwosComplement(int num,int bits) {
    if(num&(1<<(bits-1)))
        return num-(1<<bits);
    return num;
}

void booth(int M_input,int Q_input,int bits) {
    int A=0,Q=toTwosComplement(Q_input,bits),M=toTwosComplement(M_input,bits),Q_1=0;
    cout<<endl<<"Booth's Multiplication Tracing Table :"<<endl;
    cout<<HR<<"| n  |   A    |   Q   | Q' | Action/Comment  |"<<endl<<HR;
    row(bits,A,Q,Q_1,bits,"Initialization");
    for(int n=bits-1;n>=0;--n) {
        int Q0=Q&1;
        if(Q0==1&&Q_1==0) {
            A=(A+toTwosComplement(-M_input,bits))&((1<<bits)-1);
            row(n,A,Q,Q_1,bits,"A = A - M");
        }
        else if(Q0==0&&Q_1==1) {
            A=(A+M)&((1<<bits)-1);
            row(n,A,Q,Q_1,bits,"A = A + M");
        }
        ars(A,Q,Q_1,bits);
        row(n,A,Q,Q_1,bits,"ARS  AQ Q'");
    }
    cout<<HR;
    int result=((A<<bits)|Q)&((1<<(2*bits))-1);
    int signedResult=fromTwosComplement(result,2*bits);
    cout<<endl<<"Result (AQ) = "<<bitset<32>(result).to_string().substr(32-2*bits,2*bits)<<" = "<<signedResult<<endl;
}
int main() {
    int M,Q,bits;
    cout<<"Enter multiplicand (M) : ";
    cin>>M;
    cout<<"Enter multiplier (Q) : ";
    cin>>Q;
    int maxVal=max(abs(M),abs(Q));
    bits=(int)log2(maxVal+1)+1;
    if(M<0||Q<0) bits+=1;
    if(bits>8) {
        cout<<"Bit size exceeds 8. Capping to 8 bits.\n";
        bits=8;
    }
    booth(M,Q,bits);
    return 0;
}
