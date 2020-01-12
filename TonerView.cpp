/*
	
	TonerView.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include "TonerView.h"

#include "TonePlayer.h"

#include <Alert.h>
#include <Menu.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <Bitmap.h>
#include <TranslationUtils.h>
 
enum 
{
	Cmd_Level	= 'cm00',
	Cmd_Freq,
};

TonerView::TonerView(BRect rect) : BView(rect, "TonerView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW) 
{ 
	Player = new TonePlayer();
	Player->SetNoise(false);
	Player->SetFrequency(400);
	Player->SetLevel(LEVEL_MUTE);
}

void
TonerView::AttachedToWindow() 
{ //We have to change things here only.....
//	//Load & display the background bitmap
//	BBitmap *theBitmap = BTranslationUtils::GetBitmap('BMP ', 1);
//	if (theBitmap != NULL)
//		SetViewBitmap(theBitmap);
// We'll have to remove the bitmap, as the words are hard-printed onto the bitmap,
// which is not what we want.
	
	//add level & tone menus
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
	
//	BMenuField *mnuLevel = new BMenuField(BRect (46, 10, 140, 60), "", "", menu);
//	mnuLevel->SetDivider(0);

 	BMenuField *mnuLevel = new BMenuField("Level:", menu);
	
//	AddChild(mnuLevel);
	
	
	/*    ----------------    The Tone Menu    --------------           */

	menu = new BPopUpMenu("400 Hz");
	
	int Tone_Count = 14;
	const char *ToneText[] = {"20 Hz", "30 Hz", "40 Hz", "60 Hz", "80 Hz", "120 Hz", "240 Hz", "480 Hz", "1 kHz", "2 kHz", "4 kHz", "8 kHz", "16 kHz", "Pink"};
	int Tone[] = {20, 30, 40, 60, 80, 120, 240, 480, 1000, 2000, 4000, 8000, 16000, TONE_PINK};
	
	for (int i = 0; i < Tone_Count; i++)
	{
		theMessage = new BMessage(Cmd_Freq);
		theMessage->AddInt16("freq", Tone[i]);
		theItem = new BMenuItem(ToneText[i], theMessage);
		theItem->SetTarget(this);
		menu->AddItem(theItem);
	}
	
//	BMenuField *mnuFreq = new BMenuField(BRect (46, 40, 160, 100), "", "", menu);
//	mnuFreq->SetDivider(0);

 	BMenuField *mnuFreq = new BMenuField("Tone:", menu);

//	AddChild(mnuFreq);

//	Attempting to build the layout
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.AddGrid(B_USE_DEFAULT_SPACING, B_USE_SMALL_SPACING)
			.AddMenuField(mnuLevel, 0, 0, B_ALIGN_LEFT)
			.AddMenuField(mnuFreq, 0, 0, B_ALIGN_LEFT)
		.AddGlue()
		.SetInsets(B_USE_WINDOW_SPACING, B_USE_DEFAULT_SPACING,
					B_USE_WINDOW_SPACING, B_USE_DEFAULT_SPACING)
		.End();
}

TonerView::~TonerView()
{
	delete Player;
}


void
TonerView::MessageReceived(BMessage *inMessage)
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
			BView::MessageReceived(inMessage);
		break;
	}
}
