#include <iostream>
using namespace std;

void greet(string& name){
    cout << "Hello, " << name << "!" << endl;
}

int main() {
    greet((string &) "World");
    return 0;
}
