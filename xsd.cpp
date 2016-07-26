/* 
 * Class: CS530, Spring 2015
 * File:   xsd.cpp
 * Author: Michael Potts, masc0677
 * Assignment #1, Hex Simple Dump
 */

#include <iomanip>
#include <iostream>
#include <fstream>
#include <bitset>
#include <ctype.h>

using namespace std;

void hexDump(string fileName){
    ifstream fileStream;
    fileStream.open(fileName.c_str(), ifstream::in);
    int getChar[16];
    int currCharCount; // Index for getChar[]
    unsigned long int address = 0;
    int get(); // Define get function to return int
    
    while (fileStream.good()){ // Checks for file stream errors and EOF
        currCharCount = 0; // Reset indexer
	cout << setw(7) << setfill('0') << hex << address << dec << ": "; // print address length 7
        
        while (currCharCount <= 15 && // gets next 16 characters of file
              (getChar[currCharCount] = fileStream.get()) != EOF){
            address++;
            currCharCount++;
        }
        
	currCharCount = 0; // Reset indexer
	while(currCharCount <= 15 && getChar[currCharCount] != EOF){
	    cout << setw(2) << hex << getChar[currCharCount] << dec;
	    if((currCharCount%2) == 1) // Separate columns
			cout << " "; 
	    currCharCount++;
	}
	
	if(getChar[currCharCount] == EOF){ // if EOF comes before the end of current line
	    while(currCharCount <= 15){
	        cout << "  "; // Prints spaces to keep columns even
	        if((currCharCount%2) == 1)
	            cout << " ";
	        currCharCount++;
	    }
	}
	
	currCharCount = 0; // Reset indexer
	while(currCharCount <= 15 && getChar[currCharCount] != EOF){
	    if(!isprint(getChar[currCharCount]))
	        cout << '.'; // Replaces non-printable chars
	    else 
	        cout << (char)getChar[currCharCount];
	    currCharCount++;
	}

	cout << "\n";
	
    }
    fileStream.close();
}

void binDump(string fileName){
    ifstream fileStream;
    fileStream.open(fileName.c_str(), ifstream::in);
    int getChar[6];
    int currCharCount; // Indexer
    unsigned long int address = 0;
    int get(); // Define get function as int
    
    while (fileStream.good()){
        currCharCount = 0; // Reset indexer
	cout << setw(7) << setfill('0') << hex << address << dec << ": "; // print address length 7
        
        while (currCharCount <= 5 && // Gets next 6 chars
              (getChar[currCharCount] = fileStream.get()) != EOF){
            address++;
            currCharCount++;
        }
        
	currCharCount =0; // Reset Index
	while(currCharCount <= 5 && getChar[currCharCount] != EOF){
	    cout << bitset<8>(getChar[currCharCount]) << dec << ' ';
	    currCharCount++;
	}
	
	if(getChar[currCharCount] == EOF){ // If EOF comes before end of current line
	    while(currCharCount <= 5){
	        cout << "         "; // Print spaces to maintain columns
	        currCharCount++;
	    } 
	}
	
	currCharCount = 0; // Reset indexer
	while(currCharCount <= 5 && getChar[currCharCount] != EOF){
	    if(!isprint(getChar[currCharCount]))
	        cout << '.'; // Replaces unprintable chars
	    else 
	        cout << (char)getChar[currCharCount];
	    currCharCount++;
	}
	
	cout << "\n";
    }
    fileStream.close();
}

int main(int argc, char** argv) {
    
    if(argc == 2){ // Program name and file name
	hexDump(argv[1]);
	}
    else if(argc == 3){ // Has -b option
        binDump(argv[2]);
	}
    else { // too many or too little command line args
        cout << "Input should be: './xsd InputFile' or './xsd -b InputFile'";
        return 1; // failed
    }
    return 0; // succeeded
}

