#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct plane {  //все хорошо
    int time;
    char time1[10];
    char mark[20];
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
int city_len(char city[]){
    int i=0;
    while(city[i]!='\0'){
        i++;
    }
    return i;
}


int string_errors(char line[], int nume, int& flag){
    int i=0;
    int j=0;
    while ((line[i] != '\0')&&(line[i] != '\n')) {
        if(line[i]!=' '){
            j++;
        }
        i++;
    }  
    if(j==0){
        cout<<"Ошибка, строка "<<nume<<" пустая, мы её пропустили \n";
        flag =1;
        return 0;
    }
    else if(j<20){

        cout<<"Ошибка, в строке "<<nume<<" не хватает данных, мы её пропустили\n";
        flag =1;
        return 0;
    }
    return 1;
}
int time_errors(char time[],int nume,int& flag){
    int i=0;
    while(time[i]!='\0'){
        i++;
    }
    if(i!=5){
        cout<<"Ошибка, некорректное число знаков во времени в строке "<<nume<<" , мы её пропустили\n";
        flag=1;
        return 0;
    }
    else if(((time[0]- '0')>2)||((time[3]- '0')>5)){
        cout<<"Ошибка, некорректное значение времени в строке "<<nume<<" ,мы её пропустили\n";
        flag=1;
        return 0;
    }
    return 1;
}
int main(){
    setlocale(LC_ALL, "Russian");
    ifstream file("leto.txt");

    if(!file.is_open()){
        cout<<"Ошибка, файл не найден";
        return -1;
    }
    if((file.eof())||(file.fail())){
        cout<<"Ошибка, файл пустой";
        return -1;
    }

    char line[200];
    plane arr[100];
    int bub[100];
    int n=0;
    int n1=0;
    int len=0;
    int cur_len;
    int flag=0;
    cout<<"Журнал ошибок:\n";
    cout<<"-------\n";
    while (file.getline(line, 200)) {
        int i=0;
        if(string_errors(line,n1+1,flag)){;
            read(line,i,arr[n].time1);
            if(!(time_errors(arr[n].time1,n1+1,flag))){
                continue;
            }
            arr[n].time=per(arr[n].time1);
            read(line,i,arr[n].mark);
            read(line,i,arr[n].number);
            read(line,i,arr[n].city);
            int cur_len=city_len(arr[n].city);
            if(cur_len>len){
                len=cur_len;
            }
            bub[n]=n;
            n++;
        }
        n1++;
    }
    int buff; // все орошо7
    char has_swp; // все орошо7

    for (int i = 0; i < n - 1; i++) {
        has_swp = 0; // все орошо7
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[bub[j]].time < arr[bub[j+1]].time) {
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

    if(flag==0){
        cout<<"Ошибок нет\n";
    }

    



    cout<<"-------\n";
    cout << '+'<< setfill('-') << setw(7) << ""<< '+'<< setw(9) << ""<< '+'<< setw(8) << ""<< '+'<< setw(len+2) << ""<< '+'<< setfill(' ')<< '\n';
    for(int i=0;i<n;i++){
    cout <<"| "<< arr[bub[i]].time1 << " | "
              << arr[bub[i]].mark << " | "
              << arr[bub[i]].number << " | "
              <<left<< setfill(' ') <<setw(len)<< arr[bub[i]].city <<" |\n";
    }
    cout << '+'<< setfill('-') << setw(7) << ""<< '+'<< setw(9) << ""<< '+'<< setw(8) << ""<< '+'<< setw(len+2) << ""<< '+'<< setfill(' ')<< '\n';
    file.close();
    
}

