#include "source.h"
#include <iomanip>

int main()
{
	// open required files and intialize variables
	text.open("test.txt");
	if(!text.is_open())
	{
		cout << "\n\nError, missing test.txt or unable to open.\n";
		return 1;
	}
	
	result.open("parserResults.txt");
	ofstream instruc;
	instruc.open("assemblyCode.txt");

	rat24F();

	instruc << left << setw(20) << "====================================================\nInstruction Table\n====================================================\nAddress\t\t\tOp\t\t\tOprnd\n"; 
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
					instruc << endl;
				}
			} else
			{
				instruc << left << setw(20) << instructions[i][j] << "\t";
				if(j == 2)
				{
					instruc << "\n";
				}
			}
		}
	}

	instruc << left << setw(20) << "\n\n====================================================\nSymbol Table\n====================================================\nIdentifier\tMemory Location\tType\n";
	int number = 9000;
	for(int i = 0; i < 1000; i++)
	{
		string s = symbols[i][0];
		if(s == "")
		{
			continue;
		}
		instruc << left << setw(20) << s << number << "\t" << symbols[i][1] << endl;
		number++;
	}


	
	// close files
	text.close();
	result.close();
	instruc.close();
	return 0;
}
