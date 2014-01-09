/*

	TonerWindow.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include "TonerWindow.h"
#include "TonerView.h"

#include <Application.h>

TonerWindow::TonerWindow() : BWindow(BRect(100, 100, 220, 170), "Toner v1.0", B_TITLED_WINDOW, B_NOT_RESIZABLE | B_WILL_ACCEPT_FIRST_CLICK)
{
	TonerView *theView = new TonerView( Bounds() );
	AddChild(theView);
}

bool
TonerWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}
