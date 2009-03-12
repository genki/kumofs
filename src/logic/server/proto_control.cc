#include "server/framework.h"
#include "server/proto_control.h"

namespace kumo {
namespace server {


RPC_IMPL(proto_control, CreateBackup_1, req, z, response)
try {
	std::string dst = share->cfg_db_backup_basename() + req.param().suffix;
	LOG_INFO("create backup: ",dst);

	share->db().backup(dst.c_str());

	response.result(true);
}
RPC_CATCH(CreateBackup, response)


RPC_IMPL(proto_control, GetStatus_1, req, z, response)
try {
	LOG_DEBUG("GetStatus_1");

	switch((status_type)req.param().command) {
	case STAT_PID:
		response.result((uint32_t)getpid());
		break;

	case STAT_UPTIME:
		response.result(time(NULL) - share->stat_start_time());
		break;

	case STAT_TIME:
		response.result((uint64_t)time(NULL));
		break;

	case STAT_VERSION:
		response.result(std::string(VERSION));
		break;

	case STAT_CMD_GET:
		response.result(share->stat_num_get());
		break;

	case STAT_CMD_SET:
		response.result(share->stat_num_set());
		break;

	case STAT_CMD_DELETE:
		response.result(share->stat_num_delete());
		break;

	case STAT_DB_ITEMS:
		response.result( share->db().rnum() );
		break;

	default:
		response.result(msgpack::type::nil());
		break;
	}
}
RPC_CATCH(GetStatus_1, response)



}  // namespace server
}  // namespace kumo

