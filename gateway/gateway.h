#ifndef GATEWAY_GATEWAY_H__
#define GATEWAY_GATEWAY_H__

#include "logic/gw.h"
#include "rpc/wavy.h"
#include <mp/utility.h>
#include <mp/memory.h>
#include <mp/zone.h>

namespace kumo {


class GatewayInterface {
public:
	GatewayInterface() { }
	virtual ~GatewayInterface() { }
	virtual void listen(Gateway* gw) = 0;
};

typedef rpc::wavy wavy;


}  // namespace user

#endif /* gateway/gateway.h */

