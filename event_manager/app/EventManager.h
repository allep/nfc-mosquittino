#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <string>

class EventManager {
public:
    void SetReceiver(ForNotifying* receiver);
    void PushEvent(std::string topic, std::string payload);

private:
  ForNotifying *_receiver{};
};

#endif
