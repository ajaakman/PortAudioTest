#include <iostream>
#include "portaudio.h"

double time = 0.0;

static int AudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, 
	const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
	for (unsigned i = 0; i < framesPerBuffer; i++)
	{
		reinterpret_cast<float*>(outputBuffer)[i] = (float)sin(440.0 * 2.0 * 3.14 * time);
		time += 1.0f/ 44100.0f;
	}

	return 0;
}

int main()
{
	PaError err = Pa_Initialize();
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	PaStream* stream;

	err = Pa_OpenDefaultStream(	&stream, 0,	1, paFloat32, 44100, 256, AudioCallback, nullptr);

	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	err = Pa_StartStream(stream);
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	Pa_Sleep(1 * 1000);

	std::cin.get();
	
	err = Pa_StopStream(stream);
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	err = Pa_CloseStream(stream);
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err)); 

	err = Pa_Terminate();
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
}