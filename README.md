# FP_SISOP19_F16

## MP3 PLAYER

### THREAD
untuk mengerjakan mp3 player ini dapat menggunakan thread. Fitur-fitur yang di inginkan dalam MP3 Player ini adalah play, pause, resume, previous, next, dan exit. Maka setiap fitur yang ada akan dibuat threadnya masing-masing. MP3 Player ini akan mengambil lagu-lagu yang ada di suatu folder dan membuatnya menjadi sebuah list. Lalu MP3 Player ini bisa memainkan lagu pertama, dan berganti lagu dengan fitur next dan previous. Berikut Step by step membuat MP3 Player :

1. Munculkan List lagu yang ada di sebuah folder

2. Masukan lagu-lagu yang ada di dalam array 2d agar bisa dipanggil saat memanggil fungsi memainkan lagu.

3. Tampilkan menu dan option yang disediakan kepada user dan hal yang ingin dilakukan selanjutnya.

4. untuk fitur pause dan resume dapat dibuat dengan meng hold fungsi yang berada di dalam fungsi memainkan lagu.

```c
while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        while(flag==2){printf("\r");
            if(flag==3) break;
        }
        ao_play(dev, buffer, done);
    }
```
jadi apabila user menginput 2 maka music player akan ter pause, dan jika user memasukan input 3 maka music player akan ter resume.

5. selanjutknya untuk memastikan bisa melakukan next dan previous maka cara yang digunakan adalah dengan menggunakan penanda jika untuk membreak lagu yang sedang berjalan dan melanjutkan lagu ke index yang selanjutnya. maka fungsi memainkan lagu akan dimodifikasi lagi menjadi seperti yang ada dibawah.

```c
while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        while(flag==2){printf("\r");
            if(flag==3) break;
        }
        if(s==1) break;
        ao_play(dev, buffer, done);
    }
```
s adalah variabel stop yang menandakan bahwa lagu akan di break dan dikeluarkan.

6. Untuk fitur exit maka bisa ditambahkan thread baru untuk mengetahui jika tombol exit sudah ditekan

```c
void* mati(void *arg)
{
    while(1){printf("\r");
        if(flag==6)
        {
            pthread_kill(tid1, SIGKILL);
            pthread_kill(tid2, SIGKILL);
            pthread_kill(tid4, SIGKILL);
            pthread_kill(tid5,SIGKILL);
            pthread_kill(tid6,SIGKILL);
            pthread_kill(tid3, SIGKILL);
        }
    }
}
```

### FUSE
Untuk fusenya, ada beberapa tahapan, yaitu :
1. Mengumpulkan semua lagu di /home/user dalam satu folder /home/user/Music.
        Mencari semua file mp3 di semua direktori dalam home. Apabila di dalam direktori ada direktori, lakukan rekursi terhadap fungsi pencarian (fungsi direktori dalam source code). Apabila berupa file, maka cek, apakah tipe file tersebut .mp3 atau bukan, jika iya maka copy file tersebut ke /home/user/Music. Akan dilakukan hingga tidak ada direktori yang bisa dibuka lagi.
2. Setelah terkumpul semua file mp3nya dalam folder /home/user/Music, maka lakukan fuse untuk folder Music.
        Lakukan fuse terhadap folder /home/user/Music. Maka akan terbentuk mounted folder yang berisi file mp3.
