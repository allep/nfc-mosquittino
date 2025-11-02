#ifndef __EVENTS_MANAGER_H__
#define __EVENTS_MANAGER_H__

// Inbound ports
#include "ForConfiguringPort.h"
#include "ForSendingEventsPort.h"

// Outbound ports
#include "ForControllingPort.h"
#include "ForNotifyingPort.h"

#include <string_view>

class EventsManager : public ForConfiguring, public ForProcessing {
public:
  void SetNotifier(ForNotifying *receiver) override;
  void ResetNotifier() override;

  void SetController(ForControlling *controller) override;
  void ResetController() override;

  void PushEvent(std::string_view topic, std::string_view payload) override;

private:
  ForNotifying *_notifier{};
  ForControlling *_controller{};
};

#endif
