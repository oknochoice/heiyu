//
//  leveldb_yi.cpp
//  heibaiyu
//
//  Created by jiwei.wang on 2/10/17.
//  Copyright © 2017 yijian. All rights reserved.
//

#include "leveldb_yi.hpp"
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <system_error>
#include "macro.h"

leveldb_yi::leveldb_yi(const std::string & dbpath) {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, dbpath, &db_);

  if (!status.ok()) {
    throw std::system_error(std::error_code(50000, 
          std::generic_category()),
       "open db failure");
  }
  
}

leveldb_yi::~leveldb_yi() {
  delete db_;
}

/*
 * user
 *
 * */
void leveldb_yi::putUser(const chat::User & user) {
  YILOG_TRACE ("func: {}", __func__);
  if (user.id().empty() || user.countrycode().empty() || user.phoneno().empty()) {
    throw std::system_error(std::error_code(50004,
          std::generic_category()),
        "parameter is empty");
  }
  auto userkey = userKey(user.id());
  auto phonekey = userPhoneKey(user.countrycode(), user.phoneno());
  leveldb::WriteBatch batch;
  batch.Put(phonekey, user.id());
  batch.Put(userkey, user.SerializeAsString());
  put(batch);
}

chat::User leveldb_yi::getUser(const std::string & id) {
  YILOG_TRACE ("func: {}", __func__);
  auto key = userKey(id);
  auto user_s = get(key);
  auto user = chat::User();
  user.ParseFromString(user_s);
  return user;
}

chat::User leveldb_yi::getUser(const std::string & countrycode,
                               const std::string & phoneno) {
  YILOG_TRACE ("func: {}", __func__);
  auto key = userPhoneKey(countrycode, phoneno);
  auto userid = get(key);
  return getUser(userid);
}
chat::User leveldb_yi::getCurrentUser() {
  YILOG_TRACE ("func: {}", __func__);
  return getUser(getCurrentUserid());
}
void leveldb_yi::putCurrentDevice(const chat::Device & device) {
  auto value = device.SerializeAsString();
  put("current_device", value);
}
chat::Device leveldb_yi::getCurrentDevice() {
  auto value = get("current_device");
  auto device = chat::Device();
  device.ParseFromString(value);
  return device;
}
void leveldb_yi::putCurrentUserid(const std::string & userid) {
  YILOG_TRACE ("func: {}", __func__);
  put("current_user", userid);
}void leveldb_yi::deleteCurrentUserid() {
  YILOG_TRACE ("func: {}", __func__);
  db_->Delete(leveldb::WriteOptions(), "current_user");
}
std::string leveldb_yi::getCurrentUserid() {
  YILOG_TRACE ("func: {}", __func__);
  return get("current_user");
}
/*
 * add friend info
 */
void leveldb_yi::putAddfriendInfo(const chat::QueryAddfriendInfoRes & info) {
  auto key = addFriendInfoKey();
  put(key, info.SerializeAsString());
}
chat::QueryAddfriendInfoRes leveldb_yi::getAddfriendInfo() {
  auto info_s = get(addFriendInfoKey());
  auto info = chat::QueryAddfriendInfoRes();
  info.ParseFromString(info_s);
  return info;
}

/*
 * media
 */
void leveldb_yi::putMediaPath(const chat::Media & media) {
  YILOG_TRACE ("func: {}", __func__);
  auto key = mediaKey(media.md5());
  put(key, media.path());
}
std::string leveldb_yi::getMediaPath(const std::string & md5) {
  YILOG_TRACE ("func: {}", __func__);
  auto key = mediaKey(md5);
  return get(key);
}


/*
 * message
 */
void leveldb_yi::putMessage(const chat::NodeMessage & message) {
  YILOG_TRACE ("func: {}", __func__);
  leveldb::WriteBatch batch;
  batch.Put(msgKey(message.tonodeid(), message.incrementid()), message.SerializeAsString());
  auto nodeinfo = getNodeinfo(message.tonodeid());
  if (nodeinfo.maxincrementid() < message.incrementid()) {
    nodeinfo.set_tonodeid(message.tonodeid());
    nodeinfo.set_maxincrementid(message.incrementid());
    nodeinfo.set_recenttimestamp(message.timestamp());
    batch.Put(nodeinfoKey(message.tonodeid()), nodeinfo.SerializeAsString());
  }
  put(batch);
}
chat::NodeMessage leveldb_yi::getMessage(const std::string & tonodeid, const int32_t incrementid) {
  YILOG_TRACE ("func: {}", __func__);
  auto msg = get(msgKey(tonodeid, incrementid));
  auto re = chat::NodeMessage();
  re.ParseFromString(msg);
  return re;
}
chat::NodeInfo leveldb_yi::getNodeinfo(const std::string & nodeid) noexcept {
  YILOG_TRACE ("func: {}", __func__);
  auto re = chat::NodeInfo();
  try {
    auto value = get(nodeinfoKey(nodeid));
    re.ParseFromString(value);
    return re;
  } catch (...) {
    return re;
  }
}
void leveldb_yi::putMessageNode(const chat::MessageNode & node) {
  YILOG_TRACE ("func: {}", __func__);
  put(nodeKey(node.id()), node.SerializeAsString());
}
chat::MessageNode leveldb_yi::getMessageNode(const std::string & nodeid) {
  YILOG_TRACE ("func: {}", __func__);
  auto value = get(nodeKey(nodeid));
  auto re = chat::MessageNode();
  re.ParseFromString(value);
  return re;
}
/*
 * talklist
 */
void leveldb_yi::putTalklist(const chat::TalkList & talklist) {
  YILOG_TRACE ("func: {}", __func__);
  put(talklistKey(), talklist.SerializeAsString());
}
chat::TalkList leveldb_yi::getTalklist() {
  YILOG_TRACE ("func: {}", __func__);
  std::string value;
  auto re = chat::TalkList();
  re.ParseFromString(value);
  return re;
}

/*
 * private
 */
// common
void leveldb_yi::put(const leveldb::Slice & key,
    const leveldb::Slice & value) {
  YILOG_TRACE ("func: {}", __func__);
  leveldb::WriteOptions write_options;
  auto status =  db_->Put(write_options, key, value);
  if (unlikely(!status.ok())) {
    throw std::system_error(std::error_code(50001,
          std::generic_category()),
        "put failure");
  }
}
std::string leveldb_yi::get(const leveldb::Slice & key) {
  YILOG_TRACE ("func: {}", __func__);
  std::string value;
  auto status = db_->Get(leveldb::ReadOptions(), key, &value);
  if (unlikely(!status.ok())) {
    throw std::system_error(std::error_code(50002,
          std::generic_category()),
        "get failure");
  }
  return value;
}
void leveldb_yi::put(leveldb::WriteBatch & batch) {
  YILOG_TRACE ("func: {}", __func__);
  auto status = db_->Write(leveldb::WriteOptions(), &batch);
  if (unlikely(!status.ok())) {
    throw std::system_error(std::error_code(50003,
          std::generic_category()),
        "put batch failure");
  }
}

std::string leveldb_yi::userKey(const std::string & userid) {
  YILOG_TRACE ("func: {}", __func__);
  return "u_" + userid;
}
std::string leveldb_yi::userPhoneKey(const std::string & countrycode,
    const std::string phoneno) {
  YILOG_TRACE ("func: {}", __func__);
  return "p_" + countrycode + "_" + phoneno;
}
std::string leveldb_yi::addFriendInfoKey() {
  YILOG_TRACE ("func: {}", __func__);
  return "addfriendinfo_leveldb_yi_" + getCurrentUserid();
}

std::string leveldb_yi::nodeKey(const std::string & tonodeid) {
  YILOG_TRACE ("func: {}", __func__);
  return "n_" + tonodeid;
}
std::string leveldb_yi::nodeinfoKey(const std::string & tonodeid) {
  YILOG_TRACE ("func: {}", __func__);
  return "ni_" + tonodeid;
}
std::string leveldb_yi::msgKey(const std::string & tonodeid,
    const std::string & incrementid) {
  YILOG_TRACE ("func: {}", __func__);
  return "m_" + tonodeid + "_" + incrementid;
}
std::string leveldb_yi::msgKey(const std::string & tonodeid,
    const int32_t incrementid) {
  return msgKey(tonodeid, std::to_string(incrementid));
}
std::string leveldb_yi::talklistKey() {
  YILOG_TRACE ("func: {}", __func__);
  return "t_" + getCurrentUserid();
}

/* media key
 */
std::string leveldb_yi::mediaKey(const std::string & md5) {
  YILOG_TRACE ("func: {}", __func__);
  return "m_md5_" + md5;
}
