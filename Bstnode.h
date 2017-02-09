#ifndef bstnode_H
#define bstnode_H

#include <iostream>
#include "huffmantree.h"
#include "datastruct.h"

using namespace std;




class BstNode{
public:
    BstNode *LC;
    BstNode *RC;
    datastruct data;
    BstNode(){}

};

#endif
