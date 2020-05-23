#include <windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4


/* window procedure */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND hwnd);
void addControls(HWND);

HWND hName, hAge, hOut;
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
    MSG messages;        // for messages queue manipulation.
    WNDCLASSEX Wn;       // data struct for window class.
    HWND hWnd;           // handle for window.

    /* define window class */
    Wn.cbSize = sizeof(WNDCLASSEX);
    Wn.style = CS_DBLCLKS;
    Wn.hInstance = hInst;
    Wn.lpszClassName = "WindowClassName";
    Wn.lpfnWndProc = WndProc;

    /* icons, cursor and menu */
    Wn.hIcon = LoadIcon(hInst, "MAINICON"); /* default icon */
    Wn.hIconSm = LoadIcon(hInst, "MAINICON"); /* default icon */
    Wn.hCursor = LoadCursor(NULL, IDC_ARROW); /* cursor */
    Wn.lpszMenuName = NULL; /* no menu */
    Wn.cbClsExtra = 0;
    Wn.cbWndExtra = 0;

    /* window background color */
    Wn.hbrBackground = GetSysColorBrush(COLOR_BTNFACE); 
    RegisterClassEx(&Wn);
    hWnd = CreateWindowEx(0,                     /* extended window style */
                          "WindowClassName",     /* registered class */
                          "MELOMORTE APPLICATION", /* window title */
                          WS_OVERLAPPEDWINDOW,   /* default window style */
                          CW_USEDEFAULT,         /* x position */
                          CW_USEDEFAULT,         /* y position */
                          250,                   /* width of window */
                          250,                   /* heigth of window */
                          HWND_DESKTOP,          /* The window is a child-window to desktop */
                          NULL,                  /* no menu */ 
                          hInst,                 /* Program Instance handler */
                          NULL);                 /* No Window Creation data */
                          
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);  

    /* loop messages. run until GetMessage return 0*/  
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages); /* translate virtual keys into character messages*/
        DispatchMessage(&messages);  /* Send message to WndProc */
    }
    /* return value to system */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    	case WM_COMMAND:
    		switch(wParam)
			{
			case FILE_MENU_EXIT:
				DestroyWindow(hwnd);
				break;
			case FILE_MENU_NEW:
				MessageBeep(MB_ICONINFORMATION);
            case GENERATE_BUTTON:
            	
            	char name[30], age[5], out[50];
            	
            	GetWindowText(hName, name, 30);
            	GetWindowText(hAge, age, 5);
            	
            	strcpy(out, name);
            	strcat(out, " is ");
            	strcat(out,age);
            	strcat(out, " years old.");
            	
            	SetWindowText(hOut, out);
            	break;
			default:
				break;
			}
			break;
    	case WM_CREATE:
			addMenus(hwnd);
			addControls(hwnd);
    		break;
        case WM_DESTROY:
            PostQuitMessage(0); /* send a WM_QUIT to the message queue */
            break;
        default:                /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void addMenus(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();
	
	//Submenu.
	AppendMenu(hSubMenu,
			   MF_STRING,
			   NULL,
			   "Sub Menu");
	
	//new file.
	AppendMenu(hFileMenu,
			   MF_STRING,
			   FILE_MENU_NEW,
			   "New File");

    //open file.
	AppendMenu(hFileMenu,
			   MF_POPUP,
			   (UINT_PTR)hSubMenu,
			   "Open Sub Menu");

    //separator.
	AppendMenu(hFileMenu,
	           MF_SEPARATOR,
			   NULL,
			   NULL);
	
	AppendMenu(hFileMenu,
			   MF_STRING,
			   FILE_MENU_EXIT,
			   "Exit");		   			   	
    //file.
	AppendMenu(hMenu,
	           MF_POPUP,
			   (UINT_PTR)hFileMenu,
			   "File");
			   
    //help.
	AppendMenu(hMenu,
	           MF_STRING,
			   NULL,
               "Help");
			   
			   	
	SetMenu(hwnd, hMenu);	
}

void addControls(HWND hwnd)
{
	CreateWindowW(L"Static", 
	              L"Name: ",
				  WS_VISIBLE | WS_CHILD,
				  20, 
				  20, 
				  90, 
				  30,
				  hwnd,
				  NULL,
				  NULL,
				  NULL);
				  
    hName = CreateWindowW(L"Edit", 
	              L"",
				  WS_VISIBLE | WS_CHILD | WS_BORDER,
				  70, 
				  20, 
				  150, 
				  20,
				  hwnd,
				  NULL,
				  NULL,
				  NULL);
				  
    CreateWindowW(L"Static", 
	              L"Age: ",
				  WS_VISIBLE | WS_CHILD,
				  20, 
				  50, 
				  150, 
				  30,
				  hwnd,
				  NULL,
				  NULL,
				  NULL);
				  
    hAge = CreateWindowW(L"Edit", 
	              L"",
				  WS_VISIBLE | WS_CHILD | WS_BORDER,
				  70, 
				  50, 
				  150, 
				  20,
				  hwnd,
				  NULL,
				  NULL,
				  NULL);
				  
    CreateWindowW(L"Button", 
	              L"Generate",
				  WS_VISIBLE | WS_CHILD | WS_BORDER,
				  70, 
				  80, 
				  150, 
				  20,
				  hwnd,
				  (HMENU)GENERATE_BUTTON,
				  NULL,
				  NULL);
				  
    hOut = CreateWindowW(L"Edit", 
	              L"",
				  WS_VISIBLE | WS_CHILD | WS_BORDER,
				  70, 
				  110, 
				  150, 
				  20,
				  hwnd,
				  NULL,
				  NULL,
				  NULL);
}
