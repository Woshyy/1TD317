#include <stdio.h>
#include <iostream>

#define ONE_DAY_IN_SEC 86400
#define ONE_HOUR_IN_SEC 3600
#define ONE_MINUTE_IN_SEC 60

using namespace std;

int main() {
    int amount_competitors = 0;
    int winner_number = -1;
    int best_time = ONE_DAY_IN_SEC;

    while (true) {
        int runner_number;
        cout << "Startnummer? ";
        cin >> runner_number;

        // runner_number < 1 are considered valid.
        if (runner_number < 1) break;

        // Increase the amount of competitors because we got a valid runner_number i.e runner_number > 0.
        ++amount_competitors;

        // Taking in start time and saving it in seconds..
        int start_time_hour, start_time_minute, start_time_second, start_time;
        cout << "Starttid? ";
        cin >> start_time_hour >> start_time_minute >> start_time_second;
        start_time = start_time_hour * ONE_HOUR_IN_SEC + start_time_minute * ONE_MINUTE_IN_SEC + start_time_second;

        // Taking in finish time and saving it in seconds.
        int finish_time_hour, finish_time_minute, finish_time_second, finish_time;
        cout << "Måltid? ";
        cin >> finish_time_hour >> finish_time_minute >> finish_time_second;
        finish_time = finish_time_hour * ONE_HOUR_IN_SEC + finish_time_minute * ONE_MINUTE_IN_SEC + finish_time_second;

        // If the resulting time is a minus than the starttime and finishtime passes through midnight, which means we must add a day worth of time
        // to the current time to get the correct time.
        int current_time = finish_time - start_time;
        if (current_time < 0) { 
            current_time += ONE_DAY_IN_SEC;
        }

        // Check if the current time is better than the current best time.
        if (current_time < best_time) {
            best_time = current_time;
            winner_number = runner_number;
        }
    }

    // If there were competitors added to the race then we print out "normally" otherwise we output "no competitors."
    if (amount_competitors > 0) {
        // Save it as an int to remove the decimals after the division.
        int disp_hour = best_time/ONE_HOUR_IN_SEC;
        // Remove the seconds that has been converted to hours on the best time so we get the remaining time.
        best_time -= disp_hour * ONE_HOUR_IN_SEC;

        // Save it as an int to remove the decimals after the division.
        int disp_min = best_time/ONE_MINUTE_IN_SEC;
        // Remove the seconds that has been converted to minutes on the best time so we get the remaining time.
        best_time -= disp_min * ONE_MINUTE_IN_SEC;

        //The remaining time is just the second.
        int disp_sec = best_time;

        cout << "Vinnaren är startnr: " << winner_number << endl;
        cout << "Tim: " << disp_hour << " Min: " << disp_min << " Sek: " << disp_sec << endl;
        cout << "Antal tävlande: " << amount_competitors << endl;
    }
    else {
        cout << "Inga tävlande" << endl;
    }

    cout << "Programmet avslutas" << endl;
    return 0;
}