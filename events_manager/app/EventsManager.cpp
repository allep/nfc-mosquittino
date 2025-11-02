#include "EventsManager.h"

void EventsManager::AddNotifier(ForNotifying *receiver) {
  _notifier.Add(receiver);
}

void EventsManager::ResetNotifiers() { _notifier.RemoveAll(); }

void EventsManager::AddController(ForControlling *controller) {
  _controller.Add(controller);
}

void EventsManager::ResetControllers() { _controller.RemoveAll(); }

void EventsManager::PushEvent(std::string_view topic,
                              std::string_view payload) {
  for (auto n : _notifier) {
    n->NotifyEvent(topic, payload);
  }

  for (auto c : _controller) {
    c->OnEvent(topic, payload);
  }
}
