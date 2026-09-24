#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    char c;
    const char *s = "`1234567890-=" "qwertyuiop[]\\" "asdfghjkl;'" "zxcvbnm,./";

    while (cin.get(c)) {
        // Ensure character is lowercase if it's an alphabetic character
        if (isalpha(c)) {
            c = tolower(c);
        }

        const char *p = strchr(s, c);
        if (p) {
            cout << *(p - 2);
        } else {
            cout << c;
        }
    }

    return 0;
}