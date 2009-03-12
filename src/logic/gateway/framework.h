#ifndef GATEWAY_FRAMEWORK_H__
#define GATEWAY_FRAMEWORK_H__

#include "logic/client_logic.h"
#include "gateway/proto_network.h"
#include "gateway/scope_store.h"

namespace kumo {
namespace gateway {


class framework : public client_logic<framework> {
public:
	template <typename Config>
	framework(const Config& cfg);

	void dispatch(
			shared_session from, weak_responder response,
			rpc::method_id method, rpc::msgobj param, auto_zone z);

	void session_lost(const address& addr, shared_session& s);

	void step_timeout();

	// override wavy_server::run
	virtual void run();

public:
	void submit(get_request& req);
	void submit(set_request& req);
	void submit(delete_request& req);

private:
	proto_network m_proto_network;
	scope_store m_scope_store;

public:
	proto_network&   scope_proto_network()   { return m_proto_network;   }

public:
	shared_session get_server(const address& addr)
	{
		return get_session(addr);
	}

private:
	framework();
	framework(const framework&);
};


class resource {
public:
	template <typename Config>
	resource(const Config& cfg);

private:
	mp::pthread_rwlock m_hs_rwlock;
	HashSpace m_rhs;
	HashSpace m_whs;

	const address m_manager1;
	const address m_manager2;

	const bool m_cfg_async_replicate_set;
	const bool m_cfg_async_replicate_delete;

	const unsigned short m_cfg_get_retry_num;
	const unsigned short m_cfg_set_retry_num;
	const unsigned short m_cfg_delete_retry_num;

	const unsigned short m_cfg_renew_threshold;

public:
	RESOURCE_ACCESSOR(mp::pthread_rwlock, hs_rwlock);
	RESOURCE_ACCESSOR(HashSpace, rhs);
	RESOURCE_ACCESSOR(HashSpace, whs);

	RESOURCE_CONST_ACCESSOR(address, manager1);
	RESOURCE_CONST_ACCESSOR(address, manager2);

	RESOURCE_CONST_ACCESSOR(bool, cfg_async_replicate_set);
	RESOURCE_CONST_ACCESSOR(bool, cfg_async_replicate_delete);

	RESOURCE_CONST_ACCESSOR(unsigned short, cfg_get_retry_num);
	RESOURCE_CONST_ACCESSOR(unsigned short, cfg_set_retry_num);
	RESOURCE_CONST_ACCESSOR(unsigned short, cfg_delete_retry_num);

	RESOURCE_CONST_ACCESSOR(unsigned short, cfg_renew_threshold);

private:
	resource();
	resource(const resource&);
};


extern std::auto_ptr<framework> net;
extern std::auto_ptr<resource> share;


}  // namespace gateway
}  // namespace kumo

#endif  /* gateway/framework.h */

