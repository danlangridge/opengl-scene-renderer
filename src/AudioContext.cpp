#include <AudioContext.h>

#include <AL/alut.h>


bool AudioContext::initOpenAL() {
  ALuint helloBuffer, helloSource;
  alutInit(NULL,NULL);
  helloBuffer = alutCreateBufferHelloWorld();
  alGenSources(1, &helloSource);
  alSourcei(helloSource, AL_BUFFER, helloBuffer);
  alSourcePlay(helloSource);
  alutSleep(1);
  alutExit();
  return 0;
}
