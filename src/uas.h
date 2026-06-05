 #ifndef DAOS_H
 #define DAOS_H
 
//  KONSTANTA
 #define MAX_PASIEN 100
 #define MAX_DARAH 100
 #define MAX_RIWAYAT 100
 #define MAX_NAMA 64
 #define MAX_GOL_DARAH 4
 
//  DEKLARASI STRUCT
 typedef struct {
     int id;
     char nama[MAX_NAMA];
     char gol_darah[MAX_GOL_DARAH]; 
     int triage;          
     int is_emergency;    
 } Pasien;
 
 typedef struct {
     int id;
     char gol_darah[MAX_GOL_DARAH];
     int sisa_hari;
 } Darah;
 
 typedef struct {
     int nomor;
     Pasien pasien;
     Darah darah;
     char timestamp[32]; 
 } RiwayatTransaksi;

 #endif