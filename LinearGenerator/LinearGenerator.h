#ifndef LINEAR_GENERATOR_H
#define LINEAR_GENERATOR_H

#include <Arduino.h>
namespace SigUtil
{
template <typename T>
class LinearGenerator
{
  private:
    bool isRunning = false;
    bool isPaused = false;
    bool goingDown = false;

    double a, b;
    unsigned long startTimestamp;
    unsigned long endTime;
    T currentVal = 0;
    T endVal;

  public:
    void start(T startval, T endval, unsigned long timeval);
    void stop();
    void pause();
    void resume();
    bool running();
    bool paused();
    T read();
};

template <typename T>
void LinearGenerator<T>::start(T startVal, T _endVal, unsigned long _endTime)
{
    if (_endTime == 0)
    {
        currentVal = _endVal;
        return;
    }
    endVal = _endVal;
    endTime = _endTime;
    currentVal = startVal;

    a = (double)(endVal - startVal) / endTime;
    b = (double)startVal;

    if (a < 0)
        goingDown = true;
    else
        goingDown = false;

    startTimestamp = millis();

    isRunning = true;
    isPaused = false;
}

template <typename T>
void LinearGenerator<T>::stop()
{
    isPaused = false;
    isRunning = false;
}

template <typename T>
void LinearGenerator<T>::pause()
{
    if (!isRunning) //you can't pause a generator that is not running
        return;

    //save remaining time
    //so if generator was set to 1000ms and paused at 800
    //it will take remaining 200ms to finish regulation after resume
    unsigned long currentTime = (unsigned long)(millis() - startTimestamp);
    endTime = (unsigned long)(endTime - currentTime);

    isPaused = true;
}

template <typename T>
void LinearGenerator<T>::resume()
{
    if (!isRunning) //you can't resume a generator that is not running
        return;

    //resume timer from current position
    //with remaining time computed in pause() function
    //start() clears isPaused flag
    start(currentVal, endVal, endTime);
}

template <typename T>
T LinearGenerator<T>::read()
{
    if (!isRunning || isPaused)
        return currentVal;

    unsigned long currentTime = (unsigned long)(millis() - startTimestamp); //get current time
    currentVal = a * currentTime + b;                                       //compute linear function

    if (goingDown && currentVal < endVal || !goingDown && currentVal > endVal) //saturate output
        currentVal = endVal;

    if (currentTime >= endTime) //finished timewise so set result to end value and stop the generator
    {
        currentVal = endVal;
        isRunning = false;
    }

    return currentVal;
}

template <typename T>
bool LinearGenerator<T>::running()
{
    return isRunning;
}

template <typename T>
bool LinearGenerator<T>::paused()
{
    return isPaused;
}
}; // namespace SigUtil
#endif