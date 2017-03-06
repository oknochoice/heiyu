#ifndef MACRO_H_YIJIAN
#define MACRO_H_YIJIAN

#include <assert.h>
//#include "spdlog/spdlog.h"
#include <inttypes.h>
#include <memory>
#include <system_error>
#define likely(x) __builtin_expect(!!(x),1)
#define unlikely(x) __builtin_expect(!!(x),0)

#define SERVER_NAME "yijian_1"
typedef int64_t Pointor_t;

#define TO_PEER_SERVER "to_peer_server_yijian"
#define TO_PEER_USER "to_peer_user_yijian"
#define TO_SPECIFY_USER "to_specify_user_yijian"

namespace yijian {

class noncopyable {
public:
	noncopyable() = default;
	noncopyable(const noncopyable &) = delete;
	noncopyable& operator=(const noncopyable&) = delete;
	noncopyable(noncopyable &&) = default;
	noncopyable& operator=(noncopyable&&) = default;
	virtual ~noncopyable() = default;
};

}

// c++11 thread-safe
void initConsoleLog();

#ifdef DEBUG
#define YILOG_ON
#define Assert(...) assert(__VA_ARGS__)
#else
#define Assert(...)
#endif

#ifdef YILOG_ON
#define YILOG_STR_H(x) #x
#define YILOG_STR_HELPER(x) YILOG_STR_H(x)
#define YILOG_TRACE(...) \
do{ \
time_t timer; \
char buffer[26]; \
struct tm* tm_info; \
time(&timer); \
tm_info = localtime(&timer); \
strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info); \
fprintf(stderr, "[%s]%s (%s, line %d): ", buffer, __func__, __FILE__, __LINE__); \
fprintf(stderr, "\n");} while(0)

#define YILOG_DEBUG(...) \
do{ \
time_t timer; \
char buffer[26]; \
struct tm* tm_info; \
time(&timer); \
tm_info = localtime(&timer); \
strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info); \
fprintf(stderr, "[%s]%s (%s, line %d): ", buffer, __func__, __FILE__, __LINE__); \
fprintf(stderr, __VA_ARGS__);           \
fprintf(stderr, "\n");} while(0)
#define YILOG_INFO(...)
#define YILOG_WARN(...)
#define YILOG_ERROR(...)
#define YILOG_CRITICAL(...)
#else
#define YILOG_TRACE(...) 
#define YILOG_DEBUG(...)
#define YILOG_INFO(...)
#define YILOG_WARN(...)
#define YILOG_ERROR(...)
#define YILOG_CRITICAL(...)
#endif

#define MQTT_BUFFER_SIZE (1024 * 2)
#define MQTT_SESSION_COUNT (20 * 1000)

#endif


