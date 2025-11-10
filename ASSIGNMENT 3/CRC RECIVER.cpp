#include <iostream>
#include <string>
using namespace std;
string xorOperation(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);
    int n = dividend.length();

    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xorOperation(divisor, tmp) + dividend[pick];
        else
            tmp = xorOperation(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }
    if (tmp[0] == '1')
        tmp = xorOperation(divisor, tmp);
    else
        tmp = xorOperation(string(pick, '0'), tmp);

    return tmp;
}
int main() {
    string data = "10011101";
    string divisor = "1001"; // x^3 + 1

    // Append zeros equal to degree of generator
    int m = divisor.length() - 1;
    string appended_data = data + string(m, '0');

    // Step 1: Sender side CRC calculation
    string remainder = mod2div(appended_data, divisor);
    string transmitted = data + remainder;

    cout << "--- Sender Side ---\n";
    cout << "Data bits: " << data << endl;
    cout << "Generator polynomial: " << divisor << endl;
    cout << "Remainder: " << remainder << endl;
    cout << "Transmitted Frame: " << transmitted << endl;

    // Step 2: Simulate bit error (3rd bit inverted)
    string received = transmitted;
    received[2] = (received[2] == '0') ? '1' : '0'; // flip 3rd bit

    cout << "\n--- Receiver Side ---\n";
    cout << "Received Frame: " << received << endl;

    // Receiver performs division again
    string syndrome = mod2div(received, divisor);

    cout << "Syndrome (Remainder after division): " << syndrome << endl;

    if (syndrome.find('1') != string::npos)
        cout << "Error detected in transmission!" << endl;
    else
        cout << "No error detected." << endl;

    return 0;
}

