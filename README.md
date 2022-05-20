# EVBOX_Embedded_C_Coding-_Test

In a microcontroller-based system, analogue to digital converter (ADC) is sensing analogue voltage coming on one of the analogue channels. This analogue voltage needs to be converted into a discrete level (0-4) depending upon the value of input voltage in such a way that some hysteresis is added to reject sudden voltage variations due to noise. Following graph shows the relationship between analogue voltage read (%age) from the channel to the discrete level that need to be encoded by the software. Write code that will perform this job. Use this prototype so the code can be tested: unsigned int hysteresis(unsigned int input_percent)
Hint: If analogue voltage increases from 9% to 15% encoded step shall be 1 and if it decreases back to 11% from 15%, the encoded level shall remain 1 unless voltage drops to 10%.

https://lh4.googleusercontent.com/sGqTw4c2ipxxyMtgU8h2dCWfMOV1PrV4tzF9c-sYltShFnjRhsG--fEO98O_RKQOam2XqhcTUIBmLdK0yIsRpYMm3YhcuhLP9qHCRiQp5PaAUvJFn5aRyIgTGz3B6LMC=w550
