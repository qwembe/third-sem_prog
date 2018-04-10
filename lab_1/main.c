#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 21. Построить синтаксический анализатор для понятия скобки.
скобки::=квадратные | круглые
квадратные:: = [ [ квадратные ] ( круглые ) ] | B
круглые::=( ( круглые ) [ квадратные ] ) | А
 */

FILE* f_in = NULL;  // global var
FILE* f_out = NULL; // global var
void init(); //
int doublePrintf(const char *s);
int doublePrintf_c(const char s);
int Error(int c);
char GetNPost();
int brackets();
int square(char s);
int round(char s);
void pretty_look();
int deepth = 0; // ! - global var
int flag = 0;



void init()
{

    f_out = fopen("f_out.txt","w");
    if (f_out == NULL)
    {
        exit(EXIT_FAILURE);
    }
    char ans;
    doublePrintf("Do you want read from file? (y/n)\n");
    while(f_in == NULL)
    {
        scanf("%s",&ans);
        switch (ans) {
        case 'y':
            f_in = fopen("f_in.txt","r");
            if(f_in == NULL) {Error(1);}
            break;
        case 'n':
            f_in = fopen("f_stdin.txt","w");
            if(f_in == NULL) {Error(1);}
            char c;
            scanf("%s",&c);
            fprintf(f_in,"%s",&c);
            fclose(f_in);
            f_in = fopen("f_stdin.txt","r");
            if(f_in == NULL) {Error(1);}
           break;
        default:
            doublePrintf("Enter y (yes) or n (no)\n");
            break;
        }
    }
}

int doublePrintf(const char* s)
{
    printf("%s",s);
    fprintf(f_out,"%s",s);
    return 0;
}

int doublePrintf_c(const char s)
{
    printf("%c",s);
    fprintf(f_out,"%c",s);
    return 0;
}

int Error(int c)
{
    switch (c) {
    case 1:
        doublePrintf("\n!- File not found.");
        exit(EXIT_FAILURE);
        break;              // while loading from file
    case 2:
        doublePrintf(" <--\n!- Not a right scobe.");
        exit(EXIT_FAILURE);
        break;
    case 3:
        doublePrintf("<--\n!- Expected '[' or ']'.");
        exit(EXIT_FAILURE);
        break;
    case 4:
        doublePrintf("<--\n!- Not a square scobe.");
        exit(EXIT_FAILURE);
        break;
    case 5:
        doublePrintf("<--\n!- Expected '(' or ')'.");
        exit(EXIT_FAILURE);
        break;
    case 6:
        doublePrintf("<--\n!- Not a round scobe.");
        exit(EXIT_FAILURE);
        break;
    default: doublePrintf("\n!- ****."); exit(EXIT_FAILURE); break;
    }
}

char GetNPost()
{
    char s;
    fread(&s,1,1,f_in);
    doublePrintf_c(s);
    return s;
}

int brackets();
int square(char s);
int round(char s);
void pretty_look();


void pretty_look(int option) //if option equals 1, that means entering recursy, else exit. uses deepth as global var;
{
    if (option) {++deepth ;} else {--deepth;};
    doublePrintf("\n");
    for (int i = 0; i < deepth; ++i)
    {
        doublePrintf("   ");
    }

}

int brackets() //returns 1 {скобки::=квадратные | круглые} else 0
{
    doublePrintf("Analising...\n ");
    //pretty_look(1);
    char s = GetNPost();
    if (round(s) || square(s))
    {
        doublePrintf("\nIt is scobe!");
        return 1;
    }
    else
    {
        Error(777);
    };
}

int square(char s)  //returns 1 {квадратные:: = [ [ квадратные ] ( круглые ) ] | B} else 0
{



    if (s == 'B') { pretty_look(0); return 1;}
    if (s == 'A' && !flag) { pretty_look(0); return 1;}
    flag = 1;

    if(s == '[')
    {
        s = GetNPost();
        if( s == '[')
        {
            pretty_look(1);
            s = GetNPost();
            if (square(s) == 1)
            {
                s = GetNPost();
                if (s == ']')
                {
                    s = GetNPost();
                    if (s == '(')
                    {
                        pretty_look(1);
                        s = GetNPost();
                        if(round(s) == 1)
                        {
                            s = GetNPost();
                            if (s == ')')
                            {
                                s = GetNPost();
                                if (s == ']')
                                {
                                    pretty_look(0);
                                    return 1;
                                } else {Error(3);};
                            } else {Error(5);};
                        } else {Error(6);};
                    } else {Error(5);};
                } else {Error(3);};
            } else {Error(4);};
        } else {Error(3);};
    }


    return 0;

}

int round(char s)  //returns 1 {круглые::=( ( круглые ) [ квадратные ] ) | А} else 0
{




    if (s == 'A') { pretty_look(0); return 1;}
    if (s == 'B' && !flag) { pretty_look(0); return 1;}
    flag = 1;


    if(s == '(')
    {
        s = GetNPost();
        if( s == '(')
        {
            pretty_look(1);
            s = GetNPost();
            if (round(s) == 1)
            {
                s = GetNPost();
                if (s == ')')
                {
                    s = GetNPost();
                    if (s == '[')
                    {
                        pretty_look(1);
                        s = GetNPost();
                        if(square(s) == 1)
                        {
                            s = GetNPost();
                            if (s == ']')
                            {
                                s = GetNPost();
                                if (s == ')')
                                {
                                    pretty_look(0);
                                    return 1;
                                } else {Error(5);};
                            } else {Error(3);};
                        } else {Error(4);};
                    } else {Error(3);};
                } else {Error(5);};
            } else {Error(6);};
        } else {Error(5);};
    }


    return 0;
}

int main()
{
    init();
    brackets();
}
