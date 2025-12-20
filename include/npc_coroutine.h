#pragma once
#include <coroutine>
#include <exception>
#include <iostream>

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
    MyCoroutine(MyCoroutine&& other) noexcept : coro(other.coro) { other.coro = nullptr;}
    MyCoroutine(const MyCoroutine&) = delete;
    MyCoroutine& operator=(const MyCoroutine&) = delete;
    ~MyCoroutine() { if (coro) coro.destroy(); }

    bool resume()
    {
        // std::cout << "METKA 1\n";
        if (!coro.done())
        {
            // std::cout << "METKA 2\n";
            coro.resume();
            // std::cout << "METKA 3\n";
            return !coro.done();
        }
        // std::cout << "METKA 4\n";
        return false;
    }
};
