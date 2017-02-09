#ifndef tnode_H
#define tnode_H

#include <iostream>
#include "huffmantree.h"

using namespace std;

class Tnode{

public:
    Tnode *right;
    Tnode *left;
    string sdata;
    int countofdata;
    string code;

        Tnode(){
            right = 0;
            left = 0;
            sdata = "";
            code = "";
        }




};
#endif
