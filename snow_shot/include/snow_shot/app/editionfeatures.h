#ifndef SNOW_SHOT_APP_EDITIONFEATURES_H
#define SNOW_SHOT_APP_EDITIONFEATURES_H

#include "snow_shot/app/edition.h"

#include <QString>

namespace snow_shot::app {
[[nodiscard]] inline bool editionActionToolAvailable(const QString& id) {
    if (id == QStringLiteral("pin-window-to-screen")) {
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
        return true;
#else
        return false;
#endif
    }
    if (id == QStringLiteral("airdrop")) {
#ifdef Q_OS_MACOS
        return true;
#else
        return false;
#endif
    }
    if (id == QStringLiteral("barcode-recognition"))
        return edition::qrRecognition;
    if (id == QStringLiteral("document-recognition"))
        return edition::documentRecognition;
    if (id == QStringLiteral("table-recognition"))
        return edition::tableRecognition;
    if (id == QStringLiteral("latex-recognition"))
        return edition::latexRecognition;
    if (id == QStringLiteral("convert-to-markdown") || id == QStringLiteral("convert-to-html"))
        return edition::imageConversion;
    if (id == QStringLiteral("text-recognition"))
        return edition::textRecognition;
    if (id == QStringLiteral("text-translation"))
        return edition::textTranslation;
    if (id == QStringLiteral("upload-to-cloud"))
        return edition::apiConfiguration && !edition::offline;
    return true;
}

[[nodiscard]] inline bool editionRecognitionModeAvailable(int mode) {
    switch (mode) {
    case 0:
        return true;
    case 1:
        return edition::tableRecognition;
    case 2:
        return edition::qrRecognition;
    case 3:
    case 4:
        return edition::imageConversion;
    case 5:
        return edition::latexRecognition;
    case 6:
        return edition::documentRecognition;
    default:
        return false;
    }
}

[[nodiscard]] inline bool editionConfigurationKeyAvailable(const QString& key) {
    if (!edition::apiConfiguration && key.startsWith(QStringLiteral("api_configuration/")))
        return false;
    if (!edition::textRecognition &&
        (key.startsWith(QStringLiteral("text_recognition/")) ||
         key == QStringLiteral("screenshot_shortcuts/text_recognition") ||
         key == QStringLiteral("pin_to_screen_shortcuts/show_text_recognition_results") ||
         key == QStringLiteral("pin_to_screen/text_selection_on_recognition_results") ||
         key == QStringLiteral("pin_to_screen/automatic_text_recognition") ||
         key == QStringLiteral("screenshot/auto_execute_after_text_recognition") ||
         key.endsWith(QStringLiteral("/screenshot_ocr")) ||
         key.endsWith(QStringLiteral("/screenshot_ocr_copy")) ||
         key.endsWith(QStringLiteral("/text_recognition"))))
        return false;
    if (edition::offline && key.startsWith(QStringLiteral("updates/")))
        return false;
    if (edition::offline && key.startsWith(QStringLiteral("mcp/")))
        return false;
    if (!edition::extendedFeatures && key.startsWith(QStringLiteral("extended_features/")))
        return false;
    if (!edition::textTranslation && (key == QStringLiteral("interface/translation_window_size") ||
                                      key.startsWith(QStringLiteral("screenshot_translation/")) ||
                                      key.endsWith(QStringLiteral("/screenshot_translation")) ||
                                      key.endsWith(QStringLiteral("/translate_selected_text")) ||
                                      key.endsWith(QStringLiteral("/text_translation"))))
        return false;
    if (!edition::qrRecognition && (key == QStringLiteral("screenshot/auto_recognize_qr_code") ||
                                    key.endsWith(QStringLiteral("/qr_code_recognition"))))
        return false;
    if (!edition::tableRecognition && key.endsWith(QStringLiteral("/table_recognition")))
        return false;
    if (!edition::tableRecognition && !edition::qrRecognition &&
        key == QStringLiteral("screenshot_toolbar/table_qr_tool"))
        return false;
    if (!edition::imageConversion && key.startsWith(QStringLiteral("screenshot_conversion/")))
        return false;
    return true;
}
} // namespace snow_shot::app

#endif // SNOW_SHOT_APP_EDITIONFEATURES_H
