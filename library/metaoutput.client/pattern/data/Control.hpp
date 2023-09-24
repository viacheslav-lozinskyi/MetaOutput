#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Control
        {
        public:
            MP_CLASS CONSTANT
            {
            public:
                MP_CLASS ACTION
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 20);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::DARK_RED);
                    MP_CONSTANT_INTEGER(SIZE_Y, 64);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 90);
                };
            public:
                MP_CLASS BUTTON
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 14);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::BLACK);
                    MP_CONSTANT_INTEGER(SIZE_X, 200);
                    MP_CONSTANT_INTEGER(SIZE_Y, 26);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS COMBOBOX
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 12);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::BLACK);
                    MP_CONSTANT_INTEGER(SIZE_X, 140);
                    MP_CONSTANT_INTEGER(SIZE_Y, 26);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS COUNT
                {
                    MP_CONSTANT_INTEGER(BIG, 15);
                    MP_CONSTANT_INTEGER(HUGE, 20);
                    MP_CONSTANT_INTEGER(MIDDLE, 12);
                    MP_CONSTANT_INTEGER(NORMAL, 10);
                    MP_CONSTANT_INTEGER(SMALL, 7);
                    MP_CONSTANT_INTEGER(TINY, 3);
                };
            public:
                MP_CLASS DELIMITER
                {
                    MP_CONSTANT_INTEGER(SIZE_Y, 1);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS ITEM
                {
                    MP_CONSTANT_INTEGER(SIZE_X, 32);
                    MP_CONSTANT_INTEGER(SIZE_Y, 32);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS FOOTER
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 12);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::BLACK);
                    MP_CONSTANT_INTEGER(SIZE_Y, 26);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 70);
                };
            public:
                MP_CLASS HEADER
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 14);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::BLACK);
                    MP_CONSTANT_INTEGER(SIZE_Y, 26);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 70);
                };
            public:
                MP_CLASS LOGO
                {
                    MP_CONSTANT_INTEGER(SIZE_X, 150);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS MESSAGE
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 14);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::DARK_RED);
                    MP_CONSTANT_INTEGER(SIZE_Y, 20);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS PREVIEW
                {
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::ORCHID);
                    MP_CONSTANT_INTEGER(ITEM_SIZE_Y, 19);
                    MP_CONSTANT_INTEGER(MIN_COUNT, 2);
                    MP_CONSTANT_INTEGER(MIN_SIZE_X, 200);
                    MP_CONSTANT_INTEGER(PAGE_INDENT, 10);
                    MP_CONSTANT_INTEGER(PAGE_BREAK, 7);
                };
            public:
                MP_CLASS RESOURCE
                {
                    MP_CONSTANT_STRING(PICTURE_COPY, "{{{RESOURCE:METAOUTPUT/EXTENSION/COPY}}}");
                    MP_CONSTANT_STRING(PICTURE_FILE, "{{{RESOURCE:METAOUTPUT/EXTENSION/FILE}}}");
                    MP_CONSTANT_STRING(PICTURE_SAVE, "{{{RESOURCE:METAOUTPUT/EXTENSION/SAVE}}}");
                    MP_CONSTANT_STRING(PICTURE_STATUS_FAIL, "{{{RESOURCE:METAOUTPUT/OTHER/STATUS.FAIL}}}");
                    MP_CONSTANT_STRING(PICTURE_STATUS_SUCCESS, "{{{RESOURCE:METAOUTPUT/OTHER/STATUS.SUCCESS}}}");
                };
            public:
                MP_CLASS TOOL
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 14);
                    MP_CONSTANT_INTEGER(BACKGROUND, pattern::data::Color::NAME::AQUAMARINE);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::DODGER_BLUE);
                    MP_CONSTANT_INTEGER(PADDING, 3);
                    MP_CONSTANT_INTEGER(SIZE_X, 48);
                    MP_CONSTANT_INTEGER(SIZE_Y, 48);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 80);
                };
            public:
                MP_CLASS TITLE
                {
                    MP_CONSTANT_STRING(FONT_NAME, pattern::data::Font::NAME::ARIAL);
                    MP_CONSTANT_INTEGER(FONT_SIZE, 12);
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::BLACK);
                    MP_CONSTANT_INTEGER(SIZE_X, 140);
                    MP_CONSTANT_INTEGER(SIZE_Y, 18);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            public:
                MP_CLASS TRACE
                {
                    MP_CONSTANT_INTEGER(FOREGROUND, pattern::data::Color::NAME::TEAL);
                };
            public:
                MP_CLASS WINDOW
                {
                    MP_CONSTANT_INTEGER(BACKGROUND, pattern::data::Color::NAME::WHITE);
                    MP_CONSTANT_INTEGER(PADDING, 5);
                    MP_CONSTANT_INTEGER(TRANSPARENCY, 0);
                };
            };
        public:
            MP_CLASS CHART
            {
                MP_CONSTANT_INTEGER(AREA,       0x00000001);
                MP_CONSTANT_INTEGER(BAR,        0x00000002);
                MP_CONSTANT_INTEGER(DONUT,      0x00000004);
                MP_CONSTANT_INTEGER(DOT,        0x00000008);
                MP_CONSTANT_INTEGER(LINE,       0x00000010);
                MP_CONSTANT_INTEGER(STACK,      0x00000020);
            };
        public:
            MP_CLASS NAME
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
                MP_CONSTANT_STRING(HINT, "HINT");
                MP_CONSTANT_STRING(ITEM, "ITEM");
                MP_CONSTANT_STRING(LABEL, "LABEL");
                MP_CONSTANT_STRING(LINK, "LINK");
                MP_CONSTANT_STRING(PANEL, "PANEL");
                MP_CONSTANT_STRING(PICTURE, "PICTURE");
                MP_CONSTANT_STRING(PROGRESSBOX, "PROGRESSBOX");
                MP_CONSTANT_STRING(RADIOBOX, "RADIOBOX");
                MP_CONSTANT_STRING(SCROLLBOX, "SCROLLBOX");
                MP_CONSTANT_STRING(SLIDEBOX, "SLIDEBOX");
                MP_CONSTANT_STRING(SPLITTER, "SPLITTER");
                MP_CONSTANT_STRING(TABBOX, "TABBOX");
                MP_CONSTANT_STRING(TABLE, "TABLE");
                MP_CONSTANT_STRING(TEXTBOX, "TEXTBOX");
                MP_CONSTANT_STRING(TREE, "TREE");
                MP_CONSTANT_STRING(VIDEO, "VIDEO");
                MP_CONSTANT_STRING(WINDOW, "WINDOW");
            };
        public:
            MP_CLASS PROGRESS
            {
                MP_CONSTANT_INTEGER(INFINITE, 101);
                MP_CONSTANT_INTEGER(REMOVE, -1);
            };
        public:
            MP_CLASS STATE
            {
                MP_CONSTANT_INTEGER(NONE,       0x00000000);
                MP_CONSTANT_INTEGER(BLINK,      0x00000001);
                MP_CONSTANT_INTEGER(BLUR,       0x00000002);
                MP_CONSTANT_INTEGER(DISABLED,   0x00000004);
                MP_CONSTANT_INTEGER(INFINITE,   0x00000008);
                MP_CONSTANT_INTEGER(MUTE,       0x00000010);
            };
        };
    }
}
