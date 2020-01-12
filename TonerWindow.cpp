/*

	TonerWindow.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include "TonerWindow.h"
#include "TonePlayer.h"

#include <Alert.h>
#include <Application.h>
#include <LayoutBuilder.h>
#include <Menu.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>

enum 
{
	Cmd_Level	= 'cm00',
	Cmd_Freq,
};

TonerWindow::TonerWindow() : BWindow(BRect(100, 100, 250, 180), "Toner",
	B_TITLED_WINDOW, B_NOT_RESIZABLE | B_WILL_ACCEPT_FIRST_CLICK |  B_AUTO_UPDATE_SIZE_LIMITS)
{
	Player = new TonePlayer();
	Player->SetNoise(false);
	Player->SetFrequency(400);
	Player->SetLevel(LEVEL_MUTE);
	
	CreateMenus();
	
	//Building the main layout.
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.AddGrid(B_USE_DEFAULT_SPACING, B_USE_SMALL_SPACING)
			.AddMenuField(mnuLevel, 0, 0, B_ALIGN_LEFT)
			.AddMenuField(mnuFreq, 0, 1, B_ALIGN_LEFT)
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

void
TonerWindow::MessageReceived(BMessage *inMessage)
{
	switch ( inMessage->what )
	{
		case Cmd_Level:
		{
			int16 theLevel;
			if ( inMessage->FindInt16("level", &theLevel) == 0 )
				Player->SetLevel(theLevel);
		}
		break;
		
		case Cmd_Freq:
		{
			int16 theFreq;
			if ( inMessage->FindInt16("freq", &theFreq) == 0 )
			{
				if (theFreq < 10)
					Player->SetNoise(true);
				else
				{
					Player->SetNoise(false);
					Player->SetFrequency(theFreq);
				}
			}
		}
		break;
		
		default:
			BWindow::MessageReceived(inMessage);
		break;
	}
}

TonerWindow::~TonerWindow()
{
	delete Player;
}

void
TonerWindow::CreateMenus()
{
	//Add level & tone menus
	BMenu *menu;
	BMenuItem *theItem;
	BMessage *theMessage;
	
	/*    ----------------    The Level Menu    --------------           */
	
	menu = new BPopUpMenu("Mute");
	
	int Level_Count = 5;
	const char *LevelText[] = {"Unity", "-3 dB", "-10 dB", "-20 dB", "Mute"};
	int Level[] = {0, -3, -10, -20, LEVEL_MUTE};
	
	for (int i = 0; i < Level_Count; i++)
	{
		theMessage = new BMessage(Cmd_Level);
		theMessage->AddInt16("level", Level[i]);
		theItem = new BMenuItem(LevelText[i], theMessage);
		theItem->SetTarget(this);
		menu->AddItem(theItem);
	}
	
 	mnuLevel = new BMenuField("Level:", menu);
	
	/*    ----------------    The Tone Menu    --------------           */

	menu = new BPopUpMenu("400 Hz");
	
	int Tone_Count = 14;
	const char *ToneText[] = 
	{"20 Hz", "30 Hz", "40 Hz", "60 Hz", "80 Hz", "120 Hz", "240 Hz", 
	"480 Hz", "1 kHz", "2 kHz", "4 kHz", "8 kHz", "16 kHz", "Pink"};
	int Tone[] = {20, 30, 40, 60, 80, 120, 240, 480, 1000, 2000, 4000, 8000, 16000, TONE_PINK};
	
	for (int i = 0; i < Tone_Count; i++)
	{
		theMessage = new BMessage(Cmd_Freq);
		theMessage->AddInt16("freq", Tone[i]);
		theItem = new BMenuItem(ToneText[i], theMessage);
		theItem->SetTarget(this);
		menu->AddItem(theItem);
	}
	
 	mnuFreq = new BMenuField("Tone:", menu);
}
