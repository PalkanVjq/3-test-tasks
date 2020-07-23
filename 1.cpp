#include <iostream>
#include <string>
#include <vector>

using namespace std;

string word=""; //Current permutation
vector<string> vectorword;
void gen(int k=0)
{
	// the string "word" changes every time as a result of the permutation of characters, so we iterate over all possible options

	if (k == word.length())
	{
		if (word[0] == ')' || word[word.length() - 1] == '(')
			return;
		
			bool write = true;

			for (int i = 0; write && i < vectorword.size(); i++) //repetition handling
			{
				if (vectorword[i] == word)
					write = false;
			}
			if (write)
			{
				int skobk = 1; // =1 because, the first char is exactly '('
				for (int j = 1; j <word.length() - 1; j++)
				{
					if (word[j] == '(')
						skobk++;

					if (word[j] == ')')
						skobk--;

					if (skobk < 0)
						return;
				}
					vectorword.push_back(word);
			}
		
	}
	else
	{
		for (int j = k; j < word.length(); j++)
		{
			// permutation implementation
			swap(word[k], word[j]);
			gen(k + 1);
			swap(word[k], word[j]);
		}
	}
}

int main()
{
	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		word += "()";

	gen();

	for (int i = 0; i < vectorword.size(); i++)
		cout << vectorword[i] << endl;
	cout << vectorword.size();

	return 0;
}