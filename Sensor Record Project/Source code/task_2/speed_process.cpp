#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

// Create a struct to read data into
struct SensorRecord{
    int id, hour, minute, second;
    string timestamp, sorted_timestamp[1000];
    double ran_speed, sorted_speed[10000];
};

int id, sim_st, sim_i, cnt = 0, cnt_1 = 0 , i = 0, count = 0, n = 0, k = 1, num_id = 1, error_cnt = 0;
int increment_count[10000], decrement_count[10000], num[10000], id_count[10000] = { 0 }, speed_change, time_change;
string timestamp, tempString = "", temp_timestamp;
double ran_speed, temp_speed, sum[10000];
SensorRecord outlier[1000], valid_sensor[1000], max_speed[1000], min_speed[1000], avg_speed[1000],
    all_sensor[1000], myTime[1000], valid_time[1000], sorted_id[1000];

ofstream task2_error;
ifstream infile;
void outlier_data(string fileName){
    /* TASK 2.1 */
    infile.open(fileName);

    while (infile.good()){
        //reading the sensor ids
        getline(infile, tempString, ',');
        id = atoi(tempString.c_str());
        //reading the timestamp
        getline(infile, timestamp, ',');
        //reading the speed
        tempString = "";
        getline(infile, tempString, '\n');
        ran_speed = atof(tempString.c_str());
        tempString = "";

        all_sensor[cnt_1].id = id;
        all_sensor[cnt_1].timestamp = timestamp;
        all_sensor[cnt_1].ran_speed = ran_speed;
        cnt_1++;

        // check the valid speed
        if (ran_speed != 0){   // to eliminate the case the file read empty line and set ran_speed = 0
            if (ran_speed < 900 || ran_speed > 1600){
                outlier[count].id = id;
                outlier[count].timestamp = timestamp;
                outlier[count].ran_speed = ran_speed;
                count ++;   
            } else {
                valid_sensor[cnt].id = id;
                valid_sensor[cnt].timestamp = timestamp;
                valid_sensor[cnt].ran_speed = ran_speed;
                cnt++;
            }
        }
    }
    infile.close();

    // check error 2.3
    for (i = 1; i < cnt_1-1; i++){
        if (all_sensor[i].id == 0 || all_sensor[i].ran_speed == 0 || all_sensor[i].timestamp == ""){
            task2_error.open("task2.log", ios::app);
            task2_error << "error 2.3: missing data in line " << i << endl;
            task2_error.close();
            cout << "error 2.3: missing data in line " << i << endl;
            error_cnt++;
        }
    }
    if (error_cnt > 0) exit(1);

    ofstream outlier_data;
    outlier_data.open("outlier_data.csv", ios::out | ios::trunc);
    outlier_data << fixed << setprecision(1);
    outlier_data << "number of outliers: "<< count << "\n"
            << "id, time, values\n";
    for (i = 0; i < count; i++){
        outlier_data << outlier[i].id << ", " << outlier[i].timestamp << ", " << outlier[i].ran_speed << endl;
    }
}

void data_summary(string fileName){
    /* TASK 2.2 */

    // Find the simulation interval for time of the mean speed
    int m = 0, hour, minute, second;    // Get the hour, minute, second of timestamp
    int group_cnt = 0;  // number of times each sensor id in the list of all sensors appear
    string str;
    double valid_speed[10000];
    infile.open(fileName);
    getline(infile, str);   // ignore first line of the file
    while (infile.good()){
        //reading the sensor ids
        getline(infile, tempString, ',');
        tempString = "";
        getline(infile, tempString, ':');
        hour = atoi(tempString.c_str());
        tempString = "";
        getline(infile, tempString, ':');
        minute = atoi(tempString.c_str());
        tempString = "";
        getline(infile, tempString, ',');
        second = atoi(tempString.c_str());
        tempString = "";
        getline(infile, tempString, '\n');
        valid_speed[n] = atof(tempString.c_str());
        tempString = "";
        myTime[n].hour = hour;
        myTime[n].minute = minute;
        myTime[n].second = second;
        
        if (valid_speed[n] >= 900 && valid_speed[n] <= 1600){
            valid_time[m].hour = hour;       // find specific time of valid sensor
            valid_time[m].minute = minute;
            valid_time[m].second = second;
            m++;
        }
        n++;
    }
    infile.close();
    // Find the sampling time
    for (i=0;i<n;i++){
        if (myTime[i+1].second != myTime[i].second || myTime[i+1].minute != myTime[i].minute
            || myTime[i+1].hour != myTime[i].hour){
            sim_st = (myTime[i+1].hour*3600+myTime[i+1].minute*60+myTime[i+1].second) - (myTime[i].hour*3600+myTime[i].minute*60+myTime[i].second);
            break;
        }
    }
    for (i=0;i<cnt_1;i++){
        if (all_sensor[i].id == 1){     // there is at least 1 id so just need to check id = 1
            group_cnt++;
        }
    }
    // Find the simulation interval
    sim_i = sim_st*group_cnt;
    hour = sim_i/3600;
    minute = (sim_i-hour*3600)/60;
    second = sim_i-hour*3600-minute*60;

    i = 0;
    // set the speed and timestamp of max_speed and min_speed  to the speed and timestamp of the first shown id of each sensor
    while (i<cnt){
        if (valid_sensor[i].id == num_id){
            max_speed[num_id].ran_speed = valid_sensor[i].ran_speed;
            max_speed[num_id].timestamp = valid_sensor[i].timestamp;
            min_speed[num_id].ran_speed = valid_sensor[i].ran_speed;
            min_speed[num_id].timestamp = valid_sensor[i].timestamp;
            num_id++;
            i = 0;
        } else {
            i++;
        }
    }
    
    // Find max_speed, min_speed and avg_speed of each sensor id and store it in array
    i = 0;
    while (i<cnt){
        if (valid_sensor[i].id == k){
            sum[k] += valid_sensor[i].ran_speed;    // sum of speed of each sensor id
            num[k] ++;     // the number of times each sensor id in the list of valid sensors appear

            if (valid_sensor[i].ran_speed > max_speed[k].ran_speed){
                max_speed[k].ran_speed = valid_sensor[i].ran_speed;
                max_speed[k].timestamp = valid_sensor[i].timestamp;
            } 
            
            if (valid_sensor[i].ran_speed < min_speed[k].ran_speed){
                min_speed[k].ran_speed = valid_sensor[i].ran_speed;
                min_speed[k].timestamp = valid_sensor[i].timestamp;
            }
        }
        i++;
        if (i == cnt && k < num_id){
            k++;
            i = 0;
        }
    }
    
    k = 1;
    while (k<num_id){
        avg_speed[k].ran_speed = sum[k]/num[k];
        k++;
    }
    
    ofstream data_summary;
    data_summary.open("data_summary.csv", ios::out | ios::trunc);
    data_summary << fixed << setprecision(1);
    data_summary << "id, paramaters, time, values\n";
    for (i = 1; i < num_id; i++){
        data_summary << i << ", " << "max, " << max_speed[i].timestamp << ", " << max_speed[i].ran_speed << "\n"
            << i << ", " << "min, " << min_speed[i].timestamp << ", " << min_speed[i].ran_speed << "\n"
            << i << ", " << "mean, " << hour << ":" << minute << ":" << second << ", " << avg_speed[i].ran_speed << "\n";
    }
}

void data_statistics(string fileName){
    /* TASK 2.3 */
    i = 0, k = 1;
    int temp_hour[10000], temp_minute[10000], temp_second[10000];
    double temp_ran_speed[10000];
    while (i<cnt){
        if (valid_sensor[i].id == k){
            temp_ran_speed[k] = valid_sensor[i].ran_speed;
            temp_hour[k] = valid_time[i].hour;
            temp_minute[k] = valid_time[i].minute;
            temp_second[k] = valid_time[i].second;
            k++;
            i = 0;
        } else {
            i++;
        }
    }
    i = 0, k = 1;
    while (i<cnt){
        if (valid_sensor[i].id == k){
            speed_change = valid_sensor[i].ran_speed - temp_ran_speed[k]; 
            temp_ran_speed[k] = valid_sensor[i].ran_speed;

            time_change = (valid_time[i].hour*3600+valid_time[i].minute*60+valid_time[i].second)-(temp_hour[k]*3600+temp_minute[k]*60+temp_second[k]);
            temp_hour[k] = valid_time[i].hour;
            temp_minute[k] = valid_time[i].minute;
            temp_second[k] = valid_time[i].second;
            if (speed_change > 100*time_change){
                increment_count[k] ++;
            } else if (speed_change < -100*time_change){
                decrement_count[k] ++;
            }
        }
        i++;
        if (i == cnt && k < num_id){
            k++;
            i = 0;
        }
    }
    
    ofstream data_statistics;
    data_statistics.open("data_statistics.csv", ios::out | ios::trunc);
    data_statistics << "id, direction, frequency\n";
    for (i = 1; i < num_id; i++){
        data_statistics << i << ", " << "increment, " << increment_count[i] << "\n"
            << i << ", " << "decrement, " << decrement_count[i] << "\n";
    }
}

void sorted_algorithm(string fileName){
    /* TASK 2.4 */
    i = 0, k = 1;

    while (i<cnt_1){
        if (valid_sensor[i].id == k){
            sorted_id[k].sorted_speed[id_count[k]] = valid_sensor[i].ran_speed;
            sorted_id[k].sorted_timestamp[id_count[k]] = valid_sensor[i].timestamp;
            id_count[k]++;          //number of index in each of k different arrays of random speed
        }
        i++;
        if (i == cnt_1 && k < num_id){
            k++;
            i = 0;
        }
    }

    for (k=1; k<num_id; k++){
        for (i=0; i<id_count[k]; i++){
            for (int j=i+1; j<id_count[k]; j++){
                if (sorted_id[k].sorted_speed[i] > sorted_id[k].sorted_speed[j]){
                    temp_speed = sorted_id[k].sorted_speed[i];
                    sorted_id[k].sorted_speed[i] = sorted_id[k].sorted_speed[j];
                    sorted_id[k].sorted_speed[j] = temp_speed; 

                    temp_timestamp = sorted_id[k].sorted_timestamp[i];
                    sorted_id[k].sorted_timestamp[i] = sorted_id[k].sorted_timestamp[j];
                    sorted_id[k].sorted_timestamp[j] = temp_timestamp;
                }
            }
        }
    }
}

void sorted_data(string fileName){
    /* TASK 2.4 */
    clock_t start_t, end_t;
    start_t = clock();
    sorted_algorithm(fileName);
    end_t = clock();
    double time_taken = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    ofstream sorted_data;
    sorted_data.open("sorted_data.csv", ios::out | ios::trunc);
    sorted_data << "sorting duration: " << time_taken << " seconds"
                << "\nid,time,values\n";
    sorted_data << fixed << setprecision(1);
    for (k=1; k<num_id; k++){
        for (i = 0; i<id_count[k]; i++){
            sorted_data << k << "," 
            << sorted_id[k].sorted_timestamp[i]  << ","
            << sorted_id[k].sorted_speed[i] 
            << endl;
        }
    }
}

int main(int argc, char *argv[]) 
{
    string fileFormat = ".csv";
    string fileName = "speed_data" + fileFormat;
    
    if (argc == 1){
            outlier_data(fileName);
            if (error_cnt > 0) return 0;
            data_summary(fileName);
            data_statistics(fileName);
            return 0;
    }
    if (argc >= 2){
        if (strcmp(argv[1],"-s") == 0 && argc == 2){
            outlier_data(fileName);
            if (error_cnt > 0) return 0;
            data_summary(fileName);
            data_statistics(fileName);
            sorted_data(fileName);
            return 0;
        }
        fileName = argv[1];
        int found = fileName.find(".");
        if (found == -1){
            task2_error.open("task2.log", ios::app);
            task2_error << "error 2.1: non existing or not readable data file" << endl;
            task2_error.close();
            cout << "error 2.1: non existing or not readable data file" << endl;
            exit(1);
        } 
        string format = fileName.substr(found);
        if (format != fileFormat){
            task2_error.open("task2.log", ios::app);
            task2_error << "error 2.2: wrong data file format" << endl;
            task2_error.close();
            cout << "error 2.2: wrong data file format" << endl;
            exit(1);
        }
        infile.open(fileName);

        if(infile.fail()){
            task2_error.open("task2.log", ios::app);
            task2_error << "error 2.1: non existing or not readable data file" << endl;
            task2_error.close();
            cout << "error 2.1: non existing or not readable data file" << endl;
            exit(1);
        }
        infile.close();
        if (argv[2] == NULL){
            outlier_data(fileName);
            if (error_cnt > 0) return 0;
            data_summary(fileName);
            data_statistics(fileName);
        } else {
            if (argc > 3){
                task2_error.open("task2.log", ios::app);
                task2_error << "error 2.4: invalid command line argument" << endl;
                task2_error.close();
                cout << "error 2.4: invalid command line argument" << endl;
                exit(1);
            } else {
                if (strcmp(argv[2], "-s") == 0){
                    outlier_data(fileName);
                    if (error_cnt > 0) return 0;
                    data_summary(fileName);
                    data_statistics(fileName);
                    sorted_data(fileName);
                } else {
                    task2_error.open("task2.log", ios::app);
                    task2_error << "error 2.4: invalid command line argument" << endl;
                    task2_error.close();
                    cout << "error 2.4: invalid command line argument" << endl;
                    exit(1);
                }
            }
        }
    }
    return 0;
}