#define POKER_BLOCK_SIZE 4
#define POKER_TAB_SIZE 16
#define SERIA_TAB_SIZE 6
#define max_size 20000

void full_test(string file_name){
    ifstream inFile(file_name);
    if (!inFile) {
		cout << "File not created!"<<endl;
        exit(0);
	}

    stringstream ss;
    ss << inFile.rdbuf();
    string text = ss.str();
    inFile.close();

    int num_of_0=0,num_of_1=0;
    int max_seria_0=0,max_seria_1=0;
    int now_seria_0=0,now_seria_1=0;
    int seria_tab_0[SERIA_TAB_SIZE];
    int seria_tab_1[SERIA_TAB_SIZE];
    for(int i=0;i<SERIA_TAB_SIZE;i++){
        seria_tab_0[i]=0;
        seria_tab_1[i]=0;
    }

    int j=0;
    int num,pow,sum=0;
    int poker_tab[POKER_TAB_SIZE];
    for(int i=0;i<POKER_TAB_SIZE;i++)poker_tab[i]=0;

    for(int i=0;i<text.size();i++){
        if(text[i]=='0') {
            num_of_0++;
            now_seria_0++;

            if(now_seria_1>max_seria_1){
                max_seria_1=now_seria_1;
            }
            if(now_seria_1>0){
                if(now_seria_1>=SERIA_TAB_SIZE)now_seria_1=SERIA_TAB_SIZE;
                seria_tab_1[now_seria_1-1]++;
            }

            now_seria_1=0;
        } else {
            num_of_1++;
            now_seria_1++;

            if(now_seria_0>max_seria_0){
                max_seria_0=now_seria_0;
            }
            if(now_seria_0>0){
                if(now_seria_0>=SERIA_TAB_SIZE)now_seria_0=SERIA_TAB_SIZE;
                seria_tab_0[now_seria_0-1]++;
            }

            now_seria_0=0;
        }

        if(++j%POKER_BLOCK_SIZE==0){
            num=0;
            pow=1;
            for(j=0;j<POKER_BLOCK_SIZE;j++){
                num+=(text[i-j]-ASCII_padd)*pow;
                pow*=2;
            }
            poker_tab[num]++;
            j=0;
        }
        if(i>=max_size-1) break;
    }
    
    int len=num_of_0+num_of_1;
    double s=0.0, a_const=(double)len/POKER_BLOCK_SIZE;
    for(int i=0;i<POKER_TAB_SIZE;i++){
        s+=(POKER_TAB_SIZE/a_const)*poker_tab[i]*poker_tab[i];
    }
    double poker=s-a_const;

    cout<<"file_name: "<<file_name<<endl;
    cout<<"size: "<<len<<endl;
    cout<<"num_of_0: "<<num_of_0<<" num_of_1: "<<num_of_1<<endl;

    cout<<"Serie 0: ";
    for(int i=0;i<SERIA_TAB_SIZE;i++)cout<<seria_tab_0[i]<<" ";
    cout<<endl<<"Serie 1: ";
    for(int i=0;i<SERIA_TAB_SIZE;i++)cout<<seria_tab_1[i]<<" ";
    cout<<endl;

    cout<<"max_seria_0: "<<max_seria_0<<" max_seria_1: "<<max_seria_1<<endl;
    cout<<"poker_value: "<<poker<<endl;
    
    //-----------------------------------------------------------------------------------------------------
    cout<<"Test poj bitow:\t";
    if(9725<num_of_0 && num_of_0<10275 && 9725<num_of_1 && num_of_1<10275) cout<<" PASSED "<<endl;
    else cout<<" ERROR "<<endl;
    //--
    cout<<"Test serii:\t";
    bool test_serii=true;
    int tab_test_ser_top[]={2685,1386,723,384,209,209};
    int tab_test_ser_bott[]={2315,1114,527,240,103,103};
    for(int i=0;i<SERIA_TAB_SIZE;i++){
        if(seria_tab_0[i]<tab_test_ser_bott[i] || seria_tab_0[i]>tab_test_ser_top[i]) test_serii=false;
        if(seria_tab_1[i]<tab_test_ser_bott[i] || seria_tab_1[i]>tab_test_ser_top[i]) test_serii=false;
    }
    if(test_serii) cout<<" PASSED "<<endl;
    else cout<<" ERROR "<<endl;
    //--
    cout<<"Test dl serii:\t";
    if(max_seria_0<26 && max_seria_1<26) cout<<" PASSED "<<endl;
    else cout<<" ERROR "<<endl;
    //--
    cout<<"Test pokerowy:\t";
    if(poker>2.16 && poker<46.17) cout<<" PASSED "<<endl;
    else cout<<" ERROR "<<endl;
    //-----------------------------------------------------------------------------------------------------
    cout<<endl;
}