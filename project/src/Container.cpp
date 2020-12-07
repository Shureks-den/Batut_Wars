// TODO(shurek) поправить код-стайл ВЕЗДЕ

#include "Container.h"
#include "Foreach.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI {

    Container::Container()
            : _Children()
            , _SelectedChild(-1) {
    }

    void Container::pack(Component::Ptr component) {
        _Children.push_back(component);

        if (!hasSelection() && component->isSelectable())
            select(_Children.size() - 1);
    }

    bool Container::isSelectable() const {
        return false;
    }

    void Container::handleEvent(const sf::Event& event) {
        // If we have selected a child then give it events
        if (hasSelection() && _Children[_SelectedChild]->isActive()) {
            _Children[_SelectedChild]->handleEvent(event);
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                selectPrevious();
            } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                selectNext();
            } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                if (hasSelection())
                    _Children[_SelectedChild]->activate();
            }
        }
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        FOREACH(const Component::Ptr& child, _Children)
        target.draw(*child, states);
    }

    bool Container::hasSelection() const {
        return _SelectedChild >= 0;
    }

    void Container::select(std::size_t index) {
        if (_Children[index]->isSelectable()) {
            if (hasSelection())
                _Children[_SelectedChild]->deselect();

            _Children[index]->select();
            _SelectedChild = index;
        }
    }

    void Container::selectNext() {
        if (!hasSelection())
            return;

        // Search next component that is selectable, wrap around if necessary
        int next = _SelectedChild;
        do {
            next = (next + 1) % _Children.size();
        } while (!_Children[next]->isSelectable());

        // Select that component
        select(next);
    }

    void Container::selectPrevious() {
        if (!hasSelection()) {
            return;
        }
        // Search previous component that is selectable, wrap around if necessary
        int prev = _SelectedChild;
        do {
            prev = (prev + _Children.size() - 1) % _Children.size();
        } while (!_Children[prev]->isSelectable());

        // Select that component
        select(prev);
    }
}  // namespace GUI
