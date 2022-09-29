#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Network::bindings
{
    void load_class_client_rename(sol::state_view state);
    void load_class_connected(sol::state_view state);
    void load_class_disconnected(sol::state_view state);
    void load_class_event_message(sol::state_view state);
    void load_class_message(sol::state_view state);
};