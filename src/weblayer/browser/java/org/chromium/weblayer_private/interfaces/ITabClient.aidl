// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.weblayer_private.interfaces;

import org.chromium.weblayer_private.interfaces.IObjectWrapper;

/**
 * Interface used by Tab to inform the client of changes. This largely duplicates the
 * TabCallback interface, but is a singleton to avoid unnecessary IPC.
 */
interface ITabClient {
  void visibleUriChanged(in String uriString) = 0;

  void onNewTab(in int tabId, in int mode) = 1;

  void onRenderProcessGone() = 2;

  void onCloseTab() = 3;

  // Added in M82.
  void showContextMenu(in IObjectWrapper pageUrl, in IObjectWrapper linkUrl,
      in IObjectWrapper linkText, in IObjectWrapper titleOrAltText) = 4;
}
