// Project UID c1f28c309e55405daf00c565d57ff9ad
#include <iostream>
#include <sstream>
#include "json.hpp"
using nlohmann::json;
using namespace std;




#include "List.h"

class OHQueue {
public:

  //takes in valid input stream meaning request is either GET, DELETE or POST
  //can have invalid path or path matching request
  //reads the request and returns an int that corresponds to each command
  // GET returns 0, DELETE returns 1, POST returns 2 //returns -1
  bool readRequest(istream& is){
    string method;
    if(!(is>>method))
      return false;
    
    string path;
    is>>path;
    collectData(is);
    json newStudent = inOut;
    
    if(method == "GET"){
      if(path=="/api/")
        getApi();
      else if(path=="/api/queue/head/")
        getHead();
      else if(path=="/api/queue/")
        getQueue();
      else
        badRequest();


    }
    else if(method == "DELETE"){
      if(path=="/api/queue/head/")
        DELETE();
      else
        badRequest();
    }
    else if(method == "POST"){
      if(path=="/api/queue/tail/"){
        POST(newStudent);
      }
        
      else
        badRequest();
    }
    else
      assert(false);
    return true;
  }

  //collects data from the stream after the method
  //clears data if there is none to be collected
  void collectData(istream & is){
    string input;
    is>>input;
    while(input!="Content-Length:")
    {
      is>>input;
    }
    is>>input;
    if(stoi(input)==0){
      is>>input;
    }
    else{
      is>>inOut;
    }
  }


  void getApi(){
    string code = "200 OK";
    size_t length = 160;
    string body = 
            "{\n    \"queue_head_url\": \"http://localhost/queue/head/\"";
    body += ",\n    \"queue_list_url\": \"http://localhost/queue/\",\n";
    body += "    \"queue_tail_url\": \"http://localhost/queue/tail/\"\n}\n";
    writeResponse(code,length,body);

  }

  void badRequest(){
    cout<<"HTTP/1.1 400 Bad Request\nContent-Type: application/json;"
    <<" charset=utf-8\nContent-Length: 0\n\n";

  }

  void POST(json& add){
    string code = "201 Created";
    string test1 = add["uniqname"];
    Student newStu = {add["uniqname"],add["location"]};
    queue.push_back(newStu);
    add["position"] = lastPosition++;
    string body = add.dump(4)+"\n";
    size_t content_length = body.length();
    writeResponse(code,content_length,body);

  }

  void getHead(){
    json output;
    if(queue.size()==0)
      badRequest();
    else {
      output["uniqname"] = queue.front().uniqname;
      output["location"] = queue.front().location;
      output["position"] = 1;
      string code = "200 OK";
      string body = output.dump(4)+"\n";
      size_t content_length = body.length();
      writeResponse(code,content_length,body);
    }
  }
  

  void getQueue(){
    json content;
    string code = "200 OK";
      content["count"] = 0;
      content["results"];
      content["count"] = queue.size();
      int pos = 1;
      for(List<Student>::Iterator it=queue.begin();it!=queue.end();++it){
        json tmp;
        tmp["uniqname"] = (*it).uniqname;
        tmp["location"] = (*it).location;
        tmp["position"] = pos++;
        content["results"].push_back(tmp);

      
      }
    string  body = content.dump(4)+"\n";
    size_t content_length = body.length();
    writeResponse(code,content_length,body);
  }

  void DELETE(){
    if(queue.size()==0)
      badRequest();
    else{
    List<Student>::Iterator it=queue.begin();
    queue.erase(it);
    cout<<"HTTP/1.1 204 No Content\nContent-Type: application/json; "
    <<"charset=utf-8\nContent-Length: 0\n\n";
    }

  }

  void writeResponse(string code, size_t length, string body){
    cout<<"HTTP/1.1 "<<code<<endl;
    cout<<"Content-Type: application/json; charset=utf-8"<<endl;
    cout<<"Content-Length: "<<length<<endl;
    if(length!=0){
      cout<<endl;
      cout<<body;
    }
  }


private:
  struct Student {
    string uniqname;
    string location;
  };
  int lastPosition = 1;
  json inOut;
  List<Student> queue;
};

int main() {
  string a = "POST /api/queue/tail/ HTTP/1.1\nHost: localhost\nContent-Type:";
  a+=" application/json; charset=utf-8\nContent-Length: 58\n\n{\n    \"uniqname\":";
  a+=" \"jackgood\",\n    \"location\": \"Table 5\"\n}";
  a+="GET /api/queue/head/ HTTP/1.1\nHost: localhost\nContent-Type: application/json;";
  a+=" charset=utf-8\n\nContent-Length: 0\n\n";
  istringstream test(a);
  OHQueue queue = OHQueue();
  //char var = cin.peek();
  while(queue.readRequest(cin));
}