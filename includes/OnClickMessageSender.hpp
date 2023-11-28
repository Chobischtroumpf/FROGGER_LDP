#ifndef __ONMOVEMESSAGESENDER_HPP
#define __ONMOVEMESSAGESENDER_HPP

#include <Froggers.hpp>

class OnMoveMessageSender {
  std::String                 message;
  std::shared_ptr<MessageReceiver> receiver;

 protected:
  OnMoveMessageSender(const OnMoveMessageSender &)            = default;
  OnMoveMessageSender(OnMoveMessageSender &&)                 = default;
  OnMoveMessageSender &operator=(const OnMoveMessageSender &) = default;
  OnMoveMessageSender &operator=(OnMoveMessageSender &&)      = default;

 public:
  OnMoveMessageSender(string message, shared_ptr<MessageReceiver> receiver)
      : message{std::move(message)}, receiver{std::move(receiver)} {}
  void onClick() override { receiver->receiveMessage(message); }
  ~OnMoveMessageSender() override = default;
};

#endif  // !__ONMOVEMESSAGESENDER_HPP