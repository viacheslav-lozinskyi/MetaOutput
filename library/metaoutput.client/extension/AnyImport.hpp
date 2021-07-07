#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyImport
    {
    public:
        MP_CLASS NAME : public atom::Trace::NAME
        {
        };
    private:
        MP_CLASS Item
        {
        public:
            MP_STRING m_Name;
            MP_PTR(atom::Trace) m_Context;
            MP_PTR(AnyImport) m_Extension;
            MP_PTR(MP_THREAD) m_Thread;
            MP_PIPE_CLIENT m_Pipe;
        };
    public:
        static void Connect();
        static void Disconnect();
        static void Register(MP_STRING extension, MP_PTR(AnyImport) context);
        static void Execute(MP_STRING url);
        static bool Send(MP_STRING value);
    public:
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) context, MP_STRING url);
    private:
        static MP_PTR(MP_THREAD_MUTEX) __GetMutex();
    private:
        static bool __SendRequest(MP_STRING name, MP_STRING value);
        static void __Execute(MP_PTR(extension::AnyImport) sender, MP_PTR(atom::Trace) context, MP_STRING url);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        static MP_PTR(MP_THREAD_MUTEX) s_Mutex;
        static MP_PTR(MP_VECTOR(Item)) s_Items;
        static MP_PTR(MP_VECTOR(Item)) s_Pipes;
    };
}
