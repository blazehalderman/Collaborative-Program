#include "cornergrocer.h"

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
	PyObject* my_module = PyImport_ImportModule("cornergrocer");
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
	pName = PyUnicode_FromString((char*)"cornergrocer");
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
	pName = PyUnicode_FromString((char*)"cornergrocer");
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

// function prints menu options
void printMenuOptions() {
	cout << "***Welcome!***" << endl;
	cout << "***Please enter 1, 2, 3, or 4 for the following menu options below*** " << endl;
	cout << endl;
	cout << "1: Track inventory for items in grocery list (item quantity)" << endl;
	cout << "2: Track frequency of an item in grocery list (quantity of item only)" << endl;
	cout << "3: Create histogram of grocery list items (Must be run only after option 1 has been selected)" << endl;
	cout << "4: Exit (Closes program)" << endl;
}

// function runner for menu options
void runMenuOptions() {
	char val = NULL;

	// validates user input for invalid values
	while (val == NULL || val >= '4' || val < '1') {
		// gets user input
		cin >> val;
		// if user inputs 1, prints item frequency list
		if (val == '1') {
			system("CLS");
			CallProcedure("printItemsFrequency");
			system("pause");
			continue;
		}
		// if user inputs 2, print a specific items frequency
		else if (val == '2') {
			// initialize and create variables
			string itemName;
			int itemFRQ = 0;
			int valid = 0;

			// validates user input for the specified item
			while (valid == 0) {
				CallProcedure("printItemsFrequency");
				cout << endl;
				cout << "Please enter an item name to get a specific items frequency: " << endl;
				cin >> itemName;
				valid = callIntFunc("validateItemFrequency", itemName);
			}
			// retrieves the specified frequency value for the item
			itemFRQ = callIntFunc("getItemFrequency", itemName);
			system("CLS");
			cout << "Item Frequency: " + itemName + " appears " + to_string(itemFRQ) + " times in the grocery list" << endl;
			system("pause");
			continue;
		}
		// if user input 3, creates a frequency.dat file and generates histogram
		else if (val == '3') {
			CallProcedure("createDatFile");
			ifstream infile("./frequency.dat");
			string item;
			int quantity;

			system("CLS");
			while (infile >> item >> quantity) {
				cout << string(item);
				cout << " ";
				for (int i = 0; i < quantity; i++) {
					cout << "*";
				}
				cout << endl;
			}
			system("pause");
			continue;
		}
		// if user input 4, exits program
		else if (val == '4') {
			cout << "Thank you for using Corner Grocer Inventory Management Application!" << endl;
			cout << "Goodbye" << endl;
			exit(0);
		}
		// if any other input, displays error message
		else {
			cout << "ERROR: please only use values including and between 1 through 4 with the provided menu options" << endl;
			cout << endl;
			system("pause");
			system("CLS");
			printMenuOptions();
		}
	}
}

void main()
{
	// call menu options function(s)
	while (true) {
		printMenuOptions();
		runMenuOptions();
		system("CLS");
	}
}