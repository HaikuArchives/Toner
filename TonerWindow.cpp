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
#include <LayoutBuilder.h>
//Old values are 220 and 170
TonerWindow::TonerWindow() : BWindow(BRect(100, 100, 250, 180), "Toner v1.0", B_TITLED_WINDOW, B_NOT_RESIZABLE | B_WILL_ACCEPT_FIRST_CLICK |  B_AUTO_UPDATE_SIZE_LIMITS)
{
	TonerView *theView = new TonerView(BRect(0,0,0,0));
	AddChild(theView);
	
	//The view is no longer needed, just a place to hold things.
	theView->Hide();
	
	//Building the main layout.
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.AddGrid(B_USE_DEFAULT_SPACING, B_USE_SMALL_SPACING)
			.AddMenuField(theView -> mnuLevel, 0, 0, B_ALIGN_LEFT)
			.AddMenuField(theView -> mnuFreq, 0, 1, B_ALIGN_LEFT)
			.End()
		.AddGlue()
		.SetInsets(B_USE_WINDOW_SPACING, B_USE_DEFAULT_SPACING,
					B_USE_WINDOW_SPACING, B_USE_DEFAULT_SPACING)
		.End();
}

bool
TonerWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}
