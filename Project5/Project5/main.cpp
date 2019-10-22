#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

const string WORDLIST_FILE = "wordlist.txt";

string encrypt(string plaintext)
{
	  // Generate a to z
    char plaintextAlphabet[26+1];
	iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
	plaintextAlphabet[26] = '\0';

	  // Generate permutation
	string ciphertextAlphabet(plaintextAlphabet);
	default_random_engine e((random_device()()));
	shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);

	  // Run translator (opposite to the intended direction)
	Translator t;
	t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
	return t.getTranslation(plaintext);
}

bool decrypt(string ciphertext)
{
	Decrypter d;
	if ( ! d.load(WORDLIST_FILE))
	{
		cout << "Unable to load word list file " << WORDLIST_FILE << endl;
		return false;
	}
	for (const auto& s : d.crack(ciphertext))
		cout << s << endl;
	return true;
}

int main(int argc, char* argv[])
{
	if (argc == 3  &&  argv[1][0] == '-')
	{
		switch (tolower(argv[1][1]))
		{
		  case 'e':
			cout << encrypt(argv[2]) << endl;
			return 0;
		  case 'd':
			if (decrypt(argv[2]))
				return 0;
			return 1;
		}
	}

	cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
	cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
	return 1;
}
/*#include"Myhash.h"
#include <iostream>
#include<string>
using namespace std;

int main()
{
	MyHash<int, string> hash;
	for (int i = 0; i < 1019; i++)
	{
		hash.associate(i*10-3+5*i-i/7, "hi");
	}
	hash.print();

}


#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

void main()
{
	WordList wl;
	if (!wl.loadWordList("wordlist.txt")) { cout << "Unable to load word list" << endl;         return; }
	else cout << "YES" << endl;
	if (wl.contains("Please"))         cout << "it's" << endl;     else         cout << "Onomatopoeia is not in the word list!" << endl;
	string cipher = "xyqbbq";
	string decodedSoFar = "?r????";
	vector<string> v = wl.findCandidates(cipher, decodedSoFar);
	if (v.empty())         cout << "No matches found" << endl;
	else
	{
		cout << "Found these matches:" << endl;         for (size_t k = 0; k < v.size(); k++)             cout << v[k] << endl;  // writes grotto and troppo     
	}
	vector<string> v = wl.findCandidates("Lcdkgd", "P?e??e");
}*/

