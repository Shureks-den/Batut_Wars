#pragma once

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "State.h"
#include "Holder.h"
#include "StateIdentifiers.h"

class StateStack : private sf::NonCopyable {
 public:
    enum Action {
        PUSH,
        POP,
        CLEAR,
    };

 public:
    explicit StateStack(State::Context context);
    ~StateStack() = default;

    template<typename T> void registrate(States::Id state_id);

    void update(sf::Time dt);
    void draw();
    void handle_event(const sf::Event &event);

    void push(States::Id state_id);
    void pop();
    void clear_states();

    bool is_empty() const;

 private:
    State::Ptr create_state(States::Id state_id);

    void apply_pending_changes();

 private:
    struct PendingChange {
        explicit PendingChange(Action action, States::Id state_id = States::NONE);
        Action action;
        States::Id state_id;
    };

 private:
    std::vector<State::Ptr> _stack;
    std::vector<PendingChange> _pending_list;
    State::Context _context;
    std::map<States::Id, std::function<State::Ptr()>> _factories;
};

template <typename T>
void StateStack::registrate(States::Id state_id) {
    _factories[state_id] = [this] () {
        return State::Ptr(new T(*this, _context));
    };
}
