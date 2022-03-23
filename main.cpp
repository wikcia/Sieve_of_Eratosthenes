#include <iostream>
#include <string>
#include <exception>
#include <list>
#include <vector>

using namespace std;

class PrimeNumbers {
    int* tab;
    bool* prime;
    std::vector<int> myVector;

public:
    explicit PrimeNumbers(int n) {
        if (n < 2) throw std::string ("Invalid number");

        tab = new int[n];
        prime = new bool [n + 1];
        for (int i = 0; i <= n; i++)
            prime[i] = true;

        for (int p = 2; p * p <= n; p++) {
            // If prime[p] is not changed, then it is prime
            if (prime[p]) {
                // Update all multiples of p
                for (int i = p * p; i <= n; i += p) {
                    prime[i] = false;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (prime[i]) {
                myVector.insert(myVector.cend() ,i);
            }
        }
        tab = new int[myVector.size()];
        for (int i = 0; i < myVector.size(); i++) {
            tab[i] = myVector.at(i);
        }
    }

    int number(int m) {
        if(m < 0 || m >= sizeof(tab))
            throw std::string ("Number out of range");
        return tab[m];
    }
    ~PrimeNumbers(){
        delete[] tab;
    }
};

int main(int argc, char* argv[]) {
    int n, k;
    try {
        n = stoi(argv[1]);
        auto* primeNumbers = new PrimeNumbers(n); // we are using auto when initializing with new to avoid duplicating the type name

        for(int i = 2; i < argc; i++) {
            try {
                k = stoi(argv[i]);
                cout <<  argv[i] << " - " << primeNumbers->number(k) << endl;
            }
            catch (const invalid_argument &ia){
                cout << argv[i] <<  " - invalid data" << endl;
            }
            catch (string &e) {
                cout<< e <<endl;
            }
        }
        delete primeNumbers;
    }
    catch (const invalid_argument &ia){
        cout << argv[1] <<  " - invalid data" << endl;
    }
    catch (string &e) {
        cout<< e <<endl;}
}