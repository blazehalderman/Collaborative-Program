#ifndef _CORNER_GROCER_H_
#define _CORNER_GROCER_H_

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

void CallProcedure(string pName);
int callIntFunc(string proc, string param);
int callIntFunc(string proc, int param);
void printMenuOptions();
void runMenuOptions();

#endif _CORNER_GROCER_H_
