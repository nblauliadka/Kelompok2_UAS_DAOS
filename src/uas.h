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

 //  DEKLARASI VARIABEL GLOBAL
 extern Pasien heap_pasien[MAX_PASIEN];
 extern int size_pasien;
 extern int id_pasien_counter;
 
 extern Darah heap_darah[MAX_DARAH];
 extern int size_darah;
 extern int id_darah_counter;
 
 extern RiwayatTransaksi riwayat[MAX_RIWAYAT];
 extern int jumlah_riwayat;

 //  PROTOTIPE FUNGSI UTILITAS
 const char* label_triage(int triage);
 int is_kompatibel(const char* gol_pasien, const char* gol_darah);
 int validasi_gol_darah(const char* gol);

 #endif