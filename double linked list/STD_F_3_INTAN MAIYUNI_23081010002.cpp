#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//========================================================
// Struktur node untuk menyimpan data dan pointer ke node berikutnya dan sebelumnya (untuk double linked list)
struct node {
    int data;
    struct node *next;  // Pointer ke node berikutnya
    struct node *prev;  // Pointer ke node sebelumnya
};
typedef struct node node;  // Aliasing tipe struct node sebagai node

// Prototipe fungsi untuk operasi pada linked list
void tambahAwal(node **head);          // Menambah data di awal linked list
void tambahData(node **head);          // Menambah data di tengah linked list
void tambahAkhir(node **head);         // Menambah data di akhir linked list
void tranverse(node *head);            // Melihat isi linked list
void hapusAwal(node **head);           // Menghapus data di awal linked list
void hapusData(node **head);           // Menghapus data di tengah linked list
void hapusAkhir(node **head);          // Menghapus data di akhir linked list
void cariData(node *head);             // Mencari data di linked list
void jumlahData(node *head);           // Menghitung jumlah data di linked list
void hasilpenjumlahan(node *head);     // Menjumlahkan seluruh data di linked list
void insertNode(node **head, node *pPre, node *pNew);  // Menyisipkan node di linked list

//========================================================

int main() {
    node *head;       // Pointer awal linked list
    char pilih[10];   // Variabel untuk menyimpan pilihan pengguna
    int pilihan;      // Variabel integer untuk pilihan pengguna

    head = NULL;      // Inisialisasi linked list kosong
    do {
        system("cls");  // Membersihkan layar
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
        
        scanf("%s", pilih);  // Menerima input pilihan dari pengguna

        // Jika pengguna memilih 'q' atau 'Q', keluar dari program
        if (strcmp(pilih, "q") == 0 || strcmp(pilih, "Q") == 0) {
            break;
        }

        pilihan = atoi(pilih);  // Mengonversi input string menjadi integer

        // Pemilihan operasi berdasarkan input pengguna
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

    } while (1);  // Ulang terus sampai pengguna keluar

    return 0;
}

//========================================================
/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================

// Fungsi untuk menambahkan node di awal linked list
void tambahAwal(node **head) {
    int bil;
    node *pNew;  // Pointer untuk node baru

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));  // Alokasi memori untuk node baru

    if (pNew != NULL) {
        pNew->data = bil;         // Mengisi data node baru
        pNew->prev = NULL;        // Karena ini node pertama, prev harus NULL
        pNew->next = *head;       // Menghubungkan node baru ke head saat ini
        if (*head != NULL) {
            (*head)->prev = pNew;  // Menghubungkan prev head saat ini ke node baru
        }
        *head = pNew;             // Mengupdate head ke node baru
        printf("Data berhasil ditambahkan di awal.\n");
    } else {
        printf("Alokasi memori gagal");
    }
    getch();
}

//========================================================
// Fungsi untuk menambahkan node di tengah linked list
void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;  // Pointer untuk node baru dan pointer traversal

    system("cls");
    tranverse(*head);  // Cetak isi list terlebih dahulu
    printf("\nPosisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("Bilangan : ");
    scanf("%d", &bil);

    if (*head == NULL) {
        printf("List kosong. Tidak dapat menyisipkan di tengah.\n");
        getch();
        return;
    }

    // Cari node dengan nilai sesuai posisi penyisipan
    pCur = *head;
    while (pCur != NULL) {
        if (pCur->data == pos) {
            break;
        }
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
        return;
    }

    pNew = (node *)malloc(sizeof(node));  // Alokasi memori untuk node baru
    if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
        return;
    }

    // Mengisi node baru dan menghubungkan dengan node sebelum dan sesudahnya
    pNew->data = bil;
    pNew->next = pCur->next;
    pNew->prev = pCur;
    if (pCur->next != NULL) {
        pCur->next->prev = pNew;
    }
    pCur->next = pNew;

    printf("Data berhasil ditambahkan setelah %d.\n", pos);
    getch();
}

//========================================================
// Fungsi untuk menambahkan node di akhir linked list
void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pPre;  // Pointer untuk node baru dan pointer traversal

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));  // Alokasi memori untuk node baru

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;  // Karena ini node terakhir, next harus NULL
       
        if (*head == NULL) {  // Jika list kosong, node baru jadi head
            pNew->prev = NULL;
            *head = pNew;
        } else {
            // Traversal hingga menemukan node terakhir
            pPre = *head;
            while (pPre->next != NULL) {
                pPre = pPre->next;
            }
            pPre->next = pNew;
            pNew->prev = pPre;  // Hubungkan node baru dengan node sebelumnya
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================
// Fungsi untuk menampilkan isi linked list
void tranverse(node *head) {
    node *pWalker;  // Pointer untuk traversal

    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
    } else {
        pWalker = head;
        printf("Isi list: ");
        // Looping melalui list hingga node terakhir
        while (pWalker != NULL) {
            printf("%d <-> ", pWalker->data);
            pWalker = pWalker->next;
        }
        printf("NULL\n");
    }
    getch();
}

//========================================================
// Fungsi untuk menghapus node di awal linked list
void hapusAwal(node **head) {
    node *pCur;  // Pointer untuk node yang akan dihapus

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    pCur = *head;
    *head = pCur->next;  // Update head ke node berikutnya
    
    if (*head != NULL) {
        (*head)->prev = NULL;  // Update prev node pertama ke NULL
    }
    
    free(pCur);  // Dealokasi memori node
    system("cls");
    printf("Data berhasil dihapus dari awal.\n");
    getch();
}

//========================================================
// Fungsi untuk menghapus node di tengah linked list
void hapusData(node **head) {
    int pos;
    node *pCur;  // Pointer untuk traversal

    system("cls");
    tranverse(*head);  // Cetak isi list terlebih dahulu
    printf("\nPosisi penghapusan setelah data bernilai : ");
    scanf("%d", &pos);

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    // Cari node yang cocok dengan nilai posisi
    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL || pCur->next == NULL) {
        printf("Node tidak ditemukan atau tidak ada node setelahnya untuk dihapus.\n");
        getch();
        return;
    }

    // Hapus node setelah posisi yang ditemukan
    node *pDelete = pCur->next;
    pCur->next = pDelete->next;
    if (pDelete->next != NULL) {
        pDelete->next->prev = pCur;
    }
    free(pDelete);  // Dealokasi memori node yang dihapus

    system("cls");
    printf("Data berhasil dihapus setelah %d.\n", pos);
    getch();
}

//========================================================
// Fungsi untuk menghapus node di akhir linked list
void hapusAkhir(node **head) {
    node *pCur = *head;  // Pointer untuk traversal

    if (*head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }
    else if (pCur->next == NULL) {
        // Jika hanya ada satu node
        free(pCur);
        *head = NULL;
        system("cls");
        printf("\nData berhasil dihapus");
        getch();
        return;
    }

    // Traversal hingga node terakhir
    while (pCur->next != NULL) {
        pCur = pCur->next;
    }

    pCur->prev->next = NULL;  // Node sebelumnya jadi node terakhir
    free(pCur);  // Dealokasi memori node terakhir

    system("cls");
    printf("\nData berhasil dihapus");
    getch();
}

//========================================================
// Fungsi untuk mencari data di linked list
void cariData(node *head) {
    int target, found = 0;  // Variabel target dan flag found
    node *pCur = head;  // Pointer untuk traversal

    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
        getch();
        return;
    }

    printf("Masukkan nilai yang dicari : ");
    scanf("%d", &target);

    // Cari data dengan traversal
    while (pCur != NULL) {
        if (pCur->data == target) {
            found = 1;
            break;
        }
        pCur = pCur->next;
    }

    // Cek apakah data ditemukan
    if (found) {
        printf("Nilai ditemukan.\n");
    }
    else {
        printf("Nilai tidak ditemukan.\n");
    }
    getch();
}

//========================================================
// Fungsi untuk menghitung jumlah node di linked list
void jumlahData(node *head) {
    int count = 0;  // Variabel untuk menghitung jumlah node
    node *pCur = head;  // Pointer untuk traversal

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    system("cls");
    printf("Jumlah data sebanyak: %d\n", count);
    getch();
}

//========================================================
// Fungsi untuk menjumlahkan semua data di linked list
void hasilpenjumlahan(node *head) {
    int sum = 0;  // Variabel untuk menghitung jumlah total
    node *pCur = head;  // Pointer untuk traversal

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }

    system("cls");
    printf("Hasil penjumlahan seluruh data adalah: %d\n", sum);
    getch();
}

//========================================================
// Fungsi untuk menyisipkan node di linked list
void insertNode(node **head, node *pPre, node *pNew) {
    if (pPre == NULL) {
        // Tambah sebelum node pertama atau ke list kosong
        pNew->next = *head;
        pNew->prev = NULL;
        if (*head != NULL) {
            (*head)->prev = pNew;
        }
        *head = pNew;
    }
    else {
        // Tambah di tengah atau di akhir
        pNew->next = pPre->next;
        pNew->prev = pPre;
        if (pPre->next != NULL) {
            pPre->next->prev = pNew;
        }
        pPre->next = pNew;
    }
}
//========================================================