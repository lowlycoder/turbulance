#include<iostream>
using namespace std;
class Set
{
public:
    int items[100]; //定义一个数组作为容器存放100个集合元素
    int number; //定义数字i表示集合中元素的个数
    //构造函数和析构函数
    Set() {
        this->number = 0;
        memset(this->items,0,sizeof(items));
    }
    //初始化方法
    int init(int items[], int num);
    //添加元素
    bool add_item(int item);
    //删除元素
    bool remove_item(int item);
    //求集合的并集
    Set operator+ (Set set2);
    //求集合的交集
    Set operator* (Set set2);
    //显示集合元素
    int display();
    //判断集合当中是否存在item,返回元素在集合中的位置，不存在返回-1
    int is_exist(int item);
};

//判断数组中是否包含元素 item
int Set::is_exist(int item)
{
    for(int i=0; i< this->number; i++) {
        if(this->items[i] == item) {
            return i;
        }
    }
    return -1;
}

//向数组中添加元素
bool Set::add_item(int item)
{
    if(is_exist(item) >= 0 || this->number >= 100) {
        return false;
    }
    this->items[this->number] = item;
    this->number++;
    return true;
}

//从集合中移除元素
bool Set::remove_item(int item)
{
    int pos = is_exist(item);
    if(pos == -1) return false;
    for(int i=pos; i< this->number-1; i++) {
        this->items[i] = this->items[i+1];
    }
    this->number--;
    return true;
}

//求两个集合的交集
Set Set::operator* (Set set2)
{
    Set result;
    for(int i=0; i< this->number; i++) {
        if(set2.is_exist(this->items[i]) >= 0) {
            result.items[result.number] = this->items[i];
            result.number++;
        }
    }
    return result;
}

//求两个集合的并集
Set Set::operator+ (Set set2)
{
    Set result;
    for(int i=0; i<this->number; i++) {
        result.items[result.number] = this->items[i];
        result.number++;
    }
    for(int j=0; j<set2.number; j++) {
        if(result.is_exist(set2.items[j]) == -1) {
            result.items[result.number] = set2.items[j];
            result.number++;
        }
    }
    return result;
}

int main(){

}
