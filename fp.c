#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct akun{
	char nama[40];
	char username[16];
	char password[16];
	int simpanan;
	int pinjaman;
	int besarcicilan;
	int cicilan;
	char kelamin[15];
	char pekerjaan[15];
	char nohp[15];
};
typedef struct akun anggota;

//Membuat array akun sebanyak 20 anggota
anggota akun[20];
//indeks=indeks untuk input data.
//indeks juga diguanakan untuk melacak banyak data.
int indeks=0;
//Variabel ascended menampung boolean apakah array akun anggota sudah diurutkan secara ascending atau belum.
//Akan berubah ketika terjadi pengurutan(true jika ascending, false jika descending). Penambahan data akan mempengaruhi ascended.
int ascending=0;
int metodeurut=0;
int input;

void buatAkun(){
	printf("============Buat Akun============\n");
	printf("Anda akan membayar simpanan pokok sebesar Rp.1.000.000 pada koperasi.\n");
	printf("----------------------------------------------\n\n");
	printf("Nama : ");
	scanf(" %[^\n]%*c", &akun[indeks].nama);
	printf("------------------------------------\n");
	printf("Anda Laki-Laki atau perempuan?\n");
	printf("1. Laki Laki\n");
	printf("2. Perempuan\n");
	kelamin:
	printf("Input : ");
	scanf("%d",&input);
	if(input==1){
		strcpy(akun[indeks].kelamin,"Laki-laki");
	}
	else if(input==2){
		strcpy(akun[indeks].kelamin,"Perempuan");
	}
	else{
		goto kelamin;
	}
	printf("------------------------------------\n");
	printf("Pekerjaan : ");
	scanf(" %[^\n]%*c", &akun[indeks].pekerjaan);
	printf("------------------------------------\n");
	printf("Nomor HP : ");
	scanf(" %[^\n]%*c", &akun[indeks].nohp);
	printf("------------------------------------\n\n");
	printf("Username : ");
	scanf(" %[^\n]%*c", &akun[indeks].username);
	//Pengecekan username duplikasi
	int i=0;
	for(i=0; i<indeks; i++){
		if(!strcmp(akun[i].username, akun[indeks].username)){
			printf("Username ini telah ada.");
			getch();
			system("cls");
			return;
		}
	}
	if(!strcmp(akun[indeks].username, "admin")){
		printf("Anda tidak diperkenankan untuk menggunakan username ini.");
		getch();
		system("cls");
		return;
	}
	printf("Password : ");
	scanf(" %[^\n]%*c", &akun[indeks].password);
	akun[indeks].simpanan=0;
	akun[indeks].pinjaman=0;
	akun[indeks].cicilan=0;
	indeks++;
}

int cekLogin(char *user, char *password){
	int i=0;
	if(password==NULL){
		for(i=0; i<indeks; i++){
			if(!strcmp(akun[i].username, user)){
				return i;
			}
		}
		return -1;
	}
	else{
		for(i=0; i<indeks; i++){
			if(!strcmp(akun[i].username, user)){
				if(!strcmp(akun[i].password, password)){
					return i;
				}
			}
		}
		return -1;
	}
}

void hapus(int x){
	for(x;x<indeks;x++){
		strcpy(akun[x].nama,akun[x+1].nama);
		strcpy(akun[x].kelamin,akun[x+1].kelamin);
		strcpy(akun[x].pekerjaan,akun[x+1].pekerjaan);
		strcpy(akun[x].nohp,akun[x+1].nohp);
		strcpy(akun[x].username,akun[x+1].username);
		strcpy(akun[x].password,akun[x+1].password);
		akun[x].pinjaman=akun[x+1].pinjaman;
		akun[x].simpanan=akun[x+1].simpanan;
		akun[x].cicilan=akun[x+1].cicilan;
		akun[x].besarcicilan=akun[x+1].besarcicilan;
	}
	indeks-=1;
}

void tampil(){
	int i=0;
	if(indeks>0){
		for(i=0;i<indeks;i++){
			printf("==========Data Anggota %d=========\n", i+1);
			printf("Nama\t\t: %s\n",akun[i].nama);
			printf("Kelamin\t\t: %s\n",akun[i].kelamin);
			printf("Pekerjaan\t: %s\n",akun[i].pekerjaan);
			printf("Nomor HP\t: %s\n",akun[i].nohp);
			printf("-----------------------------\n");
			printf("Tabungan\t: %d\n",akun[i].simpanan);
			printf("Pinjaman\t: %d\n",akun[i].pinjaman);
			printf("Besar Cicilan\t: %d\n",akun[i].besarcicilan);
			printf("-----------------------------\n");
			printf("username\t: %s\n",akun[i].username);
			printf("password\t: %s\n",akun[i].password);
			printf("=====================================\n\n");	
		}
	}
	else{
		printf("============Daftar Anggota============\n\n");
		printf("Tidak ada anggota...\nSilahkan tambahkan anggota terlebih dahulu...\n");
	}
}

void sort(int jenis, int metode){
	int gap,i,j;
	//menampung struct sementara
	struct akun temp;
	for (gap=indeks/2; gap>0; gap/=2){
		for (i=gap; i<indeks; i++){
			temp=akun[i];
			
			//Penentuan Jenis(berdasarkan) pengurutan dan metode(ascend/descend) pengurutan.
			if (jenis==1){
				if(metode==1){
					for (j=i; j>=gap && strcmp(akun[j-gap].nama, temp.nama)>0; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;		
				}
				else{
					for (j=i; j>=gap && strcmp(akun[j-gap].nama, temp.nama)<0; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;
				}
			}
			else if (jenis==2){
				if(metode==1){
					for (j=i; j>=gap && strcmp(akun[j-gap].username, temp.username)>0; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;		
				}
				else{
					for (j=i; j>=gap && strcmp(akun[j-gap].username, temp.username)<0; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;
				}
			}
			else if (jenis==3){
				if(metode==1){
					for (j=i; j>=gap && akun[j-gap].simpanan > temp.simpanan; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;		
				}
				else{
					for (j=i; j>=gap && akun[j-gap].simpanan < temp.simpanan; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;
				}
			}
			else if (jenis==4){
				if(metode==1){
					for (j=i; j>=gap && akun[j-gap].pinjaman > temp.pinjaman; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;		
				}
				else{
					for (j=i; j>=gap && akun[j-gap].pinjaman < temp.pinjaman; j-=gap){
						akun[j]= akun[j-gap];
					}
					akun[j]= temp;
				}
			}
		}
	}
}

//Fungsi untuk mencari nilai terendah antara 2 value(Untuk search)
int min(int num1, int num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}

cari(char *dicari, int jenis){
	//Mencari range blok untuk diskip pencariannya.
	int jump=sqrt(indeks);
	int back=0;
	
	//Mencari yang dicari di setiap blok
	if(jenis==1){
		while(strcmp(akun[min(jump, indeks)-1].nama, dicari)<0){
			back=jump;
			jump+=sqrt(indeks);
			if(back>=indeks){
				//Tidak ketemu
				return -1;
			}
		}
		
		//Menggunakan linear search untuk mencari. dimulai dari variable back
		while(strcmp(akun[back].nama, dicari)<0){
			back++;
			
			//Jika mencapai blok selanjutnya atau indeks terakhir, maka yang dicari tidak ketemu.
			if(back==min(jump,indeks)){
				return -1;
			}
		}
		//Jika ternyata ketemu, maka fungsi akan return nilai indeks dari array akun yang dicari
		if(!strcmp(akun[back].nama, dicari)){
			return back;
		}
		return -1;
	}
	else if(jenis==2){
		while(strcmp(akun[min(jump, indeks)-1].username, dicari)<0){
			back=jump;
			jump+=sqrt(indeks);
			if(back>=indeks){
				//Tidak ketemu
				return -1;
			}
		}
		
		//Menggunakan linear search untuk mencari. dimulai dari variable back
		while(strcmp(akun[back].username, dicari)<0){
			back++;
			
			//Jika mencapai blok selanjutnya atau indeks terakhir, maka yang dicari tidak ketemu.
			if(back==min(jump,indeks)){
				return -1;
			}
		}
		//Jika ternyata ketemu, maka fungsi akan return nilai indeks dari array akun yang dicari
		if(!strcmp(akun[back].username, dicari)){
			return back;
		}
		return -1;
	}
}




//Former codeblock for jumpsearch method by username
/*
int cariData(char *x){
	int jump = sqrt(indeks);
	int back = 0;
	while(min(jump, indeks)-1 < indeks){
		back = jump;
		jump += sqrt(indeks);
		if (back >= indeks){
			return -1;
		}
	}
	while (back < indeks){
		back++;
		
		if(back == min(jump, indeks)){
			return -1;
		}
	}
		
	if (akun[back].username == x){
		return back;
		printf("Ketemu!!");
	}
	return -1;
}
*/

int main(){
	//variabel program
	char user[16];
	char password[16];
	int login=-1;
	int keluar=0;
	int i;
	//Atribut koperasi
	int kas=5000000, pinjam, cicil;
	
	//FILE
	FILE * fpbuka;
	fpbuka = fopen("data.txt", "r");
	
	if(fpbuka==0){
		printf("Warning... Gagal menginisialisasi database...\n");
	}
	else{
		while(!feof(fpbuka)){
			for(i=0;i<=3;i++){
				if(i==0){
					fscanf(fpbuka, "%d", &kas);
				}
				else if(i==1){
					fscanf(fpbuka, "%d", &indeks);
				}
				else if(i==2){
					fscanf(fpbuka, "%d", &ascending);
				}
				else if(i==3){
					fscanf(fpbuka, "%d", &metodeurut);
				}
			}
			for(i=0;!feof(fpbuka);i++){
				fscanf(fpbuka, " %[^\n]%*c", &akun[i].nama);
				fscanf(fpbuka, " %[^\n]%*c", &akun[i].username);
				fscanf(fpbuka, " %[^\n]%*c", &akun[i].password);
				fscanf(fpbuka, " %[^\n]%*c", &akun[i].kelamin);
				fscanf(fpbuka, " %[^\n]%*c", &akun[i].pekerjaan);
				fscanf(fpbuka, " %[^\n]%*c", &akun[i].nohp);
				fscanf(fpbuka, "%d", &akun[i].simpanan);
				fscanf(fpbuka, "%d", &akun[i].pinjaman);
				fscanf(fpbuka, "%d", &akun[i].besarcicilan);
				fscanf(fpbuka, "%d\n", &akun[i].cicilan);
			}
		}
		fclose(fpbuka);
	}
	
	
	do{
		menu:
		if(login==-1){
			printf("============Koperasi============\n");
			printf("Selamat datang di program koperasi Maju Mundur!\n");
			printf("Silahkan login terlebih dahulu!\n");
			printf("---------------------------------\n\n");
			printf("1. Login\n");
			printf("2. Buat akun\n");
			printf("=================================\n");
			printf("0. Keluar\n\n");
			printf("Input : ");
			scanf("%d", &input);
			system("cls");
			
			if(input==1){
				login:
				printf("============Koperasi============\n");
				printf("----------Login Anggota---------\n\n");
				printf("Username : ");
				scanf(" %[^\n]%*c", &user);
				//Pengecekan username pada akun
				//Login Admininstrator
				if(!strcmp(user, "admin")){
					printf("Password : ");
					scanf(" %[^\n]%*c", &password);
					if(!strcmp(password, "admin123")){
						login=-2;
						printf("Login adminstrator terdeteksi.");
						getch();
						system("cls");
					}
					else{
						printf("Password Salah!");
						getch();
						system("cls");
						goto login;
					}
				}
				//Jika salah :
				else if(cekLogin(user, NULL)==-1){
					printf("\nUsername yang anda masukkan tidak ada dalam database..");
					getch();
					system("cls");
					goto menu;
				}
				//Jika cocok :
				else{
					printf("Password : ");
					scanf(" %[^\n]%*c", &password);
					//Pencocokan username dengan password
					//-1=Salah, ekspektasi variabel login adalah indeks dari array akun.
					login=cekLogin(user, password);
					if(login==-1){
						printf("Password Salah!");
						getch();
						system("cls");
						goto login;
					}
					else{
						printf("Login telah berhasil!");
						getch();
						system("cls");
						goto menu;		
					}	
				}
			}
			else if(input==2){
				buatAkun();
				if(ascending==1){
					sort(metodeurut, 1);
				}
				kas+=1000000;
				system("cls");
			}
			else if(input==0){
				keluar=1;
				system("cls");
				
				remove("data.txt");
				FILE * fpwrite;
				fpwrite = fopen("data.txt", "w");
				
				fprintf(fpwrite, "%d\n",kas);
				fprintf(fpwrite, "%d\n",indeks);
				fprintf(fpwrite, "%d\n",ascending);
				fprintf(fpwrite, "%d\n",metodeurut);
				for(i=0;i<indeks;i++){
					fprintf(fpwrite, "%s\n",akun[i].nama);
					fprintf(fpwrite, "%s\n",akun[i].username);
					fprintf(fpwrite, "%s\n",akun[i].password);
					fprintf(fpwrite, "%s\n",akun[i].kelamin);
					fprintf(fpwrite, "%s\n",akun[i].pekerjaan);
					fprintf(fpwrite, "%s\n",akun[i].nohp);
					fprintf(fpwrite, "%d\n",akun[i].simpanan);
					fprintf(fpwrite, "%d\n",akun[i].pinjaman);
					fprintf(fpwrite, "%d\n",akun[i].besarcicilan);
					fprintf(fpwrite, "%d\n",akun[i].cicilan);
				}
				fclose(fpwrite);	
				printf("==============Koperasi============\n");
				printf("============-------------==========\n");
				printf("Data telah disimpan ke dalam database.\n");
				printf("===================================\n\n");
				printf("Terima Kasih telah menggunakan aplikasi Koperasi Maju Mundur.");
				break;
			}
			else{
				goto menu;
			}
		}
		
		else if(login==-2){
			printf("============ADMINISTRATOR============\n");
			printf("==============Koperasi===============\n");
			printf("1. Manajemen Koperasi\n");
			printf("2. Manajemen Akun Anggota\n\n");
			printf("0. Log Out\n\n");
			scanf("%d", &input);
			system("cls");
			if(input==1){
				koperasi:
				printf("============ADMINISTRATOR============\n");
				printf("1.Kas Koperasi\n");
				printf("-\n");
				printf("-\n");
				printf("0. Kembali\n\n");
				scanf("%d", &input);
				system("cls");
				if(input==1){
					printf("============Koperasi============\n");
					printf("Kas Koperasi saat ini : Rp.%d\n\n", kas);
					printf("Modal Awal Koperasi : Rp.5000000\n");
					printf("Penghasilan dari Simpanan Pokok sebesar : Rp.%d\n", indeks*1000000);
					
					int totalpinjam=0, i, totalsimpan=0;
					for(i=0; i<indeks; i++){
						totalpinjam+=akun[i].pinjaman;
						totalsimpan+=akun[i].simpanan;
					}
					printf("Total Simpanan Anggota : Rp.%d\n",totalsimpan);
					printf("Banyaknya cicilan yang belum lunas : -%d\n",totalpinjam);
					printf("---------------------------------------- +\n");
					printf("Total : Rp.%d (+%d)\n\n",5000000+(indeks*1000000), totalpinjam);
					
					getch();
					system("cls");
				}
				else if(input==0){
					system("cls");
					goto menu;
				}
				else{
					goto koperasi;
				}
			}
			if(input==2){
				anggota:
				printf("============ADMINISTRATOR============\n");
				printf("============Manage Anggota===========\n");
				printf("1. Lihat Data\n");
				printf("2. Hapus Data\n");
				printf("3. Ubah Data\n");
				printf("4. Urutkan Data\n");
				printf("5. Cari Data\n\n");
				printf("0. Kembali\n\n");
				printf("Input : ");
				scanf("%d", &input);
				system("cls");
				if(input==1){
					printf("============Daftar Anggota============\n\n");
					tampil();
					printf("Tekan tombol apa saja untuk kembali...");
					getch();
					system("cls");	
					goto anggota;
				}
				else if(input==2){
					hapus:
					//Pengecekan isi data akun
					if(indeks==0){
						printf("========================\n");
						printf("Tidak ada data! Silahkan input data terlebih dahulu!");
						getch();
						system("cls");
						goto anggota;
					}
					//fungsi tampil()
					printf("============Hapus Anggota============\n");
					printf("Pilih Data Anggota yang ingin dihapus!\n\n");
					tampil();
					printf("Masukkan angka 0 untuk kembali\n");
					printf("\nInput : ");
					scanf("%d", &input);
					system("cls");
					
					int i=input-1;
					if(input==0){
						system("cls");
						goto menu;
					}
					else if(input<=indeks){
					}
					else{
						printf("======================================\n");
						printf("Tidak ada Data anggota pada nomor %d!",input);
						getch();
						system("cls");
						goto hapus;
					}
					printf("============Hapus Anggota============\n");
					printf("Nama\t\t: %s\n",akun[i].nama);
					printf("Kelamin\t\t: %s\n",akun[i].kelamin);
					printf("Pekerjaan\t: %s\n",akun[i].pekerjaan);
					printf("Nomor HP\t: %s\n",akun[i].nohp);
					printf("-----------------------------\n");
					printf("Tabungan\t: %d\n",akun[i].simpanan);
					printf("Pinjaman\t: %d\n",akun[i].pinjaman);
					printf("-----------------------------\n");
					printf("username\t: %s\n",akun[i].username);
					printf("password\t: %s\n",akun[i].password);
					printf("=====================================\n\n");
					printf("Apakah anda ingin menghapus akun ini?\n");
					printf("1. Hapus\n");
					printf("2. Batal\n\n");
					printf("(Kembali ke menu)\n");
					printf("Input : ");
					scanf("%d", &input);
					system("cls");
					if(input==1){
						hapus(i);
						printf("============Hapus Anggota============\n\n");
						printf("Data telah dihapus.");
						getch();
						system("cls");
					}
					else if(input==2){
						goto hapus;
					}
					else{
						goto anggota;
					}
				}
				else if(input==3){
					ubah:
					//Pengecekan isi data akun
					if(indeks==0){
						printf("========================\n");
						printf("Tidak ada data! Silahkan input data terlebih dahulu!");
						getch();
						system("cls");
						goto anggota;
					}
					//fungsi tampil()
					printf("============Ubah Anggota============\n");
					printf("Pilih Data Anggota yang ingin diubah!\n\n");
					tampil();
					printf("Masukkan angka 0 untuk kembali\n");
					printf("\nInput : ");
					scanf("%d", &input);
					system("cls");
					
					int i=input-1;
					if(input==0){
						system("cls");
						goto menu;
					}
					else if(input<=indeks){
					}
					else{
						printf("======================================\n");
						printf("Tidak ada Data anggota pada nomor %d!",input);
						getch();
						system("cls");
						goto hapus;
					}
					printf("============Ubah Anggota============\n");
					printf("Nama\t\t: %s\n",akun[i].nama);
					printf("Kelamin\t\t: %s\n",akun[i].kelamin);
					printf("Pekerjaan\t: %s\n",akun[i].pekerjaan);
					printf("Nomor HP\t: %s\n",akun[i].nohp);
					printf("-----------------------------\n");
					printf("Tabungan\t: %d\n",akun[i].simpanan);
					printf("Pinjaman\t: %d\n",akun[i].pinjaman);
					printf("-----------------------------\n");
					printf("username\t: %s\n",akun[i].username);
					printf("password\t: %s\n",akun[i].password);
					printf("=====================================\n\n");
					printf("Apakah anda ingin mengubah akun ini?\n");
					printf("1. Ubah\n");
					printf("2. Batal\n\n");
					printf("(Kembali ke menu)\n");
					printf("Input : ");
					scanf("%d", &input);
					system("cls");
					if(input==1){
						pilihubah:
						printf("============Ubah Anggota============\n");
						printf("1. Nama\t\t: %s\n",akun[i].nama);
						printf("2. Kelamin\t: %s\n",akun[i].kelamin);
						printf("3. Pekerjaan\t: %s\n",akun[i].pekerjaan);
						printf("4. Nomor HP\t: %s\n",akun[i].nohp);
						printf("-----------------------------\n");
						printf("5. username\t: %s\n",akun[i].username);
						printf("6. password\t: %s\n",akun[i].password);
						printf("=====================================\n\n");
						printf("Pilih data yang ingin diubah.\n");
						printf("0. Kembali ke menu\n\n");
						printf("Input : ");
						scanf("%d", &input);
						system("cls");
						printf("============Ubah Anggota============\n\n");
							
						if(input==1){
							printf("Masukkan Nama Baru : ");
							scanf(" %[^\n]%*c", &akun[i].nama);
							ascending=0;
						}
						else if(input==2){
							ubahkelamin:
							printf("Anda Laki-Laki atau perempuan?\n");
							printf("1. Laki Laki\n");
							printf("2. Perempuan\n");
							kelamin:
							printf("Input : ");
							scanf("%d",&input);
							if(input==1){
								strcpy(akun[i].kelamin,"Laki-laki");
							}
							else if(input==2){
								strcpy(akun[i].kelamin,"Perempuan");
							}
							else{
								goto ubahkelamin;
							}
						}
						else if(input==3){
							printf("Masukkan Pekerjaan Baru : ");
							scanf(" %[^\n]%*c", &akun[i].pekerjaan);
						}
						else if(input==4){
							printf("Masukkan Nomor Hp Baru : ");
							scanf(" %[^\n]%*c", &akun[i].nohp);
						}
						else if(input==5){
							char temp[40];
							printf("Masukkan Username Baru : ");
							scanf(" %[^\n]%*c", &temp);
							//Pengecekan username duplikasi
							int j=0;
							for(j=0; j<indeks; j++){
								if(!strcmp(akun[j].username, temp)){
									printf("Username ini telah ada.");
									getch();
									system("cls");
									goto pilihubah;
								}
							}
							if(!strcmp(temp, "admin")){
								printf("Anda tidak diperkenankan untuk menggunakan username ini.");
								getch();
								system("cls");
								goto pilihubah;
							}
							strcpy(akun[i].username, temp);
							ascending=0;
						}
						else if(input==6){
							printf("Masukkan Password Baru : ");
							scanf(" %[^\n]%*c", &akun[i].password);
						}
						else if(input==0){
							system("cls");
							goto menu;
						}
						else {
							system("cls");
							goto pilihubah;
						}
						printf("============Ubah Anggota============\n");
						printf("1. Nama\t\t: %s\n",akun[i].nama);
						printf("2. Kelamin\t: %s\n",akun[i].kelamin);
						printf("3. Pekerjaan\t: %s\n",akun[i].pekerjaan);
						printf("4. Nomor HP\t: %s\n",akun[i].nohp);
						printf("-----------------------------\n");
						printf("5. username\t: %s\n",akun[i].username);
						printf("6. password\t: %s\n",akun[i].password);
						printf("=====================================\n\n");
						printf("Data telah berhasil diubah!\n");
						getch();
						system("cls");
					}
					else if(input==2){
						goto hapus;
					}
					else{
						goto anggota;
					}
				}
				else if(input==4){
					sort:
					//Pengecekan isi data akun
					if(indeks<2){
						printf("========================\n");
						printf("Data kurang dari 2, Tidak bisa melakukan Pengurutan...");
						getch();
						system("cls");
						goto anggota;
					}
					//fungsi tampil()
					printf("============Sortir Anggota============\n\n");
					printf("Diurutkan berdasarkan apa?\n");
					printf("1. Nama\n");
					printf("2. Username\n");
					printf("3. Simpanan\n");
					printf("4. Pinjaman\n");
					printf("--------------------------------------\n");
					printf("0. Kembali\n\n");
					printf("\nInput : ");
					scanf("%d", &input);
					system("cls");
				
					if(input==1){
						sortnama:
						printf("============Sortir Anggota============\n");
						printf("Sorting : Nama\n");
						printf("--------------------------------------\n\n");
						printf("Silahkan pilih metode pengurutan.\n");
						printf("1. Ascending\n");
						printf("2. Descending\n\n");
						printf("0. Kembali\n\n");
						printf("Input : ");
						scanf("%d", &input);
						
						if(input==1){
							sort(1, 1);
							printf("Data telah berhasil diurutkan!");
							ascending=1;
							metodeurut=1;
							getch();
							system("cls");
						}
						else if(input==2){
							sort(1, 0);
							printf("Data telah berhasil diurutkan!");
							ascending=0;
							getch();
							system("cls");
						}
						else if(input==0){
							system("cls");
							goto sort;
						}
						else{
							system("cls");
							goto sortnama;
						}
					}
					else if(input==2){
						sortusername:
						printf("============Sortir Anggota============\n\n");
						printf("Sorting : Username\n");
						printf("--------------------------------------\n\n");
						printf("Silahkan pilih metode pengurutan.\n");
						printf("1. Ascending\n");
						printf("2. Descending\n\n");
						printf("0. Kembali\n\n");
						printf("Input : ");
						scanf("%d", &input);
						
						if(input==1){
							sort(2, 1);
							printf("Data telah berhasil diurutkan!");
							ascending=1;
							metodeurut=2;
							getch();
							system("cls");
						}
						else if(input==2){
							sort(2, 0);
							printf("Data telah berhasil diurutkan!");
							ascending=0;
							getch();
							system("cls");
						}
						else if(input==0){
							system("cls");
							goto sort;
						}
						else{
							system("cls");
							goto sortusername;
						}
					}
					else if(input==3){
						sortsimpanan:
						printf("============Sortir Anggota============\n\n");
						printf("Sorting : Simpanan\n");
						printf("--------------------------------------\n\n");
						printf("Silahkan pilih metode pengurutan.\n");
						printf("1. Ascending\n");
						printf("2. Descending\n\n");
						printf("0. Kembali\n\n");
						printf("Input : ");
						scanf("%d", &input);
						
						if(input==1){
							sort(3, 1);
							printf("Data telah berhasil diurutkan!");
							ascending=1;
							metodeurut=3;
							getch();
							system("cls");
						}
						else if(input==2){
							sort(3, 0);
							printf("Data telah berhasil diurutkan!");
							ascending=0;
							getch();
							system("cls");
						}
						else if(input==0){
							system("cls");
							goto sort;
						}
						else{
							system("cls");
							goto sortsimpanan;
						}
					}
					else if(input==4){
						sortpinjaman:
						printf("============Sortir Anggota============\n\n");
						printf("Sorting : Pinjaman\n");
						printf("--------------------------------------\n\n");
						printf("Silahkan pilih metode pengurutan.\n");
						printf("1. Ascending\n");
						printf("2. Descending\n\n");
						printf("0. Kembali\n\n");
						printf("Input : ");
						scanf("%d", &input);
						
						if(input==1){
							sort(4, 1);
							printf("Data telah berhasil diurutkan!");
							ascending=1;
							metodeurut=4;
							getch();
							system("cls");
						}
						else if(input==2){
							sort(4, 0);
							printf("Data telah berhasil diurutkan!");
							ascending=0;
							getch();
							system("cls");
						}
						else if(input==0){
							system("cls");
							goto sort;
						}
						else{
							system("cls");
							goto sortpinjaman;
						}
					}
					else if(input==0){
						system("cls");
						goto menu;
					}
					else{
						system("cls");
						goto sort;
					}
				}
				else if(input==5){
					char temp[40];
					int ketemu;
					cari:
					//Pengecekan isi data akun
					if(indeks==0){
						printf("========================\n");
						printf("Tidak ada data akun, silahkan cari anggota terlebih dahulu...");
						getch();
						system("cls");
						goto anggota;
					}
					//fungsi tampil()
					printf("============Cari Anggota============\n\n");
					printf("Dicari berdasarkan apa?\n");
					printf("1. Nama\n");
					printf("2. Username\n");
					printf("--------------------------------------\n");
					printf("0. Kembali\n\n");
					printf("\nInput : ");
					scanf("%d", &input);
					system("cls");
				
					if(input==1){
						printf("============Cari Anggota============\n");
						printf("Searching : Nama\n");
						if(ascending==0 && indeks!=1){
							sort(1,1);
							printf("Data telah terurutkan secara otomatis agar bisa melakukan pencarian\n");
							ascending=1;
						}
						printf("--------------------------------------\n\n");
						printf("Masukkan nama yang dicari : ");
						scanf(" %[^\n]%*c", &temp);
						
						ketemu=cari(temp, input);
						if(ketemu==-1){
							printf("Data tidak ditemukan...");
							getch();
							system("cls");
							goto menu;
						}
						else{
							printf("============Cari Anggota============\n\n");
							printf("==========Data Anggota %d=========\n", ketemu+1);
							printf("Nama\t\t: %s\n",akun[ketemu].nama);
							printf("Kelamin\t\t: %s\n",akun[ketemu].kelamin);
							printf("Pekerjaan\t: %s\n",akun[ketemu].pekerjaan);
							printf("Nomor HP\t: %s\n",akun[ketemu].nohp);
							printf("-----------------------------\n");
							printf("Tabungan\t: %d\n",akun[ketemu].simpanan);
							printf("Pinjaman\t: %d\n",akun[ketemu].pinjaman);
							printf("Besar Cicilan\t: %d\n",akun[ketemu].besarcicilan);
							printf("-----------------------------\n");
							printf("username\t: %s\n",akun[ketemu].username);
							printf("password\t: %s\n",akun[ketemu].password);
							printf("=====================================\n\n");
							printf("Tekan apa saja untuk kembali...");
							getch();
							system("cls");
							goto menu;	
						}
					}
					else if(input==2){
						printf("============Cari Anggota============\n");
						printf("Searching : Username\n");
						if(ascending==0 && indeks!=1){
							sort(1,1);
							printf("Data telah terurutkan secara otomatis agar bisa melakukan pencarian\n");
							ascending=1;
						}
						printf("--------------------------------------\n\n");
						printf("Masukkan username yang dicari : ");
						scanf(" %[^\n]%*c", &temp);
						
						ketemu=cari(temp, input);
						if(ketemu==-1){
							printf("Data tidak ditemukan...");
							getch();
							system("cls");
							goto menu;
						}
						else{
							printf("============Cari Anggota============\n\n");
							printf("==========Data Anggota %d=========\n", ketemu+1);
							printf("Nama\t\t: %s\n",akun[ketemu].nama);
							printf("Kelamin\t\t: %s\n",akun[ketemu].kelamin);
							printf("Pekerjaan\t: %s\n",akun[ketemu].pekerjaan);
							printf("Nomor HP\t: %s\n",akun[ketemu].nohp);
							printf("-----------------------------\n");
							printf("Tabungan\t: %d\n",akun[ketemu].simpanan);
							printf("Pinjaman\t: %d\n",akun[ketemu].pinjaman);
							printf("Besar Cicilan\t: %d\n",akun[ketemu].besarcicilan);
							printf("-----------------------------\n");
							printf("username\t: %s\n",akun[ketemu].username);
							printf("password\t: %s\n",akun[ketemu].password);
							printf("=====================================\n\n");
							printf("Tekan apa saja untuk kembali...");
							getch();
							system("cls");
							goto menu;	
						}
					}
					else if(input==0){
						system("cls");
						goto menu;
					}
					else{
						system("cls");
						goto cari;
					}
				}
				else if(input==0){
					system("cls");
					goto menu;
				}
			}
			else if(input==0){
					printf("========================\n\n");
					printf("Anda akan keluar dari akun.\n");
					printf("1.Ya\n");
					printf("2.Batal\n\n");
					printf("Input : ");
					scanf("%d", &input);
	
					if(input==1){
						login=-1;
					}
					else{
						system("cls");
						goto menu;
					}
					system("cls");
				}
		}
		
		else{
			printf("============Koperasi============\n");
			printf("Selamat datang di koperasi Maju Mundur!\n");
			printf("Ada yang bisa saya bantu?\n");
			printf("--------------------------------\n\n");
			printf("1. Cek tabungan\n");
			printf("2. Simpan uang\n");
			printf("3. Pinjam uang\n");
			printf("4. Bayar cicilan\n");
			printf("5. Bayar Simpanan Wajib\n");
			printf("6. Akun\n");
			printf("---------------------------------\n");
			printf("0. Logout\n");
			printf("=================================\n");
			printf("Input : ");
			scanf("%d", &input);
			system("cls");
			if(input==1){
				printf("============Tabungan============\n");
				if(akun[login].simpanan==0){
					printf("Anda tidak memiliki tabungan...");
					printf("--------------------------------\n\n");
					getch();
					system("cls");
					goto menu;
				}
				printf("Anda memiliki tabungan sebesar Rp.%d\n\n",akun[login].simpanan);
				printf("--------------------------------\n\n");
				printf("Apakah anda ingin mengambil tabungan anda?\n");
				printf("1. Ya\n");
				printf("2. Tidak\n");
				printf("================================\n");
				printf("Input : ");
				scanf("%d",&input);
				system("cls");
				
				if(input==1){
					int uang;
					withdraw:
					printf("============Tabungan============\n");
					printf("-----------Ambil Uang-----------\n");
					printf("Saldo : %d\n",akun[login].simpanan);
					printf("--------------------------------\n");
					printf("0. Kembali\n");
					printf("================================\n\n");
					printf("Masukkan jumlah uang untuk diambil : ");
					scanf("%d", &uang);
					if(uang==0){
						system("cls");
						goto menu;
					}
					else if(uang<akun[login].simpanan){
						akun[login].simpanan-=uang;
						printf("Transaksi berhasil!");
						getch();
						system("cls");
					}
					else if(uang>akun[login].simpanan){
						printf("Saldo anda tidak cukup...");
						getch();
						system("cls");
						goto withdraw;
					}
					else{
						system("cls");
						goto withdraw;
					}
				}				
			}
			else if(input==2){
				printf("============Tabungan============\n\n");
				printf("Masukkan nominal uang : ");
				scanf("%d", &akun[login].simpanan);
				printf("Tabungan telah ditambahkan.\n");
				printf("Uang sejumlah Rp.%d telah ditambahkan ke dalam akun tabungan Anda...", akun[login].simpanan);
				getch();
				system("cls");
			}
			else if(input==3){
				pinjam:
				printf("============Pinjaman============\n\n");
				if(akun[login].pinjaman!=0 || akun[login].cicilan!=0){
					printf("Anda hanya bisa mempunyai 1 pinjaman!");
					getch();
					system("cls");
					goto menu;
				}
				printf("Masukkan nominal uang : ");
				scanf("%d", &pinjam);
				printf("Berapa kali cicilan : ");
				scanf("%d", &cicil);
				if(pinjam==0 || cicil==0){
					goto pinjam;
				}
				system("cls");
				int bunga=(pinjam/cicil)*2/100;
				printf("============Pinjaman============\n\n");
				printf("Anda akan mengirimkan formulir pinjaman untuk :\n");
				printf("*********************************************************************************\n");
				printf("* Pinjaman uang senilai Rp.%d						*\n",pinjam);
				printf("* Dengan total angsuran yang setelah dihitung dengan bunga sebesar Rp.%d\t*\n",pinjam+(bunga*cicil));
				printf("* yang diangsur %d kali per bulan dengan bunga 2%% per bulan.\t\t\t*\n", cicil);
				printf("* Cicilan per bulan yang harus dibayarkan sebesar : Rp.%d\t\t\t*\n",pinjam/cicil+bunga);
				if(pinjam>kas && pinjam!=0){
				printf("*-------------------------------------------------------------------------------*\n");
				printf("* Dikarenakan jumlah pinjaman anda terlalu besar, kemungkinan kami akan     	*\n");
				printf("* meninjau formulir permintaan anda terlebih dahulu.  				*\n");
				}
				printf("*********************************************************************************\n");
				printf("\nApakah anda yakin?\n");
				printf("1. Ya\n");
				printf("2. Tidak\n");
				printf("Input : ");
				scanf("%d", &input);
				system("cls");
				if(input==1){
					if(pinjam<kas){
						akun[login].pinjaman = (pinjam+(bunga*cicil));
						akun[login].cicilan = cicil;					
						akun[login].besarcicilan = pinjam/cicil+bunga;
						kas-=pinjam;
						
						printf("============Pinjaman============\n\n");
						printf("Transaksi berhasil. Anda telah menerima uang pinjaman.\n");
						printf("Silahkan memulai pembayaran cicilan dalam waktu satu bulan.");
						getch();
						system("cls");
					}
					else if(pinjam>kas && pinjam!=0){
						printf("============Pinjaman============\n\n");
						printf("Formulir telah terkirim.\n");
						printf("Kami akan menghubungi anda setelah kami menyetujui pencairan uang pinjaman anda.");
						getch();
						akun[login].cicilan=cicil;
						system("cls");
					}
					else{
						printf("Error!");
						getch();
						system("cls");
					}
				}
				goto menu;
			}
			else if(input==4){
				printf("============Pinjaman============\n\n");
				if(akun[login].pinjaman==0 && akun[login].besarcicilan==0){
					if(akun[login].cicilan>0){
						printf("Anda belum menerima pencairan uang pinjaman.\n");
						printf("Kami akan menghubungi anda setelah kami menyetujui pencairan uang pinjaman anda.");
						getch();
						system("cls");
						goto menu;
					}
					printf("============Pinjaman============\n\n");
					printf("Anda belum mempunyai pinjaman.\n");
					printf("Silahkan membuat/mengirimkan formulir pinjaman terlebih dahulu.");
					getch();
					system("cls");
					goto menu;
				}
				printf("============Pinjaman============\n\n");
				printf("Sisa cicilan anda : Rp.%d\n", akun[login].pinjaman);
				printf("Kurang cicilan : %d kali\n\n", akun[login].cicilan);
				printf("Anda akan membayar sebesar : %d\n\n", akun[login].besarcicilan);
				printf("1. Konfirmasi\n");
				printf("2. Batal\n\n");
				printf("Input : ");
				scanf("%d", &input);
				if (input==1){
					akun[login].pinjaman-=akun[login].besarcicilan;
					akun[login].cicilan-=1;
					//Masuk Kas
					kas+=akun[login].besarcicilan;
					if(akun[login].cicilan==0){
						akun[login].pinjaman=0;
						akun[login].cicilan=0;
						akun[login].besarcicilan=0;
					}
					system("cls");
					printf("============Pinjaman============\n\n");
					printf("Cicilan telah berhasil dibayar.");
					getch();
					system("cls");
				}
				else {
					system("cls");
					goto menu;
				}
			}
			else if(input==5){
				printf("============Simpanan Wajib============\n");
				printf("Anda wajib membayar simpanan wajib mulai bulan depan.");
				getch();
				system("cls");
			}
			else if(input==6){
				pengaturan:
				printf("============Pengaturan Akun============\n\n");
				printf("1. Ganti username\n");
				printf("2. Ganti password\n");
				printf("---------------------------------------\n");
				printf("0. Kembali\n\n");
				printf("Input : "); 
				scanf("%d",&input);
				printf("\n");
				if(input==1){
					char temp[40];
					printf("Masukkan Username Baru : ");
					scanf(" %[^\n]%*c", &temp);
					//Pengecekan username duplikasi
					int i=0;
					for(i=0; i<indeks; i++){
						if(!strcmp(akun[i].username, temp)){
							printf("Username ini telah ada.");
							getch();
							system("cls");
							goto menu;
						}
					}
					if(!strcmp(temp, "admin")){
						printf("Anda tidak diperkenankan untuk menggunakan username ini.");
						getch();
						system("cls");
						goto menu;
					}
					strcpy(akun[login].username, temp);
					printf("Data telah berhasil diubah!\n");
					getch();
					system("cls");
					ascending=0;
				}
				else if(input==2){
					printf("Masukkan Password Baru : ");
					scanf(" %[^\n]%*c", &akun[login].password);
					printf("Data telah berhasil diubah!\n");
					getch();
					system("cls");
				}
				else if(input==0){
					system("cls");
					goto menu;
				}
				else {
					system("cls");
					goto pengaturan;
				}
			}
			else if(input==0){
				printf("============Log Out============\n\n");
				printf("Anda akan keluar dari akun.\n");
				printf("1.Ya\n");
				printf("2.Batal\n\n");
				printf("Input : ");
				scanf("%d", &input);

				if(input==1){
					login=-1;
				}
				system("cls");
			}
		}
	}
	while(keluar==0);
}
