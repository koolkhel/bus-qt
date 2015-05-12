#ifndef MESSAGEFORMER_H
#define MESSAGEFORMER_H
#include <map>
#include <string>


class SubscribeDispatcher
{
  std::map<std::string, std::string> subscribers;
  //static SubscribeDispatcher* pInstance;

public:
    SubscribeDispatcher();
    //static SubscribeDispatcher* instance();

};

#endif // MESSAGEFORMER_H
