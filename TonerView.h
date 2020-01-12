/*
	
	TonerView.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#ifndef TONER_VIEW_H
#define TONER_VIEW_H

#include <View.h>

class TonePlayer;
class BMessage;
class BMenuField;

class TonerView : public BView
{
public:
					TonerView(BRect frame); 
					~TonerView(); 
	BMenuField		*mnuLevel;
	BMenuField		*mnuFreq;
private:	
	void			AttachedToWindow();
	void			MessageReceived (BMessage *inMessage);
	TonePlayer		*Player;
};

#endif
