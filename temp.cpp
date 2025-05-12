#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>

void display()
{
    sf::RenderWindow window(sf::VideoMode(800, 200), "Secure Access System");
    tgui::Gui gui(window);

    auto label = tgui::Label::create();
    label->setPosition(100, 80);
    label->setTextSize(30);
    label->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setText("");  // Initial empty
    label->setAutoSize(true);
    gui.add(label);

    std::string text = "Secure Access System";
    std::size_t index = 0;
    sf::Clock clock;
    float delay = 0.2f; // seconds between characters

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= delay && index <= text.size())
        {
            std::string formatted;
            for (std::size_t i = 0; i < text.size(); ++i)
            {
                if (i < index)
                    formatted += text[i];
                else if (i == index)
                    formatted += "[color=blue]" + std::string(1, text[i]) + "[/color]";
                else
                    formatted += " ";
            }
            label->setText(formatted);
            ++index;
            clock.restart();
        }

        window.clear();
        gui.draw();
        window.display();
    }
}
