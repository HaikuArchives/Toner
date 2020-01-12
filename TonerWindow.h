/*
	
	TonerWindow.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include <Window.h>

#ifndef TONER_WINDOW_H
#define TONER_WINDOW_H

class TonePlayer;
class BMenuField;

class TonerWindow : public BWindow  
{
public:
					TonerWindow();
					~TonerWindow();
private:
	bool			QuitRequested(void);
	TonePlayer		*Player;
	void			MessageReceived(BMessage *inMessage);
	void			CreateMenus();
	BMenuField		*mnuLevel;
	BMenuField		*mnuFreq;
};

#endif
