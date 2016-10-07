#ifndef GRID_H
#define GRID_H
#include <random>
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;



const int ON = 1;
const int OFF = 0;
const int SIZE = 10;

class Grid {

    int** tmp;
    int** prev;

public:

    int count;
    int** states;
    int nb_it;


    Grid(ifstream &s) : Grid(){
        /*
         * TODO
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                states[i][j] << s.;
                if(states[i][j]) count++;
            }
        }
        */
    }

    Grid(const Grid& g) :
        Grid()
    {
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                states[i][j] = g.states[i][j];
                tmp[i][j] = g.tmp[i][j];
                prev[i][j] = g.prev[i][j];
            }

        }
        nb_it = g.nb_it;
        count = g.count;
    }

    Grid() :
        nb_it(0),
        count(0)
    {

        states = new int*[SIZE];
        tmp = new int*[SIZE];
        prev = new int*[SIZE];
        for(int i = 0 ; i < SIZE ; i++){
            states[i] = new int[SIZE];
            tmp[i] = new int[SIZE];
            prev[i] = new int[SIZE];
            for(int j = 0 ; j < SIZE; j++){
                states[i][j] = OFF;
                prev[i][j] = OFF;
            }
        }

    }

    void clear(){
        if(count > 0){
            for(int i = 0 ; i < SIZE ; i++){
                for(int j = 0 ; j < SIZE ; j++){
                    states[i][j] = OFF;
                    prev[i][j] = OFF;
                }
            }
            count = 0;
        }
        nb_it = 0;
    }

    void init_random(){
        srand(time(NULL));
            for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                states[i][j] = rand()%2;
                if(states[i][j]) count++;
            }
        }
    }


    void init_random(int nb){
        int x, y;
        clear();
        while(count < nb){

           x = rand()%SIZE;
           y = rand()%SIZE;

           if( states[x][y] == OFF){
               states[x][y] = ON;
               count++;
           }
        }
    }

    bool clean()const{ return count == 0;}

    bool stable()const{
        for(int i = 0 ; i < SIZE ; i++)
            for(int j = 0 ; j < SIZE; j++)
                if(states[i][j] != prev[i][j]) return false;
        return true;

    }



    void print_grid(ofstream &file) const{
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                file << states[i][j] << " ";
            }
            file << endl;
        }
    }

    void print_grid() const{
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                cout << states[i][j] << " ";
            }
            cout << endl;
        }
    }

    int check_neighbours(const int i, const int j)const{
        int nb = - states[i][j];
        int y, x;

        x= (i==0) ? SIZE-1 : i-1;
        for(int a = 0 ; a < 3; x= (x+1)%SIZE){

            y= (j==0) ? SIZE-1 : j-1;

            for(int b = 0; b < 3; y =(y+1)%SIZE){

                nb += states[x][y];

                b++;
            }
            a++;
        }
        return (nb>3 || nb<2) ? OFF : (nb==3) ? ON : states[i][j];
    }

    void next_step(){
        count = 0;
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                tmp[i][j] = check_neighbours(i,j);
                if(tmp[i][j] == ON) count++;
            }
        }
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE; j++){
                prev[i][j] = states[i][j];
                states[i][j] = tmp[i][j];
            }
        }
        nb_it++;
    }
};

#endif // GRID_H
