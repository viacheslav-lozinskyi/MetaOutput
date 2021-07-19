#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyPreview
    {
    protected:
        MP_CLASS CONSTANT : public atom::Trace::CONSTANT
        {
        };
    protected:
        MP_CLASS NAME : public atom::Trace::NAME
        {
        };
    private:
        MP_CLASS Item
        {
        public:
            MP_STRING m_Name;
            MP_PTR(atom::Trace) m_Context;
            MP_PTR(AnyPreview) m_Extension;
            MP_PTR(MP_THREAD) m_Thread;
        };
    public:
        static void Connect();
        static void Disconnect();
        static void Register(MP_STRING extension, MP_PTR(AnyPreview) context);
        static bool Execute(MP_STRING url);
        static bool Send(MP_STRING value);
        static bool Send(MP_STRING pipeName, MP_STRING value);
    public:
        static MP_STRING GetExtension(MP_STRING url);
        static MP_STRING GetName(MP_STRING value);
        static MP_STRING GetPipeName(MP_STRING value);
        static MP_STRING GetFinalText(MP_STRING value);
        static MP_STRING GetProperty(MP_STRING name);
        static MP_INT GetProperty(MP_STRING name, bool isVerified);
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) context, MP_INT level, MP_STRING url, MP_STRING file);
    private:
        static MP_PTR(MP_THREAD_MUTEX) __GetMutex();
    private:
        static MP_INT __GetInteger(MP_STRING value);
    private:
        static void __Execute(MP_PTR(extension::AnyPreview) sender, MP_PTR(atom::Trace) context, MP_INT level, MP_STRING url);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
        static void MP_WEB_CLIENT_CALLBACK_DOWNLOAD_COMPLETED(__DownloadCompleted, sender, params);
        static void MP_WEB_CLIENT_CALLBACK_PROGRESS(__DownloadProgress, sender, params);
    private:
        static MP_PTR(MP_THREAD_MUTEX) s_Mutex;
        static MP_PTR(MP_VECTOR(Item)) s_Items;
    };
}
