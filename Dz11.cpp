#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fisy = filesystem;
class Dovidnik {
    string nazva_firmi;
    string Vlasnik;
    long telephon;
    string adress;
    string rid_diyalnosti;
public:
    static void LoadFromFile(vector<Dovidnik>& dovid, const string& filename) {
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string nazva, vlas, address, diy;
                long tel;
                ss >> nazva >> vlas >> tel;
                ss.ignore();
                ss >> address >> diy;

                if (!nazva.empty() && !vlas.empty() && tel != 0) {
                    dovid.emplace_back(nazva, vlas, tel, address, diy);
                }
            }
            file.close();
        }
        else {
            cout << "No existing data found. Starting fresh!" << endl;
        }
    }
    void printRecord() const {
        cout << "Firm Name: " << nazva_firmi << " Owner: " << Vlasnik
            << " Phone: " << telephon << " Address: " << adress
            << " Activity: " << rid_diyalnosti << endl;
    }
    Dovidnik(string nazv, string vlas,int tel,string adres,string diy)
    :nazva_firmi(nazv), Vlasnik(vlas), telephon(tel), adress(adres),
     rid_diyalnosti(diy){}
    string getNazva() const { return nazva_firmi; }
    string getVlas() const { return Vlasnik; }
    int getTel() const { return telephon; }
    string getDil() const { return rid_diyalnosti; }
    static void Find_nazva(const string& nazva, const vector<Dovidnik>& dovid) {
        for (const auto& record : dovid) {
            if (record.getNazva() == nazva) {
                record.printRecord();
            }
        }
    }
    static void Find_Vlas(const string& vlas, const vector<Dovidnik>& dovid) {
        for (const auto& record : dovid) {
            if (record.getVlas() == vlas) {
                record.printRecord();
            }
        }
    }
    static void Find_Tel(const int& tel, const vector<Dovidnik>& dovid) {
        for (const auto& record : dovid) {
            if (record.getTel() == tel) {
                record.printRecord();
            }
        }
    }
    static void Find_Dil(const string& dil, const vector<Dovidnik>& dovid) {
        for (const auto& record : dovid) {
            if (record.getDil() == dil) {
                record.printRecord();
            }
        }
    }
    static void Input(vector<Dovidnik>& dovid) {
        string nazva, vlas, address, diy;
        long tel;

        cout << "Enter firm name: ";
        cin >> nazva;
        cout << "Enter owner name: ";
        cin >> vlas;
        cout << "Enter phone number: ";
        cin >> tel;
        cout << "Enter address: ";
        cin >> address;
        cout << "Enter activity: ";
        cin >> diy;
        dovid.emplace_back(nazva, vlas, tel, address, diy);
        fisy::path fpath = "Firmi";
        if (!fisy::exists(fpath)) {
            fisy::create_directory(fpath);
        }
        fisy::path filep = fpath / "firmi.txt";
        ofstream file(filep, ios::app); 
        if (file.is_open()) {
            file << nazva << " " << vlas << " " << tel << " " << address << " " << diy << endl;
            cout << "Record added and saved to file!" << endl;
            file.close();
        }
        else {
            cout << "Error opening file for saving." << endl;
        }
    }
    static void SaveToFile(const vector<Dovidnik>& dovid) {
        fisy::path fpath = "Firmi";
        if (!fisy::exists(fpath)) {
            fisy::create_directory(fpath);
        }

        fisy::path filep = fpath / "firmi.txt";
        ofstream file(filep, ios::trunc);  
        if (file.is_open()) {
            for (const auto& record : dovid) {
                file << record.nazva_firmi << " " << record.Vlasnik << " " << record.telephon << " "
                    << record.adress << " " << record.rid_diyalnosti << endl;
            }
            file.close();
        }
        else {
            cout << "Error opening file for saving." << endl;
        }
    }
};
int main()
{
    string filename = "Firmi/firmi.txt";
    int ans, searchTel;
    string searchStr;
    vector<Dovidnik> dovidnik;
    Dovidnik::LoadFromFile(dovidnik, filename);
    cout << "What do you want?\nDodati(1)\nPrint all(2)\nFind by nazva(3)\nFind by vlasnik(4)\nFind by telephone(5)\nFind by diyalnist(6)"<<endl;
    cin >> ans;
    switch (ans) {
    case 1:
        Dovidnik::Input(dovidnik);
        Dovidnik::SaveToFile(dovidnik);
        break;
    case 2:
        for (const auto& record : dovidnik) { record.printRecord(); }
        break;
    case 3:
        cout << "Enter firm name to search: ";
        cin >> searchStr;
        Dovidnik::Find_nazva(searchStr, dovidnik);
        break;
    case 4:
        cout << "Enter owner name to search: ";
        cin >> searchStr;
        Dovidnik::Find_Vlas(searchStr, dovidnik);
        break;
    case 5:
        cout << "Enter phone number to search: ";
        cin >> searchTel;
        Dovidnik::Find_Tel(searchTel, dovidnik);
        break;
    case 6:
        cout << "Enter activity to search: ";
        cin >> searchStr;
        Dovidnik::Find_Dil(searchStr, dovidnik);
        break;
    }
}
