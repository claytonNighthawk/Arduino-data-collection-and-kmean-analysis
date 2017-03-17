#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <time.h>
#include <locale>
#include <iomanip>
#include "fileparser.hpp"

using namespace std;

int fileParser(map<string, tuple<vector<Point>, double, double>>& minMaxVectorMap, vector<string>& mapKeys, string fileName) {
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

    double timeD;
    double tempD;
    double lightD;
    double soundD;    

    string dataline;
    stringstream currentLine;
      
    if (dataset.is_open()) {
        for (string key : mapKeys) {
            minMaxVectorMap[key];
        }       
      
        while (true) {
            int i = 0;
                 
            while (getline(dataset, dataline)) {
                currentLine.str(dataline);
                //grab channel and convert text format time to tm
                currentLine >> channel >> get_time(&timestampTM, "%Y.%m.%d.%H:%M:%S");
                currentLine >> unusedLabel >> temperature;
                currentLine >> unusedLabel >> soundlevel;
                currentLine >> unusedLabel >> lightlevel;
                currentLine.clear();
                timestamp = mktime(&timestampTM);

                //catch first value
                if(firstline == true){
                    inittimestamp = timestamp;
                    firstline = false;
                }

                //subtract current from first for change in time
                timestamp = timestamp - inittimestamp;

                timeD = double(timestamp);
                tempD = double(temperature);
                lightD = double(lightlevel);
                soundD = double(soundlevel);
                double temp1, temp2;


                // stuff them into vectors in the map for Clayton
                get<0>(minMaxVectorMap["TimeTemp"]).emplace_back(timeD, tempD);
                get<0>(minMaxVectorMap["TimeLight"]).emplace_back(timeD, lightD);
                get<0>(minMaxVectorMap["TimeSound"]).emplace_back(timeD, soundD);
                get<0>(minMaxVectorMap["TempLight"]).emplace_back(tempD, lightD);
                get<0>(minMaxVectorMap["TempSound"]).emplace_back(tempD, soundD);
                get<0>(minMaxVectorMap["LightSound"]).emplace_back(lightD, soundD);

                if (i == 0) {
                    get<1>(minMaxVectorMap["TimeTemp"]) = min(timeD, tempD);
                    get<2>(minMaxVectorMap["TimeTemp"]) = max(timeD, tempD);

                    get<1>(minMaxVectorMap["TimeLight"]) = min(timeD, lightD);
                    get<2>(minMaxVectorMap["TimeLight"]) = max(timeD, lightD);

                    get<1>(minMaxVectorMap["TimeSound"]) = min(timeD, soundD);
                    get<2>(minMaxVectorMap["TimeSound"]) = max(timeD, soundD);

                    get<1>(minMaxVectorMap["TempLight"]) = min(tempD, lightD);
                    get<2>(minMaxVectorMap["TempLight"]) = max(tempD, lightD);

                    get<1>(minMaxVectorMap["TempSound"]) = min(tempD, soundD);
                    get<2>(minMaxVectorMap["TempSound"]) = max(tempD, soundD);

                    get<1>(minMaxVectorMap["LightSound"]) = min(lightD, soundD);
                    get<2>(minMaxVectorMap["LightSound"]) = max(lightD, soundD);

                } else {
                    temp1 = get<1>(minMaxVectorMap["TimeTemp"]); 
                    temp2 = get<2>(minMaxVectorMap["TimeTemp"]);
                    get<1>(minMaxVectorMap["TimeTemp"]) = min(temp1, min(timeD,tempD));
                    get<2>(minMaxVectorMap["TimeTemp"]) = max(temp2, max(timeD,tempD)); 

                    temp1 = get<1>(minMaxVectorMap["TimeLight"]); 
                    temp2 = get<2>(minMaxVectorMap["TimeLight"]); 
                    get<1>(minMaxVectorMap["TimeLight"]) = min(temp1, min(timeD,lightD));
                    get<2>(minMaxVectorMap["TimeLight"]) = max(temp2, max(timeD,lightD));

                    temp1 = get<1>(minMaxVectorMap["TimeSound"]); 
                    temp2 = get<2>(minMaxVectorMap["TimeSound"]); 
                    get<1>(minMaxVectorMap["TimeSound"]) = min(temp1, min(timeD,soundD));
                    get<2>(minMaxVectorMap["TimeSound"]) = max(temp2, max(timeD,soundD));

                    temp1 = get<1>(minMaxVectorMap["TempLight"]); 
                    temp2 = get<2>(minMaxVectorMap["TempLight"]); 
                    get<1>(minMaxVectorMap["TempLight"]) = min(temp1, min(tempD,lightD));
                    get<2>(minMaxVectorMap["TempLight"]) = max(temp2, max(tempD,lightD));

                    temp1 = get<1>(minMaxVectorMap["TempSound"]); 
                    temp2 = get<2>(minMaxVectorMap["TempSound"]); 
                    get<1>(minMaxVectorMap["TempSound"]) = min(temp1, min(tempD,soundD));
                    get<2>(minMaxVectorMap["TempSound"]) = max(temp2, max(tempD,soundD));

                    temp1 = get<1>(minMaxVectorMap["LightSound"]); 
                    temp2 = get<2>(minMaxVectorMap["LightSound"]); 
                    get<1>(minMaxVectorMap["LightSound"]) = min(temp1, min(lightD,soundD));
                    get<2>(minMaxVectorMap["LightSound"]) = max(temp2, max(lightD,soundD));

                }
            i++;
            }

            if (dataset.eof()) break; // Ensure end of read was EOF.
            //reset line      
        }
    }
  
  return 0;
}

// };