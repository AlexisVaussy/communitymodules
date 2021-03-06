//----------------------------------------------------------------------------------
// Base class for all odules that consume a U3D object.
//
// \file    U3DInspector.h
// \author  Axel Newe (axel.newe@fau.de)
// \date    2016-10-01
//----------------------------------------------------------------------------------


#pragma once


// Local includes
#include "../../MLU3DSystem.h"
#include "U3DModule.h"
#include "../../shared/U3DInternalFormat/U3D_Object.h"

// Global includes
#include <mlModuleIncludes.h>


ML_START_NAMESPACE

////////////////////////////////////////////////////////////////////////

class MLU3D_EXPORT U3DInspector : public U3DModule
{
public:

  //! Standard constructor.
  U3DInspector(int numInImages=0, int numOutImages=0);

protected:

  //! Standard destructor.
  virtual ~U3DInspector();


  /* FIELDS */

  //! U3D object input field.
  BaseField* _inU3DObjectFld;

  BoolField  *_inputValidFld;

  NotifyField *_applyFld;
  BoolField   *_autoApplyFld;

  /* VARIABLES */

  //! A pointer to the output U3D object.
  mlU3D::U3DObjectPtr _inU3DObject;

  //! a flag which stores if the input U3D object is valid
  bool _inU3DValid;


  /* METHODS */

  //! Called when input changes.
  virtual void handleNotification(Field *field);

  //! Initialize module after loading.
  virtual void activateAttachments();

  //! Execute module functionaylity.
  virtual void process() = 0;


private:

  /* FIELDS */


  /* STATE VARIABLES */



  /* METHODS */


  //! Implements interface for the runtime type system of the ML.
  ML_CLASS_HEADER(U3DInspector)
};

//////////////////////////////////////////////////////////////////////////

ML_END_NAMESPACE
