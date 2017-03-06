#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <locale>
#include <iomanip>


using namespace std;



int main()
{
  ifstream dataset("singlesensor");
  map<time_t, float> tempvalues;
  map<time_t, int> soundvalues;
  map<time_t, int> lightvalues;

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

	      //store each type with time stamp
	      timestamp = mktime(&timestampTM);
	      tempvalues[timestamp]=temperature;
	      soundvalues[timestamp]=soundlevel;
	      lightvalues[timestamp]=lightlevel;
	      cout << timestamp << " " << tempvalues[timestamp] << " " << soundvalues[timestamp] << endl;
	      currentLine.clear();
	    }
	  
	  if (!dataset.eof()) break; // Ensure end of read was EOF.
	  dataset.clear();
	  

        }
    }
  
  return 0;
}
