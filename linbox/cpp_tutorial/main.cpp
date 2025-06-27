#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double pi = 3.14;
    const float k = 9E9;
    char c = 107; // ASCII for 'k'
    bool show = true;

    if (show) cout << c << ": " << k << "\n";

    int r;
    cout << "r? ";
    cin >> r;
    cout << "C = " << 2 * pi * r << "\n";

    string s = "----";
    s[2] = '|';
    cout << "Len: " << s.length() << ", " << s << "\n";

    cout << (show ? "I did\n" : "My brother did\n");

    char arr[] = "hi!\n";
    cout << arr;

    int number = 4;
    switch (number) {
        case 1:
            cout << "one";
            break;
        case 2:
            cout << "two";
            break;
        case 3:
            cout << "three";
            break;
        case 4:
            cout << "four";
            break;
    }
    int i = 0;
    do {
        cout << i << "\n";
        i++;
    }
    while (i < 5);
    string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};
    for (string car : cars) {
        cout << car << "\n";
    }
    return 0;
}
