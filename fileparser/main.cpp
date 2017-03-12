#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <locale>
#include <iomanip>


using namespace std;

typedef std::pair<double, double> Point;


int fileParser(string fileName, vector<Point> &TimeTemp, vector<Point> &TimeLight, vector<Point> &TimeSound, vector<Point> &TempLight, vector<Point> TempSound, vector<Point> LightSound)
{
  ifstream dataset(fileName);

  // date extracted from the file
  string unusedLabel;
  string channel;
  tm timestampTM;
  time_t timestamp;
  float temperature;
  int soundlevel;
  int lightlevel;
  
  string dataline;
  stringstream currentLine;

  //Point for each vector
  Point pTimeTemp;
  Point pTimeLight;
  Point pTimeSound;
  Point pTempLight;
  Point pTempSound;
  Point pLightSound;
  
  
  cout << "started" << endl;
  if (dataset.is_open())
    {
      cout << "file is open" << endl;
      while (true)
        {
	  	     
	  while (getline(dataset, dataline))
	    {
	      cout << dataline << endl;
	      currentLine.str(dataline);
	      //grab channel and convert text format time to tm
	      currentLine >> channel >> get_time(&timestampTM, "%Y.%m.%d.%H:%M:%S");
	      currentLine >> unusedLabel >> temperature;
	      currentLine >> unusedLabel >> soundlevel;
	      currentLine >> unusedLabel >>lightlevel;

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


	      cout << get<0>(pTimeTemp) << " " << get<1>(pTimeTemp) << " ";
	      cout << get<0>(pTimeLight) << " " << get<1>(pTimeLight) << " ";
	      cout << get<0>(pTimeSound) << " " << get<1>(pTimeSound) << " ";
	      cout << get<0>(pTempLight) << " " << get<1>(pTempLight) << " ";
	      cout << get<0>(pTempSound) << " " << get<1>(pTempSound) << " ";
	      cout << get<0>(pLightSound) << " " << get<1>(pLightSound) << endl;
	     
	      
	      
	      
	    }
	  
	  if (dataset.eof()) break; // Ensure end of read was EOF.
	  //reset line
	  dataset.clear();
	  
        }
    }
  
  return 0;
}

int main() {


  

	vector<Point> points_TTemp;
	vector<Point> points_TL;
	vector<Point> points_TS;
	vector<Point> points_TempL;
	vector<Point> points_TempS;
	vector<Point> points_LS;
	// or maybe a vector of vectors or map of vectors

	// calls file parser on fileName and populates the vectors
	fileParser("singlesensor", points_TTemp, points_TL, points_TS, points_TempL, points_TempS, points_LS);
  
  
  
	return(0);
  

  
}
