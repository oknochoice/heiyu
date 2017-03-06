//
//  libev_timer.hpp
//  heibaiyu
//
//  Created by jiwei.wang on 2/21/17.
//  Copyright © 2017 yijian. All rights reserved.
//

#ifndef libev_timer_hpp
#define libev_timer_hpp

#include <stdio.h>
#include <libev/ev.h>
#include <functional>
#include <map>
#include "macro.h"
#include <atomic>
#include <mutex>

class libev_timer {
public:
  static libev_timer* sharedTimer();
  bool configure(double outtimer, double repeated,
                 std::function<void(int32_t id)>&& callback);
  void put(int32_t id);
  void remove(int32_t id);
  ~libev_timer();
private:
  libev_timer();
  struct Timer_Info {
    int32_t id;
    double timestamp;// second
  };
  std::mutex map_mutex_;
  std::map<int32_t, Timer_Info> map_;
  struct ev_loop * loop_;
  struct ev_timer * timer_;
  struct ev_async * command_;
  static void command_callback(struct ev_loop * loop,  ev_async * w, int revents);
  static void timer_callback(struct ev_loop * loop,  ev_timer * w, int revents);
  Timer_Info info_;
  std::atomic_bool isLoopRunning_;
  std::atomic_bool isCallStop_;
  double outtimer_;
  double repeated_;
  std::function<void(int32_t)> callback_;
};

#endif /* libev_timer_hpp */
