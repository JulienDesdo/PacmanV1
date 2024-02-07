#include "pch.h"
#include "matrix.h"
#include <iostream>


matrix::matrix() {
    // Allocation dynamique de la mémoire pour le tableau
    rows = 21;
    cols = 19;
    data = new int[rows * cols];

    for (int i = 0; i < rows * cols; i++) {
        data[i] = 0; 
    }
}


matrix::~matrix() {
    // Libération de la mémoire allouée dynamiquement
    delete[] data;
}

int matrix::get_value(int i, int j) {
    return data[i * cols + j];
}


void matrix::set_value(int i, int j, int value) {
    data[i * cols + j] = value;
}

void matrix::affich() { // ah si seulement MFC prenait en charge cout... => à creuser pour deboguage
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}


// Création de la MAP du JEU 
void matrix::initializeGraph() {
    //matrix graph; // ATTENTION si matrix graph() => déclaration de fonction...

    int vide = 0; 
    int block = 1;

    // 1ère ligne (indice 0) 
    for (int j = 0; j < 19; j++) {
        set_value(0, j, block);
    }

    // 2ème ligne 
    set_value(1, 0, block); 
    for (int j = 1; j <= 8; j++) {
        set_value(1, j, vide);
    }
    set_value(1, 9, block);
    for (int j = 10; j <= 17; j++) {
        set_value(1, j, vide);
    }
    set_value(1, 18, block);

    // 3ème ligne 
    set_value(2, 0, block);
    set_value(2, 1, vide);
    set_value(2, 2, block);
    set_value(2, 3, block);
    set_value(2, 4, vide);
    set_value(2, 5, block);
    set_value(2, 6, block);
    set_value(2, 7, block);
    set_value(2, 8, vide);
    set_value(2, 9, block);
    set_value(2, 10, vide);
    set_value(2, 11, block);
    set_value(2, 12, block);
    set_value(2, 13, block);
    set_value(2, 14, vide);
    set_value(2, 15, block);
    set_value(2, 16, block);
    set_value(2, 17, vide);
    set_value(2, 18, block);

    // 4ème ligne
    set_value(3, 0, block);
    set_value(3, 1, vide);
    set_value(3, 2, vide);
    set_value(3, 3, vide);
    set_value(3, 4, vide);
    set_value(3, 5, vide);
    set_value(3, 6, vide);
    set_value(3, 7, vide);
    set_value(3, 8, vide);
    set_value(3, 9, vide);
    set_value(3, 10, vide);
    set_value(3, 11, vide);
    set_value(3, 12, vide);
    set_value(3, 13, vide);
    set_value(3, 14, vide);
    set_value(3, 15, vide);
    set_value(3, 16, vide);
    set_value(3, 17, vide);
    set_value(3, 18, block);

    // 5ème ligne
    set_value(4, 0, block);
    set_value(4, 1, vide);
    set_value(4, 2, block);
    set_value(4, 3, block);
    set_value(4, 4, vide);
    set_value(4, 5, block);
    set_value(4, 6, vide);
    set_value(4, 7, block);
    set_value(4, 8, block);
    set_value(4, 9, block);
    set_value(4, 10, block);
    set_value(4, 11, block);
    set_value(4, 12, vide);
    set_value(4, 13, block);
    set_value(4, 14, vide);
    set_value(4, 15, block);
    set_value(4, 16, block);
    set_value(4, 17, vide);
    set_value(4, 18, block);

    // 6ème ligne
    set_value(5, 0, block);
    set_value(5, 1, vide);
    set_value(5, 2, vide);
    set_value(5, 3, vide);
    set_value(5, 4, vide);
    set_value(5, 5, block);
    set_value(5, 6, vide);
    set_value(5, 7, vide);
    set_value(5, 8, vide);
    set_value(5, 9, block);
    set_value(5, 10, vide);
    set_value(5, 11, vide);
    set_value(5, 12, vide);
    set_value(5, 13, block);
    set_value(5, 14, vide);
    set_value(5, 15, vide);
    set_value(5, 16, vide);
    set_value(5, 17, vide);
    set_value(5, 18, block);
    // 7ème ligne
    set_value(6, 0, block);
    set_value(6, 1, block);
    set_value(6, 2, block);
    set_value(6, 3, block);
    set_value(6, 4, vide);
    set_value(6, 5, block);
    set_value(6, 6, block);
    set_value(6, 7, block);
    set_value(6, 8, vide);
    set_value(6, 9, block);
    set_value(6, 10, vide);
    set_value(6, 11, block);
    set_value(6, 12, block);
    set_value(6, 13, block);
    set_value(6, 14, vide);
    set_value(6, 15, block);
    set_value(6, 16, block);
    set_value(6, 17, block);
    set_value(6, 18, block);
    // 8ème ligne
    set_value(7, 0, vide);
    set_value(7, 1, vide);
    set_value(7, 2, vide);
    set_value(7, 3, block);
    set_value(7, 4, vide);
    set_value(7, 5, block);
    set_value(7, 6, vide);
    set_value(7, 7, vide);
    set_value(7, 8, vide);
    set_value(7, 9, vide);
    set_value(7, 10, vide);
    set_value(7, 11, vide);
    set_value(7, 12, vide);
    set_value(7, 13, block);
    set_value(7, 14, vide);
    set_value(7, 15, block);
    set_value(7, 16, vide);
    set_value(7, 17, vide);
    set_value(7, 18, vide);
    // 9ème ligne
    set_value(8, 0, block);
    set_value(8, 1, block);
    set_value(8, 2, block);
    set_value(8, 3, block);
    set_value(8, 4, vide);
    set_value(8, 5, block);
    set_value(8, 6, vide);
    set_value(8, 7, block);
    set_value(8, 8, block);
    set_value(8, 9, block);
    set_value(8, 10, block);
    set_value(8, 11, block);
    set_value(8, 12, vide);
    set_value(8, 13, block);
    set_value(8, 14, vide);
    set_value(8, 15, block);
    set_value(8, 16, block);
    set_value(8, 17, block);
    set_value(8, 18, block);
    // 10ème ligne
    set_value(9, 0, vide);
    set_value(9, 1, vide);
    set_value(9, 2, vide);
    set_value(9, 3, vide);
    set_value(9, 4, vide);
    set_value(9, 5, vide);
    set_value(9, 6, vide);
    set_value(9, 7, block);
    set_value(9, 8, vide);
    set_value(9, 9, vide);
    set_value(9, 10, vide);
    set_value(9, 11, block);
    set_value(9, 12, vide);
    set_value(9, 13, vide);
    set_value(9, 14, vide);
    set_value(9, 15, vide);
    set_value(9, 16, vide);
    set_value(9, 17, vide);
    set_value(9, 18, vide);
    // 11ème ligne 
    set_value(10, 0, block);
    set_value(10, 1, block);
    set_value(10, 2, block);
    set_value(10, 3, block);
    set_value(10, 4, vide);
    set_value(10, 5, block);
    set_value(10, 6, vide);
    set_value(10, 7, block);
    set_value(10, 8, block);
    set_value(10, 9, block);
    set_value(10, 10, block);
    set_value(10, 11, block);
    set_value(10, 12, vide);
    set_value(10, 13, block);
    set_value(10, 14, vide);
    set_value(10, 15, block);
    set_value(10, 16, block);
    set_value(10, 17, block);
    set_value(10, 18, block);
    // 12ème ligne 
    set_value(11, 0, vide);
    set_value(11, 1, vide);
    set_value(11, 2, vide);
    set_value(11, 3, block);
    set_value(11, 4, vide);
    set_value(11, 5, block);
    set_value(11, 6, vide);
    set_value(11, 7, vide);
    set_value(11, 8, vide);
    set_value(11, 9, vide);
    set_value(11, 10, vide);
    set_value(11, 11, vide);
    set_value(11, 12, vide);
    set_value(11, 13, block);
    set_value(11, 14, vide);
    set_value(11, 15, block);
    set_value(11, 16, vide);
    set_value(11, 17, vide);
    set_value(11, 18, vide);
    
    // 13ème ligne
    set_value(12, 0, block);
    set_value(12, 1, block);
    set_value(12, 2, block);
    set_value(12, 3, block);
    set_value(12, 4, vide);
    set_value(12, 5, block);
    set_value(12, 6, vide);
    set_value(12, 7, block);
    set_value(12, 8, block);
    set_value(12, 9, block);
    set_value(12, 10, block);
    set_value(12, 11, block);
    set_value(12, 12, vide);
    set_value(12, 13, block);
    set_value(12, 14, vide);
    set_value(12, 15, block);
    set_value(12, 16, block);
    set_value(12, 17, block);
    set_value(12, 18, block);
    // 14ème ligne 
    set_value(13, 0, block);
    set_value(13, 1, vide);
    set_value(13, 2, vide);
    set_value(13, 3, vide);
    set_value(13, 4, vide);
    set_value(13, 5, vide);
    set_value(13, 6, vide);
    set_value(13, 7, vide);
    set_value(13, 8, vide);
    set_value(13, 9, block);
    set_value(13, 10, vide);
    set_value(13, 11, vide);
    set_value(13, 12, vide);
    set_value(13, 13, vide);
    set_value(13, 14, vide);
    set_value(13, 15, vide);
    set_value(13, 16, vide);
    set_value(13, 17, vide);
    set_value(13, 18, block);
    // 15ème ligne 
    set_value(14, 0, block);
    set_value(14, 1, vide);
    set_value(14, 2, block);
    set_value(14, 3, block);
    set_value(14, 4, vide);
    set_value(14, 5, block);
    set_value(14, 6, block);
    set_value(14, 7, block);
    set_value(14, 8, vide);
    set_value(14, 9, block);
    set_value(14, 10, vide);
    set_value(14, 11, block);
    set_value(14, 12, block);
    set_value(14, 13, block);
    set_value(14, 14, vide);
    set_value(14, 15, block);
    set_value(14, 16, block);
    set_value(14, 17, vide);
    set_value(14, 18, block);
    // 16ème ligne 
    set_value(15, 0, block);
    set_value(15, 1, vide);
    set_value(15, 2, vide);
    set_value(15, 3, block);
    set_value(15, 4, vide);
    set_value(15, 5, vide);
    set_value(15, 6, vide);
    set_value(15, 7, vide);
    set_value(15, 8, vide);
    set_value(15, 9, vide);
    set_value(15, 10, vide);
    set_value(15, 11, vide);
    set_value(15, 12, vide);
    set_value(15, 13, vide);
    set_value(15, 14, vide);
    set_value(15, 15, block);
    set_value(15, 16, vide);
    set_value(15, 17, vide);
    set_value(15, 18, block);
    // 17ème ligne 
    set_value(16, 0, block);
    set_value(16, 1, block);
    set_value(16, 2, vide);
    set_value(16, 3, block);
    set_value(16, 4, vide);
    set_value(16, 5, block);
    set_value(16, 6, vide);
    set_value(16, 7, block);
    set_value(16, 8, block);
    set_value(16, 9, block);
    set_value(16, 10, block);
    set_value(16, 11, block);
    set_value(16, 12, vide);
    set_value(16, 13, block);
    set_value(16, 14, vide);
    set_value(16, 15, block);
    set_value(16, 16, vide);
    set_value(16, 17, block);
    set_value(16, 18, block);
    // 18ème ligne 
    set_value(17, 0, block);
    set_value(17, 1, vide);
    set_value(17, 2, vide);
    set_value(17, 3, vide);
    set_value(17, 4, vide);
    set_value(17, 5, block);
    set_value(17, 6, vide);
    set_value(17, 7, vide);
    set_value(17, 8, vide);
    set_value(17, 9, block);
    set_value(17, 10, vide);
    set_value(17, 11, vide);
    set_value(17, 12, vide);
    set_value(17, 13, block);
    set_value(17, 14, vide);
    set_value(17, 15, vide);
    set_value(17, 16, vide);
    set_value(17, 17, vide);
    set_value(17, 18, block);
    // 19ème ligne 
    set_value(18, 0, block);
    set_value(18, 1, vide);
    set_value(18, 2, block);
    set_value(18, 3, block);
    set_value(18, 4, block);
    set_value(18, 5, block);
    set_value(18, 6, block);
    set_value(18, 7, block);
    set_value(18, 8, vide);
    set_value(18, 9, block);
    set_value(18, 10, vide);
    set_value(18, 11, block);
    set_value(18, 12, block);
    set_value(18, 13, block);
    set_value(18, 14, block);
    set_value(18, 15, block);
    set_value(18, 16, block);
    set_value(18, 17, vide);
    set_value(18, 18, block);
    // 20ème ligne 
    set_value(19, 0, block);
    set_value(19, 1, vide);
    set_value(19, 2, vide);
    set_value(19, 3, vide);
    set_value(19, 4, vide);
    set_value(19, 5, vide);
    set_value(19, 6, vide);
    set_value(19, 7, vide);
    set_value(19, 8, vide);
    set_value(19, 9, vide);
    set_value(19, 10, vide);
    set_value(19, 11, vide);
    set_value(19, 12, vide);
    set_value(19, 13, vide);
    set_value(19, 14, vide);
    set_value(19, 15, vide);
    set_value(19, 16, vide);
    set_value(19, 17, vide);
    set_value(19, 18, block);
    // 21ème ligne
    set_value(20, 0, block);
    set_value(20, 1, block);
    set_value(20, 2, block);
    set_value(20, 3, block);
    set_value(20, 4, block);
    set_value(20, 5, block);
    set_value(20, 6, block);
    set_value(20, 7, block);
    set_value(20, 8, block);
    set_value(20, 9, block);
    set_value(20, 10, block);
    set_value(20, 11, block);
    set_value(20, 12, block);
    set_value(20, 13, block);
    set_value(20, 14, block);
    set_value(20, 15, block);
    set_value(20, 16, block);
    set_value(20, 17, block);
    set_value(20, 18, block);
}

