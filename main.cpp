#include <iostream>
#include <fstream>
#include <string>
using namespace std;



template <typename T>
class linked_list
{
private:
    T* data;
    T post;
    int id;
    linked_list *next, *prev;

public:
    linked_list(int id_in, T* data_in) //for users
    {
        data = data_in;
        id = id_in;
        next = NULL;
        prev = NULL;
    }
    linked_list(int id_in, string data_in) //for posts
    {
        data=data_in;
        id=id_in;
        next=NULL;
        prev=NULL;
    }
    void add_node(linked_list *&start_ll, string data_in) //for posts
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
    void add_node(linked_list *&start_ll, T* data_in) //for users
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
    void show(linked_list* start_ll) //for posts
    {
        while(start_ll!=NULL)
        {
            cout<<"id: "<<start_ll->id<<"\tpost: "<<start_ll->post<<endl;
            start_ll=start_ll->next;
        }
        cout<<endl;
    }
    void show(linked_list* start_ll, string username) //for users
    {}
    void edit_node(linked_list*& start_ll, int id_in, string post_in) //for posts
    {
        linked_list* tmp_ll=start_ll;
        while(tmp_ll!=NULL && tmp_ll->id!=id_in)
        {
            tmp_ll=tmp_ll;
        }
        if(tmp_ll==NULL)
        {
            cout<<"error! invalid id\n";
            return;
        }
        else
        {
            tmp_ll->post=post_in;
            cout<<"done\n";
            return;
        }
    }
    void delete_node(linked_list*& start_ll, int id_in) //for posts
    {
        linked_list* tmp_ll=start_ll;
        while(tmp_ll!=NULL && tmp_ll->id!=id_in)
        {
            tmp_ll=tmp_ll->next;
        }
        if(tmp_ll==NULL)
        {
            cout<<"error! invalid id\n";
            return;
        }
        else 
        {
            if(tmp_ll->prev==NULL)
            {
                start_ll=tmp_ll->next;
                start_ll->prev=NULL;
                delete tmp_ll;
            }
            else if(tmp_ll->next==NULL)
            {
                tmp_ll->prev->next=NULL;
                delete tmp_ll;
            }
            else 
            {
                tmp_ll->prev->next=tmp_ll->next;
                tmp_ll->next->prev=tmp_ll->prev;
            }
        }
    }
    void delete_node(linked_list*& start_ll, string username_in) //for users
    {
        linked_list* tmp_ll=start_ll;
        while(tmp_ll!=NULL && tmp_ll->data->get_username(tmp_ll->data)!=username_in)
        {
            tmp_ll=tmp_ll->next;
        }
        if(tmp_ll==NULL)
        {
            cout<<"error! invalid username\n";
            return;
        }
        else 
        {
            if(tmp_ll->prev==NULL)
            {
                start_ll=tmp_ll->next;
                start_ll->prev=NULL;
                delete tmp_ll;
            }
            else if(tmp_ll->next==NULL)
            {
                tmp_ll->prev->next=NULL;
                delete tmp_ll;
            }
            else 
            {
                tmp_ll->prev->next=tmp_ll->next;
                tmp_ll->next->prev=tmp_ll->prev;
            }
        }
    }
    T* get_node(linked_list*& start_ll, string username_in) //for users
    {
        linked_list* tmp_ll=start_ll;
        while(tmp_ll!=NULL  && tmp_ll->data->get_username(tmp_ll->data)!=username_in)
            tmp_ll=tmp_ll->next;
        if(tmp_ll==NULL)
        {
            cout<<"error! no such user\n";
            return NULL;
        }
        return tmp_ll->data;
    }
    T* get_order_node(linked_list*& start_ll, int counter)
    {
        linked_list* tmp_ll=start_ll;
        for(int i=0; i<counter; i++)    
            start_ll=start_ll->next;
        return start_ll->data;
    }
    int count_mem(linked_list* start_ll)
    {
        int counter=0; 
        while(start_ll!=NULL)
        {
            counter++;
            start_ll=start_ll->next;
        }
        return counter;
    }
    int search(linked_list* start_ll, string username_in)
    {
        while(start_ll!=NULL && start_ll->data->username!=username_in)
        {
            start_ll=start_ll->next;
        }
        if(start_ll==NULL)
            return 0;
        else 
            return 1;
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
    pq* next, *prev;
public:
    pq(pq_objects*& value_in)
    {
        value=value_in;
        next=NULL;
        prev=NULL; 
    }
    void add_node(pq*& start_pq, double key_in, T* value_in)
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
    T* get_node(pq*& start)
    {
        if(start==NULL)
            return NULL;
        pq* tmp_pq=start;
        start=start->next;
        if(start!=NULL)
        {
            start->prev=NULL;
        }
        return tmp_pq->value;
    }
};

template <typename T>
class graph // this ADT is for storing relations of users.
{
private:
    linked_list<T> *start_ll;

public:
    graph()
    {
        start_ll=NULL;
    }
    void add_node(graph*& start_g, T*&start_ll_in)
    {
        start_g->start_ll->add_node(start_g->start_ll, start_ll_in);
    }
    void show(graph*& start_g)
    {
        start_g->start_ll->show(start_g->start_ll);
    }
    void delete_node(graph*& start_g, string username_in)
    {
        start_g->start_ll->delete_node(start_g->start_ll, username_in);
    }
    int search(graph*& start_g, string username_in)
    {
        return start_g->start_ll->search(start_g->start_ll, username_in);
    }
    int count_mem(graph*& start_g)
    {
        return start_g->start_ll->count_mem(start_g->start_ll);
    }
    int count_similars(graph*& start_g1, graph*& start_g2)
    {
        int mem_count_g1=start_g1->count_mem(start_g1);
        int mem_count_g2=start_g2->count_mem(start_g2);
        int sim_count=0;
        for(int i=0; i<mem_count_g1; i++)
        {
            for(int j=0; j<mem_count_g2; j++)
            {
                T* tmp_user=start_g2->start_ll->get_order_node(start_g2->start_ll, j);
                string tmp_username=tmp_user->get_username(tmp_user);
                if(start_g1->search(start_g1, tmp_username))
                    sim_count++;
            }
        }
        return sim_count;
    }
    T* get_node(graph*& start_g, string username_in)
    {
        return start_g->start_ll->get_node(start_g->start_ll, username_in);
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
    string get_username(users*& start)
    {
        return start->username;
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
                {cur_user->suggest_others_users(start, cur_user);}
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
                if(!cur_user->followings->search(cur_user->followings, tmp_user->username))
                {
                    if(!cur_user->followers->search(cur_user->followers, tmp_user->username))
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

        for(int i=0; i<6; i++)
        {
            users* tmp_user3=start_pq->get_node(start_pq);
            cout<<"suggested user "<<i<<":"<<tmp_user3->username<<endl;
            cout<<"do you want to follow? "<<"0-no  1-yes ";
            int operation=-1;
            cin>>operation;
            if(operation==0)
                continue;
            else if(operation==1)
                cur_user->follow(cur_user, tmp_user3);
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
    void unfollow(users*& cur_user, string username_in)
    {
        cur_user->followings->delete_node(cur_user->followings, username_in);
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
    void remove_follower(users*& cur_user, string username_in)
    {
        cur_user->followers->delete_node(cur_user->followers, username_in);
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


    //optional for testing.
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