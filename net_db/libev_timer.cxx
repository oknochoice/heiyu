//
//  libev_timer.cpp
//  heibaiyu
//
//  Created by jiwei.wang on 2/21/17.
//  Copyright © 2017 yijian. All rights reserved.
//

#include "libev_timer.hpp"
#include <thread>
#include <utility>
#include <vector>

libev_timer::libev_timer() {
  YILOG_TRACE ("func: {}", __func__);
  isLoopRunning_.store(false);
  isCallStop_.store(false);
  info_ = Timer_Info();
}

bool libev_timer::configure(double outtimer, double repeated,
              std::function<void(int32_t id)>&& callback) {
  YILOG_TRACE ("func: {}", __func__);
  
  if (isLoopRunning_.load()) {
    return false;
  }
  
  isLoopRunning_.store(true);
  repeated_ = repeated;
  outtimer_ = outtimer;
  callback_ = callback;
  std::thread t([&](){
    YILOG_TRACE ("func: {}, thread start.", __func__);
    try {
      loop_ = ev_default_loop();
      timer_ = (struct ev_timer*)malloc(sizeof(struct ev_timer));
      ev_timer_init(timer_, timer_callback, repeated_, 0.);
      command_ = (struct ev_async*)malloc(sizeof(struct ev_async));
      ev_async_init(command_ , (this->command_callback));
      ev_set_priority(command_ , EV_MAXPRI);
      ev_async_start(loop_, command_);
      ev_run(loop_, 0);
      free(timer_);
      free(command_);
      isLoopRunning_.store(false);
      YILOG_TRACE("exit thread");
    } catch (std::system_error & error) {
      YILOG_DEBUG("libev_timer error");
    }
    
  });
  t.detach();
  return true;
}

libev_timer::~libev_timer() {
  YILOG_TRACE ("func: {}", __func__);
  isCallStop_.store(true);
}


void libev_timer::put(int32_t id) {
  YILOG_TRACE ("func: {}", __func__);
  std::unique_lock<std::mutex> (map_mutex_);
  if (map_.empty()) {
    ev_async_send(loop_, command_);
  }
  info_.id = id;
  info_.timestamp = ev_now(loop_);
  map_[id] = info_;
}

void libev_timer::remove(int32_t id) {
  YILOG_TRACE ("func: {}", __func__);
  std::unique_lock<std::mutex> (map_mutex_);
  auto it = map_.find(id);
  if (it != map_.end()) {
    map_.erase(it);
  }
}


libev_timer* libev_timer::sharedTimer() {
  YILOG_TRACE ("func: {}", __func__);
  static libev_timer * re = new libev_timer();
  return re;
}
void libev_timer::command_callback(struct ev_loop * loop,  ev_async * w, int revents) {
  YILOG_TRACE ("func: {}", __func__);
  if (sharedTimer()->isCallStop_.load()) {
    // stop
    ev_async_stop(loop, sharedTimer()->command_);
    ev_timer_stop(loop, sharedTimer()->timer_);
    ev_loop_destroy(loop);
  }else {
    ev_timer_set(sharedTimer()->timer_, sharedTimer()->repeated_, 0.);
    ev_timer_start(loop, sharedTimer()->timer_);
  }
}
void libev_timer::timer_callback(struct ev_loop * loop,  ev_timer * w, int revents) {
  YILOG_TRACE ("func: {}", __func__);
  ev_timer_stop(loop, w);
  {
    std::unique_lock<std::mutex> (map_mutex_);
    double now = ev_now(loop);
    auto & localmap = sharedTimer()->map_;
    for (auto it = localmap.begin();
         it != localmap.end();) {
      YILOG_INFO("func: {}, timeout call", __func__);
      printf("timer_callback timeout call\n");
      auto ts = it->second.timestamp;
      if (now - ts >= sharedTimer()->outtimer_) {
        sharedTimer()->callback_(it->first);
        localmap.erase(it++);
      }else {
        ++it;
      }
    }
    if (!localmap.empty()) {
      ev_timer_set(w, sharedTimer()->repeated_, 0.);
      ev_timer_start(loop, w);
      YILOG_INFO("func: {}, timeout contine check", __func__);
      printf("timer_callback timeout contine check\n");
    }
  }
}
