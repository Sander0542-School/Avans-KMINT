#ifndef KMINT_RABBITISLAND_RESOURCES_HPP
#define KMINT_RABBITISLAND_RESOURCES_HPP

#include "kmint/graphics.hpp"
#include "kmint/map/map.hpp"
#include <vector>

namespace kmint {
namespace rabbitisland {

map::map map();
map::map SecondMap();
graphics::image dog_image();
graphics::image rabbit_image();
graphics::image misses_image();
graphics::image mister_image();
graphics::image InvisibleImage();


} // namespace rabbitisland
} // namespace kmint

#endif /* KMINT_RABBITISLAND_RESOURCES_HPP */
