
//
//////////////////////////////////////////////////////////////
//  Pawel Gaborek                                           //
//  Programowanie C++                                       //
//  Semestr 3, rok 2, album nr: 45093                       //
//  Prowadzacy, Pan dr inż. Piotr Błaszyński                //
//  LABOLATORIUM_NR-6.cpp                                   //
//  LABOLATORIUM_NR-6------wersja TABLICE                   //
//                                                          //
//  Created by Paweł Gaborek on 15/04/2019.                 //
//  Copyright © 2019 Paweł Gaborek. All rights reserved.    //
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

class matrix
{
    double matrix_number;
public:
    
    /////////////////////////////////////////////////////////////////////////
    ////----------------konstruktory dla klasy matrix--------------------////
    
    matrix(){};
    
    matrix (double number)
    {
        this -> matrix_number = number;
    }
    
    ////-------------------konstruktor dla alokacji pamieci dla macierzy wypelnionej zerami
    matrix(matrix **&create_matrix, int lines_number, int columns_number);
    
    ////-------------------konstruktor dla tworzenia macierzy wczytanej z pliku
    matrix(matrix **&create_matrix);
    
    /////////////////////////////////////////////////////////////////////////
    ////-------------------metody dla klasy matrix-----------------------////
    
    void create_matrix(matrix **&create_matrix, int lines_number, int columns_number);
    
    void change_matrix_number_value(matrix **&matrix_to_return, int line, int column, double new_value);
    
    void return_matrix_number(matrix **&matrix_to_return, int line, int column);
    
    void return_matrix_line(matrix **&matrix_to_return, int line, int column);
    
    void return_matrix_columne(matrix **&matrix_to_return, int line, int column);
    
    void return_matrix() const;
    
    void add_number_to_matrix();
    
    void delete_memory(matrix **&matrix_to_delete, int lines_number, int columns_number);
    
    void write_matrix_to_file(matrix **&matrix_to_write, string matrix_name, int lines_number, int columns_number);
    
    string get_time();
    
    int lines_number();
    
    int columns_number();
    
    void matrix_transpose(matrix **&matrix_to_transpose, matrix **&matrix_basic, int lines_number, int columns_number);
    
    void add_value_to_matrix(matrix **&matrix_value, matrix **&matrix_basic, int lines_number, int columns_number, double value);
    
private:
protected:
};



matrix::matrix(matrix **&create_matrix, int lines_number, int columns_number)
{
    create_matrix=new matrix*[lines_number];
    for(int i=0 ; i<lines_number ; i++)
    {
        create_matrix[i]= new matrix[columns_number];
    }
}

void matrix::create_matrix(matrix **&create_matrix, int lines_number, int columns_number)
{
    for (int i=0 ; i<lines_number ; i++)
    {
        for (int j=0 ; j<columns_number ; j++)
        {
            create_matrix[i][j].matrix_number= 0;
        }
    }
}

void matrix::delete_memory(matrix **&matrix_to_delete, int lines_number, int columns_number)
{
    for (int i=0 ; i<lines_number ; i++)
    {
        delete []matrix_to_delete[i];
    }
    delete []matrix_to_delete;
    matrix_to_delete = nullptr;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class _temp_line
{
public:
    string temp_line_;
    _temp_line(){};
    _temp_line(string temp)
    {
        temp_line_=temp;
    };
    void print_temp_line() const;

private:
protected:
};

void _temp_line::print_temp_line() const
{
    cout << temp_line_ << "\n";
}

void print_temp_(_temp_line *&temp_temp, int lines_numbers)
{
    for (int i=0 ; i<lines_numbers ; i++)
    {
        temp_temp[i].print_temp_line();
        cout << "\n";
    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


matrix::matrix(matrix **&create_matrix)
{
    ////-------------------otwieram plik konwertuje linie pliku do tablicy stringow
    string file_name;
    string templine;
    string templine_2;
    fstream name_file;
    fstream name_file_2;
    int lines_number=0;
    int columns_number=0;
    int j=0;
    file_name = "matrix";
    name_file.open(file_name+=".txt", ios::in);
    if(name_file.good()==false)
    {
        cout << "Przykro mi! Jednak program nie mogl odnalezc pliku o takiej nazwie.";
        cout << "Program teraz utworzy nowy plik o nazwie ''matrix.txt''";
        name_file.open("matrix.txt", ios::out | ios::app);
    }
    
    ////-------------------alokuje pamiec dla wierszy w czytanych z pliku
    _temp_line *temp_matrix=new _temp_line[1000];
    
    ////-------------------okreslam liczbe wierszy czytanej macierzy zakladam ze maksymalna liczba wierszy moze wyniesc 1000
    while(getline(name_file, templine))
    {
        temp_matrix[lines_number]=_temp_line(templine);
        lines_number++;
    }
    
    ////-------------------okreslam liczbe kolumn zakladam ze maksymalna liczba kolumn moze wyniesc 1000
    templine_2=temp_matrix[lines_number].temp_line_;
    for (int j=0 ; j<1000 ; j++)
    {
        if (templine_2[j]==';')
        {
            columns_number++;
        }
    }
    columns_number=columns_number-1;
    ////-------------------wyswietlam dla sprawdzenia zawartosc tablicy obiektow (z pliku)
    //print_temp_(temp_matrix, lines_number);
    
    ///////////////////////------WAZNE !!!--------\\\\\\\\\\\\\\\\\\\\
    ////-------------------alokujee plamiec na macierz z zpliku
    create_matrix=new matrix*[lines_number];
    for(int i=0 ; i<lines_number ; i++)
    {
        create_matrix[i]= new matrix[columns_number];
    }
    
    for (int im=0 ; im<lines_number ; im++)
    {
        string tempstring;
        string temp_value;
        tempstring = temp_matrix[im].temp_line_;
        for (int jl=0 ; jl<columns_number ; jl++)
        {
 
            temp_value=tempstring;
            tempstring.erase(tempstring.find(';'), tempstring.length());
            double temp_double = atof(tempstring.c_str());
            create_matrix[im][jl].matrix_number=temp_double;
            if (j<columns_number)
            {
                temp_value.replace(0,temp_value.find(';')+1, "");
                tempstring=temp_value;
            }
        }
    }
    ////-------------------kasuje pamiec i zamykam plik
    name_file.close();
    delete []temp_matrix;
    temp_matrix = nullptr;
}


string matrix::get_time()
{
    time_t rawtime;
    string time_to_return;
    struct tm * timeinfo;
    char time_table [100];
    
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    strftime (time_table,100,"%X",timeinfo);
    time_to_return=time_table;
    return time_to_return;
}


void matrix::write_matrix_to_file(matrix **&matrix_to_write, string matrix_name, int lines_number, int columns_number)
{
    string time_from_return;
    time_from_return = get_time();
    fstream file_export;
    string file_name=matrix_name;
    string temp_number;
    file_export.open(file_name+"_"+time_from_return+=".txt", ios::out | ios::app);
    for (int i=0 ; i<lines_number ; i++)
    {
        for (int j=0 ; j<columns_number ; j++)
        {
            temp_number=to_string((matrix_to_write)[i][j].matrix_number);
            file_export << (temp_number) << ";";
        }
        file_export << "\n";
    }
    file_export.close();
}


int matrix::lines_number()
{
    return 0;
}

int matrix::columns_number()
{
    return 0;
}


void matrix::return_matrix_number(matrix **&matrix_to_return, int line, int column)
{
    matrix_to_return[line][column].return_matrix();
    cout << "\n";
}

void matrix::return_matrix_line(matrix **&matrix_to_return, int line, int column)
{
    for (int j=0 ; j<line ; j++)
    {
        matrix_to_return[line][j].return_matrix();
        cout << "\n";
    }
}

void matrix::return_matrix_columne(matrix **&matrix_to_return, int line, int column)
{
    for (int j=0 ; j<line ; j++)
    {
        matrix_to_return[j][column].return_matrix();
        cout << "\n";
    }
}

void matrix::return_matrix() const
{
    cout << matrix_number << "\t\t\t";
}


void matrix::change_matrix_number_value(matrix **&matrix_to_return, int line, int column, double new_value)
{
    //int line;
    //int column;
    //double new_value;
    //cout << "Podaj kolumne i wiersz dla wartosci ktora ma byc zmodyfikowana.\n";
    //cout << "Kolumna:\t";
    //cin >> column;
    //cout << "\nWiersz:\t";
    //cin >> line;
    //cout << "\nPodaj nowa wartosc dla elementu macierzy:\t";
    //cin >> new_value;
    matrix_to_return[line][column].matrix_number=new_value;
}

void matrix::matrix_transpose(matrix **&matrix_to_transpose, matrix **&matrix_basic ,int lines_number, int columns_number)
{
    matrix_to_transpose=new matrix*[columns_number];
    for(int i=0 ; i<columns_number ; i++)
    {
        matrix_to_transpose[i]= new matrix[lines_number];
    }
    
    for (int j=0 ; j<columns_number ; j++)
    {
        for (int k=0 ; k<lines_number ; k++)
        {
            matrix_to_transpose[j][k].matrix_number=matrix_basic[k][j].matrix_number;
        }
    }
}


void matrix::add_value_to_matrix(matrix **&matrix_value, matrix **&matrix_basic, int lines_number, int columns_number, double value)
{
    matrix_value=new matrix*[columns_number];
    for(int i=0 ; i<lines_number ; i++)
    {
        matrix_value[i]= new matrix[columns_number];
    }
    
    for (int j=0 ; j<lines_number ; j++)
    {
        for (int k=0 ; k<columns_number ; k++)
        {
            matrix_value[j][k].matrix_number=matrix_basic[j][k].matrix_number+value;
        }
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void return_matrix_(matrix **&matrix_to_print, int lines_number, int columns_number)
{
    for (int i=0 ; i<lines_number ; i++)
    {
        for (int j=0 ; j<columns_number ; j++)
        {
            matrix_to_print[i][j].return_matrix();
        }
        cout << "\n";
    }
}


string get_time()
{
    time_t rawtime;
    string time_to_return;
    struct tm * timeinfo;
    char time_table [100];
    
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    strftime (time_table,100,"%X",timeinfo);
    time_to_return=time_table;
    return time_to_return;
}


void get_memory_(matrix **&create_matrix, int lines_number, int columns_number)
{
    get_memory_(create_matrix, lines_number, columns_number);
}

/////////////////////////////////////////////////////////////////////////
////---------------------funkcja glowna programu---------------------////


int main()
{

    
    int exit = 0;
    char continuation;
    string teamTeam;
    string name;
    string program_begin;
    string program_end;
    
    while(exit==0)
    {
        program_begin=get_time();
        cout << "\nCzas rozpoczecia dzialania programu to: " << program_begin << "\n";
        cout << "\nSuper ! Wlasnie uruchomiles program do labolatorium nr 6 - wersja z TABLICA - na kierunku Informatyka\n";
        cout << "Program umozliwi Ci tworzenie macierzy.\n";
        
        
        ////----------------
        ////----macierz nr 1
        
        ////-------------------tworze wskaznik dla nowej macierzy
        matrix **matrix_number_1;
        
        ////-------------------alokujee pamiec dla macierzy oraz wyswietlam dla sprawdzenia czy zostala prawidlowo utworzona
        matrix matrix_1(matrix_number_1, 4, 3);
        matrix_1.create_matrix(matrix_number_1, 4, 3);
        cout << "\nMacierz nr 1: \n";
        return_matrix_(matrix_number_1, 4, 3);
        matrix_1.write_matrix_to_file(matrix_number_1, "Macierz_1_druga_wersja_zapisu", 4, 3);
        
        ////----------------
        ////----macierz nr 2
        
        ////-------------------tworze wskaznik dla nowej macierzy i obiekt za pomoca konstruktora
        matrix **matrix_number_2;
        matrix matrix_2(matrix_number_2);
        cout << "\nMacierz nr 2 utworzona z pliku: \n";
        return_matrix_(matrix_number_2, 4, 3);
        matrix_2.write_matrix_to_file(matrix_number_2, "Macierz_2_druga_wersja_zapisu", 4, 3);
        ////-------------------modyfikuje wartosci
        matrix_2.change_matrix_number_value(matrix_number_2, 1, 1, 3.2456);
        matrix_2.change_matrix_number_value(matrix_number_2, 0, 1, 18.87);
        matrix_2.change_matrix_number_value(matrix_number_2, 3, 2, 5.7685);
        ////-------------------wyswietlam po modyfikacji
        cout << "Macierz po modyfikacji:\n";
        return_matrix_(matrix_number_2, 4, 3);
        matrix_2.write_matrix_to_file(matrix_number_2, "Macierz_2_po_modyfikacjiu", 4, 3);
        
        ////----------------
        ////----macierz nr 3
        
        ////-------------------tworze wskaznik
        matrix **matrix_number_3;
        matrix matrix_3;
        ////-------------------transponuje macierz z alokacja pamieci
        matrix_3.matrix_transpose(matrix_number_3, matrix_number_2 , 4, 3);
        ////-------------------wyswietlam macierz po transponowaniu
        cout << "Wyswietlam macierz po transponowaniu:\n";
        return_matrix_(matrix_number_3, 3, 4);
        matrix_3.write_matrix_to_file(matrix_number_3, "Macierz_3_po_transponowaniu", 3, 4);
        
        ////----------------
        ////----macierz nr 4
        matrix **matrix_number_4;
        matrix matrix_4;
        ////-------------------dodaje wartosc do macierzy
        matrix_4.add_value_to_matrix(matrix_number_4, matrix_number_3, 3, 4, 5);
        return_matrix_(matrix_number_4, 3, 4);
        matrix_4.write_matrix_to_file(matrix_number_4, "Macierz_2_po_modyfikacjiu", 3, 4);
        
        
        program_end=get_time();
        cout << "\nCzas zakonczenia dzialania programu to: " << program_end << "\n";
        while(1)
        {
            cout << "\nProgram wlasnie zakonczyl swoje dzialanie";
            cout << "Czy chcesz uruchomic program ponownie ??";
            cout << "W przypadku ponownego uruchomienia wpisz litere ''t'', w przerciwnym razie wpisz litere ''n''.";
            cout << "Pamietaj ze wielkosc liter ma zmaczenie.\n\n\n";
            cin >> continuation;
            if(continuation=='t')
            {
                break;
            }
            else
            {
                cout << "Niestety podales bledna litere";
                cout << "Sproboj jeszcze raz";
            }
        }
        cout << "Szkoda ze nie chcesz ponownie uruchomic programu";
        cout << "Moze nastepnycm razem. Powodzenia !!!";
    }
    return 0;
};
