#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/rabbitisland/rabbit.hpp"
#include <iostream>

namespace kmint {
namespace rabbitisland {
dog::dog(map::map_graph &g, map::map_node &initial_node)
    : play::map_bound_actor{initial_node}, drawable_{*this,
                                                     graphics::image{
                                                         dog_image()}} {}

void dog::act(delta_time dt) {
  t_passed_ += dt;
  if (to_seconds(t_passed_) >= waiting_time(node())) {
    // pick random edge
    int next_index = random_int(0, node().num_edges());
    this->node(node()[next_index].to());
    t_passed_ = from_seconds(0);   
  }

  // laat ook even zien welke konijntjes hij ruikt
  for (auto i = begin_perceived(); i != end_perceived(); ++i) {
    auto const &a = *i;
    if (auto const* p = dynamic_cast<rabbit const*>(&a); p) {
        std::cout << "Smelled something at " << a.location().x() << ", "
            << a.location().y() << "\n";
    }
  }
}

} // namespace rabbitisland
} // namespace kmint
