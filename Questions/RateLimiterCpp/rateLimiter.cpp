#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;
using namespace std::chrono;

class TokenBucket {
private:
    int capacity;
    double refillRatePerSec;
    double tokens;
    steady_clock::time_point lastRefillTime;
    mutex mtx;

public:
    TokenBucket(int capacity, double refillRatePerSec)
        : capacity(capacity), refillRatePerSec(refillRatePerSec), tokens(capacity),
          lastRefillTime(steady_clock::now()) {}

    bool allowRequest() {
        lock_guard<mutex> lock(mtx);

        auto now = steady_clock::now();
        double secondsElapsed = duration_cast<duration<double>>(now - lastRefillTime).count();
        double newTokens = secondsElapsed * refillRatePerSec;

        tokens = min((double)capacity, tokens + newTokens);
        lastRefillTime = now;

        if (tokens >= 1) {
            tokens -= 1;
            return true;
        }
        return false;
    }
};

class RateLimiter {
private:
    unordered_map<string, TokenBucket*> userBuckets;
    int capacity;
    double refillRate;

public:
    RateLimiter(int capacity, double refillRate)
        : capacity(capacity), refillRate(refillRate) {}

    bool allow(string userId) {
        if (userBuckets.find(userId) == userBuckets.end()) {
            userBuckets[userId] = new TokenBucket(capacity, refillRate);
        }
        return userBuckets[userId]->allowRequest();
    }

    ~RateLimiter() {
        for (auto& pair : userBuckets) {
            delete pair.second;
        }
    }
};

// -------------------- Demo --------------------
int main() {
    RateLimiter rl(5, 1);  // 5 tokens max, 1 token per second

    string user = "user1";

    for (int i = 0; i < 10; ++i) {
        bool allowed = rl.allow(user);
        cout << "Request " << i + 1 << ": " << (allowed ? "Allowed" : "Blocked") << endl;
        this_thread::sleep_for(milliseconds(300));
    }

    return 0;
}
