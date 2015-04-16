# TUGAS KIJ E

##Kontributor

#### [Vijay Fathur](https://github.com/vertikaldash) 5112100043
#### [Faishal Azka J](https://github.com/azukineru) 5112100061
#### [R. M Iskandar Z](https://github.com/IssenShiro) 5112100101
#### [I Gede Arya P](https://github.com/aryashinji) 5112100151

## NOTE : Gunakan stable version server dan client yang menggunakan C++ QT

## Penjelasan program
Program chat sederhana berbasis server-client dengan server menggunakan bahasa C
sedangkan di sisi client menggunakan bahasa C++ (Stable) QT dan Java (Development).

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
State |'SIGNUP' |'INCHAT' / 'SIGNUP'
Flag |'AUTH_REQUEST' | 'SIGNUP_SUCCESS' / 'SIGNUP_FAILED'
Tujuan |0 |0
Sender |0 | 'Username pengirim:SessionKey' / 'NULL'
Type   |'AUTH'  | 'NULL' 
Content |'username:password' | 'NULL'


* Proses Sign In/Login dan Request List User :

Type |  Client 		  |  Server 	
-------|-------------------|-------------------------
State |'LOGIN' |'INCHAT' / 'LOGIN'
Flag |'AUTH_REQUEST' | 'LOGIN_SUCCESS' / 'LOGIN_FAILED'
Tujuan |0 |0
Sender |0 | 'Username pengirim:SessionKey' / 'NULL'
Type   |'AUTH'  | 'NULL' 
Content |'username:password' | 'NULL'

* Proses Send Message :

Type |  Client 		  |  Server 	
-------|-------------------|-------------------------
State |'INCHAT' |'INCHAT'
Flag |'SEND_MESSAGE' | 'SEND_MESSAGE'
Tujuan |'Username tujuan' |'Username tujuan'
Sender |'Username pengirim:SessionKey' |'Username pengirim:SessionKey'
Content |'Isi Pesan' |'Isi Pesan'

## Hal yang harus dikerjakan
Daftar hal yang harus dikerjakan saat ini, antara lain:

#### Aplikasi
- [x] Code Dasar Server dan Client
- [x] Definisi protokol dan metode yang digunakan
- [x] Integrasi antara client dan server
- [x] Uji coba
- [x] Dokumentasi dan diskusi
- [x] fixing bug issues part 1 (cara kerja sistem)

#### Sekuritas
- [x] user error handling
- [x] Implementasi Session Key untuk autentifikasi
- [x] Implementasi enkripsi - dekripsi antara Client - Server
- [x] Uji coba 1 (enkripsi seluruh pesan)
- [ ] Implementasi enkripsi isi pesan antara Client - Client
- [ ] Uji coba 2 (enkripsi isi pesan private)
- [ ] Implementasi Distribute key dengan diffie-helman
- [ ] Uji coba 3 (Key Exchange)
- [ ] Implementasi hash untuk password (optional)
- [ ] Implementasi hash dari pesan untuk autentikasi (optional)   
- [ ] Uji coba 4 (hash)
- [ ] Finalisasi (fixing bug issues part 2, etc)
