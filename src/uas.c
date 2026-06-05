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