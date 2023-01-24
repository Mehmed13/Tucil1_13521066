#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "functions.hpp"

Operasi tambah(double a, double b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '+';
    ops.res = a+b; 
    return ops;
}
Operasi kurang(double a, double b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '-';
    ops.res = a-b; 
    return ops;
}
Operasi kali(double a, double b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '*';
    ops.res = a*b; 
    return ops;
}
Operasi bagi(double a, double b)
{
    // KAMUS LOKAL
    Operasi ops;
    // ALGORITMA
    ops.op = '/';
    if (b != 0){
        ops.res = a/b;
    } else {
        ops.res = 9999; //undefine
    }
    return ops;
}
void cardStringToInt(string inputString[], int inputInt[])
{
    // KAMUS LOKAL
    int i;
    // ALGORITMA
    for(i=0; i<4; i++){
        if (inputString[i] == "A"){
            inputInt[i] = 1;
        } else if (inputString[i] == "J")
        {
            inputInt[i] = 11;
        }else if (inputString[i] == "Q")
        {
            inputInt[i] = 12;
        }else if (inputString[i] == "K")
        {
            inputInt[i] = 13;
        } else {
            inputInt[i] = stoi(inputString[i]);
        }

    }
}
void cardIntToString(int inputInt[], string inputString[])
{
    // KAMUS LOKAL
    int i;
    // ALGORITMA
    for(i=0; i<4; i++){
        if (inputInt[i] == 1){
            inputString[i] = "A";
        } else if (inputInt[i] == 11){
            inputString[i] = "J";
        } else if (inputInt[i] == 12){
            inputString[i] = "Q";
        } else if (inputInt[i] == 13){
            inputString[i] = "K";
        } else {
            inputString[i] = to_string(inputInt[i]);
        }
    }
}

// REALISASI FUNGSI/PROSEDUR
void getInput(int input[]){
    // KAMUS LOKAL
    int inputType, i;
    string inputString[4];
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
    cout<<endl;
    if (inputType == 1){ // Manual
        // setup
        string inputLines, arg;
        bool firstTry = true;
        bool validInput = false;

        // Validasi input
        do {
            cout<< "Masukkan 4 Kartu {A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K} dengan dipisahkan oleh satu spasi:"<<endl;
            if (firstTry){
                cin.ignore(); // Agar mencegah bug pada getline
            }
            getline(cin,inputLines);
            if(!isValidInput(inputLines)){
                cout<<"Masukan Tidak Sesuai"<< endl;
                firstTry = false;
            } else {
                validInput = true;
            }
        } while (!validInput);

        // Valid, collect the card
        stringstream semiArgs(inputLines);
        i=0;
        while (getline(semiArgs, arg, ' ')) {  
            inputString[i] = arg;
            i++;
        }

        // Convert to int
        cardStringToInt(inputString, input);

    } else { // Auto-Generated
        srand ( time(NULL) );
        input[0] = (rand() % 13) + 1; 
        input[1] = (rand() % 13) + 1; 
        input[2] = (rand() % 13) + 1; 
        input[3] = (rand() % 13) + 1; 
        // Convert dalam bentuk string
        cardIntToString(input,inputString);
    }
    // Display
    cout << "KARTU MAKE IT 24"<<endl;
    cout << inputString[0] << " " << inputString[1] << " " << inputString[2] << " " << inputString[3] << endl <<endl;
}

void getSolution(int input[], vector<string> *output){
    // KAMUS LOKAL
    int i,j,k,l,m,n,o, nSolution, nPermutation, ctr;
    ctr = 0;
    vector<Cards> allPermutation;
    // ALGORITMA
    functionPtr operators[4] = {tambah, kurang, kali, bagi};

    //Permutasi susunan kartu
    for (i= 0 ; i< 4; i++){
        for (j=0; j<4; j++){
            if (j != i){
                for (k=0; k<4; k++){
                    if (k!=j && k!=i){
                        for (l=0; l<4;l++){
                            if (l!=k && l!=j && l!=i){
                                Cards tempCard;
                                tempCard.card1 = input[i];
                                tempCard.card2 = input[j];
                                tempCard.card3 = input[k];
                                tempCard.card4 = input[l];
                                // Jika Belum Ada kartu pada susunan yang telah dieksekusi
                                if (!isExistCards(tempCard, allPermutation)){
                                    allPermutation.push_back(tempCard);
                                    // Permutasi Operator
                                    for (m=0; m<=3; m++){
                                        for (n=0; n<=3; n++){
                                            for (o=0; o<=3; o++){
                                                functionPtr funcs[3] = {operators[m], operators[n], operators[o]};
                                                solveParentheses(tempCard,funcs,output); // Cari solusi pada kemungkinan susunan tanda kurung
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool isValidInput(string inputLines)
{
    // KAMUS LOKAL
    string stringCards[4];
    string arg;
    int i,nValid, nArg;
    // ALGORITMA 
    nValid = 0;
    nArg = 0;
    // Validasi Jumlah Input
    // splitting
    stringstream semiArgs(inputLines);
    while (getline(semiArgs, arg, ' ')) {  
        if(nArg<=3){
            stringCards[i] = arg;
        }
        i++;
        nArg++;
    }  

    if (nArg == 4){
        // Validasi Kartu
        for(i=0; i<4; i++){
            if (isValidCard(stringCards[i])){
                nValid++;
            }
        }
    }
    return (nValid == 4); // Valid keempat kartunya
}
bool isValidCard(string stringCard)
{
    // KAMUS LOKAL
    string validCard[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int idx;
    bool valid;
    // ALGORITMA
    valid = false;
    idx = 0;
    // Cek apakah kartu terdapat di dalam list kartu yang valid
    while ((idx < 13) &&(!valid))
    {
        if (stringCard == validCard[idx])
        {
            valid = true;
        }
        else {
            idx++;
        }
    }
    return valid;
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
    double epsilon = pow(10.0, -12); // Epsilon untuk menangani galat akibat pecahan
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

    // (val1 op1 val2) op2 (val3 op3 val4) => (a+b) + (c+d)
    ops1 = op1(val1,val2);
    ops2 = op3(val3,val4);
    ops3 = op2(ops1.res,ops2.res);
    if (abs(ops3.res-24)<epsilon){
        output->push_back("(" + to_string(val1) + " " + ops1.op + " " + to_string(val2) +")" + " " + ops3.op + " " + "(" + to_string(val3) + " " + ops2.op + " " + to_string(val4) + ")" );
    }

    // ((val1 op1 val2) op2 val3) op3 val4 => ((a+b) + c) + d 
    ops2 = op2(ops1.res, val3);
    ops3 = op3(ops2.res, val4);
    if (abs(ops3.res-24)<epsilon){
        output->push_back("((" + to_string(val1) + " " + ops1.op + " " + to_string(val2) +")" + " " + ops2.op + " " + to_string(val3) + ")" + " " +ops3.op + " " + to_string(val4));
    }

    // (val1 op1 (val2 op2 val3)) op3 val4 => (a+ (b+c)) + d 
    ops1 = op2(val2,val3);
    ops2 = op1(val1,ops1.res);
    ops3 = op3(ops2.res, val4);
    if (abs(ops3.res-24)<epsilon){
        output->push_back("(" + to_string(val1) + " " + ops2.op + " " + "(" + to_string(val2) + " " + ops1.op + " " + to_string(val3) + "))" + " " + ops3.op + " " + to_string(val4));
    }

    // val1 op1 ((val2 op2 val3) op3 val4) => a + ((b+c)+d)
    ops2 = op3(ops1.res, val4);
    ops3 = op1(val1,ops2.res);
    if (abs(ops3.res-24)<epsilon){
        output->push_back(to_string(val1) + " "+ ops3.op + " "+ "(("+ to_string(val2) + " " + ops1.op+ " "  + to_string(val3) + ")" + " " + ops2.op + " " +to_string(val4)+")");
    }
    // val1 op1 (val2 op2 (val3 op3 val4)) => a + (b+(c+d))
    ops1 = op3(val3,val4); 
    ops2 = op2(val2, ops1.res);
    ops3 = op1(val1,ops2.res);
    if (abs(ops3.res-24)<epsilon){
        output->push_back(to_string(val1) + " "+ ops3.op + " "+ "("+ to_string(val2) + " " + ops2.op+ " " +"(" + to_string(val3)  + " " + ops1.op + " " +to_string(val4)+"))");
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

void saveFile(string namaFile, vector<string> solutions)
{
    // KAMUS LOKAL
    // ALGORITMA
    // Create and Open a text file
    ofstream SolutionFile("test/" + namaFile + ".txt");
    string solutionTeks="";
    // Write to file
    for (auto solution = solutions.begin(); solution != solutions.end(); solution++)
    {
        solutionTeks += (*solution+ "\n");
    }
    SolutionFile << solutionTeks;
    // Close the file
    SolutionFile.close();
}