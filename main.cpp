#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
class linked_list
{
private:
    T *data;
    string post;
    int id, active;
    linked_list *next, *prev;

public:
    /**/ linked_list(int id_in, T *&data_in) // for users
    {
        data = data_in;
        id = id_in;
        next = NULL;
        prev = NULL;
    }
    /**/ linked_list(int id_in, string data_in) // for posts
    {
        post = data_in;
        id = id_in;
        active = 1;
        next = NULL;
        prev = NULL;
    }
    /**/ void add_node(linked_list *&start_ll, string data_in) // for posts
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
    /**/ void add_node(linked_list *&start_ll, T *&data_in) // for users
    {
        if (start_ll == NULL)
        {
            start_ll = new linked_list(0, data_in);
            cout << " ** added " << data_in->get_username(data_in) << endl;
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
            cout << "added " << data_in->get_username(data_in) << endl;
            return;
        }
    }
    /**/ void show(linked_list *start_ll) // for posts
    {
        while (start_ll != NULL)
        {
            if (start_ll->active != 0)
                cout << "\n\t\t\tid: " << start_ll->id << "\tpost: " << start_ll->post << endl;
            start_ll = start_ll->next;
        }
        cout << endl;
    }
    /**/ void show(linked_list *start_ll, string username) // for users
    {
        while (start_ll != NULL)
        {
            if (start_ll->data != NULL && start_ll->data->check_active(start_ll->data))
                cout << start_ll->data->get_username(start_ll->data) << "\t";
            start_ll = start_ll->next;
        }
        cout << endl;
    }
    /**/ void edit_node(linked_list *&start_ll, int id_in, string post_in) // for posts
    {
        linked_list *tmp_ll = start_ll;
        while (tmp_ll != NULL && tmp_ll->id != id_in)
        {
            tmp_ll = tmp_ll;
        }
        if (tmp_ll == NULL)
        {
            cout << "error! invalid id\n";
            return;
        }
        else
        {
            tmp_ll->post = post_in;
            cout << "done\n";
            return;
        }
    }
    /**/ void delete_node(linked_list *&start_ll, int id_in) // for posts
    {
        linked_list *tmp_ll = start_ll;
        while (tmp_ll != NULL)
        {
            if (tmp_ll->id == id_in)
                break;
            tmp_ll = tmp_ll->next;
        }
        if (tmp_ll == NULL)
        {
            cout << "error! invalid post id\n";
            return;
        }
        else
        {
            tmp_ll->active = 0;
        }
    }
    /**/ void delete_node(linked_list *&start_ll, string username_in) // for users
    {
        linked_list *tmp_ll = start_ll;
        while (tmp_ll != NULL && tmp_ll->data->get_username(tmp_ll->data) != username_in)
        {
            tmp_ll = tmp_ll->next;
        }
        if (tmp_ll == NULL)
        {
            cout << "error! invalid username\n";
            return;
        }
        else
        {
            tmp_ll->data = NULL;
        }
    }
    /**/ T *&get_node(linked_list *&start_ll, string username_in) // for users
    {
        linked_list *tmp_ll = start_ll;
        while (tmp_ll != NULL && tmp_ll->data->get_username(tmp_ll->data) != username_in)
            tmp_ll = tmp_ll->next;
        if (tmp_ll == NULL)
        {
            cout << "error! no such user\n";
            T *output = NULL;
            return output;
        }
        return tmp_ll->data;
    }
    /**/ int sim_exam(linked_list* start1, linked_list* start2)
    {
        if(start1->count_mem(start1)==0)
            {cout<<"it is NULL\n";
            return 0;}
        if(start2->count_mem(start2)==0)
            {cout<<"it is NULL\n";
            return 0;}

        int counter=0;
        linked_list<T>* tmp_user1=start1;
        linked_list<T>* tmp_user2=start2;
        for(int i=0; i<start1->count_mem(start1); i++)
        {
            for(int j=0; j<start2->count_mem(start2); j++)
            {
                if(tmp_user1->data->get_username(tmp_user1->data)==tmp_user2->data->get_username(tmp_user2->data))
                    counter++;
                tmp_user2=tmp_user2->next;
            }
            tmp_user1=tmp_user1->next;
            tmp_user2=start2;
        }
        return counter;
    }
    /**/ int count_mem(linked_list *start_ll)
    {
        int counter = 0;
        while (start_ll != NULL)
        {
            counter++;
            start_ll = start_ll->next;
        }
        return counter;
    }
    /**/ int search(linked_list *start_ll, string username_in)
    {
        while (start_ll != NULL && start_ll->data->get_username(start_ll->data) != username_in)
        {
            start_ll = start_ll->next;
        }
        if (start_ll == NULL)
            return 0;
        else
            return 1;
    }
};

template <typename T>
class pq_objects
{
public:
    pq_objects()
    {
    }
    double key;
    T *value;
};

template <typename T>
class pq
{
public:
    pq_objects<T> *value;
    pq *next, *prev;

public:
    pq(pq_objects<T> *&value_in)
    {
        value = value_in;
        next = NULL;
        prev = NULL;
    }
    void add_node(pq *&start_pq, double key_in, T *value_in)
    {
        pq_objects<T> *tmp_ob = new pq_objects<T>;

        tmp_ob->key = key_in;
        tmp_ob->value = value_in;
        // data
        if (start_pq == NULL)
        {
            start_pq = new pq(tmp_ob);
            return;
        }
        else
        {
            pq *tmp_pq = start_pq;
            if(tmp_ob->key > tmp_pq->value->key)
            {
                tmp_pq->prev=new pq(tmp_ob);
                tmp_pq->prev->next=tmp_pq;
                start_pq=tmp_pq->prev;
                return;
            }
            while ((tmp_pq->next != NULL) && (tmp_pq->value->key >= tmp_ob->key))
            {
                cout<<"************************************\n";
                tmp_pq = tmp_pq->next;
            }

            if (tmp_pq->next == NULL)
            {
                tmp_pq->next = new pq(tmp_ob);
                tmp_pq->next->prev = tmp_pq;
                return;
            }
            else
            {
                pq *tmp_pq2 = new pq(tmp_ob);
                tmp_pq2->prev = tmp_pq;
                tmp_pq2->next = tmp_pq->next;
                tmp_pq->next = tmp_pq2;
                tmp_pq2->next->prev = tmp_pq2;
                return;
            }
        }
    }
    T *&get_node(pq *&start)
    {
        if (start == NULL)
        {
            T *output = NULL;
            return output;
        }
        pq<T> *tmp_pq = start;
        start = start->next;
        if (start != NULL)
        {
            start->prev = NULL;
        }
        return tmp_pq->value->value;
    }
};

template <typename T>
class graph // this ADT is for storing relations of users.
{
private:
    linked_list<T> *start_ll;

public:
    /**/ graph()
    {
        start_ll = NULL;
    }
    /**/ void add_node(graph *&start_g, T *&user_in)
    {
        if (start_g == NULL)
        {
            start_g = new graph();
        }
        start_g->start_ll->add_node(start_g->start_ll, user_in);
    }
    /**/ void show(graph *&start_g)
    {
        if (start_g == NULL)
        {
            return;
        }
        start_g->start_ll->show(start_g->start_ll, "test text");
    }
    /**/ void delete_node(graph *&start_g, string username_in)
    {
        if (start_g == NULL)
        {
            cout << "error! empty graph.";
            return;
        }
        start_g->start_ll->delete_node(start_g->start_ll, username_in);
    }
    int search(graph *&start_g, string username_in)
    {
        if (start_g == NULL)
        {
            return 0;
        }
        return start_g->start_ll->search(start_g->start_ll, username_in);
    }
    int count_mem(graph *&start_g)
    {
        if (start_g == NULL)
            return 0;
        return start_g->start_ll->count_mem(start_g->start_ll);
    }
    int count_similars(graph *&start_g1, graph *&start_g2)
    {
        int counter=0;
        if(start_g1==NULL || start_g2==NULL)
            return 0;
        counter=start_g1->start_ll->sim_exam(start_g1->start_ll, start_g2->start_ll);
        return counter;
    }
    T *&get_node(graph *&start_g, string username_in)
    {
        if (start_g == NULL)
        {
            T *output = NULL;
            return output;
        }
        return start_g->start_ll->get_node(start_g->start_ll, username_in);
    }
};

class users
{
private:
    static int total_users;

    string username;
    int password;
    int active;

    linked_list<string> *posts;
    graph<users> *followings;
    graph<users> *followers;

    users *next, *prev;

public:
    /**/ users(string username_in, int password_in)
    {
        password = password_in;
        username = username_in;
        posts = NULL;
        followings = NULL;
        followers = NULL;
        next = NULL;
        prev = NULL;
        active = 1;
    }
    /**/ void sign_up(users *&start)
    {
        string username_in;
        int password_in;
        cout << "\tenter new username: ";
        cin >> username_in;
        cout << "\tenter new passwod: ";
        cin >> password_in;

        if (start == NULL)
        {
            start = new users(username_in, password_in);
            cout << "\taccount created succesfully.\n\n";
            total_users++;
            return;
        }
        else
        {
            users *tmp_users = start;
            while (tmp_users->next != NULL)
            {
                if (tmp_users->username == username_in)
                {
                    cout << "\terror! invalid username.\n";
                    return;
                }
                tmp_users = tmp_users->next;
            }
            if (tmp_users->username == username_in)
            {
                cout << "\terror! invalid username.\n";
                return;
            }
            tmp_users->next = new users(username_in, password_in);
            tmp_users->next->prev = tmp_users;
            cout << "\taccount created succesfuly\n";
            total_users++;
            return;
        }
    }
    /**/ void sign_up(users *&start, string username_in, int password_in)
    {
        if (start == NULL)
        {
            start = new users(username_in, password_in);
            total_users++;
            return;
        }
        else
        {
            users *tmp_user = start;
            while (tmp_user->next != NULL)
                tmp_user = tmp_user->next;
            tmp_user->next = new users(username_in, password_in);
            total_users++;
        }
    }
    /**/ string get_username(users *&start)
    {
        return start->username;
    }
    /**/ int check_active(users *&cur_user)
    {
        return cur_user->active;
    }
    /**/ void main_operations(users *&start)
    {
        cout << "wellcome to your social network!\n";
        cout << "number of total users: " << total_users << endl
             << endl;
        int operation = -1;
        while (operation != 0)
        {
            cout << "choose your operation: " << endl;
            cout << "1- sign up\n";
            cout << "2- sign in\n";
            cout << "0- exit\n";
            cin >> operation;
            if (operation == 0)
            {
                cout << "goodbye!\n";
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
                cout << "error! invalid input.\n";
            }
        }

        string username_in;
        int password_in;
        cout << "** log in **" << endl;

        cout << "\tenter username: ";
        cin >> username_in;
        cout << "\tenter password: ";
        cin >> password_in;

        users *cur_user = start;
        while (cur_user != NULL)
        {
            if (cur_user->username == username_in && cur_user->password == password_in)
            {
                if (cur_user->active == 0)
                {
                    cout << "error! deleted account\n";
                    return;
                }
                cout << "\t   loged in...\n";
                cout << "welcome " << username_in << endl
                     << endl;
                break;
            }
            cur_user = cur_user->next;
        }
        if (cur_user == NULL)
        {
            cout << "\t  error! invalid username or password.\n";
            return;
        }

        while (operation != 0)
        {
            cout << "choose your operation:\n";
            cout << "1- change username or password\n";
            cout << "2- delete_account\n";
            cout << "3- watch profile\n";
            cout << "4- suggest friend\n";
            cout << "5- search user\n";
            cout << "6- add new post\n";
            cout << "7- edit posts\n";
            cout << "8- delete post\n";
            cout << "9- unfollow\n";
            cout << "10-remove follower\n";
            cout << "0- log out\n";

            cin >> operation;
            if (operation == 1)
            {
                cur_user->change_username_or_password(cur_user);
            }
            else if (operation == 2)
            {
                cur_user->delete_account(start, cur_user);
                return;
            }
            else if (operation == 3)
            {
                cur_user->watch_profile(cur_user);
            }
            else if (operation == 4)
            {
                cur_user->suggest_others_users(start, cur_user);
            }
            else if (operation == 5)
            {
                start->search_user(start, cur_user);
            }
            else if (operation == 6)
            {
                cur_user->add_new_post(cur_user);
            }
            else if (operation == 7)
            {
                cur_user->edit_posts(cur_user);
            }
            else if (operation == 8)
            {
                cur_user->delete_post(cur_user);
            }
            else if (operation == 9)
            {
                cur_user->unfollow(cur_user);
            }
            else if (operation == 10)
            {
                cur_user->remove_follower(cur_user);
            }
            else if (operation == 0)
            {
                cout << "goodby!\n";
                return;
            }
            else
            {
                cout << "error! invalid operation.\n";
            }
            cout << "enter any key to continue: ";
            char tmp_int;
            cin >> tmp_int;
        }
    }
    /**/ void change_username_or_password(users *&start)
    {
        string username_in;
        int password_in;
        cout << "\tchoose operation: " << endl;
        cout << "\t1- change password\n";
        cout << "\t2- change username\n";
        cout << "\t3- change both\n";
        int operation = -1;
        cin >> operation;
        if (operation == 1)
        {
            cout << "\t\tenter password: ";
            cin >> password_in;
            start->password = password_in;
            cout << "\t\t  changed\n";
        }
        else if (operation == 2)
        {
            cout << "\t\tenter username: ";
            cin >> username_in;
            start->username = username_in;
            cout << "\t\t  changed\n";
        }
        else if (operation == 3)
        {
            cout << "\t\tenter username: ";
            cin >> username_in;
            start->username = username_in;
            cout << "\t\tenter password: ";
            cin >> password_in;
            start->password = password_in;
            cout << "\t\t  changed\n";
        }
        else
        {
            cout << "\t  error! invalid operation\n";
            return;
        }
    }
    /**/ void delete_account(users *&start_user, users *&cur_user)
    {
        cur_user->active = 0;
        total_users--;
        cout << "deleted\n";
    }
    /**/ void watch_profile(users *&cur_user) // yours or your friend
    {
        int operation = -1;
        cout << "\tchoose operation: \n";
        cout << "\t1- watch your profile\n";
        cout << "\t2- watch your following profile\n";
        cin >> operation;
        if (operation == 1)
        {
            cout << "\t\tusername: " << cur_user->username << endl;

            cout << "\t\tyour posts: \n\t\t";
            cur_user->posts->show(cur_user->posts);

            cout << endl;
            cout << "\t\tyour followers:\n\t\t";
            cur_user->followers->show(cur_user->followers);

            cout << endl;
            cout << "\t\tyour followings: \n\t\t";
            cur_user->followings->show(cur_user->followings);
            cout << endl
                 << endl;
            return;
        }
        else if (operation == 2)
        {
            cout << "\tyour followings:\n\t";
            cur_user->followings->show(cur_user->followings);
            cout << "\tchoose any username to watch profile: \n";
            string username_in;
            cin >> username_in;
            users *tmp_user = cur_user->followings->get_node(cur_user->followings, username_in);
            cout << "\tusername: " << tmp_user->username << endl;
            cout << "\tpost: " << endl;
            tmp_user->posts->show(tmp_user->posts);
            cout << "\tfollowers: \n\t";
            tmp_user->followers->show(tmp_user->followers);
            cout << "\tfollowings: \n\t";
            tmp_user->followings->show(tmp_user->followings);
            cout << endl
                 << endl;
        }
        else
        {
            cout << "error! invalid operation\n\n";
            return;
        }
    }
    /**/ void suggest_others_users(users *&start, users *&cur_user)
    {
        users *tmp_user = start;
        pq<users> *start_pq = NULL;
        while (tmp_user != NULL)
        {
            if (tmp_user->active)
            {
                if (tmp_user != cur_user)
                {
                    if (!cur_user->followings->search(cur_user->followings, tmp_user->username))
                    {
                        if (!cur_user->followers->search(cur_user->followers, tmp_user->username))
                        {
                            double key_index = -1; // this is the final key.
                            double total_followings = 0;
                            double same_persons = 0;
                            same_persons += cur_user->followings->count_similars(cur_user->followings, tmp_user->followings);
                            total_followings += cur_user->followings->count_mem(cur_user->followings);
                            total_followings += tmp_user->followings->count_mem(tmp_user->followings);
                            key_index = same_persons /total_followings ;
                            start_pq->add_node(start_pq, key_index, tmp_user);
                        }
                    }
                }
            }
            tmp_user = tmp_user->next;
        }

        for (int i = 0; i < 4; i++)
        {
            users *tmp_user3 = start_pq->get_node(start_pq);
            cout << "suggested user " << i << ":" << tmp_user3->username << endl;
            cout << "do you want to follow? " << "0-no  1-yes ";
            int operation = -1;
            cin >> operation;
            if (operation == 0)
                continue;
            else if (operation == 1)
                cur_user->follow(cur_user, tmp_user3);
        }
    }
    /**/ void search_user(users *&start, users *&cur_user)
    {
        string username_in;
        cout << "enter username: ";
        cin >> username_in;
        if (cur_user->followings->search(cur_user->followings, username_in))
        {
            cout << "you are following " << username_in << endl;
            return;
        }
        users *tmp_user = start;
        while (tmp_user != NULL)
        {
            if (tmp_user->username == username_in)
            {
                cout << "found\n";
                cout << "do you want to follow? 0-no 1-yes\n";
                int check = -1;
                cin >> check;
                if (check == 1)
                    cur_user->follow(cur_user, tmp_user);
                return;
            }
            tmp_user = tmp_user->next;
        }
        cout << "not found\n";
        return;
    }
    /**/ void add_new_post(users *&start)
    {
        cout << "enter your post: ";
        string new_post;
        cin.ignore();
        getline(cin, new_post);
        start->posts->add_node(start->posts, new_post);
        cout << "uploading post is finished\n";
    }
    /**/ void edit_posts(users *&start)
    {
        cout << "your posts: ";
        start->posts->show(start->posts);
        cout << "choose your post id to edit: ";
        int id_in;
        cin >> id_in;
        cout << "enter new version of the post: ";
        string post_in;
        cin.ignore();
        getline(cin, post_in);
        start->posts->edit_node(start->posts, id_in, post_in);
    }
    /**/ void delete_post(users *&start)
    {
        cout << "your posts: ";
        start->posts->show(start->posts);
        cout << "choose your post id to be deleted: ";
        int id_in;
        cin >> id_in;
        start->posts->delete_node(start->posts, id_in);
    }
    /**/ void follow(users *&cur_user, users *&tmp_user)
    {
        cur_user->followings->add_node(cur_user->followings, tmp_user);
        tmp_user->followers->add_node(tmp_user->followers, cur_user);
    }
    /**/ void follow(users *&start, string username1, string username2)
    {
        users *tmp_start = start;
        users *tmp_user1 = NULL, *tmp_user2 = NULL;
        while (tmp_start != NULL)
        {
            if (tmp_start->username == username1)
            {
                tmp_user1 = tmp_start;
            }
            else if (tmp_start->username == username2)
            {
                tmp_user2 = tmp_start;
            }
            if (tmp_user1 != NULL && tmp_user2 != NULL)
                break;
            tmp_start = tmp_start->next;
        }
        follow(tmp_user1, tmp_user2);
    }
    /**/ void unfollow(users *&cur_user, string username_in)
    {
        cur_user->followings->delete_node(cur_user->followings, username_in);
    }
    /**/ void unfollow(users *&cur_user)
    {
        cout << "followings: " << endl;
        cur_user->followings->show(cur_user->followings);
        cout << "enter account username to be deleted from your followings: ";
        string username_in;
        cin.ignore();
        getline(cin, username_in);
        users *tmp_user = cur_user->followings->get_node(cur_user->followings, username_in);
        if (tmp_user == NULL)
        {
            cout << "invalid username\n";
            return;
        }
        tmp_user->followers->delete_node(tmp_user->followings, cur_user->username);
        cur_user->followings->delete_node(cur_user->followings, username_in);
    }
    /**/ void remove_follower(users *&cur_user, string username_in)
    {
        cur_user->followers->delete_node(cur_user->followers, username_in);
    }
    /**/ void remove_follower(users *&cur_user)
    {
        cout << "followers: " << endl;
        cur_user->followers->show(cur_user->followers);
        cout << "enter account username to be deleted from your followings: ";
        string username_in;
        cin.ignore();
        getline(cin, username_in);
        users *tmp_user = cur_user->followers->get_node(cur_user->followers, username_in);
        if (tmp_user == NULL)
        {
            cout << "error! invalid username\n";
            return;
        }
        tmp_user->followings->delete_node(tmp_user->followings, cur_user->username);
        cur_user->followers->delete_node(cur_user->followers, username_in);
    }
};
int users::total_users = 0;

//test

int main(void)
{
    users *start = NULL;
    // create 10 fake accounts
    string username_in;
    int password_in;

    username_in = "amir";
    password_in = 1;
    start->sign_up(start, username_in, password_in);
    username_in = "hosein";
    password_in = 2;
    start->sign_up(start, username_in, password_in);
    username_in = "pedram";
    password_in = 3;
    start->sign_up(start, username_in, password_in);
    username_in = "parham";
    password_in = 4;
    start->sign_up(start, username_in, password_in);
    username_in = "eliza";
    password_in = 5;
    start->sign_up(start, username_in, password_in);
    username_in = "sadaf";
    password_in = 6;
    start->sign_up(start, username_in, password_in);
    username_in = "mojtaba";
    password_in = 7;
    start->sign_up(start, username_in, password_in);
    username_in = "shima";
    password_in = 8;
    start->sign_up(start, username_in, password_in);
    username_in = "mahyar";
    password_in = 9;
    start->sign_up(start, username_in, password_in);
    username_in = "firooze";
    password_in = 10;
    start->sign_up(start, username_in, password_in);

    // follow each other

    start->follow(start, "pedram", "hosein");  // 1
    start->follow(start, "amir", "hosein");    // 2
    start->follow(start, "hosein", "amir");    // 3
    start->follow(start, "amir", "parham");    // 4
    start->follow(start, "parham", "eliza");   // 5
    start->follow(start, "eliza", "sadaf");    // 6
    start->follow(start, "parham", "mahyar");  // 7
    start->follow(start, "parham", "mojtaba"); // 8
    start->follow(start, "eliza", "mojtaba");  // 9
    start->follow(start, "mojtaba", "mahyar"); // 10
    start->follow(start, "mahyar", "firooze"); // 11
    start->follow(start, "mojtaba", "shima");  // 12
    start->follow(start, "shima", "sadaf");    // 13
    start->follow(start, "firooze", "shima");  // 14
    start->follow(start, "shima", "firooze");  // 15
    start->follow(start, "shima", "eliza");    // 16
    start->follow(start, "amir", "eliza");     // 17
    start->follow(start, "amir", "sadaf");     // 18

    int operation = 1;
    cout << "this is a social network project.\n";
    cout << "do you want to continue the app? 1-continue  0-close  ";
    cin >> operation;

    while (operation != 0)
    {
        cout << endl;
        start->main_operations(start);
        cout << "do you want to continue the app? 1-continue  0-close  ";
        cin >> operation;
    }

    return 0;
}