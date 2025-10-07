#include <iostream>
#include <stdint.h>
#include <string>
#include "Board.h"
#include "ScrollableGame.h"
#include "LoadPgn.h"
#include "SetupGame.h"
#include "VConstructor.h"
#include "Timeline.h"

enum {
    a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7,
    _1 = 0, _2 = 1, _3 = 2, _4 = 3, _5 = 4, _6 = 5, _7 = 6, _8 = 7,
    l0 = 64, l1 = 63, l2 = 62, lminus1 = 65, lminus2 = 66
};

class Timeline;

int main()
{
    //bool clicked = true;
    //bool a, b;
    //auto window = sf::RenderWindow(sf::VideoMode({ 640u,480u }), "CMake SFML Project");
    //window.setFramerateLimit(144);
    //if (!ImGui::SFML::Init(window))
    //    return -1;

    //sf::Clock clock;
    //ImGui::SetNextWindowPos(sf::Vector2f(300, 200));
    //ImGui::SetNextWindowSize(sf::Vector2f(200, 200));
    //while (window.isOpen())
    //{
    //    while (const std::optional event = window.pollEvent())
    //    {
    //        ImGui::SFML::ProcessEvent(window, *event);
    //        if (event->is<sf::Event::Closed>())
    //        {
    //            window.close();
    //        }
    //       
    //    }

    //    ImGui::SFML::Update(window, clock.restart());
    //    //| ImGuiWindowFlags_::
    //    if (clicked) {
    //        ImGui::SetNextItemWidth(100);
    //        ImGui::Begin("button 1", &clicked, (ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_HorizontalScrollbar));
    //        a = ImGui::Button("Look at this pretty button");
    //        b = ImGui::Button("What does this do");   

    //        if (ImGui::ColorEdit3("Background color", color)) {
    //            bgColor.r = static_cast<std::uint8_t>(color[0] * 255.f);
    //            bgColor.g = static_cast<std::uint8_t>(color[1] * 255.f);
    //            bgColor.b = static_cast<std::uint8_t>(color[2] * 255.f);
    //        }

    //        ImGui::InputText("Window title", windowTitle, 255);

    //        if (ImGui::Button("Update window title")) {
    //            window.setTitle(windowTitle);
    //        }
    //        ImGui::NextColumn();
    //        ImGui::InputInt("number",&i);
    //        ImGui::Checkbox("true or false",&c);
    //        ImGui::SliderInt("slider", &slider, 0, 10);
    //        //ImGui::DragInt("drag", &drag, 1.0f, 0, 10);
    //        ImGui::End();
    //    }

    //    if (a) {std::cout << "pressed: Look at this pretty button\n";}
    //    if (b) {std::cout << "pressed: What does this do\n";}

    //    window.clear(bgColor);
    //    ImGui::SFML::Render(window);
    //    window.display();
    //}

    //ImGui::SFML::Shutdown();

    std::map<std::string, std::pair<VConstructor*, Location>> temp;

    temp[ConstructSquares::name] = { new ConstructSquares(8, 8, 1), Location::BOARD };
    temp["en passant"] = {new VConstructorTemplate<ByDefaultZeros, ConstructOnes>(2), Location::BOARD};
    SetupGame setup(temp);
  
    BorderBoard g;
    g.x = 8;
    g.y = 8;

    ScrollableGame a(XYTL(8, 8, 512, 129), l0, l0, 2);

    setup.Setup(a);
    a.multiverse[l0] = Timeline::CreateTimelinePointer(500, 64, 0, Board::StartingPosition8x8);
    a.multiverse[l0]->CreateNextTurnSamePointer();
    Turn move;
    move.SetStringTurn(a,"(0T1)d2d4",0);
    a.MakeMove(move);
    const string test = "game.txt";

   
    a.Print(); 
}
