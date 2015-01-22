#ifndef BONEFISH_WAMP_ROUTER_HPP
#define BONEFISH_WAMP_ROUTER_HPP

#include <bonefish/identifiers/wamp_session_id.hpp>
#include <bonefish/roles/wamp_role.hpp>
#include <bonefish/wamp_uri.hpp>
#include <memory>
#include <unordered_set>
#include <unordered_map>

namespace bonefish {

class wamp_broker;
class wamp_dealer;
class wamp_hello_message;
class wamp_session;

class wamp_router
{
public:
    wamp_router(const wamp_uri& realm);
    ~wamp_router();

    const wamp_uri& get_realm() const;
    const std::unordered_set<wamp_role>& get_roles() const;
    bool add_role(const wamp_role& role);
    bool has_session(const wamp_session_id& id);
    bool attach_session(const std::shared_ptr<wamp_session>& session);
    bool detach_session(const wamp_session_id& id);

    void process_hello_message(const wamp_session_id& id,
            const wamp_hello_message* hello_message);

private:
    const std::string m_realm;
    std::unordered_set<wamp_role> m_roles;
    std::unique_ptr<wamp_broker> m_broker;
    std::unique_ptr<wamp_dealer> m_dealer;
    std::unordered_map<wamp_session_id, std::shared_ptr<wamp_session>> m_sessions;
};

} // namespace bonefish

#endif // BONEFISH_WAMP_ROUTER_HPP