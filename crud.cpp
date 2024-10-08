#include "crud.h"
#include <cstdlib>
#include <ios>
#include <iostream>
#include <limits>


//menampilkan menu
int crud::getOpt (){
  system("clear");
  int opt;
  std::cout<<"\nPROGRAM CRUD DATA MAHASISWA\n";
  std::cout<<"============================="<<std::endl;
  std::cout<<"[1]. Tambah data mahasiswa."<<std::endl;
  std::cout<<"[2]. Tampilkan data mahasiswa."<<std::endl;
  std::cout<<"[3]. Update data mahasiswa."<<std::endl;
  std::cout<<"[4]. Hapus data mahasiswa."<<std::endl;
  std::cout<<"[5]. Selesai."<<std::endl;
  std::cout<<"============================="<<std::endl;
  std::cout<<"Masukan pilihan [1-5]! :";
  std::cin>>opt;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  return opt;
}

//mengecek database
void crud::checkDatabase(std::fstream &database_mahasiswa){
  //cek database
  database_mahasiswa.open("database_mahasiswa.bin",std::ios::in | std::ios::out | std::ios::binary);
  if(!database_mahasiswa.is_open()){
    //jika database tidak ada
    database_mahasiswa.close();
    database_mahasiswa.open("database_mahasiswa.bin", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
  } 
}

void writeData(int posisi, crud::Mahasiswa &inputMahasiswa, std::fstream &database_mahasiswa);
int getDataSize(std::fstream &database_mahasiswa);
crud::Mahasiswa readMahasiswa(std::fstream &database_mahasiswa, int posisi);

//menambahkan data mahasiswa
void crud::addMahasiswa(std::fstream &database_mahasiswa){
  crud::Mahasiswa inputMahasiswa;
  int sizeData = getDataSize(database_mahasiswa);

  std::cout<<"Nama\t: ";
  std::cin.getline(inputMahasiswa.nama,lenNama);
  std::cout<<"NIM\t: ";
  std::cin.getline(inputMahasiswa.NIM,lenNIM);
  std::cout<<"Jurusan\t: ";
  std::cin.getline(inputMahasiswa.jurusan,lenJurusan);

  if(sizeData==0) inputMahasiswa.pk = 1;
  else {
    crud::Mahasiswa lastMahasiswa;
    lastMahasiswa= readMahasiswa(database_mahasiswa,sizeData);
    inputMahasiswa.pk = lastMahasiswa.pk + 1;
  }

  writeData(sizeData+1, inputMahasiswa, database_mahasiswa);
  std::cout<<"Berhasil menambahkan data baru!"<<std::endl;
}
void writeData(int posisi, crud::Mahasiswa &inputMahasiswa, std::fstream &database_mahasiswa){
  //menambahkan data berdasarkan size data sebelumnya
  database_mahasiswa.seekp((posisi-1)*sizeof(crud::Mahasiswa),std::ios::beg);
  //menuliskan data mahasiswa baru ke database
  database_mahasiswa.write(reinterpret_cast<char*>(&inputMahasiswa), sizeof(crud::Mahasiswa));
}

int getDataSize(std::fstream &database_mahasiswa){
  int start,end;
  //mencari address awal
  database_mahasiswa.seekg(0,std::ios::beg);
  start = database_mahasiswa.tellg();
  //mencari address akhir
  database_mahasiswa.seekg(0,std::ios::end);
  end = database_mahasiswa.tellg();

  return (end-start) / sizeof(crud::Mahasiswa);
}

crud::Mahasiswa readMahasiswa(std::fstream &database_mahasiswa, int posisi){
  crud::Mahasiswa mahasiswaLast;
  database_mahasiswa.seekg((posisi-1)*sizeof(crud::Mahasiswa),std::ios::beg);
  database_mahasiswa.read(reinterpret_cast<char*>(&mahasiswaLast),sizeof(crud::Mahasiswa));
  return mahasiswaLast;
}


//menampilkan data mahasiswa
void crud::displayMahasiswa(std::fstream &database_mahasiswa){
  int sizeData = getDataSize(database_mahasiswa);
  crud::Mahasiswa getMahasiswaByPos;
  if(sizeData == 0){
    std::cout << "Belum ada data yg ditambahkan." << std::endl; 
    return;
  }
  std::cout << "\n=========== Data Mahasiswa ==========" << std::endl;
  std::cout << "no.\tpk.\tNIM.\tNama.\tJurusan." << std::endl;
  for (int i = 1; i <= sizeData; i++) {
    getMahasiswaByPos = readMahasiswa(database_mahasiswa, i);
    std::cout << i << "\t";
    std::cout << getMahasiswaByPos.pk << "\t";
    std::cout << getMahasiswaByPos.NIM << "\t";
    std::cout << getMahasiswaByPos.nama << "\t";
    std::cout << getMahasiswaByPos.jurusan << std::endl;
  }
  std::cout << "=====================================" << std::endl;
}


//mengupdate data mahasiswa
void crud::updateMahasiswa(std::fstream &database_mahasiswa){
  crud::displayMahasiswa(database_mahasiswa);
  int pk,sizeData,positionData;
  char isSave;
  std::cout<<"\nMasukan pk data mahasiswa! : ";
  std::cin>>pk;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  sizeData = getDataSize(database_mahasiswa);

  crud::Mahasiswa mahasiswaByPk,mahasiswaLast,buffer,newMahasiswa;

  for(int i = 1; i <= sizeData; i++){
    buffer = readMahasiswa(database_mahasiswa, i); 
    if(buffer.pk == pk){ 
      mahasiswaByPk = buffer;
      positionData = i;
    }
  }
  mahasiswaLast = readMahasiswa(database_mahasiswa, sizeData);
  if(mahasiswaByPk.pk <= 0 | mahasiswaByPk.pk > mahasiswaLast.pk) {
    std::cout<<"pk "<<pk<< " tidak ditemukan!"<< std::endl;
    return;
  }
  system("clear");
  std::cout << "\nData mahasiswa ditemukan:\n" << std::endl;
  std::cout << "pk.\tNIM.\tNama.\tJurusan." << std::endl;        
  std::cout << mahasiswaByPk.pk << "\t";
  std::cout << mahasiswaByPk.NIM << "\t";
  std::cout << mahasiswaByPk.nama << "\t";
  std::cout << mahasiswaByPk.jurusan << std::endl;
  std::cout << std::endl;

  //update input mahasiswa
  std::cout << "Masukan data baru mahasiswa :" << std::endl;
  std::cout << "Nama\t: ";
  std::cin.getline(newMahasiswa.nama,crud::lenNama);
  std::cout<<"NIM\t: ";
  std::cin.getline(newMahasiswa.NIM,crud::lenNIM);
  std::cout<<"Jurusan\t: ";
  std::cin.getline(newMahasiswa.jurusan,crud::lenJurusan);
  std::cout<<std::endl;

  std::cout<<"Simpan perubahan?(y/n): ";
  std::cin >> isSave;
  if((isSave != 'y') && (isSave != 'Y')){
    std::cout<<"sukses membatalkan simpan data!"<<std::endl;
    return;
  }
  newMahasiswa.pk = mahasiswaByPk.pk;

  //update database by posisition
  writeData(positionData, newMahasiswa, database_mahasiswa);
  std::cout << "berhasil update mahasiswa!"<<std::endl;
}


//menghapus data mahasiswa
void crud::deleteMahasiswa(std::fstream &database_mahasiswa){
  //file temp
  std::fstream tempFile,newDataBase;
  tempFile.open("temp.dat",std::ios::trunc| std::ios::out|std::ios::in|std::ios::binary);
  //buffer data mahsiswa
  crud::Mahasiswa buffer;
  int pk,sizeData,sizeDataTemp,position;
  bool isPkOut = false;
  displayMahasiswa(database_mahasiswa);
  std::cout << "pilih pk mahasiswa :";
  std::cin >> pk;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  system("clear");
  //mengambil panjang data 
  sizeData = getDataSize(database_mahasiswa);
  for (int i=(position=1,i=position); i<=sizeData; (i++,position++)) {
    buffer = readMahasiswa(database_mahasiswa, i);
    //menuliskan buffer di tempfile
    if(buffer.pk != pk) {
      writeData(position, buffer, tempFile);
    }
    else {
      isPkOut = true;
      std::cout << "\nberhasil menghapus data!" << std::endl;
      position--;
    }
  }  
  //jika pk tidak ditemukan
  if(!isPkOut){
    std::cout << "pk tidak ditemukan!" << std::endl;
    return;
  }
  sizeDataTemp = getDataSize(tempFile);
  //menutup file database
  database_mahasiswa.close();
  database_mahasiswa.open("database_mahasiswa.bin",std::ios::trunc|std::ios::out|std::ios::binary);
  database_mahasiswa.close();
  //membuka file database_mahasiswa baru
  database_mahasiswa.open("database_mahasiswa.bin",std::ios::out|std::ios::in|std::ios::binary);

  for(int j=1; j<=sizeDataTemp; j++){
    buffer = readMahasiswa(tempFile, j);
    writeData(j, buffer, database_mahasiswa);
  }
  tempFile.close();
  displayMahasiswa(database_mahasiswa);
}
