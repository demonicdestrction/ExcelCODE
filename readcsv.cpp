#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
#define MAXSIZE 500
typedef struct Block * List;
struct Block{
    string name;
    float area;
    string description;
    int num1;
    int num2;
    List Next;
};
typedef struct House * Ho;
struct House{
    int ID;
    string name;
    int floors;
    List FirstBlock;
    vector<float> areas;

     void countAreas() {
        for(int i = 1;i <= floors;i++){
          float tempArea = 0;
          List tempBlock = FirstBlock;
          while(tempBlock != nullptr){
            if(((tempBlock ->num1) <= i) && (i <= tempBlock -> num2)){
                tempArea += tempBlock -> area;
            }
            tempBlock = tempBlock -> Next;
          }
          //house.areas.push_back(tempArea);
          areas.push_back(tempArea);
          cout << "第" << i << "层的面积：" << tempArea << endl;
        }
    }
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
void countAreas1(House house){
    for(int i = 1;i <= house.floors;i++){
          float tempArea = 0;
          List tempBlock = house.FirstBlock;
          while(tempBlock != nullptr){
            if(((tempBlock ->num1) <= i) && (i <= tempBlock -> num2)){
                tempArea += tempBlock -> area;
            }
            tempBlock = tempBlock -> Next;
          }
          //house.areas.push_back(tempArea);
          house.areas.push_back(tempArea);
          cout << "第" << i << "层的面积：" << tempArea << endl;
    }
    cout << house.areas.size() << endl;
}
void creatCsv(vector<House> houses){
    ofstream file("面积导出.csv");

    if (!file.is_open()) {
        cerr << "Unable to open file";
    }
    // 写入表头
    file << "ID,资产名称,序号,面积\n";

    for (int i = 0; i < houses.size(); ++i) {
        //House temp1 = houses[i];
        file << houses[i].ID << ", " << houses[i].name;
         List temp = houses[i].FirstBlock;
         int j = 1;
         while (temp != nullptr){
             if(j > 1){
                file << "   ,   ";
             }
             file << " ,"<< j++ << "," << temp -> area  << endl;
            //cout << temp -> name << " "<< temp -> area << endl;
            temp = temp -> Next;
         }
         //countAreas(houses[i]);
    }
    file.close();
}
void creatCsv1(vector<House> houses){
    ofstream file("面积导出1.csv");

    if (!file.is_open()) {
        cerr << "Unable to open file";
    }
    // 写入表头
    file << "ID,资产名称,序号,面积\n";

    for (int i = 0; i < houses.size(); ++i) {
        vector<float> areas = houses[i].areas;
        //House temp1 = houses[i];
        file << houses[i].ID << ", " << houses[i].name;
         //List temp = houses[i].FirstBlock;
         int j = 1;
         //cout << houses[i].areas.size();
         //cout << areas.size();
         for(int k = 0; k < areas.size(); k++){
             if(j > 1){
                file << "   ,   ";
             }
             file << " ,"<< j++ << "," << areas[k]  << endl;
            //cout << temp -> name << " "<< temp -> area << endl;
            //temp = temp -> Next;
         }
         //countAreas(houses[i]);
    }
    file.close();
}
House* createHouse(int ID, string name, int floors) {
    House* newHouse = new House;
    //List newHouse = (List)malloc(sizeof(struct House));
    newHouse->ID = ID;
    newHouse->name = name;
    newHouse->floors = floors;
    return newHouse;
}
int main() {
    ifstream file("房屋3.csv");
    string line;
    vector<House> houses;

    // 跳过第一行（标题行）
    if (std::getline(file, line)) {
    } else {
        std::cerr << "NOTFOUNF File" << std::endl;
        return 1;
    }
    List temp1;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> values;
        while (getline(ss, item, ',')) {
            values.push_back(item);

        }
        List block1 = createBlock(values[1],stof(values[2]),values[3],stoi(values[4]),stoi(values[5]));
        House house1 = {stoi(values[0]),values[1],stoi(values[6]),block1};
        //house1.FirstBlock = temp;
        if(houses.size() > 1 && house1.name == houses[(houses.size()) - 1].name){
               temp1 -> Next = block1;
               temp1 = block1;
               //free(temp1);
               //free(house1);
        }else{
            temp1 = block1;
            houses.push_back(house1);
        }
    }
    cout << houses.size() << endl;
    for (int i = 0; i < houses.size(); ++i) {
        cout << houses[i].ID << ", Name: " << houses[i].name << endl;
         List temp = houses[i].FirstBlock;
         int j = 1;
         while (temp != nullptr){
             cout << "第"<< j++ <<"块的面积：" <<temp -> area  << endl;
            //cout << temp -> name << " "<< temp -> area << endl;
            temp = temp -> Next;
         }
         //countAreas1(houses[i]);
         houses[i].countAreas();
    }
    creatCsv1(houses);
    //cout << houses[1].name << endl;
    file.close();

    return 0;
}
