#ifndef PLUGINSCENTER_
#define PLUGINSCENTER_

#include <QtGui/QWidget>
#include <QtCore/QMap>

namespace Ui {
class PluginsCenterData;
}

/**
  @brief The widget managing plugins installation.
  This widget is meant to list plugins available from several plugins repositories. Order them by categories and provide with a way to easily download and install them.
  The plugin center also displays detailed information about each plugin.

  @see PluginInformations
  */
class PluginsCenter: public QWidget {
  Q_OBJECT
public:
  explicit PluginsCenter(QWidget *parent=0);

  void setPluginsError(const QMap<QString,QString> &);

public slots:
  void showHomePage();
  void showSearchPage();
  void showErrorsPage();
  void showDownloadsPage();
  void showReposPage();

protected slots:
  void showPage(QWidget *page);
  void listItemSelected();

private:
  Ui::PluginsCenterData *_ui;
  QMap<QString,QString> _pluginsErrors;
};

#endif // PLUGINSCENTER_
