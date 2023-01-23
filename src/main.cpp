#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "lib/functions.hpp"

using namespace std;


// ALGORITMA
int main(){
    // Setup
    int input[4];
    clock_t time_start, time_end;
    vector<string> solutions;

    // START
    cout << endl<< "==== MAKE IT 24 ====" << endl << endl;

    getInput(input);
    time_start = clock(); 
    getSolution(input,&solutions); 
    time_end = clock(); 
    double duration = (time_end-time_start)/(double)CLOCKS_PER_SEC;

    // CLOSING
    if (solutions.size()>0){ // Jika terdapat solusi
        // Menampilkan banyak solusi dan kumpulan solusinya
        char isSave;
        cout<<"Banyak Solusi: "<<solutions.size()<<endl;
        cout<<"Solusi: "<<endl;
        printSolution(solutions);
        cout<< endl;

        // Validasi opsi save solution
        do{
            cout<<"Apakah ingin menyimpan solusi? (y/n): "<< endl;
            cin>>isSave;
        } while (isSave!='y' && isSave!='n');

        // Jika user memilih save file
        if (isSave=='y'){
            string namaFile;
            cout<<"Masukkan Nama File Solusi: "<< endl;
            cin>>namaFile;
            saveFile(namaFile,solutions);
        }
    } else { // Jika tidak terdapat solusi
        cout<<"Tidak Ada Solusi"<<endl;
    }
    cout<<endl<<"Execution Time: "<<duration<<" s"<<endl;
    
    return 0;
}
