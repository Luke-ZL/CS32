#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

string pattern(string& value)
{
	int numLettters = 0;
	char count[26];
	string key;
	for (int i = 0; i < 26; i++)
		count[i] = '?';
	for (int i = 0; i < value.size(); i++)
	{
		if (value[i] == '\'') {
			key += value[i];
			continue;
		}
		value[i] = tolower(value[i]);
		if (count[value[i] - 'a'] == '?') {
			count[value[i] - 'a'] = 'a' + numLettters;
			numLettters++;
			key += count[value[i] - 'a'];
		}
		else key += count[value[i] - 'a'];
	}
	return key;
}

bool isword(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if ((s[i] != '\'') && (!isalpha(s[i]))) return false;
	}
	return true;
}

/*string tolow(string value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = tolower(value[i]);
	}
	return value;
}*/

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
	MyHash<string,vector<string>> m_list;
};

bool WordListImpl::loadWordList(string filename)
{
	//m_list.clear();
	m_list.reset();
	string s;
	ifstream infile(filename);    // infile is a name of our choosing
	if (!infile)		        // Did opening the file fail?
	{
		cerr << "Error: Cannot open data.txt!" << endl;
		return false;
	}
	while (getline(infile, s))
	{
		if (!isword(s)) continue;
		string key = pattern(s);
		//cout << s << endl;
		vector<string>* value;
		if (m_list.find(key) != nullptr) {
			value = m_list.find(key);
			value->push_back(s);
		}
	    /*for (int i = 0; i < value.size(); i++)
		{
			cout << value[i] << endl;
		}*/
		else {
			vector<string> newvalue;
			newvalue.push_back(s);
			m_list.associate(key, newvalue);
		}
	}
	return true;
   
}

bool WordListImpl::contains(string word) const
{
	string key = pattern(word);
	const vector<string>* value;
	if (m_list.find(key) == nullptr) return false;
	else value = m_list.find(key);
	for (int i = 0; i < (*value).size(); i++)
	{
		if ((*value)[i] == word) return true;
	}
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	string key = pattern(cipherWord);
	const vector<string>* value;
	vector<string> valueRe;
	if (m_list.find(key) == nullptr) return vector<string>();
	else value = m_list.find(key);
	for (int i = 0; i < (*value).size(); i++)
	{
		bool checker = true;
		for (int j = 0; j < currTranslation.size(); j++)
		{
			if ((currTranslation[j] != '?') && (tolower(currTranslation[j]) != tolower((*value)[i][j]))) {
				checker = false;
				break;
			}
		}
		if (checker == true) valueRe.push_back((*value)[i]);
	}
	return valueRe;
}

//***** hash functions for string, int, and char *****

unsigned int hasher(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hasher(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hasher(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}

