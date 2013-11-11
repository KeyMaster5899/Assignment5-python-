#include <Python.h>
#include "Framework.h"
#include "pkfw_py.h"
void CallModuleFunction( PyObject* a_pModule, char * a_pFunc);

int main(int argc, char *argv[]){
	Py_Initialize();
	PySys_SetArgv(argc, argv);
	PyObject* sysPath = PySys_GetObject((char*)"path");
	PyList_Append(sysPath, PyString_FromString("./scripts"));
	Py_InitModule("PKFW", PKFW_Functions);
	PyObject *pModule = ImportPythonModule("game");
	//main python module named Game // loads game.py in sciprts folder
	if(pModule!=NULL){
		CallModuleFunction(pModule, "GameInit");
		// call gameinitialse from game script // initialises framework 
		while (FMWKWindowOpen()){
			if(getKeyDown(257)){
				// reloads game script
				CallModuleFunction(pModule, "c");//attempting to clear sprites ??? my framework must not work
				ReloadPythonModule(pModule);
				CallModuleFunction(pModule, "LevelGridInit");
			}
			CallModuleFunction(pModule, "GameUpdate");
		}
		FMWKShutdown();
	}
	return 1;
}

void CallModuleFunction( PyObject* a_pModule, char * a_pFunc) {
	PyObject* pFunc = GetHandleToPythonFunction( a_pModule, a_pFunc );
	if (pFunc){
		PyObject* pReturnValue = CallPythonFunction( pFunc, nullptr );
		if( pReturnValue ){
			Py_DECREF(pReturnValue);
		}
		Py_XDECREF(pFunc);
	}
}