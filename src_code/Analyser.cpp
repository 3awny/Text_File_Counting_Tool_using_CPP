#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

int isWord(string &);
int geSentenceType(string &);
void readAnalyzeFile(string);

int main()
{
	string fileName;
	cout << "Please, enter your file name : " << endl;
	cin >> fileName;
	
	readAnalyzeFile(fileName);
	
	system("pause");
	return 0;
}

/*
Functionality: checks whether the input string considered as a word or not, 
a string will be considered a word if all chars
are letters and may terminate with ',' '.' '?' or '!' 
Special Case: if the string contains atleast one punctuation character then it's not a word

Function Name: isWord
Function Inputs: string
Function output: int value either 
	0(it is not a word), 
	1(a word containing letters only), 
	2(a word terminated with a punctuation character)
*/
int isWord(string & s)
{
	if (s.length() == 1 && (s[0] == ',' || s[0] == '.' || s[0] == '?' || s[0] == '!'))
	{
		return 0;
	}
	// Loop on the given string
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		{
			continue;					// if it's a letter then continue searching
		}
		else if((s[i] == ',' || s[i] == '.' || s[i] == '?' || s[i] == '!') && (i == s.length()-1))
		{			
			return 2;					// if it's a punctuation character that occurs at the end of string, then it's ok
		}
		else
		{
			return 0;					// otherwise return 0
		}
	}
	return 1;							// the whole string is ok return 1
}

/*
Functionality: checks whether the input string is considered as an end of sentence or not, 
a string will be considered as a end of sentence if it ends with '.' '?' or '!' 
Special Case: if the string contains only one character then it's not a sentence

Function Name: geSentenceType
Function Inputs: string
Function output: int value either 
	0(it is not a sentence), 
	1(a normal sentence), 
	2(an exclamatory sentence),
	3(an interrogative sentence)
*/
int geSentenceType(string & s)
{
	int i = s.length()-1;
	if (s.length() > 1)
	{
		if (s[i] == '.')
			return 1;
		else if (s[i] == '?')		
			return 2;
		else if (s[i] == '!')		
			return 3;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

/*
Functionality: reads and parses the given file to count and print number of characters, 
text objects, words, sentences, exclamatory sentences and interrogative sentences
Special Case: if the file is not found then it prints an error message

Function Name: readAnalyzeFile
Function Inputs: string
Function output: no return 
*/
void readAnalyzeFile(string fileName)
{
	ifstream in(fileName);
	if (!in.is_open())
	{
		cout << "Specified File Not Found!" << endl;
		return;
	}
	
	string text;								// the last read string
	
	int charCount = 0;							// a counter for each type of analysis
	int textCount = 0;
	int wordCount = 0;
	int sentenceCount = 0;
	int excCount = 0;	
	int interCount = 0;	
	
	bool stillSentence = true;					// a flag to indicate whether a sequence of words 
												// still form a sentence or not

	while (!in.eof())
	{
		in >> text;				
		charCount = charCount + text.length() + 1;	// to count number of chars in each string
		textCount++;								// since each string considered as a text
		int check = isWord(text);					// check if this string is a word
		int type = geSentenceType(text);			// check if this string is a end of sentence

		if (check != 0)						
		{
			wordCount++;						// to count number of words		
			if (type >= 1)						// increment the corresponding sentence type
			{
				if (stillSentence && type == 1)
					sentenceCount++;
				else if (stillSentence && type == 2)
					excCount++;
				else if (stillSentence && type == 3)
					interCount++;
				else
					stillSentence = true;
			}			
		}
		else
		{
			if (type == 0)
			{
				stillSentence = false;
			}			
		}
	}
	in.close();
	charCount--;									// to account for the last space i.e. exclude the eof character
	// print all analysis data
	cout << setw(26) << "Analysis of <" << fileName << ">" << endl;
	cout << "Number of characters in the file              : " << setw(5) << charCount << endl << endl;
	cout << "Number of text objects in the file            : " << setw(5) << textCount << endl << endl;
	cout << "Number of words in the file                   : " << setw(5) << wordCount << endl << endl;
	cout << "Number of sentences in the file               : " << setw(5) << sentenceCount << endl << endl;
	cout << "Number of exclamatory sentences in the file   : " << setw(5) << excCount << endl << endl;
	cout << "Number of interrogative sentences in the file : " << setw(5) << interCount << endl << endl;
}