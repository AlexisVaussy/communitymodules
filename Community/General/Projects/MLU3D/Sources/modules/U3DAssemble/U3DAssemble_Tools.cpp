//----------------------------------------------------------------------------------
// U3DAssemble module.
//
// \file    U3DAssemble_Tools.cpp
// \author  Axel Newe (axel.newe@fau.de)
// \date    2016-10-01
//
// Assembles a U3D object.
//----------------------------------------------------------------------------------


// Local includes
#include "U3DAssemble.h"
#include "../../shared/MLU3D_Tools.h"


ML_START_NAMESPACE

using namespace mlU3D;

//***********************************************************************************

void U3DAssemble::_updateDefaultValues()
{
  if (_outU3DObject)
  {
    _outU3DObject->defaultValues.addDefaultBoundingBoxMetaData = _addDefaultBoundingBoxMetaDataFld->getBoolValue();

    std::string fieldStringValue = "";

    // Set default prefix for point clouds
    fieldStringValue = _modelPrefixPointCloudsFld->getStringValue();

    if ("" != fieldStringValue)
    {
      _outU3DObject->defaultValues.defaultPointSetPefix = fieldStringValue;
    }
    else
    {
      _modelPrefixPointCloudsFld->setStringValue(_outU3DObject->defaultValues.defaultPointSetPefix); // Reset old value
    }

    // Set default prefix for line sets
    fieldStringValue = _modelPrefixLineSetsFld->getStringValue();

    if ("" != fieldStringValue)
    {
      _outU3DObject->defaultValues.defaultLineSetPefix = fieldStringValue;
    }
    else
    {
      _modelPrefixLineSetsFld->setStringValue(_outU3DObject->defaultValues.defaultLineSetPefix); // Reset old value
    }

    // Set default prefix for meshes
    fieldStringValue = _modelPrefixMeshesFld->getStringValue();

    if ("" != fieldStringValue)
    {
      _outU3DObject->defaultValues.defaultMeshPefix = fieldStringValue;
    }
    else
    {
      _modelPrefixMeshesFld->setStringValue(_outU3DObject->defaultValues.defaultMeshPefix); // Reset old value
    }

    // Set default material name
    fieldStringValue = _defaultMaterialNameFld->getStringValue();

    if ("" != fieldStringValue)
    {
      _outU3DObject->defaultValues.defaultMaterialName = fieldStringValue;
    }
    else
    {
      _defaultMaterialNameFld->setStringValue(_outU3DObject->defaultValues.defaultMaterialName); // Reset old value
    }

    _outU3DObject->defaultValues.defaultMaterialAmbientColor  = _defaultMaterialAmbientColorFld->getVector3Value();
    _outU3DObject->defaultValues.defaultMaterialDiffuseColor  = _defaultMaterialDiffuseColorFld->getVector3Value();
    _outU3DObject->defaultValues.defaultMaterialAlpha         = _defaultMaterialAlphaFld->getDoubleValue();
    _outU3DObject->defaultValues.defaultMaterialReflectivity  = _defaultMaterialReflectivityFld->getDoubleValue();
    _outU3DObject->defaultValues.defaultMaterialDiffuseColorWithTransparency = Vector4(_outU3DObject->defaultValues.defaultMaterialDiffuseColor, _outU3DObject->defaultValues.defaultMaterialAlpha);
    _outU3DObject->defaultValues.defaultMaterialSpecularColor = _defaultMaterialSpecularColorFld->getVector3Value();
    _outU3DObject->defaultValues.defaultMaterialEmissiveColor = _defaultMaterialEmissiveColorFld->getVector3Value();

    //_outU3DObjectFld->touch();
  }
}

//***********************************************************************************

void U3DAssemble::_addDefaultViewNode()
{
  if (_addDefaultViewNodeFld->getBoolValue())
  {
    ViewNode newViewNode;

    newViewNode.displayName  = _defaultViewNameFld->getStringValue();
    newViewNode.resourceName = _defaultViewNameFld->getStringValue();

    _outU3DObject->viewNodes.push_back(newViewNode);
  }
}

//***********************************************************************************

void U3DAssemble::_addDefaultLightNode()
{
  if (_addDefaultLightNodeFld->getBoolValue())
  {
    LightNode newLightNode;

    newLightNode.displayName  = _defaultLightNameFld->getStringValue();
    newLightNode.resourceName = _defaultLightNameFld->getStringValue();

    _outU3DObject->lightNodes.push_back(newLightNode);
  }
}

//***********************************************************************************

void U3DAssemble::_addDefaultLightResource()
{
  if (_addDefaultLightNodeFld->getBoolValue())
  {
    // Add default light resource

    LightResource defaultLightResouce;

    defaultLightResouce.resourceName     = _defaultLightNameFld->getStringValue();
    defaultLightResouce.lightType        = LIGHTTYPE_AMBIENT;
    defaultLightResouce.lightColor       = _defaultLightColorFld->getVector3Value();
    defaultLightResouce.lightAttenuation = Vector3(1.0f, 0.0f, 0.0f);
    defaultLightResouce.lightSpotAngle   = 180.0f;
    defaultLightResouce.lightIntensity   = _defaultLightIntensityFld->getDoubleValue();

    _outU3DObject->lightResources.push_back(defaultLightResouce);
  }
}

//***********************************************************************************

void U3DAssemble::_addDefaultViewResource()
{
  if (_addDefaultViewNodeFld->getBoolValue())
  {
    ViewResource defaultViewResouce;
    
    defaultViewResouce.resourceName = _defaultViewNameFld->getStringValue();

    _outU3DObject->viewResources.push_back(defaultViewResouce);
  }
}

//***********************************************************************************

void U3DAssemble::_addMetaData()
{
    _statusFld->setStringValue("Adding meta data.");

    StringVector metaDataSpecificationsVector = U3DTools::getModelSpecificationsStringFromUI(_metaDataSpecificationFld, "<MetaData>");
    const MLuint32 numberOfMEtaDataPairs = (MLuint32)metaDataSpecificationsVector.size();  

    for (MLuint32 i = 0; i < numberOfMEtaDataPairs; i++)
    {
      ObjectSpecificationMap thisSpecificationParameters = U3DTools::getAllSpecificationParametersFromString(metaDataSpecificationsVector[i]);
      MetaDataStruct metaDataPair;
      metaDataPair.key = thisSpecificationParameters["MetaDataKey"];
      metaDataPair.value = thisSpecificationParameters["MetaDataValue"];

      _outU3DObject->metaData.push_back(metaDataPair);
    }

}

//***********************************************************************************

void U3DAssemble::_addPointSetModelData()
{
  if (_inPointPositions.size() == 0)
  {
    return;
  }

  StringVector pointSetSpecificationsVector;

  if (_simpleModePointSetFld->getBoolValue())
  {
    pointSetSpecificationsVector.push_back("<PointSet><PositionTypes>all</PositionTypes></PointSet>");
  }
  else
  {
    pointSetSpecificationsVector = U3DTools::getModelSpecificationsStringFromUI(_pointCloudSpecificationFld, "<PointSet>");
  }

  if (0 == pointSetSpecificationsVector.size())
  {
    return;
  }

  _statusFld->setStringValue("Adding point set models.");

  U3DTools::addPointSetModelAndGeometry(pointSetSpecificationsVector, _outU3DObject, _inPointPositions);
}

//***********************************************************************************

void U3DAssemble::_addLineSetModelData()
{
  if (_inLinePositions.size() == 0)
  {
    return;
  }

  StringVector lineSetSpecificationsVector;

  if (_simpleModeLineSetFld->getBoolValue())
  {
    lineSetSpecificationsVector.push_back("<LineSet><PositionTypes>all</PositionTypes><ConnectionTypes>all</ConnectionTypes></LineSet>");
  }
  else
  {
    lineSetSpecificationsVector = U3DTools::getModelSpecificationsStringFromUI(_lineSetSpecificationFld, "<LineSet>");
  }

  if (0 == lineSetSpecificationsVector.size())
  {
    return;
  }

  _statusFld->setStringValue("Adding line set models.");

  U3DTools::addLineSetModelAndGeometry(lineSetSpecificationsVector, _outU3DObject, _inLinePositions, _inLineConnections);
}

//***********************************************************************************

void U3DAssemble::_addMeshModelData()
{
  if (!_inWEM)
  {
    return;
  }

  bool simpleMode = _simpleModeMeshFld->getBoolValue();
  StringVector meshSpecificationsVector;

  if (simpleMode)
  {
    meshSpecificationsVector = U3DTools::getMeshSpecificationsStringFromWEM(_inWEM);
  }
  else
  {
    meshSpecificationsVector = U3DTools::getModelSpecificationsStringFromUI(_meshSpecificationFld, "<Mesh>");
  }

  if (0 == meshSpecificationsVector.size())
  {
    return;
  }

  _statusFld->setStringValue("Adding mesh models.");

  U3DTools::addMeshModelAndGeometry(meshSpecificationsVector, _outU3DObject, _inWEM);
}

//***********************************************************************************


ML_END_NAMESPACE