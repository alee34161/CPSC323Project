#include "lexer.cpp"

void syntaxError()
{
	result << "\nSYNTAX ERROR DETECTED ON LINE " << lineNumber << "\nillegal lexeme: " << lexem << ", token type: " << token;
}
void rat24F();
void optFuncDef();
void funcDef();
void function();
void optParList();
void parList();
void parameter();
void qualifier();
void body();
void optDecList();
void decList();
void declaration();
void ids();
void stateList();
void statement();
void compound();
void assign();
void ifstatement();
void returnstatement();
void printstatement();
void scanstatement();
void whilestatement();
void condition();
void relop();
void expression();
void expressionprime();
void term();
void termprime();
void factor();
void primary();
void empty();

void rat24F()
{
	while(!lexer(token, lexem));
	print(token, lexem);
	print("\t<Rat24F> -> <Opt Function Definitions> @ <Opt Declaration List> <Statement List> @");
	optFuncDef();
	if(!(lexem == "@"))
	{
		syntaxError();
		return;
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);


	}
	optDecList();
	stateList();
	if(!(lexem == "@"))
	{
		syntaxError();
		return;
	} else
	{
		clearLexeme();
	}
}

void optFuncDef()
{
	print("\t<Opt Function Definitions> -> <Function Definitions> | <Empty>");
	if(lexem == "function")
	{
		funcDef();
	} else 
	{
		empty();
	}
}

void funcDef()
{
	print("\t<Function Definitions> -> <Function> | <Function> <Function Definitions");
	function();
	if(lexem == "function")
	{
		funcDef();
	}
}

void function()
{
	print("\t<Function> -> function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>");
	if(lexem != "function")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(token != "identifier")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			if(lexem != "(")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
				optParList();
				if(lexem != ")")
				{
					syntaxError();
				} else
				{
					clearLexeme();
					while(!lexer(token, lexem));
					print(token, lexem);
					optDecList();
					body();
				}
			}
		}
	}
}

void optParList()
{
	print("\t<Opt Parameter List> -> <Parameter List> | <Empty>");
	if(token != "identifier")
	{
		empty();
	} else
	{
		parList();
	}
}

void parList()
{
	print("\t<Parameter List> -> <Parameter> | <Parameter> , <Parameter List>");
	parameter();
	if(lexem == ",")
	{
		parList();
	}
}

void parameter()
{
	print("\t<Parameter> -> <IDs> <Qualifier>");
	ids();
	qualifier();
}

void qualifier()
{
	print("\t<Qualifier> -> integer | boolean | real");
	if(lexem != "integer" && lexem != "boolean" && lexem != "real")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
	}
}

void body()
{
	print("\t<Body> -> { <Statement List> }");
	if(lexem != "{")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		stateList();
		if(lexem != "}")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		}
	}
}

void optDecList()
{
	print("\t<Opt Declaration List> -> <Declaration List> | <Empty>");
	if(lexem != "integer" && lexem != "boolean" && lexem != "real")
	{
		empty();
	} else
	{
		decList();
	}
}
 void decList()
 {
 	print("\t<Declaration List> -> <Declaration> ; | <Declaration> ; <Declaration List>");
 	declaration();
 	if(lexem != ";")
 	{
 		syntaxError();
 	} else
 	{
 		clearLexeme();
 		while(!lexer(token, lexem));
 		print(token, lexem);
		if(lexem != "integer" && lexem != "boolean" && lexem != "real")
		{
			return;
		} else
		{
			decList();
		}
 	}
 }

void declaration()
{
	print("\t<Declaration> -> <Qualifier> <IDs>");
	qualifier();
	ids();
}

void ids()
{
	print("\t<IDs> -> <Identifier> | <Identifier> , <IDs>");
	if(token != "identifier")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem == ",")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			ids();
		}
	}
}

void stateList()
{
	print("\t<Statement List> -> <Statement> | <Statement> <StatementList>");
	statement();
	if(lexem != "{" && token != "identifier" && lexem != "if" && lexem != "return" && lexem != "put" && lexem != "get" && lexem != "while")
	{
		return;
	} else
	{
		stateList();
	}
}

void statement()
{
	print("\t<Statement> -> <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>");
	if(token == "identifier")
	{
		assign();
	} else if(lexem == "{")
	{
		compound();
	} else if(lexem == "if")
	{
		ifstatement();
	} else if(lexem == "return")
	{
		returnstatement();
	} else if(lexem == "put")
	{
		printstatement();
	} else if(lexem == "get")
	{
		scanstatement();
	} else if(lexem == "while")
	{
		whilestatement();
	} else
	{
		syntaxError();
	}
}

void compound()
{
	print("\t<Compound> -> { <Statement List> }");
	if(lexem != "{")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		stateList();
		if(lexem != "}")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		}
	}
}

void assign()
{
	print("\t<Assign> -> <Identifier> = <Expression> ;");
	if(token != "identifier")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem != "=")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			expression();
			if(lexem != ";")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
			}
		}
	}
}

void ifstatement()
{
	print("\t<If> -> if ( <Condition> ) <Statement> fi | if ( <Condition> ) <Statement> else fi");
	if(lexem != "if")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem != "(")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			condition();
			if(lexem != ")")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
				statement();
				if(lexem == "else")
				{
					clearLexeme();
					while(!lexer(token, lexem));
					print(token, lexem);
					statement();
				}
				if(lexem != "fi")
				{
					syntaxError();
				} else
				{
					clearLexeme();
					while(!lexer(token, lexem));
					print(token, lexem);
				}
			}
		}
	}
}

void returnstatement()
{
	print("\t<Return> -> return ; | return <Expression> ;");
	if(lexem != "return")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem == "-" || token == "identifier" || token == "integer" || lexem == "(" || token == "real" || lexem == "true" || lexem == "false")
		{
			expression();
		}
		if(lexem != ";")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		}
	}
}

void printstatement()
{
	print("\t<Print> -> put ( <Expression> ) ;");
	if(lexem != "put")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem != "(")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			expression();
			if(lexem != ")")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
				if(lexem != ";")
				{
					syntaxError();
				} else
				{
					clearLexeme();
					while(!lexer(token, lexem));
					print(token, lexem);
				}
			}
		}
	}
}

void scanstatement()
{
	print("\t<Scan> -> get ( <IDs> ) ;");
	if(lexem != "get")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem != "(")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			ids();
			if(lexem != ")")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
				if(lexem != ";")
				{
					syntaxError();
				} else
				{
					clearLexeme();
					while(!lexer(token, lexem));
					print(token, lexem);
				}
			}
		}
	}
}

void whilestatement()
{
	print("\t<While> -> while ( <Condition> ) <Statement>");
	if(lexem != "while")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		if(lexem != "(")
		{
			syntaxError();
		} else
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			condition();
			if(lexem != ")")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
				statement();
			}
		}
	}
}

void condition()
{
	print("\t<Condition> -> <Expression> <Relop> <Expression>");
	expression();
	relop();
	expression();
}

void relop()
{
	print("\t<Relop> -> == | != | > | < | <= | =>");
	if(lexem != "==" && lexem != "!=" && lexem != ">" && lexem != "<" && lexem != "<=" && lexem != "=>")
	{
		syntaxError();
	} else
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
	}
}

void expression()
{
	print("\t<Expression> -> <Term> <ExpressionPrime> | <Term>");
	term();
	if(lexem == "+" || lexem == "-")
	{
		expressionprime();
	}
}

void expressionprime()
{
	print("\t<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>");
	if(lexem == "+" || lexem == "-")
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		term();
		expressionprime();
	} else
	{
		empty();
	}
}

void term()
{
	print("\t<Term> -> <Factor> <TermPrime>");
	factor();
	termprime();
}

void termprime()
{
	print("\t<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>");
	if(lexem == "*" || lexem == "/")
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
		factor();
		termprime();
	} else
	{
		empty();
	}
}

void factor()
{
	print("\t<Factor> -> - <Primary> | <Primary>");
	if(lexem == "-")
	{
		clearLexeme();
		while(!lexer(token, lexem));
		print(token, lexem);
	}
	primary();
}

void primary()
{
	print("\t<Primary> -> <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false");
	if(token != "identifier" && token != "integer" && token != "real" && lexem != "(" && lexem != "true" && lexem != "false")
	{
		syntaxError();
	} else
	{
		if(token == "identifier")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			if(lexem == "(")
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
				ids();
				if(lexem != ")")
				{
					syntaxError();
				} else
				{
					clearLexeme();
					while(!lexer(token, lexem));
					print(token, lexem);
				}
			}
		} else if(token == "integer")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		} else if(token == "real")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		} else if(lexem == "(")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
			expression();
			if(lexem != ")")
			{
				syntaxError();
			} else
			{
				clearLexeme();
				while(!lexer(token, lexem));
				print(token, lexem);
			}
		} else if(lexem == "true")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		} else if(lexem == "false")
		{
			clearLexeme();
			while(!lexer(token, lexem));
			print(token, lexem);
		}
	}
}

void empty()
{
	print("\t<Empty> -> epsilon");
	return;
}
