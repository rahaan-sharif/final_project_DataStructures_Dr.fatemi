#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
class linked_list 
{
private:
    T data;
    int id;
    linked_list *next, *prev;

public:
    linked_list(int id_in, T data_in)
    {
        data = data_in;
        id = id_in;
        next = NULL;
        prev = NULL;
    }
    void add_node(linked_list *&start_ll, T data_in) 
    {
        if(start_ll==NULL)
        {
            start_ll=new linked_list(0, data_in);
            return;
        }
        else
        {
            linked_list* tmp_ll=start_ll;
            while(tmp_ll->next!=NULL)
            {
                tmp_ll=tmp_ll->next;
            }
            tmp_ll->next=new linked_list(tmp_ll->id+1, data_in);
            tmp_ll->next->prev=tmp_ll;
            return;
        }
    }
};


template <typename T>
class graph   //this ADT is for storing relations of users.
{
private:
    linked_list<T>* sart_ll;      
public:
    graph()
    {}
    void follow()
    {}
    void unfollow()
    {}
};




class users
{
private:
    string username;
    int password;
    linked_list<string> posts;
    graph<users> followings;
    graph<users> followers;
public:
    users()
    {}
    void sign_up()
    {}
    void delete_account()
    {}
    void watch_profile()
    {}
    void give_relative_accounts()
    {}
    void search_user()
    {}
    void add_new_post()
    {}
    void delete_post()
    {}

    string get_data_from_file(string location)
    {
        ifstream input_file(location);
        if(!input_file)
        {
            cout<<"error! invalid location for text file.\n";
            return NULL;
        }
        else
        {
            string line;
            getline(input_file, line);
            input_file.close();
            return line;
        }
    }
};





int main(void)
{

    return 0;
}
//upload