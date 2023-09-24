#pragma once

#include <metaplatform.core/All.hpp>

namespace extension
{
    MP_CLASS_SHARED AnyPreview
    {
    public:
        MP_CLASS CONSTANT
        {
        public:
            MP_CLASS CONTROL : public pattern::data::Control::CONSTANT
            {
            };
        };
    public:
        MP_CLASS NAME
        {
        public:
            MP_CLASS ALIGNMENT : public pattern::data::Alignment::NAME
            {
            };
        public:
            MP_CLASS COLOR : public pattern::data::Color::NAME
            {
            };
        public:
            MP_CLASS CONTROL : public pattern::data::Control::NAME
            {
            };
        public:
            MP_CLASS CULTURE : public pattern::data::Culture::NAME
            {
            };
        public:
            MP_CLASS EVENT : public pattern::data::Event::NAME
            {
            };
        public:
            MP_CLASS FONT : public pattern::data::Font::NAME
            {
            };
        public:
            MP_CLASS METADATA : public pattern::data::Metadata::NAME
            {
            };
        public:
            MP_CLASS SOURCE : public pattern::data::Source::NAME
            {
            };
        };
    public:
        MP_CLASS STATE
        {
        public:
            MP_CLASS CONTROL : public pattern::data::Control::STATE
            {
            };
        public:
            MP_CLASS FONT : public pattern::data::Font::STATE
            {
            };
        public:
            MP_CLASS MESSAGE : public pattern::data::Message::STATE
            {
            };
        public:
            MP_CLASS WORK
            {
                MP_CONSTANT_STRING(CANCEL, "CANCEL");
                MP_CONSTANT_STRING(EXECUTE, "EXECUTE");
                MP_CONSTANT_STRING(WAIT, "");
            };
        };
    public:
        MP_CLASS TML : public atom::Trace::TML
        {
        };
    public:
        MP_CLASS VARIABLE
        {
        public:
            MP_CLASS DEBUGGING
            {
                MP_CONSTANT_STRING(DATA_NESTING, "METAOUTPUT/DEBUGGING/DATA.NESTING");
                MP_CONSTANT_STRING(DATA_TIMEOUT, "METAOUTPUT/DEBUGGING/DATA.TIMEOUT");
                MP_CONSTANT_STRING(ITEM_COUNT, "METAOUTPUT/DEBUGGING/ITEM.COUNT");
                MP_CONSTANT_STRING(SHOW_PRIVATE, "METAOUTPUT/DEBUGGING/SHOW.PRIVATE");
                MP_CONSTANT_STRING(STACK_SIZE, "METAOUTPUT/DEBUGGING/STACK.SIZE");
                MP_CONSTANT_STRING(STRING_SIZE, "METAOUTPUT/DEBUGGING/STRING.SIZE");
            };
        public:
            MP_CLASS PREVIEW
            {
                MP_CONSTANT_STRING(DOCUMENT_SIZE, "METAOUTPUT/PREVIEW/DOCUMENT.SIZE");
                MP_CONSTANT_STRING(BROWSER_SIZE, "METAOUTPUT/PREVIEW/BROWSER.SIZE");
                MP_CONSTANT_STRING(MEDIA_SIZE, "METAOUTPUT/PREVIEW/MEDIA.SIZE");
                MP_CONSTANT_STRING(TABLE_SIZE, "METAOUTPUT/PREVIEW/TABLE.SIZE");
            };
        };
    public:
        static void Connect(MP_STRING application, MP_STRING extension);
        static void Disconnect();
        static bool Register(MP_STRING extension, MP_PTR(AnyPreview) context);
        static bool Unregister(MP_STRING extension);
        static bool Execute(MP_STRING url);
    public:
        static MP_STRING GetExtension(MP_STRING url);
        static MP_STRING GetFinalText(MP_STRING value);
        static MP_STRING GetPipeName(MP_STRING value);
        static MP_STRING GetProperty(MP_STRING name);
        static MP_INT GetProperty(MP_STRING name, bool isVerified);
        static MP_STRING GetState();
        static void SetState(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) trace, MP_INT level, MP_STRING url, MP_STRING file);
    private:
        static void __Execute(MP_PTR(extension::AnyPreview) sender, MP_PTR(atom::Trace) trace, MP_INT level, MP_STRING url);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
        static void MP_WEB_CLIENT_CALLBACK_DOWNLOAD_COMPLETED(__DownloadCompleted, sender, params);
        static void MP_WEB_CLIENT_CALLBACK_PROGRESS(__DownloadProgress, sender, params);
    private:
        MP_STRING m_Name;
        MP_PTR(MP_THREAD) m_Thread;
    private:
        static MP_PTR(MP_VECTOR(AnyPreview)) s_Items;
    };
}
