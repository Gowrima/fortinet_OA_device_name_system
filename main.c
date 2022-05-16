#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Device Name System
 *
 * Create unique device names to be used in a residential IoT system.
 * If a device name already exists in the system, an integer number is
 * added at the end of the name to make it unique. The integer added starts
 * with 1 and is incremented by 1 for each new request of an existing device
 * name. Given a list of device name requests, process all requests, and
 * return an array of the corresponding unique device names
 *
 * Example
 * n = 6
 * devicenames = [switch, tv, switch, tv, switch, tv]
 *
 *
 * string devicenames[n]: an array of device name strings in the order
 * requested
 * Returns
 * string[n]: an array of string usernames in the order assigned
 *
 * */
int calc_devicename_hash(char* devicename) {

    // hash fn: add up ascii value of each char
    int i = 0;
    int hash_value = 0;

    while (*(devicename+i) != '\0') {
        hash_value += *(devicename+i);
        i++;
    }

    return hash_value>>1;
}

char** deviceNameSystem(char** devicenames, int n) {
    // hashtable = copy devicename to the hashtable
    // key: devicename, value: # of occurances

    // result = array of strings
    char *result[n];
    int ri = 0;
    int hashtable[2048] = {0}; // large hash table; key = hash, value = no. of occurances

    for (int i = 0; i < n; i++) {
        result[i] = (char*) malloc(sizeof(char) * 25);
    }

    for (int i = 0; i < n; i++) {
        // calculate hash of the devicename and add it to the hashtable
        int devicename_hash = calc_devicename_hash(devicenames[i]);
        //printf("devicename = %s, hash = %d\n", devicenames[i], devicename_hash);

        int name_len = strlen(devicenames[i]);
        if (hashtable[devicename_hash] == 0) {
            // add to result
            strncpy(result[ri], devicenames[i], name_len);
            //printf("result[%d] = %s\n", ri, devicenames[ri]);

            hashtable[devicename_hash]++;
            //printf("hashtable[%d] = %d\n", devicename_hash, hashtable[devicename_hash]);
            ri++;
        } else {
            // get the value of the hash; add char value to the result string and add to result
            int num = hashtable[devicename_hash];
            hashtable[devicename_hash]++;

            // concatenate char_num with devicename
            int len = snprintf(NULL, 0, "%d", num);
            len++; // to hold null-terminator
            //printf("len = %d num = %d\n", len, num);
            char num_char[len];
            snprintf(num_char, len, "%d", num);
            strncat(result[ri], devicenames[i], name_len);
            strncat(result[ri], num_char, len);

            //printf("num_char = %s\tresult[%d] = %s\tdevicenames[%d] = %s\n", num_char, ri, result[ri], i, devicenames[i]);

            ri++;

            //printf("unique device name = %s\n", result[ri]);
        }
    }

    return result;
}

int main() {
    int n = 9;
    char *devicenames[] = {"mixer", "toaster", "mixer", "tv", "switch", "tv", "switch", "tv", "tv"};

    printf("<<<<<<<Input>>>>>>>\n");

    for (int i = 0; i < n; i++) {
        printf("%s\n", devicenames[i]);
    }

    printf("<<<<<<<Output>>>>>>>>\n");

    char ** result = deviceNameSystem(devicenames, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    return 0;
}
