#ifndef bt_implementation_cpp
#define bt_implementation_cpp
#include <iostream>
#include <cstdlib>
#include "Btree.h"
using namespace std ;

//-------------------------------------
    binTree Create()
    {	return NULL;
    }
//-------------------------------------
    bool isNull(binTree b)
    {	return (b == NULL);
    }
//-------------------------------------
    base RootBT (binTree b)
    {	if (b == NULL) {
            cerr << "Error: RootBT(null) \n";
            cerr << "Exiting decoding...\n";
            return NULL;
           // exit(1);
        }
        else return b->info;
    }
//-------------------------------------
    binTree Left (binTree b)
    {	if (b == NULL) { cerr << "Error: Left(null) \n"; exit(1); }
        else return b ->lt;
    }
//-------------------------------------
    binTree Right (binTree b)
    {	if (b == NULL) { cerr << "Error: Right(null) \n"; exit(1); }
        else return b->rt;
    }
//-------------------------------------
    binTree ConsBT(const base &x, binTree &lst,  binTree &rst)
    {	binTree p;
        p = new node;
        if ( p != NULL)	{
            p ->info = x;
            p ->lt = lst;
            p ->rt = rst;
            return p;
        }
        else {cerr << "Memory not enough\n"; exit(1);}
    }
//-------------------------------------
    void destroy (binTree &b)
    {	if (b != NULL)	{
            destroy (b->lt);
            destroy (b->rt);
            delete b;
            b = NULL;
        }
    }

#endif //bt_implementation_cpp
