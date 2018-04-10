#ifndef huff_implementation_cpp
#define huff_implementation_cpp

//huff_implementation_cpp

#include "huff.h"


#include "vecbt_implementation.cpp"

char EOC = '!';         //End Of Code
char NCH = '#';         //New CHaracter
char EMP = '@';         //EMpty node
size_t last_index;
size_t PTRNULL = 1000;

struct code_n_alph * encoding(struct code_n_alph *cna){

    Node<char> HUF[MAX_SIZE];

    int i = 1;

    log << "-------" << "Step #" << i++ << "------"<< std::endl;

    huf_init(HUF,cna);
    vec_displayBT(0,HUF,0);

    last_index =  2;                     //max index
    log << "-------" << "Step #" << i++ << "------"<< std::endl;
    while(HUF_add(HUF,cna) == 0){
        HUF_wight(HUF,0);
            log << "\n before update:\n" ;
        vec_displayBT(0,HUF,0);
            log << "\n after update:\n" ;

        while(HUF_update(HUF) == 1);
        vec_displayBT(0,HUF,0);
        log << "\n-------" << "Step #" << i++ << "------" << std::endl;
    }
    return cna;
}

template<typename T>size_t HUF_wight(Node<T>* hf,size_t index){
    //log << "\nRewighting...\n";
    if(vec_RootBT(hf,index) == EMP){
        hf[index].wight =
                HUF_wight(hf,vec_Left(hf,index))
                + HUF_wight(hf,vec_Right(hf,index));
        return hf[index].wight;
    } else if(vec_RootBT(hf,index) == NCH) {
        hf[index].wight = 0;
        return 0;
    } else {
        return hf[index].wight;;
    }
}


template<typename T>int HUF_update(Node<T>* hf){
    size_t source = 0;
    size_t destination = 0;
    unsigned int dest_wight;  //wight of destination
    size_t d = 1;  // means delta - distance between compareble wight (!) is used when next is parent;
    size_t pr;          //paren of source
    for(size_t i = last_index; i > 0; i--){
        pr = hf[i].pr;
        if(i-1 == pr) {d = 2;} else {d = 1;};
        if(hf[i].wight > hf[i-d].wight) {
            source = i;
            dest_wight = hf[source-d].wight;
            destination = source-d;
            break;
        }
    }
    if(source != 0){
        unsigned int bigger_wight;
        pr = hf[source].pr;
        for(size_t i = destination; i-2>= 0; i--){
            if(i-1 == pr) {d = 2;} else {d = 1;};
            bigger_wight = hf[i-d].wight;
            if(dest_wight < bigger_wight){
                if(i != pr){
                    destination = i;
                } else {
                    destination = i-d;
                }
                break;
            }
        }
        HUF_swap(hf,source,destination);
        HUF_wight(hf,0);
        return 1;
    }
    return 0;
}


template<typename T>void HUF_change(Node<T>* hf,size_t index,
                                    T a,size_t b,size_t c,size_t d,unsigned int e){
    hf[index].info  =a;
    hf[index].rt    =b;
    hf[index].lt    =c;
    hf[index].pr    =d;
    hf[index].wight =e;
    hf[index].number;
}

template<typename T>void HUF_swap(Node<T>* hf,size_t a, size_t b){

    log << " \nswitches " << vec_RootBT(hf,a) << "(" <<hf[a].wight << ")" ;
    log << " <-> " << vec_RootBT(hf,b) << "(" <<hf[b].wight << ")\n";

/*    if(a == b){
        if(hf[hf[a].pr].lt == a) {
            hf[a]
        }
    }*/
    size_t parent[2];
    parent[0] = hf[a].pr;
    parent[1] = hf[b].pr;
    Node<T> c[2];
    c[0]  = hf[a];
    c[1]  = hf[b];
    hf[b] =  c[0];
    hf[a] =  c[1];

    hf[a].pr = parent[0];
    hf[b].pr = parent[1];

    // to connect nodes with sons (lft & rgth) if it nesecery
    if(vec_RootBT(hf,a) == EMP){
        hf[vec_Right(hf,a)].pr = a;
        hf[vec_Left(hf,a)].pr  = a;
    }
    if(vec_RootBT(hf,b) == EMP){
        hf[vec_Right(hf,b)].pr = b;
        hf[vec_Left(hf,b)].pr  = b;
    }

}

template<typename T> int HUF_insert(Node<T>* hf,size_t index,struct code_n_alph *cna){

    char c = nextSymbol(cna);

    log << "\ninsertion...";

    HUF_change(hf,index+1,
               c, PTRNULL , PTRNULL , index , 1);

    HUF_change(hf,index+2,
               NCH, PTRNULL , PTRNULL , index , 0);

    HUF_change(hf,index,
               EMP, index+1 , index+2 , hf[index].pr , 1);

    Add(cna->answ,c);
    c = vec_RootBT(hf,index+1);


    if(c == EOC) return 1;

    last_index += 2;
    HUF_wight(hf,0);

    return 0;
}

template<typename T> int HUF_add(Node<T>* hf,struct code_n_alph *cna){
    char bit;
    size_t index = 0;
    log << "\nnext bytes:";
    char c = vec_RootBT(hf,index);
    while(c == EMP){
        bit = nextByte(cna);
        log << bit;
        if(bit == '0'){
            index = vec_Left(hf,index);
        } else if(bit == '1'){
            index = vec_Right(hf,index);
        } else {
            c = bit;
            break;
        }
        c = vec_RootBT(hf,index);
    };

    log << " - HUF code's symbol - " << c;
    if(c == NCH){
        log << " - new symbol\n";
        return HUF_insert(hf,index,cna);
    }

    if(c == EOC){
        log << " - Error add! not enough bytes...\n";
        log << " Exiting decoding...\n";
        Add(cna->answ,c);
        return 1;
    }

    Add(cna->answ,c);
    (hf[index].wight)++;
    HUF_wight(hf,0);
    return 0;
}





char nextByte(struct code_n_alph* cna){   // '0' or '1'
    char c = Item(cna->code);

    if(c != '0' && c != '1'){
            std::cerr << "Erorr nextByte! nor 0 1!\n";
            std::cerr << "Exiting decoding...\n";
            c = EOC;
            //exit(EXIT_FAILURE);
        }
    Next(cna->code);
    return c;
}

char nextSymbol(struct code_n_alph* cna){
    char code;
    char letter;
    log << "New code bytes:";
    code = nextByte(cna);
    log << code;
    binTree tmp = cna->alph;
    do{
        if(code == '0'){
            tmp = Left(tmp);
        } else if(code == '1'){
            tmp = Right(tmp);
        } else if(code == EOC){
            letter = code;
            break;
        };
        letter = RootBT(tmp);
        if(letter != '0' && letter != '1') break;
        code = nextByte(cna);
        log << code;
    } while(code == '0' || code == '1');
    log << " - symbol of " << letter  << std::endl;
    return letter;
}


template <typename T> void huf_init(Node<T>* hf,struct code_n_alph* cna){
    Start(cna->code);
    Start(cna->answ);
    char c = nextSymbol(cna);
    if(c == EOC){
        std::cerr << "Error huf_init! EOC at the start!";
        exit(EXIT_FAILURE);
    }
    Add(cna->answ,c);
    Next(cna->answ);

    //first node

    hf[0].info  =  EMP;
    hf[0].rt    =  1;
    hf[0].lt    =  2;
    hf[0].pr    = PTRNULL;
    hf[0].wight =  1;
    hf[0].number;

    //first character

    hf[1].info  =  c;
    hf[1].rt    = PTRNULL;  // means empty
    hf[1].lt    = PTRNULL;
    hf[1].pr    =  0;
    hf[1].wight =  1;
    hf[1].number;

    //New symbol

    hf[2].info  =  NCH;
    hf[2].rt    = PTRNULL;
    hf[2].lt    = PTRNULL;
    hf[2].pr    =  0;
    hf[2].wight =  0;
    hf[2].number;
}





////////////////////////////////////////////////////////////


#endif //huff_implementation_cpp

#include "vecbt.h"
using namespace std ;

int currentH = 0;
size_t lastIndex = 0;



template <typename T> bool vec_isNull(Node<T>* b,size_t index){
    if(index != PTRNULL){
        return b[index].info == NULL;
    } else {
        return NULL == NULL;
    }
}

template <typename T> T vec_RootBT (Node<T>* b, size_t index){
    if (b == NULL) {
        cerr << "Error: RootBT(null) \n";
        exit(1);
    }
    else
        return b[index].info;
}

template <typename T> size_t vec_Left (Node<T>* b,size_t index ){
    if (b == NULL){
        cerr << "Error: Left(null) \n";
        exit(1);
    }
    else
        return b[index].lt;
}

template <typename T> size_t vec_Right (Node<T>* b, size_t index){
    if (b == NULL) {
        cerr << "Error: Right(null) \n";
        exit(1);
    }
    else
        return b[index].rt;
}

template <typename T> size_t vec_ConsBT(T x, size_t lst,  size_t rst, size_t pr, unsigned int wight, unsigned int number,
                                    Node<T>* b, size_t index){
    if ( b != NULL) {
        b[index].info = x;
        b[index].lt = lst;
        b[index].rt = rst;
        b[index].pr = pr;
        b[index].wight = wight;
        b[index].number = number;
        if (lastIndex<rst)
            lastIndex = rst;
        return index;
    }
    else {
        cerr << "Memory not enough\n";
        exit(1);
    }
}

template <typename T> void vec_destroy (size_t index, Node<T>* b){
    if (b != NULL) {
        destroy (b[index].lt, b);
        destroy (b[index].rt, b);
        delete b;
        b = NULL;
    }
}
/*
template <typename T> size_t enterBT (size_t index, Node<T>* b, ifstream &fin){
    char ch;
    int p, q;
    fin >> ch;
    lastIndex = index;
    if (ch=='/'){
        b[index].info = NULL;
        return index;
    }
    else{
        p = enterBT(++index, b, fin);
        index = lastIndex;
        q = enterBT(++index, b, fin);
        index = q;
        return ConsBT(ch, p, q, b, index-(q-p+1));
    }
}
*/
template <typename T> size_t vec_readBT(size_t index, Node<T>* b){
    char ch;
    int p, q;
    cin >> ch;
    lastIndex = index;
    if (ch=='/'){
        b[index].info = NULL;
        return index;
    }
    else{
        p = readBT(++index, b);
        index = lastIndex;
        q = readBT(++index, b);
        index = q;
        return ConsBT(ch, p, q, b, index-(q-p+1));
    }
}

template <typename T> void vec_outBT(size_t index, Node<T>* b){
    if (b[index].info != NULL) {
        cout << RootBT(b,index);
        outBT(Left(b,index), b);
        outBT(Right(b,index), b);
    }
    else cout << '/';
}

template <typename T> void vec_displayBT (size_t index, Node<T>* b, size_t n){
    if (b!=NULL) {
        if(!vec_isNull(b, index)){
            log << " " << vec_RootBT(b, index) << "(" << b[index].wight << ")";
            if(!vec_isNull(b,vec_Right(b, index))){
                vec_displayBT (vec_Right(b, index), b,n+1);
            }
            else log << endl;
            if(!vec_isNull(b,vec_Left(b, index))) {
                for (int i=1;i<=n;i++) log << "      ";
                vec_displayBT (vec_Left(b, index), b,n+1);
            }
        }
        else{
            log << "(NULL)" << endl;
        }
    }
    else {
    };
}


