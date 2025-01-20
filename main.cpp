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

    linked_list<string>* posts;
    graph<users>* followings;
    graph<users>* followers;

    users* next, *prev;
public:
    users(string username_in, int password_in)
    {
        password=password_in;
        username=username_in;
        posts=NULL;
        followings=NULL;
        followers=NULL;
        next=NULL;
        prev=NULL;
    }
    void sign_up(users*& start)
    {
        string username_in;
        int password_in;
        cout<<"enter new username: ";
        cin>>username_in;
        cout<<"enter new passwod: ";
        cin>>password_in;

        if(start==NULL)
        {
            start=new users(username_in, password_in);
            cout<<"account created succesfully.\n";
            return;
        }
        else
        {
            users* tmp_users=start;
            while(tmp_users->next!=NULL)
            {
                if(tmp_users->username==username_in)
                {
                    cout<<"error! invalid username.\n";
                    return;
                }
                tmp_users=tmp_users->next;
            }
            if(tmp_users->username==username_in)
            {
                cout<<"error! invalid username.\n";
                return;
            }
            tmp_users->next=new users(username_in, password_in);
            tmp_users->next->prev=tmp_users;
            return;
        }
    }
    void delete_account(users*& start_users)
    {
        string username_in;
        int password_in;
        cout<<"enter user's username to be removed: ";
        cin>>username_in;
        cout<<"enter password: ";
        cin>>password_in;

        users* tmp_users=start_users;
        while(tmp_users!=NULL)
        {
            if(tmp_users->username==username_in && tmp_users->password==password_in)
            {
                tmp_users->prev->next=tmp_users->next;
                tmp_users->next->prev=tmp_users->prev;
                users* tmp_users2=start_users;
                while(tmp_users2!=NULL)
                {
                    tmp_users2->unfollow(username_in);
                    tmp_users2->remove_follower(username_in);
                    tmp_users2=tmp_users2->next;
                }

                delete tmp_users;
                return;
            }
            tmp_users=tmp_users->next;
        }
        cout<<"invalid username\n";
        return;
    }
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
    void follow()
    {}
    void unfollow()
    {}
    void remove_follower()
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