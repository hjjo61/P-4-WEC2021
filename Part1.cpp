// basic file operations
#include <iostream>
#include <fstream>
#include <string>

int main () {
    std::string line;
    std::ifstream myfile;
    myfile.open ("PACKAGE/Test1.txt");

    if(myfile.is_open()){
        while ( std::getline (myfile,line)){
        std::cout << line << " -> ";

        

        }
        myfile.close();
    }else{
        std::cout << "File could not be openned or could not be found" << std::endl;
    }
    
    return 0;
}