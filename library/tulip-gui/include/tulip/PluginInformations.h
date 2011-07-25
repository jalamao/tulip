/**
 *
 * This file is part of Tulip (www.tulip-software.org)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux 1 and Inria Bordeaux - Sud Ouest
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#ifndef PLUGININFORMATIONS_H
#define PLUGININFORMATIONS_H

#include <QtCore/QDateTime>
#include <QtGui/QIcon>

#include <tulip/tulipconf.h>
#include <tulip/AbstractPluginInfo.h>
#include <tulip/WithDependency.h>
#include <QMap>

namespace tlp {

/**
  * @brief This implementation of AbstractPluginInfo represents a plugin located on a remote server, thus not yet installed.
  * All the informations are 'manually' entered into this class.
  *
  **/
class TLP_QT_SCOPE DistantPluginInfo : public tlp::AbstractPluginInfo {
public:
  DistantPluginInfo(const std::string& author, const std::string& date, const std::string& group, const std::string& name, const std::string& info, const std::string& release,
                    const std::string& tulipRelease, const std::list<tlp::Dependency> dependencies, const QString& type, const QString& location, const QString& remotepluginName)
    : _author(author), _date(date), _group(group), _name(name), _info(info), _release(release), _tulipRelease(tulipRelease), _dependencies(dependencies),
      _type(type), _location(location), _remotePluginName(remotepluginName) {
  }
  virtual std::string getAuthor() const {
    return _author;
  }
  virtual std::string getDate() const {
    return _date;
  }
  virtual std::string getGroup() const {
    return _group;
  }
  virtual std::string getName() const {
    return _name;
  }
  virtual std::string getInfo() const {
    return _info;
  }
  virtual std::string getRelease() const {
    return _release;
  }
  virtual std::string getTulipRelease() const {
    return _tulipRelease;
  }
  virtual std::list<tlp::Dependency> getDependencies() const {
    return _dependencies;
  }
  virtual const QString& getType() const {
    return _type;
  }
  virtual const QString& getLocation() const {
    return _location;
  }
  virtual const QString& getRemotePluginName() const {
    return _remotePluginName;
  }

private:
  const std::string _author;
  const std::string _date;
  const std::string _group;
  const std::string _name;
  const std::string _info;
  const std::string _release;
  const std::string _tulipRelease;
  const std::list<tlp::Dependency> _dependencies;
  const QString _type;
  const QString _location;
  const QString _remotePluginName;
};

/**
 * @brief Simple wrapper around AbstractPluginInfo to provide informations about updates and installation/removal functions.
 **/
class TLP_QT_SCOPE PluginInformations {
public:
  /**
    * @brief This constructor is used for local plugin description, and the library is used to determine the path of the icon and long description.
    *
    * @param info The AbstractPluginInfo representing the plugin to describe.
    * @param type The type of the plugin.
    * @param dependencies The dependencies of the plugin.
    * @param library The library file from which the plugin was loaded.
    **/
  PluginInformations(const tlp::AbstractPluginInfo& info, const std::string& type, const std::string& library);

  /**
    * @brief This constructor is used for remote plugin description, the long description and icon's paths are directly provided.
    *
    * @param info The AbstractPluginInfo representing the plugin to describe.
    * @param type The type of the plugin.
    * @param dependencies The dependencies of the plugin.
    * @param longDescriptionPath The URL where the long description resides.
    * @param iconPath The URL where the icon resides.
    **/
  PluginInformations(const tlp::AbstractPluginInfo& info, const QString& type, const QString& basePath, const QString& remotepluginName);

  /**
   * @brief This is used when a plugin is installed and available on a remote server.
   * If the remote version is greater than the local one, consider an update is available.
   *
   * @param info The PluginInfo of the remote plugin.
   * @return void
   **/
  void AddPluginInformations(const tlp::AbstractPluginInfo* info);

  QString identifier() const;
  //TODO this should be a displayname, not the name used to register into the plugin system
  QString name() const;
  QString author() const;
  QString group() const;

  QString shortDescription() const;
  QString longDescriptionPath() const;

  QString iconPath() const;
  QDateTime installDate() const;

  QString type() const;
  const QStringList dependencies() const;
  const QString& version() const;

  QString installedVersion() const;
  bool isInstalled() const;
  bool updateAvailable() const;

  QString latestVersion() const;

  bool fetch() const;
  void remove() const;
private:
  QString _lastVersion;
  const QString _type;
  const QString _iconPath;
  const QString _longDescriptionPath;
  const bool _isLocal;
  const QString _installedVersion;
  bool _updateAvailable;
  const QString _remoteLocation;
  const QString _remoteArchive;
  const QString _version;
  const tlp::AbstractPluginInfo* _infos;
  const QString _library;
};

}

#endif //PLUGININFORMATIONS_H
