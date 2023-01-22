#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>

using namespace std;
typedef struct{
    double res;
    char op;
} Operasi;

typedef struct {
    int card1;
    int card2;
    int card3;
    int card4;
} Cards;

typedef Operasi (*functionPtr) (int, int);

// KAMUS
/**
 * @brief Get the Input object
 * @brief Input bisa diberikan oleh user atau auto-generated
 * @return int* 
 */
void getInput(int* input);

/**
 * @brief Get the Solution object
 * @brief Mencari semua solusi yang mungkin
 * @param input: array of integer 
 * @return string* 
 */
void getSolution(int input[], vector<string> *output);

void solveParentheses(Cards arrangement, functionPtr funcs[], vector<string> *output);

void printSolution(vector<string> solution);

bool isExistCards(Cards tempCard, vector<Cards> list);

bool isSameCards(Cards cards1, Cards cards2);


// ALGORITMA
int main(){
    // int arr[3] = {1,2,3};
    // string* testing;
    // testing = getSolution(arr);
    // cout<<testing[0]<<" "<< testing[1]<<endl;
    int input[4] = {6,6,6,6};
    vector<string> solutions;
    // getInput(input);
    getSolution(input,&solutions);
    cout<<"Banyak Solusi:"<<solutions.size()<<endl;
    printSolution(solutions);
    return 0;
}

Operasi tambah(int a, int b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '+';
    ops.res = a+b; 
    return ops;
}
Operasi kurang(int a, int b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '-';
    ops.res = a-b; 
    return ops;
}
Operasi kali(int a, int b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '*';
    ops.res = a*b; 
    return ops;
}
Operasi bagi(int a, int b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '/';
    ops.res = (double)a/(double)b; 
    return ops;
}

// REALISASI FUNGSI/PROSEDUR
void getInput(int * input){
    // KAMUS LOKAL
    int inputType, card1, card2, card3, card4;
    char * tempInput;

    // ALGORITMA

    // Validasi inputType
    do{
        cout<<"Tipe Input"<< endl;
        cout<<"1. Manual"<< endl;
        cout<<"2. Auto-Generated"<< endl;
        cout<<"Masukkan Jenis Input yang digunakan(1/2): ";
        cin>>inputType;
    } while (inputType!=1 && inputType!=2);
    // inputType sudah Valid

    if (inputType == 1){ // Manual


    } else { // Auto-Generated

    }
}

void getSolution(int input[], vector<string> *output){
    // KAMUS LOKAL
    int i,j,k,l,m,n,o, nSolution, nPermutation;
    vector<Cards> allPermutation;
    // ALGORITMA


    functionPtr operators[4] = {tambah, kurang, kali, bagi};

    for (i=0;i<=3;i++){
        for (j=0; j<=3; j++){
            for (k=0; k<=3; k++){
                for (l=0; l<=3; l++){
                    for (m=0; m<=3; m++){
                        for (n=0; n<=3; n++){
                            for (o=0; o<=3; o++){
                                Cards tempCard;
                                functionPtr funcs[3] = {operators[m], operators[n], operators[o]};
                                tempCard.card1 = input[i];
                                tempCard.card2 = input[j];
                                tempCard.card3 = input[k];
                                tempCard.card4 = input[l];

                                // Jika Belum Ada
                                if (!isExistCards(tempCard, allPermutation)){
                                    allPermutation.push_back(tempCard);
                                    // Check for the solution
                                    solveParentheses(tempCard,funcs,output);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool isSameCards(Cards cards1, Cards cards2)
{
    // KAMUS LOKAL
    // ALGORITMA
    return (cards1.card1 == cards2.card1) && (cards1.card2 == cards2.card2) && (cards1.card3 == cards2.card3) && (cards1.card4 == cards2.card4);
}

bool isExistCards(Cards tempCard, vector<Cards> list)
{
    // KAMUS LOKAL
    bool exist;

    // ALGORITMA
    auto idx = list.begin();
    auto ends = list.end();
    exist = false;
    while ((idx != ends) &&  !exist){
        if (isSameCards(tempCard, *idx)){
            exist = true;
        } else {
            idx++;
        }
    }
    return exist;
}

void solveParentheses(Cards values, functionPtr funcs[], vector<string> *output)
{
    // KAMUS LOKAL
    Operasi ops1, ops2, ops3;
    int val1,val2,val3,val4;
    functionPtr op1,op2,op3;
    double finalRes;
    // ALGORITMA
    // Setup

    val1 = values.card1;
    val2 = values.card2;
    val3 = values.card3;
    val4 = values.card4;

    op1 = funcs[0];
    op2 = funcs[1];
    op3 = funcs[2];

    // val1 op1 (val2 op2 val3) op3 val4 => a+(b+c)+d
    // ops1 = op2(val2, val3);
    // if ((op3 == kali || op3 == bagi) && (op2 == tambah || op2 == kurang)){
    //     ops2 = op3(ops1.res, val4);
    //     ops3 = op1(val1,ops2.res); 
    //     finalRes = ops3.res;
    // } else {
    //     ops3 = op1(val1, ops1.res);
    //     ops2 = op3(ops3.res,val4); 
    //     finalRes = ops2.res;
    // }

    // if (finalRes == 24){
    //     output->push_back("("+to_string(val1) + ops3.op + to_string(val2) + ops1.op  + to_string(val3) + ")" + ops3.op + to_string(val4));
    // }

    // val1 op1 val2 op2 (val3 op3 val4) => a+b+(c+d)
    
    // ops1 = op3(val3, val4);
    // if ((op2 == kali || op2 == bagi) && (op1 == tambah || op1 == kurang)){
    //     ops2 = op2(val2,ops1.res);
    //     ops3 = op1(val1,ops2.res); 
    //     finalRes = ops3.res;
    // } else {
    //     ops3 = op1(val1, val2);
    //     ops2 = op2(ops3.res,ops1.res); 
    //     finalRes = ops2.res;
    // }

    // if (finalRes == 24){
    //     output->push_back("("+to_string(val1) + ops3.op + to_string(val2) + ops2.op  + to_string(val3) + ")" + ops1.op + to_string(val4));
    // }
    // (val1 op1 val2 op2 val3) op3 val4 => (a+b+c)+d
    
    // if ((op2 == kali || op2 == bagi) && (op1 == tambah || op1 == kurang)){
    //     ops1 = op2(val2, val3);
    //     ops2 = op1(val1,ops1.res);
    //     ops3 = op3(ops2.res, val4);  
    // } else {
    //     ops2 = op1(val1, val2);
    //     ops1 = op2(ops2.res, val3);
    //     ops3 = op3(ops2.res, val4); 
    // }
    // finalRes = ops3.res;

    // if (finalRes == 24){
    //     output->push_back("("+to_string(val1) + ops2.op + to_string(val2) + ops1.op  + to_string(val3) + ")" + ops3.op + to_string(val4));
    // }
    // val1 op1 (val2 op2 val3 op3 val4) => a+(b+c+d)
    // if ((op3 == kali || op3 == bagi) && (op2 == tambah || op2 == kurang)){
    //     ops1 = op3(val3, val4);
    //     ops2 = op2(val2,ops1.res);
    //     ops3 = op1(val1,ops2.res); 
    // } else {
    //     ops2 = op2(val2, val3);
    //     ops1 = op3(ops2.res, val4);
    //     ops3 = op1(val1,ops1.res); 
    // }
    // finalRes = ops3.res;

    // if (finalRes == 24){
    //     output->push_back(to_string(val1) + ops3.op +"(" + to_string(val2) + ops2.op  + to_string(val3) + ops1.op + to_string(val4) + ")");
    // }
    // (val1 op1 val2) op2 val3 op3 val4 => (a+b)+c+d
    // ops1 = op1(val1,val2);
    // if ((op3 == kali || op3 == bagi) && (op2 == tambah || op2 == kurang)){
    //     ops2 = op3(val3, val4);
    //     ops3 = op2(ops1.res, ops2.res);
    //     finalRes = ops3.res;
    // } else {
    //     ops3 = op2(ops1.res, val3);
    //     ops2 = op3(ops3.res, val4);
    //     finalRes = ops2.res;
    // }
    // if (finalRes == 24){
    //     output->push_back("(" + to_string(val1) + ops1.op + to_string(val2) +") " + ops3.op  + to_string(val3) + ops2.op + to_string(val4));
    // }



    // (val1 op1 val2) op2 (val3 op3 val4) => (a+b) + (c+d)
    ops1 = op1(val1,val2);
    ops2 = op3(val3,val4);
    ops3 = op2(ops1.res,ops2.res);
    cout<< ops3.res<<endl;
    if (ops3.res == 24){
        output->push_back("(" + to_string(val1) + ops1.op + to_string(val2) +") " + ops3.op + "(" + to_string(val3) + ops3.op + to_string(val4) + ")" );
    }

    // ((val1 op1 val2) op2 val3) op3 val4 => ((a+b) + c) + d 
    ops2 = op2(ops1.res, val3);
    ops3 = op3(ops2.res, val4);
    if (ops3.res == 24){
        output->push_back("((" + to_string(val1) + ops1.op + to_string(val2) +") " + ops2.op  + to_string(val3) + ")" + ops3.op + to_string(val4));
    }

    // (val1 op1 (val2 op2 val3)) op3 val4 => (a+ (b+c)) + d 
    ops1 = op2(val2,val3);
    ops2 = op1(val1,ops1.res);
    ops3 = op3(ops2.res, val4);
    if (ops3.res == 24){
        output->push_back("(" + to_string(val1) + ops2.op + to_string(val2) +"(" + ops1.op  + to_string(val3) + "))" + ops3.op + to_string(val4));
    }

    // val1 op1 ((val2 op2 val3) op3 val4) => a + ((b+c)+d)
    ops2 = op3(ops1.res, val4);
    ops3 = op1(val1,ops2.res);
    if (ops3.res == 24){
        output->push_back(to_string(val1) + ops3.op + "(("+ to_string(val2) +  ops1.op  + to_string(val3) + ")" + ops2.op + to_string(val4)+")");
    }
}

void printSolution(vector<string> solutions)
{
    // KAMUS LOKAL

    // ALGORITMA

    for (auto solution = solutions.begin(); solution != solutions.end(); solution++)
    {
        cout << *solution << endl;
    }
}