#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
using namespace std;
template <typename elem>
struct Node {
    elem info;
    size_t lt; //left
    size_t rt; //right
};
template <typename T> bool isNull(size_t index, Node<T>* b); //проверка на нулевой узел
template <typename T> T RootBT (Node<T>* b, size_t index); //взятие корня поддерева
template <typename T> size_t Left (Node<T>* b,size_t index); //взятие индекса правого узла
template <typename T> size_t Right (Node<T>* b, size_t index);//взятие индекса левого узла
template <typename T> size_t ConsBT(T x, size_t lst,  size_t rst, Node<T>* b, size_t index);//добавление узла в список на базе вектора
template <typename T> void destroy (size_t index, Node<T>* b); // удаление дерева
template <typename T> size_t enterBT (size_t index, Node<T>* b, ifstream &fin); // считывание данных из файла
template <typename T> size_t readBT(size_t index, Node<T>* b);// считывание данных с клавиатуры
template <typename T> void outBT(size_t index, Node<T>* b); // вывод дерева на монитор
template <typename T> void displayBT (size_t index, Node<T>* b, size_t n); // вывод "изображения" дерева на монитор
template <typename T> void displayBT (size_t index, Node<T>* b, size_t n);
/*
3. Заданы два бинарных дерева b1 и b2 типа BT с произвольным типом элементов. Проверить:
а) подобны ли они (два бинарных дерева подобны, если они оба пусты либо они оба непусты и их левые поддеревья
подобны и правые поддеревья подобны);
б) равны ли они (два бинарных дерева равны, если они подобны и их соответствующие элементы равны);
в) зеркально подобны ли они (два бинарных дерева зеркально подобны, если они оба пусты либо они оба непусты и
для каждого из них левое поддерево одного подобно правому поддереву другого);
г) симметричны ли они (два бинарных дерева симметричны, если они зеркально подобны и их соответствующие
элементы равны).
*/
size_t lastIndex = 0; //????????? ?????? ???????
bool sim = true;  // SIM-metric     -(a)
bool equ = true;  // EQU-al         -(b)
bool mir = true;  // MIR-ror_like   -(v)
bool ric = true;  // simet-RIC      -(g)
int currentH = 0; // ??????? ????? ???????
template <typename T> void checkerAB(Node<T>* a, Node<T>* b, size_t A, size_t B);
template <typename T> void checkerVG(Node<T>* a, Node<T>* b, size_t A, size_t B);
void indent(int opt);
int main(){
    Node<char> a[100];
    Node<char> b[100];
    ifstream fin("KLP.txt");
    if(!fin) cerr << "Error main! File not found!" << endl;
    int input;
    printf("Read from file?(1/2 - yes/no)\n");
    scanf("%d", &input);
    if (input == 1){
        enterBT(0, a, fin);
        enterBT(0, b, fin);
        outBT(0, a);
        cout << endl;
        outBT(0, b);
    }
    else{
        cout << "Put space beetwen two BT" <<endl;
        readBT(0, a);
        readBT(0, b);
        outBT(0, a);
        cout << endl;
        outBT(0, b);
    };
    cout<<endl;
    cout << "A - Btree" << endl;
    displayBT(0,a,0);
    cout << "B - Btree" << endl;
    displayBT(0,b,0);
/// [1]
    cout << "!! Checking a,b attribute..." << endl;
    checkerAB(a,b,0,0);
    cout << endl <<"!! Checking v,g attribute..." << endl;
    checkerVG(a,b,0,0);
    if(ric || mir || equ || sim){
        cout << "They are ";
        if(sim) cout << "(a)simular ";
        if(equ) cout << "(b)equal ";
        if(mir) cout << "(v)mirror-like ";
        if(ric) cout << "(g)simetric ";
        cout << "binar trees";
    }
    else{
        cout << "Non of them have a-g attribute" << endl;
    }
    return 0;
}
/// [2]
template <typename T> void checkerAB(Node<T>* a, Node<T>* b, size_t A, size_t B){
    if (!sim) return ;
    // no sence to continue if it's not even simular BTree
    cout << "* A - (";
    if(!isNull(a,A)) { cout << RootBT(a,A); } else {cout << "nil";}
    cout << ") B -(";
    if(!isNull(b,B)) { cout << RootBT(b,B); } else {cout << "nil";}
    cout << ')';
    if ((isNull(a,A) ^ isNull(b,B))) {
        // XOR ( ^ ): if 1 - not simular or not equal, else - maybe sim-r or eq.
        indent(0);
        cout << " !! Non of atribute is true;" << endl;
        indent(3);
        equ = false;
        sim = false;
        return ;
    }
    if(isNull(b,B)){
        // maybe 0 ^ 0
        indent(3);
        cout << "* Go back" << endl;
        indent(0);
        return ;
    }   // else 1 ^ 1 (1 == smth that not equlas 0)[ 'a' ^ 'b' == 1 ]
    if((RootBT(a,A) == RootBT(b,B))){
        indent(3);
        cout << "+ They are equal";
        indent(3);
        cout << "* Check left"<< endl;
        indent(1);
        checkerAB(a,b,Left(a,A),Left(b,B));
        if (!sim) return ;
        indent(0);
        cout << "* Check right"<< endl;
        indent(1);
        checkerAB(a,b,Right(a,A),Right(b,B));
        indent(0);
        return ;
    }
    else{
        equ = false;
        indent(3);
        cout << "- They are not equal";
        indent(3);
        cout << "* Check left"<< endl;
        indent(1);
        checkerAB(a,b,Left(a,A),Left(b,B));
        if (!sim) return ;
        indent(0);
        cout << "* Check right" << endl;
        indent(1);
        checkerAB(a,b,Right(a,A),Right(b,B));
        indent(0);
        return ;
    }
}
/// {3} >-VG-<
template <typename T> void checkerVG(Node<T>* a, Node<T>* b, size_t A, size_t B){
    if (!mir) return ;
    // no sence to continue if it's not even mirror like BTree
    cout << "* A - (";
    if(!isNull(a,A)) { cout << RootBT(a,A); } else {cout << "nil";}
    cout << ") B -(";
    if(!isNull(b,B)) { cout << RootBT(b,B); } else {cout << "nil";}
    cout << ')';
    if ((isNull(a,A) ^ isNull(b,B))) {
        // XOR ( ^ ): if 1 - not simular or not equal, else - maybe sim-r or eq.
        indent(0);
        cout << " !! Non of atribute is true;" << endl;
        indent(3);
        mir = false;
        ric = false;
        return ;
    }
    if(isNull(b,B)){
        // maybe 0 ^ 0
        indent(3);
        cout << "* Go back" << endl;
        indent(0);
        return ;
    }   // else 1 ^ 1 (1 == smth that not equlas 0)[ 'a' ^ 'b' == 1 ]
    if((RootBT(a,A) == RootBT(b,B))){
        indent(3);
        cout << "+ They are equal";
        indent(3);
        cout << "* A->Right B->Left"<< endl;
        indent(1);
        checkerVG(a,b,Right(a,A),Left(b,B));
        if (!mir) return ;
        indent(0);
        cout << "* A->Left B->Right"<< endl;
        indent(1);
        checkerVG(a,b,Left(a,A),Right(b,B));
        indent(0);
        return ;
    }
    else{
        ric = false;
        indent(3);
        cout << "- They are not equal";
        indent(3);
        cout << "* A->Right B->Left"<< endl;
        indent(1);
        checkerVG(a,b,Right(a,A),Left(b,B));
        if (!mir) return ;
        indent(0);
        cout << "* A->Left B->Right"<< endl;
        indent(1);
        checkerVG(a,b,Left(a,A),Right(b,B));
        indent(0);
        return ;
    }
}
void indent(int opt){
    if(opt == 1){ ++currentH;};
    if(opt == 0){ --currentH;};
    if(opt == 2){currentH = 0;};
    if(opt == 3){cout << "\n";};
    if(currentH < 0){currentH = 0;}
    for (int i=0; i<currentH; i++) cout << "   ";
}
/// [2]!
template <typename T> bool isNull(Node<T>* b,size_t index){
    return b[index].info == NULL;
}
template <typename T> T RootBT (Node<T>* b, size_t index){
    if (b == NULL) {
        cerr << "Error: RootBT(null) \n";
        exit(1);
    }
    else
        return b[index].info;
}
template <typename T> size_t Left (Node<T>* b,size_t index ){
    if (b == NULL){
        cerr << "Error: Left(null) \n";
        exit(1);
    }
    else
        return b[index].lt;
}
template <typename T> size_t Right (Node<T>* b, size_t index){
    if (b == NULL) {
        cerr << "Error: Right(null) \n";
        exit(1);
    }
    else
        return b[index].rt;
}
template <typename T> size_t ConsBT(T x, size_t lst,  size_t rst, Node<T>* b, size_t index){
    if ( b != NULL) {
        b[index].info = x;
        b[index].lt = lst;
        b[index].rt = rst;
        if (lastIndex<rst)
            lastIndex = rst;
        return index;
    }
    else {
        cerr << "Memory not enough\n";
        exit(1);
    }
}
template <typename T> void destroy (size_t index, Node<T>* b){
    if (b != NULL) {
        destroy (b[index].lt, b);
        destroy (b[index].rt, b);
        delete b;
        b = NULL;
    }
}
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
template <typename T> size_t readBT(size_t index, Node<T>* b){
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
template <typename T> void outBT(size_t index, Node<T>* b){
    if (b[index].info != NULL) {
        cout << RootBT(b,index);
        outBT(Left(b,index), b);
        outBT(Right(b,index), b);
    }
    else cout << '/';
}
template <typename T> void displayBT (size_t index, Node<T>* b, size_t n){
    if (b!=NULL) {
        if(!isNull(b, index)){
            cout << ' ' << RootBT(b, index);
            if(!isNull(b,Right(b, index))){
                displayBT (Right(b, index), b,n+1);
            }
            else cout << endl;
            if(!isNull(b,Left(b, index))) {
                for (int i=1;i<=n;i++) cout << "  ";
                displayBT (Left(b, index), b,n+1);
            }
        }
        else{
            cout << "(NULL)" << endl;
        }
    }
    else {
    };
}
