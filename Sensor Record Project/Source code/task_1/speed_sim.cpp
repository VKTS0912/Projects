#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

// shuffle the array of sensor ids
void shuffle(int array[], int length){
    srand(time(NULL));
    for (int i = 0; i < length; i++){
        int swap_index = rand() % length;   // create a random integer between 0 and length-1
        int temp = array[i];
        array[i] = array[swap_index];
        array[swap_index] = temp;
    }
}

void createFile(int num_s, int sim_st, int sim_i)
{

    struct tm *mytm;
    // declaring argument of time()
    time_t my_time = time(NULL);

    // returns the current system time as Unix time
    time(&my_time);

    // create the beginning timestamp in the form of HH:MM:SS
    mytm = localtime(&my_time);
    char timestamp[100];

    // file pointer
    fstream myFile;
    string fileName = "speed_data_" + to_string(my_time) + ".csv";
    // opens an existing csv file or creates a new file.
    myFile.open(fileName, ios::out | ios::app);

    // generate an array of random speed
    srand(time(NULL));
    double ran_speed[1000];

    int sensor_id[1000];
    for (int i = 0; i < num_s; i++){
        sensor_id[i] = i + 1;
    }
    shuffle(sensor_id, num_s); // shuffle so that sensor ids have random orders

    // Insert the data to file
    myFile << "id,time,values\n";

    int sim_count = sim_i/sim_st;   // number of times 1 id appear
    for (int i = 0; i < sim_count; i++){
        for (int j = 0; j < num_s; j++){
            strftime(timestamp, sizeof(timestamp), "%H:%M:%S", mytm);  // create the timestamp by format
            ran_speed[j] = ((double) rand()) / ((double) RAND_MAX) * 3000; // create random speed between 0 and 3000
            myFile << sensor_id[j] << ",";
            myFile << timestamp << ","
                    << fixed << setprecision(1) << ran_speed[j]  //set fixed 1 digits after decimal point
                    << "\n";
        }
        
        if (i == sim_count-1){
            mytm->tm_sec -= sim_st;
        }
        mytm -> tm_sec += sim_st;
        if (mytm->tm_sec >= 60){
            mytm->tm_min += mytm->tm_sec/60;
            mytm->tm_sec -= (mytm->tm_sec/60 * 60);
            if (mytm->tm_min >= 60){
                mytm->tm_hour += mytm->tm_min/60;
                mytm->tm_min -= mytm->tm_min/60 * 60;
                if (mytm->tm_hour >= 24){
                    mytm->tm_hour -= 24;
                }
            }
        }
    }
    myFile.close();
}

int main(int argc, char** argv)
{
    int num_s=1, sim_st=10, sim_i=3600, cnt=0, cnt_simi=0, cnt_simst=0, cnt_nums=0;
    char str[1000];
    ofstream error;
    
    
    for (int i=1; i< argc; i++){
        if (strcmp(argv[i],"-n") == 0){
            cnt_nums++;
            num_s = atoi(argv[i+1]);    // Convert inputs into integers to be stored in variables
            itoa(num_s, str, 10);
            cnt++;
            if(num_s <= 0||strchr(argv[i+1], '.')!=NULL||strcmp(argv[i+1], str)!=0){
                num_s=0;
                //This is for the case the user enter a float number, the error message will appear normally. 
                //However, at the same time a csv file will still be created.
                error.open("task1.log", ios::app);
                error << "error 1.2 : invalid number of sensors" << "\n";
                error.close();
                cout << "error 1.2 : invalid number of sensors" << "\n";
            }
        }
        if (strcmp(argv[i],"-st") == 0){
            cnt_simst++;
            sim_st = atoi(argv[i+1]);
            itoa(sim_st, str, 10);
            cnt++;
            if(sim_st <= 0||strchr(argv[i+1], '.')!=NULL||strcmp(argv[i+1], str)!=0){
                sim_st=0;
                error.open("task1.log", ios::app);
                error << "error 1.3 : invalid number of sampling time" << "\n";
                error.close();
                cout << "error 1.3 : invalid number of sampling time" << "\n";
                
            }
        }
        if (strcmp(argv[i],"-si") == 0){
            cnt_simi++;
            sim_i = atoi(argv[i+1]);
            itoa(sim_i, str, 10);
            cnt++;
            if(sim_i <= 0||strchr(argv[i+1], '.')!=NULL||strcmp(argv[i+1], str)!=0||sim_i<sim_st){
                sim_i=0;
                error.open("task1.log", ios::app);
                error << "error 1.4 : invalid duration" << "\n";
                error.close();
                cout << "error 1.4 : invalid duration" << "\n";
                
            }
        }
    }
    
    if (num_s == 0 || sim_st == 0 || sim_i == 0) 
        return 0;
    else if(cnt != ((float)argc-1)/2||cnt_nums>1||cnt_simst>1||cnt_simi>1){
        error.open("task1.log", ios::app);
        error << "error 1.1 : invalid command line argument" << "\n";
        error.close();
        cout << "error 1.1 : invalid command line argument" << "\n";
        return 0;
    }

    createFile(num_s, sim_st, sim_i);    
    return 0;
}