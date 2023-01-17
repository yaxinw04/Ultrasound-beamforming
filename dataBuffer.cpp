#include "dataBuffer.h"
using namespace std;


dataBuffer::dataBuffer()
{
numElement = 0; //initializing numElement to 0, step 1 pt1
numSample = 0; // initializing numSample to 0, step 1 pt1
scanline = 0; // initializing scanline to 0, step 1 pt1
dataMatrix = NULL; //initializes dataMatrix to NULL, step 1 pt1 
next = NULL; // iniializing next to NULL, step 1 pt1

}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
// DO I NEED TO ADD SMTH FOR THE IFSTREAM POINTERS?? WHAT ARE IFSTREAM POINTERS? 
numElement = inputNumElement; //sets inputNumSample to numElement, step 1 pt2 WDYM ASSIGNED TO SCANLINE????!!
numSample = inputNumSample; // sets inputNumSample to numSample, step 1 pt2 
scanline = inputScanline; // sets inputScanline to scanline, step 1, pt2
dataMatrix = createDataMatrix(); // calls create dataMatrix to create a 2D array and assings it to dataMartrix
loadRFData(dataMatrix, imagFile, realFile); // call loadRFData to populate dataMatrix
} 

dataBuffer::~dataBuffer() //DESTRUCTOR 
{
deleteDataMatrix(); // destructor calls deleteDataMatrix to release 2D array for dataMatrix
}


complex **dataBuffer::createDataMatrix()
{

complex **RFData; //initializing dataBuffer as a 2D array
RFData = new complex *[numElement]; // numElement is like x values 

for (int i = 0; i <numElement; i++){
RFData[i]= new complex[numSample]; // numSample is like the y values 
}

return RFData;

}

int dataBuffer::loadRFData(complex **RFData, std::ifstream* imagFile, std::ifstream *realFile) 
{ 

if (!imagFile->good())
    return -1;  

else if (!realFile->good())
    return -1;

const int arraysize = 100;
char tempimag [arraysize]; //use variable tempimag to store the string from the imaginary file
char tempreal [arraysize]; // use variable tempreal to store the string from the real file
for ( int i = 0; i< numElement; i++ ){
    for (int x = 0; x< numSample; x++){
        imagFile ->getline(tempimag, arraysize); 
        RFData[i][x].imag = atof(tempimag); //accesing the imag part of the complex struct type, populates it with tempimag
        realFile -> getline(tempreal, arraysize);
        RFData[i][x].real = atof(tempreal); // accessing the real part of the complex struct type, populates it with tempreal
    }
}
return 0;   
}

float dataBuffer::getRealRFData(int element,int sample)
{
return dataMatrix[element][sample].real;
}

float dataBuffer::getImagRFData(int element,int sample)
{
return dataMatrix [element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
for (int i = 0; i < numElement; i++){
    delete dataMatrix [i];
}
delete dataMatrix; 
}




