/*Reza sedang ingin login ke akun sosial media, ternyata dia lupa dengan kata sandi sehingga ia harus
memulihkan kata sandinya dengan cara menjawab pertanyaan pemulihan akun. Pertanyaan yang tersedia adalah
1. Siapa nama kucing peliharaan saya? 2. Siapa nama ibu kandung saya?.
Dengan menjawab pertanyaan tersebut reza dapat memulihkan kata sandinya. Buatlah program sesuai
dengan persoalan diatas (buat jawaban untuk 2 pertanyaan diatas)
[Sample Input]
1. Siapa nama kucing peliharaan saya : Miko
2. Siapa nama ibu kandung saya : Siti
Jawaban anda benar!!

== silahkan buat kata sandi baru ==
Kata sandi baru : Daskom kece
[Sample Output]
Kata sandi baru (Daskom kece) telah dibuat!!
*/

#include<stdio.h>
#include<string.h>

void main(){

char pets[1],mom[20],neww[20];

printf("=================\n");
printf("=CHANGE PASSWORD=\n");
printf("=================\n");

//proses untuk input nama
printf("Siapa nama kucing peliharaan saya ?:  ");
gets (pets);
printf("%s",pets);
printf("Siapa nama ibu kandung saya ?: ");
gets(mom);
    if(strcmp(pets,"miko" )==0 && strcmp(mom , "siti")==0){
        printf("Silahkan masukan pasword baru kalian : ");
        gets(neww);
        printf("Kata sandi baru %s telah dibuat!!",neww);
    }
    else{
        printf("maaf jawaban anda salah");
    }
}
