#ifndef MATRIX_H
#define MATRIX_H
#include "pos.h"

class matrix {
public:
    int* data;
    int rows, cols;

public:
    matrix();
    ~matrix();

    int matrix::get_value(int i, int j);
    void matrix::set_value(int i, int j, int value);
    void matrix::initializeGraph();
    
};






#endif // MATRIX_H


