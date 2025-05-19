#include <iostream>
#include <bitset>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

const char *HR = "+----+--------+-------+----+------------------+\n";

// Format and print a row
void row(int n, int A, int Q, int Q_1, int bits, const string &comment) {
    cout << "| "
         << setw(2) << n << " | "
         << bitset<8>(A).to_string().substr(8 - bits, bits) << "  | "
         << bitset<8>(Q).to_string().substr(8 - bits, bits) << " | "
         << Q_1 << "  | "
         << left << setw(16) << comment.substr(0, 16) << "|\n" << right;
}

// Arithmetic right shift on A, Q, and Q-1
void ars(int &A, int &Q, int &Q_1, int bits) {
    int Q0 = Q & 1;
    int sign = A & (1 << (bits - 1));

    Q >>= 1;
    if (A & 1)
        Q |= (1 << (bits - 1));

    A >>= 1;
    if (sign)
        A |= (1 << (bits - 1));

    Q_1 = Q0;

    // Mask to keep A and Q within bits
    A &= (1 << bits) - 1;
    Q &= (1 << bits) - 1;
}

// Convert signed integer to two's complement within `bits`
int toTwosComplement(int num, int bits) {
    if (num < 0)
        return ((1 << bits) + num);
    return num;
}

// Convert from two's complement back to signed
int fromTwosComplement(int num, int bits) {
    if (num & (1 << (bits - 1)))
        return num - (1 << bits);
    return num;
}

void booth(int M_input, int Q_input, int bits) {
    int A = 0;
    int Q = toTwosComplement(Q_input, bits);
    int M = toTwosComplement(M_input, bits);
    int Q_1 = 0;

    cout << "\nBooth's Multiplication Trace:\n";
    cout << HR
         << "| n  |   A    |   Q   | Q' | Action/Comment  |\n"
         << HR;
    row(bits, A, Q, Q_1, bits, "Initialization");

    for (int n = bits - 1; n >= 0; --n) {
        int Q0 = Q & 1;

        if (Q0 == 1 && Q_1 == 0) {
            A = (A + toTwosComplement(-M_input, bits)) & ((1 << bits) - 1);
            row(n, A, Q, Q_1, bits, "A = A - M");
        } else if (Q0 == 0 && Q_1 == 1) {
            A = (A + M) & ((1 << bits) - 1);
            row(n, A, Q, Q_1, bits, "A = A + M");
        }

        ars(A, Q, Q_1, bits);
        row(n, A, Q, Q_1, bits, "ARS  AQ Q'");
    }

    cout << HR;

    int result = ((A << bits) | Q) & ((1 << (2 * bits)) - 1);
    int signedResult = fromTwosComplement(result, 2 * bits);

    cout << "Result (AQ) = " << bitset<16>(result).to_string().substr(16 - 2 * bits, 2 * bits)
         << " = " << signedResult << "\n";
}
int main() {
    int M, Q, bits;

    cout << "Enter multiplicand (M): ";
    cin >> M;
    cout << "Enter multiplier (Q): ";
    cin >> Q;

    // Automatically determine number of bits based on Q
    int absQ = abs(Q);
    bits = (int)log2(absQ + 1) + 1;
    if (Q < 0) bits += 1;  // for sign bit in two's complement

    if (bits > 8) {
        cout << "Bit size exceeds 8. Capping to 8 bits.\n";
        bits = 8;
    }

    booth(M, Q, bits);

    return 0;
}


