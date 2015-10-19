/*
 * Copyright 2001, MeVis gGmbH
 * ALL RIGHTS RESERVED
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF MEVIS GGMBH. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF MEVIS GGMBH
 *
 */

// $Id: UMDSoMeasureTool.h,v 1.11 2003/09/09 16:20:03 milo Exp $
// $Source: /projects/repositories/mevis/Libraries/std/Inventor/SoMeasurement/UMDSoMeasureTool.h,v $

/*! The Inventor node UMDSoMeasureTool is a base class for measurement tools, derived from SoSeparator and already containing many nodes.
// \file    UMDSoMeasureTool.h
// \author  Henry Sonnet / Christian Tietjen
// \date    09/2002
*/

#ifndef _UMDSoMeasureTool
#define _UMDSoMeasureTool

#include "UMDMeasurementInit.h"

#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>

#include <Inventor/fields/SoSFVec3f.h>

class SoAnnotation;
class SoEventCallback;
class SoFieldSensor;
class SoLevelOfDetail;
class SoMaterial;
class SoSFInt32;
class SoSwitch;
class SoTransform;

#ifdef WIN32

// Disabled warning: warning C4710: '__thiscall SbName::SbName(char const *)' ist keine Inline-Funktion
#pragma warning (disable : 4710)

#endif

//! The Inventor node UMDSoMeasureTool is a base class for measurement tools, derived from SoSeparator and
//! already containing many nodes. These nodes are
//! - die Root
//! - einen SoEventCallback-Knoten fuer Mousebutton- und Keyboardevents,
//!   die Interaktionsm�glichkeiten, die m�glich sind, werden weiter unten
//!   beschrieben
//! - einen SoLevelOfDetail-Knoten fuer die Darstellung verschiedener
//!   Fontgroessen und �nderung des Drawstyles in LINES bei gro�er Entfernung,
//!   damit des Tool weiterhin sichtbar bleibt
//! - einen SoSeparator-Knoten zum Anh�ngen der anw�hlbaren Objekte
//! - einen SoAnnotation-Knoten f�r den Text, welcher sicherstellt, da� die Bema�ung
//!   immer sichtbar ist
//!
//! Grunds�tzlich sind alle "beweglichen Teile" mit SoLocateHighlight-Knoten versehen,
//! die beim �berfahren mit der Maus aufleuchten.
//!
//! Um ein Werkzeugteil bewegen zu k�nnen, mu� man es erst mit einem einfachen Klick
//! anw�hlen. Es kann immer nur ein Werkzeug zur Zeit aktiviert werden,
//! ein evtl. vorher selektiertes Werkzeug wird automatisch deselektiert
//!
//! Interaktionsm�glichkeiten: (zus�tzliche M�glichkeiten werden in den Headern
//! der einzelnen Tools beschrieben)
//! - mit der Maus:
//!   - den DirectSelect-Mode, mit dem man durch einen einfachen Klick eine beliebige
//!            Inventor-Fl�che anw�hlen und das Teil gleichzeitig dorthin bewegen kann
//! - per Tastatur:
//!   - Space: wechseln zwischen den beiden oben beschriebenen Modi, alternativ dazu
//!            kann man auch das Feld SoSFEnum interactionMode �ndern (auch im ILab-Panel)
//!   - Cursor + Page UP/DOWN: Bewegung des Teils entlang der Hauptachsen
//!
//! Au�erdem werden verschiedene Einheiten mitsamt Umrechnungsfaktor zur Verf�gung gestellt
class SO_MEASUREMENT_CLASS_SPEC UMDSoMeasureTool : public SoSeparator {
  //! macro that defines extended methods
  SO_NODE_HEADER(UMDSoMeasureTool);


public:

  //! Konstruktor
  UMDSoMeasureTool();
  //! Destruktor
  virtual ~UMDSoMeasureTool();

  //! must be called first to initialize the class in OpenInventor
  static void initClass();

  // ######## Fields ##############

  //! the first vertice of the measure tool - default value is (-10, 0, 0)
  SoSFVec3f startPos;

  //! the color of the measure tool
  SoSFColor color;

  //! shows the tool name
  SoSFBool toolNameFlag;
  //! the tool name
  SoSFString toolName;

  //! the step size for moving the tool vertices by the keyboard - default value is (0.01)
  SoSFFloat keyboardIncrement;

  //! shows the unit - default value is (FALSE)
  SoSFBool unitFlag;
  //! the unit - default value is mm (cmm)
  SoSFEnum unit;

  //! the kind of interaction mode - default value is dragMode
  SoSFEnum interactionMode;

  SoSFFloat scale;


private:

  // ##### Die Funktionen #####

  //! inits the measure tool fields
  void initMeasureTool();

  //! Feld-Sensoren initialisieren
  void initMeasureToolFieldSensors();

  //! haengt Knoten in Graphen
  void getObject();

  //! gibt einen LevelOfDetail-Knoten zurueck, der fuer die Font-Groesse verantwortlich ist
  SoLevelOfDetail* getLOD();

  //! Callback fuer Mousebutton-Events
  static void mousePressedCB(void* userData, SoEventCallback* eventCB);

  //! Callback fuer Tastatur-Events
  static void cursorPressCB(void* userData, SoEventCallback* eventCB);

  //! called if \c startPos has been changed
  static void startChangedCB(void* userData, SoSensor*);

  static void scaleChangedCB(void* userData, SoSensor*);

protected:

  //! �nderung der Unit-Beschriftung
  static void unitChangedCB(void* userData, SoSensor*);

  //! �nderung der Unit-Beschriftung
  static void interactionModeChangedCB(void* userData, SoSensor*);

  //! Setzt den darzustellenden Text
  virtual void getTextString(){};

  //! verr�t, ob zwei Vektoren gleich sind; mit einer Toleranz von 0.0001
  bool areEqual(const SbVec3f& vec1, const SbVec3f& vec2);

  // ####### virtuelle Funktionen ###########

  //! Welches Objekt wurde getroffen;
  //! muss von abgeleiteter Klasse implementiert werden
  virtual SbBool getPickedObjectMouseLeft(const SoPickedPoint* /*pickedPoint*/){ return FALSE; }

  //! jede abgeleitete Klasse muss die folgenden Funktionen implementieren;
  //! werden aufgerufen, wenn eine Position sich aendert
  virtual void pointChanged(){};

  //! die m�glichen Zusatztasten
  enum Taste {shift, control, alt, none};

  //! moves the tool by the keyboard
  virtual SbBool setArrowByKeyboard(float, float, float, Taste){ return FALSE; }

  //! the cursorUp key was pressed
  SbBool cursorUpPressed(Taste taste);
  //! the cursorDown key was pressed
  SbBool cursorDownPressed(Taste taste);
  //! the cursorLeft key was pressed
  SbBool cursorLeftPressed(Taste taste);
  //! the cursorRight key was pressed
  SbBool cursorRightPressed(Taste taste);
  //! the pageUp key was pressed
  SbBool pageUpPressed(Taste taste);
  //! the pageDown key was pressed
  SbBool pageDownPressed(Taste taste);

  //! the interaction modi
  enum MeasureTool_InteractionMode {inactive=0, directSelect=1,
                                    INTERACTION_INACTIVE=inactive,INTERACTION_DIRECT_SELECT=directSelect};
  //! the available units, must be synchronized with \c AutoMeasureTool_Unit
  enum MeasureTool_Unit {deg, mm, cmm, cm, m, ml, l};
  //! the conversion factor, 1 is mm resp. cmm
  SoSFInt32* _unitFactor;

  //! sets the active part of the tool and the kind of interaction
  void setInteractionMode(SoGroup *highSep, MeasureTool_InteractionMode wert, short whichDragger);
  //! returns the active part of the measure tool
  short getActivePart(SoGroup *highSep);

  //! deactivates a tool
  void resetHighLightNode(UMDSoMeasureTool* tool);

  //! Handler f�r linke Maustaste
  static UMDSoMeasureTool *_currentTool;
  //! weiterschalten der Farben
  static int _colorCounter;

  //! hier gehts los
  SoSeparator *_root;

  //! Switch-Knoten fuer Dragger
  SoSwitch *_switchDragger;

  //! der Inhaber aller LocateHighlight-Knoten
  SoSeparator *_highlightSep;

  //! hier mu� der Text angeh�ngt werden.
  //! Annotate bewirkt, da� der Text immer sichtbar ist
  SoAnnotation *_textSep;
  //! Translation des Textknotens
  SoTransform *_textTrafo;

  //! Farbe und Erscheinungsbild des Objektes
  SoMaterial *_objectMaterial;


  SoSphere* _sphere;

  //! Die Feld-Sensoren:
  SoFieldSensor *_startPosSens, *_toolNameFlagSens, *_toolNameSens, *_unitFlagSens, *_unitSens, *_interactionModeSens, *_scaleSens;
};

#endif
