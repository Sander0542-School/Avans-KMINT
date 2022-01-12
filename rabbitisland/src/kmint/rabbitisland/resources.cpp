#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"
#include <array>
#include <random>
#include <algorithm>


namespace kmint {
namespace rabbitisland {
namespace {
constexpr const char *graph_description = R"graph(32 24 32
resources/rabbitisland.png
W 0 0
H 0 0
M 1 4
L 1 1
G 0 0
T 1 1
1 1 4
2 1 1
3 1 1

WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWTLLLLLLLLLLWWWWWLLM1WW
WWWWWWWWWWLLLLLLLLLLLLLLLLLLLLWW
WWWWWWWWWLLLLLLLLLLMMLLLLLLLLLWW
WWW2LLLLLLLLLLLLLLLLLLLLLLLLLLWW
WWWLHLLLLLLLLLLLLLLLLLLLLLLLLLWW
WWWLLLLLLLLLLLLLLLLLLLLLLLLLLLWW
WWWLLLLLLLLLLLLLMMLLLLLLLLLLMMWW
WWWLLLLLLLLLLLLLMMMLLLLLLLLMMMWW
WWWLLLLLLLLLLLLLMMLLLLLLMMMMMMWW
WWWLLLLLLLLLLLLLLLLLLLLLMMLMMMWW
WWWMMMLLLLLLLLLLLLLLLLLLLLLLLLWW
WWWMMMMMMMMMLLLLLLLLLLLLLLLLLLWW
WWWLLLLLLMMMMLLLLLLLLLLLLLLLLLWW
WWWLLLLLLLLMMMLLLMMMLLLLLLLLLLWW
WWWLLLLLLLLLMMLLLMMMMMMMLLLLLLWW
WWWLLLLLLLLLMLLLLLMMMMMMLLLLLLWW
WWWGGGGGGLLLLLLLLLLLLLMMMMLLLLWW
WWWGGGGGGLLLLLLLLLLLLLLMMMLLLLWW
WWWGGGGGGLLLLLLLLLLLLLLLLLLLHLWW
WWWGGGGGGLLLLLLLLLLLLLLLLLLLL3WW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
)graph";
}

map::map map() { return map::read_map(graph_description); }
graphics::image dog_image() { return graphics::image{"resources/dog.png"}; }
graphics::image rabbit_image() { return graphics::image{"resources/rabbit.png"}; }
graphics::image misses_image() { return graphics::image{"resources/ms.png"}; }
graphics::image mister_image() { return graphics::image{ "resources/mr.png" }; }
graphics::image InvisibleImage() { return graphics::image{"resources/invisible.png" }; }

} // namespace rabbitisland

} // namespace kmint
