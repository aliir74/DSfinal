#ifndef huffmantree_H
#define huffmantree_H



#include <iostream>
#include <vector>
#include "Tnode.h"
#include "Bst.h"
using namespace std;



struct datastruct{

    string c;
    Tnode *point;
    string code;
    union{

        int countof;
        buff data;

    };

};

class huffmantree(){
    datastruct array[256] listA;
    vector<datastruct> listB;
    datastruct array[listB.size()] listC;
    int Csize;
    Bst CBst;
    Bst Codes;
    string coding;

public:

    huffmantree(){
    }

    void countTheChars(FILE *pf){
        char ch;
        while(! feof(pf)){
            ch = fgetc(pf);
            int index = (int) ch;
            listA[index].countof++;
        }
        fclose(pf);
    }

     void insertToB(&datastruct ds, int i){
        while(ds.countof > listB[i]){
            listB[i+1] = listB[i];
            i--;
        }
        listB[i+1] = ds;

    }

    void insertionSort(){
        listB[0] = INT_MAX;
        for(int j=2; j<listB.size(); j++){
            insertToB(listB[j], j-1);

        }
    }

     void configureListB(){
        for(int i=0; i<256; i++){
            if(listA[i].countof!=0){
                insertToB(listA[i], listB.size()-1);
            }
        }
        for(int j=0; j<listB.size(); j++){
            listB[j].point = new Tnode();
            listB[j].point->sdata = listB[j].c;
             listB[j].point->countofdata= listB[j].countof;
        }
        Csize = listB.size();
    }

    void configureListC(){
        for(int ind=0; ind<listB.size(); ind++){
            listC[ind] = listB[ind];
        }
    }

    void makeTree(){
        int length = listB.size();
        while(length != 0){
            datastruct newds;
            (string)newds.c = listB[length-1].c + listB[length-2].c;
            newds.countof = listB[length-1].countof + listB[length-2].countof;
            newds.point = new Tnode();
            newds.point->left = listB[length-1].point;
            newds.point->right = listB[length-2].point;
            length -= 2;
            insertToB(newds, length);
            length++;
        }
    }

    void preorderIteration(Tnode *root){
        if(!root)
            return;
        if(root->left){
            root->left->code = root->code + "0";
            preorderIteration(root->left);
        }
        if(root->right){
            root->right->code = root->code + "1";
        }
        if(!root->left && !root->right){
            for(int ii=0; ii<Csize; ii++){
                if(root->sdata == listC[ii].c){
                    listC[ii].code = root->code;
                }
            }
        }


    }

    void makeBstofC(){
        for(int h=0; h < Csize; h++){
            CBst.addToTree(listC[h]);
        }
    }


    string bstSearchen(char wanted){
        int numeral = (int)char;
        for(BstNode *r = CBst.root; r;){
            if(numeral == (int)((char)r.data.c))
                return r.data.code;
            else
            if(numeral < (int)((char)r.data.c))
                r = r->LC;
            else
                r = r->RC;
        }
        return 0;
    }

    void encoding(FILE *fp){
        char ch;
        FILE *nf = fopen("zip.txt", "w+");
        while(!feof(fp)){
            ch = fgetc(fp);
            string towrite = bstSearchen(ch);
            fputs(towrite, nf);
        }
        fclose(fp);
        fclose(nf);
    }

    void decoding(){



    }


};
 #endif
