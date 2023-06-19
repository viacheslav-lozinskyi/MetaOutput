#pragma once

#include <metaplatform.core/All.hpp>

namespace atom
{
    MP_CLASS_SHARED Trace
    {
    public:
        MP_CLASS CONSTANT
        {
        public:
            MP_CLASS HMI
            {
                MP_CONSTANT_INTEGER(ACTION_FONT_SIZE, 20);
                MP_CONSTANT_INTEGER(ACTION_FOREGROUND, 0xFF8B0000);
                MP_CONSTANT_INTEGER(ACTION_MARGIN_Y, 19);
                MP_CONSTANT_INTEGER(ACTION_SIZE_Y, 64);
                MP_CONSTANT_INTEGER(ACTION_TRANSPARENCY, 90);
                MP_CONSTANT_STRING(BUTTON_FONT_NAME, "Arial");
                MP_CONSTANT_INTEGER(BUTTON_FONT_SIZE, 16);
                MP_CONSTANT_INTEGER(BUTTON_FOREGROUND, 0xFF000000);
                MP_CONSTANT_INTEGER(BUTTON_SIZE_X, 250);
                MP_CONSTANT_INTEGER(BUTTON_SIZE_Y, 30);
                MP_CONSTANT_INTEGER(DEFAULT_BACKGROUND, 0xFFFFFFFF);
                MP_CONSTANT_INTEGER(DEFAULT_PADDING, 5);
                MP_CONSTANT_INTEGER(DEFAULT_ROW_COUNT, 10);
                MP_CONSTANT_INTEGER(DEFAULT_TRANSPARENCY, 90);
                MP_CONSTANT_INTEGER(DELIMITER_MAX_MARGIN_Y, -40);
                MP_CONSTANT_INTEGER(DELIMITER_MAX_SIZE_Y, 1);
                MP_CONSTANT_INTEGER(DELIMITER_MIN_MARGIN_Y, 15);
                MP_CONSTANT_INTEGER(DELIMITER_MIN_SIZE_Y, 1);
                MP_CONSTANT_STRING(FOOTER_FONT_NAME, "Arial");
                MP_CONSTANT_INTEGER(FOOTER_FONT_SIZE, 12);
                MP_CONSTANT_INTEGER(FOOTER_FOREGROUND, 0xFF000000);
                MP_CONSTANT_INTEGER(FOOTER_SIZE_Y, 30);
                MP_CONSTANT_INTEGER(FOOTER_TRANSPARENCY, 70);
                MP_CONSTANT_STRING(HEADER_FONT_NAME, "Arial");
                MP_CONSTANT_INTEGER(HEADER_FONT_SIZE, 16);
                MP_CONSTANT_INTEGER(HEADER_FOREGROUND, 0xFF000000);
                MP_CONSTANT_INTEGER(HEADER_SIZE_Y, 30);
                MP_CONSTANT_INTEGER(LOGO_SIZE_X, 150);
                MP_CONSTANT_STRING(MESSAGE_FONT_NAME, "Arial");
                MP_CONSTANT_INTEGER(MESSAGE_FONT_SIZE, 14);
                MP_CONSTANT_INTEGER(MESSAGE_FOREGROUND, 0xFF8B0000);
                MP_CONSTANT_INTEGER(MESSAGE_MARGIN_Y, 10);
                MP_CONSTANT_INTEGER(MESSAGE_SIZE_Y, 20);
            };
        public:
            MP_CLASS OUTPUT
            {
                MP_CONSTANT_STRING(MUTEX, "urn:metaoutput:mutex:EXECUTE");
                MP_CONSTANT_STRING(REQUIREMENTS, "https://www.metaoutput.net/requirements");
                MP_CONSTANT_INTEGER(PREVIEW_FOREGROUND, Trace::NAME::COLOR::ORCHID);
                MP_CONSTANT_INTEGER(PREVIEW_ITEM_HEIGHT, 19);
                MP_CONSTANT_INTEGER(PREVIEW_MIN_SIZE, 2);
                MP_CONSTANT_INTEGER(PREVIEW_MIN_WIDTH, 200);
                MP_CONSTANT_INTEGER(PREVIEW_PAGE_INDENT, 10);
                MP_CONSTANT_INTEGER(PREVIEW_PAGE_BREAK, 7);
                MP_CONSTANT_INTEGER(MAX_BUFFER_SIZE, 100 * 1024 * 1024);
            };
        public:
            MP_CLASS PIPE
            {
                MP_CONSTANT_STRING(METAOUTPUT, "urn:metaoutput:pipe:DEFAULT");
                MP_CONSTANT_STRING(DEMO, "urn:metaoutput:pipe:DEMO");
                MP_CONSTANT_STRING(MUTEX, "urn:metaoutput:mutex:PIPE");
                MP_CONSTANT_STRING(TERMINATE_REQUEST, "urn:metaoutput:pipe:<<<CLIENT-TERMINATE>>>");
                MP_CONSTANT_INTEGER(BUFFER_SIZE, 256 * 1024);
                MP_CONSTANT_INTEGER(TIMEOUT, 100);
            };
        public:
            MP_CLASS PROGRESS
            {
                MP_CONSTANT_INTEGER(INFINITE, 101);
                MP_CONSTANT_INTEGER(REMOVE, -1);
            };
        public:
            MP_CLASS TML
            {
                MP_CONSTANT_STRING(ATTRIBUTE, "@@@");
                MP_CONSTANT_STRING(COMMENT, "/// ");
                MP_CONSTANT_STRING(GROUP_BEGIN, "<<<");
                MP_CONSTANT_STRING(GROUP_END, ">>>");
                MP_CONSTANT_STRING(NEW_LINE, "|||");
                MP_CONSTANT_STRING(PARAMETER, "@@");
                MP_CONSTANT_STRING(TRANSLATE_BEGIN, "[[[");
                MP_CONSTANT_STRING(TRANSLATE_END, "]]]");
                MP_CONSTANT_STRING(VARIABLE_BEGIN, "{{{");
                MP_CONSTANT_STRING(VARIABLE_END, "}}}");
            };
        };
    public:
        MP_CLASS NAME
        {
        public:
            MP_CLASS ALIGNMENT
            {
                MP_CONSTANT_INTEGER(NONE,          0x00);
                MP_CONSTANT_INTEGER(BOTTOM,        0x08);
                MP_CONSTANT_INTEGER(CENTER,        0x10);
                MP_CONSTANT_INTEGER(LEFT,          0x01);
                MP_CONSTANT_INTEGER(RIGHT,         0x02);
                MP_CONSTANT_INTEGER(TOP,           0x04);
                MP_CONSTANT_INTEGER(CENTER_LEFT,   CENTER | LEFT);
                MP_CONSTANT_INTEGER(CENTER_TOP,    CENTER | TOP);
                MP_CONSTANT_INTEGER(CENTER_RIGHT,  CENTER | RIGHT);
                MP_CONSTANT_INTEGER(CENTER_BOTTOM, CENTER | BOTTOM);
                MP_CONSTANT_INTEGER(CLIENT,        LEFT | TOP | RIGHT | BOTTOM);
                MP_CONSTANT_INTEGER(LEFT_BOTTOM,   LEFT | BOTTOM);
                MP_CONSTANT_INTEGER(LEFT_TOP,      LEFT | TOP);
                MP_CONSTANT_INTEGER(RIGHT_BOTTOM,  RIGHT | BOTTOM);
                MP_CONSTANT_INTEGER(RIGHT_TOP,     RIGHT | TOP);
            };
        public:
            MP_CLASS COLOR
            {
                MP_CONSTANT_INTEGER(ALICE_BLUE, 0xFFF0F8FF);              // #FFF0F8FF
                MP_CONSTANT_INTEGER(ANTIQUE_WHITE, 0xFFFAEBD7);           // #FFFAEBD7
                MP_CONSTANT_INTEGER(AQUA, 0xFF00FFFF);                    // #FF00FFFF
                MP_CONSTANT_INTEGER(AQUAMARINE, 0xFF7FFFD4);              // #FF7FFFD4
                MP_CONSTANT_INTEGER(AZURE, 0xFFF0FFFF);                   // #FFF0FFFF
                MP_CONSTANT_INTEGER(BEIGE, 0xFFF5F5DC);                   // #FFF5F5DC
                MP_CONSTANT_INTEGER(BISQUE, 0xFFFFE4C4);                  // #FFFFE4C4
                MP_CONSTANT_INTEGER(BLACK, 0xFF000000);                   // #FF000000
                MP_CONSTANT_INTEGER(BLANCHED_ALMOND, 0xFFFFEBCD);         // #FFFFEBCD
                MP_CONSTANT_INTEGER(BLUE_VIOLET, 0xFF8A2BE2);             // #FF8A2BE2
                MP_CONSTANT_INTEGER(BLUE, 0xFF0000FF);                    // #FF0000FF
                MP_CONSTANT_INTEGER(BROWN, 0xFFA52A2A);                   // #FFA52A2A
                MP_CONSTANT_INTEGER(BURLY_WOOD, 0xFFDEB887);              // #FFDEB887
                MP_CONSTANT_INTEGER(CADET_BLUE, 0xFF5F9EA0);              // #FF5F9EA0
                MP_CONSTANT_INTEGER(CHARTREUSE, 0xFF7FFF00);              // #FF7FFF00
                MP_CONSTANT_INTEGER(CHOCOLATE, 0xFFD2691E);               // #FFD2691E
                MP_CONSTANT_INTEGER(CORAL, 0xFFFF7F50);                   // #FFFF7F50
                MP_CONSTANT_INTEGER(CORNFLOWER_BLUE, 0xFF6495ED);         // #FF6495ED
                MP_CONSTANT_INTEGER(CORNSILK, 0xFFFFF8DC);                // #FFFFF8DC
                MP_CONSTANT_INTEGER(CRIMSON, 0xFFDC143C);                 // #FFDC143C
                MP_CONSTANT_INTEGER(CYAN, 0xFF00FFFF);                    // #FF00FFFF
                MP_CONSTANT_INTEGER(DARK_BLUE, 0xFF00008B);               // #FF00008B
                MP_CONSTANT_INTEGER(DARK_CYAN, 0xFF008B8B);               // #FF008B8B
                MP_CONSTANT_INTEGER(DARK_GOLDENROD, 0xFFB8860B);          // #FFB8860B
                MP_CONSTANT_INTEGER(DARK_GRAY, 0xFFA9A9A9);               // #FFA9A9A9
                MP_CONSTANT_INTEGER(DARK_GREEN, 0xFF006400);              // #FF006400
                MP_CONSTANT_INTEGER(DARK_KHAKI, 0xFFBDB76B);              // #FFBDB76B
                MP_CONSTANT_INTEGER(DARK_MAGENTA, 0xFF8B008B);            // #FF8B008B
                MP_CONSTANT_INTEGER(DARK_OLIVE_GREEN, 0xFF556B2F);        // #FF556B2F
                MP_CONSTANT_INTEGER(DARK_ORANGE, 0xFFFF8C00);             // #FFFF8C00
                MP_CONSTANT_INTEGER(DARK_ORCHID, 0xFF9932CC);             // #FF9932CC
                MP_CONSTANT_INTEGER(DARK_RED, 0xFF8B0000);                // #FF8B0000
                MP_CONSTANT_INTEGER(DARK_SALMON, 0xFFE9967A);             // #FFE9967A
                MP_CONSTANT_INTEGER(DARK_SEA_GREEN, 0xFF8FBC8F);          // #FF8FBC8F
                MP_CONSTANT_INTEGER(DARK_SLATE_BLUE, 0xFF483D8B);         // #FF483D8B
                MP_CONSTANT_INTEGER(DARK_SLATE_GRAY, 0xFF2F4F4F);         // #FF2F4F4F
                MP_CONSTANT_INTEGER(DARK_TURQUOISE, 0xFF00CED1);          // #FF00CED1
                MP_CONSTANT_INTEGER(DARK_VIOLET, 0xFF9400D3);             // #FF9400D3
                MP_CONSTANT_INTEGER(DEEP_PINK, 0xFFFF1493);               // #FFFF1493
                MP_CONSTANT_INTEGER(DEEP_SKY_BLUE, 0xFF00BFFF);           // #FF00BFFF
                MP_CONSTANT_INTEGER(DIM_GRAY, 0xFF696969);                // #FF696969
                MP_CONSTANT_INTEGER(DODGER_BLUE, 0xFF1E90FF);             // #FF1E90FF
                MP_CONSTANT_INTEGER(FIREBRICK, 0xFFB22222);               // #FFB22222
                MP_CONSTANT_INTEGER(FLORAL_WHITE, 0xFFFFFAF0);            // #FFFFFAF0
                MP_CONSTANT_INTEGER(FOREST_GREEN, 0xFF228B22);            // #FF228B22
                MP_CONSTANT_INTEGER(FUCHSIA, 0xFFFF00FF);                 // #FFFF00FF
                MP_CONSTANT_INTEGER(GAINSBORO, 0xFFDCDCDC);               // #FFDCDCDC
                MP_CONSTANT_INTEGER(GHOST_WHITE, 0xFFF8F8FF);             // #FFF8F8FF
                MP_CONSTANT_INTEGER(GOLD, 0xFFFFD700);                    // #FFFFD700
                MP_CONSTANT_INTEGER(GOLDENROD, 0xFFDAA520);               // #FFDAA520
                MP_CONSTANT_INTEGER(GRAY, 0xFF808080);                    // #FF808080
                MP_CONSTANT_INTEGER(GREEN_YELLOW, 0xFFADFF2F);            // #FFADFF2F
                MP_CONSTANT_INTEGER(GREEN, 0xFF008000);                   // #FF008000
                MP_CONSTANT_INTEGER(HONEYDEW, 0xFFF0FFF0);                // #FFF0FFF0
                MP_CONSTANT_INTEGER(HOT_PINK, 0xFFFF69B4);                // #FFFF69B4
                MP_CONSTANT_INTEGER(INDIAN_RED, 0xFFCD5C5C);              // #FFCD5C5C
                MP_CONSTANT_INTEGER(INDIGO, 0xFF4B0082);                  // #FF4B0082
                MP_CONSTANT_INTEGER(IVORY, 0xFFFFFFF0);                   // #FFFFFFF0
                MP_CONSTANT_INTEGER(KHAKI, 0xFFF0E68C);                   // #FFF0E68C
                MP_CONSTANT_INTEGER(LAVENDER_BLUSH, 0xFFFFF0F5);          // #FFFFF0F5
                MP_CONSTANT_INTEGER(LAVENDER, 0xFFE6E6FA);                // #FFE6E6FA
                MP_CONSTANT_INTEGER(LAWN_GREEN, 0xFF7CFC00);              // #FF7CFC00
                MP_CONSTANT_INTEGER(LEMON_CHIFFON, 0xFFFFFACD);           // #FFFFFACD
                MP_CONSTANT_INTEGER(LIGHT_BLUE, 0xFFADD8E6);              // #FFADD8E6
                MP_CONSTANT_INTEGER(LIGHT_CORAL, 0xFFF08080);             // #FFF08080
                MP_CONSTANT_INTEGER(LIGHT_CYAN, 0xFFE0FFFF);              // #FFE0FFFF
                MP_CONSTANT_INTEGER(LIGHT_GOLDENROD_YELLOW, 0xFFFAFAD2);  // #FFFAFAD2
                MP_CONSTANT_INTEGER(LIGHT_GRAY, 0xFFD3D3D3);              // #FFD3D3D3
                MP_CONSTANT_INTEGER(LIGHT_GREEN, 0xFF90EE90);             // #FF90EE90
                MP_CONSTANT_INTEGER(LIGHT_PINK, 0xFFFFB6C1);              // #FFFFB6C1
                MP_CONSTANT_INTEGER(LIGHT_SALMON, 0xFFFFA07A);            // #FFFFA07A
                MP_CONSTANT_INTEGER(LIGHT_SEA_GREEN, 0xFF20B2AA);         // #FF20B2AA
                MP_CONSTANT_INTEGER(LIGHT_SKY_BLUE, 0xFF87CEFA);          // #FF87CEFA
                MP_CONSTANT_INTEGER(LIGHT_SLATE_GRAY, 0xFF778899);        // #FF778899
                MP_CONSTANT_INTEGER(LIGHT_STEEL_BLUE, 0xFFB0C4DE);        // #FFB0C4DE
                MP_CONSTANT_INTEGER(LIGHT_YELLOW, 0xFFFFFFE0);            // #FFFFFFE0
                MP_CONSTANT_INTEGER(LIME_GREEN, 0xFF32CD32);              // #FF32CD32
                MP_CONSTANT_INTEGER(LIME, 0xFF00FF00);                    // #FF00FF00
                MP_CONSTANT_INTEGER(LINEN, 0xFFFAF0E6);                   // #FFFAF0E6
                MP_CONSTANT_INTEGER(MAGENTA, 0xFFFF00FF);                 // #FFFF00FF
                MP_CONSTANT_INTEGER(MAROON, 0xFF800000);                  // #FF800000
                MP_CONSTANT_INTEGER(MEDIUM_AQUAMARINE, 0xFF66CDAA);       // #FF66CDAA
                MP_CONSTANT_INTEGER(MEDIUM_BLUE, 0xFF0000CD);             // #FF0000CD
                MP_CONSTANT_INTEGER(MEDIUM_ORCHID, 0xFFBA55D3);           // #FFBA55D3
                MP_CONSTANT_INTEGER(MEDIUM_PURPLE, 0xFF9370DB);           // #FF9370DB
                MP_CONSTANT_INTEGER(MEDIUM_SEA_GREEN, 0xFF3CB371);        // #FF3CB371
                MP_CONSTANT_INTEGER(MEDIUM_SLATE_BLUE, 0xFF7B68EE);       // #FF7B68EE
                MP_CONSTANT_INTEGER(MEDIUM_SPRING_GREEN, 0xFF00FA9A);     // #FF00FA9A
                MP_CONSTANT_INTEGER(MEDIUM_TURQUOISE, 0xFF48D1CC);        // #FF48D1CC
                MP_CONSTANT_INTEGER(MEDIUM_VIOLET_RED, 0xFFC71585);       // #FFC71585
                MP_CONSTANT_INTEGER(MIDNIGHT_BLUE, 0xFF191970);           // #FF191970
                MP_CONSTANT_INTEGER(MINT_CREAM, 0xFFF5FFFA);              // #FFF5FFFA
                MP_CONSTANT_INTEGER(MISTY_ROSE, 0xFFFFE4E1);              // #FFFFE4E1
                MP_CONSTANT_INTEGER(MOCCASIN, 0xFFFFE4B5);                // #FFFFE4B5
                MP_CONSTANT_INTEGER(NAVAJO_WHITE, 0xFFFFDEAD);            // #FFFFDEAD
                MP_CONSTANT_INTEGER(NAVY, 0xFF000080);                    // #FF000080
                MP_CONSTANT_INTEGER(OLD_LACE, 0xFFFDF5E6);                // #FFFDF5E6
                MP_CONSTANT_INTEGER(OLIVE_DRAB, 0xFF6B8E23);              // #FF6B8E23
                MP_CONSTANT_INTEGER(OLIVE, 0xFF808000);                   // #FF808000
                MP_CONSTANT_INTEGER(ORANGE_RED, 0xFFFF4500);              // #FFFF4500
                MP_CONSTANT_INTEGER(ORANGE, 0xFFFFA500);                  // #FFFFA500
                MP_CONSTANT_INTEGER(ORCHID, 0xFFDA70D6);                  // #FFDA70D6
                MP_CONSTANT_INTEGER(PALE_GOLDENROD, 0xFFEEE8AA);          // #FFEEE8AA
                MP_CONSTANT_INTEGER(PALE_GREEN, 0xFF98FB98);              // #FF98FB98
                MP_CONSTANT_INTEGER(PALE_TURQUOISE, 0xFFAFEEEE);          // #FFAFEEEE
                MP_CONSTANT_INTEGER(PALE_VIOLET_RED, 0xFFDB7093);         // #FFDB7093
                MP_CONSTANT_INTEGER(PAPAYA_WHIP, 0xFFFFEFD5);             // #FFFFEFD5
                MP_CONSTANT_INTEGER(PEACH_PUFF, 0xFFFFDAB9);              // #FFFFDAB9
                MP_CONSTANT_INTEGER(PERU, 0xFFCD853F);                    // #FFCD853F
                MP_CONSTANT_INTEGER(PINK, 0xFFFFC0CB);                    // #FFFFC0CB
                MP_CONSTANT_INTEGER(PLUM, 0xFFDDA0DD);                    // #FFDDA0DD
                MP_CONSTANT_INTEGER(POWDER_BLUE, 0xFFB0E0E6);             // #FFB0E0E6
                MP_CONSTANT_INTEGER(PURPLE, 0xFF800080);                  // #FF800080
                MP_CONSTANT_INTEGER(RED, 0xFFFF0000);                     // #FFFF0000
                MP_CONSTANT_INTEGER(ROSY_BROWN, 0xFFBC8F8F);              // #FFBC8F8F
                MP_CONSTANT_INTEGER(ROYAL_BLUE, 0xFF4169E1);              // #FF4169E1
                MP_CONSTANT_INTEGER(SADDLE_BROWN, 0xFF8B4513);            // #FF8B4513
                MP_CONSTANT_INTEGER(SALMON, 0xFFFA8072);                  // #FFFA8072
                MP_CONSTANT_INTEGER(SANDY_BROWN, 0xFFF4A460);             // #FFF4A460
                MP_CONSTANT_INTEGER(SEA_GREEN, 0xFF2E8B57);               // #FF2E8B57
                MP_CONSTANT_INTEGER(SEA_SHELL, 0xFFFFF5EE);               // #FFFFF5EE
                MP_CONSTANT_INTEGER(SIENNA, 0xFFA0522D);                  // #FFA0522D
                MP_CONSTANT_INTEGER(SILVER, 0xFFC0C0C0);                  // #FFC0C0C0
                MP_CONSTANT_INTEGER(SKY_BLUE, 0xFF87CEEB);                // #FF87CEEB
                MP_CONSTANT_INTEGER(SLATE_BLUE, 0xFF6A5ACD);              // #FF6A5ACD
                MP_CONSTANT_INTEGER(SLATE_GRAY, 0xFF708090);              // #FF708090
                MP_CONSTANT_INTEGER(SNOW, 0xFFFFFAFA);                    // #FFFFFAFA
                MP_CONSTANT_INTEGER(SPRING_GREEN, 0xFF00FF7F);            // #FF00FF7F
                MP_CONSTANT_INTEGER(STEEL_BLUE, 0xFF4682B4);              // #FF4682B4
                MP_CONSTANT_INTEGER(TAN, 0xFFD2B48C);                     // #FFD2B48C
                MP_CONSTANT_INTEGER(TEAL, 0xFF008080);                    // #FF008080
                MP_CONSTANT_INTEGER(THISTLE, 0xFFD8BFD8);                 // #FFD8BFD8
                MP_CONSTANT_INTEGER(TOMATO, 0xFFFF6347);                  // #FFFF6347
                MP_CONSTANT_INTEGER(TRANSPARENT, 0x00FFFFFF);             // #00FFFFFF
                MP_CONSTANT_INTEGER(TURQUOISE, 0xFF40E0D0);               // #FF40E0D0
                MP_CONSTANT_INTEGER(VIOLET, 0xFFEE82EE);                  // #FFEE82EE
                MP_CONSTANT_INTEGER(WHEAT, 0xFFF5DEB3);                   // #FFF5DEB3
                MP_CONSTANT_INTEGER(WHITE_SMOKE, 0xFFF5F5F5);             // #FFF5F5F5
                MP_CONSTANT_INTEGER(WHITE, 0xFFFFFFFF);                   // #FFFFFFFF
                MP_CONSTANT_INTEGER(YELLOW_GREEN, 0xFF9ACD32);            // #FF9ACD32
                MP_CONSTANT_INTEGER(YELLOW, 0xFFFFFF00);                  // #FFFFFF00
            };
        public:
            MP_CLASS COMMAND
            {
            public:
                MP_CLASS COMMON
                {
                    MP_CONSTANT_STRING(EXPORT, "EXPORT");
                    MP_CONSTANT_STRING(IMPORT, "IMPORT");
                };
            public:
                MP_CLASS SOURCE
                {
                    MP_CONSTANT_STRING(APPEND, "SOURCE.APPEND");
                    MP_CONSTANT_STRING(CLEAR, "SOURCE.CLEAR");
                    MP_CONSTANT_STRING(REMOVE, "SOURCE.REMOVE");
                };
            public:
                MP_CLASS TERMINAL
                {
                    MP_CONSTANT_STRING(APPEND, "TERMINAL.APPEND");
                    MP_CONSTANT_STRING(REMOVE, "TERMINAL.REMOVE");
                };
            public:
                MP_CLASS TOOL
                {
                    MP_CONSTANT_STRING(APPEND, "TOOL.APPEND");
                    MP_CONSTANT_STRING(REMOVE, "TOOL.REMOVE");
                };
            public:
                MP_CLASS TRANSFORM
                {
                    MP_CONSTANT_STRING(APPEND, "TRANSFORM.APPEND");
                    MP_CONSTANT_STRING(REMOVE, "TRANSFORM.REMOVE");
                };
            public:
                MP_CLASS TRANSLATION
                {
                    MP_CONSTANT_STRING(APPEND, "TRANSLATION.APPEND");
                    MP_CONSTANT_STRING(REMOVE, "TRANSLATION.REMOVE");
                };
            public:
                MP_CLASS EVENT
                {
                    MP_CONSTANT_STRING(APPEND, "EVENT.APPEND");
                    MP_CONSTANT_STRING(REMOVE, "EVENT.REMOVE");
                };
            public:
                MP_CLASS VARIABLE
                {
                    MP_CONSTANT_STRING(APPEND, "VARIABLE.APPEND");
                    MP_CONSTANT_STRING(REMOVE, "VARIABLE.REMOVE");
                };
            };
        public:
            MP_CLASS CONDITION
            {
                MP_CONSTANT_STRING(CONTAINS, "CONTAINS");
                MP_CONSTANT_STRING(EMPTY, "EMPTY");
                MP_CONSTANT_STRING(EQUAL, "EQUAL");
                MP_CONSTANT_STRING(LESS, "LESS");
                MP_CONSTANT_STRING(LESS_EQUAL, "LESS.EQUAL");
                MP_CONSTANT_STRING(MORE, "MORE");
                MP_CONSTANT_STRING(MORE_EQUAL, "MORE.EQUAL");
                MP_CONSTANT_STRING(NOT_CONTAINS, "NOT.CONTAINS");
                MP_CONSTANT_STRING(NOT_EMPTY, "NOT.EMPTY");
                MP_CONSTANT_STRING(NOT_EQUAL, "NOT.EQUAL");
            };
        public:
            MP_CLASS CONTROL
            {
                MP_CONSTANT_STRING(AUDIO, "AUDIO");
                MP_CONSTANT_STRING(BROWSER, "BROWSER");
                MP_CONSTANT_STRING(BUTTON, "BUTTON");
                MP_CONSTANT_STRING(CANVAS, "CANVAS");
                MP_CONSTANT_STRING(CHART, "CHART");
                MP_CONSTANT_STRING(CHECKBOX, "CHECKBOX");
                MP_CONSTANT_STRING(COMBOBOX, "COMBOBOX");
                MP_CONSTANT_STRING(EDITBOX, "EDITBOX");
                MP_CONSTANT_STRING(GALLERY, "GALLERY");
                MP_CONSTANT_STRING(GAUGE, "GAUGE");
                MP_CONSTANT_STRING(ITEM, "ITEM");
                MP_CONSTANT_STRING(LABEL, "LABEL");
                MP_CONSTANT_STRING(PANEL, "PANEL");
                MP_CONSTANT_STRING(PICTURE, "PICTURE");
                MP_CONSTANT_STRING(PROGRESSBOX, "PROGRESSBOX");
                MP_CONSTANT_STRING(RADIOBOX, "RADIOBOX");
                MP_CONSTANT_STRING(SCROLLBOX, "SCROLLBOX");
                MP_CONSTANT_STRING(SLIDESHOW, "SLIDESHOW");
                MP_CONSTANT_STRING(SPLITTER, "SPLITTER");
                MP_CONSTANT_STRING(TABBOX, "TABBOX");
                MP_CONSTANT_STRING(TABLE, "TABLE");
                MP_CONSTANT_STRING(TEXTBOX, "TEXTBOX");
                MP_CONSTANT_STRING(TREE, "TREE");
                MP_CONSTANT_STRING(VIDEO, "VIDEO");
                MP_CONSTANT_STRING(WINDOW, "WINDOW");
            };
        public:
            MP_CLASS CULTURE
            {
                MP_CONSTANT_STRING(AFRIKAANS, "AF");
                MP_CONSTANT_STRING(AFRIKAANS_SOUTH_AFRICA, "AF-ZA");
                MP_CONSTANT_STRING(ALBANIAN, "SQ");
                MP_CONSTANT_STRING(ALBANIAN_ALBANIA, "SQ-AL");
                MP_CONSTANT_STRING(ARABIC, "AR");
                MP_CONSTANT_STRING(ARABIC_ALGERIA, "AR-DZ");
                MP_CONSTANT_STRING(ARABIC_BAHRAIN, "AR-BH");
                MP_CONSTANT_STRING(ARABIC_EGYPT, "AR-EG");
                MP_CONSTANT_STRING(ARABIC_IRAQ, "AR-IQ");
                MP_CONSTANT_STRING(ARABIC_JORDAN, "AR-JO");
                MP_CONSTANT_STRING(ARABIC_KUWAIT, "AR-KW");
                MP_CONSTANT_STRING(ARABIC_LEBANON, "AR-LB");
                MP_CONSTANT_STRING(ARABIC_LIBYA, "AR-LY");
                MP_CONSTANT_STRING(ARABIC_MOROCCO, "AR-MA");
                MP_CONSTANT_STRING(ARABIC_OMAN, "AR-OM");
                MP_CONSTANT_STRING(ARABIC_QATAR, "AR-QA");
                MP_CONSTANT_STRING(ARABIC_SAUDI_ARABIA, "AR-SA");
                MP_CONSTANT_STRING(ARABIC_SYRIA, "AR-SY");
                MP_CONSTANT_STRING(ARABIC_TUNISIA, "AR-TN");
                MP_CONSTANT_STRING(ARABIC_UNITED_ARAB_EMIRATES, "AR-AE");
                MP_CONSTANT_STRING(ARABIC_YEMEN, "AR-YE");
                MP_CONSTANT_STRING(ARMENIAN, "HY");
                MP_CONSTANT_STRING(ARMENIAN_ARMENIA, "HY-AM");
                MP_CONSTANT_STRING(AZERI_CYRILLIC, "CY-AZ");
                MP_CONSTANT_STRING(AZERI_CYRILLIC_AZERBAIJAN, "CY-AZ-AZ");
                MP_CONSTANT_STRING(AZERI_LATIN, "LT-AZ");
                MP_CONSTANT_STRING(AZERI_LATIN_AZERBAIJAN, "LT-AZ-AZ");
                MP_CONSTANT_STRING(BASQUE, "EU");
                MP_CONSTANT_STRING(BASQUE_BASQUE, "EU-ES");
                MP_CONSTANT_STRING(BELARUSIAN, "BE");
                MP_CONSTANT_STRING(BELARUSIAN_BELARUS, "BE-BY");
                MP_CONSTANT_STRING(BULGARIAN, "BG");
                MP_CONSTANT_STRING(BULGARIAN_BULGARIA, "BG-BG");
                MP_CONSTANT_STRING(CATALAN, "CA");
                MP_CONSTANT_STRING(CATALAN_CATALAN, "CA-ES");
                MP_CONSTANT_STRING(CHINESE, "ZH");
                MP_CONSTANT_STRING(CHINESE_CHINA, "ZH-CN");
                MP_CONSTANT_STRING(CHINESE_HONG_KONG_SAR, "ZH-HK");
                MP_CONSTANT_STRING(CHINESE_MACAU_SAR, "ZH-MO");
                MP_CONSTANT_STRING(CHINESE_SIMPLIFIED, "ZH-CHS");
                MP_CONSTANT_STRING(CHINESE_SINGAPORE, "ZH-SG");
                MP_CONSTANT_STRING(CHINESE_TAIWAN, "ZH-TW");
                MP_CONSTANT_STRING(CHINESE_TRADITIONAL, "ZH-CHT");
                MP_CONSTANT_STRING(CROATIAN, "HR");
                MP_CONSTANT_STRING(CROATIAN_CROATIA, "HR-HR");
                MP_CONSTANT_STRING(CZECH, "CS");
                MP_CONSTANT_STRING(CZECH_CZECH_REPUBLIC, "CS-CZ");
                MP_CONSTANT_STRING(DANISH, "DA");
                MP_CONSTANT_STRING(DANISH_DENMARK, "DA-DK");
                MP_CONSTANT_STRING(DHIVEHI, "DIV");
                MP_CONSTANT_STRING(DHIVEHI_MALDIVES, "DIV-MV");
                MP_CONSTANT_STRING(DUTCH, "NL");
                MP_CONSTANT_STRING(DUTCH_BELGIUM, "NL-BE");
                MP_CONSTANT_STRING(DUTCH_THE_NETHERLANDS, "NL-NL");
                MP_CONSTANT_STRING(ENGLISH, "EN");
                MP_CONSTANT_STRING(ENGLISH_AUSTRALIA, "EN-AU");
                MP_CONSTANT_STRING(ENGLISH_BELIZE, "EN-BZ");
                MP_CONSTANT_STRING(ENGLISH_CANADA, "EN-CA");
                MP_CONSTANT_STRING(ENGLISH_CARIBBEAN, "EN-CB");
                MP_CONSTANT_STRING(ENGLISH_IRELAND, "EN-IE");
                MP_CONSTANT_STRING(ENGLISH_JAMAICA, "EN-JM");
                MP_CONSTANT_STRING(ENGLISH_NEW_ZEALAND, "EN-NZ");
                MP_CONSTANT_STRING(ENGLISH_PHILIPPINES, "EN-PH");
                MP_CONSTANT_STRING(ENGLISH_SOUTH_AFRICA, "EN-ZA");
                MP_CONSTANT_STRING(ENGLISH_TRINIDAD_AND_TOBAGO, "EN-TT");
                MP_CONSTANT_STRING(ENGLISH_UNITED_KINGDOM, "EN-GB");
                MP_CONSTANT_STRING(ENGLISH_UNITED_STATES, "EN-US");
                MP_CONSTANT_STRING(ENGLISH_ZIMBABWE, "EN-ZW");
                MP_CONSTANT_STRING(ESTONIAN, "ET");
                MP_CONSTANT_STRING(ESTONIAN_ESTONIA, "ET-EE");
                MP_CONSTANT_STRING(FAROESE, "FO");
                MP_CONSTANT_STRING(FAROESE_FAROE_ISLANDS, "FO-FO");
                MP_CONSTANT_STRING(FARSI, "FA");
                MP_CONSTANT_STRING(FARSI_IRAN, "FA-IR");
                MP_CONSTANT_STRING(FINNISH, "FI");
                MP_CONSTANT_STRING(FINNISH_FINLAND, "FI-FI");
                MP_CONSTANT_STRING(FRENCH, "FR");
                MP_CONSTANT_STRING(FRENCH_BELGIUM, "FR-BE");
                MP_CONSTANT_STRING(FRENCH_CANADA, "FR-CA");
                MP_CONSTANT_STRING(FRENCH_FRANCE, "FR-FR");
                MP_CONSTANT_STRING(FRENCH_LUXEMBOURG, "FR-LU");
                MP_CONSTANT_STRING(FRENCH_MONACO, "FR-MC");
                MP_CONSTANT_STRING(FRENCH_SWITZERLAND, "FR-CH");
                MP_CONSTANT_STRING(GALICIAN, "GL");
                MP_CONSTANT_STRING(GALICIAN_GALICIAN, "GL-ES");
                MP_CONSTANT_STRING(GEORGIAN, "KA");
                MP_CONSTANT_STRING(GEORGIAN_GEORGIA, "KA-GE");
                MP_CONSTANT_STRING(GERMAN, "DE");
                MP_CONSTANT_STRING(GERMAN_AUSTRIA, "DE-AT");
                MP_CONSTANT_STRING(GERMAN_GERMANY, "DE-DE");
                MP_CONSTANT_STRING(GERMAN_LIECHTENSTEIN, "DE-LI");
                MP_CONSTANT_STRING(GERMAN_LUXEMBOURG, "DE-LU");
                MP_CONSTANT_STRING(GERMAN_SWITZERLAND, "DE-CH");
                MP_CONSTANT_STRING(GREEK, "EL");
                MP_CONSTANT_STRING(GREEK_GREECE, "EL-GR");
                MP_CONSTANT_STRING(GUJARATI, "GU");
                MP_CONSTANT_STRING(GUJARATI_INDIA, "GU-IN");
                MP_CONSTANT_STRING(HEBREW, "HE");
                MP_CONSTANT_STRING(HEBREW_ISRAEL, "HE-IL");
                MP_CONSTANT_STRING(HINDI, "HI");
                MP_CONSTANT_STRING(HINDI_INDIA, "HI-IN");
                MP_CONSTANT_STRING(HUNGARIAN, "HU");
                MP_CONSTANT_STRING(HUNGARIAN_HUNGARY, "HU-HU");
                MP_CONSTANT_STRING(ICELANDIC, "IS");
                MP_CONSTANT_STRING(ICELANDIC_ICELAND, "IS-IS");
                MP_CONSTANT_STRING(INDONESIAN, "ID");
                MP_CONSTANT_STRING(INDONESIAN_INDONESIA, "ID-ID");
                MP_CONSTANT_STRING(ITALIAN, "IT");
                MP_CONSTANT_STRING(ITALIAN_ITALY, "IT-IT");
                MP_CONSTANT_STRING(ITALIAN_SWITZERLAND, "IT-CH");
                MP_CONSTANT_STRING(JAPANESE, "JA");
                MP_CONSTANT_STRING(JAPANESE_JAPAN, "JA-JP");
                MP_CONSTANT_STRING(KANNADA, "KN");
                MP_CONSTANT_STRING(KANNADA_INDIA, "KN-IN");
                MP_CONSTANT_STRING(KAZAKH, "KK");
                MP_CONSTANT_STRING(KAZAKH_KAZAKHSTAN, "KK-KZ");
                MP_CONSTANT_STRING(KONKANI, "KOK");
                MP_CONSTANT_STRING(KONKANI_INDIA, "KOK-IN");
                MP_CONSTANT_STRING(KOREAN, "KO");
                MP_CONSTANT_STRING(KOREAN_KOREA, "KO-KR");
                MP_CONSTANT_STRING(KYRGYZ, "KY");
                MP_CONSTANT_STRING(KYRGYZ_KAZAKHSTAN, "KY-KZ");
                MP_CONSTANT_STRING(LATVIAN, "LV");
                MP_CONSTANT_STRING(LATVIAN_LATVIA, "LV-LV");
                MP_CONSTANT_STRING(LITHUANIAN, "LT");
                MP_CONSTANT_STRING(LITHUANIAN_LITHUANIA, "LT-LT");
                MP_CONSTANT_STRING(MACEDONIAN, "MK");
                MP_CONSTANT_STRING(MACEDONIAN_FYROM, "MK-MK");
                MP_CONSTANT_STRING(MALAY, "MS");
                MP_CONSTANT_STRING(MALAY_BRUNEI, "MS-BN");
                MP_CONSTANT_STRING(MALAY_MALAYSIA, "MS-MY");
                MP_CONSTANT_STRING(MARATHI, "MR");
                MP_CONSTANT_STRING(MARATHI_INDIA, "MR-IN");
                MP_CONSTANT_STRING(MONGOLIAN, "MN");
                MP_CONSTANT_STRING(MONGOLIAN_MONGOLIA, "MN-MN");
                MP_CONSTANT_STRING(NORWEGIAN, "NB");
                MP_CONSTANT_STRING(NORWEGIAN_NORWAY, "NB-NO");
                MP_CONSTANT_STRING(NORWEGIAN_NYNORSK, "NN");
                MP_CONSTANT_STRING(NORWEGIAN_NYNORSK_NORWAY, "NN-NO");
                MP_CONSTANT_STRING(POLISH, "PL");
                MP_CONSTANT_STRING(POLISH_POLAND, "PL-PL");
                MP_CONSTANT_STRING(PORTUGUESE, "PT");
                MP_CONSTANT_STRING(PORTUGUESE_BRAZIL, "PT-BR");
                MP_CONSTANT_STRING(PORTUGUESE_PORTUGAL, "PT-PT");
                MP_CONSTANT_STRING(PUNJABI, "PA");
                MP_CONSTANT_STRING(PUNJABI_INDIA, "PA-IN");
                MP_CONSTANT_STRING(ROMANIAN, "RO");
                MP_CONSTANT_STRING(ROMANIAN_ROMANIA, "RO-RO");
                MP_CONSTANT_STRING(RUSSIAN, "RU");
                MP_CONSTANT_STRING(RUSSIAN_RUSSIA, "RU-RU");
                MP_CONSTANT_STRING(SANSKRIT, "SA");
                MP_CONSTANT_STRING(SANSKRIT_INDIA, "SA-IN");
                MP_CONSTANT_STRING(SERBIAN_CYRILLIC, "CY-SR");
                MP_CONSTANT_STRING(SERBIAN_CYRILLIC_SERBIA, "CY-SR-SP");
                MP_CONSTANT_STRING(SERBIAN_LATIN, "LT-SR");
                MP_CONSTANT_STRING(SERBIAN_LATIN_SERBIA, "LT-SR-SP");
                MP_CONSTANT_STRING(SLOVAK, "SK");
                MP_CONSTANT_STRING(SLOVAK_SLOVAKIA, "SK-SK");
                MP_CONSTANT_STRING(SLOVENIAN, "SL");
                MP_CONSTANT_STRING(SLOVENIAN_SLOVENIA, "SL-SI");
                MP_CONSTANT_STRING(SPANISH, "ES");
                MP_CONSTANT_STRING(SPANISH_ARGENTINA, "ES-AR");
                MP_CONSTANT_STRING(SPANISH_BOLIVIA, "ES-BO");
                MP_CONSTANT_STRING(SPANISH_CHILE, "ES-CL");
                MP_CONSTANT_STRING(SPANISH_COLOMBIA, "ES-CO");
                MP_CONSTANT_STRING(SPANISH_COSTA_RICA, "ES-CR");
                MP_CONSTANT_STRING(SPANISH_DOMINICAN_REPUBLIC, "ES-DO");
                MP_CONSTANT_STRING(SPANISH_ECUADOR, "ES-EC");
                MP_CONSTANT_STRING(SPANISH_EL_SALVADOR, "ES-SV");
                MP_CONSTANT_STRING(SPANISH_GUATEMALA, "ES-GT");
                MP_CONSTANT_STRING(SPANISH_HONDURAS, "ES-HN");
                MP_CONSTANT_STRING(SPANISH_MEXICO, "ES-MX");
                MP_CONSTANT_STRING(SPANISH_NICARAGUA, "ES-NI");
                MP_CONSTANT_STRING(SPANISH_PANAMA, "ES-PA");
                MP_CONSTANT_STRING(SPANISH_PARAGUAY, "ES-PY");
                MP_CONSTANT_STRING(SPANISH_PERU, "ES-PE");
                MP_CONSTANT_STRING(SPANISH_PUERTO_RICO, "ES-PR");
                MP_CONSTANT_STRING(SPANISH_SPAIN, "ES-ES");
                MP_CONSTANT_STRING(SPANISH_URUGUAY, "ES-UY");
                MP_CONSTANT_STRING(SPANISH_VENEZUELA, "ES-VE");
                MP_CONSTANT_STRING(SWAHILI, "SW");
                MP_CONSTANT_STRING(SWAHILI_KENYA, "SW-KE");
                MP_CONSTANT_STRING(SWEDISH, "SV");
                MP_CONSTANT_STRING(SWEDISH_FINLAND, "SV-FI");
                MP_CONSTANT_STRING(SWEDISH_SWEDEN, "SV-SE");
                MP_CONSTANT_STRING(SYRIAC, "SYR");
                MP_CONSTANT_STRING(SYRIAC_SYRIA, "SYR-SY");
                MP_CONSTANT_STRING(TAMIL, "TA");
                MP_CONSTANT_STRING(TAMIL_INDIA, "TA-IN");
                MP_CONSTANT_STRING(TATAR, "TT");
                MP_CONSTANT_STRING(TATAR_RUSSIA, "TT-RU");
                MP_CONSTANT_STRING(TELUGU, "TE");
                MP_CONSTANT_STRING(TELUGU_INDIA, "TE-IN");
                MP_CONSTANT_STRING(THAI, "TH");
                MP_CONSTANT_STRING(THAI_THAILAND, "TH-TH");
                MP_CONSTANT_STRING(TURKISH, "TR");
                MP_CONSTANT_STRING(TURKISH_TURKEY, "TR-TR");
                MP_CONSTANT_STRING(UKRAINIAN, "UK");
                MP_CONSTANT_STRING(UKRAINIAN_UKRAINE, "UK-UA");
                MP_CONSTANT_STRING(URDU, "UR");
                MP_CONSTANT_STRING(URDU_PAKISTAN, "UR-PK");
                MP_CONSTANT_STRING(UZBEK_CYRILLIC, "CY-UZ");
                MP_CONSTANT_STRING(UZBEK_CYRILLIC_UZBEKISTAN, "CY-UZ-UZ");
                MP_CONSTANT_STRING(UZBEK_LATIN, "LT-UZ");
                MP_CONSTANT_STRING(UZBEK_LATIN_UZBEKISTAN, "LT-UZ-UZ");
                MP_CONSTANT_STRING(VIETNAMESE, "VI");
                MP_CONSTANT_STRING(VIETNAMESE_VIETNAM, "VI-VN");
            };
        public:
            MP_CLASS EVENT
            {
                MP_CONSTANT_STRING(UNKNOWN, "UNKNOWN");
                MP_CONSTANT_STRING(CLASS, "CLASS");
                MP_CONSTANT_STRING(CONTROL, "CONTROL");
                MP_CONSTANT_STRING(CRITICAL, "CRITICAL");
                MP_CONSTANT_STRING(DEBUG, "DEBUG");
                MP_CONSTANT_STRING(ERROR, "ERROR");
                MP_CONSTANT_STRING(EMERGENCY, "EMERGENCY");
                MP_CONSTANT_STRING(EXCEPTION, "EXCEPTION");
                MP_CONSTANT_STRING(FILE, "FILE");
                MP_CONSTANT_STRING(FOLDER, "FOLDER");
                MP_CONSTANT_STRING(FOOTER, "FOOTER");
                MP_CONSTANT_STRING(FUNCTION, "FUNCTION");
                MP_CONSTANT_STRING(HEADER, "HEADER");
                MP_CONSTANT_STRING(HINT, "HINT");
                MP_CONSTANT_STRING(INFO, "INFO");
                MP_CONSTANT_STRING(MESSAGE, "MESSAGE");
                MP_CONSTANT_STRING(OBJECT, "OBJECT");
                MP_CONSTANT_STRING(PARAMETER, "PARAMETER");
                MP_CONSTANT_STRING(PROJECT, "PROJECT");
                MP_CONSTANT_STRING(REQUEST, "REQUEST");
                MP_CONSTANT_STRING(RESPONSE, "RESPONSE");
                MP_CONSTANT_STRING(TEXT, "TEXT");
                MP_CONSTANT_STRING(TRANSFORM, "TRANSFORM");
                MP_CONSTANT_STRING(TRANSLATION, "TRANSLATION");
                MP_CONSTANT_STRING(VARIABLE, "VARIABLE");
                MP_CONSTANT_STRING(WARNING, "WARNING");
            };
        public:
            MP_CLASS FONT
            {
                MP_CONSTANT_STRING(ARIAL, "Arial");
                MP_CONSTANT_STRING(COURIER, "Courier");
                MP_CONSTANT_STRING(COURIER_NEW, "Courier New");
                MP_CONSTANT_STRING(GEORGIA, "Georgia");
                MP_CONSTANT_STRING(GARAMOND, "Garamond");
                MP_CONSTANT_STRING(IMPACT, "Impact");
                MP_CONSTANT_STRING(LUCIDA, "Lucida");
                MP_CONSTANT_STRING(SERIF, "Serif");
                MP_CONSTANT_STRING(SANS_SERIF, "Sans Serif");
                MP_CONSTANT_STRING(TAHOMA, "Tahoma");
                MP_CONSTANT_STRING(TIMES_NEW_ROMAN, "Times New Roman");
                MP_CONSTANT_STRING(VERDANA, "Verdana");
            };
        public:
            MP_CLASS KEYBOARD
            {
            public:
                MP_CLASS BUTTON
                {
                    MP_CONSTANT_STRING(DOWN_ALT, "KEY.DOWN.ALT");
                    MP_CONSTANT_STRING(DOWN_CONTROL, "KEY.DOWN.CONTROL");
                    MP_CONSTANT_STRING(DOWN_SHIFT, "KEY.DOWN.SHIFT");
                    MP_CONSTANT_STRING(DOWN_WIN, "KEY.DOWN.WIN");
                    MP_CONSTANT_STRING(UP_ALT, "KEY.UP.ALT");
                    MP_CONSTANT_STRING(UP_CONTROL, "KEY.UP.CONTROL");
                    MP_CONSTANT_STRING(UP_SHIFT, "KEY.UP.SHIFT");
                    MP_CONSTANT_STRING(UP_WIN, "KEY.UP.WIN");
                };
            };
        public:
            MP_CLASS MOUSE
            {
            public:
                MP_CLASS BUTTON
                {
                    MP_CONSTANT_STRING(DOWN_LEFT, "MOUSE.DOWN.LEFT");
                    MP_CONSTANT_STRING(DOWN_MIDDLE, "MOUSE.DOWN.MIDDLE");
                    MP_CONSTANT_STRING(DOWN_RIGHT, "MOUSE.DOWN.RIGHT");
                    MP_CONSTANT_STRING(UP_LEFT, "MOUSE.UP.LEFT");
                    MP_CONSTANT_STRING(UP_MIDDLE, "MOUSE.UP.MIDDLE");
                    MP_CONSTANT_STRING(UP_RIGHT, "MOUSE.UP.RIGHT");
                };
            public:
                MP_CLASS MOVE
                {
                    MP_CONSTANT_STRING(X, "MOUSE.MOVE.X");
                    MP_CONSTANT_STRING(Y, "MOUSE.MOVE.Y");
                };
            };
        public:
            MP_CLASS METADATA
            {
                MP_CONSTANT_STRING(AUTHORS, "AUTHORS");
                MP_CONSTANT_STRING(CHANGE_TIME, "CHANGE.TIME");
                MP_CONSTANT_STRING(COMPANY, "COMPANY");
                MP_CONSTANT_STRING(COPYRIGHT, "COPYRIGHT");
                MP_CONSTANT_STRING(COUNTRY, "COUNTRY");
                MP_CONSTANT_STRING(CREATE_TIME, "CREATE.TIME");
                MP_CONSTANT_STRING(DESCRIPTION, "DESCRIPTION");
                MP_CONSTANT_STRING(EMAIL, "EMAIL");
                MP_CONSTANT_STRING(ID, "ID");
                MP_CONSTANT_STRING(KEYWORDS, "KEYWORDS");
                MP_CONSTANT_STRING(LATITUDE, "LATITUDE");
                MP_CONSTANT_STRING(LICENSE, "LICENSE");
                MP_CONSTANT_STRING(LOGO, "LOGO");
                MP_CONSTANT_STRING(LONGITUDE, "LONGITUDE");
                MP_CONSTANT_STRING(OWNERS, "OWNERS");
                MP_CONSTANT_STRING(PATENTS, "PATENTS");
                MP_CONSTANT_STRING(PRODUCT, "PRODUCT");
                MP_CONSTANT_STRING(README, "README");
                MP_CONSTANT_STRING(SITE, "SITE");
                MP_CONSTANT_STRING(SPECIFICATION, "SPECIFICATION");
                MP_CONSTANT_STRING(TAGS, "TAGS");
                MP_CONSTANT_STRING(TITLE, "TITLE");
                MP_CONSTANT_STRING(TRADEMARKS, "TRADEMARKS");
                MP_CONSTANT_STRING(VERSION, "VERSION");
            };
        public:
            MP_CLASS PROPERTY
            {
                MP_CONSTANT_STRING(DEBUGGING_DATA_NESTING, "METAOUTPUT/DEBUGGING/DATA.NESTING");
                MP_CONSTANT_STRING(DEBUGGING_DATA_TIMEOUT, "METAOUTPUT/DEBUGGING/DATA.TIMEOUT");
                MP_CONSTANT_STRING(DEBUGGING_ITEM_COUNT, "METAOUTPUT/DEBUGGING/ITEM.COUNT");
                MP_CONSTANT_STRING(DEBUGGING_SHOW_PRIVATE, "METAOUTPUT/DEBUGGING/SHOW.PRIVATE");
                MP_CONSTANT_STRING(DEBUGGING_STACK_SIZE, "METAOUTPUT/DEBUGGING/STACK.SIZE");
                MP_CONSTANT_STRING(DEBUGGING_STRING_SIZE, "METAOUTPUT/DEBUGGING/STRING.SIZE");
                MP_CONSTANT_STRING(PREVIEW_DOCUMENT_SIZE, "METAOUTPUT/PREVIEW/DOCUMENT.SIZE");
                MP_CONSTANT_STRING(PREVIEW_BROWSER_SIZE, "METAOUTPUT/PREVIEW/BROWSER.SIZE");
                MP_CONSTANT_STRING(PREVIEW_MEDIA_SIZE, "METAOUTPUT/PREVIEW/MEDIA.SIZE");
                MP_CONSTANT_STRING(PREVIEW_TABLE_SIZE, "METAOUTPUT/PREVIEW/TABLE.SIZE");
            };
        public:
            MP_CLASS SOURCE
            {
                MP_CONSTANT_STRING(UNKNOWN, "UNKNOWN");
                MP_CONSTANT_STRING(ADVERTISEMENT, "ADVERTISEMENT");
                MP_CONSTANT_STRING(ADVISE, "ADVISE");
                MP_CONSTANT_STRING(ALERT, "ALERT");
                MP_CONSTANT_STRING(ANALYZER, "ANALYZER");
                MP_CONSTANT_STRING(BREAKPOINT, "BREAKPOINT");
                MP_CONSTANT_STRING(BUILD, "BUILD");
                MP_CONSTANT_STRING(CLOUD, "CLOUD");
                MP_CONSTANT_STRING(COMMAND, "COMMAND");
                MP_CONSTANT_STRING(CONSOLE, "CONSOLE");
                MP_CONSTANT_STRING(DATABASE, "DATABASE");
                MP_CONSTANT_STRING(DEBUG, "DEBUG");
                MP_CONSTANT_STRING(DIAGNOSTIC, "DIAGNOSTIC");
                MP_CONSTANT_STRING(EXTENSION, "EXTENSION");
                MP_CONSTANT_STRING(FIND, "FIND");
                MP_CONSTANT_STRING(HELP, "HELP");
                MP_CONSTANT_STRING(LOG, "LOG");
                MP_CONSTANT_STRING(METADATA, "METADATA");
                MP_CONSTANT_STRING(METAREPORT, "METAREPORT");
                MP_CONSTANT_STRING(NETWORK, "NETWORK");
                MP_CONSTANT_STRING(NEWS, "NEWS");
                MP_CONSTANT_STRING(NOTIFICATION, "NOTIFICATION");
                MP_CONSTANT_STRING(PERFORMANCE, "PERFORMANCE");
                MP_CONSTANT_STRING(PREVIEW, "PREVIEW");
                MP_CONSTANT_STRING(PROCESS, "PROCESS");
                MP_CONSTANT_STRING(REFACTORING, "REFACTORING");
                MP_CONSTANT_STRING(SECURITY, "SECURITY");
                MP_CONSTANT_STRING(SETTING, "SETTING");
                MP_CONSTANT_STRING(SOLUTION, "SOLUTION");
                MP_CONSTANT_STRING(STATUS, "STATUS");
                MP_CONSTANT_STRING(TASK, "TASK");
                MP_CONSTANT_STRING(TEST, "TEST");
                MP_CONSTANT_STRING(TOOL, "TOOL");
                MP_CONSTANT_STRING(THREAD, "THREAD");
                MP_CONSTANT_STRING(VARIABLE, "VARIABLE");
            };
        public:
            MP_CLASS STATE
            {
            public:
                MP_CLASS CHART
                {
                    MP_CONSTANT_INTEGER(AREA,       0x00000100);
                    MP_CONSTANT_INTEGER(BAR,        0x00000200);
                    MP_CONSTANT_INTEGER(DONUT,      0x00000400);
                    MP_CONSTANT_INTEGER(DOT,        0x00000800);
                    MP_CONSTANT_INTEGER(LINE,       0x00001000);
                    MP_CONSTANT_INTEGER(STACK,      0x00002000);
                };
            public:
                MP_CLASS CONTROL
                {
                    MP_CONSTANT_INTEGER(NONE,       0x00000000);
                    MP_CONSTANT_INTEGER(BLINK,      0x00100000);
                    MP_CONSTANT_INTEGER(BLUR,       0x00200000);
                    MP_CONSTANT_INTEGER(DISABLED,   0x00400000);
                    MP_CONSTANT_INTEGER(INFINITE,   0x00800000);
                    MP_CONSTANT_INTEGER(MUTE,       0x01000000);
                };
            public:
                MP_CLASS FONT
                {
                    MP_CONSTANT_INTEGER(NONE,       0x00000000);
                    MP_CONSTANT_INTEGER(BOLD,       0x01000000);
                    MP_CONSTANT_INTEGER(ITALIC,     0x02000000);
                    MP_CONSTANT_INTEGER(STRIKEOUT,  0x04000000);
                    MP_CONSTANT_INTEGER(UNDERSCORE, 0x08000000);
                };
            public:
                MP_CLASS TRACE
                {
                    MP_CONSTANT_INTEGER(NONE,       0x00000000);
                    MP_CONSTANT_INTEGER(BEEP,       0x00000001);
                    MP_CONSTANT_INTEGER(BLINK,      0x00000002);
                    MP_CONSTANT_INTEGER(CLEAR,      0x00000004);
                    MP_CONSTANT_INTEGER(COLLAPSE,   0x00000008);
                    MP_CONSTANT_INTEGER(EXPAND,     0x00000018);
                    MP_CONSTANT_INTEGER(FIX,        0x00000020);
                    MP_CONSTANT_INTEGER(FOCUS,      0x00000040);
                    MP_CONSTANT_INTEGER(HIDE,       0x00000080);
                    MP_CONSTANT_INTEGER(LOCK,       0x00000100);
                    MP_CONSTANT_INTEGER(MUTE,       0x00000200);
                    MP_CONSTANT_INTEGER(PIN,        0x00000400);
                    MP_CONSTANT_INTEGER(REMOVE,     0x00000800);
                    MP_CONSTANT_INTEGER(RESEND,     0x00001000);
                    MP_CONSTANT_INTEGER(SHOW,       0x00002000);
                    MP_CONSTANT_INTEGER(SPEAK,      0x00004000);
                    MP_CONSTANT_INTEGER(UNFIX,      0x00008000);
                    MP_CONSTANT_INTEGER(UNFOCUS,    0x00010000);
                    MP_CONSTANT_INTEGER(UNLOCK,     0x00020000);
                    MP_CONSTANT_INTEGER(UNPIN,      0x00040000);
                    MP_CONSTANT_INTEGER(UPDATE,     0x00080000);
                };
            public:
                MP_CLASS WORK
                {
                    MP_CONSTANT_STRING(CANCEL, "CANCEL");
                    MP_CONSTANT_STRING(EXECUTE, "EXECUTE");
                    MP_CONSTANT_STRING(WAIT, "");
                };
            };
        public:
            MP_CLASS TYPE
            {
                MP_CONSTANT_STRING(UNKNOWN, "");
                MP_CONSTANT_STRING(MSTR, "MSTR");
                MP_CONSTANT_STRING(AAC, "AAC");
                MP_CONSTANT_STRING(AVI, "AVI");
                MP_CONSTANT_STRING(BMP, "BMP");
                MP_CONSTANT_STRING(CSS, "css");
                MP_CONSTANT_STRING(CSV, "csv");
                MP_CONSTANT_STRING(DLL, "DLL");
                MP_CONSTANT_STRING(EXE, "EXE");
                MP_CONSTANT_STRING(GIF, "GIF");
                MP_CONSTANT_STRING(HTML, "htm");
                MP_CONSTANT_STRING(ICO, "ICO");
                MP_CONSTANT_STRING(INI, "ini");
                MP_CONSTANT_STRING(JPG, "JPG");
                MP_CONSTANT_STRING(JSON, "jsn");
                MP_CONSTANT_STRING(MD, "md");
                MP_CONSTANT_STRING(MKA, "MKA");
                MP_CONSTANT_STRING(MKV, "MKV");
                MP_CONSTANT_STRING(MOV, "MOV");
                MP_CONSTANT_STRING(MP3, "MP3");
                MP_CONSTANT_STRING(MP4, "MP4");
                MP_CONSTANT_STRING(MPG, "MPG");
                MP_CONSTANT_STRING(PDF, "PDF");
                MP_CONSTANT_STRING(PNG, "PNG");
                MP_CONSTANT_STRING(SQL, "sql");
                MP_CONSTANT_STRING(SVG, "svg");
                MP_CONSTANT_STRING(TIF, "TIF");
                MP_CONSTANT_STRING(TML, "tml");
                MP_CONSTANT_STRING(TXT, "txt");
                MP_CONSTANT_STRING(WAV, "WAV");
                MP_CONSTANT_STRING(WMA, "WMA");
                MP_CONSTANT_STRING(WMV, "WMV");
                MP_CONSTANT_STRING(XML, "xml");
                MP_CONSTANT_STRING(YAML, "yml");
                MP_CONSTANT_STRING(ZIP, "ZIP");
            };
        };
    public:
        Trace();
    public:
        static MP_PTR(Trace) GetInstance();
        static MP_STRING GetAttribute(MP_STRING value, MP_STRING name);
        static MP_STRING GetFirstLine(MP_STRING value, bool isAnyText);
        static MP_STRING GetMultiLine(MP_STRING value, bool isAnyText);
        static MP_STRING GetUrlFinal(MP_STRING url);
        static MP_STRING GetUrlTemp(MP_STRING url);
        static MP_STRING GetUrlTemp(MP_STRING url, MP_STRING extension);
    public:
        MP_PTR(Trace) Clear();
        MP_PTR(Trace) Send(MP_STRING source, MP_STRING event, MP_INT level);
        MP_PTR(Trace) Send(MP_STRING source, MP_STRING event, MP_INT level, MP_STRING content);
        MP_PTR(Trace) Send(MP_STRING source, MP_STRING event, MP_INT level, MP_STRING content, MP_STRING value);
        MP_PTR(Trace) SendTml(MP_STRING value);
        MP_PTR(Trace) SendTml(MP_STRING value, MP_STRING source);
        MP_PTR(Trace) SendPreview(MP_STRING event, MP_STRING url);
    public:
        MP_PTR(Trace) SetAlignment(MP_INT value);
        MP_PTR(Trace) SetBackground(MP_INT value);
        MP_PTR(Trace) SetCommand(MP_STRING name, MP_STRING value);
        MP_PTR(Trace) SetComment(MP_STRING value);
        MP_PTR(Trace) SetComment(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetCondition(MP_STRING name, MP_STRING value1, MP_STRING value2);
        MP_PTR(Trace) SetContent(MP_STRING value);
        MP_PTR(Trace) SetControl(MP_STRING name);
        MP_PTR(Trace) SetControl(MP_STRING name, MP_STRING hint, MP_STRING pipe, MP_INT state);
        MP_PTR(Trace) SetCount(MP_INT value);
        MP_PTR(Trace) SetDate(MP_INT year, MP_INT month, MP_INT day);
        MP_PTR(Trace) SetFont(MP_STRING name, MP_INT size, MP_INT state);
        MP_PTR(Trace) SetForeground(MP_INT value);
        MP_PTR(Trace) SetMargin(MP_INT x, MP_INT y);
        MP_PTR(Trace) SetPadding(MP_INT value);
        MP_PTR(Trace) SetPadding(MP_INT minX, MP_INT minY, MP_INT maxX, MP_INT maxY);
        MP_PTR(Trace) SetProgress(MP_DOUBLE value);
        MP_PTR(Trace) SetProgress(MP_DOUBLE value, MP_STRING hint);
        MP_PTR(Trace) SetSize(MP_INT x, MP_INT y);
        MP_PTR(Trace) SetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT milliSecond);
        MP_PTR(Trace) SetTml(MP_STRING value);
        MP_PTR(Trace) SetTrace(MP_STRING id, MP_INT state);
        MP_PTR(Trace) SetTranslation(MP_STRING culture, MP_STRING value);
        MP_PTR(Trace) SetTransparency(MP_DOUBLE value);
        MP_PTR(Trace) SetUrl(MP_STRING value);
        MP_PTR(Trace) SetUrl(MP_STRING value, MP_INT line, MP_INT position);
        MP_PTR(Trace) SetUrl(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetUrl(MP_STRING value, MP_STRING hint, MP_INT line, MP_INT position);
        MP_PTR(Trace) SetUrlInfo(MP_STRING value);
        MP_PTR(Trace) SetUrlInfo(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetUrlPreview(MP_STRING value);
        MP_PTR(Trace) SetUrlPreview(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetUrlSample(MP_STRING value);
        MP_PTR(Trace) SetUrlSample(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetValue(MP_STRING value);
        MP_PTR(Trace) SetValue(MP_STRING value, MP_STRING type);
        MP_PTR(Trace) SetValue(MP_PTR(MP_STREAM) value, MP_STRING type);
    private:
        MP_PTR(Trace) __SendTml(MP_STRING value);
    private:
        static MP_PTR(MP_THREAD_MUTEX) __GetMutex();
    private:
        static MP_STRING __GetEvent(MP_STRING value);
        static MP_STRING __GetSource(MP_STRING value);
        static MP_STRING __GetColor(MP_INT value);
        static MP_STRING __GetLevel(MP_INT value);
        static MP_STRING __GetTml(MP_STRING value, MP_STRING source);
        static MP_STRING __GetText(MP_STRING value);
        static MP_STRING __GetFileName(MP_STRING url);
        static MP_STRING __GetStackTrace(MP_STRING source, int level, int skip);
        static MP_STRING __GetProxyFolder();
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        static MP_PTR(MP_THREAD_MUTEX) s_Mutex;
        static MP_PTR(MP_MAP(MP_PTR(Trace))) s_Instances;
        static MP_PTR(MP_THREAD) s_TraceThread;
        static MP_STRING s_TraceBuffer;
    private:
        MP_STRING m_Background;
        MP_STRING m_Command;
        MP_STRING m_Comment;
        MP_STRING m_Condition;
        MP_STRING m_Content;
        MP_STRING m_Control;
        MP_STRING m_Count;
        MP_STRING m_Date;
        MP_STRING m_Flag;
        MP_STRING m_Font;
        MP_STRING m_Foreground;
        MP_STRING m_Progress;
        MP_STRING m_Time;
        MP_STRING m_Tml;
        MP_STRING m_Trace;
        MP_STRING m_Url;
        MP_STRING m_UrlInfo;
        MP_STRING m_UrlPreview;
        MP_STRING m_UrlSample;
        MP_STRING m_Value;
    };
}
