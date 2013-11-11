#include "pkfw_py.h"
#include "framework.h"
PyMethodDef PKFW_Functions[] = {
	{"init",		PKFW_INIT,		METH_VARARGS,		"initalise framework"								},
	{"upda",		PKFW_UPDA,		METH_VARARGS,		"update framework (time, mousepos, clearscreen)"	},
	{"sbco",		PKFW_SBCO,		METH_VARARGS,		"set background colour"								},
	{"gtmp",		PKFW_GTMP,		METH_VARARGS,		"get mouse position"								},
	{"gmpr",		PKFW_GMPR,		METH_VARARGS,		"get mouse press"									},
	{"gtmr",		PKFW_GTMR,		METH_VARARGS,		"get mouse release"									},
	{"gtkp",		PKFW_GTKP,		METH_VARARGS,		"get key press"										},
	{"gtkr",		PKFW_GTKR,		METH_VARARGS,		"get key release"									},
	{"spcr",		PKFW_SPCR,		METH_VARARGS,		"sprite create"										},
	{"spro",		PKFW_SPRO,		METH_VARARGS,		"sprite rotate"										},
	{"spmo",		PKFW_SPMO,		METH_VARARGS,		"sprite move"										},
	{"spdr",		PKFW_SPDR,		METH_VARARGS,		"sprite draw"										},
	{"spde",		PKFW_SPDE,		METH_VARARGS,		"sprite delete"										},
	{"drst",		PKFW_DRST,		METH_VARARGS,		"draw string"										},
	{"drln",		PKFW_DRLN,		METH_VARARGS,		"draw line"											},
	{NULL, NULL, 0, NULL}
};
void  ParsePyTupleError(const char* a_pFunction, int a_Line ){
	std::cout << "___Error Parsing Tuple___\nFunction: " <<  a_pFunction << "\nLine#   : " << a_Line << std::endl;
	PyErr_Print();
}
PyObject* ImportPythonModule( const char* a_pyModuleName ){
	PyObject* pObjName= PyString_FromString(a_pyModuleName);
	PyObject* pModule = PyImport_Import(pObjName);
	if (!pModule){
		PyErr_Print();
		std::cout << stderr << "Failed to load \" " << a_pyModuleName << "\"" << std::endl;
		system("pause");
	}
	Py_DECREF(pObjName);
	return pModule;
}
void ReloadPythonModule(PyObject* a_pModule){
	PyObject* pModule = PyImport_ReloadModule(a_pModule);
	if (pModule == NULL){
		std::cout << stderr << "Failed to reload, Python returned NULL.\n" << std::endl;
		return;
	}
	a_pModule = pModule;
}
PyObject* GetHandleToPythonFunction( PyObject* a_pModule, const char* a_pFunctionName ){
	PyObject* pFunction = PyObject_GetAttrString(a_pModule, a_pFunctionName);
	if( !(pFunction && PyCallable_Check(pFunction)) ){
		if (PyErr_Occurred()){
			PyErr_Print();
		}
		std::cout << stderr << "Cannot find function \"" << a_pFunctionName << "\"" << std::endl;
	}
	return pFunction;
}
PyObject* CallPythonFunction( PyObject* a_pyFunction, PyObject* a_pyFuncArguments){
	PyObject* pReturnValue = PyObject_CallObject( a_pyFunction, a_pyFuncArguments );
	if (pReturnValue == nullptr){
		PyErr_Print();
		fprintf(stderr,"Call failed\n");
	}
	return pReturnValue;
}
PyObject *PKFW_INIT	(PyObject*self, PyObject*args){
	unsigned int width, height;
	if (!PyArg_ParseTuple(args, "ii", &width, &height)){
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FMWKInitialise(width, height);
	Py_RETURN_NONE;
}

PyObject *PKFW_UPDA(PyObject*self, PyObject*args){
	FMWKUpdate();
	Py_RETURN_NONE;
}
PyObject *PKFW_SBCO(PyObject*self, PyObject*args){
	float fRed, fBlue, fGreen;
	if (!PyArg_ParseTuple(args, "fff", &fRed, &fBlue, &fGreen)) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	FMWKBackgroundColour(Vector3( fRed, fBlue, fGreen));
	Py_RETURN_NONE;
}

PyObject *PKFW_GTMP	(PyObject*self, PyObject*args){
	float fMouseX, fMouseY;
	Vector2 mp = getMousePosition();
	fMouseX = mp.x;fMouseY = mp.y;
	return Py_BuildValue("ff", fMouseX, fMouseY );
}
PyObject *PKFW_GMPR	(PyObject*self, PyObject*args){
	unsigned int iMouseButton;
	if (!PyArg_ParseTuple( args, "i", &iMouseButton ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	bool bIsDown = getMouseDown(iMouseButton);
	if ( bIsDown )
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}
PyObject *PKFW_GTMR	(PyObject*self, PyObject*args){
	unsigned int iMouseButton;
	if (!PyArg_ParseTuple( args, "i", &iMouseButton ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	bool bIsDown = getMouseRel(iMouseButton);
	if ( bIsDown )
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}
PyObject *PKFW_GTKP	(PyObject*self, PyObject*args){
	int iKeyButton;
	if (!PyArg_ParseTuple( args, "i", &iKeyButton ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	bool bIsDown = getKeyDown(iKeyButton);
	if ( bIsDown )
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}
PyObject *PKFW_GTKR	(PyObject*self, PyObject*args){
	unsigned int iKeyButton;
	if (!PyArg_ParseTuple( args, "i", &iKeyButton ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	bool bIsDown = getKeyRel(iKeyButton);
	if ( bIsDown )
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}

PyObject *PKFW_SPCR(PyObject*self, PyObject*args){
	const char* pTextureName; unsigned int uiSize[2];
	if (!PyArg_ParseTuple(args, "sii", 
			&pTextureName, 
			&uiSize[0], &uiSize[1]) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	unsigned int uiSpriteID = SpriteCreate( pTextureName, uiSize[0], uiSize[1]);
	return Py_BuildValue("i", uiSpriteID);
}
static PyObject *PKFW_SPRO	(PyObject*self, PyObject*args){
	unsigned int iSpriteID; float fRot;
	if (!PyArg_ParseTuple(args, "if", &iSpriteID,&fRot) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteRotate( iSpriteID, fRot );
	Py_RETURN_NONE;
}
static PyObject *PKFW_SPMO	(PyObject*self, PyObject*args){
	unsigned int iSpriteID; float v2fPos[2];
	if (!PyArg_ParseTuple(args, "iff", &iSpriteID, 
		&v2fPos[0], &v2fPos[1]) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteMove( iSpriteID, Vector2(v2fPos[0],v2fPos[1]));
	Py_RETURN_NONE;
}
static PyObject *PKFW_SPDR	(PyObject*self, PyObject*args){
	unsigned int iSpriteID;
	if (!PyArg_ParseTuple( args, "i", &iSpriteID ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteDraw( iSpriteID );
	Py_RETURN_NONE;
}
PyObject *PKFW_SPDE	(PyObject*self, PyObject*args){
	unsigned int iSpriteID;
	if (!PyArg_ParseTuple( args, "i", &iSpriteID ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	SpriteDelete( iSpriteID );
	Py_RETURN_NONE;
}

PyObject *PKFW_DRST	(PyObject*self, PyObject*args){
	int s;
	unsigned int x, y;
	if (!PyArg_ParseTuple( args, "iii", &s, &x, &y ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	DrawText(s, Vector2((float)x,(float)y));
	Py_RETURN_NONE;
}

PyObject *PKFW_DRLN	(PyObject*self, PyObject*args){
	float bx, by, ex, ey;
	float r,g,b;
	if (!PyArg_ParseTuple( args, "fffffff", &bx, &by, &ex, &ey, &r, &g, &b ) ) 
	{
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
	}
	DrawLine(Vector2((float)bx,(float)by), Vector2((float)ex,(float)ey), Vector3(r,g,b));
	Py_RETURN_NONE;
}

