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
#include <LayoutBuilder.h>

TonerView::TonerView(BRect rect) : BView(rect, "TonerView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW) 
{ 

}

void
TonerView::AttachedToWindow() 
{

}

TonerView::~TonerView()
{

}
