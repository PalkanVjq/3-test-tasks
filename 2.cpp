#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
int start;
int finish;

class City {
public:
	static int nr; //static variable for indexing cities
	int index; 
	string name="";
	int cost = 200000; //The cost of the journey to this city

	int **NrCost; // All neighbors and fares to them
	int masssize=0;

	bool out = false;// have we already been in this city

	
	City()
	{
		index = nr++;

		for (int i = 0; i < 10; i++)
			name += (char)(97+ rand()%26); //random char a-z
	
	}
	~City() {};

	void AddТeighbour(int _nr, int _cost) // adding neighbor and price
	{
		if (_nr == this->index)
			return;

		for (int i = 0; i < masssize; i++)
			if (NrCost[i][0] == _nr) // if this neighbor already exists, then skip it
				return;

		//adding a new neighbor

		int **boof = NrCost;

		NrCost = new int *[++masssize];

		for (int i = 0; i < masssize; i++)
			NrCost[i] = new int[2];

		for (int i = 0; i < masssize - 1; i++)
		{
			NrCost[i][0] = boof[i][0];
			NrCost[i][1] = boof[i][1];
		}

		NrCost[masssize-1][0] = _nr;
		NrCost[masssize-1][1] = _cost;

		// clear memory
		for (int i = 0; i < masssize - 1; i++)
			delete[] boof[i];
		delete[] boof;

	}

};
 int City::nr  = 1;
 vector<City> AllCity;

 bool FindMin(City &temp)
 {
	 if (temp.out || temp.index==finish) // if we have already been to the city or is it the final city
		 return false; //going back

	 bool FreeTeighbor = false; // are there any free neighbors to which you can drive

	 for (int i = 0; i < temp.masssize; i++) // enumeration of neighbors of the current city
	 {
		 // the price of the neighbor's city> the price of the current city + the price of the direct path of the current city to the neighboring city 
		 //&& we have not yet been in the neighboring city
		 if (AllCity[temp.NrCost[i][0] - 1].cost > temp.NrCost[i][1] + temp.cost && !AllCity[temp.NrCost[i][0] - 1].out) 
		 {
			 AllCity[temp.NrCost[i][0] - 1].cost = temp.NrCost[i][1] + temp.cost; // neighbor price = current city price + road to neighbor
			 FreeTeighbor = true; // there is a free neighbor
			 
		 }
	 }
	 
	 if (!FreeTeighbor) // if there are no free neighbors
		 return false; // going back

	 for (int i = 0; i < temp.masssize; i++)
	 {
		 temp.out = true; //we mark that in this city we were
		 temp.out = FindMin(AllCity[temp.NrCost[i][0]-1]);
	 }
	 return true; 
 }


int main()
{

	srand(time(0));

	vector <int> Rvector; // vector, crown stores the results of multiple paths

	int s = 1 + rand() % 3; //  s [the number of tests <= 10]

	for (int test = 0; test < s; test++) // loop for multiple tests
	{

		int N = 4 + rand() % 6; //n [the number of cities <= 10000]
		int r = 1 + rand() % 3; // r [the number of paths to find <= 100]

		for (int i = 0; i < N; i++) //adding cities to vector
			AllCity.push_back(*(new City()));

		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < 3; j++) // "give" each city 3 neighbors and the cost of the path to them
			{
				int randcity = 1 + rand() % N; // random city index
				int randcost = 1 + rand() % 20; //random price

				AllCity[i].AddТeighbour(randcity, randcost); // add current neighbor city and price
				AllCity[randcity - 1].AddТeighbour(i + 1, randcost); // add the current city to a neighbor as a neighbor and a price. (mutual neighbors)
			}
		}

		


		//SHOW
		cout<<"************ TEST " <<test+1<< " ************"<<endl;
		cout << "input:" << endl << s << endl << N << endl;
		for (int i = 0; i < AllCity.size(); i++)
		{
			cout << AllCity[i].name << endl << AllCity[i].masssize << endl; // display city name and number of neighbors

			for (int j = 0; j < AllCity[i].masssize; j++)
				cout << AllCity[i].NrCost[j][0] << " " << AllCity[i].NrCost[j][1] << endl; // Displaying indices of neighboring cities and prices
		}

		for (int rIter = 0; rIter < r; rIter++) // implementation of computation of multiple paths
		{
			start = 1 + rand() % N; //Starting city
			finish = 1 + rand() % N; // end city

			while (start == finish) // if the final and initial cities coincide, then change the final
				finish = 1 + rand() % N;

			AllCity[start - 1].cost = 0; //we reset the price of the starting city

			FindMin(AllCity[start - 1]); // Run the function to find the shortest path
			Rvector.push_back(AllCity[finish - 1].cost); // Keeping the cost of the shortest path

			cout << AllCity[start - 1].name << "\t" << AllCity[finish - 1].name << endl; // displaying the starting and ending city
			

			for (int iter = 0; iter < AllCity.size(); iter++)
				AllCity[iter].cost = 200000; // we reset the price of the cities of the final city
		}
		cout << endl;
		cout << "Output:" << endl;

		for (int iter = 0; iter < Rvector.size(); iter++)
			cout << Rvector[iter] << endl; // Outputting the results of each path

		//clear vectors for new test
		Rvector.clear(); 
		AllCity.clear();
	}
}