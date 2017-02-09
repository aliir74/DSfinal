#ifndef MANAGER_H
#define MANAGER_H


#include <iostream>
#include "huffmantree.h"
#include <math.h>
#include <string>
#include <fstream>

using namespace std;






class manager{

public:

     huffmantree *huff;
     string codes[256];

     manager(){
       huff = new huffmantree();
        for(int i = 0; i < 256; i++) {
            codes[i] = "";
        }
     }

     char getbyAscii(string in){
            int out;
            for (int f=0; f<8; f++){
                out += ((in[7-f]-'0')*pow(2,f));
            }
            //cout<<endl<<out<<endl;
            return (char)out;
        }


        string binaryOfAscii(char cc){
            string out;
            string invert = "";
            int difer;
            int cint = (int) ((unsigned char) cc);
            //cout<<cint<<endl;
//            while(cint/2 >= 1){
//                if(cint%2 == 1)
//                    invert += "1";
//                else
//                    invert += "0";
//                cint /= 2;
//            }
//            invert += "1";
//            difer = 8-invert.size();
//            for(int up=0; up<difer; up++)
//                invert += "0";
//           // cout<<invert<<endl;
//            for(int shit=invert.size()-1; shit>=0; shit--){
//                out += invert[shit];
//            }
            out = "";
            while(cint != 0) {
                out += (cint % 2) + '0';
                cint /= 2;
            }
            for(int i = out.length(); i < 8; i++) {
                out += '0';
            }
            invert = out;

            for(int i = 0; i < out.length(); i++) {
                invert[out.length() - i - 1] = out[i];
            }

            return invert;
        }

        void encoding(){
            char ch;
            string one;
            string eight;
            //FILE *nf = fopen("zip.bin", "w+");
            ifstream fp("/home/ali/DS/Huffman/my.bin", ios::binary);
            ofstream nf("/home/ali/DS/Huffman/zip.bin", ios::binary);
            if(!nf) cout<<"could not create a file to save the encoded one"<<endl;
            for(int index=0; index < huff->Csize; index++){
                //fputs(huff->listC[index].c.c_str(), nf);
                nf << huff->listC[index].c;
                string stcode = " " + huff->bstSearchen(huff->listC[index].c[0])+ " ";
                //fputs(stcode.c_str(), nf);
                nf << stcode;
            }
            //cout<<"here"<<endl;
            while(fp.get(ch)){


                //cout<<(char)ch<<endl;
                one += huff->bstSearchen(ch);
            }
            //cout<<one<<endl;
            //cout<<one.size()<<endl;
            int modeeight = one.size()%8;
            for(int leg=0; leg<((8-modeeight)%8); leg++){
                one += "1";
            }
            char khar = modeeight + '0';
//            fputc(khar, nf);
//            fputc(' ', nf);
            //cout<<one<<endl<<one.size();
            nf << khar << ' ';
            string nline = "$& ";
            //fputs(nline.c_str(),nf);
            nf << nline;
            //string limit = "L";
            //fputs(limit.c_str(),nf);

           // fputs(nline.c_str(),nf);
            int iter = 0;
            //cout<<(char)230<<endl;
            eight = "";
            cout << "one: " << one << endl;
            while(iter < one.size()){
                for(int j=iter; j<8+iter; j++){
                    eight += one[j];
                }
              //  fputc(getbyAscii(eight), nf);
                nf << getbyAscii(eight);
                eight = "";
                iter += 8;
            }
            //fclose(fp);
            //fclose(nf);
            fp.close();
            nf.close();
            //cout<<binaryOfAscii('g')<<endl;
        }



        void decoding(){
            char toread;
            int i = 0;
            string storage = "";
            string codeplace = "";
            int deadend;
            char first;
            char second;
            char thirdchar = 'a';
            string third = "";

            //FILE *fn = fopen("unzip.bin", "w");
            ifstream input("/home/ali/DS/Huffman/zip.bin", ios::binary);

            while(third != "$&"){
                if(third != ""){

                    codes[first] = third;
                    //cout<<"th"<<third<<endl;
                }

//                third = "";
                //first = fgetc(fp);
                input.get(first);
                //cout<<"f"<<first<<endl;
                //second = fgetc(fp);
                input.get(second);
                //cout<<"s"<<second<<endl;
//                do{
//                    third += thirdchar;
//                    thirdchar = fgetc(fp);
//                }while(thirdchar != ' ');
//                third.erase(0,1);
                input >> third;
//                codes[first] = third;
                input.get(second);
                cout << "aqqq: " << third << endl;
            }

            deadend = (8-(first-'0'))%8;
            cout<<"endofdic"<<deadend<<endl;
            //toread = fgetc(fp);
 /*           while(toread != EOF){
                storage += binaryOfAscii(toread);
                cout<<"store"<<storage<<endl;
                toread = fgetc(fp);
                //cout << 111 << endl;
            }
            */
            while(input.get(toread)) {
                storage += binaryOfAscii(toread);
//                cout <<"store" << storage << endl;
            }
            cout << storage.size() << endl;
            ofstream output("/home/ali/DS/Huffman/unzip.bin", ios::binary);
            for(int patu=0; patu<(storage.size()-deadend); patu++){
                codeplace += storage[patu];
//                cout<<"cplace "<<codeplace<<endl;
                for(int toshak=0; toshak<256;toshak++){
                    if( codes[toshak] != "" && codeplace == codes[toshak]){
//                        fputc((unsigned char)toshak, fn);
                        output << (unsigned char)(toshak);
                        cout << "code: " << codeplace << endl;
                        cout<<(char)toshak<<endl;
                        codeplace = "";
                        break;
                    }

                }
            }
            input.close();
            output.close();
            //fclose(fp);
         //   fclose(fn);
        }

};
#endif
