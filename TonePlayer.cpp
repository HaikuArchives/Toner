/*
	
	TonePlayer.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#include "TonePlayer.h" 
#include <Alert.h>
#include "math.h"
#include "stdlib.h"

#define SAMPLE_RATE 44100
#define INITIAL_FREQ 400
#define GAIN_CORRECTION 0.13			//the pink noise filter has a lot of gain....use this to cut back
#define RAMP_TIME 11025.0				//ramp volume over several milliseconds so there's no pop or click

	void		BufferProc(void *theCookie, void *buffer, size_t size, const media_raw_audio_format &format); //adds data to buffer 
	double		NextSample();
	
	float		TargetLevel = 0;
	float		TargetToneLevel, ToneLevel, ToneIncrement;
	float		TargetNoiseLevel, NoiseLevel, NoiseIncrement;
	uint		ChannelCount, NumSamples;
	double		p, q0, q1, q2;						//vars for the phasor
	double		white, b0, b1, b2, b3, b4, b5, b6 = 0;	//vars for the pink noise generator
	bool		Noise;								//true if we are playing noise instead of tone

double
NextSample()
{
   q2 = p * q1 - q0;
   q0 = q1;
   q1 = q2;
   return q2;
}

void BufferProc(void *theCookie, void *buffer, size_t size, const media_raw_audio_format &format) 
{ 
	//we're not smart enough to handle different sample rates / formats
	if (format.format != media_raw_audio_format::B_AUDIO_FLOAT) return; 
	if (format.frame_rate != SAMPLE_RATE) return;
	
	//convert the buffer data into handy values
	float *buf = (float *) buffer; 
	ChannelCount = format.channel_count; 
	NumSamples = size / 4; 
  
	//calculate volume envelopes so we don't get pops or clicks
	ToneIncrement = (TargetToneLevel - ToneLevel) / RAMP_TIME;
	NoiseIncrement = (TargetNoiseLevel - NoiseLevel) / RAMP_TIME;

	//iterate through buffer & fill with audio data
	for (size_t i = 0; i < NumSamples; i += ChannelCount) 
	{ 
		//Apply tone
		buf[i] = ToneLevel * NextSample();

		//Apply pink noise
		white = (double) rand() / (double) RAND_MAX;
		b0 = 0.99886 * b0 + white * 0.0555179;
		b1 = 0.99332 * b1 + white * 0.0750759;
		b2 = 0.96900 * b2 + white * 0.1538520;
		b3 = 0.86650 * b3 + white * 0.3104856;
		b4 = 0.55000 * b4 + white * 0.5329522;
		b5 = -0.7616 * b5 - white * 0.0168980;
		buf[i] += GAIN_CORRECTION * NoiseLevel * (b0 + b1 + b2 + b3 + b4 + b5 + b6 + white * 0.5362);
		b6 = white * 0.115926;		
				
		//Fill other channel(s)
		for (uint j = 1; j < ChannelCount; j++)
			buf[i + j] = buf[i];

		//Increment level controls
		ToneLevel += ToneIncrement;
		NoiseLevel += NoiseIncrement;
 	}
 }

TonePlayer::TonePlayer(void) : BSoundPlayer  ("Toner", &BufferProc, NULL, NULL)
{
	//calculate initial values for phasor
	double w = 2 * PI * INITIAL_FREQ / SAMPLE_RATE;
	p = 2.0 * cos(w);
	q0 = sin(-2 * w);
	q1 = sin(-w);

	TargetToneLevel = ToneLevel = ToneIncrement = 0;
	TargetNoiseLevel = NoiseLevel = NoiseIncrement = 0;

	//start the BSoundPlayer
	SetHasData(true);
	Start();
}

void
TonePlayer::SetNoiseMix() 
{
	if (Noise)
	{
		TargetNoiseLevel = TargetLevel;
		TargetToneLevel = 0;
	}
	else
	{
		TargetNoiseLevel = 0;
		TargetToneLevel = TargetLevel;
	}
} 
 
void
TonePlayer::SetNoise(bool inNoise) 
{
	Noise = inNoise;

	SetNoiseMix();
} 
 
void
TonePlayer::SetLevel(int16 inLevel_dB) 
{
	//convert dB's into a scaling factor, 0-1
	TargetLevel = pow(10.0, inLevel_dB / 20.0);
	
	SetNoiseMix();
} 
 
void
TonePlayer::SetFrequency(int16 inFreq)
{
	//calculate phase change per sample, in radians
	double w = 2 * PI * inFreq / SAMPLE_RATE;

	//change phase constant
	p = 2.0 * cos(w);

	//recalculate q0 as if it were at this new frequency
	q0 = sin(-2 * w + ( asin(q1) + w) );
}