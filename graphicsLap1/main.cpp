#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <cmath>
#include "iostream"
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
int x,y,x2,y2;
int counter=0;
bool isPaint2 = false;
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
void drawLine(HDC hdc , int xStart , int yStart , int xEnd , int yEnd , COLORREF color);
void drawLine2(HDC hdc , int xStart , int yStart , int xEnd , int yEnd , COLORREF color);
void drawLine3(HDC hdc , int xStart , int yStart , int xEnd , int yEnd , COLORREF color);
int WINAPI WinMain (HINSTANCE hThisInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpszArgument/*command line arguments*/,
        int nCmdShow/*default view or minimized or maximized*/){
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Line drawer"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            544,                 /* The programs width */
            375,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;
    switch (message)                  /* handle the messages */
    {
    case WM_PAINT:

        //cout<<isPaint2<<endl;
        if(isPaint2){
            BeginPaint(hwnd , &paintStruct);
//            MoveToEx(paintStruct.hdc,x,y,NULL);
//            LineTo(paintStruct.hdc,x2,y2);
//                drawLine(paintStruct.hdc , x,y,x2,y2,RGB(250,0,0));
//            drawLine2(paintStruct.hdc , x,y,x2,y2,RGB(250,0,0));
            drawLine3(paintStruct.hdc , x,y,x2,y2,RGB(250,0,0));
            isPaint2 = false;
            EndPaint(hwnd,&paintStruct);
        }
        break;
    case WM_LBUTTONDOWN :
        counter++;
        cout<<counter<<endl;
        if(counter%2==0){
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            counter=0;
            isPaint2 = true;
        }
        else{
            x = LOWORD(lParam);
            y = HIWORD(lParam);
        }
        InvalidateRect(hwnd , NULL, false);
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void drawLine(HDC hdc , int xStart , int yStart , int xEnd , int yEnd , COLORREF color){
    int deltaX = xEnd - xStart;
    int deltaY = yEnd - yStart;
    if(abs(deltaX) >= abs(deltaY)){
        if(xStart > xEnd ){
            swap(xStart , xEnd);
            swap(yStart , yEnd);
        }
        double tempY ;
        int tempX = xStart;
        SetPixel(hdc , xStart , yStart,color);
        while(tempX<xEnd){
            tempX++;
            tempY = yStart + ((deltaY * ((double) tempX-xStart))/deltaX);
            SetPixel(hdc , tempX ,(int)round(tempY),color);
        }
    }else{
        if(yStart > yEnd){
            swap(xStart , xEnd);
            swap(yStart , yEnd);
        }
        int tempY = yStart;
        double tempX;
        SetPixel(hdc , xStart , tempY , color);
        while(tempY<yEnd){
            tempY++;
            tempX = xStart + ((deltaX)*((double)(tempY-yStart)))/deltaY;
            SetPixel(hdc , (int)round(tempX) , tempY , color);
        }
    }
}
void drawLine2(HDC hdc , int xStart , int yStart , int xEnd , int yEnd , COLORREF color){
    int deltaX = xEnd - xStart;
    int deltaY = yEnd - yStart;
    double slope = (double)deltaY / deltaX;
    double inverseSlope = (double)deltaX/deltaY;
    if(abs(deltaX)>=abs(deltaY)){
        if(xStart > xEnd){
            swap(xStart , xEnd);
            swap(yStart , yEnd);
        }
        double tempY = yStart;
        int tempX = xStart;
        SetPixel(hdc , xStart , yStart , color);
        while(tempX<xEnd){
            tempX++;
            tempY = tempY + slope;
            SetPixel(hdc, tempX , (int)round(tempY) , color);
        }
    }else{
        if(yStart > yEnd){
            swap(xStart , xEnd);
            swap(yStart , yEnd);
        }
        int tempY = yStart;
        double tempX = xStart ;
        SetPixel(hdc , xStart , yStart , color);
        while(tempY<yEnd){
            tempY++;
            tempX = tempX+ inverseSlope;
            SetPixel(hdc , (int)round(tempX) , tempY,color);
        }
    }
}
//this function is not working
void drawLine3(HDC hdc , int xStart , int yStart , int xEnd , int yEnd , COLORREF color){
    int deltaX = xEnd - xStart;
    int deltaY = yEnd - yStart;
    if(abs(deltaX)>=abs(deltaY)){
        if(xStart>xEnd){
            swap(xStart , xEnd);
            swap(yStart, yEnd);
        }
        int p = 2*deltaY*xStart - 2*deltaX*yStart;
        int tempX = xStart;
        int tempY = yStart;
        int doubleDeltaY = 2*deltaY;
        int doubleDeltaX = 2*deltaX;
        SetPixel(hdc,tempX,tempY,color);
        while(tempX < xEnd){
            tempX++;
            if(p<0){
                p = p+doubleDeltaY;
            }else{
                tempY++;
                p = p + doubleDeltaY - doubleDeltaX;
            }
            SetPixel(hdc , tempX , tempY , color);
        }
    }else{
        if(yStart>yEnd){
            swap(xStart , xEnd);
            swap(yStart, yEnd);
        }
        int p = 2*deltaX*yStart - 2*deltaY*xStart;
        int tempX = xStart;
        int tempY = yStart;
        int doubleDeltaY = 2*deltaY;
        int doubleDeltaX = 2*deltaX;
        SetPixel(hdc,tempX,tempY,color);
        while(tempY < yEnd){
            tempY++;
            if(p<0){
                p = p+doubleDeltaX;
            }else{
                tempX++;
                p = p + doubleDeltaX - doubleDeltaY;
            }
            SetPixel(hdc , tempX , tempY , color);
        }
    }
}