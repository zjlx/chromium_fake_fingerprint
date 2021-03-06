// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/apps/launch_service/launch_manager.h"

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_navigator.h"
#include "chrome/browser/ui/browser_navigator_params.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/common/chrome_switches.h"
#include "chrome/common/webui_url_constants.h"
#include "ui/base/page_transition_types.h"
#include "url/gurl.h"

namespace apps {

LaunchManager::LaunchManager(Profile* profile) : profile_(profile) {}

LaunchManager::~LaunchManager() = default;

// static
std::vector<base::FilePath> LaunchManager::GetLaunchFilesFromCommandLine(
    const base::CommandLine& command_line) {
  std::vector<base::FilePath> launch_files;
  if (!command_line.HasSwitch(switches::kAppId))
    return launch_files;

  // Assume all args passed were intended as files to pass to the app.
  launch_files.reserve(command_line.GetArgs().size());
  for (const auto& arg : command_line.GetArgs()) {
    base::FilePath path(arg);
    if (path.empty())
      continue;

    launch_files.push_back(path);
  }

  return launch_files;
}

Browser* LaunchManager::CreateNewTabBrowser() {
  Browser::CreateParams create_params =
      Browser::CreateParams(profile_, /*user_gesture=*/false);
  Browser* browser = new Browser(create_params);

  NavigateParams params(browser, GURL(chrome::kChromeUINewTabURL),
                        ui::PAGE_TRANSITION_AUTO_TOPLEVEL);
  params.disposition = WindowOpenDisposition::NEW_FOREGROUND_TAB;
  params.tabstrip_add_types = TabStripModel::ADD_ACTIVE;
  Navigate(&params);

  browser->window()->Show();
  return browser;
}

}  // namespace apps
