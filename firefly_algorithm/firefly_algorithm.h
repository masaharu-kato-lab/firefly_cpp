#pragma once
#include <vector>
#include <algorithm>
#include <functional>


template <class Value, class Param>
class FireflyAlgorithm {
public:
	using Index = std::size_t;
	
	struct Firefly {
		Index id;
		Param param;
		Value value;
	};

	struct Movement {
		Index i_iterates;
		Index i_updates;
		bool is_best;
		Firefly after;
	};

	struct Log {
		Index n_fireflies;
		std::vector<Movement> movements;
	};

	struct State {
		Index i_iterates;
		Index i_updates;
		Param best_param;
		Value best_value;
	};

	static Log firefly_algorithm(
		std::vector<Param> params,
		std::function<Value(const Param&)> calc_value,
		std::function<void(Firefly&, const Firefly&)> attract,
		std::function<bool(const State&)> continue_or_not
	) {

		std::vector<Firefly> fireflies;
		for(Param param : params) {
			fireflies.emplace_back(fireflies.size(), param, calc_value(param));
		}

		Log log;
		log.n_fireflies = fireflies.size();

		State state;
		state.i_iterates = 0;
		state.i_updates = 0;

		Firefly best_firefly;
		// TODO: calculate best firefly
		
		while(continue_or_not(state)) {

			std::sort(fireflies.begin(), fireflies.end(), [](Firefly ff1, Firefly ff2) -> bool {
				return ff1.value < ff2.value;
			});

			for(auto& i = fireflies.begin(); i < fireflies.end(); ++i) {
				for(auto& j = i + 1; j < firelifes.end(); ++j) {
					attract(*i, *j);
					if (i->value() > best_firefly.value()) {
						best_firefly = *i;
					}
					log.movements.emplace_back(
						state.i_iterates,
						state.i_updates,
						best_firefly.param,
						best_firefly.value
					)
					++state.i_updates;
				}
			}

			++state.i_iterates;
		}

		return log;
	}

};
