#ifndef NET_YI_H
#define NET_YI_H

#include "macro.h"
#include "lib_client.h"
#include <string>
#include <functional>
#include <map>
#include <mutex>
#include <vector>
#include "libev_timer.hpp"

class netyi {
public:
  // call will stop if isStop not set false
  typedef std::function<void(const int16_t type, const std::string & data, bool * const isStop)>
    CB_Func_Mutiple;
  
  netyi(const std::string & certpath);
  void setNetIsReachable(bool isReachable);
  ~netyi();
  /*
   * netyi basic api
   * */ 
  void net_connect(std::vector<Buffer_SP> && ping_vec,
                   Client_CB client_callback,
                   CB_Func_Mutiple && pongfunc);
  // signup login connect
  // func(key, bool)
  void signup(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func);
  void login(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func);
  void connect(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func);
  // func(key, bool)
  void disconnect(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func);
  void logout(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func);
  // func(sessionid, bool)
  void send_buffer(std::vector<Buffer_SP> && sp_vec, int32_t * sessionid, CB_Func_Mutiple && func);
  /*
   * net noti
   * */
  // unread msg noti func(key)
  void acceptUnreadMsg(CB_Func_Mutiple && func);
  // other device loginNoti addFriendNoti addFriendAuthorizeNoti
  // func (key)
  void userInfoNoti(CB_Func_Mutiple && func);

private:
  void put_map(const int32_t sessionid, CB_Func_Mutiple && func);
  void put_map_send(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func,
                    int32_t * sessionid = nullptr);
  void put_map_send(const int32_t sessionid, 
      std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func);
  bool call_map(const int32_t sessionid, const std::vector<Buffer_SP> & sp_vec);
  void call_map_timeout(const int32_t sessionid);
private:
  std::string certpath_;
  std::mutex sessionid_map_mutex_;
  std::map<int32_t, CB_Func_Mutiple> sessionid_cbfunc_map_;
  Client_CB client_callback_;
  libev_timer * timer_;
};

#endif
