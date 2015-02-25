// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.domokit.sky.shell;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

/**
 * Main activity for SkyShell.
 */
public class SkyShellActivity extends Activity {
    /**
     * @see android.app.Activity#onCreate(android.os.Bundle)
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        String url = "https://domokit.github.io/home";
        Intent intent = getIntent();
        if (Intent.ACTION_VIEW.equals(intent.getAction())) {
            Uri skyUri = intent.getData();
            Uri httpsUri = skyUri.buildUpon().scheme("https").build();
            url = httpsUri.toString();
        }

        SkyMain.ensureInitialized(getApplicationContext());
        PlatformView view = new PlatformView(this);
        setContentView(view);
        view.loadUrl(url);
    }
}
