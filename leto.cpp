/******************************************************************************
*                      КАФЕДРА №304 1 КУРС ПРОГИНЖ                            *
*                           Летняя Практика                                   *
*-----------------------------------------------------------------------------*
* Project Type  : Win32 Console Application                                   *
* Project Name  : MaiPractice                                                 *
* File Name     : leto.cpp                                                    *
* Language      : C/C++                                                       *
* Programmer    : Касенко Георгий                                             *
* Modified By   :                                                             *
* Created       : 5/05/26                                                     *
* Last Revision : 26/05/26                                                    *
* Comment(s)    : Работа со структурами и индексной сортировкой               *
******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

typedef struct plane { //сама структура данных, получаемая из строки
    int time;
    char time1[10];
    char mark[20];
    char number[20];
    char city[50];
} plane;
void read(char line[], int& i, char dest[]);  //функция считывания элементов строки
void read_city(char line[], int& i, char dest[]); //отдельная функция для считывания города приьывания, т.к. там может быть несколько слов
int per(char time[]);//перевод времени из AA:BB в количество минут для сортировки
int citymark_len(char city[]);//функция для нахождения количества символов в марке самолета и городе
int str_same(char str1[], char str2[]); //сравнение двух поступающих строк
int string_errors(char line[], int nume, int& flag);//первоначальные ошибки в строке
int time_errors(char time[],int nume,int& flag); // поиск ошибок во времени
int mark_errors(char mark[],int nume,int& flag); //поиск ошибок в марке самолета
int number_errors(char numb[],int nume,int& flag); //поиск ошибки в бортовом номере самолета
int city_errors(char city[],int nume,int& flag);  //поиск ошибки в городе назначения самолета
int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    const char file_name[]="CORRECT3.txt";
    ifstream file(file_name); //открываем поток чтения из файла
    if(!file.is_open()){  //проверка на то,что мы смогли открыть файл
        cout<<"Ошибка, файл не удалось открыть";
        return -1;
    }
    if(file.peek() == -1){ //проверка на то,что не произлошло ошибок во время открытия
        cout<<"Ошибка чтения файла, или он пустой";
        return -1;
    }
    
    char line[200]; //считываемая строка из файла
    plane arr[100]; //массив структур 
    int bub[100];   //массив индексов для сортировки
    int n=0; //количество строк, прошедших проверку
    int n1=0; //количество всех строк
    int len=0; //длина самого длинного названия пункта прибытия самолета
    int mark =0;//длина самого длинного названия марки самолета
    int cur_mark; //длина промежуточного названия пункта прибытия самолета
    int cur_len; //длина промежуточного названия марки самолета
    int flag=0;  //флаг на то, что произошла какая либо ошибка
    int flag2=0; //флаг на то, что в записях есть одно и тоже время прибытия дли одного и того же самолета
    cout<<"Журнал ошибок:\n";
    cout<<"-------\n";
    while (file.getline(line, 200)) {//считываем строку пока это возможно
        int i=0;
        flag2=0;
        if(string_errors(line,n1+1,flag)){; //Проверка на первичные ошибки строки
            read(line,i,arr[n].time1);     //считываем подстроку времени
            if(!(time_errors(arr[n].time1,n1+1,flag))){ //проверка времени на корректность
                n1++;
                continue;
            }
            arr[n].time=per(arr[n].time1); //перевод времени в минуты
            read(line,i,arr[n].mark);   //считываем подстроку марки ЛА
            if(!(mark_errors(arr[n].mark,n1+1,flag))){  //проверка марки ЛА на корректность
                n1++;
                continue;
            }
            read(line,i,arr[n].number);  //считываем подстроку бортового номера
            if(!(number_errors(arr[n].number,n1+1,flag))){ //проверка бортового номера на корректность
                n1++;
                continue;
            }
            read_city(line,i,arr[n].city); //считываем подстроку города
            if(!(city_errors(arr[n].city,n1+1,flag))){ //проверка города на корректность
                n1++;
                continue;
            }

            for(int j=0;j<n;j++){ //поиск логической шибки, если уже есть самолет с таким бортовым номером и временем посадки
                if(str_same(arr[n].number,arr[j].number)){
                    if(str_same(arr[n].mark,arr[j].mark)){
                        if(arr[n].time==arr[j].time){
                            cout<<"Ошибка, самолеты с одинаковыми бортовыми номерами не могут прилетать в одно время, убираем последнее появление этого самолета в таблице, на строке "<<n1+1<<"\n";
                            flag2=1;
                            break;
                        }
                    }
                }
            }
            if(flag2==1){
                flag=1;
                 n1++;
                continue;
            }
            int cur_len=citymark_len(arr[n].city);  //поиск длины марки ЛА
            int cur_mark=citymark_len(arr[n].mark);  //поиск длины города
            if(cur_len>len){
                len=cur_len;
                
            }
            if(cur_mark>mark){
                mark=cur_mark;
            }
            bub[n]=n;//формируем индексный массив
            n++;
        }
        n1++;
    }
    int buff;
    char has_swp;
    for (int i = 0; i < n - 1; i++) {  //сортировка пузыриком, по убыванию
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

    if(flag==0){ //если по итогу не нашли никаких ошибок
        cout<<"Ошибок нет\n";
    }

    

    cout<<"-------\n";
    //Вывод таблицы
    cout << '+'<< setfill('-') << setw(7) << ""<< '+'<< setw(mark+2) << ""<< '+'<< setw(8) << ""<< '+'<< setw(len+2) << ""<< '+'<< setfill(' ')<< '\n';
    for(int i=0;i<n;i++){
        int now_len=citymark_len(arr[bub[i]].city);
        int now_mark=citymark_len(arr[bub[i]].mark);
        cout <<"| "<< arr[bub[i]].time1 << " | "
                <<left<< arr[bub[i]].mark ;
                for(int i=0;i<(mark-now_mark);i++){ //если размер нынешней марки самолета<максимальной, то заполняем разницу пробелами
                    cout<<" ";
                }
                cout<< " | "<< arr[bub[i]].number << " | "<<left<< arr[bub[i]].city ;
                for(int i=0;i<(len-now_len);i++){  //если размер нынешнего места прибытия самолета < максимального, то заполняем разницу пробелами
                    cout<<" ";
                }
                cout<<" |\n";
        }
    cout << '+'<< setfill('-') << setw(7) << ""<< '+'<< setw(mark+2) << ""<< '+'<< setw(8) << ""<< '+'<< setw(len+2) << ""<< '+'<< setfill(' ')<< '\n';


    file.close(); //закрываем поток чтения файла
    
}
void read(char line[], int& i, char dest[]) {
    int j = 0;
    while (line[i] == ' ') i++;    //Убираем лишние пробелы

    while (line[i] != ' ' && line[i] != '\0') {
        dest[j] = line[i];
        j++;
        i++;
    }
    dest[j] = '\0';
}

void read_city(char line[], int& i, char dest[]) {
    int j = 0;
    bool last_was_space = false;
    
    // Пропускаем начальные пробелы
    while (line[i] == ' ') i++;
    
    // Читаем до конца строки
    while (line[i] != '\0' ) {
        if (line[i] == ' ') {
            // Если встретили пробел, но предыдущий символ не был пробелом
            if (!last_was_space) {
                dest[j] = ' ';
                j++;
                last_was_space = true;
            }
        } else {
            dest[j] = line[i];
            j++;
            last_was_space = false;
        }
        i++;
    }

    if (j > 0 && dest[j-1] == ' ') { //Если в конце оказался 1 пробел, то убираем его
        j--;
    }
    
    dest[j] = '\0';
}
int per(char time[]){
    int curr=0;
    curr=(time[0]- '0')*600+(time[1]- '0')*60+(time[3]- '0')*10 + time[4]- '0'; //перевод нашего формата времени в минуты
    return curr;
}
int citymark_len(char city[]){
    int i=0;
    int j=0;
    int cur=0;
    while(city[cur]!='\0'){
        if((city[cur]!=' ')&&(city[cur]!='-')&&((city[cur] < 48 || city[cur] > 57))){ //русские символы занимают 2 байта, поэтому они считаются отдельно
            i++;    
            cur++;
        }
        else{
            j++;
            cur++;
        }
        
    }
    return (i/2)+j;
}
int str_same(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;  // не равен один символ => строки не равны
        }
        i++;
    }
    return 1; 
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
    if(j==0){ //проверка строки на пустоту
        cout<<"Ошибка в строке: "<<nume<<", она пустая \n";
        flag =1;
        return 0;
    }
    if(j<16){ //минимальное количество байт, для символов: время - 5 , марка -1, номер -6, город -1
        cout<<"Ошибка в строке: "<<nume<<", недостаточно информации \n";
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
    if(i!=5){ //более строгая проверка формата времени, ваши комментарии в общей иформации и для некоторых людей расходятся
        cout<<"Ошибка, некорректное число символов во времени в строке "<<nume<<" , пропускаем её\n";
        flag=1;
        return 0;
    }
    if(time[2]!=':'){ //более строгая проверка формата времени, ваши комментарии в общей иформации и для некоторых людей расходятся
        cout<<"Ошибка, на месте 3 символа во времени должно быть ':' в строке "<<nume<<" , пропускаем её\n";
        flag=1;
        return 0;
    }
    for(int j=0;j<5;j++){
        if(time[j]!=':'){
            if(!(48 <= time[j] && time[j] <= 57)){  //проверка на то,что символы - цифры
                cout<<"Ошибка, в символе времени "<<j+1<<" должна быть цифра, в строке "<<nume<<" , пропускаем\n";
                flag=1;
                return 0;
            }
        }
    }
    if(((time[0]- '0')>2)||((time[3]- '0')>5)||(((time[0]- '0')>1)&&((time[1]- '0')>3))){ //отдельные случаи неправильной записи времени
        cout<<"Ошибка, не правильный формат времени в строке "<<nume<<" ,пропускаем её\n";
        flag=1;
        return 0;
    }
    return 1;
}
int mark_errors(char mark[],int nume,int& flag){
    //Регулярное выражения, сначала обязательно русский символ, далее возможны символы, цифры и тире
    regex pattern(R"(^[\xD0\xD1][\x80-\xBF]([\xD0\xD1][\x80-\xBF]|[0-9\-])*$)");
    if (regex_match(mark, pattern)){
        return 1;
    }
    else{
         cout<<"Ошибка, не правильный формат марки самолета в строке "<<nume<<" ,пропускаем её\n";
         flag=1;
    }
    return 0;
}
int number_errors(char numb[],int nume,int& flag){
    if(!((numb[0] == -48) && (numb[1] == -111))){  // Первая буква обязяательно должна быть Б
        cout<<"Ошибка, не правильный формат бортового номера самолета, первая буква - Б, в строке "<<nume<<" ,пропускаем её\n";
        flag = 1;
        return 0;
    }
    if(numb[2]!='-'){ //после Б всегда -
        cout<<"Ошибка, не правильный формат бортового номера самолета, второй символ: ' - ' , в строке "<<nume<<" ,пропускаем её\n";
        flag = 1;
        return 0;        
    }
    for(int j=0;j<4;j++){ //Остальные символы должны быть цифрами

        if(!(48 <= numb[j+3] && numb[j+3] <= 57)){
            cout<<"Ошибка, в символе бортового номера "<<j+3<<" должна быть цифра, в строке "<<nume<<" , пропускаем её\n";
            flag=1;
            return 0;
        }
    }
    if(numb[7]!='\0'){
        cout<<"Ошибка, не правильный формат бортового номера самолета, слишком много символов, в строке "<<nume<<" ,пропускаем её\n";
        flag = 1;
        return 0;  
    }
    return 1;
}
int city_errors(char city[],int nume,int& flag){
    //Регулярное выражения, сначала обязательно русский символ, далее возможны пробелы и тире
    regex pattern(R"(^[\xD0\xD1][\x80-\xBF]([\xD0\xD1][\x80-\xBF]|[ -])*$)");
    if (regex_match(city, pattern)){
        return 1;
    }
    else{
         cout<<"Ошибка, не правильный формат города прилета в строке "<<nume<<" ,пропускаем её\n";
         flag=1;
    }
    return 0;
}