# TUGAS KIJ E

##Kontributor

#### [Vijay Fathur](https://github.com/vertikaldash) 5112100043
#### [Faishal Azka J](https://github.com/azukineru) 5112100061
#### [R. M Iskandar Z](https://github.com/IssenShiro) 5112100101
#### [I Gede Arya P](https://github.com/aryashinji) 5112100151

## Penjelasan program
Program chat sederhana berbasis server-client dengan server menggunakan bahasa C
sedangkan di sisi client menggunakan bahasa Java.

Program chat ini memiliki prosedur sebagai berikut:
* Di sini client akan melakukan autentifikasi terlebih dahulu,
* Setelah terhubung ke server, server akan mengirimkan list user yang sedang online ke client,
* Client mengirimkan pesan ke user yang dituju,
* Server menerima dan mengirimkan pesan ke client yang dimaksud, kemudian
* Pesan di tampilkan.

Protokol yang diterapkan pada program chat ini dijelaskan pada tabel di bawah ini :

* Proses Sign Up :

Type |  Client 		  |  Server 				
-------|-------------------|-------------------------
State |'SignUp' |'Success/Fail SignUp'
Flag |(0) | (1) / (0)
Tujuan |null |null
Sender |null; Type (1)* |null
Content |username,password |null


* Proses Sign In/Login dan Request List User :

Type |  Client 		  |  Server 	
-------|-------------------|-------------------------
State |'LogIn' |'LogInAttempt'
  |'RequestUser' |'SendUser'
Flag |(0) | (1) / (0)
Tujuan |null |username
Sender |null; Type (2)* |null; Type (3)*
Content |username,pass |Array[users]

* Proses Send Message :

Type |  Client 		  |  Server 	
-------|-------------------|-------------------------
State |'SendMsg' |'RecMsg'
Flag |(0) |(1) / (0)
Tujuan |username tujuan	|username tujuan
Sender |username pengirim;Type(4)* |username pengirim
Content |username 1,username 2,msg |username 1,username 2,msg;Type(4)*

Keterangan :
- Type (1) : Sign Up
- Type (2) : Sign In
- Type (3) : SendArray
- Type (4) : SendMessage

## Hal yang harus dikerjakan
Daftar hal yang harus dikerjakan saat ini, antara lain:
- [x] Code Dasar Server dan Client
- [x] Definisi protokol dan metode yang digunakan
- [ ] Integrasi antara client dan server
- [ ] Uji coba
- [ ] Dokumentasi dan diskusi
