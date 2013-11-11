#ifndef _PKFW_PY_
#define _PKFW_PY_
#include <Python.h>
#include <iostream>

	#if defined ( _WIN32 )
		#define __func__ __FUNCTION__
	#endif

extern PyMethodDef PKFW_Functions[];
void  ParsePyTupleError( const char* a_pFunction, int a_Line );
PyObject* ImportPythonModule( const char* a_pyModuleName );
void ReloadPythonModule(PyObject* a_pModule);
PyObject* GetHandleToPythonFunction( PyObject* a_pModule, const char* a_pFunctionName );
PyObject* CallPythonFunction( PyObject* a_pyFunction, PyObject* a_pyFuncArguments);

static PyObject *PKFW_INIT	(PyObject*self, PyObject*args);//Initialise Framework
static PyObject *PKFW_UPDA	(PyObject*self, PyObject*args);//Update Framework
static PyObject *PKFW_SBCO	(PyObject*self, PyObject*args);//Set Background Colour

static PyObject *PKFW_GTMP	(PyObject*self, PyObject*args);// get mouse position
static PyObject *PKFW_GMPR	(PyObject*self, PyObject*args);// get mouse press
static PyObject *PKFW_GTMR	(PyObject*self, PyObject*args);// get mouse release
static PyObject *PKFW_GTKP	(PyObject*self, PyObject*args);// get key press
static PyObject *PKFW_GTKR	(PyObject*self, PyObject*args);// get key release

static PyObject *PKFW_SPCR	(PyObject*self, PyObject*args);// Sprite Create
static PyObject *PKFW_SPRO	(PyObject*self, PyObject*args);// Sprite Rotate
static PyObject *PKFW_SPMO	(PyObject*self, PyObject*args);// Sprite Move
static PyObject *PKFW_SPDR	(PyObject*self, PyObject*args);// Sprite Draw
static PyObject *PKFW_SPDE	(PyObject*self, PyObject*args);// Sprite Draw

static PyObject *PKFW_DRST	(PyObject*self, PyObject*args);// draw string
static PyObject *PKFW_DRLN	(PyObject*self, PyObject*args);// draw string
#endif