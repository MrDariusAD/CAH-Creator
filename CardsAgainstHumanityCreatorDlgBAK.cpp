
// CardsAgainstHumanityCreatorDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CardsAgainstHumanityCreator.h"
#include "CardsAgainstHumanityCreatorDlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
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
	, m_deckName(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	DDX_CBIndex(pDX, IDC_DeckName, m_deckName);
	DDV_MinMaxInt(pDX, m_deckName, 0, 6);
}

BEGIN_MESSAGE_MAP(CCardsAgainstHumanityCreatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CreateCard, &CCardsAgainstHumanityCreatorDlg::OnBnClickedCreatecard)
	ON_BN_CLICKED(IDC_DeckLoad, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDeckload)
	ON_BN_CLICKED(IDC_DeckSave, &CCardsAgainstHumanityCreatorDlg::OnBnClickedDecksave)
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
	
	if(m_cardType == 0){
		m_qBox.AddString(m_input);
		qList.push_back(m_input);
	}

	if(m_cardType == 1){
		m_aBox.AddString(m_input);
		aList.push_back(m_input);
	}

	UpdateData(false);
}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDeckload()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	currentDeck = (deck)m_deckName;

	CStdioFile file;
	CString filename;

	UpdateData(true);
	
	switch(m_deckName){
	case 0:filename = "Anime";
		break;
	case 1:filename = "HIMYM_TBBT";
		break;
	case 2:filename = "GoT";
		break;
	case 3:filename = "Childhood";
		break;
	case 4:filename = "Gaming";
		break;
	case 5:filename = "Songs";
		break;
	case 6:filename = "DarkHumor";
		break;
	default:MessageBox(_T("Fehler beim Laden der Datei. Dateiname konnte nicht ermittelt werden!"));
		break;
	};

	file.Open(filename+"Questions",CFile::modeWrite);

	CString loader;

		while (true){
			try{
				bool eof = file.ReadString(loader);
				if(!eof)break;
			}
			catch (CFileException e) {
				char cBuf[1000];
				e.GetErrorMessage(cBuf, 1000);
				AfxMessageBox(cBuf);
			}
			qList.push_back(loader);
		}

	file.Close();

		switch(m_deckName){
	case 0:filename = "Anime";
		break;
	case 1:filename = "HIMYM_TBBT";
		break;
	case 2:filename = "GoT";
		break;
	case 3:filename = "Childhood";
		break;
	case 4:filename = "Gaming";
		break;
	case 5:filename = "Songs";
		break;
	case 6:filename = "DarkHumor";
		break;
	default:MessageBox(_T("Fehler beim Laden der Datei. Dateiname konnte nicht ermittelt werden!"));
		break;
	};

	file.Open(filename+"Answers",CFile::modeRead);


		while (true){
			try{
				bool eof = file.ReadString(loader);
				if(!eof)break;
			}
			catch (CFileException e) {
				char cBuf[1000];
				e.GetErrorMessage(cBuf, 1000);
				AfxMessageBox(cBuf);
			}
			aList.push_back(loader);
		}

}


void CCardsAgainstHumanityCreatorDlg::OnBnClickedDecksave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CStdioFile file;
	CString filename;

	UpdateData(true);
	
	switch(m_deckName){
	case 0:filename = "Anime";
		break;
	case 1:filename = "HIMYM_TBBT";
		break;
	case 2:filename = "GoT";
		break;
	case 3:filename = "Childhood";
		break;
	case 4:filename = "Gaming";
		break;
	case 5:filename = "Songs";
		break;
	case 6:filename = "DarkHumor";
		break;
	default:MessageBox(_T("Fehler beim Speichern der Datei. Dateiname konnte nicht ermittelt werden!"));
		break;
	};

	try{
	file.Open(filename+"Questions",CFile::modeCreate | CFile::modeReadWrite);



	for (CString cursor : qList){
		file.WriteString(cursor + ";\n");
	}
	}
	catch (CFileException e) {
		char cBuf[1000];
		e.GetErrorMessage(cBuf, 1000);
		AfxMessageBox(cBuf);
	}

	file.Close();

	switch(m_deckName){
	case 0:filename = "Anime";
		break;
	case 1:filename = "HIMYM_TBBT";
		break;
	case 2:filename = "GoT";
		break;
	case 3:filename = "Childhood";
		break;
	case 4:filename = "Gaming";
		break;
	case 5:filename = "Songs";
		break;
	case 6:filename = "DarkHumor";
		break;
	default:MessageBox(_T("Fehler beim Speichern der Datei. Dateiname konnte nicht ermittelt werden!"));
		break;
	};

	file.Open(filename+"Answers",CFile::modeCreate | CFile::modeReadWrite);

	for (CString cursor : aList){
		file.WriteString(cursor + ";\n");
	}

	MessageBox(_T("Speichern erfolgreich abgechlossen"));

	file.Close();

	UpdateData(false);
}
