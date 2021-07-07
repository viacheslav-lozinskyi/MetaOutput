
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnySource::Item)) extension::AnySource::s_Items = nullptr;
#endif

// extension::AnySource #######################################################
void extension::AnySource::Connect()
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(Item);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
    }
}

void extension::AnySource::Register(MP_STRING name, MP_PTR(AnySource) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            auto a_Context = MP_NEW Item();
            {
                a_Context->m_Name = name;
                a_Context->m_Context = MP_NEW atom::Trace();
                a_Context->m_Extension = context;
                a_Context->m_Thread = nullptr;
            }
            {
                MP_THREAD_INITIALIZE(a_Context->m_Thread, __ThreadExecute);
                MP_THREAD_START(a_Context->m_Thread, a_Context);
            }
            {
                MP_VECTOR_APPEND(s_Items, a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
    }
}

// Protected ###########
void extension::AnySource::_Execute(MP_PTR(atom::Trace))
{
}

// Private #############
void extension::AnySource::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(Item)>(sender);
    if (a_Context != nullptr)
    {
        while (a_Context->m_Thread != nullptr)
        {
            try
            {
                {
                    a_Context->m_Extension->_Execute(a_Context->m_Context);
                }
                {
                    MP_THREAD_SLEEP(50);
                }
            }
            catch (MP_PTR(MP_EXCEPTION) ex)
            {
                MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
            }
        }
    }
}
