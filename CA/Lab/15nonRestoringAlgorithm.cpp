#include<iostream>
#include<bitset>
#include<iomanip>
#include<cmath>
using namespace std;

const char *HR = "+----+---------+--------+---------------------+\n";

void row(int n, int A, int Q, int abit, int qbit, const string &comment) {
    cout << "| " << setw(2) << n << " | "
         << bitset<16>(A).to_string().substr(16 - abit, abit) << " | "
         << bitset<16>(Q).to_string().substr(16 - qbit, qbit) << " | "
         << left << setw(20) << comment << "|\n" << right;
}

int nonRestoringDivision(int dividend, int divisor, int &remainder_out, int qbit) {
    if (divisor == 0) {
        cout << "Division by zero error!\n";
        remainder_out = 0;
        return 0;
    }

    int abit = qbit + 1;
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    int rem_sign = (dividend < 0) ? -1 : 1;

    unsigned int u_dividend = abs(dividend);
    unsigned int u_divisor = abs(divisor);

    int A = 0;
    int M = u_divisor;
    unsigned int Q = u_dividend;

    cout << "\nNon-Restoring Division Tracing Table:\n";
    cout << HR;
    cout << "| n  |    A    |   Q    | Action/Comment      |\n";
    cout << HR;
    row(qbit, A, Q, abit, qbit, "Initialization");

    for (int i = qbit - 1; i >= 0; i--) {
        A = ((A << 1) | ((Q >> (qbit - 1)) & 1)) & ((1 << abit) - 1);
        Q = (Q << 1) & ((1 << qbit) - 1);
        row(i, A, Q, abit, qbit, "Shift Left AQ");

        A = (A - M) & ((1 << abit) - 1);
        row(i, A, Q, abit, qbit, "A = A - M");

        if (A & (1 << (abit - 1))) {
            Q &= ~1;
            A = (A + M) & ((1 << abit) - 1);
            row(i, A, Q, abit, qbit, "A<0 => A=A+M,Q[0]=0");
        } else {
            Q |= 1;
            row(i, A, Q, abit, qbit, "A>=0 => Q[0]=1");
        }
    }

    cout << HR;
    remainder_out = rem_sign * A;
    return sign * (int)Q;
}

int main() {
    int dividend, divisor;
    cout << "Enter dividend (Q) : ";
    cin >> dividend;
    cout << "Enter divisor (M) : ";
    cin >> divisor;

    int remainder;
    int maxVal = max(abs(dividend), abs(divisor));
    int qbit = (int)log2(maxVal + 1) + 1;
    if (dividend < 0 || divisor < 0) qbit++;
    if (qbit > 8) {
        cout << "Bit size exceeds 8. Capping to 8 bits.\n";
        qbit = 8;
    }

    int quotient = nonRestoringDivision(dividend, divisor, remainder, qbit);
    cout << endl << "Quotient  = " << quotient << endl;
    cout << "Remainder = " << remainder << endl;
    return 0;
}
