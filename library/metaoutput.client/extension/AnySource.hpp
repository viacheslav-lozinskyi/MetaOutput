#pragma once

namespace extension
{
    MP_CLASS_SHARED AnySource
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
        static bool Register(MP_STRING name, MP_PTR(AnySource) context);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) context);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        MP_STRING m_Name;
        MP_PTR(atom::Trace) m_Context;
        MP_PTR(MP_THREAD) m_Thread;
    private:
        static MP_PTR(MP_VECTOR(AnySource)) s_Items;
        static MP_BOOL s_IsTerminated;
    };
}
