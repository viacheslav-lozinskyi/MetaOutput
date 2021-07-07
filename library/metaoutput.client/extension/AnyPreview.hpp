#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyPreview
    {
    public:
        MP_CLASS CONSTANT
        {
            MP_CONSTANT_STRING(OUTPUT_EXECUTE_MUTEX, "METAOUTPUT.EXECUTE.MUTEX");
            MP_CONSTANT_STRING(OUTPUT_PIPE_GENERIC, ".METAOUTPUT.GENERIC");
            MP_CONSTANT_STRING(OUTPUT_PIPE_MUTEX, "METAOUTPUT.PIPE.MUTEX");
            MP_CONSTANT_STRING(OUTPUT_PIPE_NAME, "METAOUTPUT.PIPE");
            MP_CONSTANT_STRING(OUTPUT_PIPE_TERMINATE_REQUEST, "<<<METAOUTPUT.PIPE.TERMINATE>>>");
            MP_CONSTANT_INTEGER(OUTPUT_PIPE_BUFFER_SIZE, 1024 * 1024);
            MP_CONSTANT_INTEGER(OUTPUT_PIPE_CONNECT_COUNT, 5);
            MP_CONSTANT_INTEGER(OUTPUT_PIPE_TIMEOUT, 500);
            MP_CONSTANT_INTEGER(OUTPUT_PREVIEW_ITEM_HEIGHT, 19);
            MP_CONSTANT_INTEGER(OUTPUT_PREVIEW_MIN_SIZE, 2);
            MP_CONSTANT_INTEGER(OUTPUT_PREVIEW_MIN_WIDTH, 200);
            MP_CONSTANT_INTEGER(OUTPUT_PREVIEW_PAGE_INDENT, 10);
            MP_CONSTANT_INTEGER(OUTPUT_PREVIEW_PAGE_BREAK, 7);
        };
    public:
        MP_CLASS NAME : public atom::Trace::NAME
        {
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
                MP_CONSTANT_STRING(PREVIEW_MEDIA_SIZE, "METAOUTPUT/PREVIEW/MEDIA.SIZE");
                MP_CONSTANT_STRING(PREVIEW_STATUS, "METAOUTPUT/PREVIEW/STATUS");
                MP_CONSTANT_STRING(PREVIEW_TABLE_SIZE, "METAOUTPUT/PREVIEW/TABLE.SIZE");
                MP_CONSTANT_STRING(PREVIEW_WIDTH, "METAOUTPUT/PREVIEW/WIDTH");
            };
        };
    private:
        MP_CLASS Item
        {
        public:
            MP_STRING m_Name;
            MP_PTR(atom::Trace) m_Context;
            MP_PTR(AnyPreview) m_Extension;
            MP_PTR(MP_THREAD) m_Thread;
            MP_PIPE_CLIENT m_Pipe;
        };
    public:
        static void Connect();
        static void Disconnect();
        static void Register(MP_STRING extension, MP_PTR(AnyPreview) context);
        static void Execute(MP_STRING url);
        static bool Send(MP_STRING value);
    public:
        static MP_STRING GetExtension(MP_STRING url);
        static MP_STRING GetName(MP_STRING value);
        static MP_STRING GetPipeName(MP_STRING value);
        static MP_STRING GetFinalText(MP_STRING value);
        static MP_STRING GetUrlPreview(MP_STRING url);
        static MP_STRING GetUrlPreview(MP_STRING url, MP_STRING extension);
        static MP_STRING GetProperty(MP_STRING name);
        static MP_INT GetProperty(MP_STRING name, bool isVerified);
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) context, MP_INT level, MP_STRING url, MP_STRING file);
    private:
        static MP_PTR(MP_THREAD_MUTEX) __GetMutex();
    private:
        static MP_STRING __GetFileName(MP_STRING url);
        static MP_STRING __GetFileUrl(MP_STRING url);
        static MP_STRING __GetProxyFolder();
        static MP_INT __GetInteger(MP_STRING value);
    private:
        static bool __SendRequest(MP_STRING name, MP_STRING value);
        static void __Execute(MP_PTR(extension::AnyPreview) sender, MP_PTR(atom::Trace) context, MP_INT level, MP_STRING url);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
        static void MP_WEB_CLIENT_CALLBACK_DOWNLOAD_COMPLETED(__DownloadCompleted, sender, params);
        static void MP_WEB_CLIENT_CALLBACK_PROGRESS(__DownloadProgress, sender, params);
    private:
        static MP_PTR(MP_THREAD_MUTEX) s_Mutex;
        static MP_PTR(MP_VECTOR(Item)) s_Items;
        static MP_PTR(MP_VECTOR(Item)) s_Pipes;
    };
}
