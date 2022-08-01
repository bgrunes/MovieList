//
// Created by Owner on 7/31/2022.
//

#include "Heap.h"
#include <cmath>
#include <iostream>

Heap::Heap() {

}

void Heap::insert(Movie m) {
    vectorOfMovs.push_back(m);
    /* for (int i = 0; i < vectorOfMovs.size(); i++) {
        vectorOfMovs[i].printData();
    } */
    // cout << "insertion done! there are " << vectorOfMovs.size() << " items in the heap." << endl;
    float loc = vectorOfMovs.size() - 1;
    if (loc == 0) {
        return;
    }
    else {
        while (m.giveAverage() > vectorOfMovs[floor((loc - 1 )/ 2)].giveAverage()) {
            Movie placeholder = vectorOfMovs[floor((loc - 1)/ 2)];
            vectorOfMovs[floor((loc - 1 )/ 2)] = m;
            vectorOfMovs[loc] = placeholder;
            loc = floor(((loc) - 1) / 2);
            if (loc == 0) {
                return;
            }
        }
        /*
        for (int i = 0; i < vectorOfMovs.size(); i++) {
            vectorOfMovs[i].printData();
        }
        cout << endl;
         */
    }
}

Movie Heap::maxElem() {
    return vectorOfMovs[0];
}

void Heap::print() {
    for (int i = 0; i < 10; i++) {
        vectorOfMovs[i].printData();
    }
}
