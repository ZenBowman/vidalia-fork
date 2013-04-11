#include "PortConfigurator.h"
#include <iostream>  
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <QCoreApplication>
#include "Vidalia.h"

static PortConfigurator *instance = 0;

void inform(std::string message) {
  vInfo(QString::fromStdString(message));
}

std::string getConfigurationFilename() {
  const std::string dataDirectory = QApplication::applicationDirPath().toStdString();
    //vApp->dataDirectory().toStdString();
#if defined(Q_OS_WIN32)
  return dataDirectory + "\\portConfiguration.txt";
#else 
  return dataDirectory + "/portConfiguration.txt";
#endif
}

QStringList* PortConfigurator::containerForLineType(std::string lineType) {
  if (lineType == "http") {
    return _httpPorts;
  } else if (lineType == "https") {
    return _httpsPorts;
  } else if (lineType == "mail") {
    return _mailPorts;
  } else if (lineType == "im") {
    return _imPorts;
  } else if (lineType == "irc") {
    return _ircPorts;
  }
  return 0;
}

void PortConfigurator::processLine(std::string lineData) {
  std::string lineType;
  std::stringstream lineReader;
  lineReader << lineData;
  lineReader >> lineType;
  vInfo(QString::fromStdString(lineType));
  QStringList* container = containerForLineType(lineType);
  if (container == 0) {
    vWarn("Unknown line type in configuration file");
  } else {
    std::string temp;
    while (lineReader.good()) {
      lineReader >> temp;
      container->append(temp.c_str());
      inform("Associated " + temp + " with " + lineType);
    }
  }
}

PortConfigurator::PortConfigurator() : _httpPorts(new QStringList()), _httpsPorts(new QStringList()), _mailPorts(new QStringList()),
				       _imPorts(new QStringList()), _ircPorts(new QStringList()) 
{
  vInfo("Initializing portconfig");
  const std::string configurationFilename = getConfigurationFilename(); 
  std::ifstream configurationFileReader;
  configurationFileReader.open(configurationFilename.c_str());
  std::string currentLine;
  if (configurationFileReader.is_open()) {
    while(configurationFileReader.good()) {
      std::getline(configurationFileReader, currentLine);
      processLine(currentLine);
    }
  }
  else {
    vError("Could not find configuration file, using default port settings");
    *_httpPorts << "80";
    *_httpsPorts << "443";
    *_mailPorts << "110" << "143" << "993" << "995";
    *_imPorts << "706" << "1863" << "5050" << "5190" << "5222" << "5223" << "8300" << "8888";
    *_ircPorts << "6660-6669" << "6697" << "7000-7001";
  }
}

PortConfigurator::~PortConfigurator() {
  delete _httpPorts;
  delete _httpsPorts;
  delete _mailPorts;
  delete _imPorts;
  delete _ircPorts;
}

PortConfigurator* PortConfigurator::getInstance() {
  if (instance == 0) {
    instance = new PortConfigurator();
  }
  return instance;
}

QStringList PortConfigurator::httpPorts() {
  return *_httpPorts;
}

QStringList PortConfigurator::httpsPorts() {
  return *_httpsPorts;
}

QStringList PortConfigurator::mailPorts() {
  return *_mailPorts;
}

QStringList PortConfigurator::imPorts() {
  return *_imPorts;
}

QStringList PortConfigurator::ircPorts() {
  return *_ircPorts;
}
