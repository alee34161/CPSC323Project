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
	cout << endl;
	for(int i = 0; i < 1000; i++)
	{
		if(instructions[i][0] == "")
		{
			continue;
		}
		for(int j = 0; j < 3; j++)
		{
			if(instructions[i][j] == "nil")
			{
				if(j == 2)
				{
					cout << endl;
				}
				continue;
			}
			cout << instructions[i][j] << "\t";
			if(j == 2)
			{
				cout << "\n";
			}
		}
	}
	// close files
	text.close();
	result.close();
	return 0;
}
