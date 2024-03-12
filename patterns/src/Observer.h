#pragma once

#include <unordered_set>
#include <vector>

// 1. Attach: Allow/Forbid attaching of the same observer multiple times
// 2. Detach: If we attached: detach, but what if it was added before? (locality)
//      2.1. What if the same observer attached again, while we are doing scoped observe?
//      2.2. Do we need to detach in the higher scope
// 3. Notify: What if an observer is added/remove in the middle of notify

namespace ptrn {

template <typename Subject>
class Observer
{
public:
    using OnUpdate = std::function<void(const Subject&)>;

    Observer(OnUpdate onUpdate)
        : onUpdate_(std::move(onUpdate))
    {
    }
    
    void update(const Subject& subject) const
    {
        onUpdate_(subject);
    }

private:
    OnUpdate onUpdate_;
};


template <typename Subject>
class VectorStorage
{
public:
    using ObserverPtr = Observer<Subject>*;

    bool add(ObserverPtr obs)
    {
        auto it = std::find(obs_.begin(), obs_.end(), obs);
        
        if (it != obs_.end())
        {
            return false;
        }
        
        obs_.push_back(obs);

        return true;
    }
    
    bool remove(ObserverPtr obs)
    {
        const auto it = std::remove(obs_.begin(), obs_.end(), obs);

        if (it == obs_.end())
        {
            return false;
        }

        obs_.erase(it, obs_.end());

        return true;
    }

    template <typename Callback>
    void enumerate(const Callback& cb)
    {
        for (auto obs : obs_)
        {
            ObserverPtr obsCpy = obs;
            cb(obsCpy);
        }
    }

private:
    std::vector<ObserverPtr> obs_;
};


template <typename Subject, 
          typename StorageStrategy = VectorStorage<Subject>>
class Observable
{
public:
    using ObserverPtr = typename StorageStrategy::ObserverPtr;

    bool attach(ObserverPtr obs)
    {
        return storage_.add(obs);
    }
    
    bool detach(ObserverPtr obs)
    {
        return storage_.remove(obs);
    }

protected:
    void notify(const Subject& subject)
    {
        storage_.enumerate([&subject](ObserverPtr obs) {
            obs->update(subject);
        });
    }

private:
    StorageStrategy storage_;
};

} // namespace ptrn