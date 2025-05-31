#include<iostream>
#include<string>
#include<vector>

using namespace std;
class User
{
protected:
    string name;
    string user_type;
    int ID;
    string login_status;
    string password;
    static int userCount;

public:
    User(string name, int ID, string login_status, string password, string user_type);
    void set_Name(string name);
    void set_ID(int ID);
    void set_login(string login_status);
    void set_user_type(string user_type);
    string get_Name() const;
    int get_ID() const;
    string get_status() const;
    string get_user_type() const;
    static string get_username_by_id(string id);
    ~User();
};


class Hash_Manager
{
private:
    string sha256(const string str);
    string salting();

public:
    template<typename a_class>
    bool store_User(string id, string username, string password);
    template<typename a_class>
    bool validate_user(string id, string pwd);
    template<typename a_class>
    bool validate_id(string id);

};

class Student : public User
{
private:
    static string credentials_file;
    static string salt_file;
public:
    Student(string name, int ID, string login_status, string password);
    static string get_file();
    static string get_salt_file();
};

class Faculty : public User
{
private:
    static string credentials_file;
    static string salt_file;
public:
    Faculty(string name, int ID, string login_status, string password);
    static string get_file();
    static string get_salt_file();
};

class Admin : public User
{
private:
    static string credentials_file;
    static string salt_file;
public:
    Admin(string name, int ID, string login_status, string password);
    static string get_file();
    static string get_salt_file();
};

// bool validate_user(string id,string password);

class Zone
{
private:
    User* users;
    string zone_type;
    string security_level;
    int current;
public:
    Zone(string zone_type, string security_level);
    string get_type();
    string get_level();
    friend void operator +=(Zone& zone, User& user);
    friend bool operator ==(const Zone& zone1, const Zone& zone2);
};

class AccessLogger
{
private:
    User* users;
    vector<string> usernames;
    vector<string> actions;
    vector<string> ids;
    vector<string> times;
    vector<string> dates;
    int current;//session logs

public:
    AccessLogger();
    template <typename ran_class>
    void addLog(ran_class& r, string action);
    string read_session_logs();
    string read_all_logs();
    ~AccessLogger();
};

class SecureEntity
{
private:
public:
    virtual bool grantAccess(Zone z, const User& u) = 0;
    virtual void logAccess(Zone z, const User& u) = 0;
};

class AccessControl :public SecureEntity
{
private:
    AccessLogger ac;
public:
    bool grantAccess(Zone z, const User& u) override;
    void logAccess(Zone z, const User& u) override;
};
#pragma once
