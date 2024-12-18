//Project Calculator with functional like in engineer calculator of Windows.
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <locale>

//#include <HeaderCheckIfDigitFunc.h>

using namespace std;

bool IsDigit(const string& other) {
	bool hasDecimalPoint = false;

	for (size_t i = 0; i < other.size(); i++) {
		char ch = other[i];

		if (ch == '.') {
			if (hasDecimalPoint == true) return false;
			hasDecimalPoint = true;
		}
		else if (ch < '0' || ch > '9') {
			return false;
		}
	}
	return true;
}

class MathFunctions {
	//Creating Varuebles 
	int amountOfValues;
	int amountOfNumbers;
	int amountOfOpsPriority;
	int amountOfOperators;
	int amountOfVaruablesSubArray;
	int maxPriorityIndex;
	string* memoryArrey = new string[amountOfValues]; //General Array for User's String
	float* numberArrey = new float[amountOfNumbers]; // Array for user operands from strings in memoryArray
	string* charOperatorArrey = new string[amountOfOperators]; // Array for all operators from memoryArray
	int* strOpsPriorityArr = new int[amountOfOpsPriority]; // Array for prioritiers for operators
	string* subExpressionArray = new string[amountOfVaruablesSubArray];

	//3 Arrays for sub expression


public:

	MathFunctions() { // Constructor with parameters
		amountOfValues = 0;
		amountOfOpsPriority = 0;
		amountOfNumbers = 0;
		amountOfOperators = 0;

	}

	//---------------------

	void MathOperations() { // Math operations
		double result = 0.0;
		int FirstIndexBracket = -1;
		int SecondIndexBracket = -1;
		int maxPriorityIndex = 0;
		int counterForSubExpression = 0;





		while (amountOfOpsPriority > 0) {

			for (int i = 0; i < amountOfOpsPriority; i++) {
				if (strOpsPriorityArr[i] < strOpsPriorityArr[maxPriorityIndex]) {
					maxPriorityIndex = i;
				}
			}
			for (int i = 0; i < amountOfOperators; i++) {
				if (charOperatorArrey[i] == "(") {
					FirstIndexBracket = i;
					for (int i = FirstIndexBracket; i < amountOfOperators; i++) {
						if (charOperatorArrey[i] == ")") {
							SecondIndexBracket = i;
							break; 
						}
						counterForSubExpression++;
					}
				}

			}

			if (FirstIndexBracket != -1 && SecondIndexBracket != -1) {
				cout << "Here" << endl;
				int DebugFirstIndex = FirstIndexBracket;
				int DebugSecondIndex = SecondIndexBracket;

				ExpressionBracketsLogicalFunc(FirstIndexBracket, SecondIndexBracket, counterForSubExpression);


				

			}
			else if (charOperatorArrey[maxPriorityIndex][0] == '|') {
				string OperationSymbol = charOperatorArrey[maxPriorityIndex];
				float FirstOperand = numberArrey[maxPriorityIndex];
				result = MakingOperation(FirstOperand, 0, OperationSymbol[0]);
				cout << result << endl;
			}
			else {
				
				string OperationSymbol = charOperatorArrey[maxPriorityIndex];
				float FirstOperand = numberArrey[maxPriorityIndex];
				float SecondOperand = numberArrey[maxPriorityIndex + 1];
				result = MakingOperation(FirstOperand, SecondOperand, OperationSymbol[0]);
				cout << result << endl;

				numberArrey[maxPriorityIndex] = result; // Writing result in array
				for (int i = maxPriorityIndex + 1; i < amountOfNumbers - 1; i++) {
					numberArrey[i] = numberArrey[i + 1];
				}
				amountOfNumbers--;

				for (int i = maxPriorityIndex; i < amountOfOpsPriority - 1; i++) {
					strOpsPriorityArr[i] = strOpsPriorityArr[i + 1];
				}
				amountOfOpsPriority--;

				DeleteFromOperatorArray(maxPriorityIndex);
			}
		}
		cout << "Final Result = " << result << endl;

	}

	void ExpressionBracketsLogicalFunc(int FirstIndex, int SecondIndex, int CounterForArr) {
		//Place for creating varuables and arrays
		int amountOfSValues = CounterForArr;
		int amountOfSOperators = 0;
		int amountOfSOperands = 0;
		int amountOfSPriority = 0;

		string* subMemoryArr = new string[SecondIndex]; //Sub expression memory Array
		string* subOperatorsArr = new string[amountOfSOperators]; //Sub operators Arr
		float* subNumberArr = new float[amountOfSOperands]; //Sub NumberArr
		int* subPriorityArr = new int[amountOfSPriority]; // priority of operators in sub operators Arr
		//----------------------------
		
		//------------------------------------------------------------------Вроде бы тут проблема-----------------------
		int subIndex = 0; // индекс для записи в subMemoryArr
		cout << FirstIndex << " " << SecondIndex << endl;
		for (int i = FirstIndex ; i < SecondIndex + 1; i++) { // Начинаем с FirstIndex + 1, чтобы исключить '('
			subMemoryArr[i] = this->memoryArrey[i];
			cout << this->memoryArrey[i] << endl;
		}

		// После заполнения subMemoryArr добавляем вывод
		cout << CounterForArr;
		for (int i = 0; i < amountOfSValues; i++) {
			
			cout << "[" << i << "] -- " << subMemoryArr[i] << endl;
		}
		//-------------------------------------------------------------------------------------------------------------
		string userOperator;
		float userNumber;

		for (int i = 0; i < amountOfSValues; i++) {
			if ((subMemoryArr[i] == "+") || (subMemoryArr[i] == "-") || (subMemoryArr[i] == "*") || (subMemoryArr[i] == "/") || (subMemoryArr[i] == "^") || (subMemoryArr[i] == "|")) {

				userOperator = subMemoryArr[i];

				//sort operators by priority , information take from https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B8%D0%BE%D1%80%D0%B8%D1%82%D0%B5%D1%82_%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%B8

				if ((subMemoryArr[i] == "+") || (subMemoryArr[i] == "-")) {
					AddInStrOpsPriorityArray(subPriorityArr, amountOfSPriority, 5);
					AddInCharOperatorsArray(subOperatorsArr, amountOfSOperators, userOperator);


				}
				else if ((subMemoryArr[i] == "*") || (subMemoryArr[i] == "/")) {
					AddInStrOpsPriorityArray(subPriorityArr, amountOfSPriority, 4);
					AddInCharOperatorsArray(subOperatorsArr, amountOfSOperators, userOperator);
				}
				else if ((subMemoryArr[i] == "^") || (subMemoryArr[i] == "|")) {
					AddInStrOpsPriorityArray(subPriorityArr, amountOfSPriority, 3);
					AddInCharOperatorsArray(subOperatorsArr, amountOfSOperators, userOperator);
				}
				/*else if ((memoryArrey[i] == "(") || (memoryArrey[i] == ")")) {
					AddInStrOpsPriorityArray(subPriorityArr,amountOfSPriority, 2);
					AddInCharOperatorsArray(subOperatorsArr, amountOfSOperators, userOperator);
				}*/

			}
			else if (IsDigit(subMemoryArr[i])) {
				userNumber = stof(subMemoryArr[i].c_str());
				AddInArrayNumber(subNumberArr, amountOfSOperands, userNumber);
			}
			else {


			}


			

		}
		




	}

	//Function that takes First and Second Operand and operation , than solves the expression and return it.
	float MakingOperation(float firstOperand, float secondOperand, char operation) {
		switch (operation) {
		case '+':
			return firstOperand + secondOperand;
		case '-':
			return firstOperand - secondOperand;
		case '*':
			return firstOperand * secondOperand;
		case '/':
			if (firstOperand == 0 || secondOperand == 0) {
				cout << "<--------{Message}------------->\n Some of operands become zero, you can't divide on zero! \n <------------------->" << endl;
				return 0;
			}
			else {

				return firstOperand / secondOperand;
			}

		case '^':
			return pow(firstOperand, secondOperand);
		case '|':
			if (firstOperand == 0) {
				cout << "<--------{Message}------------->\n The operand that you want sqrt is zero, you can't do that! \n <------------------->" << endl;
				return 0;
			}
			else {
				return sqrt(firstOperand);
			}
			/*case '(':
				cout << "Found bracket" << endl;
			case ')':
				cout << "Found bracket" << endl;*/
		default:
			cout << "<--------{Message}------------->\n Unsupported operation \n <------------------->" << endl;
			return 0;

		}
	}

	//Adding all user's cin values , no matter what is that operand , operator or function.
	void AddOperandOrOperatorInMemory(string userCinValue) {


		string* tempArr = new string[this->amountOfValues];
		for (int i = 0; i < this->amountOfValues; i++) {
			tempArr[i] = this->memoryArrey[i];

		}

		delete[] this->memoryArrey;
		this->amountOfValues++;

		this->memoryArrey = new string[this->amountOfValues];

		for (int i = 0; i < this->amountOfValues - 1; i++) {
			this->memoryArrey[i] = tempArr[i];

		}

		delete[] tempArr;

		this->memoryArrey[this->amountOfValues - 1] = userCinValue;
	}

	//Adding operands from memoryArray to this array
	void AddInArrayNumber(float*& Arr, int& amountOfOperands, const int& userNum) {
		float* tempArr = new float[amountOfOperands];
		for (int i = 0; i < amountOfOperands; i++) {
			tempArr[i] = Arr[i];
		}

		delete[] Arr;
		amountOfOperands++;

		Arr = new float[amountOfOperands];

		for (int i = 0; i < amountOfOperands - 1; i++) {
			Arr[i] = tempArr[i];
		}

		delete[] tempArr;

		Arr[amountOfOperands - 1] = userNum;
	}

	//Adding priority of each operator here //Changed!
	void AddInStrOpsPriorityArray(int*& Arr, int& amountOfPrio, const int& PriorityValue) {
		int* tempArr = new int[amountOfPrio];
		for (int i = 0; i < amountOfPrio; i++) {
			tempArr[i] = Arr[i];
		}

		delete[] Arr;
		amountOfPrio++;

		Arr = new int[amountOfPrio];

		for (int i = 0; i < amountOfPrio - 1; i++) {
			Arr[i] = tempArr[i];
		}

		delete[] tempArr;

		Arr[amountOfPrio - 1] = PriorityValue;
	}

	//Function to delete operator from array
	void DeleteFromOperatorArray(int maxPriorityIndex) {
		if (maxPriorityIndex < 0 || maxPriorityIndex >> this->amountOfOperators) {
			cout << "Error Out of range" << endl;
		}
		string* tempArr = new string[this->amountOfOperators - 1];
		int tempIndex = 0;

		for (int i = 0; i < this->amountOfOperators; i++) {
			if (i != maxPriorityIndex) {
				tempArr[tempIndex++] = this->charOperatorArrey[i];
			}
		}

		delete[] this->charOperatorArrey;
		this->amountOfOperators--;

		this->charOperatorArrey = new string[this->amountOfOperators];

		for (int i = 0; i < this->amountOfOperators; i++) {
			this->charOperatorArrey[i] = tempArr[i];
		}

		delete[] tempArr;

	}

	//Adding operator from memoryArrey here.
	void AddInCharOperatorsArray(string*& Arr, int& amountOfOper, const string& userOperator) {

		string* tempArr = new string[amountOfOper];
		for (int i = 0; i < amountOfOper; i++) {
			tempArr[i] = Arr[i];

		}

		delete[] Arr;
		amountOfOper++;

		Arr = new string[amountOfOper];

		for (int i = 0; i < amountOfOper - 1; i++) {
			Arr[i] = tempArr[i];

		}

		delete[] tempArr;

		Arr[amountOfOper - 1] = userOperator;
	}


	// this function is made for extract from memoryArrey operands , operators(+, - ,* , /, ^, |) and strings(sin,log functions).
	void RecreatingOperandsOperators(/*string* ArrMemory, int amountOfValues , string* OperArr , int* PriorityArr, float* numberArr, int amountOfOper , int amountOfPriorityValues, int amountOfOperands*/) {
		int userNumber;
		string userOperator;

		for (int i = 0; i < this->amountOfValues; i++) {
			if ((memoryArrey[i] == "+") || (memoryArrey[i] == "-") || (memoryArrey[i] == "*") || (memoryArrey[i] == "/") || (memoryArrey[i] == "^") || (memoryArrey[i] == "|") || (memoryArrey[i] == "(") || (memoryArrey[i] == ")")) {

				userOperator = memoryArrey[i];

				// sort operators by priority , information take from https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B8%D0%BE%D1%80%D0%B8%D1%82%D0%B5%D1%82_%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%B8

				if ((memoryArrey[i] == "+") || (memoryArrey[i] == "-")) {
					AddInStrOpsPriorityArray(strOpsPriorityArr, amountOfOpsPriority, 5);
					AddInCharOperatorsArray(charOperatorArrey, amountOfOperators, userOperator);


				}
				else if ((memoryArrey[i] == "*") || (memoryArrey[i] == "/")) {
					AddInStrOpsPriorityArray(strOpsPriorityArr, amountOfOpsPriority, 4);
					AddInCharOperatorsArray(charOperatorArrey, amountOfOperators, userOperator);
				}
				else if ((memoryArrey[i] == "^") || (memoryArrey[i] == "|")) {
					AddInStrOpsPriorityArray(strOpsPriorityArr, amountOfOpsPriority, 3);
					AddInCharOperatorsArray(charOperatorArrey, amountOfOperators, userOperator);
				}
				else if ((memoryArrey[i] == "(") || (memoryArrey[i] == ")")) {
					AddInStrOpsPriorityArray(strOpsPriorityArr, amountOfOpsPriority, 2);
					AddInCharOperatorsArray(charOperatorArrey, amountOfOperators, userOperator);
				}

			}
			else if (IsDigit(memoryArrey[i])) {
				userNumber = stof(memoryArrey[i].c_str());


				AddInArrayNumber(numberArrey, amountOfNumbers, userNumber);
			}
			else {


			}

		}

	}



	//Function to print Info about memory Array
	void PrintInfoMemoryArr() {

		for (int i = 0; i < amountOfValues; i++) {
			cout << "[" << i << "] -- " << memoryArrey[i] << endl;
		}
	}

	//Function to print Info about number Array
	void PrintInfoNumberArr() {

		for (int i = 0; i < this->amountOfNumbers; i++) {
			cout << "[" << i << "] -- " << this->numberArrey[i] << endl;
		}
	}

	//Function to print Info about Priority Array
	void PrintInfoPriorityArr() {

		for (int i = 0; i < this->amountOfOpsPriority; i++) {
			cout << "[" << i << "] -- " << this->strOpsPriorityArr[i] << endl;
		}
	}

	//Function to print Info about operators Array
	void PrintInfoOperatorArr() {

		for (int i = 0; i < this->amountOfOperators; i++) {
			cout << "[" << i << "] -- " << this->charOperatorArrey[i] << endl;
		}
	}

	//Function to clear Dinamyc arrays.
	void Clear() {
		delete[] this->memoryArrey;
		this->memoryArrey = nullptr;

		delete[] this->numberArrey;
		this->numberArrey = nullptr;

		delete[] this->charOperatorArrey;
		this->charOperatorArrey = nullptr;

		delete[] this->strOpsPriorityArr;
		this->strOpsPriorityArr = nullptr;

		this->amountOfValues = 0;
		this->amountOfNumbers = 0;
		this->amountOfOpsPriority = 0;
		this->amountOfOperators = 0;

		this->charOperatorArrey = new string[this->amountOfOperators];
		this->strOpsPriorityArr = new int[this->amountOfOpsPriority];
		this->memoryArrey = new string[this->amountOfValues];
		this->numberArrey = new float[this->amountOfNumbers];
	}

};



struct FuncOperation {
public:
	/*void IfElseChooseFunc(string UserValue1) {
		if (UserValue1 == "sin") {

		}
		else( UserValue1 == "cos") {

		}
		else { UserValue1 == "tan" } {

		}
	}*/

};



int main()
{

	MathFunctions objMathFunc; // Creating object

	//declaration of variables
	int DebugNum1 = 0;
	int DebugNum2 = 0;
	char userOperation;
	string userCinValue;
	string tempVaruable;
	char userChooseOption = '0';

	//int amountOfValues;
	//int amountOfNumbers;
	//int amountOfOpsPriority;
	//int amountOfOperators;
	//int amountOfVaruablesSubArray;

	//string* memoryArrey = new string[amountOfValues]; //General Array for User's String
	//float* numberArrey = new float[amountOfNumbers]; // Array for user operands from strings in memoryArray
	//string* charOperatorArrey = new string[amountOfOperators]; // Array for all operators from memoryArray
	//int* strOpsPriorityArr = new int[amountOfOpsPriority]; // Array for prioritiers for operators
	//----------------
	//initialization of operator and first operand






	while (true) {
		cout << "<------------{Menu}------------->" << endl
			<< "Choose option: " << endl
			<< "1 - Enter your exspression;" << endl
			<< "2 - show your mathematical expression;" << endl
			<< "3 - Show all Array Information;" << endl
			<< "4 - Clear exspresion;" << endl
			<< "5 - Calculate;" << endl
			<< "<-------------------------------->" << endl;

		cin >> userChooseOption;
		/*if ((userChooseOption != '1') || (userChooseOption != '2') || (userChooseOption != '3') || (userChooseOption != '4') || (userChooseOption != '5')) {
			cout << "<--------{Message}------------->\n Entering a number that does not match the selection in the menu! Try again!\n <--------------------------->" << endl;
			userChooseOption = ' ';
			cin >> userChooseOption;
		}*/
		if (userChooseOption == '1') { // User enters his exspression with space after each operand or operator.

			string tempVaruable = "";

			cout << "<------------{Menu}------------->" << endl << "Enter your exspression with operands (0-9) , operators(+,-,*,/,^,| <-sqrt() , ( , ) )" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			getline(cin, userCinValue);
			for (int i = 0; i < userCinValue.length(); i++) {
				if (userCinValue[i] == ' ') {
					objMathFunc.AddOperandOrOperatorInMemory(tempVaruable);
					tempVaruable = "";
				}
				else {
					tempVaruable += userCinValue[i];
				}

			}
			if (!tempVaruable.empty()) {
				objMathFunc.AddOperandOrOperatorInMemory(tempVaruable);
				tempVaruable.clear();
			}

		}
		else if (userChooseOption == '2') {
			cout << userCinValue << endl;
		}
		else if (userChooseOption == '3') {
			cout << "------First Array-----" << endl;
			objMathFunc.PrintInfoMemoryArr();
			cout << "------Next Array-----" << endl;
			objMathFunc.PrintInfoNumberArr();
			cout << "------Next Array-----" << endl;
			objMathFunc.PrintInfoOperatorArr();
			cout << "------Next Array-----" << endl;
			objMathFunc.PrintInfoPriorityArr();
		}
		else if (userChooseOption == '4') {
			userCinValue.clear();
			tempVaruable.clear();

			objMathFunc.Clear();
		}
		else if (userChooseOption == '5') {
			/*objMathFunc.RecreatingOperandsOperators(memoryArrey, amountOfValues, charOperatorArrey, strOpsPriorityArr, numberArrey, amountOfOperators, amountOfOpsPriority, amountOfNumbers);*/
			objMathFunc.RecreatingOperandsOperators();
			objMathFunc.MathOperations();
		}

	}







	/*objMathFunc.PrintInfoMemoryArr();*/













}

