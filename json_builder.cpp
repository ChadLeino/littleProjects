#include <iostream>
#include <fstream>
#include <map>
#include <iterator>

int main() {
    std::map<std::string, int> toBuild { {"first", 1}, {"second" , 2}, {"third", 3} };

    // std::ofstream out("test.json");


    // if (!out) {
    //     return 1;
    // }

    // out << "{" << "\n";

    // for (auto it : toBuild) {
    //     std::cout << it.first << " " << it.second << "\n";

    //     out << "\t" << "\"" << it.first << "\"" << ": " << it.second << "," << "\n";  
    // }

    // out << "}";

    // out.close();

    std::ofstream out("test.json");

    if (!out) {
        return 1;
    }

    out << "{" << "\n";

    for (auto it = toBuild.begin(); it != toBuild.end(); it++) {
        if (std::next(it) == toBuild.end()) {
            out << "\t" << "\"" << it->first << "\"" << ": " << it->second << "\n";
            break;
        }
        out << "\t" << "\"" << it->first << "\"" << ": " << it->second << "," << "\n"; 
    }

    out << "}";

    out.close();


    return 0;


}