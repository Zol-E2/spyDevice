#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

class XorKripto {
private:
    string kulcs;

public:
    XorKripto(string megadott_kulcs) {
        kulcs = megadott_kulcs;
    }

    // Titkosító metódus
    string titkosit(const string& szoveg) {
        stringstream hex_eredmeny;
        int kulcs_index = 0;

        for (char c : szoveg) {
            char titkositott_karakter = c ^ kulcs[kulcs_index];
            // Hexadecimális formázás
            hex_eredmeny << hex << setfill('0') << setw(2) << (int)(unsigned char)titkositott_karakter;
            
            kulcs_index = (kulcs_index + 1) % kulcs.length();
        }
        return hex_eredmeny.str();
    }

    // Visszafejtő metódus
    string visszafejt(const string& titkos_hex) {
        string tiszta_szoveg = "";
        int kulcs_index = 0;
        
        for (size_t i = 0; i < titkos_hex.length(); i += 2) {
            string byte_string = titkos_hex.substr(i, 2);
            char titkositott_karakter = (char)strtol(byte_string.c_str(), nullptr, 16);
            
            char eredeti_karakter = titkositott_karakter ^ kulcs[kulcs_index];
            tiszta_szoveg += eredeti_karakter;

            kulcs_index = (kulcs_index + 1) % kulcs.length();
        }
        return tiszta_szoveg;
    }
};

int main() {
    cout << "=== OOP XOR KRIPTOGRAFIA ===\n\n";
    
    string jelszo;
    cout << "Add meg a kozos jelszot a muveletekhez: ";
    getline(cin, jelszo);

    if (jelszo.empty()) {
        cout << "[!] A jelszo nem lehet ures!\n";
        return 1;
    }
    
    XorKripto gep(jelszo);

    // TITKOSÍTÁS
    string eredeti_szoveg;
    cout << "\nAdd meg a titkositando szoveget: ";
    getline(cin, eredeti_szoveg);

    string titkositott = gep.titkosit(eredeti_szoveg);
    cout << "[+] A titkositott (Hex) szoveg: " << titkositott << "\n";

    // VISSZAFEJTÉS
    string visszafejtett = gep.visszafejt(titkositott);
    cout << "[+] A visszafejtett szoveg: " << visszafejtett << "\n";

    return 0;
}