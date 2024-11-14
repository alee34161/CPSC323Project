#include "source.h"

int main()
{
	// open required files and intialize variables
	text.open("test.txt");
	result.open("result.txt");

	// run lexer.
	/*while(!text.eof())
	{
		// if lexer FSMs/lists detect something, then output to result.txt
		if(lexer(token, lexem))
		{
			print(token, lexem);
		}
	}*/

	rat24F();

	// close files
	text.close();
	result.close();
	return 0;
}
