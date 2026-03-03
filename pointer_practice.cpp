#include <iostream>


int main(int argc, char* argv[]) {

    // I have forgotten a lot
    // lets start with the basics
    int x {};
    int y = x;
    x = 100;
    std::cout << y << '\n';
    // ok so we just assign y to the value of x, not pointing at the same object


    int* p {nullptr};
    p = &x;
    
    std::cout << p << " " << *p << '\n';

    // ok now lets get into arrays on the stack
    int arr[] = {1, 2, 3, 4, 5};

    std::cout << arr << '\n'; // so this prints the pointer
    // that is because when using arrays, it goes like *(arr + i) or something like that for functions?

    for (int num : arr) {
        std::cout << num << "\n";
    }
    // this is a for each loop

    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << size << "\n";
    return 0;


}