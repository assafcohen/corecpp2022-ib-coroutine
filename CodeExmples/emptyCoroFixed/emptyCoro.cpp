#include <iostream>
#include <string_view>
#include <source_location>
#include <coroutine>

void dodoLog(const std::source_location loc = std::source_location::current());

struct Operation
{
  struct promise_type
  {
    using Handle = std::coroutine_handle<promise_type>;

    Operation get_return_object()
    {
      dodoLog();
      return Operation { Handle::from_promise(*this) };
    }

    std::suspend_always initial_suspend()
    {
      dodoLog();
      return {};
    }

    std::suspend_never final_suspend() noexcept
    {
      dodoLog();
      return {};
    }

    void return_void()
    {
      dodoLog();
    }

    void unhandled_exception()
    {
      dodoLog();
    }

    promise_type()
    {
      dodoLog();
    }

    ~promise_type()
    {
      dodoLog();
    }
  };

  explicit Operation(promise_type::Handle coro) : coro_(coro)
  {
    dodoLog();
  }

  ~Operation()
  {
    dodoLog();
    if (coro_ && !coro_.done())
    {
      coro_.destroy();
    }
  }

  void destroy()
  {
    dodoLog();
    coro_.destroy();
  }

  void resume()
  {
    dodoLog();
    coro_.resume();
  }

private:
  promise_type::Handle coro_;
};

Operation emptyCoroutine()
{
  std::cerr << "Inside coroutine.\n";
  co_return;
}

std::int32_t main()
{
  std::cerr << "Before coroutine\n";
  auto c = emptyCoroutine();
  std::cerr << "After call, before resume.\n";
  c.resume();
  std::cerr << "After coroutine\n";
  return 0;
}

void dodoLog(const std::source_location location)
{
  std::cerr << location.function_name() << "\n";
};