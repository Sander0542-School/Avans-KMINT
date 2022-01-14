#include "kmint/main.hpp" // voor de main loop
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/rabbit.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include "actors/WaterNodeActor.hpp"
#include "actors/HoleNodeActor.hpp"
#include "actors/GrassNodeActor.hpp"

using namespace kmint;

int main()
{
    // een app object is nodig om
    ui::app app{};

    //  maak een venster aan
    ui::window window{app.create_window({1024, 768}, "rabbitisland", 1.0)};

    // maak een podium aan
    play::stage s{{1024, 768}};

    auto map = rabbitisland::map();
    auto& graph = map.graph();
    s.build_actor<play::background>(math::size(1024, 768), graphics::image{map.background_image()});
    s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());

    auto waterMap = rabbitisland::WaterMap();
    auto& waterGraph = waterMap.graph();
    auto grassMap = rabbitisland::GrassMap();
    auto& grassGraph = grassMap.graph();
    auto holesMap = rabbitisland::HolesMap();
    auto& holesGraph = holesMap.graph();

    for (const map::map_node& node: waterGraph)
    {
        s.build_actor<actors::WaterNodeActor>(node);
    }
    for (const map::map_node& node: grassGraph)
    {
        s.build_actor<actors::GrassNodeActor>(node);
    }
    for (const map::map_node& node: holesGraph)
    {
        s.build_actor<actors::HoleNodeActor>(node);
    }

    auto& mister = s.build_actor<rabbitisland::mister>(graph, rabbitisland::find_node_of_kind(graph, '2'));
    auto& misses = s.build_actor<rabbitisland::misses>(graph, rabbitisland::find_node_of_kind(graph, '3'));
    auto& dog = s.build_actor<rabbitisland::dog>(graph, rabbitisland::find_node_of_kind(graph, '1'), mister, misses);

    for (auto i = 0; i < 100; ++i)
    {
        s.build_actor<rabbitisland::rabbit>(dog);
    }

    // Maak een event_source aan (hieruit kun je alle events halen, zoals
    // toetsaanslagen)
    ui::events::event_source event_source{};

    // main_loop stuurt alle actors aan.
    main_loop(s, window, [&](delta_time dt, loop_controls& ctl) {
        // gebruik dt om te kijken hoeveel tijd versterken is
        // sinds de vorige keer dat deze lambda werd aangeroepen
        // loop controls is een object met eigenschappen die je kunt gebruiken om de
        // main-loop aan te sturen.

        for (ui::events::event& e: event_source)
        {
            // event heeft een methode handle_quit die controleert
            // of de gebruiker de applicatie wilt sluiten, en zo ja
            // de meegegeven functie (of lambda) aanroept om met het
            // bijbehorende quit_event
            //
            e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
            e.handle_key_up([&](auto ke) {
                switch (ke.key)
                {
                    case ui::events::key::p:
                        ctl.pause = !ctl.pause;
                        break;
                    case ui::events::key::r:
                        ctl.render = !ctl.render;
                        break;
                    case ui::events::key::opening_bracket:
                        ctl.time_scale /= 2.0;
                        break;
                    case ui::events::key::closing_bracket:
                        ctl.time_scale *= 2.0;
                        break;
                    case ui::events::key::d:
                        ctl.debug_overlay = !ctl.debug_overlay;
                    default:
                        break;
                }
            });
        }
    });
}
