
// CardsAgainstHumanityCreatorDlg.h: Headerdatei
//

#pragma once
#include <list>
#include <string>
#include "afxwin.h"

// CCardsAgainstHumanityCreatorDlg-Dialogfeld
class CCardsAgainstHumanityCreatorDlg : public CDialogEx
{
// Konstruktion
public:
	std::list<CString> deckList;
	CCardsAgainstHumanityCreatorDlg(CWnd* pParent = NULL);	// Standardkonstruktor
	std::list<CString> qList;
	std::list<CString> aList;
	CString currentDeck; 

// Dialogfelddaten
	enum { IDD = IDD_CARDSAGAINSTHUMANITYCREATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCreatecard();
	CString m_input;
	CListBox m_qBox;
	CListBox m_aBox;
	BOOL m_typeQ;
	int m_cardType;
//	int m_deckName;
	afx_msg void OnBnClickedDeckload();
	afx_msg void OnBnClickedDecksave();
	afx_msg void OnCbnSelchangeDeckname();
	afx_msg void OnBnClickedDelmarq();
	afx_msg void OnBnClickedDelmara();
	afx_msg void OnStnClickedCardnamestatic();
	CString m_deleteInput;
	afx_msg void OnBnClickedCancel();
	CComboBox m_deckNameControl;
	CString m_deckName;
	CString m_newDeck;
	afx_msg void OnBnClickedCreatedeck();
	void saveDecks();
	void loadDecks();
	afx_msg void OnBnClickedDeletedeck();
	CString m_QCounter;
	CString m_ACounter;
	afx_msg void OnEnSetfocusCreatedeletedeckinput();
	afx_msg void OnBnClickedDeletecopy();
	afx_msg void OnBnClickedDeletemarkedquestion();
	afx_msg void OnBnClickedDeletemarkedanswer();
};
