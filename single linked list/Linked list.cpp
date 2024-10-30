#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//======================================================== 
// Struktur node untuk linked list
struct node {
    int data;
    struct node *next;
};
typedef struct node node;
// Prototipe fungsi
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void tranverse(node *head);
void hapusAwal(node **head);
void hapusData(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void jumlahData(node *head);
void hasilpenjumlahan(node *head);
void insertNode(node **head, node *pPre, node *pNew);
//========================================================
// fungsi utama 
int main()
{
    node *head;              // Pointer ke head linked list
    char pilih[10];           // Menyimpan input pilihan user sebagai string
    int pilihan;              // Menyimpan input yang sudah dikonversi menjadi integer
    head = NULL;              // Inisialisasi head sebagai NULL (list kosong)
    do {
        // Tampilkan menu dan ambil input user
        system("cls");
        printf("Masukkan Pilihan\n");
        printf("1. Tambah data di awal list\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Cetak isi list\n");
        printf("5. Hapus data di awal list\n");
        printf("6. Hapus data di tengah list\n");
        printf("7. Hapus data di akhir list\n");
        printf("8. Pencarian data dalam list\n");
        printf("9. Tampilkan informasi jumlah data pada list\n");
        printf("10. Tampilkan hasil penjumlahan dari semua data di list\n");
        printf("MASUKKAN PILIHAN (Tekan q untuk keluar) : ");
        scanf("%s", pilih);   // Baca input sebagai string
        // Cek apakah user ingin keluar
        if (strcmp(pilih, "q") == 0 || strcmp(pilih, "Q") == 0) {
            break;
			}
        // Konversi input string ke integer untuk pilihan menu
        pilihan = atoi(pilih);
        // Menggunakan if-else alih-alih switch-case
        if (pilihan == 1) {
            tambahAwal(&head);
        }
        else if (pilihan == 2) {
            tambahData(&head);
        }
        else if (pilihan == 3) {
            tambahAkhir(&head);
        }
        else if (pilihan == 4) {
            tranverse(head);
        }
        else if (pilihan == 5) {
            hapusAwal(&head);
        }
        else if (pilihan == 6) {
            hapusData(&head);
        }
        else if (pilihan == 7) {
            hapusAkhir(&head);
        }
        else if (pilihan == 8) {
            cariData(head);
        }
        else if (pilihan == 9) {
            jumlahData(head);
        }
        else if (pilihan == 10) {
            hasilpenjumlahan(head);
        }
        else {
            printf("Pilihan tidak valid\n");
            getch();
        }

    } while (1);  // Loop terus sampai user memilih keluar

    return 0;
}
//======================================================== 
/*node *createNode(void){
  node *ptr;
  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/
//======================================================== 
// Fungsi untuk menambah node di awal list
void tambahAwal(node **head){
    int bil;
    node *pNew;
    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);  // Ambil input angka dari user
    pNew = (node *)malloc(sizeof(node));  // Alokasikan memori untuk node baru
    if (pNew != NULL){
        pNew->data = bil;      // Set data node baru
        pNew->next = *head;    // Hubungkan node baru ke head sebelumnya
        *head = pNew;          // Set node baru sebagai head
    }
    else{
        printf("Alokasi memori gagal");
        getch();
    }
}
//========================================================  
// Fungsi untuk menambah node di tengah list
void tambahData(node **head){
    int pos, bil;
    node *pNew, *pCur;
    system("cls");
    tranverse(*head);  // Tampilkan isi list
    printf("\nPosisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);  // Ambil input posisi penyisipan
    printf("\nBilangan : ");
    scanf("%d", &bil);  // Ambil data baru
    pCur = *head;  // Mulai dari head
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;  // Cari posisi yang diinginkan
    }
    pNew = (node *)malloc(sizeof(node));  // Alokasikan memori untuk node baru
    if (pCur == NULL){
        printf("\nNode tidak ditemukan");
        getch();
    }
    else if (pNew == NULL){
        printf("\nAlokasi memori gagal");
        getch();
    }
    else{
        pNew->data = bil;       // Set data node baru
        pNew->next = pCur->next;  // Hubungkan node baru dengan node setelahnya
        pCur->next = pNew;        // Hubungkan node sebelumnya dengan node baru
    }
}
//========================================================  
// Fungsi untuk menambah node di akhir list
void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pPre;
    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);  // Ambil data baru dari user
    pNew = (node *)malloc(sizeof(node));  // Alokasikan memori untuk node baru
    if (pNew != NULL) {
        pNew->data = bil;  // Set data node baru
        pNew->next = NULL; // Node baru akan menjadi node terakhir
        if (*head == NULL) {
            *head = pNew;  // Jika list kosong, node baru menjadi head
        }
        else {
            pPre = *head;
            while (pPre->next != NULL) {
                pPre = pPre->next;  // Cari node terakhir
            }
            pPre->next = pNew;  // Tambahkan node baru di akhir list
        }
    }
    else {
        printf("Alokasi memori gagal");
        getch();
    }
}
//========================================================  
// Fungsi untuk mencetak isi list
void tranverse(node *head){
    node *pWalker;
    system("cls");
    pWalker = head;  // Mulai dari head
    while (pWalker != NULL){
        printf("%d -> ", pWalker->data);  // Tampilkan data
        pWalker = pWalker->next;  // Lanjut ke node berikutnya
    }
    printf("NULL\n");
    getch();
}
//======================================================== 
// Fungsi untuk menghapus node di awal list
void hapusAwal(node **head) {
    node *pCur;
    if (*head != NULL) {
        pCur = *head;         // Simpan head
        *head = (*head)->next;  // Geser head ke node berikutnya
        free(pCur);           // Bebaskan memori node lama
        system("cls");
        printf("\nData berhasil dihapus");
        getch();
    }
    else {
        printf("List kosong\n");
        getch();
    }
}
//======================================================== 
// Fungsi untuk menghapus node di tengah list
void hapusData(node **head) {
    int pos, count = 0;
    node *pPre = NULL, *pCur = *head;
    system("cls");
    tranverse(*head);  // Tampilkan isi list
    printf("\nPosisi penghapusan setelah data bernilai : ");
    scanf("%d", &pos);
    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }
    // Hitung jumlah node
    pCur = *head;
    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }
    if (count < 3) {
        printf("Penghapusan tidak diizinkan, list terlalu kecil untuk menghapus di tengah\n");
        getch();
        return;
    }
    // Cari node setelah mana node akan dihapus
    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pPre = pCur;
        pCur = pCur->next;
    }
    if (pCur == NULL || pCur->next == NULL) {
        printf("Node dengan nilai %d tidak ditemukan atau tidak ada node setelahnya\n", pos);
        getch();
    }
    else if (pCur->next->next == NULL) {
        printf("Penghapusan tidak diizinkan pada node terakhir\n");
        getch();
    }
    else {
        node *pNext = pCur->next;
        pCur->next = pNext->next;
        free(pNext);  // Bebaskan memori node yang dihapus
        system("cls");
        printf("\nData berhasil dihapus");
        getch();
    }
}
//========================================================  
// Fungsi untuk menghapus node di akhir list
void hapusAkhir(node **head) {
    node *pCurrent = *head, *pPre = NULL;
    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }
    else if (pCurrent->next == NULL) {
        free(pCurrent);  // Jika hanya ada satu node
        *head = NULL;    // Set head ke NULL (list kosong)
        system("cls");
        printf("\nData berhasil dihapus");
        getch();
        return;
    }
    while (pCurrent->next != NULL) {
        pPre = pCurrent;    // Temukan node kedua terakhir
        pCurrent = pCurrent->next;
    }
    free(pCurrent);         // Bebaskan node terakhir
    pPre->next = NULL;      // Set node kedua terakhir sebagai node terakhir
    system("cls");
    printf("\nData berhasil dihapus");
    getch();
}
//======================================================== 
// Fungsi untuk mencari data dalam list
void cariData(node *head) {
    int target;
    node *pCur = head;
    system("cls");
    printf("Masukkan nilai yang dicari : ");
    scanf("%d", &target);  // Ambil nilai yang dicari dari user
    while (pCur != NULL && pCur->data != target) {
        pCur = pCur->next;  // Cari data
    }
    if (pCur != NULL){
        printf("Nilai ditemukan\n");
        getch();
    }
    else{
        printf("Nilai tidak ditemukan\n");
        getch();
    }
}
//======================================================== 
// Fungsi untuk menghitung jumlah node dalam list
void jumlahData(node *head) {
    int count = 0;
    node *pCur = head;
    while (pCur != NULL) {
        count++;  // Hitung jumlah node
        pCur = pCur->next;
    }
    system("cls");
    printf("Jumlah data sebanyak: %d\n", count);  // Tampilkan jumlah node
    getch();
}
//======================================================== 
// Fungsi untuk menghitung hasil penjumlahan semua data di list
void hasilpenjumlahan(node *head) {
    int sum = 0;
    node *pCur = head;
    while (pCur != NULL) {
        sum += pCur->data;  // Tambahkan nilai node ke dalam sum
        pCur = pCur->next;
    }
    system("cls");
    printf("Hasil penjumlahan seluruh data adalah: %d\n", sum);  // Tampilkan hasil penjumlahan
    getch();
}
//======================================================== 
// Fungsi untuk menyisipkan node ke dalam list
void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
        // Tambahkan node baru di awal list atau ke list kosong
        pNew->next = *head;
        *head = pNew;
    }
    else {
        // Tambahkan node baru di tengah atau di akhir
        pNew->next = pPre->next;
        pPre->next = pNew;
    }
}
//======================================================== 