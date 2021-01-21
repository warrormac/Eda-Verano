// CMakeProject7.cpp : Defines the entry point for the application.
//

#include "CMakeProject7.h"
#include <cmath>
#include <vector>
#include <time.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;



int Mat(vector<vector<int>>& vec, int row, int col)
{


    srand(time(NULL));

    int num = 1 + rand() % (20000 - 1);


    for (int i = 0; i < row; i++) {

        vector<int> v1;

        for (int j = 0; j < col; j++) {
            v1.push_back(num);
            num = 1 + rand() % (10000 - 1);
        }

 
        vec.push_back(v1);
    }

    return 0;

}




void ecli(vector<vector<int>>& vect1, int row, int col)
{
    int suma = 0;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = i + 1; j < row; j++)
        {
            for (size_t k = 0; k < col; k++)
                suma += pow(vect1[i][k] - vect1[j][k], 2);

        }
    }
}


int main() {


    vector<vector<int>> vect1;
    int a = 1;
    while (a == 1)
    {
        int row = 0, col = 0;
        cout << "insert numer of rows: ";
        cin >> row;
        cout << "insert number of col: ";
        cin >> col;


        Mat(vect1, row, col);





        auto begin = chrono::high_resolution_clock::now();

        ecli(vect1, row, col);

        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
        cout << ms << "ms" << endl;
        cin >> a;
    }

    /*
    for (int i = 0; i < vect1.size(); i++) {
             for (int j = 0; j < vect1[i].size(); j++)
                 cout << vect1[i][j] << " ";
             cout << endl;
         }
         cout << "\n";
         cout << "\n";
         cout << "\n";
         for (int i = 0; i < vect2.size(); i++) {
             for (int j = 0; j < vect2[i].size(); j++)
                 cout << vect2[i][j] << " ";
             cout << endl;
         }
     */


}
