// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cctype>
#include <limits>

double wordTime[10]{-1};
std::string words[10];
int buttonMap[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
double buttonDelay[] = {0, 0.25, 0.50, 0, 0.25, 0.50, 0, 0.25, 0.50,0, 0.25, 0.50,0, 0.25, 0.50,0, 0.25, 0.50, 0.75, 0, 0.25, 0.50, 0, 0.25, 0.50, 0.75};

double timeForLetter(char letter, char previousLetter){
    double time = 0;

    if (isupper(letter)){ // Add 2 seconds to the time if it is capitalized 
        letter += 32;
        time += 2;
    }
    time += buttonDelay[int(letter)-97]; // Add the time to reach the letter

    if (previousLetter != '\0' && buttonMap[int(tolower(previousLetter))-97] == buttonMap[int(letter)-97]){ 
        time += 0.5; // If its the same button cluster, then 0.5 sec
    }else if (previousLetter!='\0'){
        time += 0.25; //If its a new button cluster, then only 0.25 sec
    } // If this was the first button press, no first press delay

    return time;
}


int main () {
    std::string line;
    int counter = 0;
    double min = std::numeric_limits<double>::max();
    char previousLetter = '\0';
    double time = 0;
    std::ifstream myfile;
    myfile.open ("PACKAGE/Test1.txt");

    if(myfile.is_open()){
        while (myfile >> line){ //Read Each Word In, and Calculate Time for each word
            previousLetter = '\0';
            time = 0;
            for (int i = 0; i<line.size(); i++){ // Read Each Letter and Calculate Time for Each Letter
                time += timeForLetter(line[i], previousLetter);
                previousLetter = line[i];
            }
            std::cout << line << " -> " << time << std::endl;
            words[counter] = line;
            wordTime[counter] = time;
            counter++;
            if (time < min){
                min = time;
            }
        }

        std::cout << std::endl << "The fastest word(s) is (are):" << std::endl;
        for (int i = 0; i < int(counter); i++){
            if (wordTime[i] == min){
                std::cout << words[i] << " with time of " << min << " second(s)." << std::endl;
            }
        }

        myfile.close();
    }else{
        std::cout << "File could not be openned or could not be found" << std::endl;
    }
    
    return 0;
}