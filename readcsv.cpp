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
    //根据块面积算层面积
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
          //cout << "第" << i << "层的面积：" << tempArea << endl;
        }
    }
    //根据块面积算占地面积
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
//导出层面积文件
void creatCsv(vector<House> houses){
    ofstream file("面积导出.csv");
    if (!file.is_open()) {
        cerr << "打不开文件！";
    }
    file << "ID,资产名称,序号,面积\n";
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
//打印块面积
void printHouseBlock(House house){
    cout << house.ID << ", Name: " << house.name << endl;
    List temp = house.FirstBlock;
    int i = 1;
    while (temp != nullptr){
        cout << "第"<< i++ <<"块的面积：" << temp -> area  << endl;
        temp = temp -> Next;
    }
}
//打印层面积
void printFloorArea(House house){
     for(int i = 0; i < house.areas.size(); i++){
        cout << "第" << i + 1 << "层的面积：" <<house.areas[i] << endl;
     }
}
//读取csv，存入house中
vector<House> readcsv()
{
    ifstream file("房屋.csv");
    string line;
    vector<House> houses;

    // 跳过第一行（标题行）
    if (getline(file, line)) {
    } else {
        cerr << "找不到文件" << endl;
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
