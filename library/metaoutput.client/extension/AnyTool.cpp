
#include "../All.hpp"

// extension::AnyTool ######################################################
void extension::AnyTool::Connect(MP_STRING application, MP_STRING extension)
{
    try
    {
        if (MP_STRING_EMPTY(application) == false)
        {
            MP_REGISTRY a_Context;
            {
                MP_REGISTRY_INITIALIZE(a_Context, MP_REGISTRY_ROOT_CURRENT_USER, "Software\\MetaPlatform\\APPLICATION\\", false);
            }
            if (MP_STRING_EMPTY(MP_REGISTRY_GET(a_Context, "USER.ID", "")))
            {
                MP_FILE_EXECUTE("https://www.metaoutput.net/requirements?application=" + application + "&extension=" + extension);
            }
            {
                MP_REGISTRY_FINALIZE(a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
}

void extension::AnyTool::Disconnect()
{
    try
    {
        if ((s_Items != nullptr) && (MP_VECTOR_EMPTY(s_Items) == false))
        {
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context = MP_VECTOR_GET(s_Items, 0);
                {
                    MP_VECTOR_DELETE(s_Items, 0);
                }
                {
                    Execute(a_Context->m_Name, pattern::data::Message::CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
}

bool extension::AnyTool::Register(MP_STRING name, MP_PTR(AnyTool) handler)
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyTool);
        }
        if ((s_Items != nullptr) && (handler != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == name)
                {
                    return false;
                }
            }
            {
                handler->m_Name = name;
                handler->m_Thread = nullptr;
                handler->m_Handlers = MP_NEW MP_MAP(MP_PTR(atom::Trace::AnyHandler));
            }
            {
                MP_THREAD_INITIALIZE(handler->m_Thread, __ThreadExecute);
                MP_THREAD_NAME_SET(handler->m_Thread, name);
                MP_THREAD_APARTMENT_SET(handler->m_Thread, MP_THREAD_APARTMENT_STA);
                MP_THREAD_START(handler->m_Thread, handler);
            }
            {
                MP_VECTOR_APPEND(s_Items, handler);
            }
            return true;
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyTool::Register(MP_STRING name, MP_STRING id, MP_PTR(atom::Trace::AnyHandler) handler)
{
    try
    {
        if ((s_Items != nullptr) && (handler != nullptr) && (MP_STRING_EMPTY(name) == false) && (MP_STRING_EMPTY(id) == false))
        {
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == name)
                {
                    if (MP_MAP_CONTAINS(s_Items[i]->m_Handlers, id) == false)
                    {
                        MP_MAP_APPEND(s_Items[i]->m_Handlers, id, handler);
                    }
                    return true;
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyTool::Unregister(MP_STRING name)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == name)
                {
                    MP_VECTOR_DELETE(s_Items, i);
                    return true;
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyTool::Execute(MP_STRING name, MP_STRING value)
{
    try
    {
        if ((MP_STRING_EMPTY(value) == false) && (MP_STRING_EMPTY(MP_STRING_TRIM(value)) == false))
        {
            auto a_Context1 = (MP_PTR(MP_PIPE_CLIENT))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_WRITESTREAM))nullptr;
            {
                MP_PIPE_CLIENT_INITIALIZE(a_Context1, GetPipeName(name), MP_PIPE_DIRECTION_OUT);
                MP_PIPE_CLIENT_CONNECT(a_Context1, pattern::data::Message::CONSTANT::PIPE::TIMEOUT);
                MP_PIPE_WRITESTREAM_INITIALIZE(a_Context2, a_Context1);
            }
            if (MP_PIPE_CLIENT_CONNECTED(a_Context1))
            {
                MP_PIPE_WRITESTREAM_WRITE(a_Context2, value);
            }
            {
                MP_PIPE_WRITESTREAM_FINALIZE(a_Context2);
                MP_PIPE_CLIENT_FINALIZE(a_Context1);
            }
            return true;
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

// Public ##############
MP_STRING extension::AnyTool::GetAttribute(MP_STRING attributes, MP_STRING name)
{
    try
    {
        auto a_Context = attributes;
        {
            auto a_Index = MP_STRING_INDEXOF(a_Context, pattern::data::Message::TML::COMMENT);
            if (a_Index >= 0)
            {
                a_Context = MP_STRING_SUBSTRING(a_Context, 0, a_Index);
            }
        }
        if (MP_STRING_CONTAINS(a_Context, "\t"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\t", " ");
        }
        if (MP_STRING_CONTAINS(a_Context, "\r"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\r", " ");
        }
        if (MP_STRING_CONTAINS(a_Context, "\n"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\n", " ");
        }
        {
            auto a_Index = MP_STRING_INDEXOF(MP_STRING_UPPER(a_Context), pattern::data::Message::TML::ATTRIBUTE + MP_STRING_UPPER(name) + " ");
            if (a_Index >= 0)
            {
                auto a_Result = (MP_STRING)"";
                auto a_Size = MP_STRING_SIZE_GET(pattern::data::Message::TML::ATTRIBUTE + name);
                auto a_Index1 = MP_STRING_INDEXFROM(MP_STRING_UPPER(a_Context), pattern::data::Message::TML::ATTRIBUTE, a_Index + a_Size);
                if (a_Index1 < 0)
                {
                    a_Result = MP_STRING_TRIM(MP_STRING_SUBSTRING(a_Context, a_Index + a_Size, MP_STRING_SIZE_GET(a_Context) - a_Index - a_Size));
                }
                else
                {
                    a_Result = MP_STRING_TRIM(MP_STRING_SUBSTRING(a_Context, a_Index + a_Size, a_Index1 - a_Index - a_Size));
                }
                if (MP_STRING_CONTAINS(a_Result, pattern::data::Message::TML::NEW_LINE))
                {
                    a_Result = MP_STRING_REPLACE(a_Result, pattern::data::Message::TML::NEW_LINE, "\r\n");
                }
                return a_Result;
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return "";
}

MP_STRING extension::AnyTool::GetPipeName(MP_STRING name)
{
    auto a_Context = ":" + MP_CONVERT_STRING_FROM_INT(MP_PROCESS_ID_GET(MP_PROCESS_CURRENT_GET()), 0);
    if (MP_STRING_CONTAINS(name, a_Context))
    {
        return "urn:metaoutput:tool:" + name;
    }
    else
    {
        return "urn:metaoutput:tool:" + name + a_Context;
    }
}

// Protected ###########
void extension::AnyTool::_Execute(MP_PTR(atom::Trace), MP_INT, MP_STRING)
{
}

// Private #############
void extension::AnyTool::__Execute(MP_PTR(atom::Trace) trace, MP_INT level, MP_STRING attributes)
{
    if (this != nullptr)
    {
        auto a_Id = GetAttribute(attributes, NAME::ATTRIBUTE::ID);
        if (MP_STRING_EMPTY(a_Id))
        {
            _Execute(trace, 0, m_Name);
            return;
        }
        if (MP_MAP_CONTAINS(m_Handlers, a_Id))
        {
            MP_MAP_GET(m_Handlers, a_Id)->Execute(trace, level, m_Name, a_Id, GetAttribute(attributes, NAME::ATTRIBUTE::ACTION), attributes);
        }
    }
}

// Private #############
void extension::AnyTool::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyTool)>(sender);
    auto a_Trace = MP_NEW atom::Trace();
    auto a_IsFound = a_Context == nullptr;
    while (a_IsFound == false)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            {
                MP_PIPE_SERVER_INITIALIZE(a_Context1, extension::AnyTool::GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
                MP_PIPE_READSTREAM_INITIALIZE(a_Context2, a_Context1);
            }
            while (a_IsFound == false)
            {
                try
                {
                    {
                        MP_PIPE_SERVER_CONNECT(a_Context1);
                    }
                    if (MP_PIPE_SERVER_CONNECTED(a_Context1))
                    {
                        auto a_Context3 = MP_PIPE_READSTREAM_READ(a_Context2);
                        {
                            MP_PIPE_SERVER_DISCONNECT(a_Context1);
                        }
                        if (a_Context3 == pattern::data::Message::CONSTANT::PIPE::TERMINATE_REQUEST)
                        {
                            a_IsFound = true;
                            break;
                        }
                        else
                        {
                            a_Context->__Execute(a_Trace->Clear(), 0, a_Context3);
                        }
                        {
                            a_Trace->CommitTransaction();
                            a_Trace->CancelTransaction();
                        }
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    a_Trace->CommitTransaction();
                    a_Trace->CancelTransaction();
                    a_Trace->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
                    MP_THREAD_SLEEP(pattern::data::Message::CONSTANT::PIPE::TIMEOUT);
                    break;
                }
            }
            {
                MP_PIPE_READSTREAM_FINALIZE(a_Context2);
                MP_PIPE_SERVER_FINALIZE(a_Context1);
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            a_Trace->CommitTransaction();
            a_Trace->CancelTransaction();
            a_Trace->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
            break;
        }
    }
}
