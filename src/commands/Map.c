#include <stdio.h>
#include "point.h"
#include "matrix.h"
#include "pcolor.h"
#include "queue.h"
#include "stack.h"

void initMap (Matrix *peta){
    int i,j;
    for (i=0;i<ROWS(*peta);i++){
        for (j=0;j<COLS(*peta);j++){
            if ((i == 0) | (j == 0) | (i == ROWS(*peta)-1) | (j == COLS(*peta)-1)){
                setElmt(peta,'*',i,j);
            }
            else{
                setElmt(peta,' ',i,j);
            }
        }
    }
}

void isiMap (Matrix *peta, int jumlah){
    int i,row,col;
    char val;
    for (i=0;i<jumlah;i++){
        scanf(" %c %d %d",&val,&row,&col);
        setElmt(peta,val,row,col);
    }
}

char posisiSkrg (POINT posNow, Matrix lokMat){
    int x = Absis(posNow), y = Ordinat(posNow);
    char posisi = ELMT(lokMat,x,y);
    return posisi;
}

void printBerwarna (int pilihan, char bangunan){
    switch (pilihan){
    case 1:
        print_yellow(bangunan);
        break;
    case 2:
        print_blue(bangunan);
        break;
    case 3:
        print_red(bangunan);
        break;
    case 4:
        print_green(bangunan);
        break;
    case 5:
        print_black(bangunan);
        break;
    default:
        printf("%c",bangunan);
        break;
    }
}

int posisiToIdx(char bangunan){
    int idx;
    if (bangunan == '8'){
        idx = 0;
    }
    else{
        idx = bangunan-64;
    }
    return idx;
}

boolean cekAdj (Matrix adjMat, char bangunan, char posisiSkrg){
    boolean adj = false;
    int letakAdjMat = posisiToIdx(bangunan), posisi = posisiToIdx(posisiSkrg);
    if (ELMT(adjMat,posisi,letakAdjMat) == '1'){
        adj = true;
    }
    return adj;    
}

boolean cekToDo (char bangunan, Queue toDo){
    char i;
    boolean ada = false;
    dequeue(&toDo,&i);
    if (i == bangunan){
        ada = true;
    }
    return ada;
}

void Map (Matrix adjMat, Matrix lokMat, POINT posNow, Queue toDo, Stack dropOff){
    int i,j,warna;
    char bangunan,drop;
    for (i=0;i<ROWS(lokMat);i++){
        for (j=0;j<COLS(lokMat);j++){
            warna = 6;
            bangunan = ELMT(lokMat,i,j);
            pop(&dropOff,&drop);
            if (bangunan!='*' && bangunan!=' '){
                warna = 5;
            }
            if (cekAdj(adjMat,bangunan,posisiSkrg(posNow,lokMat))){
                warna = 4;
            }
            if (cekToDo(bangunan,toDo)){
                warna = 3;
            }
            if (bangunan == drop){
                warna = 2;
            }
            if (bangunan == posisiSkrg(posNow,lokMat)){
                warna = 1;
            }
            printBerwarna(warna,bangunan);
        }
        printf("\n");   
    }
    printf("\n");   
}