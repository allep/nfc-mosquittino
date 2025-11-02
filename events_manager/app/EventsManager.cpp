#include "EventsManager.h"

void EventsManager::AddNotifier(ForNotifying *receiver) {
  _notifiers.Add(receiver);
}

void EventsManager::ResetNotifiers() { _notifiers.RemoveAll(); }

void EventsManager::AddController(ForControlling *controller) {
  _controllers.Add(controller);
}

void EventsManager::ResetControllers() { _controllers.RemoveAll(); }

void EventsManager::PushEvent(std::string_view topic,
                              std::string_view payload) {
  for (auto n : _notifiers) {
    n->NotifyEvent(topic, payload);
  }

  for (auto c : _controllers) {
    c->OnEvent(topic, payload);
  }
}
