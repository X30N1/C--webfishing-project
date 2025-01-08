#include <iostream>
#include <string>
#include <random>
#include <vector>

using namespace std;

class Fish {
    private:
        string name;
        int catchChance;
        int price;
    public:
        Fish(string fishName, int chance, int pricing){
            name = fishName;
            catchChance = chance;
            price = pricing;
        }
};

class Rod {
    private:
        string name;
        float catchBonus;
        int price;
    public:
        Rod(string rodName, int bonus, int pricing){
            name = rodName;
            catchBonus = bonus;
            price = pricing;
        }

};

class Water {
    private:
        string name;
        vector<Fish> fishes;
    public:
        Water(vector<Fish> fishies, string waterName) {
            name = waterName;
            fishes = fishies;
        }
};

class FishingSys {
    private:
        Rod currentRod;
        Water currentWater;
        random_device rd;
        vector<Rod> rods;
        int currency;
    public:
        FishingSys(Rod starter, Water first){
            currentRod = starter;
            currentWater = first;
            rods.push_back(starter)
        }
        void setCurrentRod(Rod newrod){
            currentRod = newrod;
        }
        void setCurrentWater(Water newater) {
            currentWater = newater;
        }
        void printAllRods(){
            cout << rods << endl;
        }
        void printCurrency()

};



