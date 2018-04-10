#ifndef list_implementation_cpp
#define list_implementation_cpp

#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>

//size_t PTRNULL = 1000;

#include "huff.h"



    list* Cre_List(){
        list *l = new list();
        if(l == NULL){
            std::cerr << "Error list! Not enough mem." << std::endl;
            exit(EXIT_FAILURE);
        }
        else return l;
    }

    bool IsNull(list *l){
        if(l == NULL){
            std::cerr << "Error list! List is empty." << std::endl;
            exit(EXIT_FAILURE);
        }
        return l == NULL;
    }

    void  Next(list* l){
        IsNull(l);
        if (l->cur == NULL){
            std::cerr << "Error next! Next is empty." << std::endl;
            exit(EXIT_FAILURE);
        }
        l->cur = l->cur->next;
    }


    void Prev(list* l){
        IsNull(l);
        if(l->cur->prev == NULL){
            std::cerr << "Error prev! Prev is empty." << std::endl;
            exit(EXIT_FAILURE);
        }
        l->cur = l->cur->prev;
    }

    void Start(list* l){
        IsNull(l);
        l->cur = l->begin;
    }

    void End(list* l){
        IsNull(l);
        l->cur = l->end;
    }

    void Add(list* l, char elem){
        IsNull(l);
        atom *n = new atom();
        n->elem = elem;
        if (n == NULL){
            std::cerr << "Error add! Not enough mem." << std::endl;
            exit(EXIT_FAILURE);
        }
        if(l->begin->elem == NULL){
            l->cur = n;
            l->begin = l->cur;
            l->end   = l->cur;
            l->cur   = l->begin;
            l->size += 1;
            return;
        }
        else{
            if(l->end->prev == NULL) {
                l->end = n;
                l->end->prev = l->begin;
                l->begin->next = l->end;
                Start(l);
            }
            else{
                l->end->next = n;
                n->prev = l->end;
                l->end = l->end->next;
                Start(l);
            }
            l->size += 1;
        }
    }

    char Item(list* l){
        IsNull(l);
        if(l->cur == NULL){return '!';}
        return l->cur->elem;
    }

    void destroy(list* l){
        IsNull(l);
        for(int i = 0; i < l->size; i++){
            End(l);
            l->end = l->cur->prev;
            delete l->cur;
        }
        delete l;
    }

#endif //list_implementation_cpp

