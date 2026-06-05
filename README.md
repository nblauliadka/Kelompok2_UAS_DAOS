# Kelompok 2 DAOS: Sistem Alokasi Kantong Darah (SDG 3)

Proyek Data Analysis & Optimization System (DAOS) ini dikembangkan menggunakan bahasa C murni (in-memory) untuk memenuhi evaluasi Ujian Akhir Semester (UAS) Praktikum Struktur Data dan Algoritma B.

Sistem ini mengimplementasikan Double Priority Queue untuk mengoptimalkan distribusi darah berdasarkan tingkat kritis pasien darurat sekaligus meminimalkan pemborosan stok darah yang mendekati masa kedaluwarsa.

# Struktur Direktori Pengumpulan

Sesuai dengan standar pengumpulan UAS, repositori ini diatur dengan struktur berikut:

Kelompok2_UAS_DAOS/
├── src/
│   ├── main.c           # Entry point dan loop CLI utama
│   ├── uas.c            # Implementasi algoritma dan struktur data
│   └── uas.h            # Deklarasi prototipe, struct, dan macro
├── docs/
│   └── Kelompok2_UAS_Slide.pptx  # Revisi slide presentasi UAS
└── README.md            # Dokumentasi program dan panduan kompilasi

# Cara Kompilasi & Menjalankan Program

Program ini wajib dikompilasi menggunakan standar compiler gcc karena memuat pemisahan modul (header dan implementation file).
Lakukan kompilasi file C secara bersamaan:
    gcc -o daos main.c uas.c

# Pembagian Tugas & Modul (Sesuai Arahan Commit)

Untuk memastikan histori commit GitHub mencerminkan kontribusi merata sesuai rekomendasi aslab, pengerjaan modul dibagi secara ketat:

1. Muhammad Rizki (Kil-Rizki) - NPM: 250810701100049
Jobdesk:
 - Inisialisasi awal (adding folder structure).
 - Mengembangkan struktur data Queue/Heap utama untuk entitas Pasien (fungsi enqueue & dequeue pasien beserta headernya).
 - Membangun fungsi inti untuk struktur Max/Min-Heap (fungsi swap dan heapify untuk heap).
 - Mengintegrasikan fungsionalitas ke dalam antarmuka utama (menu utama).

2. Siti Fildzahra Revani (fildzahrarevanii) - NPM: 250810701100107
Jobdesk:
 - Mendefinisikan Data Structures fundamental untuk keseluruhan proyek (membuat struct untuk project dan variabel global).
 - Membangun algoritma Sorting/Heap spesifik untuk entitas Darah   (fungsi swap darah dan fungsi heapify darah).
 - Membangun antarmuka untuk visualisasi data (menu tampilkan data).

3. Nabil Aulia Dika (nblauliadka) - NPM: 250810701100090
Jobdesk:
 - Membangun fungsi logika prioritas pasien, termasuk algoritma pengambilan keputusan (fungsi prioritas pasien).
 - Menangani logika komputasi kecocokan golongan darah dan input spesifik (fungsi kompitibilitas dan input).
 - Mengelola konfigurasi sistem dan header (menambah header di uas.c, konstanta untuk string deskripsi).
 - Menyusun fungsionalitas menu alokasi (menu alokasi darah).

4. Irvan Almidar (irvanalmidar) - NPM: 250810701100085
Jobdesk:
 - Membangun struktur Queue spesifik untuk inventaris darah (enqueue & dequeue darah).
 - Mengembangkan fitur pencarian dan eksekusi alokasi darah (cari dan alokasi darah).
 - Menangani interaksi user input secara langsung (menu input, menu input darah).
 - Membangun fitur pelacakan rekam jejak (menu tampilkan riwayat).