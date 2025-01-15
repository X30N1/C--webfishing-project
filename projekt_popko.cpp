#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <limits>

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
        // Zmienne obecnie używane przez użytkownika
        Rod currentRod;
        Water currentWater;

        // Zmienne pomocnicze
        random_device rd;

        // Zmienne przechowujące dane
        vector<Water> places;
        vector<Rod> rods;
        vector<Fish> caughtfish;
        vector<Rod> ownedRods;
        vector<Water> ownedWaters;
        int currency = 0;


        FishingSys(Rod& starter, Water& first, vector<Water> waters = {}, vector<Rod> roddies = {}){
            currentRod = starter;
            currentWater = first;
            places = waters;
            rods = roddies;
        }
        void pauseScreen() {
            cout << "\nNaciśnij ENTER aby kontynuować...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
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
        void pushRod(Rod& addrod){
            ownedRods.push_back(addrod);
        }
        void pushWater(Water& addwater){
            ownedWaters.push_back(addwater);
        }
        void switchrod(){
            clearScreen();
            if(ownedRods.size() == 0){
            cout << "Nie posiadasz żadnych wędek" << endl;
            pauseScreen();
            overworldSelector();
            }
            cout << "Wybierz wędkę: " << endl;
            for (int i = 0; i < ownedRods.size(); i++)
            {
            cout << i + 1 << ". " << ownedRods[i].name << " | Bonus do wyłowienia: " << ownedRods[i].catchBonus << "x" << endl;
            }
            cout << ownedRods.size() + 1 << ". Powrót" << endl;
            int choice;
            cin >> choice;
            if (choice > ownedRods.size() + 1 || choice < 1)
            {
            cout << "Nie ma takiej wędki" << endl;
            pauseScreen();
            switchrod();
            }
            else if (choice == ownedRods.size() + 1)
            {
            overworldSelector();
            }
            else
            {
            setCurrentRod(ownedRods[choice - 1]);
            cout << "Zmieniono wędkę na: " << currentRod.name << endl;
            pauseScreen();
            overworldSelector();
            }
        }
        void travel(){
            clearScreen();
            if(ownedWaters.size() == 0){
            cout << "Nie posiadasz żadnych miejsc, do których mógłbyś się udać" << endl;
            pauseScreen();
            overworldSelector();
            }
            cout << "Wybierz miejsce, do którego chcesz się udać: " << endl;
            for (int i = 0; i < ownedWaters.size(); i++)
            {
            cout << i + 1 << ". " << ownedWaters[i].name << endl;
            }
            cout << ownedWaters.size() + 1 << ". Powrót" << endl;
            int choice;
            cin >> choice;
            if (choice > ownedWaters.size() + 1 || choice < 1)
            {
            cout << "Nie ma takiego miejsca" << endl;
            pauseScreen();
            travel();
            }
            else if (choice == ownedWaters.size() + 1)
            {
            overworldSelector();
            }
            else
            {
            setCurrentWater(ownedWaters[choice - 1]);
            cout << "Zmieniono miejsce na: " << currentWater.name << endl;
            pauseScreen();
            overworldSelector();
            }
        }
        void sellFish(){
            clearScreen();
            cout << "Wybierz rybę, którą chcesz sprzedać: " << endl;
            for (int i = 0; i < caughtfish.size(); i++)
            {
            cout << i + 1 << ". " << caughtfish[i].name << " | Cena: " << caughtfish[i].price << endl;
            }
            cout << caughtfish.size() + 1 << ". Sprzedaj wszystkie ryby" << endl;
            cout << caughtfish.size() + 2 << ". Powrót" << endl;
            int choice;
            cin >> choice;
            if (choice > caughtfish.size() + 2 || choice < 1)
            {
            cout << "Nie masz takiej ryby" << endl;
            pauseScreen();
            sellFish();
            }
            else if (choice == caughtfish.size() + 1)
            {
            int total = 0;
            for (const auto& fish : caughtfish)
            {
                total += fish.price;
            }
            currency += total;
            cout << "Sprzedano wszystkie ryby za " << total << " Żetonów" << endl;
            caughtfish.clear();
            pauseScreen();
            overworldSelector();
            }
            else if (choice == caughtfish.size() + 2)
            {
            overworldSelector();
            }
            else
            {
            currency += caughtfish[choice - 1].price;
            cout << "Sprzedano rybę: " << caughtfish[choice - 1].name << " za " << caughtfish[choice - 1].price << " Żetonów" << endl;
            caughtfish.erase(caughtfish.begin() + choice - 1);
            pauseScreen();
            overworldSelector();
            }
        }
        void buyLicence(){
            clearScreen();
            cout << "Wybierz licencję, którą chcesz kupić: " << endl;
            for (int i = 0; i < places.size(); i++)
            {
            bool alreadyOwned = false;
            for (const auto& ownedWater : ownedWaters)
            {
                if (ownedWater.name == places[i].name)
                {
                alreadyOwned = true;
                break;
                }
            }
            if (alreadyOwned)
            {
                cout << i + 1 << ". " << places[i].name << " | Cena: " << places[i].licenceCost << " (Posiadasz już tę licencję)" << endl;
            }
            else
            {
                cout << i + 1 << ". " << places[i].name << " | Cena: " << places[i].licenceCost << endl;
            }
            }
            cout << places.size() + 1 << ". Powrót" << endl;
            int choice;
            cin >> choice;
            if (choice > places.size() + 1 || choice < 1)
            {
            cout << "Nie ma takiej licencji" << endl;
            pauseScreen();
            buyLicence();
            }
            else if (choice == places.size() + 1)
            {
            overworldSelector();
            }
            else
            {
            bool alreadyOwned = false;
            for (const auto& ownedWater : ownedWaters)
            {
                if (ownedWater.name == places[choice - 1].name)
                {
                alreadyOwned = true;
                break;
                }
            }
            if (alreadyOwned)
            {
                cout << "Posiadasz już tę licencję" << endl;
                pauseScreen();
                buyLicence();
            }
            else if (currency >= places[choice - 1].licenceCost)
            {
                currency -= places[choice - 1].licenceCost;
                pushWater(places[choice - 1]);
                cout << "Kupiono licencję na: " << places[choice - 1].name << endl;
                pauseScreen();
                overworldSelector();
            }
            else
            {
                cout << "Nie masz wystarczająco pieniędzy" << endl;
                pauseScreen();
                overworldSelector();
            }
            }
        }
        void buyEquipment(){
            clearScreen();
            cout << "Wybierz sprzęt, który chcesz kupić: " << endl;
            for (int i = 0; i < rods.size(); i++)
            {
            cout << i + 1 << ". " << rods[i].name << " | Bonus do wyłowienia: " << rods[i].catchBonus << "x | Cena: " << rods[i].price << endl;
            }
            cout << rods.size() + 1 << ". Powrót" << endl;
            int choice;
            cin >> choice;
            if (choice > rods.size() + 1 || choice < 1)
            {
            cout << "Nie ma takiego sprzętu" << endl;
            pauseScreen();
            buyEquipment();
            }
            else if (choice == rods.size() + 1)
            {
            overworldSelector();
            }
            else
            {
            if (currency >= rods[choice - 1].price)
            {
            currency -= rods[choice - 1].price;
            pushRod(rods[choice - 1]);
            cout << "Kupiono sprzęt: " << rods[choice - 1].name << endl;
            pauseScreen();
            overworldSelector();
            }
            else
            {
            cout << "Nie masz wystarczająco pieniędzy" << endl;
            pauseScreen();
            overworldSelector();
            }
            }
        }
        void overworldSelector(){
            clearScreen();
            cout << "Obecnie jesteś w pobliżu: " << currentWater.printName() << endl;
            cout << "Posiadasz: " << currency << " Żetonów" << endl;
            cout << "Co chciałbyś / chciałabyś zrobić? \n1.Łów ryby \n2.Przejdź gdzie indziej \n3.Zmień ekwipunek \n4.Kup nowy ekwipunek \n5.Sprzedaj ryby \n6.kup licencje na wody" << endl;
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                fishing();
                break;
            case 2:
                travel();
                break;
            case 3:
                switchrod();
                break;
            case 4:
                buyEquipment();
                break;
            case 5:
                sellFish();
                break;
            case 6:
                buyLicence();
                break;
            default:
                cout << "\nNie ma takiej opcji" << endl;
                pauseScreen();
                overworldSelector();
                break;
            }
        }
        void fishing()
        {
            clearScreen();
            cout << "Zaczynasz łowić ryby" << endl;

            uniform_int_distribution<int> dist(0, currentWater.fishes.size() - 1);
            int fishIndex = dist(rd);
            Fish selectedFish = currentWater.fishes[fishIndex];

            int chance = selectedFish.catchChance + (selectedFish.catchChance * currentRod.catchBonus);
            int random = rd() % 100;
            cout << "Szansa złowienia ryby: " + to_string(chance) + "%" << endl;
            cout << "Wylosowana liczba: " + to_string(random) << endl;

            if (random < chance)
            {
                cout << "Udało Ci się złowić rybę " << selectedFish.name << endl;
                caughtfish.push_back(selectedFish);
            }
            else
            {
                cout << "Niestety nie udało Ci się złowić ryby" << endl;
            }
            pauseScreen();
            overworldSelector();
        }
        void init(){
            pushWater(currentWater);
            pushRod(currentRod);
            overworldSelector();
        }
};

int main(){

    // Przykładowe ryby
    Fish fish1("Karp", 30, 10);
    Fish fish2("Szczupak", 20, 20);
    Fish fish3("Sum", 15, 30);
    Fish fish4("Pstrąg", 25, 15);
    Fish fish5("Łosoś", 10, 40);
    Fish fish6("Sandacz", 5, 50);
    Fish fish7("Węgorz", 8, 60);
    Fish fish8("Dorsz", 12, 70);
    Fish fish9("Halibut", 7, 80);
    Fish fish10("Tuńczyk", 3, 100);
    Fish fish11("Rekin", 2, 150);
    Fish fish12("Miecznik", 1, 200);

    // Przykładowe wody
    vector<Fish> fishes1 = {fish1, fish2, fish3, fish4};
    vector<Fish> fishes2 = {fish5, fish6, fish7, fish8};
    vector<Fish> fishes3 = {fish9, fish10, fish11, fish12};
    vector<Fish> fishes4 = {fish1, fish5, fish9, fish12};

    Water jezioro(fishes1, "Jezioro", 50);
    Water rzeka(fishes2, "Rzeka", 95);
    Water staw(fishes3, "Staw", 140);
    Water ocean(fishes4, "Ocean", 185);

    // Przykładowa wędka
    Rod start("Podstawowa wędka", 1.0, 0);
    Rod drewno("Wędka z dobrej jakości drewna", 1.2, 50);
    Rod stal("Wędka z dobrej jakości stali", 1.5, 100);
    Rod karbon("Wędka z karbonu", 2.0, 200);
    Rod platyna("Wędka z platyny (Chyba naprawde nie masz co robić z pieniędzmi.)", 3.0, 500);

    // Dodanie wód do systemu
    vector<Water> waters = {jezioro, rzeka, staw, ocean};
    vector<Rod> roddies = {drewno, stal, karbon, platyna};

    // Uruchamiamy skrypt
    FishingSys system(start,jezioro,waters,roddies);
    system.init();
    return 0;
}



