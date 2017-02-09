#include <iostream>
#include <fstream>
#include <string>
#include "huffmantree.h"
#include "manager.h"
using namespace std;

int main()
{
    manager *prog;
    string decide;
    string filename;
    while(true){
        cout<<"do you want to zip a file or unzip a file?! press 'zip' or 'unzip' "<<endl;
        cout<<"press end to exit"<<endl;
        cin>>decide;
        if(decide == "zip"){
            cout<<"enter the name of the file"<<endl;

            cin>>filename;
            filename += ".bin";
            //FILE* fp = fopen(filename.c_str(), "r");

            /*if(!fp){
                cout<<"file could not be opened. try later!";
                return 0;
            }*/
            prog = new manager();

            prog->huff->countTheChars();
            prog->huff->configureListB();
            prog->huff->configureListC();
            prog->huff->makeTree();
            prog->huff->preorderIteration(prog->huff->listB[0].point);
            prog->huff->makeBstofC();
            //fp = fopen(filename.c_str(), "r");
            prog->encoding();
            cout<<"done"<<endl;
        }
        else
        if(decide == "unzip"){
            //FILE *pf = fopen("zip.bin", "r");
            prog->decoding();
        }
        else
        if(decide == "end")
            return 0;
    }
}


