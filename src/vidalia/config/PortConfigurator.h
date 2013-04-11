#ifndef PORT_CONFIGURATOR_H
#define PORT_CONFIGURATOR_H

#include <string>
#include <QStringList>

class PortConfigurator
{
 public:
  static PortConfigurator* getInstance();
  QStringList httpPorts();
  QStringList httpsPorts();
  QStringList mailPorts();
  QStringList imPorts();
  QStringList ircPorts();
 ~PortConfigurator();

 private:
  PortConfigurator();
  QStringList* containerForLineType(std::string lineType);
  QStringList* _httpPorts;
  QStringList* _httpsPorts;
  QStringList* _mailPorts;
  QStringList* _imPorts;
  QStringList* _ircPorts;
  void processLine(std::string lineData);
};

#endif
