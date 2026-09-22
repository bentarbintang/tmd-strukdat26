#include "header.h"

int indeks;
int wlen;
char cw[101];

void start(char pita[]){
    // set index dan panjang kata menjadi 0
    indeks = 0;
    wlen = 0;

    while (pita[indeks] == '#'){ // ignore blank
        indeks++;
    }
    
    // ambil kata masukkan dalam current word
    while ((pita[indeks] != '#') && (eop(pita) == 0)){
        cw[wlen] = pita[indeks];
        wlen++;
        indeks++;
    }
    cw[wlen] = '\0'; // akhiri dengan null terminator
}

//cek eop
int eop(char pita[]){
    if(pita[indeks] == '\0'){ // jika '\0' return 1 arti \0 adalah akhir string
        return 1;
    } else{
        return 0; // jika bukan '.' kembalikan 0
    }
}

// reset current word
void reset(){
    wlen = 0; // kembalikan panjang kata menjadi 0
    cw[wlen] = '\0'; // set current word menjadi null (siap diisi)
}

// pindah next kata
void inc(char pita[]){
    wlen = 0; // set panjang kata jadi 0 (memastikan)
    while (pita[indeks] == '#'){ // ignore blank
        indeks++;
    }

    // masukkan kata baru
    while ((pita[indeks] != '#') && pita[indeks] != ';' && (eop(pita) == 0)){
        cw[wlen] = pita[indeks];
        wlen++;
        indeks++;
    }
    cw[wlen] = '\0'; // akhiri lagi
}

// mengembalikan current word
char* getcw(){
    return cw;
}

// mengembalikan panjang current word
int getlen(){
    return wlen;
}

void makeTree(nilai temp, tree *T){
    simpul *node;
    node = (simpul *) malloc (sizeof (simpul));
    node->kontainer = temp;

    node->sibling = NULL;
    node->child = NULL;
    
    (*T).root = node;
    node = NULL;
}

void addChild(nilai temp, simpul *root){
    if(root != NULL){
        /* jika simpul root tidak kosong,
        berarti dapat ditambahkan simpul anak */
        simpul *baru;
        baru = (simpul *) malloc (sizeof (simpul));
        baru->kontainer = temp;
        baru->child = NULL;

        if(root->child == NULL){ //belum punya anak
            /* jika simpul root belum memiliki simpul 
            anak maka simpul baru menjadi anak pertama */

            baru->sibling = NULL;
            root->child = baru;
    } else{
        if(root->child->sibling == NULL){
            /* jika simpul root memiliki
            anak yang belum memiliki saudara, maka
            simpul baru menjadi anak kedua */

            baru->sibling = root->child;
            root->child->sibling = baru;
            baru = NULL;
        } else {
            simpul *last = root->child;
            /* mencari simpul anak terakhir
            karena akan dikaitkan dengan simpul
            baru sebagai simpul anak terakhir yang               
            baru, simpul anak terakhir adalah yang
            memiliki sibling simpul anak pertama,
            maka selama belum sampai pada simpul
            anak terakhir, penunjuk last akan
            berjalan ke simpul anak berikutnya */

            while(last->sibling != root->child){
                last = last->sibling;
            }
                baru->sibling = root->child;
                last->sibling = baru;
                baru = NULL;
            }
        }
    }
}

void delAll(simpul *root){
    if(root != NULL){
        /* jika simpul root tidak kosong */
        if(root->child != NULL){
            if(root->child->sibling == NULL){
                /* jika hanya memiliki satu simpul anak */
                delAll(root->child);
                free(root);
            } else {
                simpul *bantu;
                simpul *proses;
                bantu = root->child;

                while(bantu->sibling != root->child){
                    proses = bantu;
                    bantu = bantu->sibling;
                    delAll(proses);
                }
                //proses anak terakhir
                if(bantu != NULL){
                    delAll(bantu);
                }
                free(root);
            }
        } else {
            free(root);
        }
    }
}

void delChild(nilai temp, simpul *root){
    if(root != NULL){
        simpul *hapus = root->child;
        if(hapus != NULL){
            if(hapus->sibling == NULL){ //jika cuma punya 1 anak
                if(strcmp(root->child->kontainer.nama_simpul, temp.nama_simpul) == 0){
                    delAll(root->child);
                    root->child = NULL;
                } else {
                    printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            } else { //jika punya banyak anak
                simpul *prev = NULL;
                int ketemu = 0;
                while((hapus->sibling != root->child) && (ketemu == 0)){
                    if(strcmp(hapus->kontainer.nama_simpul, temp.nama_simpul) == 0){
                        ketemu = 1;
                    } else {
                        prev = hapus;
                        hapus = hapus->sibling;
                    }
                }
                if((ketemu == 0) && strcmp(hapus->kontainer.nama_simpul, temp.nama_simpul) == 0){
                    ketemu = 1;
                }
                if(ketemu == 1){
                    simpul *last = root->child;
                    while(last->sibling != root->child){
                        last = last->sibling;
                    }

                    if(prev == NULL){
                        if((hapus->sibling == last) && (last->sibling == root->child)){
                            root->child = last;
                            last->sibling = NULL;
                        } else { //jika anak memliki lebih dari 1 simpul
                            root->child = hapus->sibling;
                            last->sibling = root->child;
                        }
                    } else {
                        if((prev == root->child) && (hapus->sibling == root->child)){
                            root->child->sibling = NULL;
                        } else {
                            prev->sibling = hapus->sibling;
                            hapus->sibling = NULL;
                        }
                    }
                    delAll(hapus);
                } else {
                    printf("tidak ada simpul anak dengan kontianer karakter masukan\n");
                }
            }
        }
    }
}

simpul* findSimpul(nilai temp, simpul *root){
    simpul *hasil = NULL;
    if(root != NULL){
        if(strcmp(root->kontainer.nama_simpul, temp.nama_simpul) == 0){
            hasil = root;
        } else {
            simpul *bantu = root->child;
            if(bantu != NULL){
                if(bantu->sibling == NULL){ //jika punya 1 anak
                    if(strcmp(bantu->kontainer.nama_simpul, temp.nama_simpul) == 0){
                        hasil = bantu;
                    } else {
                        hasil = findSimpul(temp, bantu);
                    }
                } else { //jika banyak anak
                    int ketemu = 0;
                    while((bantu->sibling != root->child) && (ketemu == 0)){
                        if(strcmp(bantu->kontainer.nama_simpul, temp.nama_simpul) == 0){
                            hasil = bantu;
                            ketemu = 1;
                        } else {
                            hasil = findSimpul(temp, bantu);
                            bantu = bantu->sibling;
                        }
                    }
                    if(ketemu == 0){
                        if(strcmp(bantu->kontainer.nama_simpul, temp.nama_simpul) == 0){
                            hasil = bantu;
                        } else {
                            hasil = findSimpul(temp, bantu);
                        }
                    }
                }
            }
        }
    }
    return hasil;
}

void printTreePreOrder(simpul *root){
        if(root != NULL){
        printf(" %s ", root->kontainer);
        simpul *bantu = root->child;
        if(bantu != NULL){
            if(bantu->sibling == NULL){
                /*jika memiliki satu simpul anak*/
                printTreePreOrder(bantu);
            } else{
                /*jika memiliki banyak simpul anak*/

                /*mencetak simpul anak*/
                while(bantu->sibling != root->child){
                    printTreePreOrder(bantu);
                    bantu = bantu->sibling;
                }
                /*memproses simpul anak
                terakhir karena belum terproses
                dalam pengulangan*/
                printTreePreOrder(bantu);
            }
        }
    }
}

void printTreePostOrder(simpul *root){
    if(root != NULL){
        simpul *bantu = root->child;

        if(bantu != NULL){
            if(bantu->sibling == NULL){
                /*jika memiliki satu simpul anak*/
                printTreePostOrder(bantu);
            } else{
                /*jika memiliki banyak simpul anak*/

                /*mencetak simpul anak*/
                while(bantu->sibling !=
                    root->child){
                    printTreePostOrder(bantu);
                    bantu = bantu->sibling;
                }
                /*memproses simpul anak
                terakhir karena belum terproses
                dalam pengulangan*/

                printTreePostOrder(bantu);
            }
        }
        printf(" %s ", root->kontainer);
    }
}

int isEqual(simpul *root1, simpul *root2){
    int hasil = 1;
    if((root1 != NULL) && (root2 != NULL)){
        if(strcmp(root1->kontainer.nama_simpul, root2->kontainer.nama_simpul)){
            hasil = 0;
        } else {
            if((root1->child != NULL)&&(root2->child != NULL)){

                if(root1->child->sibling == NULL){
                    /*jika memiliki satu simpul anak*/
                    hasil = isEqual(root1->child,
                    root2->child);
                } else {
                    /*jika memiliki banyak simpul
                    anak*/
                    simpul *bantu1 = root1->child;
                    simpul *bantu2 = root2->child;

                    while(bantu1->sibling != root1->child){
                        if((bantu1 != NULL) &&(bantu2 != NULL)){
                            hasil = isEqual(bantu1, bantu2);
                            bantu1 = bantu1->sibling;
                            bantu2 = bantu2->sibling;
                        } else {
                            hasil = 0;
                            break;
                        }
                    }
                    /*memproses simpul anak terakhir karena belum terproses dalam pengulangan*/
                    hasil = isEqual(bantu1, bantu2);
                }
            }
        }
    } else {
        if((root1 != NULL) || (root2 != NULL)){
            hasil = 0;
        }
    }
    return hasil;
}


simpul* searchBFS(simpul *root, char target[]){
    simpul *hasil = NULL; //deklarasi penampung hasil
    
    if(root != NULL){
        simpul* queue[100]; //menggunakan queue untuk menyimpan jalur yang dilalui
        int depan = 0;
        int belakang = 0;
        
        queue[belakang] = root;
        belakang++;
        
        int ketemu = 0; //flag penanda
        while((depan < belakang) && (ketemu == 0)){
            simpul *curr = queue[depan];
            depan++;
            
            if(strcmp(curr->kontainer.nama_simpul, target) == 0){
                hasil = curr;
                ketemu = 1; // Hentikan while loop
            } else {
                simpul *bantu = curr->child;
                if(bantu != NULL){
                    if(bantu->sibling == NULL){ //jika punya 1 anak
                        queue[belakang] = bantu;
                        belakang++;
                    } else { //jika punya banyak anak
                        while(bantu->sibling != curr->child){
                            queue[belakang] = bantu;
                            belakang++;
                            bantu = bantu->sibling;
                        }
                        queue[belakang] = bantu;
                        belakang++;
                    }
                }
            }
        }
    }
    return hasil; 
}


simpul* findParent(simpul *root, simpul *target){
    simpul *hasil = NULL;
    if((root != NULL) && (target != NULL)){
        simpul *bantu = root->child;
        if(bantu != NULL){
            if(bantu->sibling == NULL){ // jika punya 1 anak
                if(bantu == target){
                    hasil = root;
                } else {
                    hasil = findParent(bantu, target);
                }
            } else { // jika banyak anak
                int ketemu = 0;
                while((bantu->sibling != root->child) && (ketemu == 0)){
                    if(bantu == target){
                        hasil = root;
                        ketemu = 1;
                    } else {
                        hasil = findParent(bantu, target);
                        // Cek apakah parent sudah ketemu di kedalaman rekursif
                        if(hasil != NULL){
                            ketemu = 1;
                        }
                        bantu = bantu->sibling;
                    }
                }
                if(ketemu == 0){
                    if(bantu == target){
                        hasil = root;
                    } else {
                        hasil = findParent(bantu, target);
                    }
                }
            }
        }
    }
    return hasil;
}


int stringtoint(char str[]) {
    int hasil = 0;
    int i = 0;
    while (str[i] != '\0') {
        hasil = hasil * 10 + (str[i] - '0');
        i++;
    }
    return hasil;
}

int hitungDigit(int angka){
    int hitung = 0;
    if(angka == 0){
        return 1; // Angka 0 dihitung 1 digit
    }

    while(angka > 0){
        hitung++;
        angka = angka / 10; // Dibagi 10 terus sampai habis
    }
    return hitung;
}

void print_tree(simpul *root, int spasi){
    if(root != NULL){

        int makslen = 0;
        simpul *cari = root;

        // cari spasi paling panjang
        // jika tidak punya sibling
        if(cari->sibling == NULL){
            int len_root = strlen(root->kontainer.nama_simpul) + 3 + hitungDigit(root->kontainer.value);
            makslen = len_root;
            
            for(int i = 0; i < root->kontainer.jumlah_konsekuensi_peluang; i++){
                int len_peluang = strlen(root->kontainer.peluang[i]) + 2; // +2 karena ada []
    
                if(len_peluang > makslen){
                    makslen = len_peluang;
                }
            }
        } else {
            do { //loop do while saya gunakan karena pada addchild menggunakan konsep circular dimana anak terakhir terhubung ke anak pertama
                int len_root = strlen(cari->kontainer.nama_simpul) + 3 + hitungDigit(cari->kontainer.value);
                if(len_root > makslen){
                    makslen = len_root;
                }
                
                for(int i = 0; i < cari->kontainer.jumlah_konsekuensi_peluang; i++){ //loop sebanyak jumlah inputan peluang
                    int len_peluang = strlen(cari->kontainer.peluang[i]) + 2; // +2 karena ada []
        
                    if(len_peluang > makslen){ //jika di peluang ada yang paling panjang bandingkan dengan len dari baris 1
                        makslen = len_peluang; //isi makslen ke len peluang
                    }
                }
                cari = cari->sibling; //traversal ke siblingnya
            } while (cari != root && cari != NULL); //berjalan selama cari tidak sama dengan simpul paling awal
        }

        //print root
        for(int i = 0; i < spasi; i++){
            printf(" ");
        }
        printf("%s - %d\n", root->kontainer.nama_simpul, root->kontainer.value);
        
        //print peluang
        for(int i = 0; i < root->kontainer.jumlah_konsekuensi_peluang; i++){
            for(int j = 0; j < spasi; j++){
                printf(" ");
            }
            printf("[%s]\n", root->kontainer.peluang[i]);
        }
        
        printf("\n");

        simpul *bantu = root->child;

        if(bantu != NULL){
            if(bantu->sibling == NULL){

                /*jika memiliki satu simpul anak*/
                print_tree(bantu, spasi + makslen);

            } else{
                /*jika memiliki banyak simpul anak*/
                /*mencetak simpul anak*/

                while(bantu->sibling != root->child){
                    print_tree(bantu, spasi + makslen);
                    bantu = bantu->sibling;
                }

                /*memproses simpul anak terakhir karena 
                belum terproses dalam pengulangan*/
                print_tree(bantu, spasi + makslen);
            }
        }
    }
}

int cek_jalur(simpul *root, simpul *sekarang, simpul *target){
    if(sekarang == NULL || target == NULL){
        return 0;
    }

    // Jika simpul sekarang adalah simpul target itu sendiri
    if(sekarang == target){
        return 1;
    }   
    
    // Cari tahu lewat orang tua si target secara berjenjang ke atas
    simpul *bantu = target;
    while (bantu != NULL) {
        simpul *parent = findParent(root, bantu);
        if (parent == sekarang) {
            return 1; // Ketemu! Simpul sekarang adalah leluhur dari target
        }
        bantu = parent; // Naik terus ke atas
    }
    
    return 0; // Jika tidak ada hubungan darah ke target
}

void print_tree_pruning(simpul *root_pohon, simpul *root, int spasi, simpul *target_daun){
    if(root != NULL) {
        // Cek dulu apakah simpul saat ini masuk dalam jalur menuju target
        if (cek_jalur(root_pohon, root, target_daun) == 0) {
            return; // Jika tidak masuk jalur, langsung keluar
        }

        //logikanya sama seperti print tree biasa
        int makslen = 0;
        simpul *cari = root;

        if(cari->sibling == NULL) {
            int len_root = strlen(root->kontainer.nama_simpul) + 3 + hitungDigit(root->kontainer.value);
            makslen = len_root;
            
            for(int i = 0; i < root->kontainer.jumlah_konsekuensi_peluang; i++) {
                int len_peluang = strlen(root->kontainer.peluang[i]) + 2;
                if(len_peluang > makslen) {
                    makslen = len_peluang;
                }
            }
        } else {
            do {
                // Hanya hitung kontribusi spasi jika simpul saudara (sibling) ini masuk dalam jalur target
                if (cek_jalur(root_pohon, cari, target_daun) == 1) {
                    int len_root = strlen(cari->kontainer.nama_simpul) + 3 + hitungDigit(cari->kontainer.value);
                    if(len_root > makslen) {
                        makslen = len_root;
                    }
                    
                    for(int i = 0; i < cari->kontainer.jumlah_konsekuensi_peluang; i++) {
                        int len_peluang = strlen(cari->kontainer.peluang[i]) + 2;
                        if(len_peluang > makslen) {
                            makslen = len_peluang;
                        }
                    }
                }
                cari = cari->sibling;
            } while (cari != root && cari != NULL);
        }

        //print baris pertama
        for(int i = 0; i < spasi; i++) {
            printf(" ");
        }
        printf("%s - %d\n", root->kontainer.nama_simpul, root->kontainer.value);
        
        //print peluang
        for(int i = 0; i < root->kontainer.jumlah_konsekuensi_peluang; i++) {
            for(int j = 0; j < spasi; j++) {
                printf(" ");
            }
            printf("[%s]\n", root->kontainer.peluang[i]);
        }
        printf("\n");

        //rekrusif
        simpul *bantu = root->child;

        if(bantu != NULL) {
            if(bantu->sibling == NULL) {
                /* jika memiliki satu simpul anak */
                print_tree_pruning(root_pohon, bantu, spasi + makslen, target_daun);
            } else {
                /* jika memiliki banyak simpul anak dengan konsep circular */
                while(bantu->sibling != root->child) {
                    print_tree_pruning(root_pohon, bantu, spasi + makslen, target_daun);
                    bantu = bantu->sibling;
                }
                /* memproses simpul anak terakhir */
                print_tree_pruning(root_pohon, bantu, spasi + makslen, target_daun);
            }
        }
    }
}

void print_peluang(simpul *root_pohon, simpul *root, simpul *target_daun, int *total_value){
    if (root != NULL) {
        // Cek apakah simpul saat ini berada di jalur menuju target_daun
        if (cek_jalur(root_pohon, root, target_daun) == 1) {
            
            // akumulasikan nilai value simpul ini ke total_value
            *total_value += root->kontainer.value;

            // printf("total value : %d\n", total_value);

            // cetak semua daftar peluang yang dimiliki oleh simpul saat ini
            for (int i = 0; i < root->kontainer.jumlah_konsekuensi_peluang; i++) {
                printf("[%s]\n", root->kontainer.peluang[i]);
            }

            // lanjutkan pencarian ke simpul anaknya jika ada
            simpul *bantu = root->child;
            if (bantu != NULL) {
                if (bantu->sibling == NULL) {
                    print_peluang(root_pohon, bantu, target_daun, total_value);
                } else {
                    while (bantu->sibling != root->child) {
                        print_peluang(root_pohon, bantu, target_daun, total_value);
                        bantu = bantu->sibling;
                    }
                    print_peluang(root_pohon, bantu, target_daun, total_value);
                }
            }
        }
    }
}