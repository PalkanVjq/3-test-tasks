#include "iostream"
#include "vector"

using namespace std;

// I have implemented the multiplication of a number (array) into a column. Thus, you can find out the factorial of absolutely any number
void Mul(vector<int> &_number, int x)
{
	int loop=0; //number of digits in a number õ
	for (int i = 1; !loop; i++)
		if (x % (int)pow(10, i) == x)
			loop = i;

	vector<int> tempresult; //here the sum of all numbers will be stored as a result of multiplying each digit of the number x by the number _number

	//for (int r = 0; r < _number.size(); r++)
	//	tempresult.push_back(0);


	for (int j = 0; j < loop; j++)
	{
		int xx=x;							//
		xx = xx % (int)pow(10, j + 1);		//getting the next digit from Õ by offset
		xx = xx / (int)pow(10, j);			//

		
		vector<int> copyvec; //copyvec = _number + offset when moving to the next multiplying digit of the number Õ

		for(int h=0; h< _number.size()+j; h++)  //we shift our number by adding zeros to the beginning
			copyvec.push_back(0);

		for (int t = 0; t < _number.size(); t++) //leave additional zeros at the beginning and copy the number _òãüèóê
			copyvec[j + t] = _number[t];

		int tenboof = 0; // the result of tens is stored here, if the multiplication turned out to be more than 10
		for (int i = 0; i < _number.size(); i++)
		{
			
			copyvec[i+j] = copyvec[i+j] * xx + tenboof; //we multiply each digit of the cisel _number by a digit of X, and then add tens from the last multiplication
			tenboof = 0;

			if (copyvec[i+j] >= 10)
			{
				if (i == _number.size()-1)
				{
					copyvec.push_back(copyvec[i+j]/10); //add the number of tens to the end
					copyvec[i+j] = copyvec[i+j] % 10; //assign the remainder of division by 10
				}
				else
				{
					tenboof = copyvec[i+j] / 10; //we save the number of tens, then add
					copyvec[i+j] = copyvec[i+j] % 10; //assign the remainder of division by 10
				}
			}
		}

		for (int y = tempresult.size(); y < copyvec.size(); y++) //if our number is longer, then we adjust the size
			tempresult.push_back(0);

		//we sum up all the numbers that we got as a result of multiplying each digit by a number. According to the rules of multiplication in a column
		for (int p = 0; p < copyvec.size(); p++)
			tempresult[p] += copyvec[p];

	}
	//the result of multiplication is assigned to our number
	_number = tempresult;

}



int main()
{
	vector<int> number = {1}; //it is a number as an array. Each digit of the number is written in a separate cell
	int result = 0; //the sum of all digits of the number will be stored here (100!)

	int N = 100; //factorial
	//cin >> N;

	
	for (int i = 2; i < N + 1; i++)
		Mul(number,i); //multiply number by i

	cout << N << "! = ";
	for (int i = 0; i < number.size(); i++)
	{
		cout << number[number.size() - 1 - i] ; //number output
		result += number[number.size() - 1 - i]; // sum of digits
	}
	cout << endl <<endl<< "Result: "<<result<< endl;
}