// wordcount-.cc
// Použijte: g++ -O2
// Příklad použití STL kontejneru unordered_map<>
// Program počítá četnost slov ve vstupním textu,
// slovo je cokoli oddělené "bílým znakem"

#include <string>
#include <iostream>
#include <unordered_map>

int main() {
    using namespace std;
    unordered_map<string,int> m;  // asociativní pole
                 // mapuje klíč/string na hodnotu/int
    string word;
    while (cin >> word) // čtení slova (jako scanf "%s", ale bezpečné)
        m[word]++;      // počítání výskytů slova (zvýší hodnotu pro
                        // zadaný klíč/slovo pokud záznam existuje,
                        // jinak vytvoří nový záznam s hodnotou 0 a
                        // tu operace ++ zvýší na 1)

    for (auto &mi: m)   // pro všechny prvky kontejneru m
        cout << mi.first << "\t" << mi.second << "\n";
        //      klíč/slovo          hodnota/počet
        // prvky kontejneru typu "map" jsou dvojice (klíč,hodnota)
}