#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/CheckBox.hpp>
#include <filesystem>

#include "project.cpp"

using namespace std;
using namespace sf;
using namespace tgui;;

//#include "project.cpp"




class UI_Template
{
protected:
    vector<Panel::Ptr> panels;
    vector<string> panels_name;
    vector<tgui::Label::Ptr> text_labels;
    RenderWindow window;
    Gui gui;

public:

    void initialize_panels()
    {
        auto init_panel = Panel::create({ "100%","100%" });
        panels.push_back(init_panel);
        panels_name.push_back("Main Menu");
        gui.add(init_panel);

        auto user_add_panel = Panel::create({ "100 %","100 %" });
        panels.push_back(user_add_panel);
        panels_name.push_back("User Form");
        gui.add(user_add_panel);

        auto login_panel_s = Panel::create({ "100%","100%" });
        panels.push_back(login_panel_s);
        panels_name.push_back("Login Form-student");
        gui.add(login_panel_s);

        auto login_panel_f = Panel::create({ "100%","100%" });
        panels.push_back(login_panel_f);
        panels_name.push_back("Login Form-faculty");
        gui.add(login_panel_f);

        auto login_panel_a = Panel::create({ "100%","100%" });
        panels.push_back(login_panel_a);
        panels_name.push_back("Login Form-admin");
        gui.add(login_panel_a);

        auto user_menu_panel_s = Panel::create({ "100%","100%" });
        panels.push_back(user_menu_panel_s);
        panels_name.push_back("PostLogin Menu-student");
        gui.add(user_menu_panel_s);

        auto user_menu_panel_f = Panel::create({ "100%","100%" });
        panels.push_back(user_menu_panel_f);
        panels_name.push_back("PostLogin Menu-faculty");
        gui.add(user_menu_panel_f);

        auto user_menu_panel_a = Panel::create({ "100%","100%" });
        panels.push_back(user_menu_panel_a);
        panels_name.push_back("PostLogin Menu-admin");
        gui.add(user_menu_panel_a);



        auto logs_panel = Panel::create({ "100%","100%" });
        panels.push_back(logs_panel);
        panels_name.push_back("Logs");
        gui.add(logs_panel);

        auto sub_logs_panel = Panel::create({ "100%","100%" });
        panels.push_back(sub_logs_panel);
        panels_name.push_back("Sub-Logs");
        gui.add(sub_logs_panel);

        UI_template_Maker();
    }


    auto return_Button(string cap, int width, int height, int pos_x, int pos_y, Panel::Ptr P, string name)
    {
        auto button = Button::create();
        button->setText(cap);
        button->setPosition(pos_x, pos_y);
        button->setSize(width, height);
        button->getRenderer()->setBorders(1.4);
        button->getRenderer()->setTextColorHover(sf::Color::Blue);
        button->getRenderer()->setBorderColorHover(sf::Color::Blue);
        P->add(button, name);;
        return button;
    }

    auto return_Radio(string cap, int pos_x, int pos_y, Panel::Ptr P, string name)
    {
        auto button = RadioButton::create();
        button->setText(cap);
        button->setPosition(pos_x, pos_y);
        button->getRenderer()->setBorders(1.4);
        button->getRenderer()->setTextColorHover(sf::Color::Blue);
        button->getRenderer()->setBorderColorHover(sf::Color::Blue);
        button->getRenderer()->setBorderColorChecked(sf::Color::Blue);
        button->getRenderer()->setTextColorChecked(sf::Color::Blue);
        P->add(button, name);
        return button;
    }

    auto return_EditBox(string text, int width, int height, int pos_x, int pos_y, Panel::Ptr P, string name)
    {
        auto editBox = EditBox::create();
        editBox->setPosition(pos_x, pos_y);
        editBox->setSize(width, height);
        editBox->setDefaultText(text);
        editBox->getRenderer()->setBorders(1.4);
        editBox->getRenderer()->setBorderColorHover(sf::Color::Blue);
        editBox->getRenderer()->setBorderColorFocused(sf::Color::Blue);
        editBox->getRenderer()->setTextSize(15);
        P->add(editBox, name);
        return editBox;
    }

    int find_index(string s)
    {
        int index = 0;
        for (int i = 0;i < panels_name.size();i++)
        {
            if (panels_name[i] == s)
            {
                return i;
            }

        };
        return -1;
    }

    void display_panel(Panel::Ptr panel = nullptr)
    {
        if (panel == nullptr)
        {
            for (int i = 0;i < panels.size();i++)
            {
                panels[i]->setVisible(false);
            }
        }
        else
        {
            for (int i = 0;i < panels.size();i++)
            {
                if (panel == panels[i])
                {
                    panels[i]->setVisible(true);
                }
                else
                {
                    panels[i]->setVisible(false);
                }
            }
        }
    }

    void display_panel(string panel_name)
    {
        int panel_index = find_index(panel_name);
        display_panel(panels[panel_index]);
    }



    void Animated_Text_Logo()
    {
        char logo[] = { 'S','e','c','u','r','e',' ','A','c','c','e','s','s',' ','S','y','s','t','e','m' };
        for (int i = 0;i < 20;i++)
        {
            Label::Ptr label = Label::create();
            label->setText(logo[i]);
            label->setTextSize(40);
            label->setPosition(370 + i * 28, 50);
            label->getRenderer()->setFont("files/ApexMk2.otf");
            label->getRenderer()->setTextOutlineThickness(1.2);
            label->getRenderer()->setTextOutlineColor(sf::Color::Black);
            label->getRenderer()->setTextColor(sf::Color::White);
            text_labels.push_back(label);
            gui.add(text_labels[i]);
        }
    }


    void Main_Menu_Panel()
    {
        int index = find_index("Main Menu");

        if (index == -1)
            window.close();

        auto button1 = return_Button("Login As A Student", 150, 50, 580, 180, panels[index], "student_login");
        auto button2 = return_Button("Login As A Faculty", 150, 50, 580, 250, panels[index], "faculty_login");
        auto button3 = return_Button("Login As A Admin", 150, 50, 580, 320, panels[index], "admin_login");
        auto button4 = return_Button("Add A New User", 150, 50, 580, 390, panels[index], "add_user");
        auto button5 = return_Button("Exit", 150, 50, 580, 460, panels[index], "exit");
    }

    void Add_User_Panel()
    {
        int  index = find_index("User Form");

        if (index == -1)
            window.close();


        auto uname_eb = return_EditBox("Enter UserName", 250, 50, 550, 170, panels[index], "eb_u");
        auto uid_eb = return_EditBox("Enter UserID", 250, 50, 550, 250, panels[index], "eb_id");
        auto pwd_eb = return_EditBox("Enter Password", 250, 50, 550, 320, panels[index], "eb_p");
        auto re_pwd_eb = return_EditBox("Re-enter Password", 250, 50, 550, 390, panels[index], "eb_rp");
        auto r_button_1 = return_Radio("Student", 550, 470, panels[index], "t_u");
        auto r_button_2 = return_Radio("Faculty", 630, 470, panels[index], "t_f");
        auto r_button_3 = return_Radio("Admin", 710, 470, panels[index], "t_a");
        auto button = return_Button("Save", 100, 30, 625, 570, panels[index], "save");
        auto arrow_button = return_Button("<----", 50, 30, 300, 170, panels[index], "back");
        button->getRenderer()->setRoundedBorderRadius(20);
        arrow_button->getRenderer()->setRoundedBorderRadius(20);
        auto label = tgui::Label::create();
        label->setTextSize(18);;
        label->setPosition(550, 530);
        panels[index]->add(label, "label");
    }

    void Login_Form_Panel(string user_type)
    {
        int index = find_index("Login Form-" + user_type);

        if (index == -1)
            window.close();

        auto uid_eb = return_EditBox("Enter UserID", 250, 50, 550, 170, panels[index], "uid_eb");
        auto pwd_eb = return_EditBox("Enter Password", 250, 50, 550, 250, panels[index], "pwd_eb");
        auto button = return_Button("Login", 100, 30, 625, 350, panels[index], "login");
        auto arrow_button = return_Button("<----", 50, 30, 300, 170, panels[index], "back");
        button->getRenderer()->setRoundedBorderRadius(20);
        arrow_button->getRenderer()->setRoundedBorderRadius(20);

        auto label = Label::create();
        panels[index]->add(label, "label");
    }


    void Post_Login_Panel(string user_type)
    {
        int index = find_index("PostLogin Menu-" + user_type);

        auto label = Label::create();
        label->setTextSize(20);
        label->setPosition(560, 120);
        panels[index]->add(label, "label");

        auto button1 = return_Button("Access to Cyber Lab", 200, 50, 560, 180, panels[index], "cyber lab");
        auto button2 = return_Button("Access to Digital Library", 200, 50, 560, 250, panels[index], "library");
        auto button3 = return_Button("Access to Data Center", 200, 50, 560, 320, panels[index], "datacenter");
        auto button4 = return_Button("View Logs (Admin Only)", 200, 50, 560, 390, panels[index], "logs");
        auto button5 = return_Button("Logout", 200, 50, 560, 460, panels[index], "logout");
    }



    void Logs_Panel()
    {
        int index = find_index("Logs");
        auto button1 = return_Button("View Session Logs", 200, 50, 560, 250, panels[index], "ses-logs");
        auto button2 = return_Button("View All Logs", 200, 50, 560, 320, panels[index], "all-logs");

        auto arrow_button = return_Button("<----", 60, 30, 100, 100, panels[index], "back");
        arrow_button->getRenderer()->setRoundedBorderRadius(20);
    }

    void Sub_Logs_Panel()
    {
        int index = find_index("Sub-Logs");

        auto view_logs_panel = ScrollablePanel::create({ "70%","70%" });;
        view_logs_panel->setPosition(200, 150);
        view_logs_panel->getRenderer()->setBackgroundColor(sf::Color(230, 230, 230));
        view_logs_panel->setVerticalScrollbarValue(10);
        panels[index]->add(view_logs_panel, "sub-panel");

        auto arrow_button = return_Button("<----", 60, 30, 100, 100, panels[index], "back");
        arrow_button->getRenderer()->setRoundedBorderRadius(20);
    }

    void UI_template_Maker()
    {
        Animated_Text_Logo();
        Main_Menu_Panel();
        Add_User_Panel();
        Login_Form_Panel("student");
        Login_Form_Panel("faculty");
        Login_Form_Panel("admin");
        Post_Login_Panel("student");
        Post_Login_Panel("faculty");
        Post_Login_Panel("admin");
        Logs_Panel();
        Sub_Logs_Panel();

    }

};

class UI_Functionality : public UI_Template
{
protected:
    AccessLogger logger;
    AccessControl controller;
    Hash_Manager hash_manager;
    map<string, bool> panel_manager;
    Zone* zone[3];

public:

    UI_Functionality()
    {
        zone[0] = new Zone("Cyber Lab", "High");
        zone[1] = new Zone("Digital Library", "Low");
        zone[2] = new Zone("Data Center", "High");;

        for (auto& i : panels_name)
        {
            panel_manager[i] = false;
        }

        string folder_name = "files";
        if (!Filesystem::directoryExists(folder_name))
        {
            Filesystem::createDirectory(folder_name);
        }
    }

    void add_Main_Menu()
    {
        int index = find_index("Main Menu");

        if (index == -1)
            window.close();

        display_panel(panels[index]);

        if (!panel_manager["Main Menu"])
        {
            auto button1 = panels[index]->get<tgui::Button>("student_login");
            auto button2 = panels[index]->get<tgui::Button>("faculty_login");
            auto button3 = panels[index]->get<tgui::Button>("admin_login");
            auto button4 = panels[index]->get<tgui::Button>("add_user");
            auto button5 = panels[index]->get<tgui::Button>("exit");


            button1->onPress([=] {Login_Form<Student>("student");});
            button2->onPress([=] {Login_Form<Faculty>("faculty");});
            button3->onPress([=] {Login_Form<Admin>("admin");});
            button4->onPress([=] {useradd();});
            button5->onPress([=] {window.close();});

            panel_manager["Main Menu"] = true;
        }
    }



    void useradd()
    {


        int index = find_index("User Form");

        if (index == -1)
            window.close();

        display_panel(panels[index]);

        if (!panel_manager["User Form"])
        {

            auto uname_eb = panels[index]->get<tgui::EditBox>("eb_u");
            auto uid_eb = panels[index]->get<tgui::EditBox>("eb_id");
            auto pwd_eb = panels[index]->get<tgui::EditBox>("eb_p");
            auto re_pwd_eb = panels[index]->get<tgui::EditBox>("eb_rp");
            auto r_button_1 = panels[index]->get<tgui::RadioButton>("t_u");
            auto r_button_2 = panels[index]->get<tgui::RadioButton>("t_f");
            auto r_button_3 = panels[index]->get<tgui::RadioButton>("t_a");
            auto button = panels[index]->get<tgui::Button>("save");
            auto arrow_button = panels[index]->get<tgui::Button>("back");
            auto label = panels[index]->get<tgui::Label>("label");


            button->onPress([=]
                {
                    label->setText("");
                    tgui::String u_name = uname_eb->getText();
                    string uname = u_name.toStdString();
                    tgui::String u_id = uid_eb->getText();
                    string uid = u_id.toStdString();
                    tgui::String u_pwd = pwd_eb->getText();
                    string pwd = u_pwd.toStdString();
                    tgui::String u_re_pwd = re_pwd_eb->getText();
                    string re_pwd = u_re_pwd.toStdString();
                    bool secure_pass = false;
                    bool has_lower = false;
                    bool has_upper = false;
                    bool has_special = false;
                    bool has_number = false;
                    bool has_length = false;
                    for (int i = 0;i < pwd.length();i++)
                    {
                        if (tolower(pwd[i]) && !has_lower)
                        {
                            has_lower = true;
                        }
                        if (toupper(pwd[i]) && !has_upper)
                        {
                            has_upper = true;
                        }
                        if (isdigit(pwd[i]) && !has_number)
                        {
                            has_number = true;
                        }
                        if (ispunct(pwd[i]) && !has_special)
                        {
                            has_special = true;
                        }
                        if (pwd.length() > 8 && !has_length)
                        {
                            has_length = true;
                        }
                    }

                    if (has_lower && has_upper && has_number && has_special && has_length)
                    {
                        secure_pass = true;
                    }
                    if (uname != "" && uid != "" && pwd != "" && pwd == re_pwd && secure_pass)
                    {
                        if (r_button_1->isChecked())
                        {
                            if (hash_manager.store_User<Student>(uid, uname, pwd))
                            {
                                label->setText("SuccessFully Added");
                            }
                            else
                            {
                                label->setText("User With Same ID Exists");;
                            }
                        }
                        else if (r_button_2->isChecked())
                        {
                            if (hash_manager.store_User<Faculty>(uid, uname, pwd))
                            {
                                label->setText("SuccessFully Added");
                            }
                            else
                            {
                                label->setText("User With Same ID Exists");

                            }
                        }
                        else if (r_button_3->isChecked())
                        {
                            if (hash_manager.store_User<Admin>(uid, uname, pwd))
                            {
                                label->setText("SuccessFully Added");
                            }
                            else
                            {
                                label->setText("User With Same ID Exists");
                            }
                        }
                        else
                        {
                            label->setText("Please Select user Type");
                        }
                    }
                    else if (!secure_pass)
                    {
                        label->setText("Password is Not Strong");
                    }
                    else if (uname == "")
                    {
                        label->setText("Username cant be empty");
                    }
                    else if (uid == "")
                    {
                        label->setText("UserID cant be empty");
                    }
                    else if (pwd == "")
                    {
                        label->setText("Password cant be empty");
                    }
                    else if (re_pwd != pwd)
                    {
                        label->setText("Password didnt match");;
                    }
                });
            arrow_button->onPress([=] {
                label->setText("");
                add_Main_Menu();
                });

            panel_manager["User Form"] = true;
        }
    }

    template <typename T>
    void Login_Form(string user_type)
    {
        int index = find_index("Login Form-" + user_type);

        if (index == -1)
            exit(-1);

        display_panel(panels[index]);

        if (!panel_manager["Login Form-" + user_type])
        {

            auto uid_eb = panels[index]->get<tgui::EditBox>("uid_eb");
            auto pwd_eb = panels[index]->get<tgui::EditBox>("pwd_eb");
            auto button = panels[index]->get<tgui::Button>("login");
            auto arrow_button = panels[index]->get<tgui::Button>("back");
            auto label = panels[index]->get<tgui::Label>("label");

            uid_eb->onUnfocus([=]
                {
                    string uid = uid_eb->getText().toStdString();
                    if (hash_manager.validate_id<T>(uid))
                    {
                        uid_eb->getRenderer()->setTextColor(sf::Color(0, 100, 0));
                        uid_eb->getRenderer()->setBorderColor(sf::Color(0, 100, 0));
                    }
                    else
                    {
                        uid_eb->getRenderer()->setTextColor(sf::Color::Red);
                        uid_eb->getRenderer()->setBorderColor(sf::Color::Red);;
                    }
                });



            pwd_eb->onUnfocus([=]
                {
                    string uid = uid_eb->getText().toStdString();
                    string ps = pwd_eb->getText().toStdString();
                    if (hash_manager.validate_user<T>(uid, ps))
                    {
                        pwd_eb->getRenderer()->setTextColor(sf::Color(0, 100, 0));
                        pwd_eb->getRenderer()->setBorderColor(sf::Color(0, 100, 0));

                    }
                    else
                    {
                        pwd_eb->getRenderer()->setTextColor(sf::Color::Red);
                        pwd_eb->getRenderer()->setBorderColor(sf::Color::Red);
                    }

                });

            button->onPress([=]
                {
                    label->setText("");

                    label->setTextSize(20);

                    string uid = uid_eb->getText().toStdString();
                    string ps = pwd_eb->getText().toStdString();;

                    if (hash_manager.validate_user<T>(uid, ps))
                    {
                        T user;
                        user.set_ID(stoi(uid));
                        user.set_Name(User::get_username_by_id(uid));
                        user.set_login("Logged In");
                        logger.addLog(user, "Logged In");
                        label->setText("");
                        uid_eb->setText("");
                        pwd_eb->setText("");
                        display_user_menu<T>(user);
                    }
                    else
                    {
                        label->setText("Username or Password Not Correct");
                        label->setPosition(525, 450);

                    }
                });
            arrow_button->onPress([=] {
                uid_eb->setText("");
                pwd_eb->setText("");
                label->setText("");
                add_Main_Menu();
                });

            panel_manager["Login Form-" + user_type] = true;

        }
    }

    template<typename r_class>
    void display_sub_logs_panel(string logs, r_class user)
    {

        int index = find_index("Sub-Logs");
        display_panel(panels[index]);


        auto arrow_button = panels[index]->get<tgui::Button>("back");
        auto view_logs_panel = panels[index]->get<tgui::Panel>("sub-panel");
        view_logs_panel->removeAllWidgets();

        stringstream sst(logs);
        string s_line;

        string name, id, action, t, d;
        vector<string>names, ids, actions, time, date;

        while (getline(sst, s_line))
        {
            stringstream ss(s_line);
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, action, ',');
            getline(ss, t, ',');
            getline(ss, d, ',');

            names.push_back(name);
            ids.push_back(id);
            actions.push_back(action);
            time.push_back(t);
            date.push_back(d);
        }

        for (int i = 0;i < names.size();i++)
        {
            string log = to_string((i + 1)) + ". Name : " + names[i] + "\nID: " + ids[i] + "\nAction : " + actions[i] + "\nTime : " + time[i] + "\nDate : " + date[i] + "\n";
            auto log_label = tgui::Label::create();
            log_label->setText(log);
            log_label->setTextSize(18);
            log_label->setPosition(100, 50 + (i * 120));;
            view_logs_panel->add(log_label);
        }

        arrow_button->onPress([=] {
            display_logs_panel(user);
            });

    }

    template<typename r_class>
    void display_logs_panel(r_class user)
    {
        int index = find_index("Logs");
        display_panel(panels[index]);

        if (!panel_manager["Logs"])
        {
            auto button1 = panels[index]->get<tgui::Button>("ses-logs");
            auto button2 = panels[index]->get<tgui::Button>("all-logs");
            auto arrow_button = panels[index]->get<tgui::Button>("back");


            button1->onPress([=] {

                string logs = logger.read_session_logs();
                display_sub_logs_panel(logs, user);

                });

            button2->onPress([=] {

                string logs = logger.read_all_logs();
                display_sub_logs_panel(logs, user);
                });

            arrow_button->onPress([=] {

                display_user_menu<r_class>(user);

                });

            panel_manager["Logs"] = true;
        }

    }





    template<typename r_class>
    void display_user_menu(r_class user)
    {
        int index = find_index("PostLogin Menu-" + (user.get_user_type()));
        display_panel(panels[index]);

        if (!panel_manager["PostLogin Menu-" + (user.get_user_type())])
        {

            auto button1 = panels[index]->get<tgui::Button>("cyber lab");
            auto button2 = panels[index]->get<tgui::Button>("library");
            auto button3 = panels[index]->get<tgui::Button>("datacenter");
            auto button4 = panels[index]->get<tgui::Button>("logs");
            auto button5 = panels[index]->get<tgui::Button>("logout");
            auto label = panels[index]->get<tgui::Label>("label");
            label->setText("Welcome , " + user.get_Name());
            label->getRenderer()->setTextColor(sf::Color::Black);



            button1->onPress([=]
                {
                    if (controller.grantAccess(*zone[0], user))
                    {
                        controller.logAccess(*zone[0], user);
                        label->getRenderer()->setTextColor(sf::Color(0, 100, 0));
                        label->setPosition(600, 120);
                        label->setText("Accessed");
                    }
                    else
                    {
                        label->getRenderer()->setTextColor(sf::Color::Red);
                        label->setPosition(610, 120);
                        label->setText("Denied");
                    }
                });

            button2->onPress([=]
                {

                    if (controller.grantAccess(*zone[1], user))
                    {
                        controller.logAccess(*zone[1], user);
                        label->getRenderer()->setTextColor(sf::Color(0, 100, 0));
                        label->setPosition(600, 120);
                        label->setText("Accessed");
                    }
                    else
                    {
                        label->getRenderer()->setTextColor(sf::Color::Red);
                        label->setPosition(610, 120);
                        label->setText("Denied");
                    }
                });

            button3->onPress([=] {
                if (controller.grantAccess(*zone[2], user))
                {
                    controller.logAccess(*zone[2], user);
                    label->getRenderer()->setTextColor(sf::Color(0, 100, 0));
                    label->setPosition(600, 120);
                    label->setText("Accessed");
                }
                else
                {
                    label->getRenderer()->setTextColor(sf::Color::Red);
                    label->setPosition(610, 120);
                    label->setText("Denied");
                }
                });

            button4->onPress([=]
                {
                    if (user.get_user_type() == "admin")
                    {
                        display_logs_panel(user);;
                    }

                    else
                    {
                        label->setText("Denied");
                        label->getRenderer()->setTextColor(sf::Color::Red);
                    }

                });

            button5->onPress([=] {
                logger.addLog(user, "Logged Out");
                label->setText("");
                add_Main_Menu();
                });

            panel_manager["PostLogin Menu-" + (user.get_user_type())] = true;

        }
    }

    ~UI_Functionality()
    {
        for (int i = 0;i < 3;i++)
        {
            delete zone[i];
        }
    }
};


class GUI : public UI_Functionality
{
public:

    void initialize_GUI()
    {
        window.create(sf::VideoMode(1280, 720), "Secure System");
        gui.setTarget(window);
        window.setFramerateLimit(60);
        initialize_panels();;
        add_Main_Menu();
    }

    void draw_GUI()
    {
        int l = 0;
        sf::Clock clock;
        float animation_time = 0.5f;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                gui.handleEvent(event);

                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (clock.getElapsedTime().asSeconds() > animation_time)
            {
                text_labels[l % 20]->getRenderer()->setTextColor(sf::Color::Blue);
                for (int i = 0;i < 20;i++)
                {
                    if (i != l % 20)
                    {
                        text_labels[i]->getRenderer()->setTextColor(sf::Color::White);
                    }

                }
                l++;
                clock.restart();
            }

            window.clear(sf::Color::White);
            gui.draw();
            window.display();
        }
    }
};



int main()
{
    GUI ss;
    ss.initialize_GUI();
    ss.draw_GUI();
    return 0;
}