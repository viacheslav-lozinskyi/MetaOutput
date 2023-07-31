#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyPipe
    {
    public:
        MP_CLASS CONSTANT : public atom::Trace::CONSTANT
        {
        };
    public:
        MP_CLASS NAME : public atom::Trace::NAME
        {
        public:
            MP_CLASS ACTION
            {
                MP_CONSTANT_STRING(CHANGE, "CHANGE");
                MP_CONSTANT_STRING(CLICK, "CLICK");
                MP_CONSTANT_STRING(ENTER, "ENTER");
                MP_CONSTANT_STRING(LEAVE, "LEAVE");
                MP_CONSTANT_STRING(MOVE, "MOVE");
                MP_CONSTANT_STRING(WHEEL, "WHEEL");
            };
        public:
            MP_CLASS ATTRIBUTE
            {
                MP_CONSTANT_STRING(ACTION, "ACTION");
                MP_CONSTANT_STRING(CONTENT, "CONTENT");
                MP_CONSTANT_STRING(CURSOR_X, "CURSOR.X");
                MP_CONSTANT_STRING(CURSOR_Y, "CURSOR.Y");
                MP_CONSTANT_STRING(ID, "ID");
                MP_CONSTANT_STRING(KEYBOARD, "KEYBOARD");
                MP_CONSTANT_STRING(MOUSE, "MOUSE");
                MP_CONSTANT_STRING(URL, "URL");
            };
        };
    public:
        static void Connect(MP_STRING application, MP_STRING extension);
        static void Disconnect();
        static bool Register(MP_STRING name, MP_PTR(AnyPipe) context);
        static bool Unregister(MP_STRING name);
        static bool Execute(MP_STRING name, MP_STRING value);
        static void Validate(MP_STRING application, MP_STRING extension);
    public:
        static bool IsButtonPressed(MP_STRING value);
    public:
        static MP_STRING GetPipeName(MP_STRING value);
        static MP_STRING GetAttribute(MP_STRING value, MP_STRING name);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) trace, MP_STRING pipe, MP_STRING value);
    private:
        static MP_PTR(MP_THREAD_MUTEX) __GetMutex();
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        MP_STRING m_Name;
        MP_PTR(MP_THREAD) m_Thread;
    private:
        static MP_PTR(MP_THREAD_MUTEX) s_Mutex;
        static MP_PTR(MP_PIPE_WRITESTREAM) s_Default;
        static MP_PTR(MP_VECTOR(AnyPipe)) s_Items;
    };
}
