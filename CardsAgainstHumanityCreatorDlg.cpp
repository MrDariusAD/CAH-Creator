
// CardsAgainstHumanityCreatorDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CardsAgainstHumanityCreator.h"
#include "CardsAgainstHumanityCreatorDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <list>
#include <iostream>
#include <string>

#ifdef _DEBUG
#define dnew DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCardsAgainstHumanityCreatorDlg-Dialogfeld



CCardsAgainstHumanityCreatorDlg::CCardsAgainstHumanityCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCardsAgainstHumanityCreatorDlg::IDD, pParent)
	, m_input(_T(""))
	, m_typeQ(FALSE)
	, m_cardType(0)
	, m_deleteInput(_T(""))
	, m_deckName(_T(""))
	, m_newDeck(_T(""))
	, m_QCounter(_T(""))
	, m_ACounter(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	currentDeck = "";
}

void CCardsAgainstHumanityCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NewCardInput, m_input);
	DDX_Control(pDX, IDC_Questions, m_qBox);
	DDX_Control(pDX, IDC_Answers, m_aBox);
	//  DDX_Radio(pDX, IDC_Cardtype_Question, m_typeQ);
	DDX_Radio(pDX, IDC_Cardtype_Question, m_cardType);
	DDV_MinMaxInt(pDX, m_cardType, 0, 1);
	//  DDX_CBIndex(pDX, IDC_DeckName, m_deckName);
	//  DDV_MinMaxInt(pDX, m_deckName, 0, 6);
	DDX_Text(pDX, IDC_DeleteInput, m_deleteInput);
	DDX_Control(pDX, IDC_DeckName, m_deckNameControl);
	DDX_CBString(pDX, IDC_DeckName, m_deckName);
	DDX_Text(pDX, IDC_CreateDeleteDeckInput, m_newDeck);
	DDX_Text(pDX, IDC_QCounter, m_QCounter);
	DDX_Text(pDX, IDC_ACounter, m_ACounter);
}

BEGIN_MESSAGE_MAP(CCardsAgainstHumanityCreatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CreateCard, &CCardsAgainstHumanityCreatorDlg::OnBnClickedCreatecard)
	ON_BN_CLICKED(IDC_DeckLoad, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDeckload)
	ON_BN_CLICKED(IDC_DeckSave, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDecksave)
	ON_CBN_SELCHANGE(IDC_DeckName, &CCardsAgainstHumanityCreatorDlg::OnCbnSelchangeDeckname)
	ON_BN_CLICKED(IDC_DelMarQ, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDelmarq)
	ON_BN_CLICKED(IDC_DelMarA, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDelmara)
	ON_STN_CLICKED(IDC_CardNameStatic, &CCardsAgainstHumanityCreatorDlg::OnStnClickedCardnamestatic)
	ON_BN_CLICKED(IDCANCEL, &CCardsAgainstHumanityCreatorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CreateDeck, &CCardsAgainstHumanityCreatorDlg::OnBnClickedCreatedeck)
	ON_BN_CLICKED(IDC_DeleteDeck, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletedeck)
	ON_EN_SETFOCUS(IDC_CreateDeleteDeckInput, &CCardsAgainstHumanityCreatorDlg::OnEnSetfocusCreatedeletedeckinput)
	ON_BN_CLICKED(IDC_DeleteMarkedQuestion, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletemarkedquestion)
	ON_BN_CLICKED(IDC_DeleteMarkedAnswer, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletemarkedanswer)
END_MESSAGE_MAP()


// CCardsAgainstHumanityCreatorDlg-Meldungshandler

BOOL CCardsAgainstHumanityCreatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	loadDecks();

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CCardsAgainstHumanityCreatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CCardsAgainstHumanityCreatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CCardsAgainstHumanityCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedCreatecard()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	if(m_input != ""){


		if(m_cardType == 0){
			for(auto crs:qList){
				if(crs == m_input){
					AfxMessageBox(_T("Card already exists"));
					return;
				}
			}
			m_qBox.AddString(m_input);
			qList.push_back(m_input);
			m_QCounter.Format(_T("%d"),qList.size()-1);
			
		}

		if(m_cardType == 1){
			for(auto crs:aList){
				if(crs == m_input){
					AfxMessageBox(_T("Card already exists"));
					return;
				}
			}
			m_aBox.AddString(m_input);
			aList.push_back(m_input);
			m_ACounter.Format(_T("%d"),aList.size()-1);
		}
		
		m_input = "";
	}
	else AfxMessageBox(_T("Card Name can't be empty"));
	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDeckload()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	
	UpdateData(true);
	qList.clear();
	aList.clear();

	currentDeck = m_deckName;

	std::ifstream file;


	file.open(currentDeck+"Questions"+".sData",std::ios::in | std::ios::out);
	char output[50];

	if(file.good()){
	
		

		while(!file.eof()){
			file.getline(output,50);
			if(output != "")qList.push_back((*new CString(output)));
		}
		m_qBox.ResetContent();
		for(auto crs:qList){
			if(crs != "")m_qBox.AddString(crs);
		}
	}

	else MessageBox("Error while loading Question file!","QUESTION ERROR");

	file.close();


	file.open(currentDeck+"Answers"+".sData",std::ios::in);

	output[50];
	if(file.good()){

		while(!file.eof()){
			file.getline(output,50);
			if(output != "")aList.push_back((*new CString(output)));
		}
		m_aBox.ResetContent();
		for(auto crs:aList){
			if(crs != "")m_aBox.AddString(crs);
		}
		
		m_QCounter.Format(_T("%d"),qList.size()-1);
		m_ACounter.Format(_T("%d"),aList.size()-1);
	}
	
	else MessageBox("Error while loading Answer file!","ANSWER ERROR");

	file.close();

	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDecksave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	
	UpdateData(true);

	CStdioFile file;

	currentDeck = m_deckName;
	
	if(m_deckName == "")return;

	file.Open(currentDeck+"Questions"+".sData",CFile::modeCreate | CFile::modeReadWrite);



	for (CString cursor : qList){
		if(cursor != "")file.WriteString(cursor + "\n");
	}

	file.Close();
	file.Open(currentDeck+"Answers"+".sData",CFile::modeCreate | CFile::modeReadWrite);

	for (CString cursor : aList){
		if(cursor != "")file.WriteString(cursor + "\n");
	}

	MessageBox(_T("Deck \""+currentDeck+"\" saved =)"));

	file.Close();

	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnCbnSelchangeDeckname()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);


	if(m_deckName != currentDeck && currentDeck != ""){
		if(MessageBoxA("Switch deck? Not saved progress will be lost","Switch Deck?",MB_YESNO) == IDYES){
			m_qBox.ResetContent();
			m_aBox.ResetContent();
			qList.clear();
			aList.clear();
			OnBnClickedDeckload();
			m_QCounter.Format(_T("%d"),qList.size()-1);
			m_ACounter.Format(_T("%d"),aList.size()-1);
		}
		else{
			m_deckName = currentDeck;
		}
		
	}
	if(currentDeck == "")OnBnClickedDeckload();
	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDelmarq()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	CString del = m_deleteInput;
	bool removed = false;

	for (auto crs:qList){
		if (crs == del){
			qList.remove(crs);
			removed = true;
			break;
		}
	}

	if(removed){
		m_qBox.ResetContent();
		for(auto crs:qList){
			if(crs != "")m_qBox.AddString(crs);
		}
		AfxMessageBox(("Card "+del+" deleted"));
	}

	else AfxMessageBox("Card "+del+" not found");

	m_QCounter.Format(_T("%d"),qList.size()-1);
	m_ACounter.Format(_T("%d"),aList.size()-1);

	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDelmara()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	CString del = m_deleteInput;
	bool removed = false;

	for (auto crs:aList){
		if (crs == del){
			aList.remove(crs);
			removed = true;
			break;
		}
	}

	if(removed){
		m_aBox.ResetContent();
		for(auto crs:aList){
			if(crs != "")m_aBox.AddString(crs);
		}
		AfxMessageBox(("Card "+del+" deleted"));
	}

	else AfxMessageBox("Card "+del+" not found");

	m_QCounter.Format(_T("%d"),qList.size()-1);
	m_ACounter.Format(_T("%d"),aList.size()-1);

	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnStnClickedCardnamestatic()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedCancel()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if(currentDeck != "")if(MessageBoxA("Do you wish to save before exit?","Save?",MB_YESNO) == IDYES)OnBnClickedDecksave();


	CDialogEx::OnCancel();
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedCreatedeck()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	if(m_newDeck != ""){
		CStdioFile file;
		deckList.push_back(m_newDeck);
		m_deckNameControl.AddString(m_newDeck);
		saveDecks();
		AfxMessageBox("Deck "+m_newDeck+" created");

		file.Open(m_newDeck+"Questions"+".sData",CFile::modeCreate | CFile::modeWrite);
		file.Close();

		file.Open(m_newDeck+"Answers"+".sData",CFile::modeCreate | CFile::modeWrite);
		file.Close();
		m_newDeck = "";
	}
	else AfxMessageBox("Please enter a Deck Name");

	UpdateData(false);
}

void CCardsAgainstHumanityCreatorDlg::saveDecks()
{
	UpdateData(true);

	CStdioFile file;


	file.Open("Decks.sData",CFile::modeCreate | CFile::modeReadWrite);

	for (CString cursor : deckList){
		if(cursor != "")file.WriteString(cursor + "\n");
	}

	file.Close();


}

void CCardsAgainstHumanityCreatorDlg::loadDecks()
{
	std::ifstream file;


	file.open("Decks.sData",std::ios::in);
	if(file.good()){
		char output[50];

		while(!file.eof()){
			file.getline(output,50);
			if(output != "")deckList.push_back((*new CString(output)));
		}
		
		for(auto crs: deckList)
		{
			if(crs != "")m_deckNameControl.AddString(crs);
		}
	}
	else MessageBox("Error while loading Decks! Creating new File","Decks ERROR");
	file.close();

}

void CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletedeck()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	if(MessageBoxA("Are you sure? All Deck Files will be deleted","Delete?",MB_YESNO) == IDYES){
		remove(m_deckName+"Questions"+".sData");
		remove(m_deckName+"Answers"+".sData");
		deckList.remove(m_deckName);
		m_deckNameControl.DeleteString(m_deckNameControl.GetCurSel());
		m_qBox.ResetContent();
		m_aBox.ResetContent();
		currentDeck = "";
		m_QCounter.Format(_T("%d"),qList.size()-1);
		m_ACounter.Format(_T("%d"),aList.size()-1);
		saveDecks();
	}
	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnEnSetfocusCreatedeletedeckinput()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletecopy()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletemarkedquestion()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	int del = 0;
	for(auto crs:qList){
		if(del == m_qBox.GetCurSel()){
			qList.remove(crs);
			m_qBox.DeleteString(del);
			break;
		}
		del++;
	}
	m_QCounter.Format(_T("%d"),qList.size()-1);
	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDeletemarkedanswer()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	UpdateData(true);
	int del = 0;
	for(auto crs:aList){
		if(del == m_aBox.GetCurSel()){
			aList.remove(crs);
			m_aBox.DeleteString(del);
			break;
		}
		del++;
	}
	m_ACounter.Format(_T("%d"),aList.size()-1);
	UpdateData(false);
}
