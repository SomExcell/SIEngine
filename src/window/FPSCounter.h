#ifndef WINDOW_FPSCOUNTER_H_
#define WINDOW_FPSCOUNTER_H_

class FPSCounter
{
public:
    static void displayFPS();
private:
    static double prevTime;
    static double crntTime;
    static double timeDiff;
    static unsigned int counter;
};

#endif