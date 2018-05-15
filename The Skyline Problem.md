## The Skyline Problem
### 问题描述
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).
<div align="center">
<img src="images/skyline1.jpg" height="300px" alt="图片说明" >
<img src="images/skyline2.jpg" height="300px" alt="图片说明" >
</div>

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

1. The number of buildings in any input list is guaranteed to be in the range [0, 10000].
1. The input list is already sorted in ascending order by the left x position Li.
1. The output list must be sorted by the x position.
1. There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

### 思路说明
本体的关键在于记录所有可能的转折点，以及在可能得转折点的高度是多少，并且判断当前点是否是转折点。因此代码中使用`vector<pair<int, int>> ` 来记录可能得转折点x和高度，并区分当前是一个区域的开始还是结束，然后用`multiset<int>`来记录循环到某一个转折点x时，所有的覆盖这个点的区域的高度，取出最高，并判断是否和上一个加入结果集的点高度相同，如果不同，则将当前点加入结果集，并更新上一个加入结果集的点。

```c++
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> h, res;
        multiset<int> m;
        int pre = 0, cur = 0;
        for (auto &a : buildings) {
            h.push_back({a[0], -a[2]});
            h.push_back({a[1], a[2]});
        }
        sort(h.begin(), h.end());
        m.insert(0);
        for (auto &a : h) {
            if (a.second < 0) m.insert(-a.second);
            else m.erase(m.find(a.second)); //跳出当前矩形区域覆盖的位置
            cur = *m.rbegin();//multiset自动排序，因此这是取出当前点的最高高度
            if (cur != pre) {
                res.push_back({a.first, cur}); 
                pre = cur;
            }
        }
        return res;
    }
};
```

### `multiset`使用说明
#### 定义格式
```c++
template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class multiset;
```
其中key是存储的数据类型，Compare是对key进行比较的函数

查询、插入和修改的复杂度均是O(logn)

和`set`不同的是，`multiset`在保持数据有序的同时，允许数据重复, 内部通常由平衡二叉树实现。

#### 基本操作
	insert() 插入
	count() 返回某个值元素的个数
	find()  返回一个指向被查找到元素的迭代器
	erase() 删除某个值的所有元素
	
#### 使用自定义结构体

需要重定义operator<

```c++
#include<iostream>
#include<set>
using namespace std;
struct test
{
    int a;
    char s;
    friend bool operator<(struct test a,struct test b)
    {
        return a.s<b.s;
    }
};
multiset<struct test>element;
int main()
{
    struct test a,b,c,d;
    a.a=1; a.s='d';
    b.a=2; b.s='c';
    c.a=4; c.s='b';
    d.a=3; d.s='a';
    element.insert(d);
    element.insert(b);
    element.insert(c);
    element.insert(a);
    multiset<struct test>::iterator it;
    for(it=element.begin(); it!=element.end();it++)
        cout<<(*it).a<<" ";
    cout<<endl;
    for(it=element.begin(); it!=element.end();it++)
        cout<<(*it).s<<" ";
}

```

#### 交集，并集，差集
```c++
#include<stdio.h>
#include<string>
#include<set>
#include<iostream>
#include <algorithm>//包含
using namespace std;

struct compare//自定义排序方式
{
    bool operator() (string s1,string s2)
    {
        return s1>s2;
    }///自定义一个仿函数，仿函数(functor)，就是使一个类的使用看上去象一个函数。其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了。
};
int main()
{
    set<string,compare> s;//建立第一个集合
    s.insert(string("apple"));
    s.insert(string("english"));
    s.insert(string("bcd"));
    cout<<"第一个集合s1为:"<<endl;
    set<string,compare>::iterator it = s.begin();
    while(it!=s.end())
        cout<<*it++<<"   ";
    
    set<string,compare> s2;//建立第二个集合
    s2.insert(string("abc"));
    s2.insert(string("apple"));
    s2.insert(string("english"));
    cout<<endl<<"第一个集合s2为:"<<endl;
    it = s2.begin();
    while(it!=s2.end())
        cout<<*it++<<"   ";
    cout<<endl<<endl;
    
    string str[10];
    string *end =set_intersection(s.begin(),s.end(),s2.begin(),s2.end(),str,compare());//求交集，返回值指向str最后一个元素的尾端
    /*set_intersection包含于#include <algorithm>   头文件中  其中上面的不一定非要为set容器 也可以使数组 但是前提是要把2个数组都排好序才可以
     返回值是一个指向交集序列末尾的迭代器 至于是什么迭代器与第5个参数有关 如果是数组 返回为int的迭代器 */
    cout<<"s1,s2的交集为:"<<endl;
    string *first = str;
    while(first<end)
        cout <<*first++<<" ";
    
    
    cout<<endl<<endl<<"s1,s2的并集为："<<endl;
    end =set_union(s.begin(),s.end(),s2.begin(),s2.end(),str,compare());//并集
    first = str;
    while(first<end)
        cout <<*first++<<" ";
    
    
    cout<<endl<<endl<<"s2相对于s1的差集："<<endl;
    first = str;
    end = std::set_difference(s.begin(),s.end(),s2.begin(),s2.end(),str,compare());//s2相对于s1的差集
    while(first<end)
        cout <<*first++<<" ";
    
    
    cout<<endl<<endl<<"s1相对于s2的差集："<<endl;
    first = str;
    end = std::set_difference(s2.begin(),s2.end(),s.begin(),s.end(),str,compare());//s1相对于s2的差集
    
    while(first<end)
        cout <<*first++<<" ";
    cout<<endl<<endl;
    first = str;
    end = std::set_symmetric_difference(s.begin(),s.end(),s2.begin(),s2.end(),str,compare());//上面两个差集的并集
    while(first<end)
        cout <<*first++<<" ";
    cout<<endl;
    
}
```

