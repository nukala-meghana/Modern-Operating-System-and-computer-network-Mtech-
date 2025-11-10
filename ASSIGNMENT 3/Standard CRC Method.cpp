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

    // Last step
    if (tmp[0] == '1')
        tmp = xorOperation(divisor, tmp);
    else
        tmp = xorOperation(string(pick, '0'), tmp);

    return tmp;
}

int main() {
    string data, divisor;

    // ?? Taking input from user
    cout << "Enter the data bits: ";
    cin >> data;

    cout << "Enter the generator polynomial (in binary): ";
    cin >> divisor;

    int m = divisor.length() - 1;

    // Append m zeros to data
    string appended_data = data + string(m, '0');

    // Perform division to get remainder
    string remainder = mod2div(appended_data, divisor);

    // Final transmitted codeword
    string codeword = data + remainder;

    cout << "\n--- CRC Calculation ---\n";
    cout << "Data bits: " << data << endl;
    cout << "Generator (Polynomial): " << divisor << endl;
    cout << "Remainder: " << remainder << endl;
    cout << "Transmitted Frame (Data + CRC): " << codeword << endl;

    return 0;
}

