#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

void AdvanceToNextDifferent (string &bag, string::iterator &pos)
{
	string::iterator initialPos = pos;

	while ((pos != bag.end()) && (*pos == *initialPos))
		++pos;
}

int factorial (int n)
{
	if (n == 0)
		return 1;
	else
		return (n*factorial(n-1));
}

int choose (int n, int k)
{
	return (factorial(n) / factorial(k) / factorial(n-k));
}

double CalcProb (string &bag, string stem)
{
	int n,k;
	int blanks = 2;

	double prob = 1;	

	sort(stem.begin(), stem.end());
	string::iterator pos = stem.begin();

	while (pos != stem.end())
	{
		k = count_if(stem.begin(), stem.end(), bind2nd(equal_to<char>(), *pos));
		n = count_if(bag.begin(), bag.end(), bind2nd(equal_to<char>(), *pos));

		prob *= choose(n,k);

		AdvanceToNextDifferent(stem, pos);
	}

	// If stem contains an S then multiply probability by 1.5
	if (stem.find("S") != std::string::npos)
		prob *= 1.5;

	return prob;
}

int CountUsableTiles (string stem, string &bag, int blanks, map<string, string> &dict)
{
	int usable = 0;
	string str;

	for (string::iterator It = bag.begin(); It != bag.end(); ++It)
	{
		str = stem + (*It);
		sort(str.begin(), str.end());
		if (dict.find(str) != dict.end())
		{
			usable++;
		}
	}
	for (string::iterator It = stem.begin(); It != stem.end(); ++It)
	{
		str = stem + (*It);
		sort(str.begin(), str.end());
		if (dict.find(str) != dict.end())
		{
			usable--;
		}
	}
	if (usable > 0)
		usable += blanks;

	return usable;
}

void CreateDictionary (map<string, string> &dict)
{
	ifstream dictfile("OWL2.txt");

	while (dictfile.good())
	{
		string word, alphagram;

		dictfile >> word;

		alphagram = word;

		sort(alphagram.begin(), alphagram.end());
		dict.insert(std::pair<std::string, std::string>(alphagram, word));
	}
}

void BuildStems (int length, string stem, string &bag, string::iterator pos, set<string> &stemSet)
{
	if (stem.size() == length)
	{
		stemSet.insert(stem);
		
		return;
	}

	while (pos != bag.end())
	{
		BuildStems(length, stem + (*pos), bag, pos+1, stemSet);
		AdvanceToNextDifferent(bag, pos);
	}
}

int main ()
{
	string bag("AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ");
	string stem;
	string::iterator It = bag.begin();

	set<string> stemSet;
	map<string, string> dict;

	CreateDictionary(dict);	
	BuildStems(7, stem, bag, It, stemSet);

	for (set<string>::iterator It = stemSet.begin(); It != stemSet.end(); ++It)
	{
		double relProb = 1.5 * CalcProb (bag, *It)/CalcProb (bag, "SATINE");	
		int usableTiles = CountUsableTiles(*It, bag, 2, dict);

		cout << (*It) << '\t' << relProb << '\t' << usableTiles << '\t' << relProb*usableTiles << endl;
	}

	return 0;
}
