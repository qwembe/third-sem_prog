#ifndef LIST_H
#define LIST_H

#include <iostream>
    struct atom{
        char elem;
        atom * next;
        atom * prev;
        atom(){elem = NULL; next = NULL; prev = NULL;}
    };
    struct list{
        atom * begin;
        atom * cur;
        atom * end;
        int size;
        list(){ atom a;
                cur   = &a ;
                begin = cur;
                end   = cur;
                size  = 0;}
    };

    list* Cre_List();
    bool isNull(list *l);
    void Next(list *l);
    void Prev(list *l);
    void Start(list *l);
    void End(list *l);
    void Add(list *,char);
    char Item(list *);
    void destroy(list *l);


#endif // LIST_H
