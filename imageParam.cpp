#include "imageParam.h"

using namespace std;

imageParam::imageParam() // step 1, pt 2
{
    numElement = 128;                                                            // sets numElement to 128
    numSample = 3338;                                                            // sets numSample to 3338
    numScanline = 127;                                                           // sets numScanline to 127
    elementPosition = genElementPosition();                                      // Calls genElementPosition and assign the returned 1D array to elementPosition
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // Call genScanlinePosition and assign the returned 2D array to scanlinePosition
}

imageParam::~imageParam()
{
    deletePositionArray(); // Step 2 of part 2
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    float *elementLocation = new float[numElement]; // initiation of eleLocation
    float N = numElement;                           // float type to avoid truncation within the calculation
    for (int n = 0; n < numElement; n++)            // for loop to acesss the each index of eleLocation
    {
        elementLocation[n] = ((n - ((N - 1) / 2)) * PITCH); // inputing the values into eleLocation
    }
    return elementLocation;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    cout << "enter desired imaging depth" << endl; // asks user for desired imaging depth
    float desiredDepth;
    cin >> desiredDepth;
    cout << "enter desired number of pickels per scanline" << endl; // asks user for desired number of pixels per scanline
    cin >> numPixel;
    float2 **scanlinePosition = new float2 *[numScanline]; // making the first dimension of the array scanlinePosition
    for (int i = 0; i < numScanline; i++)
    {
        scanlinePosition[i] = new float2[numPixel]; // fills the second dimention of the array scanlinePosition
    }// I TYPECASTED NUMPIXEL TO INT.... IS THIS SUPPSED TO BE HERE?! IM SO CONFUSED WHY IT DOESNT ACCEPT FLOAT TYPE?!
    // float scanlinevalue = 0; // initiates scanlinevalue and sets it to 0
    // scanlinePosition [0] = scanlinevalue; // IS THIS NEEDED?!
    int M = numScanline;
    float increase = desiredDepth / (float(numPixel) -1); // how much each iteration should increase by
for (int m = 0; m < numScanline; m++){
    float startdepth = 0; //initiates variable for the start depth 
    scanlinePosition[m][0].y=startdepth; // start the scanline position to be zero
    
    for (int n = 1; n < numPixel; n++){
            scanlinePosition[m][n-1].x = (m - (float(M) - 1) / 2) * PITCH;
            scanlinePosition[m][n].y = increase + scanlinePosition[m][n-1].y; // WTF R U SUPPOSED TO DO HERE?!
    }
   
    }
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline()
{
    return numScanline;
}

int imageParam::getNumPixel()
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    for (int i = 0; i < numScanline; i++)
    {
        delete scanlinePosition[i];
    }
    delete scanlinePosition;

    delete elementPosition;
}
