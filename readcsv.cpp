#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
#define MAXSIZE 500
#define HALF 1
typedef struct Block * List;
struct Block{
    string name;
    float area;
    string description;
    int num1;
    int num2;
    List Next;
};
Block* createBlock(string name, float area,string type, int num1, int num2) {
    Block* newBlock = new Block;
    //List newBlock = (List)malloc(sizeof(struct Block));
    newBlock->name = name;
    newBlock->area = area;
    newBlock->description = type;
    newBlock->num1 = num1;
    newBlock->num2 = num2;
    newBlock->Next = nullptr;
    return newBlock;
}
typedef struct House * Ho;
struct House{
    int ID;
    string name;
    int floors;
    List FirstBlock;
    vector<float> areas;
    float footprintarea;
    //���ݿ����������
    void countAreas() {
        for(int i = 1;i <= floors;i++){
          float tempArea = 0;
          List tempBlock = FirstBlock;
          while(tempBlock != nullptr){
            if(((tempBlock ->num1) <= i) && (i <= tempBlock -> num2)){
                tempArea += tempBlock -> area * HALF;
            }
            tempBlock = tempBlock -> Next;
          }
          areas.push_back(tempArea);
          //cout << "��" << i << "��������" << tempArea << endl;
        }
    }
    //���ݿ������ռ�����
     void countFootprintarea(){
         float tempArea = 0;
         List tempBlock = FirstBlock;
         while(tempBlock != nullptr){
             tempArea += tempBlock -> area;
             tempBlock = tempBlock -> Next;
         }
         footprintarea = tempArea;
     }
};
House* createHouse(int ID, string name, int floors) {
    House* newHouse = new House;
    //List newHouse = (List)malloc(sizeof(struct House));
    newHouse->ID = ID;
    newHouse->name = name;
    newHouse->floors = floors;
    return newHouse;
}
//����������ļ�
void creatCsv(vector<House> houses){
    ofstream file("�������.csv");
    if (!file.is_open()) {
        cerr << "�򲻿��ļ���";
    }
    file << "ID,�ʲ�����,���,���\n";
    for (int i = 0; i < houses.size(); ++i) {
        vector<float> areas = houses[i].areas;
        file << houses[i].ID << "," << houses[i].name;
        int j = 1;
        for(int k = 0; k < areas.size(); k++){
             if(j > 1){
                file << ",";
             }
             file << ","<< j++ << "," << areas[k]  << endl;
         }
    }
    file.close();
}
//��ӡ�����
void printHouseBlock(House house){
    cout << house.ID << ", Name: " << house.name << endl;
    List temp = house.FirstBlock;
    int i = 1;
    while (temp != nullptr){
        cout << "��"<< i++ <<"��������" << temp -> area  << endl;
        temp = temp -> Next;
    }
}
//��ӡ�����
void printFloorArea(House house){
     for(int i = 0; i < house.areas.size(); i++){
        cout << "��" << i + 1 << "��������" <<house.areas[i] << endl;
     }
}
//��ȡcsv������house��
vector<House> readcsv()
{
    ifstream file("����.csv");
    string line;
    vector<House> houses;

    // ������һ�У������У�
    if (getline(file, line)) {
    } else {
        cerr << "�Ҳ����ļ�" << endl;
    }
    List temp1;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> values;
        while (getline(ss, item, ',')) {
            values.push_back(item);
        }
        List block = createBlock(values[1],stof(values[2]),values[3],stoi(values[4]),stoi(values[5]));
        House house = {stoi(values[0]),values[1],stoi(values[6]),block};
        if(houses.size() > 1 && house.name == houses[(houses.size()) - 1].name){
               temp1 -> Next = block;
               temp1 = block;
        }else{
            temp1 = block;
            houses.push_back(house);
        }
    }
    file.close();
    return houses;
}
int main() {
    vector<House> houses = readcsv();
    for (int i = 0; i < houses.size(); ++i) {
         houses[i].countAreas();
         houses[i].countFootprintarea();

         printHouseBlock(houses[i]);
         printFloorArea(houses[i]);
    }
    creatCsv(houses);
    return 0;
}
