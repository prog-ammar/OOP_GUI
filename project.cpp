#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<time.h>
#include<sstream>
#include<string>
#include<openssl/sha.h>
#include "project.h"

using namespace std;

#pragma warning(disable : 4996).

int User::userCount = 0;

string Student::credentials_file = "student-cre.txt";
string Faculty::credentials_file = "faculty-cre.txt";
string Admin::credentials_file = "admin-cre.txt";

string Student::salt_file = "student-salt.txt";
string Faculty::salt_file = "faculty-salt.txt";
string Admin::salt_file = "admin-salt.txt";

User::User(string name = "", int ID = 0, string login_status = "", string password = "",string user_type="")
{
    this->name = name;
    this->ID = ID;
    this->login_status = login_status;
    this->password = password;
    this->user_type = user_type;
    userCount++;
}

void User::set_Name(string name)
{
    this->name = name;
}

void User::set_ID(int ID)
{
    this->ID = ID;
}

void User::set_login(string login_status)
{
    this->login_status = login_status;
}

void User::set_user_type(string user_type)
{
    this->user_type = user_type;
}

string User::get_Name() const
{
    return name;
}

int User::get_ID() const
{
    return ID;
}

string User::get_status() const
{
    return login_status;
}

string User::get_user_type() const
{
    return user_type;
}

template<typename anyclass>
void User::add_User(string id, string username, string password)
{
    ifstream file(anyclass::get_file());
    string line;
    string u_id;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, u_id, ',');
        if (u_id == id)
        {
            cout << "Another User With Same ID already exists\n";
            return;
        }
    }
    file.close();
    fstream file1(anyclass::get_file(), ios::app);
    file1 << id << ',' << password << '\n';
    file1.close();
    cout << "\n" << username << "Is Added Successfully\n";
}

User::~User()
{
    userCount--;
}


template<typename a_class>
string Hash_Manager<a_class>::sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

template<typename a_class>
string Hash_Manager<a_class>::salting()
{
    string salt;
    srand(time(0));
    for (int i = 0;i < 16;i++)
    {
        salt += char((rand() % 26) + 97);//generate random characters 
    }
    return salt;
}

template<typename a_class>
bool Hash_Manager<a_class>::store_User(string id, string password)
{
    ifstream file(a_class::get_file());
    ifstream file1(a_class::get_salt_file());
    string wholeline;
    string salt;
    string hashed_id;
    string hashed_pwd;
    while (getline(file, wholeline) && getline(file1, salt))
    {
        stringstream ss(wholeline);
        getline(ss, hashed_id, ',');
        getline(ss, hashed_pwd, ',');
        if (hashed_id == sha256(id + salt))
        {
            return false;
        }
    }
    
    file.close();
    file1.close();

    string salt_ = salting();

    fstream file_n(a_class::get_file(), ios::app);
    file_n << sha256(id + salt_) << ',' << sha256(password + salt_) << '\n';
    file_n.close();

    file_n.open(a_class::get_salt_file(), ios::app);
    file_n << salt_ << '\n';
    file_n.close();

    return true;
}


template<typename a_class>
bool Hash_Manager<a_class>::validate_user(string id, string pwd)
{
    ifstream file(a_class::get_file());
    ifstream file1(a_class::get_salt_file());
    string salt;
    string wholeline;
    string user_hash;
    string pass_hash;
    while (getline(file, wholeline) && getline(file1, salt))
    {
        stringstream ss(wholeline);
        getline(ss, user_hash, ',');
        getline(ss, pass_hash, ',');

        if (sha256(id + salt) == user_hash && sha256(pwd + salt) == pass_hash)
        {
            return true;
        }
    }
    file.close();
    file1.close();
    return false;
}

template<typename a_class>
bool Hash_Manager<a_class>::validate_id(string id)
{
    ifstream file(a_class::get_file());
    ifstream file1(a_class::get_salt_file());
    string hashed_id;
    string hashed_pwd;
    string wholeline;
    string salt;
    while (getline(file, wholeline) && getline(file1, salt))
    {
        stringstream ss(wholeline);
        getline(ss, hashed_id, ',');
        getline(ss, hashed_pwd, ',');
        if (hashed_id == sha256(id + salt))
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}



template<typename anyclass>
bool validate_id(string id)
{
    ifstream file(anyclass::get_file());
    ifstream file1(anyclass::get_salt_file());
    string hashed_id;
    string hashed_pwd;
    string wholeline;
    string salt;
    while (getline(file, wholeline) && getline(file,salt))
    {
        stringstream ss(wholeline);
        getline(ss, hashed_id, ',');
        getline(ss, hashed_pwd, ',');
        if (hashed_id == id)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

template<typename anyclass>
bool User::validate_user(string id,string pwd)
{
    ifstream file(anyclass::get_file());
    string u_id;
    string password;
    string wholeline;
    while (getline(file, wholeline))
    {
        stringstream ss(wholeline);
        getline(ss, u_id, ',');
        getline(ss, password, ',');
        if (u_id == id && password == pwd)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

string User::get_username_by_id(string id)
{
    ifstream file("usernames.txt");
    string wholeline;
    string username;
    string u_id;
    while (getline(file, wholeline))
    {
        stringstream ss(wholeline);
        getline(ss, u_id, ',');
        getline(ss, username, ',');
        if (u_id == id)
        {
            file.close();
            return username;
        }
    }
    file.close();
    return "N/A";
}


Student::Student(string name = "", int ID = 0, string login_status = "", string password = "") :User(name, ID, login_status, password,"student") {}
Faculty::Faculty(string name = "", int ID = 0, string login_status = "", string password = "") :User(name, ID, login_status, password,"faculty") {}
Admin::Admin(string name = "", int ID = 0, string login_status = "", string password = "") :User(name, ID, login_status, password,"admin") {}

string Student::get_file() { return credentials_file; }
string Faculty::get_file() { return credentials_file; }
string Admin::get_file() { return credentials_file; }

string Student::get_salt_file() { return salt_file; }
string Faculty::get_salt_file() { return salt_file; }
string Admin::get_salt_file() { return salt_file; }


Zone::Zone(string zone_type, string security_level)
{
    this->zone_type = zone_type;
    this->security_level = security_level;
    current = 0;
}

string Zone::get_level() { return security_level; }
string Zone::get_type() { return zone_type; }

void operator+=(Zone& zone, User& user)
{
    if (zone.current == 0)
    {
        zone.users = new User(user);
        zone.current++;
    }
    else
    {
        User* temp = new User[zone.current];
        for (int i = 0;i < zone.current;i++)
        {
            temp[i] = zone.users[i];
        }
        delete[] zone.users;
        zone.users = new User[zone.current + 1];
        for (int i = 0;i < zone.current;i++)
        {
            zone.users[i] = temp[i];
        }
        zone.users[zone.current] = user;
        delete[] temp;
        zone.current++;
    }
}

bool operator==(const Zone& zone1, const Zone& zone2)
{
    return zone1.zone_type == zone2.zone_type;
}


AccessLogger::AccessLogger()
{
    this->current = 0;
    ifstream file("log-events.txt");
    string wholeline;
    string u_name;
    string id;
    string act;
    string time1;
    string date1;
    while (getline(file, wholeline))
    {
        stringstream ss(wholeline);
        getline(ss, u_name, ',');
        getline(ss, id, ',');
        getline(ss, act, ',');
        getline(ss, time1, ',');
        getline(ss, date1, ',');
        file_users.push_back(u_name);
        file_ids.push_back(id);
        file_actions.push_back(act);
        times.push_back(time1);
        dates.push_back(date1);
    }
    file.close();
}

template<typename ran_class>
void AccessLogger::addLog(ran_class& r, string action)
{
    if (current == 0)
    {
        users = new User(r);
        current++;
    }
    else
    {
        User* temp = new User[current];
        for (int i = 0;i < current;i++)
        {
            temp[i] = users[i];
        }
        users = new User[current + 1];
        for (int i = 0;i < current;i++)
        {
            users[i] = temp[i];
        }
        delete[] temp;
        users[current] = r;
        current++;
    }
    usernames.push_back(r.get_Name());
    ids.push_back(to_string(r.get_ID()));
    actions.push_back(action);
    time_t now = time(NULL);
    tm cur_time;
    localtime_s(&cur_time, &now);
    log_time.push_back(cur_time.tm_hour);
    log_time.push_back(cur_time.tm_min);
    log_time.push_back(cur_time.tm_sec);
    log_date.push_back(cur_time.tm_mday);
    log_date.push_back(cur_time.tm_mon + 1);
    log_date.push_back(cur_time.tm_year - 100);
}

AccessLogger::~AccessLogger()
{
    fstream file("log-events.txt", ios::app);
    for (int i = 0;i < usernames.size();i++)
    {
        file << usernames[i] << ',' << ids[i] << ',' << actions[i] << ',' << log_time[(i) * 3] << ':' << log_time[(i * 3) + 1] << ':' << log_time[(i * 3) + 2] << ',' << log_date[i * 3] << '/' << log_date[(i * 3) + 1] << '/' << log_date[(i * 3) + 2] << '\n';
    }
    file.close();
    delete[] users;
}

void AccessLogger::display_Session_logs()
{
    cout << "\nSession Logs : \n";
    for (int i = 0;i < current;i++)
    {
        cout << "\n" << i + 1 << ".Name : " << usernames[i] << "\nID : " << ids[i] << "\nAction : " << actions[i] << "\nTime : " << log_time[i * 3] << ":" << log_time[(i * 3) + 1] << ":" << log_time[(i * 3) + 2] << "\nDate : " << log_date[i * 3] << "/" << log_date[(i * 3) + 1] << "/" << log_date[(i * 3) + 2] << "\n";
    }
}



bool AccessControl::grantAccess(Zone& z, const User& u)
{
    if (z.get_level() == "Low" && (u.get_user_type() == "student" || u.get_user_type() == "faculty" || u.get_user_type() == "admin"))
    {
        return true;
    }
    else if (z.get_level() == "Medium" && (u.get_user_type() == "faculty" || u.get_user_type() == "admin"))
    {
        return true;
    }
    else if (z.get_level()=="High" && (u.get_user_type() == "admin"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AccessControl::logAccess(Zone& z,const User& u)
{
    ac.addLog(u, "Accessed " + z.get_type());
}
