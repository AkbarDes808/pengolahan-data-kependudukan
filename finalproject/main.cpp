#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>


using namespace std;

//Global Variable untuk deklarasi untuk MYSQL
int qstate ;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else{
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        }
        //bagian ini untuk mengkoneksikan database dengan codeblock, localhost sebagai alamat, root dan "" sebagai username dan password pengguna, pengolahan_data sebagai database
        conn = mysql_real_connect(conn, "localhost", "root", "", "pengolahan_nama", 0, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else{
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
            }
    }
};

//welcome functions
void selamatdatang(){
    cout<<"SELAMAT DATANG DI APLIKASI PENGOLAHAN DATA"<<endl<<endl;
    cout<<"MENU"<<endl;
}

//functions
void inputdata();
void tampildata();
void caridata();
void perbaikidata();
void hapusdata();

int main()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Call Methods
    db_response::ConnectionFunction();
    // Call Methods End

    // Variables
    int pilih = 0;
    char keluarprogram;
    int num = 1;
    int fin = 0;
    // Variables End

    selamatdatang();
    for (int i = 0; i < 1; i++) {
        fin = num;
        cout << fin << ". Input data" << endl;
        fin += num;
        cout << fin << ". Tampil data" << endl;
        fin += num;
        cout << fin << ". Cari data" << endl;
        fin += num;
        cout << fin << ". Perbaiki data" << endl;
        fin += num;
        cout << fin << ". Hapus data" << endl;
        fin += num;
        cout << fin << ". Keluar" << endl;
        cout << "pilih : ";
    }
    cin >> pilih;

    switch(pilih){
    case 1:
        inputdata();
        break;
    case 2:
        tampildata();
        break;
    case 3:
        caridata();
        break;
    case 4:
        perbaikidata();
        break;
    case 5:
        hapusdata();
        break;
    case 6:
        cout<<"apakah anda ingin keluar (y/n) : ";
        cin>>keluarprogram;
        if(keluarprogram == 'y' || keluarprogram == 'Y'){
            return 0;
        }else if(keluarprogram == 'n' || keluarprogram == 'N'){
            system("cls");
            main();
        }else{
            cout<<"pilih antara 'y' dan 'n'"<<endl;
        }
        break;
    default:
        cout << "pilih antara 1-7, tekan enter untuk melanjutkan....";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}

void inputdata()
{
    system("cls");
    //variables declared
    string nama = "";
    string nik = "";
    string ttl = "";
    string kelurahan = "";
    string agama = "";
    string jenis_kelamin = "";
    char pilih;
    //variable end

    selamatdatang();
    cin.ignore(1, '\n');
    cout<<"input nama : ";
    getline(cin, nama);
    cout<<"input NIK  : ";
    getline(cin, nik);
    cout<<"tanggal lahir (dd-mm-yyyy) : ";
    getline(cin, ttl);
    cout<<"input kelurahan : ";
    getline(cin, kelurahan);
    cout<<"input agama : ";
    getline(cin, agama);
    cout<<"input jenis kelamin : ";
    getline(cin, jenis_kelamin);

    string insert_query = "insert into data_penduduk (nama, NIK, ttl, kelurahan, agama, jenis_kelamin) values ('"+nama+"','"+nik+"',STR_TO_DATE('"+ttl+"', '%d-%m-%Y'),'"+kelurahan+"','"+agama+"','"+jenis_kelamin+"')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Berhasil dimasukkan dalam database..." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) <<endl<< endl;
    }
    // Exit Code
    cout << "tekan 'm' untuk Menu dan 'a' untuk menginput data kembali atau tekan sembarang tombol untuk exit: ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else if (pilih == 'a' || pilih == 'A')
    {
        inputdata();
    }
    else
    {
        exit(0);
    }
}

void tampildata()
{
    system("cls");

    char pilih;

    selamatdatang();
    qstate = mysql_query(conn, "select * from data_penduduk");
    if(!qstate)
    {
       res = mysql_store_result(conn);
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-15s | %-25s | %-20s | %-15s | %-15s | %-15s |\n", "id", "nama", "NIK", "tanggal lahir", "kelurahan", "agama", "jenis kelamin");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-5s | %-15s | %-25s | %-20s | %-15s | %-15s | %-15s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        }
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    }else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << endl;
    cout << "Press 'm' to Menu any other key to Exit: ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

void caridata()
{
     // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    string input = "";
    char pilih;
    // Variables End

    selamatdatang();
    cin.ignore(1, '\n');
    cout << "Masukan NIK: ";
    getline(cin, input);
    string findbynik_query = "select * from data_penduduk where NIK like '%"+input+"%'";
    const char* qn = findbynik_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "ID: " << row[0] << "\nNama: " << row[1] << "\nNIK: " << row[2] << "\nTanggal Lahir: " << row[3] << "\nKelurahan: " << row[4] << "\nAgama: " << row[5] << "\nJenis Kelamin: " << row[6] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "tekan 'm' untuk Menu dan 'a' untuk menginput data kembali atau tekan sembarang tombol untuk exit: ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else if (pilih == 'a' || pilih == 'A')
    {
        caridata();
    }
    else
    {
        exit(0);
    }
}

void perbaikidata()
{
    system("cls");

    // Variables
    string nama = "";
    string nik = "";
    string ttl = "";
    string kelurahan = "";
    string jenis_kelamin = "";
    string agama = "";
    string items[5000];
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storenama = "";
    string storenik = "";
    string storettl = "";
    string storekelurahan = "";
    string storeagama = "";
    string storejeniskelamin = "";
    // Variables End

    selamatdatang();
    qstate = mysql_query(conn, "select * from data_penduduk");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s|\n", "kolom id", "nama", "NIK", "ttl", "kelurahan", "agama", "jenis kelamin");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s|\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        }
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "jika anda ingin kembali ke menu, tekan sembarang angka selain id di tabel " << endl;
        cout << "masukkan ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        HaveException = true;
        cout << "tolong masukkan nomor yang benar." << endl;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from data_penduduk where id = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    cout << "kolom ID: " << row[0]
                         << "\nNama: " << row[1]
                         << "\nNIK: " << row[2]
                         << "\nTTL: " << row[3]
                         << "\nKelurahan: " << row[4]
                         << "\nAgama: " << row[5]
                         << "\nJenis Kelamin: " << row[6]
                         << endl << endl;

                    storeid = row[0];
                    storenama = row[1];
                    storenik = row[2];
                    storettl = row[3];
                    storekelurahan = row[4];
                    storeagama = row[5];
                    storejeniskelamin = row[6];

                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            string defaultString = "xN";
            cout << "Enter Name (" << defaultString << "  to not change): ";
            getline(cin, nama);
            if (nama == defaultString)
            {
                nama = storenama;
            }
            cout << "Enter NIK (" << defaultString << "  to not change): ";
            getline(cin, nik);
            if (nik == defaultString)
            {
                nik = storenik;
            }
            cout << "Enter tanggal lahir (" << defaultString << "  to not change): ";
            getline(cin, ttl);
            if (ttl == defaultString)
            {
                ttl = storettl;
            }
            cout << "Enter kelurahan (" << defaultString << "  to not change): ";
            getline(cin, kelurahan);
            if (kelurahan == defaultString)
            {
                kelurahan = storekelurahan;
            }
            cout << "Enter agama (" << defaultString << "  to not change): ";
            getline(cin, agama);
            if (agama == defaultString)
            {
                agama = storeagama;
            }
            cout << "Enter jenis kelamin (" << defaultString << "  to not change): ";
            getline(cin, jenis_kelamin);
            if (jenis_kelamin == defaultString)
            {
                 jenis_kelamin = storejeniskelamin;
            }

            string update_query = "update data_penduduk set nama = '"+nama+"', nik = '"+nik+"', ttl = '"+ttl+"', kelurahan = '"+kelurahan+"', agama = '"+agama+"', jenis_kelamin = '"+jenis_kelamin+"' where id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Berhasil Memperbarui..." << endl;
            }
            else
            {
                cout << "Gagal memperbarui data! error " << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Data tidak ditemukan di database." << endl;
        }
    }

    ExitMenu:
    cout << "tekan 'm' untuk kembali ke Menu, 'e' untuk mengedit data lagi dan tekan sembarang untuk keluar : ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        perbaikidata();
    }
    else
    {
        exit(0);
    }
}

void hapusdata()
{
    system("cls");

    // Variables
    char kembali;
    char pilih;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    selamatdatang();
    qstate = mysql_query(conn, "select * from data_penduduk");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("--------------------------------------------------------------------\n");
        printf("| %-10s | %-15s | %-20s | %-10s |\n", "Column Id", "Nama", "NIK", "Kelurahan");
        printf("--------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-20s | %-10s |\n", row[0], row[1], row[2], row[4]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("--------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "jika anda ingin kembali ke menu, tekan sembarang angka selain id di tabel " << endl;
        cout << "masukan ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Masukan ID yang benar!." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from data_penduduk where id = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Berhasil Dihapus." << endl;
            }
            else
            {
                cout << "Gagal menghapus! error " << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Data tidak ditemukan di database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Tekan 'm' untuk kembali ke Menu, 'd' untuk menghapus data lagi dan tekan sembarang untuk keluar : ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else if (pilih == 'd' || pilih == 'D')
    {
        hapusdata();
    }
    else
    {
        exit(0);
    }
}

#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>


using namespace std;

//Global Variable untuk deklarasi untuk MYSQL
int qstate ;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else{
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        }
        //bagian ini untuk mengkoneksikan database dengan codeblock, localhost sebagai alamat, root dan "" sebagai username dan password pengguna, pengolahan_data sebagai database
        conn = mysql_real_connect(conn, "localhost", "root", "", "pengolahan_nama", 0, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else{
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
            }
    }
};

//welcome functions
void selamatdatang(){
    cout<<"SELAMAT DATANG DI APLIKASI PENGOLAHAN DATA"<<endl<<endl;
    cout<<"MENU"<<endl;
}

//functions
void inputdata();
void tampildata();
void caridata();
void perbaikidata();
void hapusdata();

int main()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Call Methods
    db_response::ConnectionFunction();
    // Call Methods End

    // Variables
    int pilih = 0;
    char keluarprogram;
    int num = 1;
    int fin = 0;
    // Variables End

    selamatdatang();
    for (int i = 0; i < 1; i++) {
        fin = num;
        cout << fin << ". Input data" << endl;
        fin += num;
        cout << fin << ". Tampil data" << endl;
        fin += num;
        cout << fin << ". Cari data" << endl;
        fin += num;
        cout << fin << ". Perbaiki data" << endl;
        fin += num;
        cout << fin << ". Hapus data" << endl;
        fin += num;
        cout << fin << ". Keluar" << endl;
        cout << "pilih : ";
    }
    cin >> pilih;

    switch(pilih){
    case 1:
        inputdata();
        break;
    case 2:
        tampildata();
        break;
    case 3:
        caridata();
        break;
    case 4:
        perbaikidata();
        break;
    case 5:
        hapusdata();
        break;
    case 6:
        cout<<"apakah anda ingin keluar (y/n) : ";
        cin>>keluarprogram;
        if(keluarprogram == 'y' || keluarprogram == 'Y'){
            return 0;
        }else if(keluarprogram == 'n' || keluarprogram == 'N'){
            system("cls");
            main();
        }else{
            cout<<"pilih antara 'y' dan 'n'"<<endl;
        }
        break;
    default:
        cout << "pilih antara 1-7, tekan enter untuk melanjutkan....";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}

void inputdata()
{
    system("cls");
    //variables declared
    string nama = "";
    string nik = "";
    string ttl = "";
    string kelurahan = "";
    string agama = "";
    string jenis_kelamin = "";
    char pilih;
    //variable end

    selamatdatang();
    cin.ignore(1, '\n');
    cout<<"input nama : ";
    getline(cin, nama);
    cout<<"input NIK  : ";
    getline(cin, nik);
    cout<<"tanggal lahir (dd-mm-yyyy) : ";
    getline(cin, ttl);
    cout<<"input kelurahan : ";
    getline(cin, kelurahan);
    cout<<"input agama : ";
    getline(cin, agama);
    cout<<"input jenis kelamin : ";
    getline(cin, jenis_kelamin);

    string insert_query = "insert into data_penduduk (nama, NIK, ttl, kelurahan, agama, jenis_kelamin) values ('"+nama+"','"+nik+"',STR_TO_DATE('"+ttl+"', '%d-%m-%Y'),'"+kelurahan+"','"+agama+"','"+jenis_kelamin+"')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Berhasil dimasukkan dalam database..." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) <<endl<< endl;
    }
    // Exit Code
    cout << "tekan 'm' untuk Menu dan 'a' untuk menginput data kembali atau tekan sembarang tombol untuk exit: ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else if (pilih == 'a' || pilih == 'A')
    {
        inputdata();
    }
    else
    {
        exit(0);
    }
}

void tampildata()
{
    system("cls");

    char pilih;

    selamatdatang();
    qstate = mysql_query(conn, "select * from data_penduduk");
    if(!qstate)
    {
       res = mysql_store_result(conn);
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-15s | %-25s | %-20s | %-15s | %-15s | %-15s |\n", "id", "nama", "NIK", "tanggal lahir", "kelurahan", "agama", "jenis kelamin");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-5s | %-15s | %-25s | %-20s | %-15s | %-15s | %-15s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        }
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    }else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << endl;
    cout << "Press 'm' to Menu any other key to Exit: ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

void caridata()
{
     // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    string input = "";
    char pilih;
    // Variables End

    selamatdatang();
    cin.ignore(1, '\n');
    cout << "Masukan NIK: ";
    getline(cin, input);
    string findbynik_query = "select * from data_penduduk where NIK like '%"+input+"%'";
    const char* qn = findbynik_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "ID: " << row[0] << "\nNama: " << row[1] << "\nNIK: " << row[2] << "\nTanggal Lahir: " << row[3] << "\nKelurahan: " << row[4] << "\nAgama: " << row[5] << "\nJenis Kelamin: " << row[6] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "tekan 'm' untuk Menu dan 'a' untuk menginput data kembali atau tekan sembarang tombol untuk exit: ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else if (pilih == 'a' || pilih == 'A')
    {
        caridata();
    }
    else
    {
        exit(0);
    }
}

void perbaikidata()
{
    system("cls");

    // Variables
    string nama = "";
    string nik = "";
    string ttl = "";
    string kelurahan = "";
    string jenis_kelamin = "";
    string agama = "";
    string items[5000];
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storenama = "";
    string storenik = "";
    string storettl = "";
    string storekelurahan = "";
    string storeagama = "";
    string storejeniskelamin = "";
    // Variables End

    selamatdatang();
    qstate = mysql_query(conn, "select * from data_penduduk");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s|\n", "kolom id", "nama", "NIK", "ttl", "kelurahan", "agama", "jenis kelamin");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s|\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        }
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "jika anda ingin kembali ke menu, tekan sembarang angka selain id di tabel " << endl;
        cout << "masukkan ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        HaveException = true;
        cout << "tolong masukkan nomor yang benar." << endl;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from data_penduduk where id = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    cout << "kolom ID: " << row[0]
                         << "\nNama: " << row[1]
                         << "\nNIK: " << row[2]
                         << "\nTTL: " << row[3]
                         << "\nKelurahan: " << row[4]
                         << "\nAgama: " << row[5]
                         << "\nJenis Kelamin: " << row[6]
                         << endl << endl;

                    storeid = row[0];
                    storenama = row[1];
                    storenik = row[2];
                    storettl = row[3];
                    storekelurahan = row[4];
                    storeagama = row[5];
                    storejeniskelamin = row[6];

                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            string defaultString = "xN";
            cout << "Enter Name (" << defaultString << "  to not change): ";
            getline(cin, nama);
            if (nama == defaultString)
            {
                nama = storenama;
            }
            cout << "Enter NIK (" << defaultString << "  to not change): ";
            getline(cin, nik);
            if (nik == defaultString)
            {
                nik = storenik;
            }
            cout << "Enter tanggal lahir (" << defaultString << "  to not change): ";
            getline(cin, ttl);
            if (ttl == defaultString)
            {
                ttl = storettl;
            }
            cout << "Enter kelurahan (" << defaultString << "  to not change): ";
            getline(cin, kelurahan);
            if (kelurahan == defaultString)
            {
                kelurahan = storekelurahan;
            }
            cout << "Enter agama (" << defaultString << "  to not change): ";
            getline(cin, agama);
            if (agama == defaultString)
            {
                agama = storeagama;
            }
            cout << "Enter jenis kelamin (" << defaultString << "  to not change): ";
            getline(cin, jenis_kelamin);
            if (jenis_kelamin == defaultString)
            {
                 jenis_kelamin = storejeniskelamin;
            }

            string update_query = "update data_penduduk set nama = '"+nama+"', nik = '"+nik+"', ttl = '"+ttl+"', kelurahan = '"+kelurahan+"', agama = '"+agama+"', jenis_kelamin = '"+jenis_kelamin+"' where id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Berhasil Memperbarui..." << endl;
            }
            else
            {
                cout << "Gagal memperbarui data! error " << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Data tidak ditemukan di database." << endl;
        }
    }

    ExitMenu:
    cout << "tekan 'm' untuk kembali ke Menu, 'e' untuk mengedit data lagi dan tekan sembarang untuk keluar : ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        perbaikidata();
    }
    else
    {
        exit(0);
    }
}

void hapusdata()
{
    system("cls");

    // Variables
    char kembali;
    char pilih;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    selamatdatang();
    qstate = mysql_query(conn, "select * from data_penduduk");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("--------------------------------------------------------------------\n");
        printf("| %-10s | %-15s | %-20s | %-10s |\n", "Column Id", "Nama", "NIK", "Kelurahan");
        printf("--------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-20s | %-10s |\n", row[0], row[1], row[2], row[4]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("--------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "jika anda ingin kembali ke menu, tekan sembarang angka selain id di tabel " << endl;
        cout << "masukan ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Masukan ID yang benar!." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from data_penduduk where id = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Berhasil Dihapus." << endl;
            }
            else
            {
                cout << "Gagal menghapus! error " << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Data tidak ditemukan di database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Tekan 'm' untuk kembali ke Menu, 'd' untuk menghapus data lagi dan tekan sembarang untuk keluar : ";
    cin >> pilih;
    if (pilih == 'm' || pilih == 'M')
    {
        main();
    }
    else if (pilih == 'd' || pilih == 'D')
    {
        hapusdata();
    }
    else
    {
        exit(0);
    }
}

