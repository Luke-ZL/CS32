#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
	DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
	WordList m_list;
	Tokenizer m_token;
	Translator m_trans;
	int countUnknown(string s)
	{
		int count = 0;
		string trans = m_trans.getTranslation(s);
		for (int i = 0; i < trans.size(); i++)
		{
			if (trans[i] == '?') count++;
		}
		return count;

	}

	int mostUnknown(const vector<string>& v)
	{
		int max = 0;
		int index = -1;
		for (int i = 0; i < v.size(); i++)
		{
			if (countUnknown(v[i]) >= max) {
				index = i;
				max = countUnknown(v[i]);
			}
		}
		return index;
	}

	bool checkComplete(string s)
	{
		for (int i = 0; i < s.size(); i++)
			if (s[i] == '?') return false;
		return true;
	}

	string removeApo(string s)
	{
		for (int i = 0; i < s.size(); i++)
			if (s[i] == '\'') s.erase(i, 1);
		return s;
	}
	
};

DecrypterImpl::DecrypterImpl()
	:m_token(",;:.!()[]{}-\"#$%^& 0123456789"){}

bool DecrypterImpl::load(string filename)
{
	return m_list.loadWordList(filename); 
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> finalSolutions;

	vector<string> cypher;
	cypher = m_token.tokenize(ciphertext);
	int index = mostUnknown(cypher); 
	//cout << cypher[index] << ' ';
	string translated = m_trans.getTranslation(cypher[index]);
	//if (m_trans.getTranslation(cypher[1]) == "encrypt") cout << cypher[index] << ' ' << translated;

	vector<string> solutions = m_list.findCandidates(cypher[index], translated);
	//cout << cypher[index] << ' '<<translated<< ' ';

	/*for (int i = 0; i < solutions.size(); i++)
	{
		if  (solutions[i].size() ==5)cout << solutions[i] << endl;
	}
	return vector<string>();*/

	//for (int i = 0; i < solutions.size(); i++)
		//if (solutions[i] == "please") cout << "YES";

	if (solutions.empty()) {
		m_trans.popMapping();
		return vector<string>();
	}

	else {
		for (int i = 0; i < solutions.size(); i++)
		{
			//cout << solutions[i] << endl;
			bool check = true;
			bool checkAll = true;

			/*if (solutions[i] == "please") {
				m_trans.print();
				cout << "hi" << endl;
			}
			
			cout << "BEFORE" << endl;
			m_trans.print();
			cout << removeApo(solutions[i]) << endl;*/

			if (!m_trans.pushMapping(removeApo(cypher[index]), removeApo(solutions[i]))) continue;

			/*cout << "AFTER" << endl;
			m_trans.print();

			if (solutions[i] == "please") {
				m_trans.print();
				cout << "hi" << endl;
			}*/

			string nextStage = m_trans.getTranslation(ciphertext);
			vector<string> cypherNext = m_token.tokenize(nextStage);

			//cout << nextStage<<' ';

			for (int j = 0; j < cypherNext.size(); j++)
				if (checkComplete(cypherNext[j]) && (!m_list.contains(cypherNext[j]))) {
					check = false;
					break;
				}

			if (check == false) {
				m_trans.popMapping();
				continue;
			}

			for (int j = 0; j < cypherNext.size(); j++)
				if (!checkComplete(cypherNext[j])) {
					checkAll = false;
					break;
				}

			
			if (checkAll == false) {
				//cout << nextStage << endl;;
				//exit(1);
				vector<string> tmp = crack(ciphertext);
				finalSolutions.insert(finalSolutions.end(), tmp.begin(), tmp.end());
			}
			else {
				finalSolutions.push_back(nextStage);
				//cout << nextStage; 
				m_trans.popMapping();
			}
		}
	}

	m_trans.popMapping();
	sort(finalSolutions.begin(), finalSolutions.end());
	// sort
	return finalSolutions;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
