#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Keyboard
        {
        public:
            MP_CLASS NAME
            {
            public:
                MP_CLASS KEY
                {
                    MP_CONSTANT_NAME(CANCEL);
                    MP_CONSTANT_NAME(BACK);
                    MP_CONSTANT_NAME(TAB);
                    MP_CONSTANT_NAME(LINE_FEED);
                    MP_CONSTANT_NAME(CLEAR);
                    MP_CONSTANT_NAME(RETURN);
                    MP_CONSTANT_NAME(PAUSE);
                    MP_CONSTANT_NAME(CAPS_LOCK);
                    MP_CONSTANT_NAME(ESCAPE);
                    MP_CONSTANT_NAME(SPACE);
                    MP_CONSTANT_NAME(PAGE_UP);
                    MP_CONSTANT_NAME(PAGE_DOWN);
                    MP_CONSTANT_NAME(END);
                    MP_CONSTANT_NAME(HOME);
                    MP_CONSTANT_NAME(LEFT);
                    MP_CONSTANT_NAME(UP);
                    MP_CONSTANT_NAME(RIGHT);
                    MP_CONSTANT_NAME(DOWN);
                    MP_CONSTANT_NAME(SELECT);
                    MP_CONSTANT_NAME(PRINT);
                    MP_CONSTANT_NAME(EXECUTE);
                    MP_CONSTANT_NAME(PRINT_SCREEN);
                    MP_CONSTANT_NAME(INSERT);
                    MP_CONSTANT_NAME(DELETE);
                    MP_CONSTANT_NAME(HELP);
                    MP_CONSTANT_NAME(D0);
                    MP_CONSTANT_NAME(D1);
                    MP_CONSTANT_NAME(D2);
                    MP_CONSTANT_NAME(D3);
                    MP_CONSTANT_NAME(D4);
                    MP_CONSTANT_NAME(D5);
                    MP_CONSTANT_NAME(D6);
                    MP_CONSTANT_NAME(D7);
                    MP_CONSTANT_NAME(D8);
                    MP_CONSTANT_NAME(D9);
                    MP_CONSTANT_NAME(A);
                    MP_CONSTANT_NAME(B);
                    MP_CONSTANT_NAME(C);
                    MP_CONSTANT_NAME(D);
                    MP_CONSTANT_NAME(E);
                    MP_CONSTANT_NAME(F);
                    MP_CONSTANT_NAME(G);
                    MP_CONSTANT_NAME(H);
                    MP_CONSTANT_NAME(I);
                    MP_CONSTANT_NAME(J);
                    MP_CONSTANT_NAME(K);
                    MP_CONSTANT_NAME(L);
                    MP_CONSTANT_NAME(M);
                    MP_CONSTANT_NAME(N);
                    MP_CONSTANT_NAME(O);
                    MP_CONSTANT_NAME(P);
                    MP_CONSTANT_NAME(Q);
                    MP_CONSTANT_NAME(R);
                    MP_CONSTANT_NAME(S);
                    MP_CONSTANT_NAME(T);
                    MP_CONSTANT_NAME(U);
                    MP_CONSTANT_NAME(V);
                    MP_CONSTANT_NAME(W);
                    MP_CONSTANT_NAME(X);
                    MP_CONSTANT_NAME(Y);
                    MP_CONSTANT_NAME(Z);
                    MP_CONSTANT_NAME(APPS);
                    MP_CONSTANT_NAME(SLEEP);
                    MP_CONSTANT_NAME(NUMPAD_0);
                    MP_CONSTANT_NAME(NUMPAD_1);
                    MP_CONSTANT_NAME(NUMPAD_2);
                    MP_CONSTANT_NAME(NUMPAD_3);
                    MP_CONSTANT_NAME(NUMPAD_4);
                    MP_CONSTANT_NAME(NUMPAD_5);
                    MP_CONSTANT_NAME(NUMPAD_6);
                    MP_CONSTANT_NAME(NUMPAD_7);
                    MP_CONSTANT_NAME(NUMPAD_8);
                    MP_CONSTANT_NAME(NUMPAD_9);
                    MP_CONSTANT_NAME(MULTIPLY);
                    MP_CONSTANT_NAME(ADD);
                    MP_CONSTANT_NAME(SEPARATOR);
                    MP_CONSTANT_NAME(SUBTRACT);
                    MP_CONSTANT_NAME(DECIMAL);
                    MP_CONSTANT_NAME(DIVIDE);
                    MP_CONSTANT_NAME(F1);
                    MP_CONSTANT_NAME(F2);
                    MP_CONSTANT_NAME(F3);
                    MP_CONSTANT_NAME(F4);
                    MP_CONSTANT_NAME(F5);
                    MP_CONSTANT_NAME(F6);
                    MP_CONSTANT_NAME(F7);
                    MP_CONSTANT_NAME(F8);
                    MP_CONSTANT_NAME(F9);
                    MP_CONSTANT_NAME(F10);
                    MP_CONSTANT_NAME(F11);
                    MP_CONSTANT_NAME(F12);
                    MP_CONSTANT_NAME(F13);
                    MP_CONSTANT_NAME(F14);
                    MP_CONSTANT_NAME(F15);
                    MP_CONSTANT_NAME(F16);
                    MP_CONSTANT_NAME(F17);
                    MP_CONSTANT_NAME(F18);
                    MP_CONSTANT_NAME(F19);
                    MP_CONSTANT_NAME(F20);
                    MP_CONSTANT_NAME(F21);
                    MP_CONSTANT_NAME(F22);
                    MP_CONSTANT_NAME(F23);
                    MP_CONSTANT_NAME(F24);
                    MP_CONSTANT_NAME(NUM_LOCK);
                    MP_CONSTANT_NAME(SCROLL);
                    MP_CONSTANT_NAME(SHIFT_LEFT);
                    MP_CONSTANT_NAME(SHIFT_RIGHT);
                    MP_CONSTANT_NAME(CTRL_LEFT);
                    MP_CONSTANT_NAME(CTRL_RIGHT);
                    MP_CONSTANT_NAME(ALT_LEFT);
                    MP_CONSTANT_NAME(ALT_RIGHT);
                    MP_CONSTANT_NAME(WIN_LEFT);
                    MP_CONSTANT_NAME(WIN_RIGHT);
                    MP_CONSTANT_NAME(BROWSER_BACK);
                    MP_CONSTANT_NAME(BROWSER_FORWARD);
                    MP_CONSTANT_NAME(BROWSER_REFRESH);
                    MP_CONSTANT_NAME(BROWSER_STOP);
                    MP_CONSTANT_NAME(BROWSER_FIND);
                    MP_CONSTANT_NAME(BROWSER_FAVORITES);
                    MP_CONSTANT_NAME(BROWSER_HOME);
                    MP_CONSTANT_NAME(VOLUME_MUTE);
                    MP_CONSTANT_NAME(VOLUME_DOWN);
                    MP_CONSTANT_NAME(VOLUME_UP);
                    MP_CONSTANT_NAME(MEDIA_NEXT_TRACK);
                    MP_CONSTANT_NAME(MEDIA_PREV_TRACK);
                    MP_CONSTANT_NAME(MEDIA_STOP);
                    MP_CONSTANT_NAME(MEDIA_PLAY_PAUSE);
                    MP_CONSTANT_NAME(MEDIA_SELECT);
                    MP_CONSTANT_NAME(LAUNCH_MAIL);
                    MP_CONSTANT_NAME(LAUNCH_APPLICATION1);
                    MP_CONSTANT_NAME(LAUNCH_APPLICATION2);
                    MP_CONSTANT_NAME(SYSTEM);
                    MP_CONSTANT_NAME(PLAY);
                    MP_CONSTANT_NAME(ZOOM);
                    MP_CONSTANT_NAME(OEM_SEMICOLON);
                    MP_CONSTANT_NAME(OEM_PLUS);
                    MP_CONSTANT_NAME(OEM_COMMA);
                    MP_CONSTANT_NAME(OEM_MINUS);
                    MP_CONSTANT_NAME(OEM_PERIOD);
                    MP_CONSTANT_NAME(OEM_QUESTION);
                    MP_CONSTANT_NAME(OEM_TILDE);
                    MP_CONSTANT_NAME(OEM_OPEN_BRACKETS);
                    MP_CONSTANT_NAME(OEM_CLOSE_BRACKETS);
                    MP_CONSTANT_NAME(OEM_PIPE);
                    MP_CONSTANT_NAME(OEM_QUOTES);
                    MP_CONSTANT_NAME(OEM_BACK_SLASH);
                    MP_CONSTANT_NAME(OEM_FINISH);
                    MP_CONSTANT_NAME(OEM_COPY);
                    MP_CONSTANT_NAME(OEM_AUTO);
                    MP_CONSTANT_NAME(OEM_ENLW);
                    MP_CONSTANT_NAME(OEM_BACK_TAB);
                    MP_CONSTANT_NAME(OEM_CLEAR);
                };
            };
        public:
            MP_CLASS VARIABLE
            {
                MP_CONSTANT_STRING(BUTTON_ALT, "<<SHARED>>HMI/KEYBOARD/BUTTON.ALT");
                MP_CONSTANT_STRING(BUTTON_CAPS, "<<SHARED>>HMI/KEYBOARD/BUTTON.CAPS");
                MP_CONSTANT_STRING(BUTTON_CONTROL, "<<SHARED>>HMI/KEYBOARD/BUTTON.CONTROL");
                MP_CONSTANT_STRING(BUTTON_NUM_LOCK, "<<SHARED>>HMI/KEYBOARD/BUTTON.NUM.LOCK");
                MP_CONSTANT_STRING(BUTTON_SCROLL_LOCK, "<<SHARED>>HMI/KEYBOARD/BUTTON.SCROLL.LOCK");
                MP_CONSTANT_STRING(BUTTON_SHIFT, "<<SHARED>>HMI/KEYBOARD/BUTTON.SHIFT");
                MP_CONSTANT_STRING(BUTTON_WINDOWS, "<<SHARED>>HMI/KEYBOARD/BUTTON.WINDOWS");
                MP_CONSTANT_STRING(KEY_DOWN, "<<SHARED>>HMI/KEYBOARD/KEY.DOWN");
                MP_CONSTANT_STRING(KEY_UP, "<<SHARED>>HMI/KEYBOARD/KEY.UP");
            };
        public:
            MP_CONSTANT_PATTERN(Keyboard);
            MP_CONSTANT_NAME(KEY);
            MP_CONSTANT_NAME(KEY_DOWN);
            MP_CONSTANT_NAME(KEY_UP);
            MP_CONSTANT_NAME(TEXT);
        };
    }
}
