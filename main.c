#include "header.h"

int main(){
    tree T;
    nilai temp;
    temp.value = 0;

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        char str[101];
        scanf(" %100[^\n]", str);

        start(str);
        strcpy(temp.nama_simpul, getcw()); //ambil string # pertama

        inc(str); //lanjut ke string berikutnya
        strcpy(temp.nama_simpul_orangtau, getcw()); //ambil string # kedua

        inc(str); //lanjut ke string berikutnya
        temp.value = stringtoint(getcw()); //ambil string # ketiga value yang sudah di ubah ke integer

        inc(str); //lanjut ke string berikutnya
        temp.jumlah_konsekuensi_peluang = stringtoint(getcw());

        for(int j = 0; j < temp.jumlah_konsekuensi_peluang; j++){ //menggunakan array 2d untuk menyimpan inputan peluang
            scanf(" %80[^\n]", temp.peluang[j]);
        }

        if(strcmp(temp.nama_simpul_orangtau, "null") == 0){ //jika orang tua null berarti inputan adalah akar
            makeTree(temp, &T); //masukkan ke tree
        } else { //jika inputan ada orang tua
            simpul *root = searchBFS(T.root, temp.nama_simpul_orangtau); //menggunakan metode bfs unutk mencari orang tua

            if(root != NULL){ //jika root ada 
                addChild(temp, root); //tambah anak anaknya
            }
        }
    }

    char daun[101];
    scanf("%s", daun); //inputan untuk peluang yang dipilih

    int spasi = 0;
    print_tree(T.root, spasi); //print tree full

    simpul *cari_daun = searchBFS(T.root, daun); //simpan inputan yang di acari untuk di pruning

    if(cari_daun != NULL){ //jika ada/ketemu
        print_tree_pruning(T.root, T.root, 0, cari_daun); //panggil tree logikanya mirip dengan tree full
        
        int total_value = 0;
        printf("peluang akhir yang diambil: %s\n", daun);
        printf("total value: %d\n", total_value);
        printf("semua peluang:\n");
        print_peluang(T.root, T.root, cari_daun, &total_value);
    }

    return 0;
}