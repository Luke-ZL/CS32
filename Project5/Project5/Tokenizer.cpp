#include "provided.h"
#include <string>
#include <vector>

using namespace std;

bool notInside(char c, const string& s)
{
	for (int i = 0; i < s.size(); i++)
		if (c == s[i]) return false;
	return true;
}

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
	string seperator;
};

TokenizerImpl::TokenizerImpl(string separators)
	:seperator(separators)
{
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
	vector<string> list;
	int wordcount = 0;
	bool check = false;
	for (int i = 0; i < s.size();i++)
	{
		if (notInside(s[i], seperator))
		{
			if (check == false) {
				wordcount++;
				list.push_back("");
				list[wordcount - 1] += s[i];
				check = true;
			}
			else list[wordcount - 1] += s[i];
		}
		else check = false;
	}
    return list; 
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}

/*int main()
{
	TokenizerImpl	t(",;:.!()[]{}-\"#$%^& ");
	vector<string>	v = t.tokenize("Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn");
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	string	s = "!!!!!";
	v = t.tokenize(s);
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
}*/