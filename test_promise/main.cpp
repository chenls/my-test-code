#include <chrono>
#include <cstdio>
#include <future>
#include <iostream>
#include <thread>

std::mutex gPromiseMutex;
std::promise<void> gPromise;

void Thread_Fun1(std::promise<void> &promise) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  gPromiseMutex.lock();
  std::cout << "---------- " << std::endl;
  gPromise = std::promise<void>();
  gPromise.set_value();
  std::cout << "++++++++++1 " << &gPromise << std::endl;

  // gPromise = std::promise<void>();
  // gPromise.set_value();
  // std::cout << "++++++++++2 " << &gPromise << std::endl;
  gPromiseMutex.unlock();
}

void Thread_Fun2(std::promise<void> &promise) {
  //声明一个std::future对象fu1，并通过std::promise的get_future()函数与pr1绑定
  gPromiseMutex.lock();
  std::cout << "xxxxxxxxxx " << &gPromise << std::endl;
  std::future<void> future = gPromise.get_future();
  gPromiseMutex.unlock();

  //阻塞函数，直到收到相关联的std::promise对象传入的数据
  // auto iVal = f.get(); // iVal = 233
  if (future.valid()) {
    std::chrono::milliseconds timeout = std::chrono::seconds(3);
    auto expiration = std::chrono::system_clock::now() + timeout;
    std::future_status status = future.wait_until(expiration);
    gPromiseMutex.lock();
    gPromise = std::promise<void>();
    gPromiseMutex.unlock();
    if (status == std::future_status::timeout) {
      std::cout << "no status" << std::endl;
    } else if (status == std::future_status::ready) {
      std::cout << "收到数据(int)：" << std::endl;
    }
  }
}

int main() {
  //声明一个std::promise对象pr1，其保存的值类型为int

  //创建一个线程t1，将函数Thread_Fun1及对象pr1放在线程里面执行
  std::thread t1(Thread_Fun1, std::ref(gPromise));
  std::thread t11(Thread_Fun1, std::ref(gPromise));
  //创建一个线程t2，将函数Thread_Fun2及对象fu1放在线程里面执行
  std::thread t2(Thread_Fun2, std::ref(gPromise));

  //阻塞至线程结束
  t1.join();
  t11.join();
  t2.join();

  return 1;
}