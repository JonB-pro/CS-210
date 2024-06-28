#include <Python.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Creates a number of instances of a character for design detail
string NCharString(size_t n, char c) {

	string totalC;

	for (int i = 0; i < n; ++i) {
		totalC += c;
	}

	return totalC;
	// return the n character string

}

//Creates vector of items in order
vector<string> CreateItemVector(string dataFileName) {
	vector <string> items;

	fstream freqFile;
	freqFile.open(dataFileName, ios::in);
	if (!freqFile) {
		cout << "Error opening file";
	}
	else {
		string item;
		int quant;

		while (true) {
			freqFile >> item;
			freqFile >> quant;
			if (freqFile.eof()) {
				break;
			}
			items.push_back(item);
		}

	}
	freqFile.close();
	return items;
}

// Creates vector of quantities in order
vector<int> CreateQuantityVector(string dataFileName) {
	vector <int> quants;

	fstream freqFile;
	freqFile.open(dataFileName, ios::in);
	if (!freqFile) {
		cout << "Error opening file";
	}
	else {
		string item;
		int quant;

		while (true) {
			freqFile >> item;
			freqFile >> quant;
			if (freqFile.eof()) {
				break;
			}
			quants.push_back(quant);
		}

	}
	freqFile.close();
	return quants;
}

// Prints histogram from input from 2 vectors
void PrintHistogram(vector<string> items, vector<int> quants) {
	cout << endl;
	cout << endl;
	cout << "||" << NCharString(24, '-') << "||" << endl;
	cout << "||-Histogram of Purchases-" << "||" << endl;
	cout << "||" << NCharString(24, '-') << "||" << endl;
	for (int i = 0; i < items.size(); ++i) {
		cout << "||" << setw(13) << left << items[i] << "|";
		cout << setw(10) << left << NCharString(quants[i], '$') << "||" << endl; // 1 $ per quantity sold
	}
	cout << "||" << NCharString(13, '-') << "|123456789+" << "||" << endl;
	cout << "||" << NCharString(24, '-') << "||" << endl;
	cout << endl;
	cout << endl;
}

void main()
{
	system("Color 0A");
	int menuChoice = 0;

	//Keeps menu running after choices
	while (true) {
		// Prints menu and gets input
		CallProcedure("PrintMenu");
		cout << endl;
		cin >> menuChoice;

		// If 1, prints list of items and number sold
		if (menuChoice == 1) {
			CallProcedure("PrintItemizedList");

			continue;
		}

		// If 2, asks for item to count and returns quantity found in file accessed
		if (menuChoice == 2) {
			int quantity = 0;
			string itemWanted = "";

			cout << "Please enter the item to quantify: ";

			while (true) {
				cin >> itemWanted;
				cout << endl;
				quantity = callIntFunc("ListQuantity", itemWanted);

				if (quantity > 0) {
					cout << quantity << " sold today." << endl;
					cout << endl;
					break;
				}

				else {
					cout << "Error-No item by that name found, please try again: ";
				}

			}

			continue;
		}

		// If 3, writes data file of items and quantities and then prints histogram from data file
		if (menuChoice == 3) {
			vector <string> itemsVector;
			vector <int> quantsVector;

			callIntFunc("WriteToFile", "frequency.dat");

			itemsVector = CreateItemVector("frequency.dat");
			quantsVector = CreateQuantityVector("frequency.dat");

			PrintHistogram(itemsVector, quantsVector);

			continue;
		}

		// If exit choice, end loop
		if (menuChoice == 4) {
			break;
		}

		// If number not 1-4 entered, displays warning, gets new entry
		else {
			cout << "Please enter a number 1-4" << endl;
			cout << endl;
		}
	}

}