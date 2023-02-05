#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyExport
    {
    protected:
        MP_CLASS CONSTANT : public atom::Trace::CONSTANT
        {
        };
    protected:
        MP_CLASS NAME : public atom::Trace::NAME
        {
        };
    public:
        static void Connect();
        static void Disconnect();
        static bool Register(MP_STRING extension, MP_PTR(AnyExport) context);
        static bool Execute(MP_STRING url, MP_STRING from);
    public:
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) context, MP_STRING url, MP_STRING from);
    private:
        static void __Execute(MP_PTR(extension::AnyExport) sender, MP_PTR(atom::Trace) context, MP_STRING url, MP_STRING from);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        MP_STRING m_From;
        MP_STRING m_Name;
        MP_PTR(atom::Trace) m_Context;
        MP_PTR(MP_THREAD) m_Thread;
        MP_PTR(MP_THREAD_MUTEX) m_Mutex;
    private:
        static MP_PTR(MP_VECTOR(AnyExport)) s_Items;
    };
}
