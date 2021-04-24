# soal-shift-sisop-modul-2-C11-2021
## Anggota
* James Raferty Lee 	(05111940000055)
* Mohammad Tauchid		(05111940000136)
* Kevin Davi Samuel		(05111940000157)

# Soal dan Penjelasan Jawaban
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

