#include <iostream>
#include <thread>
using namespace std;

/*
 thread指的是多线程同时并行执行代码的一种方式。
 通常情况下我们使用的是单线程，即我们写的每一行代码，都是逐行执行的，如果一行在等待，后面的行的代码就别想执行了。
 
 但是如果我们可以在主线程上，让某些功能在其他线程中完成。 这需要在主线程某个地方，产生分支，并在之后的某个地方重新加入回主线程。
 那么就要求在加回主线程的位置上，等待分线程完成，才能继续执行主线程
 */

static bool IsFinished = false;

void doWork(){
    using namespace std::literals::chrono_literals;
    
    cout << "the work is started" << endl;
    
    while (!IsFinished){
        cout << "working ..." << endl;
        std::this_thread::sleep_for(1s);   //sleep 1s
    }
    
    cout << "the work is finished" << endl;
}

void thread_tst(){
    //开启一个线程
    thread worker(doWork);  //线程的名字叫worker， 做的事情是doWork 这里采用的是functionptr来传递的
    std:cin.get();   // 这里一旦按了回车，就继续执行。
    IsFinished = true; // 按了回车以后，这个变量就是false了，支线的循环就结束了。
    
    worker.join();  //在这里worker就要回到主线任务上，如果没有回来，就要等他回来。因为后面等着他的结果
    
    cout << "the main thread is finished" << endl;
    
}
