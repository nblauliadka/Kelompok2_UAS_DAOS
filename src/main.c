 #include <stdio.h>
 #include "uas.h"
 
 int main(void) {
     int pilihan;
 
     printf("============================================================\n");
     printf("  DAOS - SISTEM ALOKASI KANTONG DARAH\n");
     printf("  Data Analysis & Optimization System\n");
     printf("  Berbasis Tingkat Kritis (Triage) & Kedaluwarsa\n"); 
     printf("============================================================\n");
 
     do {
         printf("\n  MENU UTAMA:\n");
         printf("------------------------------------------------------------\n");
         printf("  [1] Input Data Pasien\n");
         printf("  [2] Input Kantong Darah\n");
         printf("  [3] Eksekusi Alokasi Darah\n");
         printf("  [4] Tampilkan Antrean Pasien & Stok Darah\n");
         printf("  [5] Tampilkan Riwayat Transaksi\n");
         printf("  [0] Keluar\n");
         printf("------------------------------------------------------------\n");
         printf("  Pilih menu: ");
         fflush(stdout);
 
         if (scanf("%d", &pilihan) != 1) {
             int c;
             while ((c = getchar()) != '\n' && c != EOF);
             pilihan = -1;
         }
 
         printf("\n");
 
         switch (pilihan) {
             case 1: menu_input_pasien(); break;
             case 2: menu_input_darah(); break;
             case 3: menu_eksekusi_alokasi(); break;
             case 4: menu_tampilkan_data(); break;
             case 5: menu_tampilkan_riwayat(); break;
             case 0:
                 printf("============================================================\n");
                 printf("  Program dihentikan. Total transaksi: %d.\n", jumlah_riwayat);
                 printf("============================================================\n");
                 break;
             default:
                 printf("  [!] Pilihan tidak valid. Masukkan angka 0-5.\n");
                 break;
         }
     } while (pilihan != 0);
 
     return 0;
 }