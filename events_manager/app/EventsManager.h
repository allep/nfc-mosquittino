#ifndef __EVENTS_MANAGER_H__
#define __EVENTS_MANAGER_H__

#include "StaticContainer.h"

// Inbound ports
#include "ForConfiguringPort.h"
#include "ForSendingEventsPort.h"

// Outbound ports
#include "ForControllingPort.h"
#include "ForNotifyingPort.h"

#include <string_view>

class EventsManager : public ForConfiguring, public ForProcessing {
public:
  void AddNotifier(ForNotifying *receiver) override;
  void ResetNotifiers() override;

  void AddController(ForControlling *controller) override;
  void ResetControllers() override;

  void PushEvent(std::string_view topic, std::string_view payload) override;

private:
  StaticContainer<ForNotifying, 3> _notifiers{};
  StaticContainer<ForControlling, 3> _controllers{};
};

#endif
