
// CardsAgainstHumanityCreator.h: Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// CCardsAgainstHumanityCreatorApp:
// Siehe CardsAgainstHumanityCreator.cpp f�r die Implementierung dieser Klasse
//

class CCardsAgainstHumanityCreatorApp : public CWinApp
{
public:
	CCardsAgainstHumanityCreatorApp();

// �berschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CCardsAgainstHumanityCreatorApp theApp;