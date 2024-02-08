#ifndef MATRIX_H
#define MATRIX_H

class matrix {
private:
    int* data;
    int rows, cols;

public:
    matrix();
    ~matrix();

    int matrix::get_value(int i, int j);
    void matrix::set_value(int i, int j, int value);
    void matrix::initializeGraph();
    void matrix::affich();

    
};






#endif // MATRIX_H


