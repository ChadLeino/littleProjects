#include <iostream>
#include <string>
#include <vector>


class mainClass {
    public:
        int x;
        int y;
        void print() {
            std::cout << x << " " << y << std::endl;
        }
        void printz() {
            std::cout << z << std::endl;
        }

        mainClass() {
            x = 1;
            y = 2;
            z = 3;
            k = 4;
        }
    private:
        int z;
    protected:
        int k;
        void printk() {
            std::cout << k << std::endl;
        }
};

class subClass: public mainClass {
    public:
        int a;
        int b;
        void printNew() {
            std::cout << a << " " << b << std::endl;
        }
        void printOld() {
            std::cout << x << " " << y << " " << k << std::endl;
        }
        subClass() {
            a = 6;
            b = 7;
        }
};



int main() {
    mainClass Obj1;
    subClass Obj2;

    Obj1.print();
    Obj1.printz();

    Obj2.printNew();
    Obj2.printOld();
    Obj2.print();



    //for (int i = 0)


    
    return 0;
}
