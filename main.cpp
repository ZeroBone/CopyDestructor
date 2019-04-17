#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

volatile int calls = 0;
std::mutex callsLock;

class Dragon {

    private:

    bool angry = true;
    int id;
    char name[128];

    public:

    explicit Dragon() : Dragon(10) {}
    explicit Dragon(int hp) : id(hp) {}

    ~Dragon() {

        using namespace std::chrono_literals;

        bool f = false;

        callsLock.lock();
        std::cout << "Calls: " << calls << " Dragon #" << id << " destructor called." << std::endl;

        if (calls == 0) {
            f = true;
        }
        else {
            calls--;
        }

        callsLock.unlock();

        std::thread([=]() {

            callsLock.lock();
            calls++;
            callsLock.unlock();

            std::unique_ptr<Dragon> dp1 = std::make_unique<Dragon>(id + 1);

            /*callsLock.lock();
            calls--;
            callsLock.unlock();*/

        }).detach();

        std::thread([=]() {

            callsLock.lock();
            calls++;
            callsLock.unlock();

            std::unique_ptr<Dragon> dp1 = std::make_unique<Dragon>(id - 1);

            /*callsLock.lock();
            calls--;
            callsLock.unlock();*/

        }).detach();

        if (f) {
            std::cout << "First time." << std::endl;

            while (true) {

                std::this_thread::sleep_for(2s);

                callsLock.lock();
                if (calls <= 0) {
                    // this will never happen, unfortunately...
                    callsLock.unlock();
                    break;
                }
                callsLock.unlock();

            }
        }

    }


};

int main() {

    std::cout << "Creating an immortal dragon..." << std::endl;

    Dragon* d = new Dragon();

    delete d;

    system("pause");

    return 0;

}