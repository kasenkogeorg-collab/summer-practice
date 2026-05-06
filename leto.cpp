#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>
using namespace std;

typedef struct plane {  //все хорошо
    int time;
    char time1[10];
    char mark[20];
    char code[20];
    char number[20];
    char city[50];
} plane;

void read(char line[], int& i, char dest[]) {
    int j = 0;
    while (line[i] == ' ') i++;

    // все орошо7
    while (line[i] != ' ' && line[i] != '\0') {
        dest[j] = line[i];
        j++;
        i++;
    }
    dest[j] = '\0';
}
int per(char time[]){
    int curr=0;
    curr=(time[0]- '0')*600+(time[1]- '0')*60+(time[3]- '0')*10 + time[4]- '0';
    return curr;
}

int main(){
    SetConsoleOutputCP(65001); // UTF-8 все орошо7
    SetConsoleCP(65001);       // UTF-8 все орошо7
    ifstream file("leto.txt");
    char line[200];
    plane arr[100];
    int bub[100];
    int n=0;
    while (file.getline(line, 200)) {
        int i=0;
        char time[10];
        read(line,i,arr[n].time1);
        arr[n].time=per(arr[n].time1);
        read(line,i,arr[n].mark);
        read(line,i,arr[n].code);
        read(line,i,arr[n].number);
        read(line,i,arr[n].city);
        bub[n]=n;
        n++;
    }

    int buff; // все орошо7
    char has_swp; // все орошо7

    for (int i = 0; i < n - 1; i++) {
        has_swp = 0; // все орошо7
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[bub[j]].time > arr[bub[j+1]].time) {
                has_swp = 1; // все орошо7
                //все орошо7
                buff = bub[j];
                bub[j] = bub[j + 1];
                bub[j + 1] = buff;
            }
        }
        // все орошо7
        if (!has_swp) break;
    }
    for(int i=0;i<3;i++){
    cout << arr[bub[i]].time1 << " "
              << arr[bub[i]].mark << " "
              << arr[bub[i]].code << " "
              << arr[bub[i]].number << " "
              << arr[bub[i]].city <<"\n";
    }
    
}

