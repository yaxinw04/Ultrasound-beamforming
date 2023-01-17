#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
imparams = NULL; // set imparams to NULL
RFData = NULL; // set RFData to NULL
next = NULL; //sets next to NULL
line = 0; //sets line to 0
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
imparams = params;
RFData = data;
line = numline; //numline is the number of scanlines
scanline = createScanline(imparams -> getNumPixel()); 
beamform();
}

BmodeClass::~BmodeClass()
{
deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
float * mem = new float[numPixel]; // dynamically allocating a 1D array of size numPixel as mem
return mem; //returning mem
}

void BmodeClass::beamform() // WHY IS THERE NOTHING ENTERED HERE????? TF??
{
    float tfa = 0;    // initializing tfa (t forwsrds array)
    float tba = 0; // initializing tba (t back array)
    float tta = 0; // initializing tta (t total array)
    int s ;  // initiating s array as integer because of floor function


    for (int i = 0; i < imparams->getNumPixel(); i++) // outer loop to iterate though the first dimension of the array 
    {
        float prSum = 0, piSum = 0; //initializing the Preal and pimag sums to be zero
        tfa= (imparams-> getYPosition(line, i)/imparams->SOS); //calculating tfa
        
        for (int k = 0; k < imparams->getNumElement(); k++) //another loop to iterate through the second dimension of array
        {
            tba = (sqrt ((pow(imparams -> getYPosition(line, i),2))+ pow((imparams->getXPosition(line, i) - imparams ->getElementPosition(k)),2))/imparams->SOS);// equation for calculating tba
            tta= tfa+ tba;       // equation for calculating tta
            s= floor(tta*(imparams->FS));    // equation for calculating s 

            if (s< imparams->getNumSample()){ // prevents memory leak
            prSum += RFData->getRealRFData(k,s); // equation for calculating prSum 
            piSum += RFData->getImagRFData(k,s); // equation for calculating piSum   
            }                                                                      // equation for calculating s
        }
        scanline[i] = sqrt((prSum*prSum)+(piSum*piSum)); //final equation for calculating scanline
        
    } 
}

void BmodeClass::getScanline(float *data)
{
for (int i = 0; i<imparams->getNumPixel(); i++){ //for loop to iterate through all elements of scanline
    data[i] = scanline[i]; // inputs all values from scanline[] into data[]
}
}

void BmodeClass::deleteScanline()
{
    delete scanline; // no need for for loop because scanline is only a 1D array
}