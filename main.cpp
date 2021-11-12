#ifndef UNICODE
#define UNICODE
#endif 

//includes
#include <windows.h>
#include <CommCtrl.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define NEXT_BUTTON 4
#define PREVIOUS_BUTTON 5
#define ECHO_BUTTON 6
#define FINISH_BUTTON 7

using namespace std;
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void fControls(HWND);
void sControls(HWND);
//void Hide(HWND);


//Define handlers
HMENU hMenu;
HWND fMenu;
HWND sMenu;
HWND hLabel;
HWND hname;
HWND hOut;//output handle
HWND hNBut, hPBut, hDBut, hBut;
HWND hTb;
char out[2400];
char hnamec[100];

// Register the window class.
const wchar_t CLASS_NAME[] = L"myWindowClass";


//Execute
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(CLASS_NAME, L"My Book!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 640, 480, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//Main Window Functionality
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int val;
	switch (msg)
	{
	
	case WM_COMMAND:

		switch (wp)
		{
		case FILE_MENU_EXIT:
			val = MessageBoxW(NULL, L"Program Terminate", L"Exit", MB_OK | MB_ICONINFORMATION);
			if (val == IDOK)
			{
				DestroyWindow(hWnd);
			}
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case NEXT_BUTTON:
			//ShowWindow(void fControls(HWND hWnd), SW_HIDE);
			sControls(hWnd);
			GetWindowTextA(hname, hnamec, 100);
			DestroyWindow(hLabel);
			DestroyWindow(hname);
			DestroyWindow(hNBut);
			MessageBeep(MB_ICONINFORMATION);
			break;
		case PREVIOUS_BUTTON:
			//ShowWindow(void sControls(HWND hWnd), SW_HIDE);
		    //fControls(hWnd);
		    fControls(hWnd);
			strcpy(out, hnamec);
			SetWindowTextA(hname, out);
			DestroyWindow(hDBut);
			DestroyWindow(hBut);
			DestroyWindow(hOut);
			DestroyWindow(hPBut);

			MessageBeep(MB_ICONINFORMATION);
			break;
		case ECHO_BUTTON:

			//Variables from forms to  char

			strcpy(out, "Your name is ");
			strcat(out, hnamec);
			strcat(out, ". ");

			SetWindowTextA(hOut, out);

			break;
		case FINISH_BUTTON:
			MessageBeep(MB_ICONINFORMATION);
			PostQuitMessage(0);
			break;
		}
	
		break;
	case WM_CREATE: //By the initial window creation executes
		AddMenus(hWnd);
		fControls(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

//Window menu TOP BAR Functionality
void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_EXIT, "kILL");
	AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	SetMenu(hWnd, hMenu);
}

//Labels, Inputs, onscreen output

void fControls(HWND hWnd)
{
	//nameLabel
	hTb = CreateWindow (L"Edit", L"PRESS TAB HERE", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | WS_VSCROLL | ES_WANTRETURN | WS_TABSTOP,
    20, 60, 300, 50, hWnd, NULL, NULL, NULL);
	hLabel = CreateWindowExW(NULL, L"static", L"Insert your Name: ", WS_VISIBLE | WS_CHILD, 20, 20, 125, 20, hWnd, NULL, NULL, NULL);
	
	//nameInput
	hname = CreateWindowW(L"Edit", L"",  WS_VISIBLE | WS_CHILD | WS_BORDER | WS_GROUP, 140, 18, 180, 20, hWnd, NULL, NULL, NULL);

	//nextButton
	hNBut = CreateWindow(L"button", L"Next", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON |  WS_GROUP, 512, 7, 80, 80, hWnd, (HMENU)NEXT_BUTTON, NULL, NULL);
}

void sControls(HWND hWnd)
{
	//previousButton
	hPBut = CreateWindow(L"button", L"Previous", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON , 20, 200, 80, 40, hWnd, (HMENU)PREVIOUS_BUTTON, NULL, NULL);

	//DisplayButton
	hDBut = CreateWindow(L"button", L"Display", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON , 120, 200, 80, 40, hWnd, (HMENU)ECHO_BUTTON, NULL, NULL);

	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 284, 480, 120, hWnd, NULL, NULL, NULL);
		
	//finishButton
	hBut = CreateWindowW(L"Button", L"Finish", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON , 512, 284, 80, 120, hWnd, (HMENU)FINISH_BUTTON, NULL, NULL);
}

