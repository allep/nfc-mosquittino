#include "EventsManager.h"

void EventsManager::SetNotifier(ForNotifying *receiver) {
  _notifier = receiver;
}

void EventsManager::SetController(ForControlling *controller) {
  _controller = controller;
}

void EventsManager::PushEvent(std::string topic, std::string payload) {
  if (_notifier) {
    _notifier->NotifyEvent(std::move(topic), std::move(payload));
  }

  if (_controller) {
    _controller->OnEvent();
  }
}
