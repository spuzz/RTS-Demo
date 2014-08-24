//
///*
// *		This Code Was Created By Jeff Molofee 2000
// *		A HUGE Thanks To Fredric Echols For Cleaning Up
// *		And Optimizing The Base Code, Making It More Flexible!
// *		If You've Found This Code Useful, Please Let Me Know.
// *		Visit My Site At nehe.gamedev.net
// */
//
//#define _WIN32_WINDOWS 0x0410
//#define WINVER 0x0400
//#include <windows.h>		// Header File For Windows
//#include <stdio.h>			// Header File For Standard Input/Output
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
//#include "texLoad.h"
//#include "grid.h"
//#include "setup.h"
//#include <png.h>
//#include "control.h"
//
//
//using namespace std;
//
//#define ZOOM -20.f
//setup set;
//control* ctrl;
//
//HDC			hDC=NULL;		// Private GDI Device Context
//HGLRC		hRC=NULL;		// Permanent Rendering Context
//HWND		hWnd=NULL;		// Holds Our Window Handle
//HINSTANCE	hInstance;		// Holds The Instance Of The Application
//RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
//
//bool	keys[258];			// Array Used For The Keyboard Routine
//bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
//bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
//bool	light;				// Lighting ON/OFF ( NEW )
//bool	lp;					// L Pressed? ( NEW )
//bool	fp;					// F Pressed? ( NEW )
//
//
//  
//float mousePosition[2] = {0.0f,0.0f};
//float curXCam = 0;
//float curYCam = 0;
//float curXEndCam = 6400;
//float curYEndCam = 6420;
//float mouseWheel = 0;
//float zoomspeed = 300;
//GLfloat	xrot;				// X Rotation
//GLfloat	yrot;				// Y Rotation
//GLfloat xspeed;				// X Rotation Speed
//GLfloat yspeed;				// Y Rotation Speed
//GLfloat	z=-5.0f;			// Depth Into The Screen
//
//GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
//GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
//GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };
//
//GLuint	filter;				// Which Filter To Use
//GLuint	texture[3];			// Storage For 3 Textures
//
//LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
//
//int LoadGLTextures()									// Load Bitmaps And Convert To Textures
//{		
//	//texture[0] = texLoad::LoadGLTextures("Data/Dfloor.bmp",texture[0]);
//	return 1;// Return The Status
//}
//
//GLvoid moveScreen()	// Resize And Initialize The GL Window
//{
//	// Calculate The Aspect Ratio Of The Window
//	glMatrixMode(GL_PROJECTION);
//
//	glPushMatrix();
//
//	glLoadIdentity();
//	gluOrtho2D(curXCam, curXEndCam, curYCam, curYEndCam);
//
//	glMatrixMode(GL_MODELVIEW);
//
//}
//GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
//{
//	if (height==0)										// Prevent A Divide By Zero By
//	{
//		height=1;										// Making Height Equal One
//	}
//	glViewport(0,height*0.2,width*0.7,height);
//	// Calculate The Aspect Ratio Of The Window
//	glMatrixMode(GL_PROJECTION);
//
//	glPushMatrix();
//
//	glLoadIdentity();
//	gluOrtho2D(curXCam, curXEndCam, curYCam, curYEndCam);
//
//	glMatrixMode(GL_MODELVIEW);
//
//}
//
//GLvoid zoomIn() {
//	POINT cursorPos;
//	GetCursorPos(&cursorPos);
//	float x = 0;
//	float y = 0;
//	float xPerc = 0;
//	float yPerc = 0;
//	x = cursorPos.x - 8; 
//	y = cursorPos.y - 8;
//	xPerc = (x/ WindowRect.right) *100;
//	yPerc = (y/ WindowRect.bottom) *100;
//	if(curXEndCam - curXCam > 100 && curYEndCam - curYCam > 100) {
//		curXCam += (zoomspeed/100)*xPerc;
//		curYCam += (zoomspeed/100)*(100-yPerc);
//		curXEndCam -= (zoomspeed/100)*(100-xPerc);
//		curYEndCam -= (zoomspeed/100)*yPerc;
//	}
//	glMatrixMode(GL_PROJECTION);
//
//	glPushMatrix();
//
//	glLoadIdentity();
//	gluOrtho2D(curXCam, curXEndCam, curYCam, curYEndCam);
//
//	glMatrixMode(GL_MODELVIEW);
//}
//
//GLvoid zoomOut() {
//	POINT cursorPos;
//	GetCursorPos(&cursorPos);
//	float x = 0;
//	float y = 0;
//	float xPerc = 0;
//	float yPerc = 0;
//	x = cursorPos.x; 
//	y = cursorPos.y;
//	xPerc = x/ WindowRect.right;
//	yPerc = y/ WindowRect.bottom;
//	glMatrixMode(GL_PROJECTION);
//
//	glPushMatrix();
//
//	glLoadIdentity();
//	int newCurXCam = curXCam - zoomspeed/2;
//	int newCurYCam = curYCam - zoomspeed/2;
//	int newCurXEndCam = curXEndCam + zoomspeed/2;
//	int newCurYEndCam = curYEndCam + zoomspeed/2;
//	bool maxed = false;
//	if(newCurXCam < 0) {
//		newCurXEndCam -= newCurXCam;
//		newCurXCam = 0;
//		if(newCurXEndCam > 6400) {
//			newCurXEndCam = 6400;
//			maxed = true;
//		}
//	}
//	if(newCurXEndCam > 6400 & maxed != true) {
//		newCurXCam += (6400 - newCurXEndCam);
//		newCurXEndCam = 6400;
//		if(newCurXCam < 0) {
//			newCurXCam = 0;
//			maxed = true;
//		}
//	}
//
//
//	if(newCurYCam < 0 & maxed != true) {
//		newCurYEndCam -= newCurYCam;
//		newCurYCam = 0;
//		if(newCurYEndCam > 6420) {
//			newCurYEndCam = 6420;
//			maxed = true;
//		}
//	}
//	if(newCurYEndCam > 6420 & maxed != true) {
//		newCurYCam += (6420 - newCurYEndCam);
//		newCurYEndCam = 6420;
//		if(newCurYCam < 0) {
//			newCurYCam = 0;
//			maxed = true;
//		}
//	}
//	if(maxed != true) {
//		curXCam = newCurXCam;
//		curYCam = newCurYCam;
//		curXEndCam = newCurXEndCam;
//		curYEndCam = newCurYEndCam;
//	}
//	gluOrtho2D(curXCam, curXEndCam, curYCam, curYEndCam);
//
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void getMouseInfo()
//{
//   static POINT lastMouse = {0,0};
//   //Get current mouse position
//   GetCursorPos(&lastMouse);
//   //Set cursor position to some point so that the
//   //movement can be calculated later on 
//   //SetCursorPos(320,240);
//    
//   //Calculate movement of the mouse with the above coords
//   float moveX = float((320 - lastMouse.x))/100.0f;
//   float moveY = float((240 - lastMouse.y))/100.0f;
//   
//   //Update mouse position
//   mousePosition[0] = 6400*((float(lastMouse.x)/float(WindowRect.right)));
//   mousePosition[1] = 6420 - 6420*((float(lastMouse.y)/float(WindowRect.bottom)));
//   cout<<"MOUSE POS "<<lastMouse.x/WindowRect.right<< " " << lastMouse.y/WindowRect.bottom<<endl;
//   if(mousePosition[0] > 6400) {
//	   mousePosition[0] = 6350;
//	   if(curXEndCam < 6351) {
//		   curXEndCam += 50;
//		   curXCam += 50;
//	   }
//   }
//   else if (mousePosition[0] < 50) {
//	   mousePosition[0] = 50;
//	   if(curXCam > 49) {
//		   curXEndCam -= 50;
//		   curXCam -= 50;
//	   }
//
//   }
//   if(mousePosition[1] > 6320) {
//	   mousePosition[1] = 6320;
//	   if(curYEndCam < 6371) {
//		   curYEndCam += 50;
//		   curYCam += 50;
//	   }
//   }
//   else if (mousePosition[1] < 0) {
//	   mousePosition[1] = 50;
//	   if(curYCam > 49) {
//		   curYEndCam -= 50;
//		   curYCam -= 50;
//	   }
//   }
//   moveScreen();
//}
//int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
//{
//
//	freopen("Data/file.txt", "w", stdout);
//	printf ("OPENING FILE");
//	if (!LoadGLTextures())								// Jump To Texture Loading Routine
//	{
//		return FALSE;									// If Texture Didn't Load Return FALSE
//	}
//	ctrl = new control();
//	set.createGrid(("Data/map.txt"));
//	ctrl->setMainGrid(set.getGrid());
//	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
//	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
//	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
//	glClearDepth(1.0f);									// Depth Buffer Setup
//	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
//	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
//
//	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
//	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
//	glEnable(GL_LIGHT1);								// Enable Light One
//	return TRUE;										// Initialization Went OK
//}
//
//int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
//{
//	getMouseInfo();
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_BLEND);
//	glLoadIdentity();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
//	ctrl->go();
//	xrot+=xspeed;
//	yrot+=yspeed;
//
//	return TRUE;										// Keep Going
//}
//
//GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
//{
//	if (fullscreen)										// Are We In Fullscreen Mode?
//	{
//		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
//		ShowCursor(TRUE);								// Show Mouse Pointer
//	}
//
//	if (hRC)											// Do We Have A Rendering Context?
//	{
//		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
//		{
//			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
//		}
//
//		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
//		{
//			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
//		}
//		hRC=NULL;										// Set RC To NULL
//	}
//
//	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
//	{
//		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
//		hDC=NULL;										// Set DC To NULL
//	}
//
//	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
//	{
//		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
//		hWnd=NULL;										// Set hWnd To NULL
//	}
//
//	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
//	{
//		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
//		hInstance=NULL;									// Set hInstance To NULL
//	}
//}
//
///*	This Code Creates Our OpenGL Window.  Parameters Are:					*
// *	title			- Title To Appear At The Top Of The Window				*
// *	width			- Width Of The GL Window Or Fullscreen Mode				*
// *	height			- Height Of The GL Window Or Fullscreen Mode			*
// *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
// *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
// 
//BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
//{
//	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
//	WNDCLASS	wc;						// Windows Class Structure
//	DWORD		dwExStyle;				// Window Extended Style
//	DWORD		dwStyle;				// Window Style
//	
//	WindowRect.left=(long)0;			// Set Left Value To 0
//	WindowRect.right=(long)width;		// Set Right Value To Requested Width
//	WindowRect.top=(long)0;				// Set Top Value To 0
//	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height
//
//	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag
//
//	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
//	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
//	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
//	wc.cbClsExtra		= 0;									// No Extra Window Data
//	wc.cbWndExtra		= 0;									// No Extra Window Data
//	wc.hInstance		= hInstance;							// Set The Instance
//	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
//	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
//	wc.hbrBackground	= NULL;									// No Background Required For GL
//	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
//	wc.lpszClassName	= "OpenGL";								// Set The Class Name
//
//	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
//	{
//		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;											// Return FALSE
//	}
//	
//	if (fullscreen)												// Attempt Fullscreen Mode?
//	{
//		DEVMODE dmScreenSettings;								// Device Mode
//		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
//		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
//		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
//		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
//		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
//		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
//
//		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
//		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
//		{
//			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
//			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
//			{
//				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
//			}
//			else
//			{
//				// Pop Up A Message Box Letting User Know The Program Is Closing.
//				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
//				return FALSE;									// Return FALSE
//			}
//		}
//	}
//
//	if (fullscreen)												// Are We Still In Fullscreen Mode?
//	{
//		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
//		dwStyle=WS_POPUP;										// Windows Style
//		ShowCursor(FALSE);										// Hide Mouse Pointer
//	}
//	else
//	{
//		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
//		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
//	}
//
//	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size
//
//	// Create The Window
//	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
//								"OpenGL",							// Class Name
//								title,								// Window Title
//								dwStyle |							// Defined Window Style
//								WS_CLIPSIBLINGS |					// Required Window Style
//								WS_CLIPCHILDREN,					// Required Window Style
//								0, 0,								// Window Position
//								WindowRect.right-WindowRect.left,	// Calculate Window Width
//								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
//								NULL,								// No Parent Window
//								NULL,								// No Menu
//								hInstance,							// Instance
//								NULL)))								// Dont Pass Anything To WM_CREATE
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
//	{
//		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
//		1,											// Version Number
//		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
//		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
//		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
//		PFD_TYPE_RGBA,								// Request An RGBA Format
//		bits,										// Select Our Color Depth
//		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
//		0,											// No Alpha Buffer
//		0,											// Shift Bit Ignored
//		0,											// No Accumulation Buffer
//		0, 0, 0, 0,									// Accumulation Bits Ignored
//		16,											// 16Bit Z-Buffer (Depth Buffer)  
//		0,											// No Stencil Buffer
//		0,											// No Auxiliary Buffer
//		PFD_MAIN_PLANE,								// Main Drawing Layer
//		0,											// Reserved
//		0, 0, 0										// Layer Masks Ignored
//	};
//	
//	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	ShowWindow(hWnd,SW_SHOW);						// Show The Window
//	SetForegroundWindow(hWnd);						// Slightly Higher Priority
//	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
//	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen
//
//	if (!InitGL())									// Initialize Our Newly Created GL Window
//	{
//		KillGLWindow();								// Reset The Display
//		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
//		return FALSE;								// Return FALSE
//	}
//
//	return TRUE;									// Success
//}
//
//LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
//							UINT	uMsg,			// Message For This Window
//							WPARAM	wParam,			// Additional Message Information
//							LPARAM	lParam)			// Additional Message Information
//{
//	switch (uMsg)									// Check For Windows Messages
//	{
//		case WM_ACTIVATE:							// Watch For Window Activate Message
//		{
//			if (!HIWORD(wParam))					// Check Minimization State
//			{
//				active=TRUE;						// Program Is Active
//			}
//			else
//			{
//				active=FALSE;						// Program Is No Longer Active
//			}
//
//			return 0;								// Return To The Message Loop
//		}
//
//		case WM_SYSCOMMAND:							// Intercept System Commands
//		{
//			switch (wParam)							// Check System Calls
//			{
//				case SC_SCREENSAVE:					// Screensaver Trying To Start?
//				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
//				return 0;							// Prevent From Happening
//			}
//			break;									// Exit
//		}
//
//		case WM_CLOSE:								// Did We Receive A Close Message?
//		{
//			PostQuitMessage(0);						// Send A Quit Message
//			return 0;								// Jump Back
//		}
//		case WM_MOUSEWHEEL:
//		{
//			if(wParam == 7864320) {
//				keys[256] = TRUE;
//				cout<<"FORWARD SCROLL"<<endl;
//			}
//			else if(wParam == 4287102976) {
//				keys[257] = TRUE;
//				cout<<"BACK SCROLL"<<endl;
//			}
//			//keys[wParam] = TRUE;
//			return 0;
//		}
//		case WM_KEYDOWN:							// Is A Key Being Held Down?
//		{
//			keys[wParam] = TRUE;					// If So, Mark It As TRUE
//			return 0;								// Jump Back
//		}
//
//		case WM_KEYUP:								// Has A Key Been Released?
//		{
//			keys[wParam] = FALSE;					// If So, Mark It As FALSE
//			return 0;								// Jump Back
//		}
//
//		case WM_SIZE:								// Resize The OpenGL Window
//		{
//			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
//			return 0;								// Jump Back
//		}
//		case WM_MOUSEMOVE:
//		{
//			keys[wParam] = TRUE;
//			return 0;
//		}
//	}
//
//	// Pass All Unhandled Messages To DefWindowProc
//	return DefWindowProc(hWnd,uMsg,wParam,lParam);
//}
//
//int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
//					HINSTANCE	hPrevInstance,		// Previous Instance
//					LPSTR		lpCmdLine,			// Command Line Parameters
//					int			nCmdShow)			// Window Show State
//{
//	MSG		msg;									// Windows Message Structure
//	BOOL	done=FALSE;								// Bool Variable To Exit Loop
//
//	// Ask The User Which Screen Mode They Prefer
//	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
//	{
//		fullscreen=FALSE;							// Windowed Mode
//	}
//
//	// Create Our OpenGL Window
//	if (!CreateGLWindow("NeHe's Textures, Lighting & Keyboard Tutorial",640,480,16,fullscreen))
//	{
//		return 0;									// Quit If Window Was Not Created
//	}
//
//	while(!done)									// Loop That Runs While done=FALSE
//	{
//		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
//		{
//			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
//			{
//				done=TRUE;							// If So done=TRUE
//			}
//			else									// If Not, Deal With Window Messages
//			{
//				TranslateMessage(&msg);				// Translate The Message
//				DispatchMessage(&msg);				// Dispatch The Message
//			}
//		}
//		else										// If There Are No Messages
//		{
//			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
//			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
//			{
//				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
//			}
//			else									// Not Time To Quit, Update Screen
//			{
//				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
//				if (keys['L'] && !lp)
//				{
//					lp=TRUE;
//					light=!light;
//					if (!light)
//					{
//						glDisable(GL_LIGHTING);
//					}
//					else
//					{
//						glEnable(GL_LIGHTING);
//					}
//				}
//				if (!keys['L'])
//				{
//					lp=FALSE;
//				}
//				if (keys['F'] && !fp)
//				{
//					fp=TRUE;
//					filter+=1;
//					if (filter>2)
//					{
//						filter=0;
//					}
//				}
//				if (!keys['F'])
//				{
//					fp=FALSE;
//				}
//				if (keys[VK_PRIOR])
//				{
//					z-=0.02f;
//				}
//				if (keys[VK_NEXT])
//				{
//					z+=0.02f;
//				}
//				if (keys[VK_UP])
//				{
//					xspeed-=0.01f;
//				}
//				if (keys[VK_DOWN])
//				{
//					xspeed+=0.01f;
//				}
//				if (keys[VK_RIGHT])
//				{
//					yspeed+=0.01f;
//				}
//				if (keys[VK_LEFT])
//				{
//					yspeed-=0.01f;
//				}
//				if(keys[256]) {
//					if(mouseWheel < 2000) {
//						mouseWheel += 100;
//					}
//					cout<<"WHEELUP "<<mouseWheel<<endl;
//					zoomIn();
//					keys[256] = FALSE;
//				}
//				if(keys[257]) {
//					if(mouseWheel > -2000) {
//						mouseWheel -= 100;
//						
//					}
//					zoomOut();
//					cout<<"WHEELDOWN "<<mouseWheel<<endl;
//					keys[257] = FALSE;
//					
//				}
//				if (keys[VK_F1])						// Is F1 Being Pressed?
//				{
//					keys[VK_F1]=FALSE;					// If So Make Key FALSE
//					KillGLWindow();						// Kill Our Current Window
//					fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
//					// Recreate Our OpenGL Window
//					if (!CreateGLWindow("NeHe's Textures, Lighting & Keyboard Tutorial",640,480,16,fullscreen))
//					{
//						return 0;						// Quit If Window Was Not Created
//					}
//				}
//				if (keys[0]) {
//
//				}
//			}
//		}
//	}
//	fclose (stdout);
//	// Shutdown
//	KillGLWindow();									// Kill The Window
//	return (msg.wParam);							// Exit The Program
//}
//
