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

//Global Variable
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
        conn = mysql_real_connect(conn, "localhost", "root", "", "pengolahan_data", 0, NULL, 0);
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
    int chooseOneFromMenu = 0;
    char keluarprogram;
    int num = 1;
    int fin = 0;
    // Variables End

    selamatdatang();
    for (int i = 0; i < 1; i++) {
        fin = num;
        cout << fin << ". Input data" << endl;
        fin += num;
        cout << fin << ". Cari data" << endl;
        fin += num;
        cout << fin << ". Perbaiki data" << endl;
        fin += num;
        cout << fin << ". Hapus data" << endl;
        fin += num;
        cout << fin << ". Exit" << endl;
        cout << "Choose One: ";
    }
    cin >> chooseOneFromMenu;

    switch(chooseOneFromMenu){
    case 1:
        inputdata();
        break;
    case 2:
        caridata();
        break;
    case 3:
        perbaikidata();
        break;
    case 4:
        hapusdata();
        break;
    case 5:
        exitprogram:
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
    cout<<"input NIK : ";
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
        cout << endl << "Successfully added in database." << endl;
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

    ExitMenu:
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
        printf("-----------------------------------------------------------------------\n");
        printf("| %-10s | %-20s | %-10s | %-10s | %-5s | \n", "Column Id", "Nama", "NIK", "TTL", "Kelurahan", "Agama");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-20s | %-10s | %-10s | %-5s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("-----------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "masukkan ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "tolong masukkan nomor yang benar." << endl;
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
            cout << "Enter tanggal lahir (" << defaultString << "  to not change) (yyyy-mm-dd): ";
            getline(cin, ttl);
            if (ttl == defaultString)
            {
                ttl = storettl;
            }
            cout << "Enter kelurahan (" << defaultString << "  to not change) (yyyy-mm-dd): ";
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
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
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
    char choose;
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
        printf("----------------------------------------------------------\n");
        printf("| %-10s | %-15s | %-10s | %-10s |\n", "Column Id", "Nama", "NIK", "Kelurahan");
        printf("----------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-10s | %-10s |\n", row[0], row[1], row[2], row[4]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("----------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "masukan ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
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
                cout << "Successfully Deleted." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Press 'm' to Menu, 'd' to delete another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'd' || choose == 'D')
    {
        hapusdata();
    }
    else
    {
        exit(0);
    }
}
