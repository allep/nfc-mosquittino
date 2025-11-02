#ifndef __FOR_CONFIGURING_PORT_H__
#define __FOR_CONFIGURING_PORT_H__

class ForNotifying;
class ForControlling;

class ForConfiguring {
public:
  virtual void SetNotifier(ForNotifying *receiver) = 0;
  virtual void ResetNotifier() = 0;

  virtual void SetController(ForControlling *controller) = 0;
  virtual void ResetController() = 0;
};

#endif

