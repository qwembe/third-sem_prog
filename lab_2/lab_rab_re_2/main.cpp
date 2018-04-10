#include <iostream>
#include "l_intrfc.h"
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
/*
 *
Пусть выражение (логическое, арифметическое, алгебраическое*) представлено иерархическим списком.
 В выражение входят константы и переменные, которые являются атомами списка.
Операции представляются в префиксной форме ( (<операция> <аргументы>) ),
либо в постфиксной форме (<аргументы> <операция>) ). Аргументов может быть 1, 2 и более.
 Например (в префиксной форме): (+ a (* b (- c))) или (OR a (AND b (NOT c))).
В задании даётся один из следующих вариантов требуемого действия с выражением:
 проверка синтаксической корректности, упрощение (преобразование), вычисление.
Пример упрощения: (+ 0 (* 1 (+ a b))) преобразуется в (+ a b).
17) логическое, упрощение, префиксная форма
*/


using namespace std;
using namespace h_list;


     void input_lisp ( lisp& y,ifstream &infile);
     void input_s_expr (base prev, lisp& y,ifstream &infile);
     void input_seq ( lisp& y,ifstream &infile);

     lisp make_super_atom (const base prev, ifstream &infile);

     void write_super_lisp (const lisp x);
     void write_super_seq (const lisp x);

     void analizator(lisp& y);
     int first_selector(const lisp &p_tail,const lisp &pp_tail,const lisp &c_head,const lisp &c_tail,lisp& lst);

     void sv_asocc(const lisp& p_tail,const lisp& c_branch);
     void nep_nep(const lisp& p_head, const lisp &c_head);
     void pogloshenie(const lisp& x,const base y,const lisp& z);
     void zatiranie1(const lisp& x );
     void zatiranie2(const lisp& x );

     lisp find_last(const lisp &y);

     bool reboot = false;

     void analizator(lisp& y)
     {
        int b;
        if (isNull(y)) return ;
        do
        {
            b = first_selector(NULL,NULL,y,y,y);
            cout << endl <<"         !<< exit recursy. There was " << b << " changes >>!" << endl <<endl;
            reboot = false;
        } while (b != 0);
     }

                                             //----------------
                                             //svoistva logicheskih uravnenii
                                             //----------------


     void sv_asocc(const lisp &p_tail, const lisp &c_branch)
     {
         lisp x = tail(c_branch);
         if(isNull(p_tail))
         {
             c_branch->node.pair.tl = x->node.pair.tl;
             c_branch->node.pair.hd = x->node.pair.hd;
             return;
         }
         lisp y = tail(p_tail);
         p_tail->node.pair.tl = c_branch->node.pair.tl;
         if(!isNull(y)) find_last(x)->node.pair.tl = y->node.pair.tl;
         else  find_last(x)->node.pair.tl = y;
     }

     void nep_nep(const lisp& p_head, const lisp &c_head)
     {
         lisp x = tail(c_head);
         p_head->node.pair.tl = c_head->node.pair.tl;                        // '@' vspomagatel'nii simvol
         if(isAtom(head(p_head))) head(p_head)->node.atom = '@';             //pri sled prohode izbavliaetsa ot skobochek
     }

     void pogloshenie(const lisp& x, const base y, const lisp& z)
     {
        if(!isNull(x)) tail(x)->node.pair.hd = make_atom(y);
        else
        {
            z->node.pair.hd = make_atom(y);
            z->node.pair.tl = NULL;
        }
     }

     void zatiranie1(const lisp& x)
     {
            head(x)->node.atom = '@';
     }
     void zatiranie2(const lisp& x)
     {
            x->node.pair.tl = x->node.pair.tl->node.pair.tl;
     }

                                     //----------------
                                     // end svoistva logicheskih uravnenii
                                     //----------------

                                     //*******
                                     //vspomagatel'nie funkcii
                                     //*******

     lisp find_last(const lisp& y)
     {
         if(!isNull(tail(y))) return find_last(tail(y));
         else return y;
     }

                                     //*******
                                     //**end**
                                     //*******

     int first_selector(const lisp& p_head, const lisp& pp_tail, const lisp &c_head, const lisp &c_tail, lisp &lst)
     {                      //p_op - prev operand, c_op - curent operand
//! -- #1'
        int smth_changed = 0;
        if(getAtom(head(lst)) == '@' && isNull(tail(lst))) lst = NULL;
        if(isNull(c_tail) || isNull(c_head) || isNull(tail(c_head))) return smth_changed;
        base p_op;
        base c_op = getAtom(head(c_head));
        lisp temp = c_tail;
        base cur;
        if(isNull(p_head)) p_op = NULL; else p_op = getAtom(head(p_head));
        if(!isAtom(head(c_tail))) cur = NULL; else cur = getAtom(head(c_tail));




        if(c_head == c_tail)
        {
//! -- #2'
            do{
                if(!isAtom(head(tail(temp))) )
                {
                    smth_changed += first_selector(c_head,temp,head(tail(temp)),head(tail(temp)),lst);
                }
                else
                {
                    smth_changed += first_selector(p_head,pp_tail,c_head,tail(temp),lst);
                }
                    temp = tail(temp);

            }while (!isNull(tail(temp)));

//! -- #3'

            if (c_op == '@')
            {
                sv_asocc(pp_tail,c_head);
                smth_changed++;
                write_super_lisp(lst);
                cout  << "      - deleted symbol '@' " << endl;
            }



            if((c_op == '+') || (c_op == '*') ) if (!isNull(tail(c_head))) if (isNull(tail(tail(c_head))))
            {
                sv_asocc(pp_tail,c_head);
                smth_changed++;
                write_super_lisp(lst);
                cout  << "      - [AND/OR b = b] " << endl;

            }

            if(!isNull(tail(c_tail))) if (isAtom(head(tail(c_tail)))) if (getAtom(head(tail(c_tail))) == '@')
            {
                zatiranie2(c_tail);
                smth_changed++;
                write_super_lisp(lst);
                cout  << "      - [symbol '@' was removed] " << endl;
            }


            switch (p_op) {
            case '*':
                switch (c_op) {
                case '*':                   //**
                    sv_asocc(pp_tail,c_head);
                    write_super_lisp(lst);
                    cout  << "      - open scobes (AND AND) " << endl;
                     smth_changed++;
                    break;
                case '+':                   //*+

                    break;
                case '-':                   //*-

                    break;
                }
                break;
            case '+':
                switch (c_op) {
                case '*':                   //+*

                    break;
                case '+':                   //++
                    sv_asocc(pp_tail,c_head);
                     write_super_lisp(lst);
                     cout  << "      - open scobes (OR OR) " << endl;
                     smth_changed++;

                    break;
                case '-':                   //+-

                    break;
                }
                break;
            case '-':
                switch (c_op) {
                case '*':                   //-*

                    break;
                case '+':                   //-+

                    break;
                case '-':                   //--
                    if(!reboot){
                        nep_nep(p_head,c_head);
                        write_super_lisp(lst);
                        cout  << "      - open doble (NOT NOT) [symbol '@' was placed] " << endl;
                        reboot = true;
                        smth_changed++;
                    }
                    break;
                }
                break;
            default:
                break;
            }
        }
        else // c_head != c_tail
//! -- #4'
        {

            if(!isNull(tail(c_tail))) if (isAtom(head(tail(c_tail)))) if (getAtom(head(tail(c_tail))) == '@')
            {
                zatiranie2(c_tail);
                smth_changed++;
                write_super_lisp(lst);
                cout  << "      - [symbol '@' was removed] " << endl;
            }




                switch (c_op) {
                case '+':
                    switch (cur) {
                    case '1':
                        pogloshenie(pp_tail,cur,c_head);
                        write_super_lisp(lst);
                        cout  << "      - [1 OR C = 1]" << endl;
                         smth_changed++;
                        break;
                    case '0':
                        zatiranie1(c_tail);
                        write_super_lisp(lst);
                        cout  << "      - deleted 0 [symbol '@' was placed]" << endl;
                         smth_changed++;
                        break;
                    }
                    break;
                case '*':
                    switch (cur) {
                    case '0':
                        pogloshenie(pp_tail,cur,c_head);
                        write_super_lisp(lst);
                        cout  << "      - - [0 AND C = 0]" << endl;
                         smth_changed++;
                        break;
                    case '1':
                        zatiranie1(c_tail);
                        write_super_lisp(lst);
                        cout  << "      - deleted 1 [symbol '@' was placed]" << endl;
                         smth_changed++;
                        break;
                    }
                    break;
                case '-':
                    if(p_op != '-')
                    {
                        switch (cur) {
                        case '1':
                            pogloshenie(pp_tail,'0',c_head);
                            write_super_lisp(lst);
                            cout  << "      - [NOT 1 = 0]" << endl;
                             smth_changed++;
                            break;
                        case '0':
                            pogloshenie(pp_tail,'1',c_head);
                            write_super_lisp(lst);
                            cout  << "      - [NOT 0 = 1]" << endl;
                             smth_changed++;
                            break;
                        }
                        break;
                    }
                }

                if(cur == '@')
                {
                    head(c_tail)->node.atom = ' ';
                    write_super_lisp(lst);
                    cout  << "      - [Symbol '@' was removed]" << endl;
                    smth_changed++;
                }
        }
        return smth_changed;
     }

    int main()
    {

                                        //----------------
                                        //initialization
                                        //----------------

    ifstream infile ("in_list.txt");
    if (!infile)
    {
        cout << "Erorr: file not found!" << endl;
        exit(EXIT_FAILURE);
    }

    lisp lst;

    input_lisp (lst,infile);

                                        //----------------
                                        // ! end initialization
                                        //----------------

                                        //----------------
                                        // ! Analizator !
                                        //----------------

    write_super_lisp(lst);

    cout  << endl;

    analizator(lst);

                                            //----------------
                                            // ! Analizator !
                                            //----------------

    write_super_lisp(lst);





    return 0;
    }

    //--- input from file ---

    //...........................
    // vvod spiska iz faila
        void input_lisp ( lisp& y,ifstream &infile)
        {	base x;
            do infile >> x; while (x==' ');
            input_s_expr ( x, y, infile);
        } //end read_lisp
    //...........................
        void input_s_expr (base prev, lisp& y,ifstream &infile)
        { //prev - ranee prochitannii simvol}
            if ( prev == ')' ) {cerr << " ! List.Error 1 " << endl; exit(1); }
            else if ( prev != '(' ) y = make_super_atom (prev,infile);
                 else input_seq (y,infile);
        } //end read_s_expr
    //...........................
        void input_seq ( lisp& y,ifstream &infile)
        {	base x;
            lisp p1, p2;

            if (!(infile >> x)) {cerr << " ! List.Error 2 " << endl; exit(1);}
            else {
                while  ( x==' ' ) infile >> x;
                if ( x == ')' ) y = NULL;
                else {
                    input_s_expr ( x, p1, infile);
                    input_seq ( p2, infile);
                    y = cons (p1, p2);
                }
            }
        } //end input_seq

    //-----------------------
    //...........................

        lisp make_super_atom (base prev,ifstream &infile)
        {
            if(prev == 'A')
            {
                infile >> prev;
                if( prev == 'N')
                {
                    infile >> prev;
                    if(prev == 'D')
                    {
                        return make_atom('*');
                    }else {cerr << " ! List.Error unidentified character  " << endl; exit(1);}
                } {cerr << " ! List.Error unidentified character  " << endl; exit(1);}
            }
            if(prev == 'O')
            {
                infile >> prev;
                if( prev == 'R')
                {
                    return make_atom('+');
                } {cerr << " ! List.Error unidentified character  " << endl; exit(1);}
            }
            if(prev == 'N')
            {
                infile >> prev;
                if( prev == 'O')
                {
                    infile >> prev;
                    if(prev == 'T')
                    {
                        return make_atom('-');
                    }else {cerr << " ! List.Error unidentified character  " << endl; exit(1);}
                } {cerr << " ! List.Error unidentified character  " << endl; exit(1);}
            }
            return make_atom(prev);
        }
        //----------------------

        //...................................
        void write_super_lisp (const lisp x)
        {//пустой список выводитс как ()
        if (isNull(x)) cout << " ()";
        else if (isAtom(x))
            switch (x->node.atom) {
        case '+':
            cout << ' ' << "OR";
            break;
        case '*':
            cout << ' ' << "AND";
            break;
        case '-':
            cout << ' ' << "NOT";
            break;
        default:
            cout << ' ' << x->node.atom;
            break;
        }
            else  { //непустой список}
                cout << " (" ;
                write_super_seq(x);
                cout << " )";
            }
        } // end write_lisp

        void write_super_seq (const lisp x)
        {//выводит последовательность элементов списка без обрамлzющих его скобок
            if (!isNull(x)) {
                write_super_lisp(head (x));
                write_super_seq(tail (x));
            }
        }
        //...........................
