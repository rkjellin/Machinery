#include "machineryplugin.h"
#include "machineryconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/mimedatabase.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QtPlugin>

using namespace Machinery::Internal;

MachineryPlugin::MachineryPlugin() {
  // Create your members
}

MachineryPlugin::~MachineryPlugin() {
  // Unregister objects from the plugin manager's object pool
  // Delete members
}

bool MachineryPlugin::initialize(const QStringList &arguments,
                                 QString *errorString) {
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize function, a plugin can be sure that the plugins it
  // depends on have initialized their members.

  Q_UNUSED(arguments)
  Q_UNUSED(errorString)

  if (!Core::MimeDatabase::addMimeTypes(tr("Rust.mimetypes.xml"), errorString)) {
      return false;
  }

  QAction *action = new QAction(tr("Machinery action"), this);
  Core::Command *cmd = Core::ActionManager::registerAction(
      action, Constants::ACTION_ID, Core::Context(Core::Constants::C_GLOBAL));
  cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
  connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));

  Core::ActionContainer *menu =
      Core::ActionManager::createMenu(Constants::MENU_ID);
  menu->menu()->setTitle(tr("Machinery"));
  menu->addAction(cmd);
  Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

  return true;
}

void MachineryPlugin::extensionsInitialized() {
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized function, a plugin can be sure that all
  // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag MachineryPlugin::aboutToShutdown() {
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

void MachineryPlugin::triggerAction() {
  QMessageBox::information(Core::ICore::mainWindow(), tr("Action triggered"),
                           tr("This is an action from Machinery."));
}

Q_EXPORT_PLUGIN2(Machinery, MachineryPlugin)
