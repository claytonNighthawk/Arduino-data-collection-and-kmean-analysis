#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
// #include <stdio.h>
#include <locale>
#include <iomanip>
#include "fileparser.hpp"


using namespace std;

int fileParser(string fileName, vector<Point> &TimeTemp, vector<Point> &TimeLight, vector<Point> &TimeSound, vector<Point> &TempLight, vector<Point> &TempSound, vector<Point> &LightSound) {
    ifstream dataset(fileName);

    // date extracted from the file
    string unusedLabel;
    string channel;
    tm timestampTM;
    time_t timestamp;
    time_t inittimestamp;
    float temperature;
    int soundlevel;
    int lightlevel;
    bool firstline = true;

    string dataline;
    stringstream currentLine;

    //Point for each vector
    Point pTimeTemp;
    Point pTimeLight;
    Point pTimeSound;
    Point pTempLight;
    Point pTempSound;
    Point pLightSound;
      
    if (dataset.is_open()) {
      
        while (true) {
                 
            while (getline(dataset, dataline)) {
                //cout << dataline << endl;
                currentLine.str(dataline);
                //grab channel and convert text format time to tm
                currentLine >> channel >> get_time(&timestampTM, "%Y.%m.%d.%H:%M:%S");
                currentLine >> unusedLabel >> temperature;
                currentLine >> unusedLabel >> soundlevel;
                currentLine >> unusedLabel >>lightlevel;
                currentLine.clear();
                timestamp = mktime(&timestampTM);
                //catch first value
                if(firstline == true){
                    inittimestamp = timestamp;
                    firstline = false;
                }

                //subtract current from first for change in time
                timestamp = timestamp - inittimestamp;
                //cout << timestamp << endl;
                // cast into doubles into points "pairs"        
                pTimeTemp   = make_pair(double(timestamp), double(temperature));
                pTimeLight  = make_pair(double(timestamp), double(lightlevel));
                pTimeSound  = make_pair(double(timestamp), double(soundlevel));
                pTempLight  = make_pair(double(temperature), double(lightlevel));
                pTempSound = make_pair(double(temperature), double(soundlevel));
                pLightSound = make_pair(double(lightlevel), double(soundlevel));

                // stuff them into vectors for Clayton
                TimeTemp.push_back(pTimeTemp);
                TimeLight.push_back(pTimeLight);
                TimeSound.push_back(pTimeSound);
                TempLight.push_back(pTempLight);
                TempSound.push_back(pTempSound);
                LightSound.push_back(pLightSound);
            }
          
            if (dataset.eof()) break; // Ensure end of read was EOF.
            //reset line      
        }
    }
  
  return 0;
}