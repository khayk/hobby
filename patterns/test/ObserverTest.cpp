#include <gtest/gtest.h>

#include "Observer.h"

#include <thread>
#include <chrono>
#include <atomic>

using namespace std::chrono_literals;

struct WeatherInfo
{
    int currentTemperature {30};
};

namespace ptrn {

class WeatherStation : public Observable<WeatherInfo>
{
    std::atomic_bool stopRequested_ {false};

public:
    void monitor()
    {
        stopRequested_ = false;
        WeatherInfo weather;

        while (!stopRequested_.load(std::memory_order_relaxed))
        {
            // std::this_thread::sleep_for(500ms);

            // const bool increase = (rand() % 2 == 0);
            // int delta           = (rand() % 3);
            // delta               = increase ? delta : -delta;
            // weather.currentTemperature += delta;

            notify(weather);
        }
    }

    void stop()
    {
        stopRequested_ = true;
    }
};

class MediaAgency : public Observer<WeatherInfo>
{
    int64_t updates_ {0};
    int lastValue_ {0};

public:
    MediaAgency()
        : Observer<WeatherInfo>([this](const WeatherInfo& wi) {
            onWeatherChanged(wi);
        })
    {
    }

    ~MediaAgency()
    {
        std::cout << "Received " << updates_ << " updates\n";
    }

    void onWeatherChanged(const WeatherInfo& wi)
    {
        std::ignore = wi;
        lastValue_  = wi.currentTemperature;
        ++updates_;
        // std::cout << "Temperature changed: " << wi.currentTemperature << std::endl;
    }

    int64_t updatesCount() const noexcept
    {
        return updates_;
    }

};


} // namespace ptrn 

/*
namespace sj {

class IWeatherInfo
{
public:
    virtual void onWeatherChanged(const WeatherInfo& wi) = 0;
};

class WeatherStation : public sj::Observable<IWeatherInfo>
{
    std::atomic_bool stopRequested_ {false};

public:
    void monitor()
    {
        stopRequested_ = false;
        WeatherInfo weather;

        while (!stopRequested_.load(std::memory_order_relaxed))
        {
            // std::this_thread::sleep_for(500ms);

            // const bool increase = (rand() % 2 == 0);
            // int delta           = (rand() % 3);
            // delta               = increase ? delta : -delta;
            // weather.currentTemperature += delta;

            notifyObservers(&IWeatherInfo::onWeatherChanged, weather);
        }
    }

    void stop()
    {
        stopRequested_ = true;
    }
};

class MediaAgency : public sj::IWeatherInfo
{
    int64_t updates_ {0};
    int lastValue_ {0};

public:
    MediaAgency()
    {
    }

    ~MediaAgency()
    {
        std::cout << "Received " << updates_ << " updates\n";
    }

    void onWeatherChanged(const WeatherInfo& wi) override
    {
        std::ignore = wi;
        lastValue_  = wi.currentTemperature;
        ++updates_;
        // std::cout << "Temperature changed: " << wi.currentTemperature << std::endl;
    }
};

} // namespace sj 

template <typename WS, typename MA>
void test()
{
    WS station;
    MA agency;

    station.addObserver(&agency);

    std::thread stopper([&station]() {
        std::this_thread::sleep_for(2000ms);
        station.stop();
    });

    station.monitor();
    stopper.join();
}*/

using namespace ptrn;

TEST(ObserverTest, Basics)
{
    WeatherStation station;
    MediaAgency agency;

    station.attach(&agency);

    std::thread stopper([&station, &agency]() {
        //std::this_thread::sleep_for(2000ms);

        station.stop();
    });

    station.monitor();
    stopper.join();
}
