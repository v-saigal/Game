/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

#ifndef LTIMER_H
#define LTIMER_H

#include <SDL3/SDL.h>

class LTimer
{
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint64 getTicksNS();
    float getDeltaSeconds();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    Uint64 mStartTicks;
    Uint64 mLastTicks;
    //The ticks stored when the timer was paused
    Uint64 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};

#endif
