#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import csv
import numpy
import matplotlib.ticker as tick

head=2
fsize=10
maxPok=200
step_of_markers=20

xscale=0.001
xmin=60
xmax=500000
yscale=100
ymin=0.6
ymax=1

ox2=numpy.arange(0,1.1,0.2)
ox2*=maxPok

data=[]

files=['1evolrs.csv','1coevrs.csv','2coevrs.csv','1coev.csv','2coev.csv']
names=['1-Evol-RS','1-Coev-RS','2-Coev-RS','1-Coev','2-Coev']
styles=['>','<','o','^','D']

def yformat(x, pos):
    return '{:.5g}'.format(x*100)

def main():
    fig = plt.figure(figsize=(10, 8))
    
    ax1=plt.subplot(1, 2, 1)
    ax1.grid(linestyle='dotted')
    
    ax1.set_xlim([xmin*xscale,xmax*xscale])
    ax1.set_ylim([ymin*yscale,ymax*yscale])

    ax1.set_xlabel("Rozegranych gier (X 1000)",size=str(fsize))
    ax1.set_ylabel("Odsetek wygranych gier [%]",size=str(fsize))
    
    ax3=plt.subplot(1, 2, 2)
    ax3.grid(linestyle='dotted')
    
    for file,name,style in zip(files,names,styles):
        with open('dane/'+file, 'r') as csvfile:
            csvreader = csv.DictReader(csvfile)
            headers=csvreader.fieldnames
            measurements=[]
            avg=0.0
            licznik=0
            
            for row in csvreader:
                for i in range(head,len(row)):
                    avg+=float((row[headers[i]]))
                avg=avg/(len(row)-1)
                measurements.append([
                    float(row[headers[0]]),
                    float(row[headers[1]])*xscale,
                    avg*yscale
                ])
                licznik+=1
                tmp=[]
                
                if(licznik==maxPok):
                    for i in range(head,len(row)):
                        tmp.append(float(row[headers[i]]))
                    data.append(tmp)
        measurements=numpy.array(measurements)
        
        ax1.plot(
            list(map(float,measurements[:,1])),
            list(map(float,measurements[:,2])),
            marker=style,
            markevery=step_of_markers,
            markersize=8,
            markeredgecolor = "black", 
            markeredgewidth = 0.75,
            label=name
        )

    ax1.legend(loc='lower right',prop={'size': 15},numpoints = 2)
    
    ax2=ax1.twiny()
    ax2.set_xticks(ox2)
    ax2.set_xlabel("Pokolenie")
    
    ax3.boxplot(
        data,
        
        notch=True, 
        sym='+', 
        patch_artist=True,
        boxprops=dict(facecolor=(0,0,0,0), color="blue"),
        whiskerprops=dict(color="blue", linestyle=(0, (5, 5))),
        flierprops=dict(color="blue", markeredgecolor="blue"),
        medianprops=dict(color="red"),
        showmeans=True,
        meanprops=dict(markerfacecolor="blue", marker="o",
        markeredgecolor = "black")
    )
    
    loc = tick.MultipleLocator(0.05)
    ax3.yaxis.set_major_locator(loc)
    ax3.set_ylim([ymin,ymax])
    ax3.yaxis.set_major_formatter(tick.FuncFormatter(yformat)) 
    ax3.yaxis.tick_right()
    ax3.set_xticklabels(names,rotation=30)

    plt.savefig('wykresy.pdf')
    plt.show()
    plt.close()

if __name__ == '__main__':
    main()