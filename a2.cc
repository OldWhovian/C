/*
#Chase Cabrera masc1074 
#Michael Potts masc1071 
#June 9th, 2015         
#Professor Leonard      
#CS570 Summer 2015      
#Assignment 2
#README570              
*/
#include "a2.h"

using namespace std;

a2::a2(string s):frame_vector() {
    read_file(s);
}
void a2::read_file(string file) {			//function that reads the text file
    string word;
    int num;
    
    ifstream in(file.c_str());//We pass "pages.txt" by using ifstream
    if(!in){
        cout << "File does not exist" << endl;
        exit(1);
    }
    while (in >> word){
    	//num = stoi(word);		//convert word to an integer by using stoi
        stringstream ss(word);
        ss >> num;                      //convert word to an integer using stringstream, stoi is only avaiable on C++11
        frame_vector.push_back(num);
    }
    in.close();
}

void a2::fifo(int num_frame){		//fifo page replacement algorithm
	int frame[num_frame];
	bool found = false;
    int fault_count = 0;
	int index = 0;
	for(unsigned int i = 0; i < num_frame; i++){
		frame[i]= -1;				//intializes the frames to -1
	}
	for(unsigned int i = 0; i < frame_vector.size(); i++){
		int temp = frame_vector.at(i);
		bool found = find(num_frame, frame, temp);	//checks if the there is a duplicate that is being entered in the frames
		if(!found){					//if it is not a duplicate then replace the page frame and increment fault count
			frame[index++ % num_frame] = temp;
			fault_count++;
		}
        
    }
	cout<< "FIFO Number of Page Faults: " << fault_count << endl;
}

void a2::lru(int num_frame){
    
	bool found = false;
    int fault_count = 0;
	int index = 0;
    int indextmp = 0;

    int frame[num_frame];
	for(unsigned int i = 0; i < num_frame; i++){
		frame[i]= -1;				//intializes frames to -1
	}
	for(unsigned int i = 0; i < frame_vector.size(); i++){
        cout << "Begin ";
		int temp = frame_vector.at(i);
		bool found = find(num_frame, frame, temp);	//checks if the there is a duplicate that is being entered in the frames
        cout << "value: " << temp << " ";
        cout << "found: " << found << " " ;
		if(!found){
            //if it is not a duplicate then replace the page frame and increment fault count
            if( index != num_frame){//fill the array
                frame[index++] = temp;
                
            }
            else {//shift
                for (int j = 0; j < num_frame ; j++) {
                    frame[j] = frame[j+ 1];
                    if (j  == num_frame -1 ) {
                        frame[num_frame - 1]=temp;
                        break;
                     }
                    
                }
            }
        fault_count++;
            cout << "fault: " << fault_count;
            
		}
        else {//inside
            int repvalue;
            cout << "in" << " ";
            for (unsigned int j = 0; j < num_frame; j++) {
                if(temp == frame[j]){//found that value in the array
                    cout << "j: " << j << " " ;
                    for (unsigned int s = j; j < num_frame; s++) {
                        cout << "s: " << s << " " ;

                        if (s == num_frame-1) {
                            cout <<" h ";
                            frame[num_frame-1] =temp;
                            cout <<" z ";
                            break;
                        }
                                                frame[s] = frame[s+1];
                        cout << " not founat ";

                    }
                }
            }
        }
        cout << "frame: ";
        for (unsigned int y = 0; y < num_frame; y++) {
            cout <<frame[y] << " ";
        }
        cout<< "END" <<endl;
    
    }
        

	cout<< "LRU Number of Page Faults: " << fault_count << endl;
}


void a2::opt(int num_frame){
    int frame[num_frame];
    
    for (unsigned int i = 0; i < num_frame; i++) {
        frame[i] = -1;					//initializes frames to -1
    }
    unsigned int index, check, good, turn;
    unsigned int pageindex = 0;
    unsigned int best = 0;
    unsigned int fault = 0;
    
    for (index = 0;  index < frame_vector.size(); index++) {
        check = 0;
        for (unsigned int i = 0; i < num_frame; i++) {			//check page table
            if(frame[i] == frame_vector.at(index)){
                check++;
                break;
            }
        }
        if (check == 0) {						//checks for a page fault
            if(pageindex < num_frame){
                frame[pageindex++] = frame_vector.at(index);		//initializes the page table
            }
            else {							//checks the furthest element in the input
                good = turn = 0;
                for (unsigned int j = 0; j < num_frame; j++) {
                    for (unsigned int k = index+1; k < frame_vector.size(); k++) {
                        if (frame_vector.at(k) == frame[j]) {
                            turn  = k;
                            break;
                        }
                        turn = k;
                    }
                    if (turn == (frame_vector.size()-1) && frame_vector.at(turn) != frame[j]) {
                        turn++;
                    }
                    if (turn > good) {
                        good = turn;
                        best = j;
                    }
                    
                }
                frame[best] = frame_vector.at(index);
            }
            fault++;						//increments fault count
        }
        
    }
    cout << "OPT Number of Page Faults: " <<  fault << endl;
}



void a2::clock(int num_frame){
    
    int frame[num_frame];
    int bits[num_frame];
    int index = 0;
    int fault = 0;
    int bits_count = 0;
    int insert = 0;
    int pointer = 0;
    int full = 0;
    for (unsigned int i = 0 ; i < num_frame; i++) { //initialize the arrays
        frame[i] = -1;
        bits[i] = 0;
    }
    
    bool flag = false; //check for page fault
    for (unsigned int i = 0; i < frame_vector.size(); i++) { // goes through the frames vector
        flag = true;
        
        if (isfull(bits, num_frame)) {//check in the bit array is full (all 1)
            full = num_frame;
        }
        int temp = frame_vector.at(i);
        for(unsigned int j = 0; j < num_frame; j++){ //goes into the frame array and check for the value
            
            if (frame[j] == temp) {//if in frame, make bit = 1
                flag = false; // no page fault so skip
                bits[j] = 1;
                break;
            }
        }
        if(flag){//page fault
            for (unsigned int j = 0; j < num_frame ; j++) {
                
                //reset if not found
                if (full == num_frame) {
                    for (int g = 0; g < num_frame; g++) {
                        bits[g] = 0;
                    }
                    
                    frame[bits_count] = temp;
                    bits[bits_count] = 1;
                    
                    
                    bits_count = (bits_count + 1) % num_frame;
                    
                    full = 0;
                    break;
                }
                //check if clock pointer is 1 if so  make that bit 0 and move until the next 0 bits and make flip it to 1
                //and add to frame
      /*          else if(bits[bits_count] == 1){
                    bits[bits_count] = 0;
                    //keep going until open space
                    index = bits_count;
                    while (true) {
                        index = (index+1) % num_frame;
                        if (bits[index] == 0) {
                            bits[index] = 1;
                            frame[index] = temp;
                            bits_count = (index+1) % num_frame;
                            break;
                        }
                        index++;
                        
                    }
                    break;
                }*/
                else if(bits[bits_count] == 1){
                    //bits[bits_count] = 0;
                    //keep going until open space
                    index = bits_count;
                    while (true) {
                        index = (index+1) % num_frame;
                        if (bits[index] == 0) {
                            bits[index] = 1;
                            frame[index] = temp;
                         //   bits_count = (index+1) % num_frame;
                            break;
                        }
                        index++;
                        
                    }
                    break;
                }
                //check is clock pointer is 0, if it is flip to one and add to the frame
                else if(bits[bits_count]==0){
                    frame[bits_count] = temp;
                    bits[bits_count]=1;
                    bits_count = (bits_count + 1) % num_frame;
                    
                    break;
                }
            }
            fault++;
        }
        for (int h = 0; h < num_frame; h++) {
            cout << frame[h] << " ";
        }
        cout << endl;
        for (int h = 0; h < num_frame; h++) {
            cout << bits[h] << " ";
        }
        cout<<endl;
    }
    cout << "Clock Number of Page Faults: " << fault << endl;
}


bool a2::isfull(int frame[], int num_frame){
    for (unsigned int i = 0; i < num_frame; i++) {
        if (frame[i] == 0) {
            return false;
        }
    }
    return true;
}


bool a2::find(int length, int *frame_queue, int value){			//function to check if the number is already in the page frames
    
	for(int i = 0; i < length; i++){
		if(frame_queue[i] == value){
			return true;
		}
	}
	return false;
}

int main (int argc, char *argv[]) {
    
    if (argc != 1) {
        cout << "This program requires no arguments" << endl;
        exit(1);
    }
    
    int number;
    string temp;
    
    cout << "Please enter a number of frames to begin: " << endl;
    while (cin >> temp) // Used cin over getline to prevent errors on recursive call.
    {
        stringstream ss(temp);

        if (ss >> number)
        {
            if (ss.eof() && number <= 100)
            {
                break;
            }
        }
        cout << "Invalid entry: frame must be between 1 - 100\n"
        "Try again."<<endl;
    }
    cout << "Running algorithm...\n"<<endl;

    
    a2 fault_algorithm("pages.txt");
    //fault_algorithm.fifo(number);
    fault_algorithm.lru(number);
    fault_algorithm.opt(number);
    fault_algorithm.clock(number);
    
    cout << endl;
    
    a2 fault_algorithm2("pages2.txt");
    //fault_algorithm2.fifo(number);
    fault_algorithm2.lru(number);
    fault_algorithm2.opt(number);
    fault_algorithm2.clock(number);
    
    cout << "Do you want to try again? (y) to continue. Anything else to exit (n)" << endl;
    cin >> temp;
    
    if (temp == "y"){
		main(1,0); // agrc is expected to be 1
                exit(0);   // Program will return recursively so must be able to exit after it calls itself
    }
    
    
    else{
		exit(0);
    }
}


