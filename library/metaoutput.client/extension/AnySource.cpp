
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnySource)) extension::AnySource::s_Items = nullptr;
MP_BOOL extension::AnySource::s_IsTerminated = false;
#endif

// extension::AnySource #######################################################
void extension::AnySource::Connect()
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnySource);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnySource::Disconnect()
{
    try
    {
        if ((s_Items != nullptr) && (MP_VECTOR_EMPTY(s_Items) == false))
        {
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                s_Items[i]->m_Thread = nullptr;
            }
        }
        {
            s_IsTerminated = false;
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

bool extension::AnySource::Register(MP_STRING name, MP_PTR(AnySource) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            {
                context->m_Name = (MP_STRING_INDEXOF(name, "urn:") == 0 ? "" : "urn:metaoutput:source:") + MP_STRING_LOWER(name);
                context->m_Context = MP_NEW atom::Trace();
                context->m_Thread = nullptr;
            }
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == context->m_Name)
                {
                    return false;
                }
            }
            {
                MP_THREAD_INITIALIZE(context->m_Thread, __ThreadExecute);
                MP_THREAD_NAME_SET(context->m_Thread, context->m_Name);
                MP_THREAD_START(context->m_Thread, context);
            }
            {
                MP_VECTOR_APPEND(s_Items, context);
            }
            return true;
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
    return false;
}

// Protected ###########
void extension::AnySource::_Execute(MP_PTR(atom::Trace))
{
}

// Private #############
void extension::AnySource::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnySource)>(sender);
    if (a_Context != nullptr)
    {
        while ((a_Context->m_Thread != nullptr) && (s_IsTerminated == false))
        {
            try
            {
                a_Context->_Execute(a_Context->m_Context);
            }
            catch (MP_PTR(MP_EXCEPTION) ex)
            {
                MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
            }
            {
                MP_THREAD_SLEEP(50);
            }
        }
    }
}
