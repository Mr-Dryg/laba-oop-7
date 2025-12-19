#pragma once
#include <coroutine>
#include <exception>

struct MyCoroutine
{
    struct promise_type
    {
        MyCoroutine get_return_object()
        {
            return MyCoroutine{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int i = 0) { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> coro;

    MyCoroutine(std::coroutine_handle<promise_type> coro) : coro(coro) {}
    ~MyCoroutine() { if (coro) coro.destroy(); }

    bool resume()
    {
        if (!coro.done())
        {
            coro.resume();
            return !coro.done();
        }
        return false;
    }
};
