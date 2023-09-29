// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_pushsizebasic) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_TRUE(list.size()==3);
}

TEST(test_pushfrontbackpopfront) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_back(4);
    ASSERT_TRUE(list.size()==4);
    list.pop_front();
    list.pop_front();
    ASSERT_TRUE(list.front()==1);
    ASSERT_TRUE(list.back()==4);
    ASSERT_TRUE(list.size()==2);
}

TEST(test_pushfrontbackpopback) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_back(4);
    ASSERT_TRUE(list.size()==4);
    list.pop_back();
    list.pop_back();
    ASSERT_TRUE(list.front()==3);
    ASSERT_TRUE(list.back()==2);
    ASSERT_TRUE(list.size()==2);
}

TEST(test_pushbackfirstpopback) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(4);
    ASSERT_TRUE(list.size()==4);
    list.pop_front();
    list.pop_back();
    ASSERT_TRUE(list.front()==1);
    ASSERT_TRUE(list.back()==2);
    ASSERT_TRUE(list.size()==2);
}

TEST(clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(4);
    list.clear();
    ASSERT_TRUE(list.empty());
   
}

TEST(Iterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    int i=0;
    for(auto it = list.begin(); it!=list.end();++it ){
        ASSERT_TRUE(*it==i);
        i++;
    }
}

TEST(copyCnstr) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(4);
    List<int> copyList(list);
    ASSERT_TRUE(copyList.size()==4);
    copyList.pop_front();
    copyList.pop_back();
    ASSERT_TRUE(copyList.front()==1);
    ASSERT_TRUE(copyList.back()==2);
    ASSERT_TRUE(copyList.size()==2);
    ASSERT_TRUE(list.size()==4);
    ASSERT_TRUE(list.front()==4);
   ASSERT_TRUE(list.back()==3);
}

TEST(BIG3Iterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    int i=0;
    List<int>::Iterator s = list.begin();
    List<int>::Iterator t = list.end();
    t = s;
    for(auto it(t); it!=list.end();++it ){
        ASSERT_TRUE(*it==i);
        i++;
    }
}

TEST(IteratorTests) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    List<int>::Iterator s = list.begin();
    List<int>::Iterator t = list.end();
    ASSERT_TRUE(s!=t);
    t = s;
    ++++t;
    ++s;
    --t;
    ASSERT_TRUE(s==t);
}

TEST(assignmentOperatorNonEmpty) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(4);
    List<int> copyList;
    copyList.push_back(1);
    copyList = list;
    ASSERT_TRUE(copyList.size()==4);
    copyList.pop_front();
    copyList.pop_back();
    ASSERT_TRUE(copyList.front()==1);
    ASSERT_TRUE(copyList.back()==2);
    ASSERT_TRUE(copyList.size()==2);
    ASSERT_TRUE(list.size()==4);
    ASSERT_TRUE(list.front()==4);
   ASSERT_TRUE(list.back()==3);
}

TEST(assignmentReturn) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    List<int> copyList;
    copyList.push_back(1);
    List<int> copy2(copyList);
    copy2 = copyList = list;
    ASSERT_TRUE(list.front()==copyList.front());
    ASSERT_TRUE(copy2.front()==list.front());
    ASSERT_TRUE(list.back()==copyList.back());
    ASSERT_TRUE(copy2.back()==list.back());
    copy2.pop_back();
    ASSERT_TRUE(list.front()==copyList.front());
    ASSERT_TRUE(list.back()==copyList.back());
}

TEST(Erase) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    List<int>::Iterator remove = list.begin();
    ++++remove;
    list.erase(remove);
    int i=0;
    for(auto it = list.begin(); it!=list.end();++it ){
        ASSERT_TRUE(*it==i);
        i++;
        if(i==2)
            i++;
    }
    ASSERT_TRUE(list.size()==3);
}
TEST(EraseLast) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    List<int>::Iterator remove = list.begin();
    ++++++remove;
    list.erase(remove);
    int i=0;
    for(auto it = list.begin(); it!=list.end();++it ){
        ASSERT_TRUE(*it==i);
        i++;
    }
    ASSERT_TRUE(list.size()==3);
}
TEST(EraseFirst) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    List<int>::Iterator remove = list.begin();
    list.erase(remove);
    int i=1;
    for(auto it = list.begin(); it!=list.end();++it ){
        ASSERT_TRUE(*it==i);
        i++;
    }
    ASSERT_TRUE(list.size()==3);
}

TEST(Insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);
    list.push_front(0);
    List<int>::Iterator in = list.begin();
    list.insert(in,-1);
    in = list.begin();
    ++++++in;
    list.insert(in,2);
    int i=-1;
    for(auto it = list.begin(); it!=list.end();++it ){
        ASSERT_TRUE(*it==i);
        i++;
    }
}

TEST(CompileTest){
        List<int> my_list;

    int size = 0;
    ASSERT_TRUE(my_list.empty());
    ASSERT_TRUE(my_list.size()==0);
    ASSERT_TRUE(my_list.size() == size);

    my_list.push_front(42);
    my_list.push_back(42);

    my_list.front() = 73;
    my_list.back() = 73;

    my_list.pop_front();
    my_list.pop_back();
    ASSERT_TRUE(my_list.empty());

    List<int> list2(my_list);
    list2 = my_list;

    List<int>::Iterator iter = my_list.begin();
    my_list.insert(iter, 42);
    iter = my_list.begin();
    my_list.erase(iter);
    ASSERT_TRUE(my_list.empty());
    iter = my_list.begin();

    List<int>::Iterator iter2 = my_list.end();
    const List<int>::Iterator iter3 = iter2;

    bool b = iter == iter2;
    ASSERT_TRUE(b);
    b = iter3 == my_list.end();
    ASSERT_TRUE(b);
    b = my_list.end() == iter3;
    ASSERT_TRUE(b);
    my_list.push_front(42);
    my_list.push_back(42);
    iter = my_list.begin();
    b = iter != iter2;
    ASSERT_TRUE(b);
    b = iter3 != my_list.end();
    ASSERT_FALSE(b);
    b = my_list.end() != iter3;
    ASSERT_FALSE(b);
    ++iter;

    ASSERT_TRUE(*iter==42);

    List<int>::Iterator iter_cpy(iter);
    iter_cpy = iter;

    ASSERT_TRUE(*++--iter==42);
    ASSERT_TRUE(*--++my_list.begin()==42);

    my_list.insert(my_list.begin(), 3);
    my_list.erase(my_list.begin());

    List<int> list3;
    list3.push_back(3);
    ASSERT_TRUE(*list3.begin()==3);

    List<int> list4;
    list4.push_back(4);
    ASSERT_TRUE(list4.size()==1);

    my_list.clear();

}

TEST_MAIN()
