#include <fstream>

namespace crud {

  //length data
  const int lenNama = 30;
  const int lenNIM = 12;
  const int lenJurusan = 20;
  
  //struktur data Mahasiswa
  struct Mahasiswa{
    int pk;
    char NIM[lenNIM];
    char nama[lenNIM];
    char jurusan[lenJurusan];
  };

  //menampilkan menu
  int getOpt();

  //mengecek database
  void checkDatabase(std::fstream &database_mahasiswa);

  //menambah data mahasiswa
  void addMahasiswa(std::fstream &database_mahasiswa);
  //menampilkan data mahasiswa
  void displayMahasiswa(std::fstream &database_mahasiswa);
  //update data mahasiswa
  void updateMahasiswa(std::fstream &database_mahasiswa);
  //menghapus data mahasiswa
  void deleteMahasiswa(std::fstream &database_mahasiswa);
}
