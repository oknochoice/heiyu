//
//  netdb_yi.cpp
//  heibaiyu
//
//  Created by jiwei.wang on 2/9/17.
//  Copyright © 2017 yijian. All rights reserved.
//

#include "netdb_yi.hpp"
#include "buffer_yi_util.hpp"
#include <openssl/sha.h>

static const std::string netdb_success_ = "success";

netdb_yi::netdb_yi(const std::string & certpath, const std::string & dbpath, const std::string & phoneModel, const std::string & phoneUDID, const std::string & osVersion, const std::string & appVersion)
:model_(phoneModel), udid_(phoneUDID), os_version_(osVersion), app_version_(appVersion), certpath_(certpath) {
  YILOG_TRACE ("func: {}", __func__);
  isOpenNet_.store(false);
  dbyi_ = new leveldb_yi(dbpath);
  auto device = chat::Device();
  device.set_os(chat::Device_OperatingSystem::Device_OperatingSystem_iOS);
  device.set_devicemodel(model_);
  device.set_uuid(udid_);
  dbyi_->putCurrentDevice(device);
}

netdb_yi::~netdb_yi() {
  YILOG_TRACE ("func: {}", __func__);
  if (isOpenNet_.load()) {
    clear_client();
  }
  delete dbyi_;
}

void netdb_yi::openNet(Client_CB client_callback, CB_Func && pongback) {
  YILOG_TRACE ("func: {}", __func__);
  if (isOpenNet_.load()) {
    return;
  }
  netyi_ = new netyi(certpath_);
  client_callback_ = client_callback;
  auto ping = chat::Ping();
  ping.set_msg("ping");
  /*
#ifdef DEBUG
  ping.set_msg("pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping"
               "pingpingpingpingpingpingpingpingpingpingpingpingpingpingpingpingping");
#endif
   */
  netyi_->setNetIsReachable(true);
  netyi_->net_connect(yijianBuffer(ping), [this](const int error_no, const std::string & error_msg) {
    if (0 == error_no) {
      isOpenNet_.store(true);
      try {
        auto user = dbyi_->getCurrentUser();
        this->connect(user.id(), [this](const int err_no, const std::string & err_msg){
          client_callback_(err_no, err_msg);
        });
      } catch (...) {
        client_callback_(error_no, std::forward<const std::string>(error_msg));
      }
    }else{
      client_callback_(error_no, std::forward<const std::string>(error_msg));
    }
  }, [pongback = std::forward<CB_Func>(pongback)](const int16_t type, const std::string & data, bool * const isStop){
    if (!pongback) {
      return ;
    }
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      pongback(error.errnum(), error.errmsg());
    }else if(type == ChatType::pong) {
      auto res = chat::Pong();
      res.ParseFromString(data);
      pongback(0, res.msg());
    }else {
      YILOG_DEBUG("unknow type in pingpong");
    }
  });
}

void netdb_yi::netIsReachable(bool isreachable) {
  client_setNet_isConnect(isreachable);
}

void netdb_yi::closeNet() {
  YILOG_TRACE ("func: {}", __func__);
  isOpenNet_.store(false);
  clear_client();
}

leveldb_yi * netdb_yi::db() {
  YILOG_TRACE ("func: {}", __func__);
  return dbyi_;
}

/*
 * noti
 */
void netdb_yi::messageNoti(CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  netyi_->acceptUnreadMsg([this,callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if(type == ChatType::nodemessagenoti) {
      auto noti = chat::NodeMessageNoti();
      noti.ParseFromString(data);
      auto tonodeid = noti.tonodeid();
      this->getMessage(tonodeid, 0, noti.unreadincrement() + 1, [tonodeid, callback](const int err_no, const std::string & err_msg){
        if (0 == err_no) {
          callback(0, tonodeid);
        }else{
          callback(err_no, err_msg);
        }
      });
    }else {
      YILOG_DEBUG("message noti error unknow type");
    }
  });
}
// login noti add friend noti add friend authorize noti
void netdb_yi::userNoti(CB_Func && logincb, CB_Func && addfriendcb, CB_Func && addfriendauthorizecb) {
  YILOG_TRACE ("func: {}", __func__);
  netyi_->userInfoNoti([this, login = std::forward<CB_Func>(logincb),
                        addfriend = std::forward<CB_Func>(addfriendcb),
                        authorize = std::forward<CB_Func>(addfriendauthorizecb)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      YILOG_DEBUG("user noti error");
    }else if (type == ChatType::loginnoti) {
      login(0, netdb_success_);
    }else if (type == ChatType::addfriendnoti) {
      auto noti = chat::AddFriendNoti();
      auto friendid = noti.response().inviterid();
      this->getUser(friendid, [friendid, addfriend](const int err_no, const std::string & err_msg){
        if (0 == err_no) {
          addfriend(0, friendid);
        }else{
          addfriend(err_no, err_msg);
        }
      });
    }else if (type == ChatType::addfriendauthorizenoti) {
      auto noti = chat::AddFriendAuthorizeNoti();
      auto friendid = noti.response().inviteeid();
      this->getUser(friendid, [friendid, authorize](const int err_no, const std::string & err_msg){
        if (0 == err_no) {
          authorize(0, friendid);
        }else{
          authorize(err_no, err_msg);
        }
      });
    }else {
      YILOG_DEBUG("user noti error un know type");
    }
  });
}

/*
 * user
 */
void netdb_yi::registCheck(const std::string & phoneno, const std::string & countrycode, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto signup = chat::Register();
  signup.set_phoneno(phoneno);
  signup.set_countrycode(countrycode);
  netyi_->signup(yijianBuffer(signup), [callback = std::forward<CB_Func>(callback)](const int16_t type, const std::string & data, bool * const isStop) {
    if (type == ChatType::registorres) {
      auto res = chat::RegisterRes();
      res.ParseFromString(data);
      if (res.issuccess()) {
        callback(0, netdb_success_);
      }else{
        callback(res.e_no(), res.e_msg());
      }
    }else{
      callback(type, data);
    }
  });
}
void netdb_yi::regist(const std::string & phoneno, const std::string & countrycode, const std::string & password, const std::string & verifycode, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto signup = chat::Register();
  signup.set_phoneno(phoneno);
  signup.set_countrycode(countrycode);
  signup.set_password(password);
  signup.set_verifycode(verifycode);
  netyi_->signup(yijianBuffer(signup), [this, phoneno, countrycode, password, callback = std::forward<CB_Func>(callback)](const int16_t type, const std::string & data, bool * const isStop) {
    if (type == ChatType::registorres) {
      auto res = chat::RegisterRes();
      res.ParseFromString(data);
      if (res.issuccess()) {
        this->login(phoneno, countrycode, password, [this, callback](const int err_no, const std::string & err_msg) {
          callback(err_no, err_msg);
        });
      }else{
        callback(res.e_no(), res.e_msg());
      }
    }else{
      callback(type, data);
    }
  });
}
void netdb_yi::login(const std::string & phoneno, const std::string & countrycode, const std::string & password, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto login = chat::Login();
  login.set_phoneno(phoneno);
  login.set_countrycode(countrycode);
  login.set_password(password);
  auto md = login.mutable_device();
  (*md) = dbyi_->getCurrentDevice();
  netyi_->login(yijianBuffer(login), [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (type == ChatType::loginres) {
      auto res = chat::LoginRes();
      res.ParseFromString(data);
      if (res.issuccess()) {
        this->connect(res.userid(), [this, callback](const int err_no, const std::string & err_msg) {
          callback(err_no, err_msg);
        });
      }else{
        callback(res.e_no(), res.e_msg());
      }
    }else{
      callback(type, data);
    }
  });
}
void netdb_yi::connect(const std::string & userid, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto connect = chat::ClientConnect();
  connect.set_userid(userid);
  connect.set_uuid(udid_);
  connect.set_isrecivenoti(true);
  connect.set_clientversion("");
  connect.set_osversion(os_version_);
  connect.set_appversion(app_version_);
  netyi_->connect(yijianBuffer(connect), [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (type == ChatType::clientconnectres) {
      auto res = chat::ClientConnectRes();
      res.ParseFromString(data);
      if (res.issuccess()) {
        dbyi_->putCurrentUserid(res.userid());
        this->getUser(res.userid(), [this, callback](const int err_no, const std::string & err_msg) {
          callback(err_no, err_msg);
        });
      }else{
        callback(res.e_no(), res.e_msg());
      }
    }else {
      callback(type, data);
    }
  });
}
void netdb_yi::disconnect(CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto discon = chat::ClientDisConnect();
  discon.set_userid(dbyi_->getCurrentUserid());
  discon.set_uuid(udid_);
  netyi_->disconnect(yijianBuffer(discon), [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop){
    if (ChatType::error == type) {
      auto err = chat::Error();
      err.ParseFromString(data);
      callback(err.errnum(), err.errmsg());
    }else if (ChatType::clientdisconnectres == type){
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
void netdb_yi::logout(CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto logout = chat::Logout();
  logout.set_userid(dbyi_->getCurrentUserid());
  logout.set_uuid(udid_);
  netyi_->logout(yijianBuffer(logout), [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop){
    callback(0, netdb_success_);
    if (ChatType::error == type) {
      auto err = chat::Error();
      err.ParseFromString(data);
      callback(err.errnum(), err.errmsg());
    }else if(ChatType::logoutres == type){
      dbyi_->deleteCurrentUserid();
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
  
void netdb_yi::setUserProterty(const chat::SetUserProperty & property, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  netyi_->send_buffer(yijianBuffer(property), nullptr, [property, this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::setuserprotertyres) {
      /*
      auto userid = dbyi_->getCurrentUserid();
      this->getUser(userid, [callback](const int err_no, const std::string & data){
        callback(err_no, data);
      });
       */
      auto res = chat::SetUserPropertyRes();
      res.ParseFromString(data);
      auto user = dbyi_->getCurrentUser();
      switch (res.property()) {
        case chat::UserProperty::realname:
        {
          user.set_realname(res.value());
          break;
        }
        case chat::UserProperty::nickname:
        {
          user.set_nickname(res.value());
          break;
        }
        case chat::UserProperty::icon:
        {
          user.set_icon(res.value());
          break;
        }
        case chat::UserProperty::description:
        {
          user.set_description(res.value());
          break;
        }
        case chat::UserProperty::isMale:
        {
          if (res.value().front() == 't') {
            user.set_ismale(true);
          }else{
            user.set_ismale(false);
          }
          break;
        }
        case chat::UserProperty::birthday:
        {
          user.set_birthday(std::stoi(res.value()));
          break;
        }
        default:
          break;
      }
      user.set_version(user.version() + 1);
      dbyi_->putUser(user);
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
void netdb_yi::userSetRealname(const std::string & realname, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto property = chat::SetUserProperty();
  property.set_property(chat::UserProperty::realname);
  property.set_value(realname);
  setUserProterty(property, std::forward<CB_Func>(callback));
}
void netdb_yi::userSetNickname(const std::string & nickname, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto property = chat::SetUserProperty();
  property.set_property(chat::UserProperty::nickname);
  property.set_value(nickname);
  setUserProterty(property, std::forward<CB_Func>(callback));
}
void netdb_yi::userSetIcon(const std::string & icon, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto property = chat::SetUserProperty();
  property.set_property(chat::UserProperty::icon);
  property.set_value(icon);
  setUserProterty(property, std::forward<CB_Func>(callback));
}
void netdb_yi::userSetIsmale(bool isMale, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto property = chat::SetUserProperty();
  property.set_property(chat::UserProperty::isMale);
  if (isMale) {
    property.set_value("true");
  }else{
    property.set_value("false");
  }
  setUserProterty(property, std::forward<CB_Func>(callback));
}
void netdb_yi::userSetBirthday(int32_t birthdayTimestamp, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto property = chat::SetUserProperty();
  property.set_property(chat::UserProperty::birthday);
  property.set_value(std::to_string(birthdayTimestamp));
  setUserProterty(property, std::forward<CB_Func>(callback));
}
void netdb_yi::userSetDescription(const std::string & description, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto property = chat::SetUserProperty();
  property.set_property(chat::UserProperty::description);
  property.set_value(description);
  setUserProterty(property, std::forward<CB_Func>(callback));
}

void netdb_yi::addFriend(const std::string & friendid, const std::string & msg, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto query = chat::AddFriend();
  query.set_inviterid(dbyi_->getCurrentUserid());
  query.set_inviteeid(friendid);
  query.set_msg(msg);
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::addfriendres) {
      auto res = chat::AddFriendRes();
      res.ParseFromString(data);
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
void netdb_yi::addFriendAuthorize(const std::string & friendid, const bool isAgree, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto query = chat::AddFriendAuthorize();
  query.set_inviterid(dbyi_->getCurrentUserid());
  query.set_inviteeid(friendid);
  if (isAgree) {
    query.set_isagree(chat::IsAgree::agree);
  }else {
    query.set_isagree(chat::IsAgree::refuse);
  }
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::addfriendauthorizeres) {
      auto res = chat::AddFriendAuthorizeRes();
      res.ParseFromString(data);
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
  
}
void netdb_yi::getAddfriendInfo(CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto query = chat::QueryAddfriendInfo();
  query.set_count(50);
  addfriendInfo_.Clear();
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::queryaddfriendinfores) {
      auto res = chat::QueryAddfriendInfoRes();
      res.ParseFromString(data);
      dbyi_->putAddfriendInfo(res);
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
  
void netdb_yi::getUser(const std::string & userid, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  // get db user
  int32_t version = 0;
  try {
    auto user = dbyi_->getUser(userid);
    version = user.version();
  } catch (...) {
  }
  // query user version
  auto query = chat::QueryUserVersion();
  query.set_userid(userid);
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, version, userid, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::queryuserversionres) {
      auto res = chat::QueryUserVersionRes();
      res.ParseFromString(data);
      if (version < res.version()) {
        auto query = chat::QueryUser();
        query.set_userid(userid);
        netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback](int16_t type, const std::string & data, bool * isStop){
          if (0 == type) {
            auto error = chat::Error();
            error.ParseFromString(data);
            callback(error.errnum(), error.errmsg());
          }else {
            Assert(type == ChatType::queryuserres);
            auto res = chat::QueryUserRes();
            res.ParseFromString(data);
            dbyi_->putUser(res.user());
            callback(0, netdb_success_);
          }
        });
      }else {
        callback(0, netdb_success_);
      }
    }else {
      callback(type, data);
    }
  });
}
void netdb_yi::getUser(const std::string & phone, const std::string & countrycode, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto query = chat::QueryUser();
  query.set_userid(phone);
  query.set_countrycode(countrycode);
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop){
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::queryuserres) {
      auto res = chat::QueryUserRes();
      res.ParseFromString(data);
      dbyi_->putUser(res.user());
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
/*
 * media
 */
void netdb_yi::setMediaPath(const std::string & md5, const std::string & path, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto media = chat::Media();
  media.set_md5(md5);
  media.set_path(path);
  netyi_->send_buffer(yijianBuffer(media), nullptr, [this, callback = std::forward<CB_Func>(callback), &media](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::queryuserres) {
      dbyi_->putMediaPath(media);
    }else {
      callback(type, data);
    }
  });
}

void netdb_yi::getMediaPath(const std::string & md5, CB_Func &&callback) {
  YILOG_TRACE ("func: {}", __func__);
  try {
    dbyi_->getMediaPath(md5);
    callback(0, netdb_success_);
  } catch (...) {
    auto query = chat::QueryMedia();
    query.set_md5(md5);
    netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
      if (0 == type) {
        auto error = chat::Error();
        error.ParseFromString(data);
        callback(error.errnum(), error.errmsg());
      }else if (type == ChatType::querymediares) {
        auto res = chat::QueryMediaRes();
        dbyi_->putMediaPath(res.media());
        callback(0, netdb_success_);
      }else {
        callback(type, data);
      }
    });
  }
}
  

/*
 * message
 */
void netdb_yi::sendMessage(const std::string & toNodeID, const int32_t type,
                           const std::string & content, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto message = chat::NodeMessage();
  message.set_fromuserid(dbyi_->getCurrentUserid());
  message.set_tonodeid(toNodeID);
  message.set_type(static_cast<chat::MediaType>(type));
  message.set_content(content);
  netyi_->send_buffer(yijianBuffer(message), nullptr, [this, callback = std::forward<CB_Func>(callback), &message](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::queryuserres) {
      auto res = chat::NodeMessageRes();
      message.set_id(res.id());
      message.set_incrementid(res.incrementid());
      dbyi_->putMessage(message);
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
/*
void netdb_yi::queryOneMessage(const std::string & tonodeid, const int32_t increment, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  auto query = chat::QueryOneMessage();
  query.set_tonodeid(tonodeid);
  query.set_incrementid(increment);
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::querymessageres) {
      auto res = chat::QueryMessageRes();
      res.ParseFromString(data);
      for (auto & msg: res.messages()) {
        dbyi_->putMessage(msg);
      }
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}
 */
void netdb_yi::getMessage(const std::string & tonodeid, const int32_t fromIncrement,
                            const int32_t toIncrement, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  Assert(toIncrement >= fromIncrement);
  
  int32_t newFromIncrement = fromIncrement;
  if (toIncrement - fromIncrement > 50) {
    newFromIncrement = toIncrement - 50;
  }
  auto nodeinfo = dbyi_->getNodeinfo(tonodeid);
  if (newFromIncrement < nodeinfo.maxincrementid()) {
    newFromIncrement = nodeinfo.maxincrementid();
  }
  auto query = chat::QueryMessage();
  query.set_tonodeid(tonodeid);
  query.set_fromincrementid(newFromIncrement);
  query.set_toincrementid(toIncrement);
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, tonodeid, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::queryuserres) {
      auto res = chat::QueryMessageRes();
      res.ParseFromString(data);
      for (auto & msg: res.messages()) {
        dbyi_->putMessage(msg);
      }
      callback(0, netdb_success_);
    }else {
      callback(type, data);
    }
  });
}

void netdb_yi::getNode(const std::string & nodeid, CB_Func && callback) {
  YILOG_TRACE ("func: {}", __func__);
  int32_t version = 0;
  try {
    auto node = dbyi_->getMessageNode(nodeid);
    version = node.version();
  } catch (...) {
  }
  // query node version
  auto query = chat::QueryNodeVersion();
  query.set_tonodeid(nodeid);
  netyi_->send_buffer(yijianBuffer(query), nullptr, [this, version, callback = std::forward<CB_Func>(callback)](int16_t type, const std::string & data, bool * isStop) {
    if (0 == type) {
      auto error = chat::Error();
      error.ParseFromString(data);
      callback(error.errnum(), error.errmsg());
    }else if (type == ChatType::querynodeversionres) {
      auto res = chat::QueryNodeVersionRes();
      res.ParseFromString(data);
      if (version < res.version()) {
        auto query = chat::QueryNode();
        query.set_tonodeid(res.tonodeid());
        netyi_->send_buffer(yijianBuffer(query), nullptr, [this, callback](int16_t type, const std::string & data, bool * isStop) {
          if (0 == type) {
            auto error = chat::Error();
            error.ParseFromString(data);
            callback(error.errnum(), error.errmsg());
          }else {
            Assert(type == ChatType::querynoderes);
            auto res = chat::QueryNodeRes();
            res.ParseFromString(data);
            dbyi_->putMessageNode(res.node());
            callback(0, netdb_success_);
          }
        });
      }else {
        callback(0, netdb_success_);
      }
    }else {
      callback(type, data);
    }
  });
}

