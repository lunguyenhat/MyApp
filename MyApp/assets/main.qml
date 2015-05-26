/*
 * Copyright (c) 2013-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.3

Page {
    Container {
        Label {
            // Localized text with the dynamic translation and locale updates support
            text: qsTr("MyApp Service says Hello!") + Retranslate.onLocaleOrLanguageChanged
        }
      
        Button {
            id: resendAuthorization
            text: "Resend Authorization"
            onClicked: {
                app.resendAuthorization();
            }
        }
        
        Button {
            id: stopHeadless
            text: "Stop Headless"
            onClicked: {
                app.stopHeadless();
                //resendAuthorization.enabled = false;
                stopHeadless.enabled = false;
                startHeadless.enabled = true;
            }
        }
        Button {
            id: startHeadless
            text: "Start Headless"
            enabled: false
            onClicked: {
                app.startHeadless();
                resendAuthorization.enabled = true;
                stopHeadless.enabled = true;
                startHeadless.enabled = false;
            }
        }
        Button {
            id: resetAndQuit
            text: "Reset and Quit"
            onClicked: {
                if (stopHeadless.enabled) {
                    app.stopHeadless();                        
                }
                app.resetAndQuit();
            }
        }
    }
}
