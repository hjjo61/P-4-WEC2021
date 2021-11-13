// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cctype>


int buttonMap[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
double buttonDelay[] = {0, 0.25, 0.50, 0, 0.25, 0.50, 0, 0.25, 0.50,0, 0.25, 0.50,0, 0.25, 0.50,0, 0.25, 0.50, 0.75, 0, 0.25, 0.50, 0, 0.25, 0.50, 0.75};
double buttonBDelay[] = {0.75, 0.5, 0.25, 0.75, 0.5, 0.25, 0.75, 0.5, 0.25, 0.75, 0.5, 0.25, 0.75, 0.5, 0.25, 0.75, 0.75, 0.5, 0.25, 0.75, 0.5, 0.25, 0.75, 0.75, 0.5, 0.25}; 
int buttonBroke = -1; 

double timeForLetter(char letter, char previousLetter){
    double time = 0;

    if (isupper(letter)){ // Add 2 seconds to the time if it is capitalized 
        letter += 32; //Changes all capitals to lower case just to make it easier to work with
        time += 2;
    }

    if (buttonBroke == buttonMap[int(letter)-97]){
        time+= buttonBDelay[int(letter)-97]; // Add the time to reach the letter on the broken button
    }else{
        time += buttonDelay[int(letter)-97]; // Add the time to reach the letter
    }

    if (previousLetter != '\0' && buttonMap[int(tolower(previousLetter))-97] == buttonMap[int(letter)-97]){ 
        if (buttonMap[int(tolower(previousLetter))-97] != buttonBroke){
            time+= 0.5; // If its the same button cluster, then 0.5 sec
        }else{
            time += 0.25; // If the previous button used the work around, clicking the button again will will not trigger the delay
        }
    }else if (previousLetter!='\0'){
        time += 0.25; //If its a new button cluster, then only 0.25 sec
    } // If this was the first button press, no first press delay

    return time;
}


int main () {
    std::string line;
    char previousLetter = '\0';
    double time = 0;
    std::ifstream myfile;
    myfile.open ("PACKAGE/Part2.txt");

    if(myfile.is_open()){
        myfile >> buttonBroke;
        while (myfile >> line){
            previousLetter = '\0';
            time = 0;
            for (int i = 0; i<line.size(); i++){
                time += timeForLetter(line[i], previousLetter);
                previousLetter = line[i];
            }
            std::cout << line << " -> " << time << std::endl;
        }

        myfile.close();
    }else{
        std::cout << "File could not be openned or could not be found" << std::endl;
    }
    
    return 0;
}