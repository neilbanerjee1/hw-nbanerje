#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int totalSpots;
  int *buildingHeights;
  string **skyline;
  string curr;

  input >> totalSpots;
  getline(input, curr); //consume the newline character for the first line.
  skyline = new string*[totalSpots];

  //you will need to keep track of the height of each building
  buildingHeights = new int[totalSpots];

  for (int i = 0; i < totalSpots; i++) {
	  buildingHeights[i] = 0;
	  skyline[i] = NULL;
  }
  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;

	  if (curr == "BUILD") {
		  int x,y;
		  string c;
		  ss >> x;
		  ss >> y;
		  ss >> c;

		  //checking for invalid conditions
		  if (ss.fail() || skyline[x] != NULL || x < 0 || x > totalSpots || y < 0) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	//set height of building at certain plot
			buildingHeights[x] = y;
			skyline[x] = new string[y];
			
			//specifying building color
			for (int i = 0; i < y; i++){
				skyline[x][i] = c; 	 				
			}
		  }
	  }

	  else if (curr == "EXTEND") {
	  	  
	  	  int x,y;
	  	  string c;
	  	  ss >> x;
	  	  ss >> y;
	  	  ss >> c;

	  	  if (ss.fail() || x < 0 || x > totalSpots || y < 0 || skyline[x] == NULL){
	  	  	output << "Error - incorrect command" << endl;
	  	  }

	  	  //making temporary array of strings with extended # of floors
	  	  int existingFloors = buildingHeights[x];
	  	  string* tempFloors = new string[existingFloors + y];

	  	  //filling copy with existing skyline values
	  	  for(int i = 0; i < existingFloors; i++){
	  	  	tempFloors[i] = skyline[x][i];
	  	  }

	  	  for(int i = existingFloors; i < existingFloors + y; i++){
	  	  	tempFloors[i] = c;
	  	  }

	  	  delete[] skyline[x];
	  	  skyline[x] = tempFloors;
	  	  delete[] tempFloors;

	  }

	  else if (curr == "DEMOLISH") {
	  	  
	  	  int x;
	  	  ss >> x;

	  	  if (skyline[x] == NULL){
	  	  	output << "Error - incorrect command" << endl;
	  	  }

	  	  delete [] skyline[x];
	  	  skyline[x] = NULL;
	  	  buildingHeights[x] = 0;

	  	  //for (int i = 0; i < length; i++){
			//skyline[x][i] = NULL; 	 				
			//}
	  }

	  else if (curr == "SKYLINE") {
	  	  int y;
	  	  ss >> y;

	  	  for(int i = 0; i < totalSpots; i++){
	  	  	if(buildingHeights[i] < y){
	  	  		output << "SKY ";
	  	  	}
	  	  	else {
	  	  		output << skyline[i][y-1] << " ";
		  	  }
		  	}

	  	  output << endl;
	  }

	  else {
	  	  cout << "Error - incorrect command" << endl;
	  }
  }

  for(int i = 0; i < totalSpots; i++){
  	delete [] skyline[i];
  }

  delete [] skyline;
  delete [] buildingHeights;


  return 0;
}