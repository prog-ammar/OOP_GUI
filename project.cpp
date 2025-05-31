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

string Student::credentials_file = "files/student-cre.txt";
string Faculty::credentials_file = "files/faculty-cre.txt";
string Admin::credentials_file = "files/admin-cre.txt";

string Student::salt_file = "files/student-salt.txt";
string Faculty::salt_file = "files/faculty-salt.txt";
string Admin::salt_file = "files/admin-salt.txt";

User::User(string name = "", int ID = 0, string login_status = "", string password = "", string user_type = "")
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
    return login_status;;
}

string User::get_user_type() const
{
    return user_type;
}

User::~User()
{
    userCount--;
}


string Hash_Manager::sha256(const string str)
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

string Hash_Manager::salting()
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
bool Hash_Manager::store_User(string id, string username, string password)
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
            file.close();
            file1.close();
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

    file_n.open("files/usernames.txt", ios::app);
    file_n << id << ',' << username << '\n';
    file_n.close();

    return true;
}


template<typename a_class>
bool Hash_Manager::validate_user(string id, string pwd)
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
            file.close();
            file1.close();
            return true;
        }
    }
    file.close();
    file1.close();
    return false;
}

template<typename a_class>
bool Hash_Manager::validate_id(string id)
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



string User::get_username_by_id(string id)
{
    ifstream file("files/usernames.txt");
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


Student::Student(string name = "", int ID = 0, string login_status = "", string password = "") :User(name, ID, login_status, password, "student") {}
Faculty::Faculty(string name = "", int ID = 0, string login_status = "", string password = "") :User(name, ID, login_status, password, "faculty") {}
Admin::Admin(string name = "", int ID = 0, string login_status = "", string password = "") :User(name, ID, login_status, password, "admin") {}

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


AccessLogger::AccessLogger() :users(nullptr)
{
    this->current = 0;
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

    time_t now = time(NULL);
    tm cur_time;
    localtime_s(&cur_time, &now);
    string time = to_string(cur_time.tm_hour) + ":" + to_string(cur_time.tm_min) + ":" + to_string(cur_time.tm_sec);
    string date = to_string(cur_time.tm_mday) + '/' + to_string(cur_time.tm_mon + 1) + '/' + to_string(cur_time.tm_year - 100);

    fstream file("files/log-events.txt", ios::app);
    file << r.get_Name() << ',' << r.get_ID() << ',' << action << ',' << time << ',' << date << '\n';
    file.close();

    usernames.push_back(r.get_Name());
    ids.push_back(to_string(r.get_ID()));
    actions.push_back(action);
    times.push_back(time);
    dates.push_back(date);
}

AccessLogger::~AccessLogger()
{
    delete[] users;
}


string AccessLogger::read_all_logs()
{
    ifstream file("files/log-events.txt");
    string wholeline;
    string wholefile;
    while (getline(file, wholeline))
    {
        wholefile += wholeline + "\n";
    }
    file.close();
    return wholefile;
}

string AccessLogger::read_session_logs()
{
    string sessionlogs;
    for (int i = 0;i < usernames.size();i++)
    {
        sessionlogs += usernames.at(i) + "," + ids.at(i) + "," + actions.at(i) + "," + times.at(i) + "," + dates.at(i) + "\n";
    }
    return sessionlogs;
}

bool AccessControl::grantAccess(Zone z, const User& u)
{
    if (z.get_level() == "Low" && (u.get_user_type() == "student" || u.get_user_type() == "faculty" || u.get_user_type() == "admin"))
    {
        return true;
    }
    else if (z.get_level() == "Medium" && (u.get_user_type() == "faculty" || u.get_user_type() == "admin"))
    {
        return true;
    }
    else if (z.get_level() == "High" && (u.get_user_type() == "admin"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AccessControl::logAccess(Zone z, const User& u)
{
    ac.addLog(u, "Accessed " + z.get_type());
}
