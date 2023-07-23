#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyImport
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
        static void Connect(MP_STRING application, MP_STRING extension);
        static void Disconnect();
        static bool Register(MP_STRING extension, MP_PTR(AnyImport) context);
        static bool Unregister(MP_STRING extension);
        static bool Execute(MP_STRING url);
    public:
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) trace, MP_STRING url);
    private:
        static void __Execute(MP_PTR(extension::AnyImport) sender, MP_PTR(atom::Trace) trace, MP_STRING url);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        MP_STRING m_Name;
        MP_PTR(MP_THREAD) m_Thread;
    private:
        static MP_PTR(MP_VECTOR(AnyImport)) s_Items;
    };
}
