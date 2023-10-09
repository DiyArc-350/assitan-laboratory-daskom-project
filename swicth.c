/*
Andre ingin membuat kalkulator yang bisa menghitung volume kerucut, tabung, dan bola,
sehingga andre membutuhkan program yang bisa menghitung volume bidang-bidang tersebut.
Bantulah Andre dalam membuat program kalkulator volume. (jari jari, tinggi, dan volume menggunakan
float dan dalam bentuk cm; output dalam bentuk bilangan 2 angka dibelakang koma; menggunakan switch
case).
Hint :
Volume kerucut = 1/3  r ²t
Volume tabung =  r²t
Volume bola = 4/3  r³
phi = 3.14

[Sample Input]
Menu pilihan :
1. volume kerucut
2. volume tabung
3. volume bola
Pilih : 1
Jari jari (cm) : 4
Tinggi (cm) : 8

[Sample Output]
Volume kerucut : 133.97 cm^3
*/

#include<stdio.h>

#define phi 3.14

#define bola phi*r*r
void main(){

    float r;
    scanf("%f",&r);
    printf("%.2f",bola);
}
