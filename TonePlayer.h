/*
	
	TonePlayer.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include <SoundPlayer.h> 

#ifndef TONE_PLAYER_H
#define TONE_PLAYER_H

#define TONE_PINK 0
#define LEVEL_MUTE -120

class TonePlayer : public BSoundPlayer
{
public:
					TonePlayer(void); 
	void			SetNoise(bool inNoise);
	void			SetFrequency(int16 inFreq);
	void			SetLevel(int16 inLevel_dB);
private:
	void			SetNoiseMix();
};

#endif