#ifndef KMINT_RABBITISLAND_RABBIT_HPP
#define KMINT_RABBITISLAND_RABBIT_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>

namespace kmint {
namespace rabbitisland {

class rabbit : public play::free_roaming_actor {
public:
  rabbit();
  const ui::drawable &drawable() const override { return drawable_; }
  math::vector2d random_location();
  void act(delta_time dt) override;


  scalar perception_range() const override { return 50.0f; }
  scalar collision_range() const override { return 32.0f; }

  bool must_draw() const override { return alive; }
  bool incorporeal() const override { return !alive; }
  bool perceivable() const override { return alive; }
  bool perceptive() const override { return alive; }


private:
  play::image_drawable drawable_;
  bool alive;
};

} // namespace rabbitisland
} // namespace kmint

#endif /* KMINT_RABBITISLAND_RABBIT_HPP */
