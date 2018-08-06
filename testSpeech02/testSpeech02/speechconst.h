#ifndef SPEECHCONST_H
#define SPEECHCONST_H

#include <QString>

const QString CPressToSpeek    = QString::fromLocal8Bit("按住说话");
const QString CUpToEndSpeek    = QString::fromLocal8Bit("松开结束");
const QString CAnalyzingSpeech = QString::fromLocal8Bit("正在识别");

const QString CBaiduTokenUrl  = "https://aip.baidubce.com/oauth/2.0/token?";
const QString CBaiduTokenData = "grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString CBaiduClientSecret = "KtlySZ1eGGyOUbGnPm4kpozqt3kHsOUT";
const QString CBaiduClientId     = "x37eQHbPmTHPN0cRMCCM36fE";

const QString CBaiduIdentfySpeechUrl = "https://vop.baidu.com/server_api?dev_pid=1536&cuid=%1&token=%2";

const QString CBaiduComponseSpeechUrl = "https://tsn.baidu.com/text2audio";
const QString CBaiduComponseSpeechData = "tex=%1&lan=zh&cuid=%2&ctp=1&aue=3&tok=%3";
#endif