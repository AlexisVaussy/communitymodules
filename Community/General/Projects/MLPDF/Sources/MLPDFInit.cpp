//----------------------------------------------------------------------------------
// Dynamic library and runtime type system initialization.
//
// \file    MLPDFInit.cpp
// \author  Axel Newe (axel.newe@fau.de)
// \date    2014-02-06
//----------------------------------------------------------------------------------


// Local includes
#include "MLPDFSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include "mlLibraryInitMacros.h"

// Include all module headers ...
#include "abstract/PDFGenerator/PDFGenerator.h"
#include "PDFUtils/PDFCalcCamera.h"
#include "PDFUtils/PDFCreateViewSpecifications.h"

ML_START_NAMESPACE

//----------------------------------------------------------------------------------
//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
//----------------------------------------------------------------------------------
int MLPDFInit()
{
  PDFGenerator::initClass();

  PDFCalcCamera::initClass();
  PDFCreateViewSpecifications::initClass();

  return 1;
}

ML_END_NAMESPACE


//! Calls the init method implemented above during load of shared library.
ML_INIT_LIBRARY(MLPDFInit)