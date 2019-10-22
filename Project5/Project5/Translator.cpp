#include "provided.h"
#include <string>
#include <cctype>
#include <vector>

using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl ();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;


private:
	vector<string> maps;
	string current;
	int map_count;

	

	bool checkAlpha(string s)
	{
		for (int i = 0; i < s.size(); i++)
			if (!isalpha(s[i])) return false;
		return true;
	}
	bool checkExist(char c)
	{
		for (int i = 0; i < current.size(); i++)
			if (current[i] == c) return true;
		return false;
	}
};

TranslatorImpl::TranslatorImpl()
{
	for (int i = 0; i < 26; i++)
		current += '?';
	map_count = 1;
}



bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.size() != plaintext.size()) return false;
	if ((!checkAlpha(ciphertext)) || (!checkAlpha(plaintext))) return false;
	string tmpcurrent = current;
	string tmp = current;
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if (tmpcurrent[tolower(ciphertext[i]) - 'a'] == '?')
		{
			if (!checkExist(toupper(plaintext[i]))) tmpcurrent[tolower(ciphertext[i]) - 'a'] = toupper(plaintext[i]);
			else return false;
		}
		else if (tmpcurrent[tolower(ciphertext[i]) - 'a'] != toupper(plaintext[i])) return false;		
	}
	maps.push_back(tmp);
	map_count++;
	current = tmpcurrent;

	/*char c;
	for (int i = 0; i < 26; i++)
	{
		c = 'A' + i;
		cout << c;
	}
	cout << endl;
	cout << current << endl;*/

	return true;
}

bool TranslatorImpl::popMapping()
{
	if (map_count <= 1) return false;
	else {
		current = maps.back();
		map_count--;
		maps.pop_back();

		/*char c;
		for (int i = 0; i < 26; i++)
		{
			c = 'A' + i;
			cout << c;
		}
		cout << endl;
		cout << current << endl;*/


		return true;  
	}


}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{

	string result;
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if (islower(ciphertext[i])) result += tolower(current[ciphertext[i] - 'a']);
		else if (isupper(ciphertext[i])) result += current[ciphertext[i] - 'A'];
		else result += ciphertext[i];
	}
	return result;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}



