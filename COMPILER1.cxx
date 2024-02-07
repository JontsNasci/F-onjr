#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

std::vector<std::string> VARIABLES;
std::vector<std::string> VALUES;

std::vector<std::string> ENDS;	  // CLOSE LINE
std::vector<std::string> DEFINES; // EQUALITARY

std::vector<std::string> OPERATORS;

// for use

std::vector<std::string> PRINTCODE;
std::vector<std::string> WCODES;
std::vector<std::string> CONSTANT_VARIABLES;

std::vector<std::string> BREAKS;
std::vector<std::string> LOOPS;
std::vector<std::string> WHILES;
//PRINTCODE
//WCODES

bool LEGACY_BACK_TRACK = false;
bool HAS_LOG = true;
bool IS_READING = false;

std::string STACK;

int LINE_NUMBER;

std::string LETTER = "abcdefghijklmnopqrstuvwxyz";
std::string CAPITAL_LETTER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string NUMBER = "1234567890";

int DEBUG_MEMORY()
{
	if (true)
	{
		int IDX = 0;
		cout << "DEBUG" << endl;
		for (std::string N : VARIABLES)
		{
			cout << N << " L " << VALUES[IDX] << endl;
			IDX++;
		}
	}
}

std::string CREATE_STRING(std::string A, int L)
{
	std::string R;
	for (size_t i = 0; i < 1; i++)
		for (char C : A)
		{
			R.push_back(C);
		}
	R.push_back(' ');
	R.push_back(L);
	return R;
}

std::string REPLACE(std::string A, std::string B, std::string C)
{
	int IDX = A.find(B);
	std::string FIRST = A.substr(0, IDX);
	std::string LAST = A.substr(IDX + B.size(), A.size());

	std::string RETURN;

	RETURN = RETURN + FIRST;
	RETURN = RETURN + C;
	RETURN = RETURN + LAST;
	return RETURN;
}

bool CONTAINS(std::string A, std::string B)
{
	return A.find(B) != std::string::npos;
}

bool HAS_END(std::string A)
{
	for (std::string B : ENDS)
		if (A.find(B) != std::string::npos)
			return true;

	return false;
}

bool HAS_DEFINE(std::string A)
{
	for (std::string DEF : DEFINES)
	{
		if (A.find(DEF) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

std::string GET_OPERATOR(std::string A)
{
	for (size_t i = 0; i < OPERATORS.size(); i++)
	{
		//std::cout << "UNABLE traxk " << A << endl;
		if (A.find(OPERATORS[i]) != std::string::npos)
		{
			return OPERATORS[i];
		}
	}
	std::string RETURN("");
	std::string RE = CREATE_STRING("UNABLE TO FIND OPERATOR AT LINE", LINE_NUMBER);
	std::cout << RE << endl;
	return RE;
}

std::string GET_VALUE1(std::string A, std::string OP)
{
	return A.substr(0, A.find(OP));
}

std::string GET_VALUE2(std::string A, std::string OP)
{
	return A.substr(A.find(OP), A.size());
}

float string_to_number(std::string A)
{
	return 1.3747;
}

std::string OPERATE_CALCULATOR(std::string A, std::string B, std::string C)
{
	//OPERATOR_LINE
	std::string RE;
	std::string X = A;
	std::string OP = B;
	std::string Y = C;
	float F = string_to_number(X);
	float J = string_to_number(Y);
	if (OP == "*")
	{
		return std::to_string(F * J);
	}
	if (OP == "-")
	{
		return std::to_string(F - J);
	}
	if (OP == "+")
	{
		return std::to_string(F + J);
	}
	if (OP == "/")
	{
		return std::to_string(F / J);
	}
	if (OP == "÷")
	{
		return std::to_string(F / J);
	}
	if (OP == "×")
	{
		return std::to_string(F * J);
	}

	return RE;
}

bool UNSOLVED(std::string A)
{
	for (std::string OP : OPERATORS)
	{
		if (A.find(OP) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

std::string CALCULATE_VARIABLES()
{
	std::string SUM;
	for (size_t i = 0; i < VALUES.size(); i++)
	{
		if (UNSOLVED(VALUES[i]))
		{
			std::string A = VALUES[i];
			//std::string SUM;
			//std::cout << "1 SHOW UP " << A << endl;
			std::string OPERATOR = GET_OPERATOR(A);
			//std::cout << "2 " << OPERATOR << endl;
			std::string VALUE1 = GET_VALUE1(A, OPERATOR);
			//std::cout << "3" << endl;
			std::string VALUE2 = GET_VALUE2(A, OPERATOR);
			//std::cout << "5" << endl;
			SUM = OPERATE_CALCULATOR(VALUE1, OPERATOR, VALUE2);
			//std::cout << "6" << endl;
			VALUES.erase(VALUES.begin() + i);
			VALUES.push_back(SUM);
			return SUM;
		}
	}
	std::string RE = CREATE_STRING("UNABLE TO TO FIND VARIABLES FINDOUT ", LINE_NUMBER);
	std::cout << RE << endl;
	return RE;
	//cout << "21" << endl;
}

std::string CALCULATE_LINE(std::string A)
{
	//std::string A = VALUES[i];
	std::string OPERATOR = GET_OPERATOR(A);
	std::string VALUE1 = GET_VALUE1(A, OPERATOR);
	std::string VALUE2 = GET_VALUE2(A, OPERATOR);
	std::string SUM = OPERATE_CALCULATOR(VALUE1, OPERATOR, VALUE2);
	//VALUES.erase(VALUES.begin() + i);
	//VALUES.push_back(SUM);
	return SUM;
}

void SEARCH_FOR(std::string A)
{
	if (LEGACY_BACK_TRACK)
		cout << "INSTRUCTION AT " << A << endl;
}

std::string CLEAN_STRING(std::string A)
{
	std::string RETURN;
	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] != ' ' and A[i] != '.')
			RETURN.push_back(A[i]);
	}
	return RETURN;
}

std::string GET_NAME(std::string A)
{
	for (std::string O : DEFINES)
	{
		if (A.find(O) != std::string::npos)
		{
			int IDX = A.find(O);

			return A.substr(0, IDX);
		}
	}
	if (LEGACY_BACK_TRACK)
		std::cout << "UNABLE TO GET NAME." << endl;
	exit(1);
	return A;
}

std::string GET_VALUE(std::string A)
{
	for (std::string O : DEFINES)
	{
		if (A.find(O) != std::string::npos)
		{
			int FIDX = 0;
			int IDX = A.find(O);
			IDX++;
			for (std::string F : ENDS)
				if (A.find(F) != std::string::npos)
					FIDX = A.find(F);
				else if (LEGACY_BACK_TRACK)
					cout << "UNFOUND GET VALUE..." << endl;
			FIDX--;
			return A.substr(IDX, FIDX);
		}
	}
	if (LEGACY_BACK_TRACK)
		std::cout << "UNABLE TO GET VALUE." << endl;
	exit(1);
	return A;
}

void PROCESS_VARIABLES()
{
	/* 	for (size_t i=0;i<VALUES)
	{
		
	}*/
}

// IS TABLE BREAK LOOP WHILE

bool IS_TABLE_BREAK(std::string A)
{
	for (size_t i = 0; i < BREAKS.size(); i++)
	{
		if (A.find(BREAKS[i]) != std::string::npos)
		{
			cout << "BREAK AT LINE " << LINE_NUMBER << endl;
		}
	}
}

bool IS_TABLE_LOOP(std::string A)
{
	for (size_t i = 0; i < LOOPS.size(); i++)
	{
		if (A.find(LOOPS[i]) != std::string::npos)
		{
			cout << "LOOP AT LINE " << LINE_NUMBER << endl;
		}
	}
}

bool IS_TABLE_WHILE(std::string A)
{
	for (size_t i = 0; i < WHILES.size(); i++)
	{
		if (A.find(WHILES[i]) != std::string::npos)
		{
			cout << "WHILE AT LINE " << LINE_NUMBER << endl;
		}
	}
}

bool IS_WCODE(std::string A)
{
	//const std::string PRINTCODE = "";
	for (size_t i = 0; i < PRINTCODE.size(); i++)
	{
		if (A.find(PRINTCODE[i]) != std::string::npos)
		{
			IS_READING = true;
			return IS_READING;
		}
	}

	if(IS_TABLE_BREAK(A))
	{
	}

	if (IS_TABLE_LOOP(A))
	{
	}

	if (IS_TABLE_WHILE(A))
	{
	}

	std::cout << "UNFOUND WCODE AT LINE " << LINE_NUMBER << endl;
	return false;
}

void OPERATE(std::string A)
{
	std::string TEMP = A;
	if (A.size() > 0)
	{
		if (!HAS_END(A))
		{
			std::cout << "EXPERMINETLA" << std::endl;
			if (HAS_DEFINE(A))
			{
				cout << "HAS_DEFINITION WITHOUT ENDS LINE " << LINE_NUMBER;
			}
			else
			{
				SEARCH_FOR("SEARCH FOR OR INSTRUCTION WCODE.");
			}
		}
		else
		{
		}
		while (HAS_END(TEMP))
		{
			cout << HAS_DEFINE(TEMP) << endl;
			if (IS_WCODE(A))
			{
			}
			else if (HAS_DEFINE(TEMP))
			{
				std::string ACTUAL_CHUNK;
				/**for (std::string E : ENDS)
					if (TEMP.find(E) != std::string::npos)
						TEMP = TEMP.substr(0, TEMP.find(E));**/
				if (LEGACY_BACK_TRACK)
					std::cout << TEMP << endl;
				std::string CLEANED = CLEAN_STRING(TEMP);
				std::string VARIABLE_NAME = GET_NAME(CLEANED);
				std::string VARIABLE_VALUE = GET_VALUE(CLEANED);
				if (true)
					cout << VARIABLE_NAME << "/" << VARIABLE_VALUE << "/" << TEMP << endl;
				//VARIABLES.push_back(VARIABLE_NAME);
				STACK = VARIABLE_VALUE;
				cout << STACK << endl;
				STACK = CALCULATE_LINE(STACK);
				if (HAS_LOG)
					cout << "ADD UP " << STACK << endl;
				VARIABLES.push_back(VARIABLE_NAME);
				VALUES.push_back(STACK);
				if (LEGACY_BACK_TRACK)
					cout << TEMP << endl;
			}
			else
				break;
			for (std::string E : ENDS)
				if (TEMP.find(E) != std::string::npos)
					TEMP = TEMP.substr(0, TEMP.find(E));
			if (HAS_LOG)
				cout << "AFTER " << TEMP << endl;
		}
	}
	//std::cout << "shsn" << endl;
	//cout << "shsh" << endl;
}

int main(int argc, char *argv[])
{
	std::string filePath = "/storage/emulated/10/Download/FIONJR";

	std::ifstream arquivo(filePath);

	ENDS.push_back(".");
	DEFINES.push_back("=");
	OPERATORS.push_back("-");
	OPERATORS.push_back("+");
	OPERATORS.push_back("*");
	OPERATORS.push_back("/");
	OPERATORS.push_back("÷");
	OPERATORS.push_back("×");

	PRINTCODE.push_back("PRINT");
	PRINTCODE.push_back("LOG");

	WCODES.push_back("LOOP");
	WCODES.push_back("FOR");
	
	CONSTANT_VARIABLES.push_back("ACTUAL INDICE");
	CONSTANT_VARIABLES.push_back("BREAK LOOP");

//BREAKS LOOPS WHILES
	BREAKS.push_back("");
	LOOPS.push_back("");
	WHILES.push_back("");

	bool LATER_CLOSE = false;
	// Verifica se o arquivo foi aberto com sucesso
	if (arquivo.is_open())
	{
		//cout << "LLO" << endl;
		// Lê e exibe cada LINE do arquivo
		std::string LINE;
		while (std::getline(arquivo, LINE))
		{
			LINE_NUMBER++;
			OPERATE(LINE);

			//cout << LINE << endl;
			//	cout << "TESTAR TODAS FUNCOES" << endl;
		}

		// Fecha o arquivo após a leitura
		arquivo.close();
	}

	else
	{
		// Exibe uma mensagem de erro se o arquivo não pôde ser aberto
		std::cerr << "Erro ao abrir o arquivo." << std::endl;
	}

	DEBUG_MEMORY();

	return 0;
}
