#include <iostream>

using FcnType = int(*)(double, int);
// this is a type that is a pointer, pointing to a function that takes in a double and int, and returns an int!!!!

using Ptype = int(*)();

int printData() {
    std::cout << "x\n";
    return 1;
}

int foo(double x, int y) {
    return x + y;
}

int main() {
    FcnType ptr = foo; // pointer points to foo, which is really just an address in memory

    int result = ptr(5.0, 4);

    std::cout << result << std::endl;

    Ptype ptr2 = printData; // delcare type, identifier, and set it equal to the function that matches the type

    int result2 = ptr2(); // an identifier equal to the pointer called(with arguments)

    std::cout << "result2\n";

    return 0;


}