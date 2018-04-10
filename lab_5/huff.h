#ifndef HUFF_H
#define HUFF_H

#include <iostream>
#include <cstdlib>

#include "Btree.h"
#include "list.h"
#include "vecbt.h"

#define MAX_SIZE 257      // posible asci character
#define HEAD MAX_SIZE - 1

struct code_n_alph{
    list *code;         //contains code
    binTree alph;       //contains alphavite
    list* answ;         //contains answer. Is used to hold decoded msg
    code_n_alph(){
        list *code = new list();
        binTree* alph = new binTree();
        list *answ = new list();
    }
};

code_n_alph *encoding(struct code_n_alph* cna);     //encoding finction
template <typename T> void huf_init(Node<T>*hf, struct code_n_alph* cna);   //initiating huf tree with first symbol

char nextSymbol(struct code_n_alph* cna);    //returns next symbol from code if it was transmited
char nextByte(struct code_n_alph* cna);     // returns next byte from code

//Changes nodes (current <-> index)
template<typename T>void   HUF_swap(Node<T>* hf,size_t current, size_t index);

//Inserts new symbol in the tree with index from code cna
template<typename T> int   HUF_insert(Node<T>* hf,size_t index,struct code_n_alph *cna);

//Makes tree -> huffman tree
template<typename T>int   HUF_update(Node<T>* hf);

//Adds mew symbol to answ from next bytes of code
template<typename T> int   HUF_add(Node<T>* hf,struct code_n_alph *cna);

//Recursiv rewight of hf
template<typename T>size_t HUF_wight(Node<T>* hf,size_t index);

//Changes HUFFTREE[index] with determined info
template<typename T>void   HUF_change(Node<T>* hf,size_t index,
                                        T a,size_t b,size_t c,size_t d,unsigned int e);


#endif // HUFF_H
