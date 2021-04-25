# soal-shift-sisop-modul-2-C11-2021
## Anggota
* James Raferty Lee 	(05111940000055)
* Mohammad Tauchid		(05111940000136)
* Kevin Davi Samuel		(05111940000157)

# Soal dan Penjelasan Jawaban
## Soal Nomor 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. 

Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany.

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

**(a)** Dikarenakan Stevany sangat menyukai huruf **Y**, Steven ingin nama folder-foldernya adalah **Musyik** untuk mp3, **Fylm** untuk mp4, dan **Pyoto** untuk jpg.

**(b)** Untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).

**(c)** Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu **meng-extract-nya** setelah didownload, serta

**(d)** **memindahkannya** ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

**(e)** Untuk memudahkan Steven, ia ingin semua hal di atas berjalan **otomatis** 6 jam sebelum waktu ulang tahun Stevany).

**(f)** Setelah itu pada **waktu** ulang tahunnya Stevany, semua folder akan di zip dengan nama **Lopyu_Stevany.zip** dan semua folder akan di **delete**(sehingga hanya menyisakan .zip).

## Jawaban Nomor 1
**(a)** Pertama, kita diminta untuk membuat folder dengan nama-nama yang telah ditentukan. Programnya adalah sebagai berikut.

```c
if (child_id == 0) {
	child_id = fork();
	if (child_id == 0) {
		for (idx = 0; idx < 3; idx++) {
			if (0 == fork()) continue;
			execv("/bin/mkdir", mkdir[idx]);
		}
	}
	// program selanjutnya
}
```

Program tersebut membuat *child process* baru dan menyimpan id-nya di `child_id`. Setelah dicek apakah *child process* yang berjalan, program akan melakukan looping untuk membuat folder. Program ini menggunakan array `mkdir` untuk memudahkan proses looping. Isi dari `mkdir` adalah sebagai berikut.

```c
char *mkdir[][3] = {
	{"mkdir", "Musyik", NULL}, 
	{"mkdir", "Pyoto", NULL}, 
	{"mkdir", "Fylm", NULL}
};
```

**(b)** Program kedua adalah program yang digunakan untuk men-download file zip yang dibutuhkan dari link yang telah disediakan. Programnya adalah sebagai berikut.

```c
// program sebelumnya
else {
	while (wait(&status) > 0);
	child_id = fork();
	if (child_id == 0) {
		for (idx = 0; idx < 3; idx++) {
			if (0 == fork()) continue;
			execv("/usr/bin/wget", wget[idx]);
		}
	}
	// program selanjutnya
}
```

Program ini memastikan bahwa program sebelumnya sudah selesai dijalankan dan sudah berhenti dengan fungsi `wait()`. Setelah itu, sama seperti jawaban **(a)**, buat *child process* baru kemudian jalankan program. Program ini juga melakukan looping pada array `wget` dengan isi sebagai berikut.

```c
char *wget[][4] = {
	{"wget", "-nc", link[0], NULL},
	{"wget", "-nc", link[1], NULL},
	{"wget", "-nc", link[2], NULL}
};
```

Di dalam array `wget` terdapat array lagi yang bernama `link` yang merupakan kumpulan link download file. Isi dari array tersebut adalah sebagai berikut.

```c
char *link[] = {
	"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
	"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
	"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
};
```

**(c)** Program ketiga adalah program untuk meelakukan unzip pada file zip yang telah didownload. Program ini meng-ekstrak file download dengan cara sama seperti program-program sebelumnya. Programnya sebagai berikut.

```c
	// program sebelumnya
	else {
		while (wait(&status) > 0);
		sleep(5);
		child_id = fork();
		if (child_id == 0) {
			for (idx = 0; idx < 3; idx++) {
				if (0 == fork()) continue;
				execv("/usr/bin/unzip", unzip[idx]);
			}
		}
		// program selanjutnya
	}
```

Diprogram ini terdapat fungsi `sleep` dengan parameter `5` yang berfungsi untuk menunggu 5 detik. Hal ini berguna agar file dipastikan telah di-download dengan benar sehingga sewaktu di-unzip file nya tidak corrupt. Isi dari array `unzip` adalah sebagai berikut.

```c
char *unzip[][3] = {
	{"unzip", output_file[0], NULL},
	{"unzip", output_file[1], NULL},
	{"unzip", output_file[2], NULL}
};
```

Terdapat array `output_file` yang berfungsi menyimpan nama file hasil download. Dikarenakan ada masalah yang tidak diketahui penyebabnya, maka nama file menggunakan nama bawaan dari wget. Isi dari `output_file` adalah sebagai berikut.

```c
char *output_file[] = {
	"uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
	"uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
	"uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
};
```

**(d)** Program selanjutnya adalah program yang memindahkan isi file dari folder ekstrak ke folder yang diinginkan. Cara yang digunakan berbeda. Isi dari program ini adalah sebagai berikut.

```c
		// program sebelumnya
		else {
			while (wait(&status) > 0);
			sleep(5);
			child_id = fork();
			if (child_id == 0) {
				for (idx = 0; idx < 3; idx++) {
					if (0 == fork()) continue;
					DIR *dp;
			        struct dirent *ep;
			        char src[50];
			        char dest[50];
			        char path[100]; 

			        getcwd(path, sizeof(path));
                    strcat(path,"/");
                    strcpy(dest,"");
                    strcpy(dest,path);
                    strcat(dest,dest_dir[idx]);
                    strcat(path,src_dir[idx]);
                    dp = opendir(path);

                    while ((ep = readdir (dp))) {
                        strcpy(src,"");
                        strcpy(src,path);
                        if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
                            if (0 == fork()) {
                                strcat(src,"/");
                                strcat(src,ep->d_name);
                                char *argv[] = {"mv", src, dest, NULL};
                                execv("/bin/mv", argv);      
                            } else {
                            	waitpid(child_id, &status, 0);
                            }
                        }
                    }
				}
			}
			// program selanjutnya
		}
```

Program tersebut mengggunakan library khusus yang disebut `dirent.h`. Inti dari program ini adalah membaca isi dari folder asal (source) satu per satu lalu melakukan move ke folder tujuan (destination) hingga tidak ada lagi file yang tersisa. Terdapat dua array yang membantu program tersebut yaitu `src_dir` dan `dest_dir` yang isinya adalah sebagai berikut.

```c
char *src_dir[3] = {
	"MUSIK",
	"FOTO",
	"FILM"
};
char *dest_dir[3] = {
	"Musyik",
	"Pyoto",
	"Fylm"
};
```

Setelah semua program sebelumnya telah dijalankan dan menyisakan folder yang seharusnya, folder hasil ekstrak, dan file hasil download, maka selanjutnya adalah menghapus folder dan file yang tidak diinginkan sehingga menyisakan folder yang diinginkan beserta file nya (**Musyik**, **Pyoto**, **Fylm**).

```c
			// program sebelumnya
			else {
				sleep(10);
				for (idx = 0; idx < 3; idx++) {
					if (0 == fork()) continue;
					execv("/bin/rm", rm[idx]);
				}
				for (idx = 0; idx < 3; idx++) {
					if (0 == fork()) continue;
					execv("/bin/rmdir", rmdir[idx]);
				}
			}
			// program selanjutnya
```

Pada program tersebut terdapat `sleep(10)` yang berfungsi untuk menunda eksekusi program selama 10 detik untuk memastikan program sebelumnya telah selesai berjalan (program move). Setelah program sebelumnya benar-benar telah selesai, maka jalankan program remove. Program ini menggunakan dua array yaitu `rm` dan `rmdir` yang isinya adalah sebagai berikut.

```c
char *rm[][3] = {
	{"rm", output_file[0], NULL},
	{"rm", output_file[1], NULL},
	{"rm", output_file[2], NULL}
};
char *rmdir[][3] = {
	{"rmdir", "MUSIK", NULL},
	{"rmdir", "FOTO", NULL},
	{"rmdir", "FILM", NULL}
};
```

**(e)** Untuk menjalankan semua program sebelumnya tepat 6 jam sebelum ulang tahun Stevany, dibutuhkan library `time.h` untuk memperoleh localtime komputer. 

```c
struct tm *Sys_T;
time_t Tval = time(NULL);
Sys_T = localtime(&Tval);
```

Setelah itu lakukan pengecekan, apakah waktu saat ini telah sesuai dengan waktu yang diinginkan yaitu 6 jam sebelum ulang tahun Stevany.

```c
if (Sys_T->tm_mday == 9 &&
	Sys_T->tm_mon+1 == 4 &&
	Sys_T->tm_hour == 16 &&
	Sys_T->tm_min == 22) {
		// program sebelumnya
}
// program selanjutnya
```

**(f)** Untuk Program terakhir, yang pertama dilakukan adalah mengecek apakah waktu saat ini adalah waktu tepat ulang tahun Stevany dengan cara

```c
else if (Sys_T->tm_mday == 9 &&
	Sys_T->tm_mon+1 == 4 &&
	Sys_T->tm_hour == 22 &&
	Sys_T->tm_min == 22) {
	// program selanjutnya
}
```

Setelah dicek dan hasilnya **true**, maka jalankan program untuk men-zip semua folder dan menghapus semua folder. Programnya adalah sebagai berikut.

```c
	child_id = fork();
	if (child_id == 0) {
		char *argv[] = {"zip", "-r", "Lopyu_Stevany", "Musyik", "Fylm", "Pyoto", NULL};
		execv("/usr/bin/zip", argv);
	} else {
		while (wait(&status) > 0);
		char *argv[] = {"rm", "-r", "Musyik", "Fylm", "Pyoto", NULL};
		execv("/bin/rm", argv);
	}
```

Yang pertama dilakukan adalah `fork` untuk membuat *child process* baru lalu lakukan zip dengan flag `-r` yang berfungsi untuk men-zip folder beserta isinya. Setelah zip selesai, maka hapus semua folder dengan flag `-r` yang juga untuk menghapus folder beserta isinya.

## Soal Nomor 2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

**(a)** Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

**(b)** Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.

**(c)** Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”. 

**(d)** Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.

**(e)** Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.

## Jawaban Nomor 2

**(a)** 
```c
pid_t child_id[10];
  int status[10];
  
  child_id[0] = fork();

  if (child_id[0] == 0) {
  	char *argv[] = {"mkdir", "-p", "modul2/petshop", NULL};
	execv("/bin/mkdir", argv);
  }
  
  while ((wait(&status[0])) > 0);
  child_id[1] = fork();
  if (child_id[1] == 0) {
  	char *argv[] = {"unzip", "/home/solxius/Downloads/pets.zip", "-d", "/home/solxius/modul2/petshop/", NULL};
	execv("/bin/unzip", argv);
  }
```
Pertama, kita diminta untuk membuat folder "/home/[user]/modul2/petshop" dan mengekstrak zip yang kita diberikan ke dalamnya. Untuk melakukan itu, kita membuat anak, dan anak itu kita suruh untuk membuat folder modul2, dan folder petshop di dalamnya dengan command execv. Lalu, kita beli wait, supaya parent processnya bisa menunggu child process untuk menyelesaikan proses pembuatan foldernya. Setelah child process sudah selesai, kita membuat child baru lagi untuk men-unzip zip yang kita diberikan ke dalam modul2/petshop.

```c
  while ((wait(&status[1])) > 0);
  child_id[2] = fork();
  if (child_id[2] == 0) {
  	glob_t globbuf;
	int err = glob("/home/solxius/modul2/petshop/*/", 0, NULL, &globbuf);
	int numberofmatch = 3+(int) globbuf.gl_pathc;
	char *argv[100] = {"rm", "-r"};
	int count = 2;
        for (int i = 0; globbuf.gl_pathv[i]; i++) {
            argv[count] = globbuf.gl_pathv[i];
            count++;
        }
        
     	argv[count+1] = NULL;

	execv("/bin/rm", argv);
  }
```
Selanjutnya, kita diminta untuk menghapus semua folder yang ada di dalam folder modul2/petshop. Untuk melakukan itu, kita menggunakan glob. Glob gunanya untuk mencari semua folder dengan filter yang ditentukan (di case ini, wildcard). Lalu, dengan result yang diberikan glob, kita membuat child baru dan menggunakan execv untuk meng-remove semua hasil result glob.

**(b, c, d, e)** 
```c

  struct dirent **namelist;
  int n = scandir("/home/solxius/modul2/petshop/", &namelist, NULL, alphasort);
  if (n == -1) {
      perror("scandir");
      exit(EXIT_FAILURE);
  }
  char filename[n][50];
  for(int i=0; i<n; i++) {
       strcpy(filename[i], namelist[i]->d_name);
       free(namelist[i]);
  }
  free(namelist);
  for(int i=2; i<n; i++){
  	int test = handleElse(filename[i], 0);
  }  
```
Selanjutnya, untuk dapat menkategorisasikan hewan-hewannya, kita mengambil dulu nama-nama filenya dengan command scandir, lalu memasukkannya ke dalam array. Lalu, untuk setiap nama file, kita berikan ke dalam fungsi HandleElse.

```c
int animalCount = 0, nameCount = 0, ageCount = 0;
char animals[55][20];
char names[55][20];
char ages[55][3];

int handleElse(char filename[], int j){
	j = handleAnimal(filename, j);
	j = handleName(filename, j);
	j = handleAge(filename, j);
```
Dengan variabel global untuk menampung tipe, nama, dan umurnya, kita di fungsi handleElse, memberikan nama file-filenya ke dalam fungsi handleAnimal, handleName, dan handleAge, untuk menyimpan.

```c
int handleAnimal(char filename[], int j){
	int charCount=0;
	for(; j<strlen(filename)-4; j++){
  		if(filename[j] == ';'){
  			break;
  		}
  		animals[animalCount][charCount] = filename[j];
  		charCount++;
  	}
  	animalCount++;
  
 	return j;
}
int handleName(char filename[], int j){
	int charCount=0;
	for(j=j+1; j<strlen(filename)-4; j++){
  		if(filename[j] == ';'){
  			break;
  		}
  		names[nameCount][charCount] = filename[j];
  		charCount++;
  	}
  	nameCount++;
  	return j;
}
int handleAge(char filename[], int j){
	int charCount=0;
	for(j=j+1; j<strlen(filename)-4; j++){
  		if(filename[j] == '_'){
  			j++;
  			break;
  		}
  		ages[ageCount][charCount] = filename[j];
  		charCount++;
  	}
  	ageCount++;
  	return j;
}
```
Selanjutnya, fungsi di atas adalah untuk menyimpan nama-nama dari setiap hewan, nama, dan umur. Untuk setiap karakter, jika ditemukan ;, langsung return indeksnya. Lalu, indeks diberikan ke fungsi selanjutnya untuk memulai fungsi mereka. Pada handleAge, saat bertemu _ atau jika sudah selesai, direturn. Dengan itu, semua telah disimpan.

```c
	pid_t cid[10];
  	int stat[10];
  	char loc[100] = "modul2/petshop/";
  	char curloc[100] = "modul2/petshop/";
  	char animalName[50], animalName2[50], animalName3[50];
  	strcpy(animalName, animals[animalCount-1]);
  	strcpy(animalName2, animals[animalCount-1]);
  	strcpy(animalName3, animals[animalCount-1]);
  	strcat(loc, animalName);
  	strcat(curloc, filename); 	
  
  	cid[0] = fork();

  	if (cid[0] == 0) {
  		char *argv[4] = {"mkdir", "-p", loc, NULL};
		execv("/bin/mkdir", argv);
 	 }
  
 	 while ((wait(&stat[0])) > 0);
```

Selanjutnya, kita membuat child baru untuk menggunakan exec dan membuat folder untuk setiap hewan. Setiap kali melewati satu file, akan dilakukan mkdir, namun karena ada '-p', yang fungsinya adalah untuk dibiarkan jika sudah ada foldernya, tidak ada folder duplikat.

```c
	 char log[30]="";
 	 
 	 FILE *fp;
 	 strcat(log, "/home/solxius/modul2/petshop/");
 	 strcat(log, animalName2);
 	 strcat(log, "/keterangan.txt");
 	 
 	 fp = fopen (log, "a");
   	 fprintf(fp, "nama : %s\numur : %s\n\n", names[nameCount-1], ages[ageCount-1]);  
   	 fclose(fp);
```
Selanjutnya, untuk file itu, kita membuat file dengan nama 'keterangan.txt' di folder tersebut. a berarti append (jika tidak ada, dibikinkan filenya, jika ada, hanya append). Kita memasukkan nama dan umur yang sudah disimpan.

```c
	 char loca[100] = "modul2/petshop/";
   	 strcat(loca, animalName3);
 	 strcat(loca, "/");
  	 strcat(loca, names[nameCount-1]);
  	 strcat(loca, ".jpg");
 	 
 	 if(j<strlen(filename)-4){
 	 	cid[1] = fork();

	  	if (cid[1] == 0) {
	  		char *argv[4] = {"cp", curloc, loca, NULL};
			execv("/bin/cp", argv);
	 	 }
	 	 while ((wait(&stat[1])) > 0);
  		handleElse(filename, j);
  	 }
 	 
 	 else{
 	 	cid[1] = fork();

	  	if (cid[1] == 0) {
	  		char *argv[4] = {"mv", curloc, loca, NULL};
			execv("/bin/mv", argv);
	 	 }
	 	 while ((wait(&stat[1])) > 0);
 	 	return j;
 	 }
```
Di sini, kita simpan path, lalu mengecek. Jika, indeks untuk file itu masih di bawah strlen(filename)-4 (karena ada .jpg nya), berarti di handleAge, ditemukan _ sehingga masih ada hewan lagi, jadi kita hanya meng-copy ke foldernya (dengan mengganti nama sesuai nama yang sudah disimpan), dan dilakukan handleElse dengan indeks sekarang.

Jika sudah selesai, langsung move.

## Dokumentasi
Saat unzip:

![sisop1](https://user-images.githubusercontent.com/68369091/115996623-39878a80-a60a-11eb-8fdd-e8957c694aa4.png)

Folder-foldernya:

![sisop2](https://user-images.githubusercontent.com/68369091/115996627-3b514e00-a60a-11eb-81c3-e3a8d2e07482.png)

Folder cat:

![sisop3](https://user-images.githubusercontent.com/68369091/115996630-3be9e480-a60a-11eb-9620-fb41b10c7edd.png)

Folder dog:

![sisop4](https://user-images.githubusercontent.com/68369091/115996631-3c827b00-a60a-11eb-99b0-e2bcc33042f9.png)

Isi keterangan dog:

![sisop5](https://user-images.githubusercontent.com/68369091/115996632-3c827b00-a60a-11eb-999e-63b26951df9b.png)


## Kendala
- Memiliki beberapa kendala dengan fork(). 
- fopen() memiliki beberapa masalah karena tidak memakai path yang full
- glob() susah sehingga harus mencari dokumentasi yang banyak.

## Soal Nomor 3
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

**(a)** Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

**(b)** Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

**(c)** Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

**(d)** Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

**(e)** Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dsdengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
