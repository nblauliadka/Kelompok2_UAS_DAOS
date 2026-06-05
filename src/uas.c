#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uas.h"

Pasien heap_pasien[MAX_PASIEN];
int size_pasien = 0;
int id_pasien_counter = 1;

Darah heap_darah[MAX_DARAH];
int size_darah = 0;
int id_darah_counter = 1;

RiwayatTransaksi riwayat[MAX_RIWAYAT];
int jumlah_riwayat = 0;

// Mengubah angka triage menjadi label string deskriptif
const char* label_triage(int triage) {
    switch (triage) {
        case 1: return "KRITIS EKSTREM";
        case 2: return "KRITIS";
        case 3: return "MENDESAK";
        case 4: return "KURANG MENDESAK";
        case 5: return "TIDAK MENDESAK";
        default: return "TIDAK DIKETAHUI";
    }
}

// Mengecek kompatibilitas donor darah sesuai aturan medis ABO
int is_kompatibel(const char* gol_pasien, const char* gol_darah) {
    if (strcmp(gol_pasien, "AB") == 0) return 1;
    if (strcmp(gol_pasien, "A") == 0) return (strcmp(gol_darah, "A") == 0 || strcmp(gol_darah, "O") == 0);
    if (strcmp(gol_pasien, "B") == 0) return (strcmp(gol_darah, "B") == 0 || strcmp(gol_darah, "O") == 0);
    if (strcmp(gol_pasien, "O") == 0) return (strcmp(gol_darah, "O") == 0);
    return 0;
}

// Memastikan input pengguna hanya A, B, AB, atau O
int validasi_gol_darah(const char* gol) {
    return (strcmp(gol, "A")  == 0 || strcmp(gol, "B")  == 0 ||
            strcmp(gol, "AB") == 0 || strcmp(gol, "O")  == 0);
}

// Menentukan pasien mana yang lebih prioritas (Triage terkecil atau Darurat)
int prioritas_pasien_lebih_tinggi(int a, int b) {
    if (heap_pasien[a].triage != heap_pasien[b].triage) {
        return heap_pasien[a].triage < heap_pasien[b].triage;
    }
    return heap_pasien[a].is_emergency > heap_pasien[b].is_emergency;
}

// Menukar posisi dua pasien di dalam array heap
void swap_pasien(int i, int j) {
    Pasien tmp = heap_pasien[i];
    heap_pasien[i] = heap_pasien[j];
    heap_pasien[j] = tmp;
}

// Memperbaiki struktur Max-Heap dari bawah ke atas saat enqueue
void heapify_up_pasien(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (prioritas_pasien_lebih_tinggi(idx, parent)) {
            swap_pasien(idx, parent);
            idx = parent;
        } else break;
    }
}

// Menambah pasien ke antrean (Bypass langsung ke root jika Darurat)
void enqueue_pasien(Pasien p) {
    if (size_pasien >= MAX_PASIEN) {
        printf("  [!] Antrean pasien penuh.\n");
        return;
    }
    if (p.is_emergency) {
        for (int i = size_pasien; i > 0; i--) heap_pasien[i] = heap_pasien[i - 1];
        heap_pasien[0] = p;
        size_pasien++;
        heapify_down_pasien(0);
    } else {
        heap_pasien[size_pasien] = p;
        size_pasien++;
        heapify_up_pasien(size_pasien - 1);
    }
}

// Mengambil pasien paling kritis (root) dari Max-Heap
Pasien dequeue_pasien(void) {
    Pasien hasil = heap_pasien[0];
    heap_pasien[0] = heap_pasien[size_pasien - 1];
    size_pasien--;
    if (size_pasien > 0) heapify_down_pasien(0);
    return hasil;
}

//  FUNGSI MIN-HEAP DARAH

// Menukar posisi dua kantong darah di dalam array heap
void swap_darah(int i, int j) {
    Darah tmp = heap_darah[i];
    heap_darah[i] = heap_darah[j];
    heap_darah[j] = tmp;
}

// Memperbaiki struktur Min-Heap dari bawah ke atas saat enqueue
void heapify_up_darah(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap_darah[idx].sisa_hari < heap_darah[parent].sisa_hari) {
            swap_darah(idx, parent);
            idx = parent;
        } else break;
    }
}

// Memperbaiki struktur Min-Heap dari atas ke bawah saat dequeue
void heapify_down_darah(int idx) {
    int terkecil = idx, kiri = 2 * idx + 1, kanan = 2 * idx + 2;
    if (kiri < size_darah && heap_darah[kiri].sisa_hari < heap_darah[terkecil].sisa_hari) terkecil = kiri;
    if (kanan < size_darah && heap_darah[kanan].sisa_hari < heap_darah[terkecil].sisa_hari) terkecil = kanan;
    if (terkecil != idx) {
        swap_darah(idx, terkecil);
        heapify_down_darah(terkecil);
    }
}

/ Menambah kantong darah baru ke stok Min-Heap
void enqueue_darah(Darah d) {
    if (size_darah >= MAX_DARAH) {
        printf("  [!] Stok darah penuh.\n");
        return;
    }
    heap_darah[size_darah] = d;
    size_darah++;
    heapify_up_darah(size_darah - 1);
}

// Mengambil kantong darah terpilih (berdasarkan indeks hasil Greedy)
Darah dequeue_darah_by_index(int idx) {
    Darah hasil = heap_darah[idx];
    heap_darah[idx] = heap_darah[size_darah - 1];
    size_darah--;
    if (idx < size_darah) {
        heapify_up_darah(idx);
        heapify_down_darah(idx);
    }
    return hasil;
}

//  ALGORITMA INTI: LINEAR SEARCH DAN GREEDY

// Mengeksekusi alokasi: Peek Max-Heap -> Linear Search -> Greedy -> Dequeue
int cari_dan_alokasi_darah(void) {
    if (size_pasien == 0 || size_darah == 0) {
        printf("  [!] Antrean pasien atau stok darah kosong.\n");
        return 0;
    }

    Pasien* p = &heap_pasien[0];
    printf("\n  Pasien Prioritas Tertinggi: %s (Gol: %s)\n", p->nama, p->gol_darah);
    printf("------------------------------------------------------------\n");

    int idx_terpilih = -1, sisa_min = __INT_MAX__, jumlah_kompatibel = 0;
    
    // Linear Search untuk mencari seluruh darah yang kompatibel
    for (int i = 0; i < size_darah; i++) {
        if (is_kompatibel(p->gol_darah, heap_darah[i].gol_darah)) {
            jumlah_kompatibel++;
            
            // Greedy: Pilih sisa hari yang paling kecil
            if (heap_darah[i].sisa_hari < sisa_min) {
                sisa_min = heap_darah[i].sisa_hari;
                idx_terpilih = i;
            }
        }
    }

    if (idx_terpilih == -1) {
        printf("  [GAGAL] Tidak ada darah kompatibel.\n");
        return 0;
    }

    Pasien pasien_terpilih = dequeue_pasien();
    Darah darah_terpilih = dequeue_darah_by_index(idx_terpilih);

    // Pencatatan ke array riwayat statis
    if (jumlah_riwayat < MAX_RIWAYAT) {
        RiwayatTransaksi* r = &riwayat[jumlah_riwayat];
        r->nomor = jumlah_riwayat + 1;
        r->pasien = pasien_terpilih;
        r->darah = darah_terpilih;
        snprintf(r->timestamp, sizeof(r->timestamp), "Transaksi #%03d", r->nomor);
        jumlah_riwayat++;
    }

    printf("  [SUKSES] Kantong D%03d dialokasikan ke Pasien P%03d.\n", darah_terpilih.id, pasien_terpilih.id);
    return 1;
}

//  FUNGSI MENU CLI

void menu_input_pasien(void) {
    Pasien p; p.id = id_pasien_counter++;
    printf("  Nama pasien       : "); scanf(" %63[^\n]", p.nama);
    do { printf("  Golongan darah    : "); scanf("%3s", p.gol_darah); } while (!validasi_gol_darah(p.gol_darah));
    do { printf("  Triage (1-5)      : "); scanf("%d", &p.triage); } while (p.triage < 1 || p.triage > 5);
    printf("  Darurat? (1/0)    : "); scanf("%d", &p.is_emergency);
    enqueue_pasien(p);
    printf("  [OK] Pasien berhasil ditambahkan.\n");
}

void menu_input_darah(void) {
    Darah d; d.id = id_darah_counter++;
    do { printf("  Golongan darah    : "); scanf("%3s", d.gol_darah); } while (!validasi_gol_darah(d.gol_darah));
    do { printf("  Sisa hari (1-365) : "); scanf("%d", &d.sisa_hari); } while (d.sisa_hari < 1 || d.sisa_hari > 365);
    enqueue_darah(d);
    printf("  [OK] Kantong Darah berhasil ditambahkan.\n");
}

void menu_eksekusi_alokasi(void) {
    printf("  EKSEKUSI ALOKASI DARAH\n"); 
    printf("------------------------------------------------------------\n");
    cari_dan_alokasi_darah();
}

// Menampilkan seluruh isi antrean pasien dan stok darah untuk membuktikan bahwa struktur Max-Heap dan Min-Heap berjalan dengan benar
void menu_tampilkan_data(void) {
    printf("============================================================\n");
    printf("  ANTREAN PASIEN (Max-Heap) & STOK DARAH (Min-Heap)\n");
    printf("============================================================\n");
    
    printf("\n  [ANTREAN PASIEN]\n");
    if (size_pasien == 0) {
        printf("  (Kosong)\n");
    } else {
        for (int i = 0; i < size_pasien; i++) {
            printf("  %d. P%03d | %s | Gol: %s | Triage: %d | Darurat: %s\n",
                   i + 1, heap_pasien[i].id, heap_pasien[i].nama, heap_pasien[i].gol_darah,
                   heap_pasien[i].triage, heap_pasien[i].is_emergency ? "Ya" : "Tidak");
        }
    }

    printf("\n  [STOK KANTONG DARAH]\n");
    if (size_darah == 0) {
        printf("  (Kosong)\n");
    } else {
        for (int i = 0; i < size_darah; i++) {
            printf("  %d. D%03d | Gol: %s | Sisa: %d hari\n",
                   i + 1, heap_darah[i].id, heap_darah[i].gol_darah, heap_darah[i].sisa_hari);
        }
    }
    printf("============================================================\n");
}