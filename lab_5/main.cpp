#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>

#include "huff.h"
using namespace std;

//Makes alphavite binTree
binTree alpha();
//Comstucts BT
binTree make_tree(binTree p);
// Reads from file characters and adds to the code list
void input_code(list* l);
//Shows list
void show_list(list* l);

void outBT(binTree b);
void displayBT(binTree b, int n);

ofstream log("log.txt");
int main()
{
    setlocale (0, "rus");
    code_n_alph* cna = new code_n_alph();
    cna->code = Cre_List();
    cna->answ = Cre_List();
    log << "loading code..." << endl;
    cout << "Loaded code:\n";
    input_code(cna->code);
    cout << endl;
    log << "Loading alphavite to BT..." << endl;
    cna->alph = alpha();
    log << "Structure of alphaBT:" << endl;
    outBT(cna->alph);
    log <<"\nDisplay:" <<endl;
    displayBT((cna->alph),0);
    cna = encoding(cna);
    //log << "Decoded message" << endl;
    //cout <<"Decoded message" << endl;
    show_list(cna->answ);
    log  << "\nSucessful end!";
    cout << "\nSucessful end!";

}


void show_list(list*l){
    Start(l);
    Next(l);
    for(int i = 0; i < l->size-1 ; i++){
        log << Item(l);
        cout << Item(l);
        Next(l);
    }
    log << endl;
    Start(l);
}

// Reads from file characters and adds to the code list
void input_code(list* l){
    ifstream code("code.txt");
    if(!code){
        log << "Erorr code! File not found!" << endl;
        exit(EXIT_FAILURE);
    }
    char cur;
    do{
        code.read(&cur,1);
        Add(l,cur);
    }while(cur != '\n');
    code.close();
    show_list(l);
}

ifstream data("data.txt");
binTree alpha()                 // constructing BT of alphavite
{
    if(!data){
        log << "Erorr data! File not found!" << endl;
        exit(EXIT_FAILURE);
    }
    binTree p = new node();
        p =  make_tree(p);
    return p;

}

binTree make_tree(binTree p){   //0 -> left, 1 -> right
    char cur;
    binTree x = Create();
    binTree tmp = p;
    if(isNull(tmp)) {
        tmp = new node();
    }
    log << "Alphavite:" << endl;

    do{                         // cur != '\0' && !data.eof()

        /*
         * Data must look like
         * [ bin code <space> symbol <enter> ]
         * do not use EOC NCH EMP symbols in data
         * for avoiding unpredictable circustamces
         */

        data.read(&cur,1);      // Loading from file

        log << cur;

        if(cur == '\n'){        // alternativ exit from cycle
            data.read(&cur,1);
            log << cur;
            if(cur == '\n'){
                data.read(&cur,1);
                log << cur;
                if(cur == '\n'){
                    return p;
                }
            }
        }
        if(cur == '0')
            if(!isNull(Left(tmp))) {
                tmp = Left(tmp);
                continue;
            }
            else{
                tmp->lt = ConsBT(cur,x,x);
                tmp = Left(tmp);
                continue;
            }
        if(cur == '1')
            if(!isNull(tmp->rt)) {
                tmp = Right(tmp);
                continue;
            }
            else{
                tmp->rt = ConsBT(cur,x,x);
                tmp = Right(tmp);
                continue;
            }
        if(cur == ' '){
            data.read(&cur,1);
            log << cur;
            tmp->info = cur;
            tmp = p;
            continue;
        }

     } while (cur != '\0' && !data.eof());

    return p;               //Apparently nevr goes to here

}

void outBT(binTree b)
{
    if (b!=NULL) {
        log << RootBT(b);
        outBT(Left(b));
        outBT(Right(b));
    }
    else log << '/';
}

void displayBT (binTree b, int n)
{	// n - уровень узла
    if (b!=NULL) {
        log << ' ' << RootBT(b);
        if(!isNull(Right(b))) {displayBT (Right(b),n+1);}
        else log << endl; // вниз
        if(!isNull(Left(b))) {
            for (int i=1;i<=n;i++) log << "  "; // вправо
            displayBT (Left(b),n+1);}
    }
    else {};
}
