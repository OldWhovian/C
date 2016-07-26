/*
#Chase Cabrera masc1074 
#Michael Potts masc1071 
#June 20th, 2015         
#Professor Leonard      
#CS570 Summer 2015      
#Assignment 3
#README 570              
*/

#include "a3.h"

using namespace std;


int pipefds[2];
char buffer[1];
pid_t firstp,secondp,thirdp;


//Display the local time 
clock_t a3::clock (){
	 while (true) {
	        sleep(1);
	 	close(pipefds[1]);
	 	read(pipefds[0],buffer,1);
	 	if(buffer[0]=='0'){
	 		exit(0);
	 	}
        time_t timer;
        struct tm * timeinfo;
        char buffer[80];
        time (&timer);
        timeinfo = localtime (&timer);
        strftime(buffer, 80, "%I:%M:%S\n", timeinfo);
        cout << buffer;
        //sleep(1);
    }
return 0;

}

//Creates a countdown that communicates with clock once it reaches 0;
void a3::countDownTimer(int num){
    int m, s;
    int count = num;

    cout << "A COUNTDOWN TIMER " << endl;
	while(count >= 0){
		s = count%60;
    	m = count/60;
    	//prints
    	cout << "Countdown: ";
    	cout << "00:";
        cout << setfill('0') << setw(2) << m << ":";
        cout << setfill('0') << setw(2) << s <<endl;
        write(pipefds[1],"1",1); //initialize the value of the pipe so it has something to read

    	count--;
    	sleep(1);
	}

	close(pipefds[0]);
    write(pipefds[1],"0",1); //writes breaking condition for pipe
    close(pipefds[1]);
}

void a3::callUpTime(){
    
    while (true) {
	sleep(5);
	close(pipefds[1]);
	read(pipefds[0],buffer,1);
	if(buffer[0]=='0'){
	exit(0);
        }
    }
       
    FILE *handle = popen("/user/bin/uptime","r");
    if(handle == NULL){
        exit(1); //failure to open program
    }
    
    char buff[64];
    size_t readn;
    while((readn = fread(buff, 1, sizeof(buff), handle)) > 0){
        fwrite(buff, 1, readn, stdout);
    }
    
    pclose(handle);
    //sleep(5);
}

int main(int argc, char* argv[]){
    a3 obj;
	int runtime;
	//signal handlers, makes the clock uninterruptible
	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
        if(argc > 1){
	    cout << "Too many arguments." << '\n';
	}
	if(argc == 1)
            runtime = 10;  // default runtime to 10 if no arg passed
        else{
            stringstream ss (argv[1]);
            ss >> runtime; // convert input string to int if there is an arg
        }
        
	if(runtime > 3599 ){
		cout << "Too long of a countdown. Exiting" << endl;
		exit(1);
	}
	//pipe error checking
	if(pipe(pipefds) == -1){
		cout << "Pipe Failure" << endl;
		exit(1);
	}
	firstp = fork();
	if(firstp == -1){
		cout << "Fork Failed"<< endl;
		exit(1);
	}
	//In child process
	if(firstp == 0){
        obj.countDownTimer(runtime); //do countdown until reaches 0
        
	}
	else {
		secondp = fork();
		if(secondp == -1){
			cout << "Fork Failed" << endl;
			exit(1);
		}
		//In child process
		else if(secondp == 0){
                    obj.callUpTime();
		                
		}
                else {
                    thirdp = fork();
                    if(thirdp == -1){
                        cout << "Fork Failed" << "\n";
                    }
                    else if(thirdp == 0){
                        obj.clock();
			
                    }                
		//Wait for the child to be done
                    else {
                            waitpid(firstp,NULL,0);
			    waitpid(thirdp,NULL,0);
                            cout<< "Countdown is finished." << endl;
                            exit(0);
			    exit(0);
                    }
                }
	}
	exit(0);
}
    

