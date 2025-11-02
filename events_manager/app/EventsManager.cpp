#include "EventsManager.h"

void EventsManager::SetNotifier(ForNotifying *receiver) {
  _notifier = receiver;
}

void EventsManager::ResetNotifier() { _notifier = nullptr; }

void EventsManager::SetController(ForControlling *controller) {
  _controller = controller;
}

void EventsManager::ResetController() { _controller = nullptr; }

void EventsManager::PushEvent(std::string_view topic,
                              std::string_view payload) {
  if (_notifier) {
    _notifier->NotifyEvent(topic, payload);
  }

  if (_controller) {
    _controller->OnEvent(topic, payload);
  }
}
