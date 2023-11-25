#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <conio.h>
#include <time.h>
#include <io.h>

// colors
#define green(text) printf("\033[0;32m%s", text)
#define red(text) printf("\033[1;31m", text)
#define yellow(text) printf("\033[1;33m%s", text)
#define cyan(text) printf("\033[0;36m%s", text)
#define purple(text) printf("\033[0;35m%s", text)
#define blue(text) printf("\033[0;34m%s", text)
#define reset() printf("\033[0m")

// deklarasi file
FILE *f_acc;
FILE *f_listing;
FILE *f_riwayat;
FILE *temp_acc;
FILE *temp_listing;
FILE *temp_riwayat;

// fungsi admin (listing = kendaraan)
void loginAdmin(int y), menuAdmin(), manajemenRequest(), manajemenUser(), requestUser(), manajemenListing();
void editPasswordUser(char key[40], char pass[40]), hapusUser(char key[40]), editListing(int id, char ans[20]), hapusListing(int id), tambahListing(), cariListing(char key[40], int id);
int fileExist(), idGenerator(char key[40]);

// fungsi acc
void loginUser(int y), registerUser(), menuUser(), listingSaya(), riwayatSaya();
void pilihJenis(char menu[20]), beliKendaraan(char jenis[20]), jualKendaraan(char jenis[20]), sewaKendaraan(char jenis[20]);
int cekUsername(char username[16]);

// fungsi sorting
void userList(), kendaraanList(char key[20], char jenis[20]);

// struct (tabel)
struct Acc
{
    char nama[50], username[16], pass[16], no[12], alamat[100];
} user, userSort[300], tempUser, cek, session;

struct Listing
{
    char nama[50], status[20], jenis[10], merk[20], username[16], request[20];
    int id;
    double harga, hargaSewa;
} listing, tempListing, listingSort[300];

struct Riwayat
{
    char namaKendaraan[50], status[20], jenis[10], merk[20], namaUser[50], username[16], pembeli[16], alamat[100], no[12], waktuPembelian[20];
    int id, lamaSewa;
    double harga, hargaSewa, bayar;
} riwayat, tempRiwayat, riwayatSort[300];

// variabel global
int i, j, k, n, pilih;
char konfirmasi[10], nama[50], username[16], pass[16], alamat[100], no[12];

int main()
{
    int attempt = 3, pilih = 0, n;
    fileExist();
    system("cls");
    printf("\n");
    printf("\t\t||= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =||\n");
    printf("\t\t||                                                                           ||\n");
    printf("\t\t||                   -------------------------------------                   ||\n");
    printf("\t\t||                   [   SELAMAT DATANG di D'Showroom    ]                   ||\n");
    printf("\t\t||                   -------------------------------------                   ||\n");
    printf("\t\t||                                                                           ||\n");
    printf("\t\t||= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =||\n\n");
    // system("pause");
    // system("cls");
    printf("\t\t||===========================================================================||\n");
    printf("\t\t||                              ----------------                             ||\n");
    printf("\t\t||                              | Pilih   Menu |                             ||\n");
    printf("\t\t||                              ----------------                             ||\n");
    printf("\t\t||===========================================================================||\n");
    printf("\t\t||                         ====>> 1. Admin   <<====                          ||\n");
    printf("\t\t||                         ====>> 2. User    <<====                          ||\n");
    printf("\t\t||                         ====>> 3. Keluar  <<====                          ||\n");
    printf("\t\t||===========================================================================||\n\n");
    printf("  Pilih : ");
    scanf("%d", &pilih);
    switch (pilih)
    {
    case 1:
    {
        printf("\n\t== Login Admin ==");
        system("cls");
        loginAdmin(attempt);
    }
    break;
    case 2:
    {
        system("cls");
        printf("\n\t    === Pilih [2] untuk Login ===");
        printf("\n== Belum Punya Akun?, Daftar dengan pilih [1] ==\n");
        printf("\n1. Register\n2. Log in\n\nPilih : ");
        scanf("%d", &n);
        getchar();
        switch (n)
        {
        case 1:
            system("cls");
            registerUser();
            break;
        case 2:
            system("cls");
            loginUser(attempt);
            break;
        default:
            printf("Harap masukan opsi yang benar...\n");
            system("pause");
            main();
            break;
        }
    }
    break;
    case 3:
    {
        system("cls");
        exit(0);
    }
    break;
    default:
        system("cls");
        printf("Harap masukan opsi yang benar...\n");
        system("pause");
        main();
        break;
    }
}

int fileExist()
{
    if (access("userAcc.dat", F_OK) == 0 && access("dataListing.dat", F_OK) == 0 && access("riwayatUser.dat", F_OK) == 0)
    {
        return 0;
    }
    else
    {
        f_acc = fopen("userAcc.dat", "ab+");
        f_listing = fopen("listingKendaraan.dat", "ab+");
        f_riwayat = fopen("riwayatUser.dat", "ab+");
        fclose(f_acc);
        fclose(f_listing);
        fclose(f_riwayat);
        return 1;
    }
}

void datetime()
{
    int hours, minutes, seconds, day, month, year, ret;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    hours = local->tm_hour;  // get hours since midnight (0-23)
    minutes = local->tm_min; // get minutes passed after the hour (0-59)
    seconds = local->tm_sec; // get seconds passed after a minute (0-59)

    day = local->tm_mday;         // get day of month (1 to 31)
    month = local->tm_mon + 1;    // get month of year (0 to 11)
    year = local->tm_year + 1900; // get year since 1900

    sprintf(riwayat.waktuPembelian, "%02d/%02d/%d %02d:%02d:%02d", day, month, year, hours, minutes, seconds);
}

// login
void loginAdmin(int y)
{
    if (y > 0)
    {

        fflush(stdin);
        printf("==========[   Login Admin DShowroom   ]==========\n");
        printf("   =======[Enter Username and Password]=======   \n");
        printf("\nUsername : ");
        scanf("%s", &username);
        printf("Password : ");
        scanf("%s", &pass);

        if (strcmp(username, "admin") == 0 && strcmp(pass, "admin123") == 0)
        {
            strcpy(session.username, "admin");
            strcpy(session.pass, "admin123");
            printf("\n>Login Berhasil<\n");
            // printf("\nEnter anything to continue...\n");
            system("pause");
            menuAdmin();
        }
        else
        {
            printf("\n\t>Login Gagal<\n");
            system("pause");
            system("cls");
            loginAdmin(--y);
        }
    }
    else
    {
        printf("\n\t\tAttempt login sudah habis, NT\n");
        // printf("\n\tEnter anything to continue...\n");
        system("pause");
        getchar();
        main();
    }
}

void loginUser(int y)
{
    if (y > 0)
    {

        fflush(stdin);
        system("cls");
        printf("==========[   Login User D'Showroom   ]==========\n");
        printf("   =======[Enter Username and Password]=======   \n");
        printf("\nUsername : ");
        scanf("%s", &username);
        printf("Password : ");
        scanf("%s", &pass);

        f_acc = fopen("userAcc.dat", "rb+");
        while ((fread(&session, sizeof(session), 1, f_acc)) != 0)
        {
            if ((strcmp(session.username, username)) == 0 && strcmp(session.pass, pass) == 0)
            {
                printf("\n>Login Berhasil<\n");
                system("pause");
                fclose(f_acc);
                menuUser();
            }
        }
        system("cls");
        printf("\n\t>Login Gagal<\n");
        system("pause");
        loginUser(--y);
    }
    else
    {
        system("cls");
        printf("\n\t\tAttempt Login sudah habis, NT\n");
        system("pause");
        getchar();
        main();
    }
}

// Register User
void registerUser()
{
    char a[5];
    int z;
    printf("\n\t==[Sign Up]==\n");

    fflush(stdin);
    printf("Fill in the required input\n");
    printf("\nNama Lengkap\t\t: ");
    gets(user.nama);
    printf("\nAlamat\t\t\t: ");
    gets(user.alamat);
    printf("\nNo\t\t\t: ");
    gets(user.no);
    printf("\nUsername\t\t: ");
    gets(user.username);
    printf("\nPassword\t\t: ");
    gets(user.pass);

    system("pause");
    if (cekUsername(user.username) != 1)
    {
        f_acc = fopen("userAcc.dat", "ab+");
        fwrite(&user, sizeof(user), 1, f_acc);
        system("cls");
        printf("\n   ==[Registrasi Akun Berhasil]==\n");
        printf(" Lanjut Login? [y/n] : ");
        fclose(f_acc);
        gets(a);
        if (strcasecmp(a, "y") == 0)
        {
            system("cls");
            loginUser(3);
        }
        else
        {
            system("cls");
            main();
        }
    }
    else
    {
        system("cls");
        printf("\n   ==[Registrasi Akun Gagal]==\n");
        printf("Username Sudah Ada!\n");
        printf("Sudah Punya Akun? [y/n] : ");
        gets(a);
        if (strcasecmp(a, "y") == 0)
        {
            system("cls");
            loginUser(3);
        }
        else
        {
            system("cls");
            registerUser();
        }
    }
}

int cekUsername(char username[16])
{
    int x;
    f_acc = fopen("userAcc.dat", "rb+");
    while ((fread(&cek, sizeof(cek), 1, f_acc)) != 0)
    {
        if ((strcmp(cek.username, username)) == 0)
        {
            x = 1; // username already exist
        }
        else
        {
            x = 0; // username hasnt exist
        }
    }
    fclose(f_acc);
    return x;
}

// Menu Admin
void menuAdmin()
{
    char answer[3];
    system("cls");
    printf("\t  ==[ Manajemen D'Showroom ]==\n\n");
    printf("1. Requests\n");
    printf("2. Mananajemen User\n");
    printf("3. Manajemen Listing \n");
    printf("4. Keluar \n");
    printf("\nPilih Menu (1-4): ");
    scanf("%d", &pilih);
    getchar();
    switch (pilih)
    {
    case 1:
        system("cls");
        manajemenRequest();
        break;
    case 2:
        system("cls");
        manajemenUser();
        break;
    case 3:
        system("cls");
        manajemenListing();
        break;
    case 4:
        system("cls");
        printf("\t===LOGOUT===");
        printf("\nYakin untuk melanjutkan?(y/n)  ");
        scanf("%s", &answer);
        if (strcmp(answer, "y") == 0)
        {
            system("cls");
            main();
        }
        else
        {
            system("cls");
            menuAdmin();
        }
        break;
    default:
        system("cls");
        menuAdmin();
        break;
    }
}

void manajemenRequest()
{
    int id;
    system("cls");
    printf("\t  ==[ Request Listing ]==\n\n");
    kendaraanList("pending", "pending");
    printf("\n\t  ==[  A k s i  ]==\n\n");
    printf("1. Terima Request\n");
    printf("2. Tolak Request\n");
    printf("3. Kembali\n");
    printf("\nPilih Menu (1-3): ");
    scanf("%d", &pilih);

    switch (pilih)
    {
    case 1:
        // system("cls");
        printf("\n\t  ==[ Terima Request ]==\n");
        printf("Masukan ID Listing: ");
        scanf("%d", &id);
        editListing(id, "Disetujui");
        break;
    case 2:
        // system("cls");
        printf("\n\t  ==[ Tolak Request ]==\n");
        printf("Masukan ID Listing: ");
        scanf("%d", &id);
        editListing(id, "Ditolak");
    case 3:
        system("cls");
        menuAdmin();
        break;
    default:
        system("cls");
        menuAdmin();
        break;
    }
}

void manajemenUser()
{
    char username[16], pass[16];
    system("cls");
    printf("\t  ==[ List User ]==\n\n");
    userList();
    printf("\n\n\t  ==[Manajemen User]==\n\n");
    printf("1. Edit Password User\n");
    printf("2. Hapus User\n");
    printf("3. Kembali\n");
    printf("\nPilih Menu (1-3): ");
    scanf("%d", &pilih);
    getchar();
    switch (pilih)
    {
    case 1:
        system("cls");
        printf("\t  ==[Edit  Password]==\n");
        printf("Masukan Username \t: ");
        scanf("%s", &username);
        printf("Masukan Password Baru\t: ");
        scanf("%s", &pass);
        editPasswordUser(username, pass);
        break;
    case 2:
        system("cls");
        printf("\t  ==[ Hapus User ]==\n");
        printf("Masukan Username: ");
        scanf("%s", &username);
        hapusUser(username);
        break;
    case 3:
        system("cls");
        menuAdmin();
        break;
    default:
        system("cls");
        menuAdmin();
        break;
    }
}

void editPasswordUser(char key[40], char pass[40])
{
    // char pass[16];
    int x = 0;
    printf("\n");
    f_acc = fopen("userAcc.dat", "rb");
    temp_acc = fopen("userAcc2.dat", "wb");

    while (fread(&tempUser, sizeof(tempUser), 1, f_acc) == 1)
    {
        if (strcmp(key, tempUser.username) != 0)
        {
            fwrite(&tempUser, sizeof(tempUser), 1, temp_acc);
        }
        else if (strcmp(key, tempUser.username) == 0)
        {
            strcpy(tempUser.pass, pass);
            fwrite(&tempUser, sizeof(tempUser), 1, temp_acc);
            x = 1;
        }
    }
    fclose(f_acc);
    fclose(temp_acc);

    remove("userAcc.dat");
    rename("userAcc2.dat", "userAcc.dat");
    if (x == 1)
    {
        green("Berhasil Mengubah Password User!!\n\n");
        reset();
    }
    else
    {
        red("Gagal Mengubah Password User!!\n\n");
        reset();
    }
    printf("\n<= See acc list\n");
    system("pause");
    manajemenUser();
}

void hapusUser(char key[40])
{
    int x = 0;
    printf("\n");
    f_acc = fopen("userAcc.dat", "rb");
    temp_acc = fopen("userAcc2.dat", "wb");

    while (fread(&user, sizeof(user), 1, f_acc) == 1)
    {
        if (strcmp(user.username, key) != 0)
        {
            fwrite(&user, sizeof(user), 1, temp_acc);
        }
        else if (strcmp(user.username, key) == 0)
        {
            x = 1;
        }
    }
    fclose(f_acc);
    fclose(temp_acc);
    remove("userAcc.dat");
    rename("userAcc2.dat", "userAcc.dat");

    if (x == 1)
    {
        green("User Berhasil Dihapus!!\n\n");
        reset();
    }
    else
    {
        red("User Gagal Dihapus!!\n\n");
        reset();
    }
    printf("\n<= lihat list user\n\n");
    system("pause");
    manajemenUser();
}

void manajemenListing()
{
    char key[40];
    int id;
    system("cls");
    printf("\t  ==[ Listing Kendaraan ]==\n\n");
    kendaraanList("all", "all");
    printf("\n\t  ==[Manajemen Listing]==\n\n");
    printf("1. Tambah Kendaraan\n");
    printf("2. Hapus Kendaraan\n");
    printf("3. Cari Kendaraan\n");
    printf("4. Kembali\n");
    printf("\nPilih Menu (1-4): ");
    scanf("%d", &pilih);
    getchar();
    switch (pilih)
    {
    case 1:
        system("cls");
        tambahListing();
        break;
    case 2:
        // system("cls");
        printf("\n\t  ==[ Hapus Kendaraan ]==\n");
        printf("Masukan ID Listing: ");
        scanf("%d", &id);
        hapusListing(id);
    case 3:
        system("cls");
        printf("\t  ==[Cari Listing Kendaraan]==\n\n");
        printf("Masukan Merk atau Nama Kendaraan: ");
        gets(key);
        cariListing(key, 0);
        break;
    case 4:
        system("cls");
        menuAdmin();
        break;
    default:
        system("cls");
        menuAdmin();
        break;
    }
}

int idGenerator(char key[40])
{
    int len, sum;
    len = strlen(key);
    for (i = 0; i < len; i++)
    {
        sum = sum + key[i];
    }

    // cek id
    f_listing = fopen("listingKendaraan.dat", "rb");
    while (fread(&tempListing, sizeof(tempListing), 1, f_listing))
    {
        if (tempListing.id == sum)
            ++sum;
    }
    fclose(f_listing);

    return sum;
}

void tambahListing()
{
    // nama, status, jenis, merk, username, request, ID, harga, hargaSewa;
    system("cls");
    printf("\t  ==[Tambah Kendaraan]==\n\n");
    // printf("Banyak kendaraan: ");
    // scanf("%d", &n);
    // printf("\n");
    // getchar();
    // for (i = 0; i < n; i++)
    // {
    printf("    Merk\t\t: ");
    gets(listing.merk);
    printf("    Jenis(Motor/Mobil)\t: ");
    gets(listing.jenis);
    printf("    Nama\t\t: ");
    scanf("%[^\n]s", &listing.nama);
    getchar();
    printf("    Jual/Sewa?\t\t: ");
    gets(listing.status);
    if (strcasecmp(listing.status, "jual") == 0)
    {
        printf("    Harga Jual\t\t: ");
        scanf("%lf", &listing.harga);
        listing.hargaSewa = 0.0;
    }
    else if (strcasecmp(listing.status, "sewa") == 0)
    {
        printf("    Harga Sewa(per jam)\t: ");
        scanf("%lf", &listing.hargaSewa);
        listing.harga = 0.0;
    }
    listing.id = idGenerator(listing.nama);
    strcpy(listing.request, "Disetujui");
    strcpy(listing.username, "admin");
    getchar();
    printf("\n");
    // }
    // write to file, avoiding openning 2 file simontenously
    f_listing = fopen("listingKendaraan.dat", "ab+");
    fwrite(&listing, sizeof(listing), 1, f_listing);
    fclose(f_listing);

    green("\nBerhasil Ditambahkan!\n\n");
    reset();
    printf("\n<= Lihat listing\n\n");
    system("pause");
    manajemenListing();
}

void editListing(int id, char ans[20])
{
    system("cls");
    int x = 0;
    printf("\n");
    f_listing = fopen("listingKendaraan.dat", "rb");
    temp_listing = fopen("listingKendaraan2.dat", "wb");

    while (fread(&tempListing, sizeof(tempListing), 1, f_listing))
    {
        if (listing.id != id)
        {
            fwrite(&tempListing, sizeof(tempListing), 1, temp_listing);
        }
        else if (listing.id == id)
        {
            strcpy(tempListing.request, ans);
            fwrite(&tempListing, sizeof(tempListing), 1, temp_listing);
            x = 1;
        }
    }

    fclose(f_listing);
    fclose(temp_listing);

    remove("listingKendaraan.dat");
    rename("listingKendaraan2.dat", "listingKendaraan.dat");
    if (x == 1)
    {
        green("Berhasil Mengubah Request!!\n\n");
        reset();
    }
    else
    {
        red("Gagal Mengubah Request!!\n\n");
        reset();
    }
    printf("\n<= Lihat list Request\n");
    system("pause");
    manajemenRequest();
}

void hapusListing(int id)
{
    int x = 0;
    printf("\n");
    f_listing = fopen("listingKendaraan.dat", "rb");
    temp_listing = fopen("listingKendaraan2.dat", "wb");

    while (fread(&listing, sizeof(listing), 1, f_listing) == 1)
    {
        if (listing.id != id)
        {
            fwrite(&listing, sizeof(listing), 1, temp_listing);
        }
        else if (listing.id == id)
        {
            x = 1;
        }
    }
    fclose(f_listing);
    fclose(temp_listing);

    remove("listingKendaraan.dat");
    rename("listingKendaraan2.dat", "listingKendaraan.dat");
    // printf("%d, %d",x,id);

    if (x == 1)
    {
        green("Listing Kendaraan Berhasil Dihapus!!\n");
        reset();
    }
    else
    {
        red("Listing Kendaraan Gagal Dihapus!!\n");
        reset();
    }

    printf("\n<= Lihat Listing Kendaraan\n");
    system("pause");
    manajemenListing();
}

void cariListing(char key[40], int id)
{
    int x = 0;
    system("cls");
    printf("\n");
    f_listing = fopen("listingKendaraan.dat", "rb");

    while ((fread(&listing, sizeof(listing), 1, f_listing)) != 0)
    {
        if ((strcmp(listing.nama, key)) == 0 || (strcmp(listing.merk, key)) == 0)
        {
            printf("%d.  ID\t\t: %d\n", x + 1, listing.id);
            printf("    Jenis\t: %s\n", listing.jenis);
            printf("    Merk\t: %s\n", listing.merk);
            printf("    Nama\t: %s\n", listing.nama);
            printf("    Pemilik\t: %s\n", listing.username);
            printf("    Status\t: ");
            if (strcasecmp(listing.status, "jual") == 0)
            {
                green(listing.status);
                reset();
                printf("\n    Harga\t: Rp.%.2f\n\n", listing.harga);
            }
            else if (strcasecmp(listing.status, "sewa") == 0)
            {
                cyan(listing.status);
                reset();
                printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listing.hargaSewa);
            }
            x++;
        }
        if (listing.id == id)
        {
            printf("%d.  ID\t\t: %d\n", x + 1, listing.id);
            printf("    Jenis\t: %s\n", listing.jenis);
            printf("    Merk\t: %s\n", listing.merk);
            printf("    Nama\t: %s\n", listing.nama);
            printf("    Pemilik\t: %s\n", listing.username);
            printf("    Status\t: ");
            if (strcasecmp(listing.status, "jual") == 0)
            {
                green(listing.status);
                reset();
                printf("\n    Harga\t: Rp.%.2f\n\n", listing.harga);
            }
            else if (strcasecmp(listing.status, "sewa") == 0)
            {
                cyan(listing.status);
                reset();
                printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listing.hargaSewa);
            }
            x++;
        }
        else if (listing.id == id && strcasecmp(key, "menuSewa") == 0)
        {
            printf("%d.  ID\t\t: %d\n", x + 1, listing.id);
            printf("    Jenis\t: %s\n", listing.jenis);
            printf("    Merk\t: %s\n", listing.merk);
            printf("    Nama\t: %s\n", listing.nama);
            printf("    Pemilik\t: %s\n", listing.username);
            printf("    Status\t: ");
            if (strcasecmp(listing.status, "jual") == 0)
            {
                green(listing.status);
                reset();
                printf("\n    Harga\t: Rp.%.2f\n\n", listing.harga);
            }
            else if (strcasecmp(listing.status, "sewa") == 0)
            {
                cyan(listing.status);
                reset();
                printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listing.hargaSewa);
            }
            break;
        }
        else if (listing.id == id && strcasecmp(key, "menuBeli") == 0)
        {
            printf("%d.  ID\t\t: %d\n", x + 1, listing.id);
            printf("    Jenis\t: %s\n", listing.jenis);
            printf("    Merk\t: %s\n", listing.merk);
            printf("    Nama\t: %s\n", listing.nama);
            printf("    Pemilik\t: %s\n", listing.username);
            printf("    Status\t: ");
            if (strcasecmp(listing.status, "jual") == 0)
            {
                green(listing.status);
                reset();
                printf("\n    Harga\t: Rp.%.2f\n\n", listing.harga);
            }
            else if (strcasecmp(listing.status, "sewa") == 0)
            {
                cyan(listing.status);
                reset();
                printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listing.hargaSewa);
            }
            break;
        }
    }
    if ((fread(&listing, sizeof(listing), 1, f_listing)) == 0 && x == 0)
    {
        printf("Listing Kendaraan Tidak Ditemukan.\n");
    }
    fclose(f_listing);

    if (strcmp(session.username, "admin") == 0 && strcmp(session.pass, "admin123") == 0)
    {
        printf("\n<= Lihat Listing Kendaraan\n");
        system("pause");
        manajemenListing();
    }
    // printf("\n<= Lihat Listing Kendaraan\n");
    // system("pause");
    // manajemenListing();
}

// menu User
void menuUser()
{
    char answer[3];
    system("cls");
    printf("\t==[Selamat Datang di D'Showroom ~ %s]==\n\n", session.username);
    printf("1. Beli Kendaraam\n");
    printf("2. Jual Kendaraan\n");
    printf("3. Sewa Kendaraan\n");
    printf("4. Listing Saya\n");
    printf("5. Riwayat \n");
    printf("6. logout \n");
    printf("\nPilih Menu (1-5): ");
    scanf("%d", &pilih);
    getchar();
    switch (pilih)
    {
    case 1:
        system("cls");
        pilihJenis("Beli");
        break;
    case 2:
        system("cls");
        pilihJenis("Jual");
        break;
    case 3:
        system("cls");
        pilihJenis("Sewa");
        break;
    case 4:
        system("cls");
        listingSaya();
        break;
    case 5:
        system("cls");
        riwayatSaya();
        break;
    case 6:
        system("cls");
        printf("\t===LOGOUT===");
        printf("\nYakin untuk melanjutkan (y/n)? ");
        scanf("%s", &answer);
        if (strcmp(answer, "y") == 0)
        {
            system("cls");
            main();
        }
        else
        {
            system("cls");
            menuUser();
        }
        break;
    default:
        // printf("Harap masukan opsi yang benar...\n");
        system("pause");
        menuUser();
        break;
    }
}

void pilihJenis(char menu[20])
{
    char answer[3];
    system("cls");
    printf("\t==[Pilih Jenis Kendaraan [%s]~ %s]==\n\n", menu, session.username);
    printf("1. Motor\n");
    printf("2. Mobil\n");
    printf("3. Ganti Menu\n");
    printf("\nPilih Menu (1-3): ");
    scanf("%d", &pilih);
    getchar();
    switch (pilih)
    {
    case 1:
        system("cls");
        if (strcasecmp(menu, "beli") == 0)
            beliKendaraan("motor");
        else if (strcasecmp(menu, "jual") == 0)
            jualKendaraan("motor");
        else if (strcasecmp(menu, "sewa") == 0)
            sewaKendaraan("motor");
        break;
    case 2:
        system("cls");
        if (strcasecmp(menu, "beli") == 0)
            beliKendaraan("mobil");
        else if (strcasecmp(menu, "jual") == 0)
            jualKendaraan("mobil");
        else if (strcasecmp(menu, "sewa") == 0)
            sewaKendaraan("mobil");
        break;
    case 3:
        system("cls");
        menuUser();
        break;
    default:
        // printf("Harap masukan opsi yang benar...\n");
        system("pause");
        menuUser();
        break;
    }
}

void beliKendaraan(char jenis[20])
{
    int id, x = 0, attempt = 3;
    double uang;
    // pilih kendaraan
    system("cls");
    printf("\t  ==[ Beli Kendaraan ]==\n\n");
    kendaraanList("jualUser", jenis);
    printf("\n\t  ==[ Pilih Kendaraan ]==\n\tatau ketik 1 untuk kembali ke Menu Utama\n");
    printf("ID kendaraan\t: ");
    scanf("%d", &id);
    if (id == 1)
    {
        menuUser();
    }

    // cari kendaraan
    cariListing("menuBeli", id);

    // pemabayaran
    printf("\n\nHarga Kendaraan Sebesar, Rp.%.2f\n", listing.harga);
    while (attempt > 0)
    {
        printf("Masukan Nominal: Rp.");
        scanf("%lf", &uang);
        getchar();
        if (listing.harga == uang)
        {
            system("cls");
            green("Pembayaran Berhasil!!\n");
            printf("Berhasil Membeli Kendaraan!!\n\n");
            reset();
            break;
        }
        else if (listing.harga < uang)
        {
            uang = uang - listing.harga;
            system("cls");
            printf("Kembalian: Rp.%.2f\n", uang);
            green("Pembayaran Berhasil!!\n\n");
            reset();
            break;
        }
        else
        {
            printf("Harap masukan nominal uang yang sesuai/ lebih dari nominal bayar...\n");
            uang = 0.0;
            --attempt;
        }
    }
    if (attempt == 0 && uang == 0.0)
    {
        system("cls");
        red("\n\t Transaksi Gagal!!\n\n");
        reset();
        system("pause");
        sewaKendaraan(jenis);
    }

    // proses sewa, update listing status
    f_listing = fopen("listingKendaraan.dat", "rb");
    temp_listing = fopen("listingKendaraan2.dat", "wb");

    while (fread(&tempListing, sizeof(tempListing), 1, f_listing))
    {
        if (listing.id != id)
        {
            fwrite(&tempListing, sizeof(tempListing), 1, temp_listing);
        }
        else if (listing.id == id)
        {
            strcpy(tempListing.status, "Terjual");
            fwrite(&tempListing, sizeof(tempListing), 1, temp_listing);
            x = 1;
        }
    }

    fclose(f_listing);
    fclose(temp_listing);
    remove("listingKendaraan.dat");
    rename("listingKendaraan2.dat", "listingKendaraan.dat");

    // write ke riwayat
    f_riwayat = fopen("riwayatUser.dat", "ab");
    riwayat.id = idGenerator(listing.nama);
    strcpy(riwayat.namaKendaraan, listing.nama);
    strcpy(riwayat.status, "Terjual");
    strcpy(riwayat.jenis, jenis);
    strcpy(riwayat.merk, listing.merk);
    strcpy(riwayat.namaUser, session.nama);
    strcpy(riwayat.username, listing.username);
    strcpy(riwayat.pembeli, session.username);
    strcpy(riwayat.alamat, session.alamat);
    strcpy(riwayat.no, session.no);
    datetime(); // waktu beli
    riwayat.harga = listing.harga;
    printf("\n");
    fwrite(&riwayat, sizeof(riwayat), 1, f_riwayat);
    fclose(f_riwayat);

    system("cls");
    if (x == 1)
    {
        green("Berhasil Membeli Kendaraan!!\n\n");
        reset();
    }
    else
    {
        red("Gagal Membeli Kendaraan!!\n\n");
        reset();
    }
    printf("\n<= Lihat Riwayat Saya\n\n");
    system("pause");
    riwayatSaya();
}

void jualKendaraan(char jenis[20])
{
    system("cls");
    printf("\t  ==[Jual Kendaraan]==\n\n");
    printf("Banyak kendaraan: ");
    scanf("%d", &n);
    printf("\n");
    getchar();
    f_listing = fopen("listingKendaraan.dat", "ab+");
    for (i = 0; i < n; i++)
    {
        printf("%d.  Merk\t\t: ", i + 1);
        gets(listing.merk);
        printf("    Nama\t\t: ");
        scanf("%[^\n]s", listing.nama);
        getchar();
        printf("    Jual/Sewa?\t\t: ");
        gets(listing.status);
        if (strcasecmp(listing.status, "jual") == 0)
        {
            printf("    Harga Jual\t\t: ");
            scanf("%lf", &listing.harga);
            listing.hargaSewa = 0.0;
        }
        else if (strcasecmp(listing.status, "sewa") == 0)
        {
            printf("    Harga Sewa(per jam)\t: ");
            scanf("%lf", &listing.hargaSewa);
            listing.harga = 0.0;
        }
        listing.id = idGenerator(listing.nama);
        strcpy(listing.request, "Pending");
        strcpy(listing.jenis, jenis);
        strcpy(listing.username, session.username);
        getchar();
        printf("\n");
        fwrite(&listing, sizeof(listing), 1, f_listing);
    }
    fclose(f_listing);
    green("\nBerhasil Ditambahkan!\n\n");
    reset();
    printf("\n<= Lihat listing\n\n");
    system("pause");
    listingSaya();
}

void sewaKendaraan(char jenis[20])
{
    int id, t, x = 0, attempt = 3;
    double uang, bayar;
    // pilih kendaraan
    system("cls");
    printf("\t  ==[ Sewa Kendaraan ]==\n\n");
    kendaraanList("sewaUser", jenis);
    printf("\n\t  ==[ Pilih Kendaraan ]==\n\tatau ketik 1 untuk kembali ke Menu Utama\n");
    printf("ID kendaraan\t: ");
    scanf("%d", &id);
    if (id == 1)
    {
        menuUser();
    }
    printf("Lama Sewa\t: ");
    scanf("%d", &t);

    // cari kendaraan
    cariListing("menuSewa", id);

    // pemabayaran
    bayar = listing.hargaSewa * t;
    printf("\n\nHarga Sewa Sebesar, Rp.%.2f\n", bayar);
    while (attempt > 0)
    {
        printf("Masukan Nominal: Rp.");
        scanf("%lf", &uang);
        getchar();
        if (listing.hargaSewa == uang)
        {
            system("cls");
            green("Pembayaran Berhasil!!\n");
            printf("Berhasil Menyewa!!\n\n");
            reset();
            break;
        }
        else if (listing.hargaSewa < uang)
        {
            uang = uang - listing.hargaSewa;
            system("cls");
            printf("Kembalian: Rp.%.2f\n", uang);
            green("Pembayaran Berhasil!!\n\n");
            reset();
            break;
        }
        else
        {
            printf("Harap masukan nominal uang yang sesuai/ lebih dari nominal bayar...\n");
            uang = 0.0;
            --attempt;
        }
    }
    if (attempt == 0 && uang == 0.0)
    {
        system("cls");
        red("\n\t Transalsi Gagal!!\n\n");
        reset();
        system("pause");
        sewaKendaraan(jenis);
    }

    // proses sewa, update listing status
    f_listing = fopen("listingKendaraan.dat", "rb");
    temp_listing = fopen("listingKendaraan2.dat", "wb");

    while (fread(&tempListing, sizeof(tempListing), 1, f_listing))
    {
        if (listing.id != id)
        {
            fwrite(&tempListing, sizeof(tempListing), 1, temp_listing);
        }
        else if (listing.id == id)
        {
            strcpy(tempListing.status, "Disewakan");
            fwrite(&tempListing, sizeof(tempListing), 1, temp_listing);
            x = 1;
        }
    }

    fclose(f_listing);
    fclose(temp_listing);
    remove("listingKendaraan.dat");
    rename("listingKendaraan2.dat", "listingKendaraan.dat");

    // write ke riwayat
    f_riwayat = fopen("riwayatUser.dat", "wb");
    riwayat.id = idGenerator(listing.nama);
    strcpy(riwayat.namaKendaraan, listing.nama);
    strcpy(riwayat.status, listing.status);
    strcpy(riwayat.jenis, jenis);
    strcpy(riwayat.merk, listing.merk);
    strcpy(riwayat.namaUser, session.nama);
    strcpy(riwayat.username, listing.username);
    strcpy(riwayat.pembeli, session.username);
    strcpy(riwayat.alamat, session.alamat);
    strcpy(riwayat.no, session.no);
    datetime(); // waktu
    riwayat.lamaSewa = t;
    riwayat.hargaSewa = listing.hargaSewa;
    riwayat.bayar = bayar;
    printf("\n");
    fwrite(&riwayat, sizeof(riwayat), 1, f_listing);
    fclose(f_riwayat);

    system("cls");
    if (x == 1)
    {
        green("Berhasil Menyewa Kendaraan!!\n\n");
        reset();
    }
    else
    {
        red("Gagal Menyewa Kendaraan!!\n\n");
        reset();
    }
    printf("\n<= Lihat Riwayat Saya\n\n");
    system("pause");
    riwayatSaya();
}

void listingSaya()
{
    system("cls");
    printf("\t  ==[ Listing Kendaraan Saya ]==\n\n");
    kendaraanList(session.username, "all");
    printf("\n<= Kembali ke menu utama\n\n");
    system("pause");
    menuUser();
}

void riwayatSaya()
{
    system("cls");
    printf("\t  ==[ Riwayat Saya ]==\n\n");
    riwayatList();
    printf("\n<= Kembali ke menu utama\n\n");
    system("pause");
    menuUser();
}

// fungsi sorting
void userList()
{
    int len = 0;
    f_acc = fopen("userAcc.dat", "rb");
    while (fread((&user), sizeof(user), 1, f_acc))
    {
        userSort[len] = user;
        len++;
    }
    fclose(f_acc);
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - i - 1; j++)
        {
            if (strcmp(userSort[j].username, userSort[j + 1].username) > 0)
            {
                tempUser = userSort[j];
                userSort[j] = userSort[j + 1];
                userSort[j + 1] = tempUser;
            }
        }
    }

    for (i = 0; i < len; i++)
    {
        printf("%d.  Username\t\t: %s\n", i + 1, userSort[i].username);
        printf("    Nama\t\t: %s\n", userSort[i].nama);
        printf("    Alamat\t\t: %s\n", userSort[i].alamat);
        printf("    No. Telp\t\t: %s\n", userSort[i].no);
    }
}

void kendaraanList(char key[20], char jenis[20])
{
    int len = 0;
    f_listing = fopen("listingKendaraan.dat", "rb");

    while (fread(&listing, sizeof(listing), 1, f_listing))
    {
        if (strcasecmp(listing.status, key) == 0 && strcasecmp(listing.jenis, jenis) == 0)
        {
            listingSort[len] = listing; // buat nampilin list yang spesifik
            len++;
        }
        else if (strcasecmp(listing.request, key) == 0)
        {
            listingSort[len] = listing; // buat admin nge-acc
            len++;
        }
        else if (strcasecmp(listing.username, key) == 0)
        {
            listingSort[len] = listing; // buat fitur listing saya
            len++;
        }
        else if (strcasecmp(key, "jualUser") == 0 && strcasecmp(listing.status, "jual") == 0 && strcasecmp(listing.jenis, jenis) == 0 && strcasecmp(listing.username, session.username) != 0)
        {
            listingSort[len] = listing; // buat fitur beli kendaraan user
            len++;
        }
        else if (strcasecmp(key, "sewaUser") == 0 && strcasecmp(listing.status, "jual") == 0 && strcasecmp(listing.jenis, jenis) == 0 && strcasecmp(listing.username, session.username) != 0)
        {
            listingSort[len] = listing; // buat fitur sewa kendaraan user
            len++;
        }
        else if (strcasecmp(key, "all") == 0 && strcasecmp(listing.request, "pending") != 0 && strcasecmp(listing.status, "terjual") != 0 && strcasecmp(listing.status, "disewakan") != 0)
        {
            listingSort[len] = listing; // buat nampilin semua list
            len++;
        }
    }
    fclose(f_listing);

    // bbsordt
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - i - 1; j++)
        {
            if (listingSort[j].harga > listingSort[j + 1].harga)
            {
                tempListing = listingSort[j];
                listingSort[j] = listingSort[j + 1];
                listingSort[j + 1] = tempListing;
            }
        }
    }
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - i - 1; j++)
        {
            if (listingSort[j].hargaSewa > listingSort[j + 1].hargaSewa)
            {
                tempListing = listingSort[j];
                listingSort[j] = listingSort[j + 1];
                listingSort[j + 1] = tempListing;
            }
        }
    }

    // print sorted data
    for (i = 0; i < len; i++)
    {
        printf("%d.  ID\t\t: %d\n", i + 1, listingSort[i].id);
        printf("    Jenis\t: %s\n", listingSort[i].jenis);
        printf("    Merk\t: %s\n", listingSort[i].merk);
        printf("    Nama\t: %s\n", listingSort[i].nama);
        printf("    Pemilik\t: %s\n", listingSort[i].username);
        printf("    Status\t: ");
        if (strcasecmp(listingSort[i].status, "jual") == 0)
        {
            green(listingSort[i].status);
            reset();
            printf("\n    Harga\t: Rp.%.2f\n\n", listingSort[i].harga);
        }
        else if (strcasecmp(listingSort[i].status, "sewa") == 0)
        {
            cyan(listingSort[i].status);
            reset();
            printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listingSort[i].hargaSewa);
        }
        else if (strcasecmp(listingSort[i].status, "terjual") == 0)
        {
            yellow(listingSort[i].status);
            reset();
            printf("\n    Harga\t: Rp.%.2f\n\n", listingSort[i].harga);
        }
        else if (strcasecmp(listingSort[i].status, "disewakan") == 0)
        {
            yellow(listingSort[i].status);
            reset();
            printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listingSort[i].hargaSewa);
        }
    }
}

void riwayatList()
{
    int len = 0;
    f_riwayat = fopen("riwayatUser.dat", "rb");
    while (fread((&riwayat), sizeof(riwayat), 1, f_riwayat) != 0)
    {
        if (strcasecmp(riwayat.pembeli, session.username) == 0)
        {
            riwayatSort[len] = riwayat;
            len++;
        }
    }
    fclose(f_riwayat);
    printf("%s\n", riwayatSort[0].waktuPembelian);
    // for (i = 0; i < len - 1; i++)
    // {
    //     for (j = 0; j < len - i - 1; j++)
    //     {
    //         if (strcmp(riwayatSort[j].waktuPembelian, riwayatSort[j + 1].waktuPembelian) > 0)
    //         {
    //             tempRiwayat = riwayatSort[j];
    //             riwayatSort[j] = riwayatSort[j + 1];
    //             riwayatSort[j + 1] = tempRiwayat;
    //         }
    //     }
    // }
    system("pause");
    for (i = 0; i < len; i++)
    {
        printf("%d.  ID\t\t: %s\n", i + 1, riwayatSort[i].id);
        printf("    Nama\t\t: %s\n", riwayatSort[i].namaKendaraan);
        printf("    Jenis\t\t: %s\n", riwayatSort[i].jenis);
        printf("    Pemilik\t\t: %s\n", riwayatSort[i].username);
        printf("    Pembeli/Penyewa\t: %s\n", riwayatSort[i].pembeli);
        printf("    Alamat\t\t: %s\n", riwayatSort[i].alamat);
        printf("    No. Telp\t\t: %s\n", riwayatSort[i].no);
        printf("    Waktu Transaksi\t\t: %s\n", riwayatSort[i].waktuPembelian);
        printf("    Biaya Sewa\t\t: %.2f\n", riwayatSort[i].hargaSewa);
        if (strcasecmp(riwayatSort[i].status, "jual") == 0 || strcasecmp(riwayatSort[i].status, "Terjual") == 0)
        {
            green(riwayatSort[i].status);
            reset();
            printf("\n    Harga\t: Rp.%.2f\n\n", riwayatSort[i].harga);
        }
        else if (strcasecmp(riwayatSort[i].status, "sewa") == 0 || strcasecmp(riwayatSort[i].status, "disewakan") == 0)
        {
            cyan(riwayatSort[i].status);
            reset();
            printf("\n    Harga Sewa\t: Rp.%.2f\n\n", riwayatSort[i].hargaSewa);
            printf("\n    Nominal Bayar\t: Rp.%.2f\n\n", riwayatSort[i].bayar);
            printf("\n    Lama Sewa\t: %d\n\n", riwayatSort[i].lamaSewa);
        }
    }
    system("pause");
}
