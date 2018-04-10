#ifndef VECBT_H
#define VECBT_H

#include <iostream>
#include <cstdlib>

//size_t PTRNULL = 1000;

template <typename elem>
struct Node {
    elem info;
    unsigned int wight;
    unsigned int number;
    size_t pr; //parent
    size_t lt; //left
    size_t rt; //right
};

template <typename T> bool vec_isNull(size_t index, Node<T>* b); //проверка на нулевой узел
template <typename T> T vec_RootBT (Node<T>* b, size_t index); //взятие корня поддерева
template <typename T> size_t vec_Left (Node<T>* b,size_t index); //взятие индекса правого узла
template <typename T> size_t vec_Right (Node<T>* b, size_t index);//взятие индекса левого узла
template <typename T> size_t vec_ConsBT(T x, size_t lst,  size_t rst,size_t pr,unsigned int wight,unsigned int number, Node<T>* b, size_t index);//добавление узла в список на базе вектора
template <typename T> void vec_destroy (size_t index, Node<T>* b); // удаление дерева
template <typename T> size_t vec_readBT(size_t index, Node<T>* b);// считывание данных с клавиатуры
template <typename T> void vec_outBT(size_t index, Node<T>* b); // вывод дерева на монитор
template <typename T> void vec_displayBT (size_t index, Node<T>* b, size_t n); // вывод "изображения" дерева на монитор

extern std::ofstream log;

#endif // VECBT_H
