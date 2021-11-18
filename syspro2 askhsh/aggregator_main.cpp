#include <string>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>

#include "AggregatorShell.h"
#include "CountryInfo.h"
#include "Date.h"
#include "errors.h"
#include "Protocol.h"

using namespace std;

int main_worker(int argc, char *argv[]);

void catchinterruptA1(int signo) { // grapse to log kai kane exit
    cout << "Aggregaotr Signo: " << signo << " catched (SIGINT/QUIT)" << endl;

}

int main(int argc, char *argv[]) {
   

    int bufferSize;
    int numWorkers;
    char* whichDirectory;
    int i;

    if (argc == 7) {

        int whichArg = 1;

        while (whichArg < 7) {
            if (strcmp(argv[whichArg], "-i") == 0) {
                whichDirectory = argv[whichArg + 1];
                whichArg = whichArg + 2;
            } else if (strcmp(argv[whichArg], "-w") == 0) {
                if (atoi(argv[whichArg + 1]) != 0) {
                    numWorkers = atoi(argv[whichArg + 1]);
                    whichArg = whichArg + 2;
                } else {
                    whichArgumentError(argv[whichArg]);
                    exit(-1);
                }
            } else if (strcmp(argv[whichArg], "-b") == 0) {
                if (atoi(argv[whichArg + 1]) != 0) {
                    bufferSize = atoi(argv[whichArg + 1]);
                    whichArg = whichArg + 2;
                } else {
                    whichArgumentError(argv[whichArg]);
                    exit(-1);
                }
            } else {
                printf("Error : inputs are wrong , try./[programName] -u [file].txt -w [integer] -b [integer]\n");
                exit(-1);
            }
        }
    } else {
        printArgumentError();
        exit(-1);
    }


    cout << "looking into: " << whichDirectory << endl;

    DIR * mydir = opendir(whichDirectory);

    if (mydir == nullptr) {
        cout << "Directory: " << whichDirectory << " could not be opened " << endl;
        return -1;
    } else {
        struct dirent *direntp;
        int i = 0;

        while ((direntp = readdir(mydir)) != NULL) {
            if (isalpha(direntp->d_name[0])) {
                string name = direntp->d_name;
                CountryInfo::add(new CountryInfo(name, i % numWorkers));
                i++;
            }
        }
    }

    CountryInfo::print();

    Protocol::bufferSize = bufferSize;
    Protocol::buffer = new char[bufferSize];

    Worker * workers = AggregatorShell::setupCommunication(whichDirectory, numWorkers, bufferSize);

    printf("Aggregator prepared!!! \n");

    static struct sigaction act;

    act.sa_handler = catchinterruptA1;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    AggregatorShell::shell(workers, numWorkers, bufferSize);

    // na grapsw ta log files!!!!!!!!!!!!
    AggregatorShell::closeCommunication(numWorkers, workers);



    CountryInfo::destroy();

    delete [] (char*) Protocol::buffer;
    
    
    

    cout << "Aggregator exited with PID: " << getpid() << "\n";

    return 0;
}