#include <utility>
#include <memory>
#include <SFML/Graphics.hpp>


class Object {
    virtual bool is_visible(void);
    virtual bool is_physical(void);
    virtual bool is_interactive(void);

    virtual bool can_move(void);

    virtual std::tuple<int, int, int, int> get_position(void);
    virtual std::tuple<int, int> get_speed(void);
    virtual std::tuple<int, int> get_acceleration(void);
    virtual int get_weight(void);

    virtual int get_plan(void);

    virtual std::shared_ptr<sf::Drawable> get_screen_object(void);
};
