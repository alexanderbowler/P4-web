#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
#include "List.h"


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //default cnstctr
  List():first(nullptr),last(nullptr),length(0){
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return (first==nullptr)&&(last==nullptr);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const{
    return length;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node* add = new Node();
    add->datum = datum;
    add->next = first;
    if(first)
      first->prev = add;
    first = add;
    first->prev = nullptr;
    if(length==0)
      last = first;
    length++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node* add = new Node();
    add->datum = datum;
    add->next = nullptr;
    add->prev = last;
    if(last)
      last->next = add;
    last = add;
    if(length==0)
      first = last;
    length++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    Node* second = first->next;
    delete first;
    first = second;
    length--;
    if(first)
      first->prev = nullptr;
    if(length==0)
      last=nullptr;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    if(length==1){
      pop_front();
      last=nullptr;
    }
    else{
    Node* previous = last->prev;
    delete last;
    last = previous;
    previous->next = nullptr;
    length--;
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    Node* nextNode = first;
    Node* tmp;
    while(nextNode!=nullptr){
      tmp = nextNode->next;
      delete nextNode;
      nextNode = tmp;
    }
    first = nullptr;
    last = nullptr;
    length = 0;

  }
  //destructor
  ~List(){
    clear();
  }
  

  //copy cnst
  List(const List<T> &other){
    clear();
    copy_all(other);
  }

  //assignment operator
  List & operator=(const List<T> &rhs){
    if(this == &rhs)
      return *this;
    clear();
    copy_all(rhs);
    return *this;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    assert(empty());
    Node* i = other.first;
    while(i){
      push_back(i->datum);
      i = i->next;
    }
  }

  Node *first=nullptr;   // points to first Node in list, or nullptr if list is empty
  Node *last=nullptr;    // points to last Node in list, or nullptr if list is empty

  int length=0; //number of els in the list

public:
  ////////////////////////////////////////
  class Iterator {
    
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    //default cnstr
    Iterator():node_ptr(nullptr){}

    //destructor
    ~Iterator(){node_ptr = nullptr;}

    //copy cnstr
    Iterator(const Iterator &other):node_ptr(other.node_ptr){}

    //assignment operator
    Iterator & operator=(const Iterator &rhs){
      if(this==&rhs)
        return *this;
      node_ptr = rhs.node_ptr;
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    //derefenecable iterator requres that the node is valid
    // returns the data in the node
    T & operator*() const{
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator & operator++(){
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p): node_ptr(p){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    Iterator i = Iterator(first);
    return i;
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    Iterator i = Iterator();
    return i;
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    assert(i!=nullptr);
    if(i.node_ptr==first)
      pop_front();
    else if(i.node_ptr==last)
      pop_back();
    else{
    Node* removeAd = i.node_ptr;
    Node* nextAd = (++i).node_ptr;
    --i;
    (--i).node_ptr->next = nextAd;
    delete removeAd;
    length--;
    if(length==0)
    {
      first=nullptr;
      last = nullptr;
    }
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    if(i==nullptr){
      Node* add = new Node();
      add->datum = datum;
      add->next = nullptr;
      add->prev = nullptr;
      first = add;
      last = add;
      length++;
    }
    else{
    if(i.node_ptr==first)
      push_front(datum);
    else{
    Node* add = new Node();
    add->next = i.node_ptr;
    add->datum = datum;
    add->prev = (--i).node_ptr;
    add->prev->next = add;
    add->next->prev = add;
    length++;
    }
    }
    /*if(i.node_ptr)
      
    if(add->next)
      add->next->prev = add;*/
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.






#endif // Do not remove this. Write all your code above this line.
