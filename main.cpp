#include "crud.h"
#include <iostream>

int main () {
  std::fstream database_mahasiswa;
  //fungsi pengecekan database
  crud::checkDatabase(database_mahasiswa);

  int option = crud::getOpt(); 
  char isContinue;
  enum option{CREATE=1,READ,UPDATE,DELETE,FINISH};

  while (option != FINISH) {
    switch (option) {
      case CREATE: std::cout << "> Menambahkan data" <<std::endl;
                   crud::addMahasiswa(database_mahasiswa);
                   std::cout << std::endl;
              break;
      case READ: std::cout << "> Menampilkan data" <<std::endl;
                 crud::displayMahasiswa(database_mahasiswa);
                 std::cout << std::endl;
              break;
      case UPDATE: std::cout << "> Mengupdate data" <<std::endl;
                   crud::updateMahasiswa(database_mahasiswa);
              break;
      case DELETE: std::cout << "> Menghapus data" <<std::endl;
                   crud::deleteMahasiswa(database_mahasiswa);
              break;
      default: std::cout << "> Opsi tidak ditemukan!" <<std::endl;
              break;
    }
    label_continue:
    
    std::cout << "\ningin melanjutkan?(y/n) : ";
    std::cin >> isContinue;
    if(isContinue=='y'||isContinue=='Y') option = crud::getOpt();
    else if (isContinue=='n'||isContinue=='N') break;
    else goto label_continue;
  }

  std::cout<<"Sampai jumpa :)"<<std::endl;
  return 0;
}

