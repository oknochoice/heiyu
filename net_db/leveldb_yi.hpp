//
//  leveldb_yi.hpp
//  heibaiyu
//
//  Created by jiwei.wang on 2/10/17.
//  Copyright © 2017 yijian. All rights reserved.
//

#ifndef leveldb_yi_hpp
#define leveldb_yi_hpp

#include <stdio.h>
#include <leveldb/db.h>
#include "chat_message.pb.h"

class leveldb_yi {
public:
  leveldb_yi(const std::string & dbpath);
  ~leveldb_yi();
  
  /*
   * user
   * */
  void putUser(const chat::User & user);
  chat::User getUser(const std::string & id);
  chat::User getUser(const std::string & countrycode,
               const std::string & phoneno);
  chat::User getCurrentUser();
  
  void putCurrentUserid(const std::string & userid);
  void deleteCurrentUserid();
  std::string getCurrentUserid();
  
  void putCurrentDevice(const chat::Device & device);
  chat::Device getCurrentDevice();
  
  /*
   * add friend info
   */
  void putAddfriendInfo(const chat::QueryAddfriendInfoRes & info);
  chat::QueryAddfriendInfoRes getAddfriendInfo();
  
  /*
   * media
   */
  void putMediaPath(const chat::Media & media);
  std::string getMediaPath(const std::string & md5);
  
  /*
   * message
   */
  void putMessage(const chat::NodeMessage & message);
  chat::NodeMessage getMessage(const std::string & tonodeid, const int32_t incrementid);
  chat::NodeInfo getNodeinfo(const std::string & nodeid) noexcept;
  void putMessageNode(const chat::MessageNode & node);
  chat::MessageNode getMessageNode(const std::string & nodeid);
  
  /*
   * talklist
   */
  void putTalklist(const chat::TalkList & talklist);
  chat::TalkList getTalklist();
  
  /*
   * common leveldb put get
   *
   * */
  void put(const leveldb::Slice & key,
      const leveldb::Slice & value);
  void put(leveldb::WriteBatch & batch);
  std::string get(const leveldb::Slice & key);

  /*
   * user key
   * */
  // u_$userid
  std::string userKey(const std::string & userid);
  // p_$code_$phoneno
  std::string userPhoneKey(const std::string & countrycode,
      const std::string phoneno);
  // addfriendinfo_kvdb_$currentuserid
  std::string addFriendInfoKey();
  /*
   * message key
   * */
  // n_$tonodeid
  std::string nodeKey(const std::string & tonodeid);
  std::string nodeinfoKey(const std::string & tonodeid);
  // m_$tonodeid_$incrementid
  std::string msgKey(const std::string & tonodeid,
      const std::string & incrementid);
  std::string msgKey(const std::string & tonodeid,
      const int32_t incrementid);
  // t_$userid
  std::string talklistKey();
  /*
   * error key
   * */
  // e_userid_$nth
  std::string errorKey(const std::string & userid,
      const int32_t nth);
  /* media key
   */
  std::string mediaKey(const std::string & md5);
  
private:
  leveldb::DB * db_;
};

#endif /* leveldb_yi_hpp */
