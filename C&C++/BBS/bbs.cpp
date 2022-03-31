#define BYTE 8
#define ASCII_padd 48


//https://www.geeksforgeeks.org/multiply-large-integers-under-large-modulo/
unsigned long long power2Mod(unsigned long long x,unsigned long long num){
    unsigned long long y=0;
    unsigned long long tmp=x;

    while(tmp){
        if(tmp&1){
            y=(y+x)%num;
        }
        x=(2*x)%num;
        tmp>>=1;
    }
    return y;
}

unsigned char* myBBS(unsigned long long blum_num, int len, unsigned long long a, string file_name, bool bits){
    //NWD(blum_num, a) = 1
    if(__gcd(blum_num, a)!=1){
        cout<<"Wrong numbers!"<<endl;
        exit(0);
    } else if(!(1 <= a && a <= (blum_num-1))){
        cout<<"blum_num >= a!"<<endl;
        exit(0);
    }

    if(len<=0) len=BYTE;
    while(len%BYTE!=0)len++;
    
    ofstream outFile(file_name, ios::binary);
    if (!outFile) {
		cout << "File not created!"<<endl;
        exit(0);
	}

    int final_len=len;
    if(bits)final_len/=BYTE;

    unsigned char *result = new unsigned char[final_len];
    unsigned long long x=power2Mod(a,blum_num),j=0;
    
    if(bits){
        unsigned char tmp=(x%2);
        for(int i=1;i<len;i++){
            x=power2Mod(x,blum_num);

            tmp<<=1;
            tmp|=(x%2);

            if((i+1)%BYTE==0){
                result[j++]=tmp;
                tmp=0x00;
            }
        }
    } else {
        result[0]=(x%2)+ASCII_padd;
        for(int i=1;i<len;i++){
            x=power2Mod(x,blum_num);
            result[i]=(x%2)+ASCII_padd;
        }
    }

    if(outFile){
        outFile.write((char*)result,final_len);
        outFile.close();
    }
    return result;
}

void bbs_encrypt(string file_in,string file_out,string file_key){
    vector<char> result=ReadAllBytes(file_in);
    vector<char> key=ReadAllBytes(file_key);

    //cout<<result.size()<<" "<<key.size()<<endl;
    if(key.size()<result.size()){
        cout<<"Key size is too small!"<<endl;
        exit(0);
    }

    ofstream outFile(file_out, ios::binary);
    if (!outFile) {
		cout << "File not created!"<<endl;
	}

    for(int i=0;i<result.size();i++){
        result[i]^=key[i];
    }

    if(outFile){
        outFile.write(reinterpret_cast<char*>(&result[0]),result.size());
        outFile.close();
    }
}