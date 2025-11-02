#ifndef __FOR_CONFIGURING_PORT_H__
#define __FOR_CONFIGURING_PORT_H__

class ForNotifying;
class ForControlling;

class ForConfiguring {
public:
  virtual void AddNotifier(ForNotifying *receiver) = 0;
  virtual void ResetNotifiers() = 0;

  virtual void AddController(ForControlling *controller) = 0;
  virtual void ResetControllers() = 0;
};

#endif

