#include <chrono>

class Timer {
public:
    Timer(){
        m_startTimePoint = std::chrono::high_resolution_clock::now(); //给我们current time
    }

    ~Timer () {
        stop();
    }
    void stop () {
        auto endTimePoint = std::chrono::high_resolution_clock::now();//默认按s算
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count(); // time_since_epoch 获得时间长度，cont取查数量
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
        auto duration = end - start;
        auto ms = duration * 0.001;
        std::cout << duration << "us" << "(" << ms << ")" << "ms" <<  std::endl;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
};

int main() {
    {
        Timer t;
        int val = 0;
        for (int i = 0; i < 1000000; i++) {
            val++;
        }
    }


    std::cout << "ENDING" << std::endl;
    return 0;
}
