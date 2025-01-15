#include <iostream>
#include <string>
#include <random>
#include <vector>

using namespace std;

class Fish {
    public:
        string name;
        int catchChance;
        int price;
        Fish(string fishName, int chance, int pricing){
            name = fishName;
            catchChance = chance;
            price = pricing;
        }
        Fish() = default;
};

class Rod {
    public:
        string name;
        float catchBonus;
        int price;
        Rod(string rodName, float bonus, int pricing){
            name = rodName;
            catchBonus = bonus;
            price = pricing;
        }
        Rod() = default;

};

class Water {
    public:
        string name;
        vector<Fish> fishes;
        int licenceCost;
        Water(vector<Fish> fishies, string waterName, int licence) {
            name = waterName;
            fishes = fishies;
            licenceCost = licence;
        }
        string printName(){
            return name;
        }
        Water() = default;
};

class FishingSys {
    public:
        Rod currentRod;
        Water currentWater;
        random_device rd;
        vector<Water> places;
        vector<Rod> rods;

        vector<Fish> caughtfish;
        int currency = 0;
        FishingSys(Rod& starter, Water& first){
            currentRod = starter;
            currentWater = first;
            rods.push_back(starter);
        }
        void clearScreen(){
            cout << string(100, '\n');
        }
        void setCurrentRod(Rod& newrod){
            currentRod = newrod;
        }
        void setCurrentWater(Water& newater) {
            currentWater = newater;
        }
        void printCurrency()
        {
            cout << "Masz obecnie " << currency << " Żetonów" << endl;
        }
        void pushRod(Rod& addrod){
            rods.push_back(addrod);
        }
        void switchrod(){
            clearScreen();
            cout << "Wybierz wędkę: " << endl;
            for (int i = 0; i < rods.size(); i++)
            {
                cout << i + 1 << ". " << rods[i].name << " | Bonus do wyłowienia: " << rods[i].catchBonus << " x" << endl;
            }
            int choice;
            cin >> choice;
            if (choice > rods.size() || choice < 1)
            {
                cout << "Nie ma takiej wędki" << endl;
                switchrod();
            }
            else
            {
                setCurrentRod(rods[choice - 1]);
                cout << "Zmieniono wędkę na: " << currentRod.name << endl;
                overworldSelector();
            }
        }
        void overworldSelector(){
            clearScreen();
            cout << "Obecnie jesteś w pobliżu: " << currentWater.printName() << endl;
            cout << "Co chciałbyś / chciałabyś zrobić? \n1.Łów ryby \n2.Przejdź gdzie indziej \n3.Zmień ekwipunek \n4.Kup nowy ekwipunek \n5.Sprzedaj ryby \n";
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                fishing();
                break;
            case 2:
                //travel();
                break;
            case 3:
                switchrod();
                break;
            case 4:
                //buyEquipment();
                break;
            case 5:
                //sellFish();
                break;
            default:
                cout << "\nNie ma takiej opcji" << endl;
                overworldSelector();
                break;
            }
        }

        void fishing()
        {
            clearScreen();
            cout << "Zaczynasz łowić ryby" << endl;
            int chance = currentWater.fishes[0].catchChance + (currentWater.fishes[0].catchChance * currentRod.catchBonus);
            int random = rd() % 100;
            cout << "Szansa złowienia ryby: " + to_string(chance) + "%" << endl;
            cout << "Wylosowana liczba: " + to_string(random) << endl;


            if (random < chance)
            {
                cout << "Udało Ci się złowić rybę!" << endl;
                caughtfish.push_back(currentWater.fishes[0]);
                overworldSelector();
            }
            else
            {
                cout << "Niestety nie udało Ci się złowić ryby" << endl;
                overworldSelector();
            }
        }
        void init(){
            overworldSelector();
        }
};

int main(){

    // RYBY :D
    Fish karp("Karp", 78,5);
    Fish szczupak("Szczupak", 50, 10);
    Fish leszcz("Leszcz", 60, 7);
    Fish sandacz("Sandacz", 40, 12);
    Fish pstrag("Pstrąg", 55, 9);
    Fish sum("Sum", 30, 15);
    Fish okon("Okoń", 70, 6);
    Fish wegorz("Węgorz", 45, 11);
    Fish karas("Karaś", 80, 4);
    Fish lin("Lin", 65, 8);
    Fish ploc("Płoć", 75, 5);

    // Wędki
    Rod start("Wędka startowa", 0, 0);

    // Wody
    Water jezioro({karp},"jeziorko", 0);

    // Uruchamiamy skrypt
    FishingSys system(start,jezioro);
    system.init();
    return 0;
}



