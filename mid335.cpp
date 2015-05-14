//Moises Ayala
//This program reads in notes and will do a testing with its frequency output.
//CMPS 335
//mid335.cpp
// with a tolerance of .005 our number of bad values is 108.
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4

typedef enum {
	C = 1,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
    Z, 
	END = Z,
	HALF_STEPS_PER_OCTAVE = B,
} note_t;

double freq(note_t note, int octave_delta);
void unitTest(note_t *);
//The following variables are 
//needed for my unit test function
//------------------------------
int octaveArray[9];
double output[9][12];
double tolerance = .004, error;
//-----------------------------
int main(int argc, char *argv[])
{
    string info;
	note_t note;
	int octave_delta = 0;
    ifstream file;
    file.open("info.txt");
    note_t testNote[12] = {C,Cs,D,Ds,E,F,Fs,G,Gs,A,As,B};
	if (argc != 3 && argc != 4) {
		cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA> <optional:tolerance>" << endl;
		return 0;
	}
    if (argc == 4) {
        tolerance = atoi(argv[3]);
    }
    // Setting up the ocale array and also importing my values from the website
    for (int i = 0; i < 9; i++) {
        octaveArray[i] = i;
        for(int j = 0;j < 12;j++) {
            file >> info;
            output[i][j] = atof(info.c_str());
        }
    }
    //Done with file so closing it.
    file.close();
	//
	note = (note_t)(toupper(argv[1][0]) - 64);
	switch(toupper(argv[1][0])) {
		case 'A': note = A; break;
		case 'B': note = B; break;
		case 'C': note = C; break;
		case 'D': note = D; break;
		case 'E': note = E; break;
		case 'F': note = F; break;
        case 'Z': note = Z;  break;
	}
	if (note > END) {
		cout << "Invalid note!" << endl;
        return 1;
    }
    //You may call your unit test here...
    if(note == Z && octave_delta == 0) {
        unitTest(testNote);
        cout<<"bad element count: "<<error<<endl;
        cout<<"unit test complete\n";
    }
    else {
        octave_delta = atoi(argv[2]);
        cout << HALF_STEPS_PER_OCTAVE << endl;
        cout << freq(note, octave_delta) << endl;
    }
    return 0;
}

//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
	double freq;
	double factor;
	double a;
	int n;
	int octave = octave_delta - F0_octave;

	a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
	n = note - F0_note;
	freq = F0 * pow(a, (double)n);
	factor = pow(2.0, (double)octave);
	freq = freq * factor;
	return freq;
}

//--------------------------------------------------------------------------------------
//This functions will do a unit test on the freq function and will print out each result.
//---------------------------------------------------------------------------------------
void unitTest(note_t *testNote) 
{
    cout<<"tolerance: "<<tolerance<<endl;
    cout<<"freq function unit-test\n\n\n";
    string check;
    double diff;
    double result;
    error = 0;
    cout<<setw(10)<<"note"<<setw(10)<<"octave"<<setw(10)<<"value"<<setw(15)<<"diff\n";
    cout<<setw(10)<<"----"<<setw(10)<<"------"<<setw(10)<<"-----"<<setw(15)<<"----\n";

    for ( int i = 0; i < 9; i++) {
        for (int j = 0 ; j < 12; j++) {
            result = freq(testNote[j],octaveArray[i]);
            diff = result - output[i][j];
            diff = abs(diff);
            if (diff < tolerance) {
                check = "GOOD!";
            }
            else {
                check = "<---BAD";
                error++;
            }
            cout<<setw(10)<<testNote[j]<<setw(10)<<octaveArray[i]<<setw(10)<<result<<setw(20)<<diff<<setw(10)<<check<<endl;
        }
    }
}
