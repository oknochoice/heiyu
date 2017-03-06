#include "net_yi.h"
#include "macro.h"
#include "typemap.h"
#include "buffer_yi.h"
#include <iostream>

using yijian::buffer;

enum Session_ID : int32_t {
  regist_id = -1,
  login_id = -2,
  connect_id = -3,
  disconnect_id = -4,
  logout_id = -5,
  accept_unread_msg_id = -6,
  user_noti_id = -7,
  ping_pong_id = -8
};

netyi::netyi(const std::string & certpath):
  certpath_(certpath){
  YILOG_TRACE ("func: {}", __func__);
  timer_ = libev_timer::sharedTimer();
  timer_->configure(10, 5, [this](auto id) {
    this->call_map_timeout(id);
  });
}

void netyi::setNetIsReachable(bool isReachable) {
  YILOG_TRACE ("func: {}", __func__);
  client_setNet_isConnect(isReachable);
}
netyi::~netyi() {
  YILOG_TRACE ("func: {}", __func__);
  delete timer_;
  clear_client();
}
/*
 * net func
 * */
void netyi::net_connect (std::vector<Buffer_SP> && ping_vec,
                         Client_CB client_callback,
                         CB_Func_Mutiple && pongfunc) {
  YILOG_TRACE ("func: {}", __func__);
  client_callback_ = client_callback;
  put_map(Session_ID::ping_pong_id, std::forward<CB_Func_Mutiple>(pongfunc));
  create_client(certpath_, ping_vec,
    [=](const std::vector<Buffer_SP> & sp_vec){
    YILOG_TRACE ("net callback");
    switch(sp_vec.back()->datatype()) {
      case ChatType::pong:
      {
        call_map(Session_ID::ping_pong_id, sp_vec);
        break;
      }
      case ChatType::loginnoti:
      case ChatType::addfriendnoti:
      case ChatType::addfriendauthorizenoti:
      {
        call_map(Session_ID::user_noti_id, sp_vec);
        break;
      }
      case ChatType::nodemessagenoti:
      {
        call_map(Session_ID::accept_unread_msg_id, sp_vec);
        break;
      }
      case ChatType::registorres:
      {
        call_map(Session_ID::regist_id, sp_vec);
        break;
      }
      case ChatType::loginres:
      {
        call_map(Session_ID::login_id, sp_vec);
        break;
      }
      case ChatType::clientconnectres:
      {
        call_map(Session_ID::connect_id, sp_vec);
        break;
      }
      case ChatType::logoutres:
      {
        call_map(Session_ID::logout_id, sp_vec);
        break;
      }
      case ChatType::clientdisconnectres:
      {
        call_map(Session_ID::disconnect_id, sp_vec);
        break;
      }
      default:
      call_map(sp_vec.back()->session_id(), sp_vec);
    }
  }, client_callback);
}


void netyi::signup(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map_send(Session_ID::regist_id, std::forward<std::vector<Buffer_SP>>(sp_vec),
      std::forward<CB_Func_Mutiple>(func));
}
void netyi::login(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map_send(Session_ID::login_id, std::forward<std::vector<Buffer_SP>>(sp_vec),
      std::forward<CB_Func_Mutiple>(func));
}
void netyi::connect(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map_send(Session_ID::connect_id, std::forward<std::vector<Buffer_SP>>(sp_vec),
      std::forward<CB_Func_Mutiple>(func));
}

void netyi::disconnect(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map_send(Session_ID::disconnect_id, std::forward<std::vector<Buffer_SP>>(sp_vec),
      std::forward<CB_Func_Mutiple>(func));
}
void netyi::logout(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map_send(Session_ID::logout_id, std::forward<std::vector<Buffer_SP>>(sp_vec),
      std::forward<CB_Func_Mutiple>(func));
}

void netyi::send_buffer(std::vector<Buffer_SP> && sp_vec, int32_t * sessionid, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map_send(std::forward<std::vector<Buffer_SP>>(sp_vec),
      std::forward<CB_Func_Mutiple>(func), sessionid);
}

/*
 * net noti
 *
 * */
// unread msg noti func(key)
void netyi::acceptUnreadMsg(CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map(Session_ID::accept_unread_msg_id,
      std::forward<CB_Func_Mutiple>(func));
}
// other device loginNoti addFriendNoti addFriendAuthorizeNoti
void netyi::userInfoNoti(CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  put_map(Session_ID::user_noti_id,
      std::forward<CB_Func_Mutiple>(func));
}

/*
 * private
 * */
void netyi::put_map(const int32_t sessionid, CB_Func_Mutiple && func) {
  YILOG_TRACE ("func: {}", __func__);
  std::unique_lock<std::mutex> ul(sessionid_map_mutex_);
  sessionid_cbfunc_map_[sessionid] = func;
}
void netyi::put_map_send(std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func, int32_t * sessionid) {
  YILOG_TRACE ("func: {}", __func__);
  if (!client_isWorking()) {
    bool isStop = true;
    std::string err_msg = "not reachable";
    func(-200, err_msg, &isStop);
  }
  uint16_t temp_session;
  {
    std::unique_lock<std::mutex> ul(sessionid_map_mutex_);
    client_send(std::forward<std::vector<Buffer_SP>>(sp_vec), &temp_session);
    if (likely(nullptr != sessionid)) {
      *sessionid = temp_session;
    }
    YILOG_TRACE ("func: {}, sessionid: {}", __func__, temp_session);
    sessionid_cbfunc_map_[temp_session] = func;
  }
  {
    timer_->put(temp_session);
  }
}
void netyi::put_map_send(const int32_t sessionid,
    std::vector<Buffer_SP> && sp_vec, CB_Func_Mutiple && func) {

  YILOG_TRACE ("func: {}", __func__);
  if (!client_isWorking()) {
    bool isStop = true;
    std::string err_msg = "not reachable";
    func(-200, err_msg, &isStop);
  }
  {
    std::unique_lock<std::mutex> ul(sessionid_map_mutex_);
    client_send(std::forward<std::vector<Buffer_SP>>(sp_vec), nullptr);
    sessionid_cbfunc_map_[sessionid] = func;
  }
  {
    timer_->put(sessionid);
  }
}
bool netyi::call_map(const int32_t sessionid, const std::vector<Buffer_SP> & sp_vec) {
  YILOG_TRACE ("func: {}", __func__);
  timer_->remove(sessionid);
  bool isCalled = false;
  auto lfunc = CB_Func_Mutiple();
  std::unique_lock<std::mutex> ul(sessionid_map_mutex_);
  auto it = sessionid_cbfunc_map_.find(sessionid);
  if (likely(it != sessionid_cbfunc_map_.end())) {
    lfunc = it->second;
  }else {
    YILOG_DEBUG ("user stop call back");
    std::string data = "user callback not find: not put map Or session id error";
    client_callback_(-1, data);
  }
  ul.unlock();
  if (lfunc) {
    bool isStop = true;
    std::string data;
    for (auto sp: sp_vec) {
      data.append(sp->data(), sp->data_size());
    }
    lfunc(sp_vec.back()->datatype(), data, &isStop);
    isCalled = true;
    if (isStop) {
      if (sessionid >= 0) {
        std::unique_lock<std::mutex> ul(sessionid_map_mutex_);
        sessionid_cbfunc_map_.erase(it);
      }
    }
  }else {
    YILOG_DEBUG ("callback func is nullptr");
  }
  return isCalled;
}

void netyi::call_map_timeout(const int32_t sessionid) {
  YILOG_TRACE ("func: {}", __func__);
  auto lfunc = CB_Func_Mutiple();
  {
    std::unique_lock<std::mutex> ul(sessionid_map_mutex_);
    auto it = sessionid_cbfunc_map_.find(sessionid);
    if (likely(it != sessionid_cbfunc_map_.end())) {
      lfunc = it->second;
      sessionid_cbfunc_map_.erase(it);
    }
  }
  if (lfunc) {
    bool isStop = true;
    std::string timeout = "timeout";
    lfunc(-100, timeout, &isStop);
  }
  
}

