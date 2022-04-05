#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;

static vector<char> ReadAllBytes(string filename);
const string PATH_bbs = "files/bbs/";
const string PATH_in = "files/input/";
const string PATH_out = "files/output/";
#include "BBS.cpp"
#include "tests.cpp"

int main(int argc, char* argv[]){
    
    unsigned long long p,q,blum_num;
    int len1,len2,len3;
    unsigned long long seed1,seed2,seed3;

    //blum_num, p, q
    //p=1707892411793;
    //q=2290939653701;
    p=687444379;
    q=419074319;
    blum_num=p*q;
    //max - 18446744073709551615 

    //ziarno
    seed1=6367859;
    seed2=7005359;
    seed3=9988229;

    //dlugosci bbs
    len1=20000;
    len2=1000000;
    len3=8000000;

    //myBBS(blum_num,len1,seed1,PATH_bbs+"out2.txt",true);
    //ascii2bits(PATH_in+"anna.txt",PATH_out+"anna_char.txt");

    myBBS(blum_num,len2,seed1,PATH_bbs+"key_sk.txt",true);
    bbs_encrypt(PATH_in+"text2.txt",PATH_out+"sk.txt",PATH_bbs+"key_sk.txt");

    //szyfrowanie i deszyfrowanie
    myBBS(blum_num,len2,seed1,PATH_bbs+"key1.txt",true);
    myBBS(blum_num,len2,seed2,PATH_bbs+"key2.txt",true);
    bbs_encrypt(PATH_in+"text1.txt",PATH_out+"cipher_1.txt",PATH_bbs+"key1.txt");
    bbs_encrypt(PATH_in+"cipher1.txt",PATH_out+"text_1.txt",PATH_bbs+"key1.txt");
    bbs_encrypt(PATH_in+"text2.txt",PATH_out+"cipher_2.txt",PATH_bbs+"key2.txt");
    bbs_encrypt(PATH_out+"cipher_2.txt",PATH_out+"text_2.txt",PATH_bbs+"key2.txt");
    bbs_encrypt(PATH_out+"cipher_1.txt",PATH_out+"text_1a.txt",PATH_bbs+"key1.txt");

    bits2ascii(PATH_out+"cipher_1.txt",PATH_out+"out_c1.txt");
    full_test(PATH_out+"out_c1.txt");
    bits2ascii(PATH_out+"cipher_2.txt",PATH_out+"out_c2.txt");
    full_test(PATH_out+"out_c2.txt");

    //generowanie plikow pod pomiary
    myBBS(blum_num,len3,seed1,PATH_bbs+"out0.txt",true);
    myBBS(blum_num,len3,seed2,PATH_bbs+"out1.txt", false);
    myBBS(blum_num,len1,seed1,PATH_bbs+"out2.txt", false);
    myBBS(blum_num,len1,seed2,PATH_bbs+"out3.txt", false);
    myBBS(blum_num,len1,seed3,PATH_bbs+"out4.txt", false);

    //wykonanie testow
    full_test(PATH_bbs+"out2.txt");
    full_test(PATH_bbs+"out3.txt");
    full_test(PATH_bbs+"out4.txt");
//*/
    return 0;
}

static vector<char> ReadAllBytes(string filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    if (!ifs) {
		cout << "File not found!"<<endl;
        exit(0);
	}

    fstream::pos_type pos = ifs.tellg();
    vector<char> result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);
    ifs.close();

    return result;
}