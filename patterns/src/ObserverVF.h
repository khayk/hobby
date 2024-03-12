#pragma once

#include <stdexcept>
#include <vector>

namespace sj {

/**
 * @brief Generic observable class accept add/remove requests from
 *        the observers and enables notifying functionality
 *
 * @tparam Observer      Type of the observer.
 * @tparam ContainerType Type of the container.
 */
template <typename Observer, typename ContainerType = std::vector<Observer*>>
class Observable
{
public:
    using ObserverType = Observer;

    /**
     * @brief Add an observer
     *
     * @param obs An observer object.
     */
    void addObserver(Observer* obs)
    {
        if (obs)
        {
            obs_.push_back(obs);
        }
    }

    /**
     * @brief Remove an observer
     *
     * @param obs An observer object.
     */
    void removeObserver(Observer* obs) noexcept
    {
        if (obs)
        {
            if (auto it = std::find(std::begin(obs_), std::end(obs_), obs);
                std::end(obs_) != it)
            {
                *it = nullptr;
                dirty_ = true;
            }
        }
    }

    /**
     * @brief Notify observers about change, handle functions with any number of arguments
     *
     * @tparam Fn   Type of the function.
     * @tparam Args Type of the arguments.
     * @param fn    Pointer to member function to be called, it should be the part of an
     *              interface for the Observer type.
     * @param args  Variable arguments providing [in,out] The arguments.
     */
    template <typename Fn, typename... Args>
    void notifyObservers(Fn fn, Args&&... args)
    {
        for (auto* obs : obs_)
        {
            if (obs)
            {
                (obs->*fn)(std::forward<Args>(args)...);
            }
        }

        // Some observers are removed while we are notifying
        if (dirty_)
        {
            cleanup();
        }
    }

protected:
    ~Observable() = default;

private:
    ContainerType obs_;
    bool dirty_ {false};

    void cleanup()
    {
        std::erase_if(obs_, [](const Observer* obs) noexcept {
            return obs == nullptr;
        });
        dirty_ = false;
    }
};


/**
 * @brief Helper class to perform automatic add/remove on behalf of
 *        the observer during the lifetime of this class instance.
 *
 * @note Observable should be an instance of Observable<Observer> class
 */
template <typename Observer>
class ScopedObserve
{
    using ObservableType = Observable<Observer>;

    ObservableType* observable_ {nullptr};
    Observer* observer_ {nullptr};

public:
    /**
     * @brief Adds observer to listen events from observable during the construction
     *        and removes observer on destruction
     *
     * @throws std::invalid_argument if the observable is null.
     */
    ScopedObserve(ObservableType* observable, Observer* observer)
        : observable_(observable)
        , observer_(observer)
    {
        if (!observable_)
        {
            throw std::invalid_argument("Observable object is null.");
        }

        observable_->addObserver(observer_);
    }

    ~ScopedObserve()
    {
        observable_->removeObserver(observer_);
    }
};

} // namespace sj
