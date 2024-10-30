#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//========================================================

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

int main()
{
    node *head;
    char pilih[10]; // Ubah dari char ke string
    int pilihan;

    head = NULL;
    do {
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
        
        scanf("%s", pilih); // Baca sebagai string

        // Cek apakah pengguna ingin keluar
        if (strcmp(pilih, "q") == 0 || strcmp(pilih, "Q") == 0) {
            break;
        }

        pilihan = atoi(pilih); // Konversi string ke integer

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

    } while (1); // Loop terus hingga pengguna memilih keluar

    return 0;
}

//========================================================
/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================

void tambahAwal(node **head){
    int bil;
    node *pNew, *pLast;

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL){
        pNew->data = bil;
        if (*head == NULL) {
            pNew->next = pNew; // Node menunjuk ke dirinya sendiri
            *head = pNew;
        }
        else {
            // Cari node terakhir
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pNew->next = *head;
            pLast->next = pNew;
            *head = pNew;
        }
        printf("Data berhasil ditambahkan di awal.\n");
    }
    else{
        printf("Alokasi memori gagal");
    }
    getch();
}

//========================================================

void tambahData(node **head){
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nPosisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("Bilangan : ");
    scanf("%d", &bil);

    if (*head == NULL) {
        printf("List kosong. Tidak dapat menyisipkan di tengah.\n");
        getch();
        return;
    }

    pCur = *head;
    do {
        if (pCur->data == pos) {
            break;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur->data != pos) {
        printf("\nNode tidak ditemukan");
        getch();
        return;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL){
        printf("\nAlokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = pCur->next;
    pCur->next = pNew;

    printf("Data berhasil ditambahkan setelah %d.\n", pos);
    getch();
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pLast;

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            pNew->next = pNew; // Node menunjuk ke dirinya sendiri
            *head = pNew;
        }
        else {
            pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
            pNew->next = *head;
        }
        printf("Data berhasil ditambahkan di akhir.\n");
    }
    else {
        printf("Alokasi memori gagal");
    }
    getch();
}

//========================================================

void tranverse(node *head){
    // Traverse a circular linked list
    node *pWalker;

    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
    }
    else {
        pWalker = head;
        printf("Isi list: ");
        do {
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->next;
        } while (pWalker != head);
        printf("(circular)\n");
    }
    getch(); // Memberi waktu untuk melihat daftar sebelum layar dibersihkan
}

//========================================================

void hapusAwal(node **head) {
    node *pCur, *pLast;

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    pCur = *head;
    if (pCur->next == *head) {
        // Hanya satu node
        *head = NULL;
        free(pCur);
    }
    else {
        // Cari node terakhir
        pLast = *head;
        while (pLast->next != *head) {
            pLast = pLast->next;
        }
        *head = pCur->next;
        pLast->next = *head;
        free(pCur);
    }

    system("cls");
    printf("\nData berhasil dihapus dari awal.\n");
    getch();
}

//========================================================

void hapusData(node **head) {
    int pos, count = 0;
    node *pPre = NULL, *pCur = *head, *pLast;

    system("cls");
    tranverse(*head);
    printf("\nPosisi penghapusan setelah data bernilai : ");
    scanf("%d", &pos);

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    // Hitung jumlah node
    pLast = *head;
    do {
        count++;
        pLast = pLast->next;
    } while (pLast != *head);

    if (count < 3) {
        printf("Penghapusan tidak diizinkan, list terlalu kecil untuk menghapus di tengah\n");
        getch();
        return;
    }

    // Cari node setelah mana node akan dihapus
    pCur = *head;
    do {
        if (pCur->data == pos) {
            break;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur->data != pos) {
        printf("Node dengan nilai %d tidak ditemukan\n", pos);
        getch();
        return;
    }

    if (pCur->next == *head) {
        printf("Tidak ada node setelah node dengan nilai %d untuk dihapus\n", pos);
        getch();
        return;
    }

    // Jika node setelah pCur adalah head, tidak bisa dihapus
    if (pCur->next->next == *head && pCur->next != *head) {
        printf("Penghapusan tidak diizinkan pada node terakhir\n");
        getch();
        return;
    }

    node *pDelete = pCur->next;
    pCur->next = pDelete->next;
    free(pDelete);

    system("cls");
    printf("\nData berhasil dihapus setelah %d.\n", pos);
    getch();
}

//========================================================

void hapusAkhir(node **head) {
    node *pCurrent = *head, *pPre = NULL, *pLast;

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }
    else if (pCurrent->next == *head) {
        // Hanya satu node
        free(pCurrent);
        *head = NULL;
        system("cls");
        printf("\nData berhasil dihapus dari akhir.\n");
        getch();
        return;
    }

    // Cari node terakhir dan node sebelum terakhir
    while (pCurrent->next != *head) {
        pPre = pCurrent;
        pCurrent = pCurrent->next;
    }

    pPre->next = *head;
    free(pCurrent);

    system("cls");
    printf("\nData berhasil dihapus dari akhir.\n");
    getch();
}

//========================================================

void cariData(node *head) {
    int target, found = 0;
    node *pCur = head;

    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    printf("Masukkan nilai yang dicari : ");
    scanf("%d", &target);

    do {
        if (pCur->data == target) {
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != head);

    if (found){
        printf("Nilai ditemukan.\n");
    }
    else{
        printf("Nilai tidak ditemukan.\n");
    }
    getch();
}

//========================================================

void jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    if (head != NULL) {
        do {
            count++;
            pCur = pCur->next;
        } while (pCur != head);
    }

    system("cls");
    printf("Jumlah data sebanyak: %d\n", count);
    getch();
}

//========================================================

void hasilpenjumlahan(node *head) {
    int sum = 0;
    node *pCur = head;

    if (head != NULL) {
        do {
            sum += pCur->data;
            pCur = pCur->next;
        } while (pCur != head);
    }

    system("cls");
    printf("Hasil penjumlahan seluruh data adalah: %d\n", sum);
    getch();
}

//========================================================

void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
        // Tambah sebelum node pertama atau ke list kosong
        if (*head == NULL) {
            pNew->next = pNew;
            *head = pNew;
        }
        else {
            // Cari node terakhir
            node *pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pNew->next = *head;
            pLast->next = pNew;
            *head = pNew;
        }
    }
    else {
        // Tambah di tengah atau di akhir
        pNew->next = pPre->next;
        pPre->next = pNew;
    }
}

//========================================================
