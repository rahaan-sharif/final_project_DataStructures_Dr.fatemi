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
        if (start_ll == NULL)
        {
            start_ll = new linked_list(0, data_in);
            return;
        }
        else
        {
            linked_list *tmp_ll = start_ll;
            while (tmp_ll->next != NULL)
            {
                tmp_ll = tmp_ll->next;
            }
            tmp_ll->next = new linked_list(tmp_ll->id + 1, data_in);
            tmp_ll->next->prev = tmp_ll;
            return;
        }
    }
};

template<typename T>
class pq_objects
{
public:    
    double key;
    T value;
};

template <typename T>
class pq
{
private:
    pq_objects<T>* value;
    pq* next, prev;
public:
    pq(pq_objects*& value_in)
    {
        value=value_in;
        next=NULL;
        prev=NULL; 
    }
    void add_node(pq*& start_pq, double key_in, T value_in)
    {
        pq_objects<T>* tmp_ob;
        tmp_ob->key=key_in;
        tmp_ob->value=value_in;
        
        if(start_pq==NULL)
        {
            start_pq=new pq(tmp_ob);
            return;
        }
        else
        {
            pq* tmp_pq=start_pq;
            while((tmp_pq->next!=NULL)   &&   (tmp_pq->next->value->key<=tmp_ob->key))
            {
                tmp_pq=tmp_pq->next;
            }

            if(tmp_pq->next==NULL)
            {
                tmp_pq->next=new pq(tmp_ob);
                tmp_pq->next->prev=tmp_pq;
                return;
            }
            else
            {
                pq* tmp_pq2=new pq(tmp_ob);
                tmp_pq2->prev=tmp_pq;
                tmp_pq2->next=tmp_pq->next;
                tmp_pq->next=tmp_pq2;
                tmp_pq2->next->prev=tmp_pq2;
                return;
            }
        }
    }
    pq* get_next(pq*& start_pq)
    {
        return start_pq->next;
    }
    pq* get_prev(pq*& start_pq)
    {
        return start_pq->prev;
    }

};

template <typename T>
class graph // this ADT is for storing relations of users.
{
private:
    linked_list<T> *sart_ll;

public:
    graph()
    {
    }
    void add_node()
    {
    }
};

class users
{
private:
    static int total_users;

    string username;
    int password;

    linked_list<string> *posts;
    graph<users> *followings;
    graph<users> *followers;

    users *next, *prev;

public:
    users(string username_in, int password_in)
    {
        password = password_in;
        username = username_in;
        posts = NULL;
        followings = NULL;
        followers = NULL;
        next = NULL;
        prev = NULL;
        total_users++;
    }
    void sign_up(users *&start)
    {
        string username_in;
        int password_in;
        cout << "enter new username: ";
        cin >> username_in;
        cout << "enter new passwod: ";
        cin >> password_in;

        if (start == NULL)
        {
            start = new users(username_in, password_in);
            cout << "account created succesfully.\n";
            return;
        }
        else
        {
            users *tmp_users = start;
            while (tmp_users->next != NULL)
            {
                if (tmp_users->username == username_in)
                {
                    cout << "error! invalid username.\n";
                    return;
                }
                tmp_users = tmp_users->next;
            }
            if (tmp_users->username == username_in)
            {
                cout << "error! invalid username.\n";
                return;
            }
            tmp_users->next = new users(username_in, password_in);
            tmp_users->next->prev = tmp_users;
            return;
        }
    }
    void main_operations(users *&start)
    {
            cout << "wellcome to your social network!\n";
            cout << "number of total users: " << total_users << endl<<endl;
        int operation = -1;
        while(operation != 0)
        {        
            cout << "choose your operation: " << endl;
            cout << "1- sign up\n";
            cout << "2- sign in\n";
            cout<<"0- exit\n";
            cin >> operation;
            if (operation == 0)
            {
                cout<<"goodbye!\n";
                return;
            }
            else if (operation == 1)
            {
                start->sign_up(start);
            }
            else if (operation == 2)
            {
                break;
            }
            else
            {
                cout<<"error! invalid input.\n";
            }
        }

        string username_in;
        int password_in;
        cout << "** log in **" << endl;

        cout << "enter username: ";
        cin >> username_in;
        cout << "enter password: ";
        cin >> password_in;

        users *cur_user = start;
        while (cur_user != NULL)
        {
            if (cur_user->username == username_in && cur_user->password == password_in)
            {
                cout << "\t loged in...\n";
                break;
            }
            cur_user = cur_user->next;
        }
        if (cur_user == NULL)
        {
            cout << "error! invalid username or password.\n";
            return;
        }
        while (operation != 0)
        {
            cout << "welcome " << username << endl;
            cout << "choose your operation:\n";
            cout << "1- change username or password\n";
            cout<<  "2- delete_account\n";
            cout<<  "3- watch profile\n";
            cout<<  "4- suggest friend\n";
            cout<<  "5- search user\n";
            cout<<  "6- add new post\n";
            cout<<  "7- edit posts\n";
            cout<<  "8- delete post\n";
            cout<<  "9- unfollow\n";
            cout<<  "10-remove follower\n";
            cout<<  "0- exit\n";

            cin>>operation;
            if(operation==1)
                {cur_user->change_username_or_password(cur_user);}
            else if(operation==2)
            {
                cur_user->delete_account(start, cur_user);
                return;
            }
            else if(operation==3)
                {cur_user->watch_profile(cur_user);}
            else if(operation==4)
                {}
            else if(operation==5)
                {start->search_user(start);}
            else if(operation==6)
                {cur_user->add_new_post(cur_user);}
            else if(operation==7)
                {cur_user->edit_posts(cur_user);}
            else if(operation==8)
                {cur_user->delete_post(cur_user);}
            else if(operation==9)
                {cur_user->unfollow(cur_user);}
            else if(operation==10)
                {cur_user->remove_follower(cur_user);}
            else if(operation==0)
            {
                cout<<"goodby!\n";
                return;
            }
            else
            {
                cout<<"error! invalid operation.\n";
            }
        }
    }
    void change_username_or_password(users*& start)
    {
        string username_in;
        int password_in;
        cout<<"choose operation: "<<endl;
        cout<<"1- change password\n";
        cout<<"2- change username\n";
        cout<<"3- change both\n";
        int operation=-1;
        cin>>operation;
        if(operation==1)
        {
            cout<<"enter password: ";
            cin>>password_in;
            start->password=password_in;
            cout<<"changed\n";
        }
        else if(operation==2)
        {
            cout<<"enter username: ";
            cin>>username_in;
            start->username=username_in;
            cout<<"changed\n";
        }
        else if(operation==3)
        {
            cout<<"enter username: ";
            cin>>username_in;
            start->username=username_in;
            cout<<"enter password: ";
            cin>>password_in;
            start->password=password_in;
            cout<<"changed\n";
        }
        else
        {
            cout<<"error! invalid operation\n";
            return;
        }
    }
    void delete_account(users*& start_user, users *&cur_user)
    {
        if(cur_user->prev==NULL)
        {
            start_user=cur_user->next;
        }
        else if(cur_user->next==NULL)
        {
            cur_user->prev->next=NULL;
        }
        else
        {
            cur_user->prev->next=cur_user->next;
            cur_user->next->prev=cur_user->prev;
        }
        users* tmp_user=start_user;
        while(tmp_user!=NULL)
        {
            tmp_user->unfollow(tmp_user, cur_user->username);
            tmp_user->remove_follower(tmp_user, cur_user->username);
            tmp_user=tmp_user->next;
        }

        delete cur_user;
        total_users--;
    }
    void watch_profile(users *&cur_user)// yours or your friend
    {
        int operation=-1;
        cout<<"choose operation: ";
        cout<<"1- watch your profile\n";
        cout<<"2- watch your following profile\n";
        cin>>operation;
        if(operation==1)
        {
            cout<<"username: "<<cur_user->username<<endl;
            cout<<"your posts: \n";
            cur_user->posts->show(cur_user->posts);
            cout<<"your followers:\n";
            cur_user->followers->show(cur_user->followers);
            cout<<"your followings: \n";
            cur_user->followings->show(cur_user->followings);
            return;
        }
        else if(operation==2)
        {
            cout<<"your followings:\n";
            cur_user->followings->show(cur_user->followings);
            cout<<"choose any username to watch profile: \n";
            string username_in;
            cin>>username_in;
            users* tmp_user=cur_user->followings->get_node(cur_user->followings, username_in);
            cout<<"username: "<<tmp_user<<endl;
            cout<<"post: "<<endl;
            tmp_user->posts->show(tmp_user->posts);
            cout<<"followers: \n";
            tmp_user->followers->show(tmp_user->followers);
            cout<<"followings: \n";
            tmp_user->followings->show(tmp_user->followings);
        }
        else
        {
            cout<<"error! invalid operation\n";
            return;
        }

    }
    void suggest_others_users(users*& start, users*& cur_user)
    {
        users* tmp_user=start;
        pq<users>* start_pq=NULL;
        while(tmp_user!=NULL)
        {
            if(tmp_user!=cur_user)
            {
                if(!cur_user->followings->search(cur_user->followings, tmp_user))
                {
                    if(!cur_user->followers->search(cur_user->followers, tmp_user))
                    {
                        double key_index=-1;       //this is the final key.
                        double total_distinct_followers=0;
                        double same_persons=0;
                        same_persons+=cur_user->followers->count_similars(cur_user->followers, tmp_user->followers);
                        total_distinct_followers+=cur_user->followers->count_mem(cur_user->followers);
                        total_distinct_followers+=tmp_user->followers->count_mem(tmp_user->followers);
                        total_distinct_followers-=2*same_persons;
                        key_index=total_distinct_followers/same_persons;
                        start_pq->add_node(start_pq, key_index, tmp_user);
                    }
                }
            }
            tmp_user=tmp_user->next;
        }
    }
    void search_user(users*& start, users*& cur_user)
    {
        string username_in;
        cout<<"enter username: ";
        cin>>username_in;
        users* tmp_user=start;
        while(tmp_user!=NULL)
        {
            if(tmp_user->username==username_in)
            {
                cout<<"found\n";
                cout<<"do you want to follow? 0-no 1-yes\n";
                int check=-1;
                cin>>check;
                if(check)
                    cur_user->follow(cur_user, tmp_user);
                return;
            }
            tmp_user=tmp_user->next;
        }
        cout<<"not found\n";
        return;
    }
    void add_new_post(users*& start)
    {   
        cout<<"enter your post: ";
        string new_post;
        getline(cin, new_post);
        start->posts->add_node(start->posts, new_post);
        cout<<"uploading post is finished\n";
    }
    void edit_posts(users*& start)
    {
        cout<<"your posts: ";
        start->posts->show(start->posts);
        cout<<"choose your post id to edit: ";
        int id_in;
        cin>>id_in;
        cout<<"enter new version of the post: ";
        string post_in;
        getline(cin, post_in);
        start->posts->edit_node(start->posts, id_in, post_in);
    }
    void delete_post(users*& start)
    {
        cout<<"your posts: ";
        start->posts->show(start->posts);
        cout<<"choose your post id to be deleted: ";
        int id_in;
        cin>>id_in;
        start->posts->delete_node(start->posts, id_in);
    }
    void follow(users*& cur_user, users*& tmp_user)
    {
        cur_user->followings->add_node(cur_user->followings, tmp_user);
    }
    void unfollow(users*& cur_user)
    {   
        cout<<"followings: "<<endl;
        cur_user->followings->show(cur_user->followings);
        cout<<"enter account username to be deleted from your followings: ";
        string username_in;
        getline(cin, username_in);
        cur_user->followings->delete_node(cur_user->followings, username_in);
    }
    void remove_follower(users*& cur_user)
    {   
        cout<<"followers: "<<endl;
        cur_user->followers->show(cur_user->followers);
        cout<<"enter account username to be deleted from your followings: ";
        string username_in;
        getline(cin, username_in);
        cur_user->followers->delete_node(cur_user->followers, username_in);
    }

    string get_data_from_file(string location)
    {
        ifstream input_file(location);
        if (!input_file)
        {
            cout << "error! invalid location for text file.\n";
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
int users::total_users = 0;

int main(void)
{

    return 0;
}