#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct plane {  //Структура данных прилета самолета
    int time;
    char time1[10];
    char mark[20];
    char number[20];
    char city[50];
} plane;

void read(char line[], int& i, char dest[]) {  //Чтение следующего набоа символов в строке до пробела или ее конца
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
int per(char time[]){    //перевод времени в минуты для будущего сравнения
    int curr=0;
    curr=(time[0]- '0')*600+(time[1]- '0')*60+(time[3]- '0')*10 + time[4]- '0';
    return curr;
}
int city_len(char city[]){  //определение длины слова названия пункта отправления, для формирования длины таблицы вывода
    int i=0;
    while(city[i]!='\0'){
        i++;
    }
    return i;
}


int string_errors(char line[], int nume, int& flag){ //Провека на ошибки в самой строке
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
int time_errors(char time[],int nume,int& flag){  //Проверка на ошибки во времени

    int i=0;
    while(time[i]!='\0'){
        i++;
    }
    if(i!=5){
        cout<<"Ошибка, некорректное число знаков во времени в строке "<<nume<<" , мы её пропустили\n";
        flag=1;
        return 0;
    }
    for(int j=0;j<5;j++){
        if(time[j]!=':'){
            if(!(48 <= time[j] && time[j] <= 57)){
                cout<<"Ошибка, некорректный символ на "<<j+1<<" месте времени, должна быть цифра, в строке "<<nume<<" , мы её пропустили\n";
                flag=1;
                return 0;
            }
        }
    }
    if(((time[0]- '0')>2)||((time[3]- '0')>5)||(((time[0]- '0')>1)&&((time[1]- '0')>3))){
        cout<<"Ошибка, некорректное значение времени в строке "<<nume<<" ,мы её пропустили\n";
        flag=1;
        return 0;
    }
    return 1;
}
int mark_errors(char mark[],int nume,int& flag){ //Проверка на ошибки в марке ЛА

    int i=0;
    while(mark[i]!='\0'){
        i++;
    }
    if(i!=7){
        cout<<"Ошибка, некорректное число знаков марки ЛА  / Некорректная форма записи макрки ЛА, в строке "<<nume<<" , мы её пропустили\n";
        flag=1;
        return 0;
    }
    if (!(mark[0] >= -64 && mark[0] <= -1)) {
        cout << "Ошибка, некорректный символ на 1 месте марки ЛА, должна быть русская буква, в строке "
            << nume << " , мы её пропустили\n";
        flag = 1;
        return 0;
    }

    if (!(mark[1] >= -64 && mark[1] <= -1)) {
        cout << "Ошибка, некорректный символ на 2 месте марки ЛА, должна быть русская буква, в строке "
            << nume << " , мы её пропустили\n";
        flag = 1;
        return 0;
    }

    if (mark[2] != '-') {
        cout << "Ошибка, некорректный символ на 3 месте марки ЛА, должно быть '-', в строке "
            << nume << " , мы её пропустили\n";
        flag = 1;
        return 0;
    }

    for (int j = 0; j < 3; j++) {
        if (!(mark[3 + j] >= 48 && mark[3 + j] <= 57)) {
            cout << "Ошибка, некорректный символ на "
                << (3 + j + 1)
                << " месте марки ЛА, должна быть цифра, в строке "
                << nume << " , мы её пропустили\n";

            flag = 1;
            return 0;
        }
    }

    if (!(mark[6] >= -64 && mark[6] <= -1)) {
        cout << "Ошибка, некорректный символ на 7 месте марки ЛА, должна быть русская буква, в строке "
            << nume << " , мы её пропустили\n";

        flag = 1;
        return 0;
    }

    return 1;
}
int number_errors(char numb[],int nume,int& flag){ //Проверка на ошибки бортового номера

    int i=0;
    while(numb[i]!='\0'){
        i++;
    }
    if(i!=6){
        cout<<"Ошибка, некорректное число знаков бортового номера  / Некорректная форма записи бортового номера, в строке "<<nume<<" , мы её пропустили\n";
        flag=1;
        return 0;
    }
    if (!(numb[0] >= -64 && numb[0] <= -1)) {
        cout << "Ошибка, некорректный символ на 1 месте бортового номера, должна быть русская буква, в строке "
            << nume << " , мы её пропустили\n";
        flag = 1;
        return 0;
    }


    if (numb[1] != '-') {
        cout << "Ошибка, некорректный символ на 2 месте бортового номера, должно быть '-', в строке "
            << nume << " , мы её пропустили\n";
        flag = 1;
        return 0;
    }

    for (int j = 0; j < 4; j++) {
        if (!(numb[2 + j] >= 48 && numb[3 + j] <= 57)) {
            cout << "Ошибка, некорректный символ на "
                << (3 + j + 1)
                << " месте бортового номера, должна быть цифра, в строке "
                << nume << " , мы её пропустили\n";

            flag = 1;
            return 0;
        }
    }

    return 1;
}
int city_errors(char city[],int nume,int& flag){ //Проверка на ошибки в пункте отправления
    int i=0;
    while(city[i]!='\0'){
        i++;
    }
    for (int j = 0; j < i; j++) {
        if (!(city[j] >= -64 && city[j] <= -1)) {
            cout << "Ошибка, некорректный символ на "
                << (3 + j + 1)
                << " месте пункта отправления, должна быть русская буква, в строке "
                << nume << " , мы её пропустили\n";

            flag = 1;
            return 0;
        }
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

    char line[200];  //считываемая строка
    plane arr[100];  //массив структур
    int bub[100];    //индексный массив
    int n=0;
    int n1=0;
    int len=0;
    int cur_len;
    int flag=0;
    cout<<"Журнал ошибок:\n";
    cout<<"-------\n";
    while (file.getline(line, 200)) { //считываем строки пока это возможно
        int i=0;
        if(string_errors(line,n1+1,flag)){;
            read(line,i,arr[n].time1);  //считваем время из строки
            if(!(time_errors(arr[n].time1,n1+1,flag))){//Если нашли ошибку, фиксируем ее и пропускаем строку
                n1++;
                continue;
            }
            arr[n].time=per(arr[n].time1); //Перевод времени в минуты
            read(line,i,arr[n].mark); //считваем марку ЛА из строки
            if(!(mark_errors(arr[n].mark,n1+1,flag))){ //Если нашли ошибку, фиксируем ее и пропускаем строку
                n1++;   
                continue;
            }
            read(line,i,arr[n].number); //считваем бортовой номер из строки
            if(!(number_errors(arr[n].number,n1+1,flag))){ //Если нашли ошибку, фиксируем ее и пропускаем строку
                n1++;
                continue;
            }
            read(line,i,arr[n].city); //считваем название пункта отправления из строки
            if(!(city_errors(arr[n].city,n1+1,flag))){ //Если нашли ошибку, фиксируем ее и пропускаем строку
                n1++;
                continue;
            }
            int cur_len=city_len(arr[n].city); //находим длину названия населенного пункта
            if(cur_len>len){
                len=cur_len;     //ищем и сохраяем максимальную длину
            }
            bub[n]=n;   //Формируем индексный массив
            n++;
        }
        n1++;
    }
    int buff; 
    char has_swp; 
    for (int i = 0; i < n - 1; i++) {  //сортировка методом «пузырька» в порядке убывания времени посадки; 
        has_swp = 0; 
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[bub[j]].time < arr[bub[j+1]].time) {
                has_swp = 1; 
                buff = bub[j];
                bub[j] = bub[j + 1];
                bub[j + 1] = buff;
            }
        }

        if (!has_swp) break;
    }

    if(flag==0){//выводим, если нет ошибок
        cout<<"Ошибок нет\n";
    }

    


    //Вывод  таблицы
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

