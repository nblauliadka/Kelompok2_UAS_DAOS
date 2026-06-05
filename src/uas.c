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
