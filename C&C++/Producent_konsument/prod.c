#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

#define Rozmiar 10 //rozmiar tablicy gl buf
#define BUF_SIZE 4096

int main(int ile,char **arg)
{
        srand(time(NULL));
        int N=atoi(arg[1]);
        sem_t *S_bin,*Sk,*Sp;
        int pid,e=0;
        int fd_Lpk;//liczba potencjalnych produktow
        int *Lpk;
        int fd_A,fd_B,fd_C,fd_D;
        int *A,*B,*C,*D; //znacznie opisane w instrukcji
        int fd_ws,fd_prod,fd_buff;
        int *ws,*prod,*buff;

        S_bin=sem_open("/sk_S_bin",O_CREAT,0600,1);
        Sk=sem_open("/sk_konsumenci",O_CREAT,0600,0);
        Sp=sem_open("/sk_producenci",O_CREAT,0600,Rozmiar);

        fd_Lpk=shm_open("/sk_Lpk",O_CREAT|O_RDWR,0600);
        fd_A=shm_open("/sk_A",O_CREAT|O_RDWR,0600);
        fd_B=shm_open("/sk_B",O_CREAT|O_RDWR,0600);
        fd_C=shm_open("/sk_C",O_CREAT|O_RDWR,0600);
        fd_D=shm_open("/sk_D",O_CREAT|O_RDWR,0600);
        fd_ws=shm_open("/sk_ws",O_CREAT|O_RDWR,0600);//wole sloty
        fd_prod=shm_open("/sk_prod",O_CREAT|O_RDWR,0600);//produkty
        fd_buff=shm_open("/sk_buff",O_CREAT|O_RDWR,0600);//buff glowny

        ftruncate(fd_Lpk,sizeof(int));
        ftruncate(fd_A,sizeof(int));
        ftruncate(fd_B,sizeof(int));
        ftruncate(fd_C,sizeof(int));
        ftruncate(fd_D,sizeof(int));
        ftruncate(fd_ws,Rozmiar*sizeof(int));
        ftruncate(fd_prod,Rozmiar*sizeof(int));
        ftruncate(fd_buff,Rozmiar*sizeof(int));
        Lpk=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_Lpk,0);
        A=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_A,0);
        B=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_B,0);
        C=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_C,0);
        D=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_D,0);
        ws=mmap(NULL,Rozmiar*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_ws,0);
        prod=mmap(NULL,Rozmiar*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_prod,0);
        buff=mmap(NULL,Rozmiar*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd_buff,0);

        if(Lpk==MAP_FAILED)e=1;
        if(A==MAP_FAILED)e=1;
        if(B==MAP_FAILED)e=1;
        if(C==MAP_FAILED)e=1;
        if(D==MAP_FAILED)e=1;
        if(S_bin==SEM_FAILED)e=2;
        if(Sk==SEM_FAILED)e=2;
        if(Sp==SEM_FAILED)e=2;
        if(ile!=2)e=3;
        if(N<1)e=3;

        if(e==1){
                perror("mmap2");
                exit(1);
        }
        else if(e==2){
                perror("sem_open");
                exit(2);
        }
        else if(e==3){
                perror("argumenty");
                exit(3);
        }

        pid=getpid();
        sem_wait(S_bin);
        *Lpk+=N;
        sem_post(S_bin);
        int tmp,pobraneWS,oddanePD;
        while(N)
        {
                printf("Producent %d czeka\n",pid);
                sem_wait(Sp);
                sem_wait(S_bin);

                pobraneWS=prod[*B];
                *B+=1;
                *B%=Rozmiar;
                sem_post(S_bin);

                tmp=rand()%200+10;
                buff[pobraneWS]=tmp;
                printf("Producent %d jest aktywny i zapisuje wartosc %d na miejsce %d\n(pracuje)\n",pid,tmp,pobraneWS);
                sleep(rand()%10+2);

                sem_wait(S_bin);
                oddanePD=*C;
                *C+=1;
                *C%=Rozmiar;
                prod[oddanePD]=pobraneWS;
                sem_post(S_bin);
                sem_post(Sk);
                printf("Producent %d konczy prace i zapelnia slot nr %d\n",pid,oddanePD);
                N-=1;
        }
        printf("Producent %d nie ma nic do zrobienia\n",pid);
        sem_close(S_bin);
        sem_close(Sk);
        sem_close(Sp);
        sem_unlink("/S_bin");
        sem_unlink("/Sk");
        sem_unlink("/Sp");
        return 0;
}
