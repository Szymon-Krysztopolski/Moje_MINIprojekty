data=[]
header=[]
types=[]

order=[1,0,4,2,3] #AS > Damage > TTL > HMC > Winrate
borders=[
    (18.,17.,16.), #damage
    (3.,2.), #AS
    (9.,7.,5.), #HMC
    (50.5,49.), #Winrate
    (4.,6.,8.) #TTL
]
TERMS=2 #id, names

def convert_AS(s):
    if s=="Slow":
        return 1
    elif s=="Normal":
        return 2
    elif s=="Fast":
        return 3
    else:
        return s
    

def ranking(step,data,result):
    i=order[step]
    
    rank=[]
    for _ in range(len(borders[i])+1):
        rank.append([])
        
    for variant in data:
        j=0
        for b in borders[i]:
            if(types[i]=='g'):
                if(variant[TERMS+i]>=b):
                    break
            else:
                if(variant[TERMS+i]<=b):
                    break
            j+=1
        rank[j].append(variant)

    
    if(step<len(order)-1):
        for tab in rank:
            if(tab!=[]):
                ranking(step+1,tab,result)
    else:
        result.append(rank)
    
    if(step==0):
        return result
    
def show_ranking(tab):
    if tab==[]:
        return
    
    if(isinstance(tab[0], int)):
        print(tab)
    else:
        for i in tab:
            show_ranking(i)

def main():
    global types, header
    
    file=open("data.txt",'r')
    types=file.readline().split()
    header=file.readline().split()
    
    for line in file:
        tmp=line.replace(',','.').split()
        tmp[3]=convert_AS(tmp[3])
        tmp[0]=int(tmp[0])
        tmp[TERMS:]=list(map(float,tmp[TERMS:]))
        
        data.append(tmp)
    file.close()
    
    if(len(order)!=len(data[0])-TERMS):
        print("Error")
        exit(0)
        
    result=ranking(0,data,[])
    #print("wynik: ",result)
    show_ranking(result)


if __name__=="__main__":
    main()