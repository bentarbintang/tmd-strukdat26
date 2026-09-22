#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*Saya Bentar Bintang Umeir mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah Algoritma dan 
Struktur Data untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah 
dispesifikasikan. Aamiin.*/

typedef struct{
    char nama_simpul[301];
    char nama_simpul_orangtau[301];
    int value;
    int jumlah_konsekuensi_peluang;
    char peluang[11][81]; //menggunakan array 2d untuk menyimpan inputan peluang
} nilai;

typedef struct smp *alamatsimpul;
typedef struct smp{
    nilai kontainer;
    alamatsimpul sibling;
    alamatsimpul child;
}simpul;

typedef struct{
    simpul *root;
}tree;

void makeTree(nilai temp, tree *T);
void addChild(nilai temp, simpul *root);
void delAll(simpul *root);
void delChild(nilai temp, simpul *root);
simpul* findSimpul(nilai temp, simpul *root);
void printTreePreOrder(simpul *root);
void printTreePostOrder(simpul *root);
int isEqual(simpul *root1, simpul *root2);

//fungsi dan procedure tambahan
simpul* searchBFS(simpul *root, char target[]);
simpul* findParent(simpul *root, simpul *target);
int stringtoint(char str[]);
int hitungDigit(int angka);
void print_tree(simpul *root, int spasi);
int cek_jalur(simpul *root, simpul *sekarang, simpul *target);
void print_tree_pruning(simpul *root_pohon, simpul *root, int spasi, simpul *target_daun);
void print_peluang(simpul *root_pohon, simpul *root, simpul *target_daun, int *total_value);

//MESIN KATA
void start(char pita[]);
int eop(char pita[]);
void inc(char pita[]);
void reset();
char* getcw(); 
int getlen();