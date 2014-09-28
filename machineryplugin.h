#ifndef MACHINERY_H
#define MACHINERY_H

#include "machinery_global.h"

#include <extensionsystem/iplugin.h>

namespace Machinery {
namespace Internal {

class MachineryPlugin : public ExtensionSystem::IPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE
                        "Machinery.json")

public:
  MachineryPlugin();
  ~MachineryPlugin();

  bool initialize(const QStringList &arguments, QString *errorString);
  void extensionsInitialized();
  ShutdownFlag aboutToShutdown();

private slots:
  void triggerAction();
};

} // namespace Internal
} // namespace Machinery

#endif // MACHINERY_H
