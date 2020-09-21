// Copyright (c) 2020, Qihoo, Inc.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TENSORNET_UTILITY_BLOCKING_QUEUE_H_
#define TENSORNET_UTILITY_BLOCKING_QUEUE_H_

#include <ctime>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;

namespace tensornet {

template<typename T>
class BlockingQueue {
public:
    BlockingQueue() {
    }

    ~BlockingQueue() {
    }

    BlockingQueue(const BlockingQueue&) = delete;

    BlockingQueue& operator=(const BlockingQueue&) = delete;

    void push(T&& value) {
        std::unique_lock<std::mutex> lock(mutex_);

        queue_.push_front(value);

        condition_.notify_one();
    }

    bool pop (T& value) {
        std::unique_lock<std::mutex> lock(mutex_);

        if (!condition_.wait_for(lock, 100ms, [this]{ return !queue_.empty(); })) {
            return false;
        }

        value = std::move(queue_.back());

        queue_.pop_back();

        return true;
    }

private:
    std::mutex mutex_;
    std::deque<T> queue_;
    std::condition_variable condition_;
};

} // namespace tensornet

#endif // TENSORNET_UTILITY_BLOCKING_QUEUE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
