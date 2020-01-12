/*

	TonerApp.cpp

*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include "TonerApp.h"
#include "TonerWindow.h"
#include <Alert.h>

int main(int, char**)
{
	TonerApp myApplication;
	myApplication.Run();
	return(0);
}

TonerApp::TonerApp() : BApplication("application/x-vnd.Be-BTL.Toner")
{
	TonerWindow *theWindow = new TonerWindow();
	theWindow->Show();
}

void TonerApp::AboutRequested(void)
{
	(new BAlert("", "Toner by Ben Loftis", "Cool"))->Go();
}

