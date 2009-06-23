//----------------------------------------------------------------------------------
//! Project global and OS specific declarations
/*!
// \file    UMDDraw2DSilhouetteSystem.h
// \author  Bj�rn Meyer
// \date    2004-09-28
//
*/
//----------------------------------------------------------------------------------


#ifndef __UMDSOVIEW2DEXTENSIONSSYSTEM_H__
#define __UMDSOVIEW2DEXTENSIONSSYSTEM_H__


// DLL export macro definition
#ifdef WIN32


//Unterdr"uckt die Warnung warning C4275: class 'SoCoordinate4' ist keine DLL-Schnittstelle 
//und wurde als Basisklasse fuer die DLL-Schnittstelle class '...' verwendet
#pragma warning (disable : 4275)

// Disable warning C4514: '/=' : Nichtreferenzierte Inline-Funktion wurde entfernt
#pragma warning (disable : 4514)

// Disable warning C4244: 'argument' : Konvertierung von 'int' in 'short', moeglicher Datenverlust (at inventor node initialization)
#pragma warning (disable : 4244)

// Disable warning for release mode: Warning C4710: '__thiscall XXX::YYY(ZZZ)' ist keine Inline-Funktion
#pragma warning(disable : 4710 )

// disable warning: Keine Definitionen fuer die Inline-Funktion 
#pragma warning (disable : 4506)

// disable warning:std::reverse_iterator... Bezeichner wurde auf '255' Zeichen in den Debug-Informationen reduziert
#pragma warning (disable : 4786)

// Include often used libraries automatically and disable its warnings
// to be able to compile the ml in highest warning level. 
#pragma warning (disable: 4018)

// Nichtreferenzierte lokale Funktion wurde entfernt
#pragma warning (disable : 4505)


#ifdef UMDSOVIEW2DEXTENSIONS_EXPORTS
// Use the UMDDRAW2DSILHOUETTE_EXPORT macro to export classes and functions
#define UMDSOVIEW2DEXTENSIONS_EXPORT __declspec(dllexport)
#else
// If included by external modules, exported symbols are declared as import symbols
#define UMDSOVIEW2DEXTENSIONS_EXPORT __declspec(dllimport)
#endif

#else
// No export declarations are necessary for non-Windows systems
#define UMDSOVIEW2DEXTENSIONS_EXPORT
#endif


#endif
// __UMDSOVIEW2DEXTENSIONSSYSTEM_H__
