import re

# Define keywords, operators, and separators
keywords = ["function", "integer", "boolean", "real", "if", "else", "fi", "return", "put", "get", "while", "true", "false"]
operators = ['|', '==', '!=', '<', '<=', '>', '=>', '+', '-', '*', '/', '%']
separators = ['(', ')', ';', '{', '}', '@']


def identifier_fsm(s: str) -> bool:
	'''Finite state machine that determines if a string is an identifier'''
	state = 'Start'

	if len(s) == 1 and s.isalpha():
		return True

	for i, ch in enumerate(s):
		if state == 'Start':
			if ch.isalpha():
				state = 'Middle'
			else:
				return False

		elif state == 'Middle':
		# Middle characters can be letters or digits
			if ch.isdigit():
				continue
			elif ch.isalpha():
				if i == len(s) - 1:
					state = 'End'  # Last character must be a letter
			else:
				return False

		elif state == 'End':
		# Once we reach the end state, the string is valid
			break

	return state == 'End'  # The FSM is only valid if it ends in 'End'


def integer_fsm(num: str) -> bool:
	'''Finite state machine that determines if a string is an integer'''
	state = 'Start'

	if len(num) == 1 and num.isdigit():
		return True

	for i, ch in enumerate(num):
		if ch.isdigit():
			if i == len(num) - 1:
				return True
		else:
			return False


def real_fsm(num: str) -> bool:
	'''Finite state machine that determines if a string is a real number'''
	if '.' not in num:
		return False

	state = 'Start'
	for i, ch in enumerate(num):
		if state == 'Start':
			if ch.isdigit():
				state = 'Middle'
			else:
				return False

		elif state == 'Middle':
		# Middle characters must be digits
			if ch.isdigit():
				if i == len(num) - 1:
					state = 'End'  # Last character must be a number
			elif ch == '.':
				continue
			else:
				return False

		elif state == 'End':
		# Once we reach the end state, the string is valid
			break

	return state == 'End'  # The FSM is only valid if it ends in 'End'


def lexer(lexemes, result):
	'''Lexical analyzer that takes a list of lexemes as input and outputs its result to a given file'''
	for lexeme in lexemes:
		
		# Filter out keywords
		for keyword in keywords:
			if keyword in lexeme:
				result.write(f'keyword: {keyword}\n')
				lexeme = lexeme.replace(keyword, '').strip()
		
		# Filter out operators
		for operator in operators:
			if operator in lexeme:
				result.write(f'operator: {operator}\n')
				lexeme = lexeme.replace(operator, ''). strip()

		# Filter out separators
		for separator in separators:
			if separator in lexeme:
				result.write(f'separator: {separator}\n')
				lexeme = lexeme.replace(separator, '').strip()

		# Find identifiers
		if identifier_fsm(lexeme):
				result.write(f'identifier: {lexeme}\n')

		# Find integers
		if integer_fsm(lexeme):
			result.write(f'integer: {lexeme}\n')

		# Find real numbers
		if real_fsm(lexeme):
			result.write(f'real: {lexeme}\n')

	result.write('\n***** Analysis Complete *****\n')


def main(filename, testcase_num=1):
	# Open the file containing the source code to be analysed
	with open(filename, 'r') as testcase:
		source_code = testcase.read()
		source_code = re.sub('\[\*.*?\*\]', '', source_code) # Remove comments from code
		lexemes = source_code.split(' ') # Split code using whitespace as the delimiter

	# Open the file to be outputed to
	with open(f'result{testcase_num}.txt', 'w') as result:
		result.write(f'\nLexical Analysis for {filename}\n')
		result.write('*' * 35 + '\n')

		# Perfrom lexical analysis
		lexer(lexemes, result)


if __name__ == '__main__':
		main('test_1.txt', 1)
		main('test_2.txt', 2)
		main('test_3.txt', 3)
