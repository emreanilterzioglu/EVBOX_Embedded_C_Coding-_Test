/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define DISCRETE_LEVEL_0 0
#define DISCRETE_LEVEL_1 1
#define DISCRETE_LEVEL_2 2
#define DISCRETE_LEVEL_3 3
#define DISCRETE_LEVEL_4 4

#define ANALOG_THRESHOLD_1 12.5
#define ANALOG_THRESHOLD_2 37.5
#define ANALOG_THRESHOLD_3 62.5
#define ANALOG_THRESHOLD_4 87.5

#define ANALOG_ERROR_MARGIN 2.5

int main()
{
    volatile int analogVoltage = 0;
    int discreteLevel = 0;

    while (TRUE)
    {
        analogVoltage = readFromMemAddress(0x00000000); // Read Analog Level
        discreteLevel = AnalogToDigitalLevelConv(&analogVoltage, &discreteLevel);
        
        printf("Discrete Level: %d\n",discreteLevel);

        timerDelayUs(100);

    }
    return 0;
}

int AnalogToDigitalLevelConv(const float const *analogVoltage, const int const *oldDiscreteLevel)
{
    int returnVal = DISCRETE_LEVEL_0;
    int tempDiscValue = DISCRETE_LEVEL_0;

    // Basic Test
    if (analogVoltage >= (ANALOG_THRESHOLD_1 + ANALOG_ERROR_MARGIN))
    {
        tempDiscValue = DISCRETE_LEVEL_1; 
    }
    if (analogVoltage >= (ANALOG_THRESHOLD_2 + ANALOG_ERROR_MARGIN))
    {
        tempDiscValue = DISCRETE_LEVEL_2; 
    }
    if (analogVoltage >= (ANALOG_THRESHOLD_3 + ANALOG_ERROR_MARGIN))
    {
        tempDiscValue = DISCRETE_LEVEL_3; 
    }
    if (analogVoltage >= (ANALOG_THRESHOLD_4 + ANALOG_ERROR_MARGIN))
    {
        tempDiscValue = DISCRETE_LEVEL_4; 
    }

    if(abs(tempDiscValue-(*oldDiscreteLevel)) > 1)  // Major Spike Operation (Discrete Level Jump detected)
    {
        returnVal = tempDiscValue;
    }
    else                                            // Normal and Minor Spike Operation
    {
        switch (*oldDiscreteLevel)
        {
            case DISCRETE_LEVEL_0:
                if (analogVoltage >= (ANALOG_THRESHOLD_1 + ANALOG_ERROR_MARGIN))
                {
                    tempDiscValue = DISCRETE_LEVEL_1; 
                }
                else
                {
                    returnVal = DISCRETE_LEVEL_0;
                }
            break;
            case DISCRETE_LEVEL_1
                if (analogVoltage >= (ANALOG_THRESHOLD_2 + ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_2; 
                }
                else if(analogVoltage <= (ANALOG_THRESHOLD_1 - ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_0; 
                }
                else
                {
                    returnVal = DISCRETE_LEVEL_1;
                }
            break;
            case DISCRETE_LEVEL_2:
                if (analogVoltage >= (ANALOG_THRESHOLD_3 + ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_3; 
                }
                else if(analogVoltage <= (ANALOG_THRESHOLD_2 - ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_1; 
                }
                else
                {
                    returnVal = DISCRETE_LEVEL_2;
                }
            break;
            case DISCRETE_LEVEL_3:
                if (analogVoltage >= (ANALOG_THRESHOLD_4 + ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_4; 
                }
                else if(analogVoltage <= (ANALOG_THRESHOLD_3 - ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_2; 
                }
                else
                {
                    returnVal = DISCRETE_LEVEL_3;
                }
            break;
            case DISCRETE_LEVEL_4:
                if(analogVoltage <= (ANALOG_THRESHOLD_4 - ANALOG_ERROR_MARGIN))
                {
                    returnVal = DISCRETE_LEVEL_3; 
                }
                else
                {
                    returnVal = DISCRETE_LEVEL_4;
                }
            break;
            default:
                returnVal = DISCRETE_LEVEL_0; // Something Wrong Power-off output.
            break;
        }
    }

    return returnVal;

}

void timerDelayUs(int delayTimeInUs)
{
    //Wait delayTimeInUs microseconds using timer.
}

int readFromMemAddress(int memAddress)
{
    volatile int data = 0;
    // Read data from mapped memory(Imagining there is FPGA inside the system to control discreteIO controls). For example sensor data.  
    return data;
}

