#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true; // 2 is the only even prime number
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to reverse the digits of a number
int reverseNumber(int n) {
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed;
}

// Function to classify the number as non-prime, prime, or emirp
string classifyNumber(int n) {
    if (!isPrime(n)) {
        return to_string(n) + " is not prime.";
    }
    
    int reversed = reverseNumber(n);
    if (n != reversed && isPrime(reversed)) {
        return to_string(n) + " is emirp.";
    }
    
    return to_string(n) + " is prime.";
}

int main() {
    int n;
    while (cin >> n) {
        cout << classifyNumber(n) << endl;
    }
    return 0;
}
9