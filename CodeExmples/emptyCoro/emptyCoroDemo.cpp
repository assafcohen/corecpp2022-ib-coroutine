#include <iostream>
#include <string_view>
#include <source_location>
#include <coroutine>

void doLog(const std::source_location loc=std::source_location::current());

struct Operation {

  struct promise_type {
    Operation get_return_object()                 {   doLog();  return {};  }
    std::suspend_never initial_suspend() noexcept {   doLog();  return {};  }
    std::suspend_never final_suspend() noexcept   {   doLog();  return {};  }
    void return_void()                            {   doLog();              }
    void unhandled_exception()                    {   doLog();              }
    promise_type()                                {   doLog();              }
    ~promise_type()                               {   doLog();              }
  };
  Operation() {    doLog();  }
  ~Operation() {    doLog();  }
};

Operation emptyCoroutine() {
  std::cerr << "Inside coroutine. \n";
  co_return;
}

int main() {
  std::cerr << "Before coroutine\n";
  auto c = emptyCoroutine();
  std::cerr << "After coroutine\n";
}

void doLog(const std::source_location location) {
  std::cerr << "Function " << location.function_name() <<":"<< location.line() << " called.\n";
};