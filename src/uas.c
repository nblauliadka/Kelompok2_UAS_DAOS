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
