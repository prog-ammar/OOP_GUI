#include<iostream>
#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/CheckBox.hpp>

#include "project.cpp"

using namespace std;
using namespace sf;
using namespace tgui;

//#include "project.cpp"

class GUI
{
    private:
        RenderWindow window;
        Gui gui;
        vector<Panel::Ptr> panels;
        vector<string> panels_name;
        AccessLogger logger;
        vector<tgui::Label::Ptr> t;
        AccessControl controller;

    public:
        
        GUI():window(sf::VideoMode(1280, 720), "Secure System"),gui(window) 
        {
            window.setFramerateLimit(60);
            initialize_panels();
        }


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

            auto login_panel = Panel::create({ "100%","100%" });
            panels.push_back(login_panel);
            panels_name.push_back("Login Form");
            gui.add(login_panel);

            auto user_menu_panel = Panel::create({ "100%","100%" });
            panels.push_back(user_menu_panel);
            panels_name.push_back("PostLogin Menu");
            gui.add(user_menu_panel);
        }


        auto return_Button(string cap, int width, int height, int pos_x, int pos_y, Panel::Ptr P)
        {
            auto button = Button::create();
            button->setText(cap);
            button->setPosition(pos_x, pos_y);
            button->setSize(width, height);
            button->getRenderer()->setBorders(1.4);
            button->getRenderer()->setTextColorHover(sf::Color::Blue);
            button->getRenderer()->setBorderColorHover(sf::Color::Blue);
            P->add(button);
            return button;
        }

        auto return_Radio(string cap, int pos_x, int pos_y, Panel::Ptr P)
        {
            auto button = RadioButton::create();
            button->setText(cap);
            button->setPosition(pos_x, pos_y);
            button->getRenderer()->setBorders(1.4);
            button->getRenderer()->setTextColorHover(sf::Color::Blue);
            button->getRenderer()->setBorderColorHover(sf::Color::Blue);
            button->getRenderer()->setBorderColorChecked(sf::Color::Blue);
            button->getRenderer()->setTextColorChecked(sf::Color::Blue);
            P->add(button);
            return button;
        }

        auto return_EditBox(string text, int width, int height, int pos_x, int pos_y, Panel::Ptr P)
        {
            auto editBox = EditBox::create();
            editBox->setPosition(pos_x, pos_y);
            editBox->setSize(width, height);
            editBox->setDefaultText(text);
            editBox->getRenderer()->setBorders(1.4);
            editBox->getRenderer()->setBorderColorHover(sf::Color::Blue);
            editBox->getRenderer()->setBorderColorFocused(sf::Color::Blue);
            editBox->getRenderer()->setTextSize(15);
            P->add(editBox);
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

            }
            return -1;
        }

        void display_panel(Panel::Ptr panel)
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


        void add_Main_Menu()
        {
            int index = find_index("Main Menu");

            if (index == -1)
                exit(-1);

            text();
      
            auto button1 = return_Button("Login As A Student", 150, 50, 580, 180, panels[index]);
            auto button2 = return_Button("Login As A Faculty", 150, 50, 580, 250, panels[index]);
            auto button3 = return_Button("Login As A Admin", 150, 50, 580, 320, panels[index]);
            auto button4 = return_Button("Add A New User", 150, 50, 580, 390, panels[index]);
            auto button5 = return_Button("Exit", 150, 50, 580, 460, panels[index]);
            
            button1->onPress(&GUI::Login_Form<Student>, this);
            button2->onPress(&GUI::Login_Form<Admin>, this);
            button3->onPress(&GUI::Login_Form<Faculty>, this);   
            button4->onPress(&GUI::useradd, this);
            button5->onPress([&] {exit(0);});

            
            display_panel(panels[index]);
        }

       

        void useradd()
        {
            int index = find_index("User Form");
            
            if (index == -1)
            exit(-1);


            auto uname_eb = return_EditBox("Enter UserName", 250, 50, 550, 170,panels[index]);
            auto uid_eb = return_EditBox("Enter UserID", 250, 50, 550, 250, panels[index]);
            auto pwd_eb = return_EditBox("Enter Password", 250, 50, 550, 320, panels[index]);
            auto re_pwd_eb = return_EditBox("Re-enter Password", 250, 50, 550, 390, panels[index]);
            auto r_button_1 = return_Radio("Student", 550, 470, panels[index]);
            auto r_button_2 = return_Radio("Faculty", 630, 470, panels[index]);
            auto r_button_3 = return_Radio("Admin", 710, 470, panels[index]);
            auto button = return_Button("Save", 100, 30, 625, 570, panels[index]);
            auto arrow_button = return_Button("<----", 50, 30, 300, 170, panels[index]);
            button->getRenderer()->setRoundedBorderRadius(20);
            arrow_button->getRenderer()->setRoundedBorderRadius(20);
            
            display_panel(panels[index]);

            auto label = tgui::Label::create();
            label->setTextSize(25);
            label->setPosition(550, 550);
            button->onPress([=]()
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
                    if (uname != "" && uid != "" && pwd != "" && pwd == re_pwd)
                    {
                        if (r_button_1->isChecked())
                        {
                            Hash_Manager<Student>::store_User(uid, pwd);
                        }
                        else if (r_button_2->isChecked())
                        {
                            Hash_Manager<Faculty>::store_User(uid, pwd);
                        }
                        else if (r_button_3->isChecked())
                        {
                            Hash_Manager<Admin>::store_User(uid, pwd);
                        }
                        else
                        {
                            label->setText("Please Select user Type");
                            panels[index]->add(label);
                        }
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
                        label->setText("Password didnt match");
                    }
                    panels[index]->add(label);
                });
            arrow_button->onPress([&] {
                display_panel(panels[0]);
                });

        }

        template <typename T>
        void Login_Form()
        {
           
            int index = find_index("Login Form");

            if (index == -1)
                exit(-1);

            auto uid_eb=return_EditBox("Enter UserID", 250, 50, 550, 170,panels[index]);
            auto pwd_eb=return_EditBox("Enter Password", 250, 50, 550, 250,panels[index]);
            auto button=return_Button("Login", 100, 30, 625, 350,panels[index]);
            auto arrow_button = return_Button("<----", 50, 30, 300, 170, panels[index]);
            button->getRenderer()->setRoundedBorderRadius(20);
            arrow_button->getRenderer()->setRoundedBorderRadius(20);
            
            display_panel(panels[index]);
            auto label = Label::create();

            uid_eb->onUnfocus([=]
                    {
                        string uid = uid_eb->getText().toStdString();
                        if (Hash_Manager<T>::validate_id(uid))
                        {
                            uid_eb->getRenderer()->setTextColor(sf::Color(0,100,0));
                            uid_eb->getRenderer()->setBorderColor(sf::Color(0,100,0));
                        }
                        else
                        {
                            uid_eb->getRenderer()->setTextColor(sf::Color::Red);
                            uid_eb->getRenderer()->setBorderColor(sf::Color::Red);
                        }
                    });
    

            
            pwd_eb->onUnfocus([=]
                {
                    string uid = uid_eb->getText().toStdString();
                    string ps= pwd_eb->getText().toStdString();
                    if (Hash_Manager<T>::validate_user(uid, ps))
                    {
                        pwd_eb->getRenderer()->setTextColor(sf::Color(0,100,0));
                        pwd_eb->getRenderer()->setBorderColor(sf::Color(0,100,0));

                    }
                    else
                    {
                        pwd_eb->getRenderer()->setTextColor(sf::Color::Red);
                        pwd_eb->getRenderer()->setBorderColor(sf::Color::Red
                        );
                    }
      
                });
            
            button->onPress([=]()
                {
                    label->setText("");
                    
                    label->setTextSize(20);
                    
                    string uid = uid_eb->getText().toStdString();
                    string ps = pwd_eb->getText().toStdString();

                    if (Hash_Manager<T>::validate_user(uid, ps))
                    {
                        label->setText("Login SuccessFull");
                        T user;
                        user.set_ID(stoi(uid));
                        user.set_Name(User::get_username_by_id(uid));
                        user.set_login("Logged In");
                        logger.addLog(user, "Logged In");
                        display_user_menu<T>(user);
                    }
                    else
                    {
                        label->setText("Username or Password Not Correct");
                        label->setPosition(525, 450);
                        
                    }
                    panels[index]->add(label);
                });
            arrow_button->onPress([&] {
                display_panel(panels[0]);
                });
        }
        
        template<typename r_class>
        void display_user_menu(r_class& user)
        {

            int index = find_index("PostLogin Menu");

            auto label = Label::create();
            label->setText("Welcome , "+user.get_Name());
            label->setTextSize(20);
            label->setPosition(550, 110);
            panels[index]->add(label);

            auto button1 = return_Button("Access to Cyber Lab", 150, 50, 580, 180, panels[index]);
            auto button2 = return_Button("Access to Digital Library", 150, 50, 580, 250, panels[index]);
            auto button3 = return_Button("Access to Data Center", 150, 50, 580, 320, panels[index]);
            auto button4 = return_Button("View Logs (Admin Only)", 150, 50, 580, 390, panels[index]);
            auto button5 = return_Button("Logout", 150, 50, 580, 460, panels[index]);

            Zone* z1=new Zone("Cyber Lab", "Low");
            Zone* z2=new Zone("Digital Library", "Medium");
            Zone* z3=new Zone("Data Center", "High");

            display_panel(panels[index]);

            button1->onPress([=,&z1,&user] {
                
                if (controller.grantAccess(*z1, user))
                {
                    controller.logAccess(*z1, user);
                    label->setText("Accessed");
                }
                else
                {
                    label->setText("Denied");
                }
            });

            button2->onPress([=,&z2,&user] {
                
                if (controller.grantAccess(*z2, user))
                {
                    controller.logAccess(*z2, user);
                    label->setText("Accessed");
                }
                else
                {
                    label->setText("Denied");
                }
                
            });

            button3->onPress([=,&z3,&user] {
                
                if (controller.grantAccess(*z3, user))
                {
                    controller.logAccess(*z3, user);
                    label->setText("Accessed");
                }
                else
                {
                    label->setText("Denied");
                }
            });

        }


        void text()
        {
            char logo[] = { 'S','e','c','u','r','e',' ','A','c','c','e','s','s',' ','S','y','s','t','e','m'};
            sf::Font font;
            font.loadFromFile("Closeness.ttf");
            for (int i = 0;i < 20;i++)
            {
                Label::Ptr label = Label::create();

                label->setText(logo[i]);
                label->setTextSize(40);
                label->setPosition(370+i*28, 50);
                label->getRenderer()->setFont("ApexMk2.otf");
                label->getRenderer()->setTextOutlineThickness(1.2);
                label->getRenderer()->setTextOutlineColor(sf::Color::Black);
                label->getRenderer()->setTextColor(sf::Color::White);
                t.push_back(label);
                gui.add(t[i]);
            }
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
                    t[l % 20]->getRenderer()->setTextColor(sf::Color::Blue);
                    /*t[l % 20]->getRenderer()->setTextOutlineColor(sf::Color::Black);*/
                    for (int i = 0;i < 20;i++)
                    {
                        if (i != l % 20)
                        {
                            t[i]->getRenderer()->setTextColor(sf::Color::White);
                            /*t[i]->getRenderer()->setTextOutlineColor(sf::Color::Black);*/
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
    ss.add_Main_Menu();
    ss.draw_GUI();
    return 0;
}