#include <iostream>
#include <string>


template <typename T> T myTemplate(T x, T y) {
    if (x > y) {
        return x;
    }
    else if (y > x)
    {
        return y;
    }
    else {
        return 0;
    }
    
}


int main() {
    int x = 1;
    int y = 2;
    int z = 3;

    double a = 5;
    double b = 3.1;
    double c = 9.01;

    std::string n = "hey";
    std::string m = "hello";

    std::cout << myTemplate(x, y) << "\n";
    std::cout << myTemplate(a, b) << "\n";
    std::cout << myTemplate(n, m) << "\n";


    double listed[] = {1, 2, 5, 6, 2, 3, 9, 0, 1, 2};

    // let sort listed in here
    int k = sizeof(listed) / sizeof(listed[0]);
    std::cout << k << std::endl;

    for (int i = 0; i < k; i++) {
        
    }

    return 0;
}