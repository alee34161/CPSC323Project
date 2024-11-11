#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

// TODO:
// optimize and try to make code more legible since it's so messy
// update the operator/separator/keyword lists if we are missing any
// write documentation for the assignment



// Initializing global lists and functions.
ifstream text;
ofstream result;
char opList[11] = {'+','=','-','*','/','%','<','>','!','&','|'};
char sepList[9] = {'{','}','[',']','(',')',',',';',':'};
string keywords[18] = {"if", "for", "else", "return", "get", "put", "true", "false", "int", "real", "while", "do", "case", "break", "switch", "endl", "cout", "cin"};


// FSMs for ids, int/reals, and strings
bool fsmId(string& token, const string& lexem);
bool fsmDigit(string& token, const string& lexem);
bool fsmString(string& token, const string& lexem);

// lexer itself/print function to avoid repetitive code
bool lexer(string& token, string& lexem);
void print(string& token, string& lexem) {result << '<' << token << ">\t" << lexem << endl; lexem = "";}

// a really poor work around for double operators, ex == !=, so that the lexem isnt cleared improperly
bool called = true;
bool comment = false;
char c;


int main()
{
	// open required files and intialize variables
	text.open("test.txt");
	result.open("result.txt");
	string token, lexem;

	// run lexer.
	while(!text.eof())
	{
		// if lexer FSMs/lists detect something, then output to result.txt
		if(lexer(token, lexem))
		{
			print(token, lexem);
		}
	}

	// close files
	text.close();
	result.close();
	return 0;
}


bool lexer(string& token, string& lexem)
{
	if(called)
	{
		text.get(c);
	}
	called = false;
	
	// This is to recognize and ignore comments
	if(c == '[' && text.peek() == '*')
	{
		comment = true;
		called = true;
		return false;
	} else if(c == '*' && text.peek() == ']')
	{
		comment = false;
		text.get(c);
		called = true;
		return false;
	}
	if(comment)
	{
		called = true;
		return false;
	}
	// This horrible mess is to catch operators such as == which would otherwise be read as two separate =
	switch(c)
	{
		case '=':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '=')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;
		}
		break;
		case '!':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '=')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;
		}
		break;
		case '<':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '=' || text.peek() == '<')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;
		}
		break;
		case '>':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '=' || text.peek() == '>')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;
		}
		break;
		case '+':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '+' || text.peek() == '=')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;
		}
		break;
		case '-':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '-' || text.peek() == '=')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;
		}
		break;
		case '&':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '&')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;			
		}
		break;
		case '|':
		if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
		{
			return true;
		}
		if(text.peek() == '|')
		{
			lexem = c;
			text.get(c);
			lexem += c;
			token = "operator";
			called = true;
			return true;		
		}
		break;
	}
	

	// If the next character is a whitespace, run the current lexem through the FSMs.
	if(isspace(c))
	{
		if(lexem != "")
		{
			if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
			{
				return true;
			} else
			{
				token = "unknown";
				return true;
			}
		}
		called = true;
		return false;
	}

	// Check to see if c is in the operator list and print/clear lexem.
	for(char i : opList)
	{
		if(c == i)
		{
			if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
			{
				return true;
			} else if(lexem != "")
			{
				token = "unknown";
				return true;
			}
			lexem = c;
			token = "operator";
			called = true;
			return true;
			break;
		}
	}

	// Check to see if c is in the separator list and print/clear lexem.
	for(char i : sepList)
	{
		if(c == i)
		{
			if(fsmDigit(token, lexem) || fsmId(token, lexem) || fsmString(token, lexem))
			{
				return true;
			} else if(lexem != "")
			{
				token = "unknown";
				return true;
			}
			lexem = c;
			token = "separator";
			called = true;
			return true;
			break;
		} 
	} 

	// If the operator/separator lists were not used, then add the character to the lexem for next iteration and set token to unused for RDP

	called = true;
	lexem += c;
	token = "unused";
	
	return false;
}



bool fsmString(string& token, const string& lexem)
{
	// 0=starting, 1=characters, 2=success, 3=failure
	int currentState = 0;

	for(char c : lexem)
	{
		switch(currentState)
		{
			case 0:
			if(c == '"')
			{
				currentState = 1;
			} else
			{
				currentState = 3;
			}
			break;
			case 1:
			if(c == '"')
			{
				currentState = 2;
			}
			break;
			case 2:
			currentState = 3;
			break;
			case 3:
			break;
		}
	}

	if(currentState == 2)
	{
		token = "string";
		return true;
	}

	return false;
}

bool fsmDigit(string& token, const string& lexem)
{
	// 0=starting, 1=int, 2=real, 3=period, 4=failure
	int currentState = 0;

	for(char c : lexem)
	{
		switch(currentState)
		{
			case 0:
			if(isdigit(c))
			{
				currentState = 1;
			} /*else if(c == '.')	// This cover .d+ for real numbers, but is not listed in the compiler project definitions
			{
				currentState = 3;
			} */else
			{
				currentState = 4;
			}
			break;
			case 1:
			if(isdigit(c))
			{
				currentState = 1;
			} else if(c == '.')
			{
				currentState = 3;
			} else
			{
				currentState = 4;
			}
			break;
			case 2:
			if(isdigit(c))
			{
				currentState = 2;
			} else
			{
				currentState = 4;
			}
			break;
			case 3:
			if(isdigit(c))
			{
				currentState = 2;
			} else
			{
				currentState = 4;
			}
			break;
			case 4:
			return false;
		}
	}

	if(currentState == 1)
	{
		token = "integer";
		return true;
	} else if(currentState == 2)
	{
		token = "real";
		return true;
	}
	return false;
}

bool fsmId(string& token, const string& lexem)
{
	int currentState = 0;

	// Check if lexem is a keyword first
	for(string word : keywords)
	{
		if(lexem == word)
		{
			token = "keyword";
			return true;
		}
	}

	// 0=starting, 1=first l, 2=middle characters, 3=final l, 4=failure
	for(char c : lexem)
	{
		switch(currentState)
		{
			case 0:
			if(isalpha(c))
			{
				currentState = 1;
			} else
			{
				currentState = 4;
			}
			break;
			case 1:
			if(isalpha(c) || isdigit(c))
			{
				currentState = 2;
			} else
			{
				currentState = 4;
			}
			break;
			case 2:
			if(isalpha(c))
			{
				currentState = 3;
			} else if(!isdigit(c))
			{
				currentState = 4;
			}
			break;
			case 3:
			if(isdigit(c))
			{
				currentState = 2;
			}
		}
	}

	if(currentState == 1 || currentState == 3)
	{
		token = "identifier";
		return true;
	}
	return false;
}
