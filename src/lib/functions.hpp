#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

/**
 * @brief Tipe data untuk suatu operasi
 * @param res: Hasil
 * @param op: symbol operator
 */
typedef struct{
    double res;
    char op;    
} Operasi;

/**
 * @brief Tipe data untuk arrangement kartu
 * @param card1: Kartu posisi pertama
 * @param card2: Kartu posisi kedua
 * @param card3: Kartu posisi ketiga
 * @param card4: Kartu posisi keempat
 */
typedef struct {
    int card1;
    int card2;
    int card3;
    int card4;
} Cards;

/**
 * @brief Tipe data untuk menyimpan address fungsi operator
 */
typedef Operasi (*functionPtr) (double, double);

// FUNGSI / PROSEDUR
/**
 * @brief Get the Input object
 * @brief Input bisa diberikan oleh user atau auto-generated
 * @return int* 
 */
void getInput(int input[]);

/**
 * @brief Get the Solution object
 * @brief Mencari semua solusi yang mungkin
 * @param input: array of integer 
 * @return string* 
 */
void getSolution(int input[], vector<string> *output);
/**
 * @brief Mencari kombinasi tanda kurung yang memenuhi
 * 
 * @param arrangement: Susunan Kartu 
 * @param funcs: Kombinasi operator 
 * @param output 
 */
void solveParentheses(Cards arrangement, functionPtr funcs[], vector<string> *output);
/**
 * @brief Mencetak Solusi game 24
 * @param solution: Vektor Solusi  
 */
void printSolution(vector<string> solution);
/**
 * @brief Menyimpan file solusi
 * @param namaFile 
 * @param solutions 
 */
void saveFile(string namaFile, vector<string> solutions);
/**
 * @brief Mengubah Kartu dari representasi string menjadi representasi integer
 * @param inputString 
 * @param inputInt 
 */
void cardStringToInt(string inputString[], int inputInt[]);
/**
 * @brief Mengubah kartu dari representasi integer menjadi string
 * @param inputInt 
 * @param inputString 
 */
void cardIntToString(int inputInt[], string inputString[]);
/**
 * @brief Menegcek apakah input(manual) valid
 * @param inputLines: baris input 
 * @return true jika valid
 * @return false jika tidak valid
 */
bool isValidInput(string inputLines);
/**
 * @brief Mengecek apakah kartu termasuk kartu yang valid
 * @param stringCard: Kartu dengan representasi string
 * @return true jika valid
 * @return false jika tidak valid
 */
bool isValidCard(string stringCard);

/**
 * @brief Mengecek apakah kartu sudah terdapat di dalam list
 * @param tempCard 
 * @param list 
 * @return true jika sudah terdapat
 * @return false jika tidak terdapat
 */
bool isExistCards(Cards tempCard, vector<Cards> list);
/**
 * @brief Menegcek apakah dua buah kartu sama
 * @param cards1 
 * @param cards2 
 * @return true jika sama
 * @return false jika berbeda
 */
bool isSameCards(Cards cards1, Cards cards2);
/**
 * @brief Operasi penjumlahan
 * @param a 
 * @param b 
 * @return Operasi 
 */
Operasi tambah(double a, double b);
/**
 * @brief Operasi pengurangan
 * @param a 
 * @param b 
 * @return Operasi 
 */
Operasi kurang(double a, double b);
/**
 * @brief Operasi perkalian
 * @param a 
 * @param b 
 * @return Operasi 
 */
Operasi kali(double a, double b);
/**
 * @brief Operasi pembagian
 * @param a 
 * @param b 
 * @return Operasi 
 */
Operasi bagi(double a, double b);
#endif 
