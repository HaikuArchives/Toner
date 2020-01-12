/*

	TonerApp.h

*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include <Application.h>

class TonerWindow;

class TonerApp : public BApplication
{
public:
					TonerApp(void);
private:
	void        	AboutRequested(void);
};
