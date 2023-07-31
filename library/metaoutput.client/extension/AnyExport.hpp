#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyExport
    {
    public:
        MP_CLASS CONSTANT : public atom::Trace::CONSTANT
        {
        };
    public:
        MP_CLASS NAME : public atom::Trace::NAME
        {
        };
    public:
        static void Connect(MP_STRING application, MP_STRING extension);
        static void Disconnect();
        static bool Register(MP_STRING extension, MP_PTR(AnyExport) context);
        static bool Unregister(MP_STRING extension);
        static bool Execute(MP_STRING url, MP_STRING from);
    public:
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) trace, MP_STRING url, MP_STRING from);
    private:
        static void __Execute(MP_PTR(extension::AnyExport) sender, MP_PTR(atom::Trace) trace, MP_STRING url, MP_STRING from);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        MP_STRING m_From;
        MP_STRING m_Name;
        MP_PTR(MP_THREAD) m_Thread;
    private:
        static MP_PTR(MP_VECTOR(AnyExport)) s_Items;
    };
}
