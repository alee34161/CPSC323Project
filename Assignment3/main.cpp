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

	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << instructions[i][j] << "\t";
		}
	}
	// close files
	text.close();
	result.close();
	return 0;
}
