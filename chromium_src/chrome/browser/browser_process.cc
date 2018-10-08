// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/browser_process.h"

#include "chrome/browser/printing/print_job_manager.h"
#include "electron/buildflags/buildflags.h"
#include "ui/base/l10n/l10n_util.h"

BrowserProcess* g_browser_process = NULL;

BrowserProcess::BrowserProcess()
    : print_job_manager_(nullptr), icon_manager_(new IconManager) {
#if BUILDFLAG(ENABLE_PRINTING_ELECTRON)
  print_job_manager_.reset(new printing::PrintJobManager());
#endif
  g_browser_process = this;
}

BrowserProcess::~BrowserProcess() {
  g_browser_process = NULL;
}

void BrowserProcess::SetApplicationLocale(const std::string& locale) {
  locale_ = locale;
}

std::string BrowserProcess::GetApplicationLocale() {
  return locale_;
}

printing::PrintJobManager* BrowserProcess::print_job_manager() {
  return print_job_manager_.get();
}
